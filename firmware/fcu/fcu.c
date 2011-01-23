#include "fcu.h"

/* USART Initialization */
/*
ISR(USART<XX>_RXC_vect)
{
    stdout = &debugOut;
}
*/

/* SPI Initialization */
static void spi_init (void)
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
    uint8_t i;
	for (i = 0; i < NUM_BYTES; i++) {
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

static void initUarts (void)
{
	PORTD.DIRCLR   = PIN2_bm;
	PORTD.DIRCLR   = PIN6_bm;
	PORTC.DIRCLR   = PIN2_bm;
	PORTC.DIRCLR   = PIN6_bm;
	
	// Set pins to inverting
	PORTD.PIN2CTRL= 0b01000000;
	PORTD.PIN6CTRL= 0b01000000;
	PORTC.PIN2CTRL= 0b01000000;
	PORTC.PIN6CTRL= 0b01000000;
 
    // BSEL = 51 so at 32mhz clock, baud rate should be 38400

	/* USARTD0, 8 Data bits, No Parity, 2 Stop bit. */
	USART_Format_Set(&USARTD0, USART_CHSIZE_8BIT_gc,
                     USART_PMODE_DISABLED_gc, 1);
	/* USARTD1, 8 Data bits, No Parity, 2 Stop bit. */
	USART_Format_Set(&USARTD1, USART_CHSIZE_8BIT_gc,
                     USART_PMODE_DISABLED_gc, 1);
	/* USARTC0, 8 Data bits, No Parity, 2 Stop bit. */
	USART_Format_Set(&USARTC0, USART_CHSIZE_8BIT_gc,
                     USART_PMODE_DISABLED_gc, 1);
	/* USARTC1, 8 Data bits, No Parity, 2 Stop bit. */
	USART_Format_Set(&USARTC1, USART_CHSIZE_8BIT_gc,
                     USART_PMODE_DISABLED_gc, 1);
 
    //~ USARTC0.BAUDCTRLB = 0;			// BSCALE = 0 as well
    USARTC0.BAUDCTRLA = 0b00110111;
    USARTC1.BAUDCTRLA = 0b00110111;
    USARTD0.BAUDCTRLA = 0b00110111;
    USARTD1.BAUDCTRLA = 0b00110111;
    
    USARTC0.BAUDCTRLB = 0b10110100;
    USARTC1.BAUDCTRLB = 0b10110100;
    USARTD0.BAUDCTRLB = 0b10110100;
    USARTD1.BAUDCTRLB = 0b10110100;
 
    /* Enable TX. */
	USART_Tx_Enable(&USARTD0);
	USART_Tx_Enable(&USARTD1);
	USART_Tx_Enable(&USARTC0);
	USART_Tx_Enable(&USARTC1);
}

/*
static int putcharimu (char c, FILE *stream, USART_t usart)
{
    if (c == '\n')
        putcharimu('\r', stream);
    while ( !( usart.STATUS & USART_DREIF_bm) ); // Wait for the transmit buffer to be empty
    usart.DATA = c; // Put our character into the transmit buffer
    return 0;
}
*/

int main (void) 
{
    PORTA.DIRSET=0b11110000;
    PORTF.DIRSET=0b11110000;
    while(1)
    {
        LED_1_RED_ON();
        LED_1_GREEN_ON();
        LED_2_RED_ON();
        LED_2_GREEN_ON();
        LED_3_RED_ON();
        LED_3_GREEN_ON();
        LED_4_RED_ON();
        LED_4_GREEN_ON();
        _delay_ms(500);
        LED_1_RED_OFF();
        LED_1_GREEN_OFF();
        LED_2_RED_OFF();
        LED_2_GREEN_OFF();
        LED_3_RED_OFF();
        LED_3_GREEN_OFF();
        LED_4_RED_OFF();
        LED_4_GREEN_OFF();
        _delay_ms(500);
    }
    return;
}
