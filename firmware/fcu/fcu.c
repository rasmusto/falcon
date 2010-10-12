#include "fcu.h"
/* Initialize UARTs used for motor communication */
static void initMotorUart (void)
{
    PORTD.DIRCLR   = PIN2_bm;
    PORTD.DIRCLR   = PIN6_bm;
    PORTC.DIRCLR   = PIN2_bm;
    PORTC.DIRCLR   = PIN6_bm;

    /* Set pins to inverting */
    PORTD.PIN2CTRL= 0b01000000;
    PORTD.PIN6CTRL= 0b01000000;
    PORTC.PIN2CTRL= 0b01000000;
    PORTC.PIN6CTRL= 0b01000000;

    /* BSEL = 51 so at 32mhz clock, baud rate should be 38400 */

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

    /* Enable PMIC interrupt level low. */
    PMIC.CTRL |= PMIC_LOLVLEX_bm;
}

static void initIMUUart (void)
{
    PORTE.DIRCLR	=	PIN2_bm;
    PORTE.DIRSET	=	PIN3_bm;

    /* USARTE0, 8 Data bits, No Parity, 1 Stop bit. */
    USART_Format_Set(&USARTE0, USART_CHSIZE_8BIT_gc,
            USART_PMODE_DISABLED_gc, 0);

    /* Enable RXC interrupt. */
    USART_RxdInterruptLevel_Set(&USARTE0, USART_RXCINTLVL_LO_gc);

    // bscale = -6 = 0b1010
    // bsel = 1047 
    USART_Baudrate_Set(&USARTE0, 1070, -6);

    /* Enable both RX and TX. */
    USART_Rx_Enable(&USARTE0);
    USART_Tx_Enable(&USARTE0);

    /* Enable PMIC interrupt level low. */
    PMIC.CTRL |= PMIC_LOLVLEX_bm;
}

static void initDebugUart (void)
{
    PORTF.DIRCLR	=	PIN2_bm;
    PORTF.DIRSET	=	PIN3_bm;

    /* USARTF0, 8 Data bits, No Parity, 1 Stop bit. */
    USART_Format_Set(&USARTF0, USART_CHSIZE_8BIT_gc,
            USART_PMODE_DISABLED_gc, 0);

    //~ USARTC0.BAUDCTRLB = 0;			// BSCALE = 0 as well
    USARTF0.BAUDCTRLA = 229; // 19200 baud
    USARTF0.BAUDCTRLB = 188;

    /* Enable RXC interrupt. */
    USART_RxdInterruptLevel_Set(&USARTF0, USART_RXCINTLVL_LO_gc);

    /* Enable PMIC interrupt level low. */
    PMIC.CTRL |= PMIC_LOLVLEX_bm;

    /* Enable both RX and TX. */
    USART_Rx_Enable(&USARTF0);
    USART_Tx_Enable(&USARTF0);
}

static void initCtrlUart (void)
{
    PORTE.DIRCLR	=	PIN6_bm;
    PORTE.DIRSET	=	PIN7_bm;

    /* USARTE1, 8 Data bits, No Parity, 1 Stop bit. */
    USART_Format_Set(&USARTE1, USART_CHSIZE_8BIT_gc, USART_PMODE_DISABLED_gc, 0);

    //~ USARTC0.BAUDCTRLB = 0;			// BSCALE = 0 as well
    USARTE1.BAUDCTRLA = 51;
    USARTE1.BAUDCTRLB = 0;

    /* Enable RXC interrupt. */
    USART_RxdInterruptLevel_Set(&USARTE1, USART_RXCINTLVL_LO_gc);

    /* Enable both RX and TX. */
    USART_Rx_Enable(&USARTE1);
    USART_Tx_Enable(&USARTE1);
}
