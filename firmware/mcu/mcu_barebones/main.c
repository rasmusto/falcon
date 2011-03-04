//#include "/usr/lib/avr/include/avr/iox128a3.h"

#define F_CPU 32000000UL
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "spi_driver.h"


void spiInit (void);

volatile uint8_t spiBuffer[8];

int main (void) {

    while(1){}
	spiInit ();
	sei();
	
	while (1) 
    {
        SPIC.DATA = 0xBB;
    }
	
}

void spiInit () 
{
    SPIC.CTRL = (0<<SPI_CLK2X_bp) | (1<<SPI_ENABLE_bp) | (0<<SPI_DORD_bp) | (0<<SPI_MASTER_bp) | (1<<SPI_MODE1_bp) | (0<<SPI_MODE0_bp) | (1<<SPI_PRESCALER1_bp) | (0<<SPI_PRESCALER0_bp);
    SPIC.INTCTRL = SPI_INTLVL_LO_gc;
    PORTC.DIRSET = SPI_MISO_bm;
}
