#include "fcu.h"

/* USART Initialization */
ISR(USART<XX>_RXC_vect)
{
    stdout = &debugOut;
}

/* SPI Initialization */
static void init_spi (void)
{
    /* Init signal select pins with wired AND pull-up. */
    PORTC.DIRSET = PIN4_bm;
    PORTC.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;

    /* Set SS output to high. (No slave addressed). */
    PORTC.OUTSET = PIN4_bm;

    /* Initialize SPI master on port C. */
    SPI_MasterInit(     &spiMasterC,
                        &SPIC,
                        &PORTC,
                        false,
                        SPI_MODE_0_gc,
                        SPI_INTLVL_LO_gc,
                        false,
                        SPI_PRESCALER_DIV4_gc);
    /* Enable low and medium level interrupts in the interrupt controller. */
    PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
    sei();

	/* Create data packet (SS to slave by PC4) */
	SPI_MasterCreateDataPacket(&dataPacket,
	                           sendData,
	                           receivedData,
	                           NUM_BYTES + 1,
	                           &PORTC, //THESE SHOULD BE SET TO SS PINS
	                           PIN4_bm);

	/* Transmit and receive first data byte. */
	uint8_t status;
	do {
		status = SPI_MasterInterruptTransceivePacket(&spiMasterC, &dataPacket);
	} while (status != SPI_OK);

	/* Wait for transmission to complete. */
	while (dataPacket.complete == false) {

	}

	/* Check that correct data was received. Assume success at first. */
	success = true;
	for (uint8_t i = 0; i < NUM_BYTES; i++) {
		if (receivedData[i + 1] != (uint8_t)(sendData[i] + 1)) {
			success = false;
		}
	}
	while(true) {
		nop();
	}
}

ISR(SPIC_INT_vect)
{
	SPI_MasterInterruptHandler(&spiMasterC);
}

ISR(SPID_INT_vect)
{
	/* Get received data. */
	uint8_t data = SPI_SlaveReadByte(&spiSlaveD);

	/* Increment data. */
	data++;

	/* Send back incremented value. */
	SPI_SlaveWriteByte(&spiSlaveD, data);
}

int main (void) 
{
    init_spi();
    while(1);
    return;
}
