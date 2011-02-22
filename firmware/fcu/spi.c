#include "spi.h"
#include <string.h>

//#include "/usr/lib/avr/include/avr/iox128a3.h"

// initialize SPI interface on PORTD:4-7
// PORTD:4 - SS   (active low)
// PORTD:5 - MOSI
// PORTD:6 - MISO
// PORTD:7 - SCK
void init_spi(void)
{
    PORTE.DIR = (1<<7) | (1<<5) | (1<<4);   // configure MOSI, MOT_EN, CLK as outputs on PORTE
    //PORTB.DIR = 0xFF;                       // set SS pins as outputs
    PORTB.DIRSET = 1<<SS0;
    PORTB.DIRSET = 1<<SS1;
    PORTB.OUT = 0xFF;                       // set SS pins high
    // enable SPI master mode, CLK/128 (@32MHz=>250kHz)
    SPIE.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_2_gc | SPI_PRESCALER_DIV64_gc;
    SPIE.INTCTRL = SPI_INTLVL_LO_gc;
};
