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

int main (void) 
{
	spiInit ();
    sei();
    PORTB.DIRSET = PIN0_bm; //SS0
	
	while (1) 
    {
        PORTB.OUTCLR = PIN0_bm;
        //PORTB.OUT = 0b00000000;
        SPIE.DATA = 0xAA;
        //while(!(SPIE.STATUS & (1<<7)))
        _delay_us(100);
        PORTB.OUTSET = PIN0_bm;
        //PORTB.OUT = 0b00000001;
        _delay_us(100);
    }
	
}

void spiInit () 
{
    //SPIE.CTRL = (0<<SPI_CLK2X_bp) | (1<<SPI_ENABLE_bp) | (0<<SPI_DORD_bp) | (1<<SPI_MASTER_bp) | (1<<SPI_MODE1_bp) | (0<<SPI_MODE0_bp) | (1<<SPI_PRESCALER1_bp) | (0<<SPI_PRESCALER0_bp);
    PORTE.DIRSET = PIN5_bm; //MOSI
    PORTE.DIRSET = PIN7_bm; //CLK
    PORTB.DIRSET = PIN0_bm; //SS0
    SPIE.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_2_gc | SPI_PRESCALER_DIV64_gc;
    SPIE.INTCTRL = SPI_INTLVL_LO_gc;
    PMIC.CTRL |= PMIC_LOLVLEX_bm;
}
