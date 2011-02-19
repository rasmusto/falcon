#include "spi.h"
#include "shared.h"
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
    PORTB.DIR = 0xFF;                       // set SS pins as outputs
    PORTB.OUT = 0xFF;                       // set SS pins high
    // enable SPI master mode, CLK/128 (@32MHz=>250kHz)
    SPIE.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV128_gc;
};

void spi_write(char data, uint8_t pin)
{
    PORTB.OUT &= ~(1<<pin);     // lower ss line indicating start of transfer
    SPIE.DATA = data;           // initiate write
    // wait for transfer complete
    while(!(SPIE.STATUS & (1<<7)));
    PORTB.OUT |= (1<<pin);      // raise ss line indicating end of transfer
};

void spi_write_read_multi(char * tx_pkt, char * rx_pkt, uint8_t len, uint8_t pin)
{
    PORTB.OUT &= ~(1<<pin);     // lower ss line indicating start of transfer
    int i;
    for(i = 0; i < len; i++)
    {
        SPIE.DATA = tx_pkt[i];           // initiate write
        // wait for transfer complete
        while(!(SPIE.STATUS & (1<<7)));
        rx_pkt[i] = SPIE.DATA;
    }
    PORTB.OUT |= (1<<pin);      // raise ss line indicating end of transfer
}

char spi_read(uint8_t pin)
{
    // write 0x00 and read back results clocked into data buffer
    spi_write(0x00, pin);
    return SPIE.DATA;
};

char spi_write_read(char data, uint8_t pin)
{
    spi_write(data, pin);
    return SPIE.DATA;
};
