#include "fcu.h"

static FILE xbee_out = FDEV_SETUP_STREAM (putchar_xbee, NULL, _FDEV_SETUP_WRITE);
static FILE usb_out = FDEV_SETUP_STREAM (putchar_usb, NULL, _FDEV_SETUP_WRITE);
static FILE rs232_out = FDEV_SETUP_STREAM (putchar_rs232, NULL, _FDEV_SETUP_WRITE);
static FILE sonar_out = FDEV_SETUP_STREAM (putchar_sonar, NULL, _FDEV_SETUP_WRITE);

volatile char usb_rx_buf[128];
volatile uint8_t usb_rx_count = 0;

/************************* SPI Initialization ************************/

/*** APP NOTE CODE ***/
/*! \brief Number of test data bytes. */
#define NUM_BYTES   2

/* Global variables. */

/*! \brief SPI master on PORT E. */
SPI_Master_t spiMasterE;

/*! \brief Data packet. */
SPI_DataPacket_t dataPacket;

/*! \brief Test data to send. */
const uint8_t sendData[NUM_BYTES + 1] = { 0x55, 0xaa, 0x00 };

/*! \brief Buffer for test data reception. */
uint8_t receivedData[NUM_BYTES + 1];

/*! \brief Result of the example test. */
bool success;

/*** END APP NOTE CODE ***/

static void spi_init (void)
{
    /* Init signal select pins with wired AND pull-up. */
    PORTB.DIRSET = 0b11111111;

    //IGNORING THIS FOR NOW
    //PORTC.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;

    /* Set SS output to high. (No slave addressed). */
    PORTB.OUTSET = 0b11111111;

    /* Initialize SPI master on port E. */
    SPI_MasterInit(     &spiMasterE,
                        &SPIC,
                        &PORTE,
                        false,
                        SPI_MODE_0_gc,
                        SPI_INTLVL_LO_gc,
                        false,
                        SPI_PRESCALER_DIV4_gc);
    /* Enable low and medium level interrupts in the interrupt controller. */
    PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
    sei();

	/* Create data packet (SS to slave by PC4) */
	SPI_MasterCreateDataPacket(&dataPacket,
	                           sendData,
	                           receivedData,
	                           NUM_BYTES + 1,
	                           &PORTC, //THESE SHOULD BE SET TO SS PINS
	                           PIN4_bm);

	/* Transmit and receive first data byte. */
	uint8_t status;
	do {
		status = SPI_MasterInterruptTransceivePacket(&spiMasterE, &dataPacket);
	} while (status != SPI_OK);

	/* Wait for transmission to complete. */
	while (dataPacket.complete == false) {

	}

	/* Check that correct data was received. Assume success at first. */
	success = true;
    uint8_t i;
	for (i = 0; i < NUM_BYTES; i++) {
		if (receivedData[i + 1] != (uint8_t)(sendData[i] + 1)) {
			success = false;
		}
	}
	while(true) {
		nop();
	}
}

ISR(SPIC_INT_vect)
{
	SPI_MasterInterruptHandler(&spiMasterE);
}

/**********************************************/

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

/********* INTERRUPTS **********/

/***** xbee *****/
ISR(USARTF0_TXC_vect)
{
}

ISR(USARTF0_RXC_vect) 
{
    unsigned char c = USARTF0.DATA;
    stdout = &usb_out;
    printf("Received: %c via xbee.\n\r", c);
}

/***** usb *****/
ISR(USARTC1_TXC_vect) 
{
}

ISR(USARTC1_RXC_vect) 
{
    unsigned char c = USARTC1.DATA;
    putchar_rs232(c);
    stdout = &usb_out;
    //printf("Received: %c via usb.\n\r", c);
    if(c == '\r')
    {
        usb_rx_buf[usb_rx_count] = '\0';
        printf("usb_rx_buf = %s\n\r", usb_rx_buf);
        usb_rx_count = 0;
    }
    else 
    { 
        usb_rx_buf[usb_rx_count] = c; 
        usb_rx_count++;
    }
}

/***** rs232 *****/
ISR(USARTD1_TXC_vect)
{
}

ISR(USARTD1_RXC_vect) 
{
    unsigned char c = USARTD1.DATA;
    stdout = &usb_out;
    printf("Received: %c via rs232.\n\r", c);
}

/***** sonar *****/
ISR(USARTE0_TXC_vect)
{
}

ISR(USARTE0_RXC_vect)
{
    unsigned char c = USARTE0.DATA;
    stdout = &usb_out;
    printf("Received: %c via sonar.\n\r", c);
}



int main (void) 
{
    configClock();

    //set led pins as outputs
    PORTA.DIRSET=0b11110000;
    PORTF.DIRSET=0b11110000;

    PORTD.DIRSET=PIN5_bm; //drive rs232 enable low
    PORTD.OUTCLR=PIN5_bm;

    init_xbee_uart  (-4, 3317); //32MHz, 9600 baud
    init_usb_uart   (-4, 3317); //32MHz, 9600 baud
    init_rs232_uart (-4, 3317); //32MHz, 9600 baud
    init_sonar_uart (-4, 3317); //32MHz, 9600 baud

    LED_4_GREEN_ON();

    sei();

    /************** Main Loop ***************/
    while(1)
    {
        /*
        LED_1_RED_ON();
        LED_3_GREEN_ON();
        _delay_ms(25);
        LED_1_RED_OFF();
        LED_3_GREEN_OFF();
        _delay_ms(25);
        LED_2_RED_ON();
        LED_4_GREEN_ON();
        _delay_ms(25);
        LED_2_RED_OFF();
        LED_4_GREEN_OFF();
        _delay_ms(25);
        LED_3_RED_ON();
        LED_1_GREEN_ON();
        _delay_ms(25);
        LED_3_RED_OFF();
        LED_1_GREEN_OFF();
        _delay_ms(25);
        LED_4_RED_ON();
        LED_2_GREEN_ON();
        _delay_ms(25);
        LED_4_RED_OFF();
        LED_2_GREEN_OFF();
        _delay_ms(25);
        */
    }
    return 0;
}
