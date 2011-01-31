#include "spi.h"
#include <string.h>

// initialize SPI interface on PORTD:4-7
// PORTD:4 - SS   (active low)
// PORTD:5 - MOSI
// PORTD:6 - MISO
// PORTD:7 - SCK
void init_spi(void)
{
    PORTE.DIR = (1<<7) | (1<<5) | (1<<4);   // configure MOSI, MOT_EN, CLK as outputs on PORTE
    PORTB.DIR = 0xFF;                       // set SS pins as outputs
    PORTB.OUT = 0xFF;                       // set SS pins high
    // enable SPI master mode, CLK/64 (@32MHz=>500KHz)
    SPIE.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV64_gc;
};

void spi_write(char data, uint8_t pin)
{
    PORTB.OUT &= ~(1<<pin);     // lower ss line indicating start of transfer
    SPIE.DATA = data;           // initiate write
    // wait for transfer complete
    while(!(SPIE.STATUS & (1<<7)));
    PORTB.OUT |= (1<<pin);      // raise ss line indicating end of transfer
};

void spi_write_multi(char * packet, uint8_t length, uint8_t pin)
{
    PORTB.OUT &= ~(1<<pin);     // lower ss line indicating start of transfer
    int i;
    char * tmp;
    memcpy(packet, tmp, length);
    for(i = 0; i < length; i++)
    {
        SPIE.DATA = tmp[i];           // initiate write
        // wait for transfer complete
        while(!(SPIE.STATUS & (1<<7)));
    }
    PORTB.OUT |= (1<<pin);      // raise ss line indicating end of transfer
}

char spi_read(uint8_t pin)
{
    // write 0x00 and read back results clocked into data buffer
    spi_write(0, pin);
    return SPIE.DATA;
};

char spi_write_read(char data, uint8_t pin)
{
    spi_write(data, pin);
    return SPIE.DATA;
};
