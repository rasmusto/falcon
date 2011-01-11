/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  XMEGA SPI polled driver example source.
 *
 *      This file contains an example application that demonstrates the polled
 *      SPI drivers.
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
 * $Revision: 771 $
 * $Date: 2007-11-06 14:54:00 +0100 (ti, 06 nov 2007) $  \n
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


/*! \brief The number of test data bytes. */
#define NUM_BYTES     4

/* Global variables */

/*! \brief SPI master module on PORT C. */
SPI_Master_t spiMasterC;

/*! \brief SPI slave module on PORT D. */
SPI_Slave_t spiSlaveD;

/*! \brief SPI Data packet */
SPI_DataPacket_t dataPacket;

/*! \brief Test data to send from master. */
uint8_t masterSendData[NUM_BYTES] = {0x11, 0x22, 0x33, 0x44};

/*! \brief Data received from slave. */
uint8_t masterReceivedData[NUM_BYTES];

/*! \brief Result of the test. */
bool success = true;



/*! \brief Test function.
 *
 *  This function tests the SPI master and slave drivers in polled operation,
 *  with a master (on port C) communicating with a slave (on port D).
 *
 *  Hardware setup:
 *
 *    - Connect PC4 to PD4 (SS)
 *    - Connect PC5 to PD5 (MOSI)
 *    - Connect PC6 to PD6 (MISO)
 *    - Connect PC7 to PD7 (SCK)
 *
 *  The drivers are tested in two phases:
 *
 *  1: Data is transmitted on byte at a time from the master to the slave.
 *     The slave increments the received data and sends it back. The master reads
 *     the data from the slave and verifies that it equals the data sent + 1.
 *
 *  2: Data is transmitted 4 bytes at a time to the slave. As the master sends
 *     a byte to the slave, the preceding byte is sent back to the master.
 *     When all bytes have been sent, it is verified that the last 3 bytes
 *     received at the master, equal the first 3 bytes sent.
 *
 *  The variable, 'success', will be non-zero when the function reaches the
 *  infinite for-loop if the test was successful.
 */
int main(void)
{
	/* Init SS pin as output with wired AND and pull-up. */
	PORTC.DIRSET = PIN4_bm;
	PORTC.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;

	/* Set SS output to high. (No slave addressed). */
	PORTC.OUTSET = PIN4_bm;

	/* Instantiate pointer to ssPort. */
	PORT_t *ssPort = &PORTC;

	/* Initialize SPI master on port C. */
	SPI_MasterInit(&spiMasterC,
	               &SPIC,
	               &PORTC,
	               false,
	               SPI_MODE_0_gc,
	               SPI_INTLVL_OFF_gc,
	               false,
	               SPI_PRESCALER_DIV4_gc);

	/* Initialize SPI slave on port D. */
	SPI_SlaveInit(&spiSlaveD,
	              &SPID,
	              &PORTD,
	              false,
				  SPI_MODE_0_gc,
				  SPI_INTLVL_OFF_gc);

	/* PHASE 1: Transceive individual bytes. */

	/* MASTER: Pull SS line low. This has to be done since
	 *         SPI_MasterTransceiveByte() does not control the SS line(s). */
	SPI_MasterSSLow(ssPort, PIN4_bm);

	for(uint8_t i = 0; i < NUM_BYTES; i++) {
		/* MASTER: Transmit data from master to slave. */
		SPI_MasterTransceiveByte(&spiMasterC, masterSendData[i]);

		/* SLAVE: Wait for data to be available. */
		while (SPI_SlaveDataAvailable(&spiSlaveD) == false) {

		}

		/* SLAVE: Get the byte received. */
		uint8_t slaveByte = SPI_SlaveReadByte(&spiSlaveD);

		/* SLAVE: Increment received byte and send back. */
		slaveByte++;
		SPI_SlaveWriteByte(&spiSlaveD, slaveByte);

		/* MASTER: Transmit dummy data to shift data from slave to master. */
		uint8_t masterReceivedByte = SPI_MasterTransceiveByte(&spiMasterC, 0x00);

		/* MASTER: Check if the correct value was received. */
		if (masterReceivedByte != (masterSendData[i] + 1) ) {
			success = false;
		}
	}

	/* MASTER: Release SS to slave. */
	SPI_MasterSSHigh(ssPort, PIN4_bm);

	/* PHASE 2: Transceive data packet. */

	/* Create data packet (SS to slave by PC4). */
	SPI_MasterCreateDataPacket(&dataPacket,
	                           masterSendData,
	                           masterReceivedData,
	                           NUM_BYTES,
	                           &PORTC,
	                           PIN4_bm);

	/* Transceive packet. */
	SPI_MasterTransceivePacket(&spiMasterC, &dataPacket);

	/* Check that correct data was received. Assume success at first. */
	for (uint8_t i = 0; i < NUM_BYTES - 1; i++) {
		if (masterReceivedData[i + 1] != masterSendData[i]) {
			success = false;
		}
	}

	while(true) {
		nop();
	}
}
