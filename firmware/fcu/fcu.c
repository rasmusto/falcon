#include "fcu.h"

static FILE usb_out = FDEV_SETUP_STREAM (putchar_usb, NULL, _FDEV_SETUP_WRITE);
static FILE rs232_out = FDEV_SETUP_STREAM (putchar_rs232, NULL, _FDEV_SETUP_WRITE);

/* SPI Initialization */
//static void spi_init (void)
//{
//    /* Init signal select pins with wired AND pull-up. */
//    PORTC.DIRSET = PIN4_bm;
//    PORTC.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;
//
//    /* Set SS output to high. (No slave addressed). */
//    PORTC.OUTSET = PIN4_bm;
//
//    /* Initialize SPI master on port C. */
//    SPI_MasterInit(     &spiMasterC,
//                        &SPIC,
//                        &PORTC,
//                        false,
//                        SPI_MODE_0_gc,
//                        SPI_INTLVL_LO_gc,
//                        false,
//                        SPI_PRESCALER_DIV4_gc);
//    /* Enable low and medium level interrupts in the interrupt controller. */
//    PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
//    sei();
//
//	/* Create data packet (SS to slave by PC4) */
//	SPI_MasterCreateDataPacket(&dataPacket,
//	                           sendData,
//	                           receivedData,
//	                           NUM_BYTES + 1,
//	                           &PORTC, //THESE SHOULD BE SET TO SS PINS
//	                           PIN4_bm);
//
//	/* Transmit and receive first data byte. */
//	uint8_t status;
//	do {
//		status = SPI_MasterInterruptTransceivePacket(&spiMasterC, &dataPacket);
//	} while (status != SPI_OK);
//
//	/* Wait for transmission to complete. */
//	while (dataPacket.complete == false) {
//
//	}
//
//	/* Check that correct data was received. Assume success at first. */
//	success = true;
//    uint8_t i;
//	for (i = 0; i < NUM_BYTES; i++) {
//		if (receivedData[i + 1] != (uint8_t)(sendData[i] + 1)) {
//			success = false;
//		}
//	}
//	while(true) {
//		nop();
//	}
//}

//ISR(SPIC_INT_vect)
//{
//	SPI_MasterInterruptHandler(&spiMasterC);
//}
//
//ISR(SPID_INT_vect)
//{
//	/* Get received data. */
//	uint8_t data = SPI_SlaveReadByte(&spiSlaveD);
//
//	/* Increment data. */
//	data++;
//
//	/* Send back incremented value. */
//	SPI_SlaveWriteByte(&spiSlaveD, data);
//}

void init_xbee_uart (int8_t bScale, uint16_t bSel) 
{
    PORTF.DIRCLR    =   PIN2_bm;
    PORTF.DIRSET    =   PIN3_bm;

    /* USARTE0, 8 Data bits, No Parity, 1 Stop bit. */
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

    /* USARTE0, 8 Data bits, No Parity, 1 Stop bit. */
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

    /* USARTE0, 8 Data bits, No Parity, 1 Stop bit. */
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

//xbee
ISR(USARTF0_RXC_vect) 
{
    unsigned char c = USARTF1.DATA;
}

//usb rx complete
ISR(USARTC1_RXC_vect) 
{
    unsigned char c = USARTC1.DATA;
    putchar_rs232(c);
    stdout = &usb_out;
    printf("Received: %c via usb.\n\r", c);
}

//rs232
ISR(USARTD1_RXC_vect) 
{
    unsigned char c = USARTD1.DATA;
    stdout = &usb_out;
    printf("Received: %c via rs232.\n\r", c);
}

void putchar_xbee (char c) 
{
    while ( !( USARTF0.STATUS & USART_DREIF_bm) ); // Wait for the transmit buffer to be empty
    USARTF0.DATA = c; // Put our character into the transmit buffer
}

void putchar_usb (char c) 
{
    while ( !( USARTC1.STATUS & USART_DREIF_bm) ); // Wait for the transmit buffer to be empty
    USARTC1.DATA = c; // Put our character into the transmit buffer
}

void putchar_rs232 (char c) 
{
    while ( !( USARTD1.STATUS & USART_DREIF_bm) ); // Wait for the transmit buffer to be empty
    USARTD1.DATA = c; // Put our character into the transmit buffer
}

void configClock (void) 
{
    // enable 32mhz oscillator 
    CLKSYS_Enable( OSC_RC32MEN_bm );
    do {} while ( CLKSYS_IsReady( OSC_RC32MRDY_bm ) == 0 );

    // configure pll source = 32mhz oscillator/4 * 16 = 4*32mhz = 128mhz output
    CLKSYS_PLL_Config( OSC_PLLSRC_RC32M_gc, 16 );

    // enable pll
    CLKSYS_Enable( OSC_PLLEN_bm );
    do {} while ( CLKSYS_IsReady( OSC_PLLEN_bm ) == 0 );

    // enable prescale by 2 and 2 again to generate 2x and 4x clocks
    CCP = CCP_IOREG_gc;
    CLK.PSCTRL = CLK_PSBCDIV_2_2_gc;

    // select main clock source as pll output
    CLKSYS_Main_ClockSource_Select( CLK_SCLKSEL_PLL_gc );
    
    // output clock on port d pin 7
    //~ PORTCFG.CLKEVOUT = PORTCFG_CLKOUT_PD7_gc; 
}

int main (void) 
{
    configClock();
    //set led pins as outputs
    PORTA.DIRSET=0b11110000;
    PORTF.DIRSET=0b11110000;

    PORTD.DIRSET=PIN5_bm; //rs232 enable pin
    PORTD.OUTCLR=PIN5_bm;

    init_xbee_uart(-4, 3317); //32MHz, 9600 baud
    init_usb_uart(-4, 3317); //32MHz, 9600 baud
    init_rs232_uart(-4, 3317); //32MHz, 9600 baud
    sei();
    while(1)
    {
        LED_1_RED_ON();
        _delay_ms(100);
        LED_1_RED_OFF();
        _delay_ms(100);
        LED_1_GREEN_ON();
        _delay_ms(100);
        LED_1_GREEN_OFF();
        _delay_ms(100);
        LED_2_RED_ON();
        _delay_ms(100);
        LED_2_RED_OFF();
        _delay_ms(100);
        LED_2_GREEN_ON();
        _delay_ms(100);
        LED_2_GREEN_OFF();
        _delay_ms(100);
        LED_3_RED_ON();
        _delay_ms(100);
        LED_3_RED_OFF();
        _delay_ms(100);
        LED_3_GREEN_ON();
        _delay_ms(100);
        LED_3_GREEN_OFF();
        _delay_ms(100);
        LED_4_RED_ON();
        _delay_ms(100);
        LED_4_RED_OFF();
        _delay_ms(100);
        LED_4_GREEN_ON();
        _delay_ms(100);
        LED_4_GREEN_OFF();
        _delay_ms(100);
        //putchar_xbee('x');
        //putchar_usb('x');
    }
    return 0;
}
