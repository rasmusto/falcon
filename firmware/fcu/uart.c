#include "uart.h"
#include "usart_driver.h"

void init_xbee_uart (int8_t bScale, uint16_t bSel) 
{
    PORTF.DIRCLR    =   PIN2_bm;
    PORTF.DIRSET    =   PIN3_bm;

    /* USARTF0, 8 Data bits, No Parity, 1 Stop bit. */
    USART_Format_Set (&USARTF0, USART_CHSIZE_8BIT_gc,
                     USART_PMODE_DISABLED_gc, 0);
                     
    /* Enable RXC interrupt. */
    USART_RxdInterruptLevel_Set (&USARTF0, USART_RXCINTLVL_LO_gc);

    USART_Baudrate_Set (&USARTF0, bSel, bScale);
    
    /* Enable both RX and TX. */
    USART_Rx_Enable (&USARTF0);
    USART_Tx_Enable (&USARTF0);

    /* Enable PMIC interrupt level low. */
    PMIC.CTRL |= PMIC_LOLVLEX_bm;
}

void init_usb_uart (int8_t bScale, uint16_t bSel) 
{
    PORTC.DIRCLR    =   PIN6_bm;
    PORTC.DIRSET    =   PIN7_bm;

    /* USARTC1, 8 Data bits, No Parity, 1 Stop bit. */
    USART_Format_Set (&USARTC1, USART_CHSIZE_8BIT_gc,
                     USART_PMODE_DISABLED_gc, 0);
                     
    /* Enable RXC interrupt. */
    USART_RxdInterruptLevel_Set (&USARTC1, USART_RXCINTLVL_LO_gc);

    USART_Baudrate_Set (&USARTC1, bSel, bScale);
    
    /* Enable both RX and TX. */
    USART_Rx_Enable (&USARTC1);
    USART_Tx_Enable (&USARTC1);

    /* Enable PMIC interrupt level low. */
    PMIC.CTRL |= PMIC_LOLVLEX_bm;
}

void init_rs232_uart (int8_t bScale, uint16_t bSel) 
{
    PORTD.DIRCLR    =   PIN6_bm;
    PORTD.DIRSET    =   PIN7_bm;

    /* USARTD1, 8 Data bits, No Parity, 1 Stop bit. */
    USART_Format_Set (&USARTD1, USART_CHSIZE_8BIT_gc,
                     USART_PMODE_DISABLED_gc, 0);
                     
    /* Enable RXC interrupt. */
    USART_RxdInterruptLevel_Set (&USARTD1, USART_RXCINTLVL_LO_gc);

    USART_Baudrate_Set (&USARTD1, bSel, bScale);
    
    /* Enable both RX and TX. */
    USART_Rx_Enable (&USARTD1);
    USART_Tx_Enable (&USARTD1);

    /* Enable PMIC interrupt level low. */
    PMIC.CTRL |= PMIC_LOLVLEX_bm;
}

void init_sonar_uart (int8_t bScale, uint16_t bSel) 
{
    PORTE.DIRCLR    =   PIN2_bm;
    PORTE.DIRSET    =   PIN3_bm;

    /* USARTE0, 8 Data bits, No Parity, 1 Stop bit. */
    USART_Format_Set (&USARTE0, USART_CHSIZE_8BIT_gc,
                     USART_PMODE_DISABLED_gc, 0);
                     
    /* Enable RXC interrupt. */
    USART_RxdInterruptLevel_Set (&USARTE0, USART_RXCINTLVL_LO_gc);

    USART_Baudrate_Set (&USARTE0, bSel, bScale);
    
    /* Enable both RX and TX. */
    USART_Rx_Enable (&USARTE0);
    USART_Tx_Enable (&USARTE0);

    /* Enable PMIC interrupt level low. */
    PMIC.CTRL |= PMIC_LOLVLEX_bm;
}

void putchar_xbee (char c) 
{ while ( !( USARTF0.STATUS & USART_DREIF_bm) ); 
    USARTF0.DATA = c; }

void putchar_usb (char c) {
    while ( !( USARTC1.STATUS & USART_DREIF_bm) ); 
    USARTC1.DATA = c; }

void putchar_rs232 (char c) 
{ while ( !( USARTD1.STATUS & USART_DREIF_bm) );
    USARTD1.DATA = c; }

void putchar_sonar (char c)
{ while ( !( USARTE0.STATUS & USART_DREIF_bm) );
    USARTE0.DATA = c; }
