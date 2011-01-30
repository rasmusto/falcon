#include "spi.h"

void init_spi (void)
{
    /* Init signal select pins with wired AND pull-up. */
    PORTB.DIRSET = 0b11111111;

    //IGNORING THIS FOR NOW
    //PORTC.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;

    /* Set SS output to high. (No slave addressed). */
    PORTB.OUTSET = 0b11111111;

    /* Initialize SPI master on port E. */
    SPI_MasterInit(     &spiMasterE,
                        &SPIE,
                        &PORTE,
                        false,
                        SPI_MODE_0_gc,
                        SPI_INTLVL_LO_gc,
                        false,
                        SPI_PRESCALER_DIV4_gc);
    /* Enable low and medium level interrupts in the interrupt controller. */
    PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
}
