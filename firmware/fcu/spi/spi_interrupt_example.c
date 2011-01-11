/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  XMEGA SPI interrupt-driven driver example source.
 *
 *      This file contains an example application that demonstrates the SPI
 *      interrupt-driven driver.
 *
 * \par Application note:
 *      AVR1309: Using the XMEGA SPI
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * $Revision: 763 $
 * $Date: 2007-11-06 14:51:56 +0100 (ti, 06 nov 2007) $  \n
 *
 * Copyright (c) 2008, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include "avr_compiler.h"
#include "spi_driver.h"

/*! \brief Number of test data bytes. */
#define NUM_BYTES   2

/* Global variables. */

/*! \brief SPI master on PORT C. */
SPI_Master_t spiMasterC;

/*! \brief SPI slave on PORT D. */
SPI_Slave_t spiSlaveD = {NULL, NULL};

/*! \brief Data packet. */
SPI_DataPacket_t dataPacket;

/*! \brief Test data to send. */
const uint8_t sendData[NUM_BYTES + 1] = { 0x55, 0xaa, 0x00 };

/*! \brief Buffer for test data reception. */
uint8_t receivedData[NUM_BYTES + 1];

/*! \brief Result of the example test. */
bool success;



/*! \brief Test function.
 *
 *  This function tests the SPI master and slave drivers in interrupt-driven
 *  operation, with a master (on port C) communicating with a slave (on port D).
 *
 *  Hardware setup:
 *
 *    - Connect PC4 to PD4 (SS)
 *    - Connect PC5 to PD5 (MOSI)
 *    - Connect PC6 to PD6 (MISO)
 *    - Connect PC7 to PD7 (SCK)
 *
 *  The driver is tested by transmitting data from the master to the slave.
 *  The slave increments the received data and sends it back. The master reads
 *  the data from the slave and verifies that it equals the data sent + 1.
 *
 *  The first data transaction is initiated by the main routine. When a
 *  transaction has finished, an interrupt will be triggered which will start
 *  new transactions until all bytes have been transceived.
 *
 *  The variable, 'success', will be non-zero when the function reaches the
 *  infinite for-loop if the test was successful.
 *
 *  \note This example uses multilevel interrupts. For more information on how
 *        to use the interrupt controller, refer to application note AVR1305.
 */
int main( void )
{
	/* Init SS pin as output with wired AND and pull-up. */
	PORTC.DIRSET = PIN4_bm;
	PORTC.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;

	/* Set SS output to high. (No slave addressed). */
	PORTC.OUTSET = PIN4_bm;

	/* Initialize SPI master on port C. */
	SPI_MasterInit(&spiMasterC,
	               &SPIC,
	               &PORTC,
				   false,
	               SPI_MODE_0_gc,
	               SPI_INTLVL_LO_gc,
	               false,
	               SPI_PRESCALER_DIV4_gc);

	/* Initialize SPI slave on port D. */
	SPI_SlaveInit(&spiSlaveD,
	              &SPID,
	              &PORTD,
	              false,
	              SPI_MODE_0_gc,
	              SPI_INTLVL_MED_gc);

	/* Enable low and medium level interrupts in the interrupt controller. */
	PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	sei();

	/* Create data packet (SS to slave by PC4) */
	SPI_MasterCreateDataPacket(&dataPacket,
	                           sendData,
	                           receivedData,
	                           NUM_BYTES + 1,
	                           &PORTC,
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


/*! \brief SPI master interrupt service routine.
 *
 *  The interrupt service routines calls one common function,
 *  SPI_MasterInterruptHandler(SPI_Master_t *spi),
 *  passing information about what module to handle.
 *
 *  Similar ISRs must be added if other SPI modules are to be used.
 */
ISR(SPIC_INT_vect)
{
	SPI_MasterInterruptHandler(&spiMasterC);
}



/*! \brief SPI slave interrupt service routine.
 *
 *  This ISR increments the received data and stores it in the
 *  data register, read to be shifted back by the master.
 *
 *  If more extensive computation is needed, it is recommended
 *  to do this in a function, which is then called by the ISR.
 *
 *  Similar ISRs must be added if other SPI modules are to be used.
 */
ISR(SPID_INT_vect)
{
	/* Get received data. */
	uint8_t data = SPI_SlaveReadByte(&spiSlaveD);

	/* Increment data. */
	data++;

	/* Send back incremented value. */
	SPI_SlaveWriteByte(&spiSlaveD, data);
}
