#include "fcu.h"
#include "wdt_driver.h"

volatile char usb_rx_buf[128];
volatile uint8_t usb_rx_count = 0;

volatile struct mot_tx_pkt_t mot_tx;
volatile struct mot_rx_pkt_t mot_rx;

volatile struct imu_tx_pkt_t imu_tx;
volatile struct imu_rx_pkt_t imu_rx;

void mot_tx_pkt_init(volatile struct mot_tx_pkt_t * mot_tx)
{
    mot_tx->start = MOT_START;
    mot_tx->tgt_1 = 0;
    mot_tx->tgt_2 = 0;
    mot_tx->tgt_3 = 0;
    mot_tx->tgt_4 = 0;
}

void mot_tx_rx(volatile struct mot_tx_pkt_t * mot_tx, volatile struct mot_rx_pkt_t * mot_rx)
{
    mot_tx->crc = crc((char *)&mot_tx, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
    SPI_MasterCreateDataPacket(     &mot_dataPacket,
                                    (uint8_t *)&mot_tx,
                                    (uint8_t *)&mot_rx,
                                    sizeof(mot_tx) + 1,
                                    &PORTB,
                                    SS0);
    /* Transmit and receive first data byte. */
    uint8_t status;
    do {
        status = SPI_MasterInterruptTransceivePacket(&spiMasterE, &mot_dataPacket);
    } while (status != SPI_OK);

    /* Wait for transmission to complete. */
    while (mot_dataPacket.complete == false) {
    }
}

void imu_tx_rx(volatile struct imu_tx_pkt_t * imu_tx, volatile struct imu_rx_pkt_t * imu_rx)
{
    imu_tx->crc = crc((char *)&imu_tx, 9, 7); //calculate the crc on the first 9 bytes of imu packet with divisor 7
    SPI_MasterCreateDataPacket(     &imu_dataPacket,
                                    (uint8_t *)&imu_tx,
                                    (uint8_t *)&imu_rx,
                                    sizeof(imu_tx) + 1,
                                    &PORTB,
                                    SS1);
    /* Transmit and receive first data byte. */
    uint8_t status;
    do {
        status = SPI_MasterInterruptTransceivePacket(&spiMasterE, &imu_dataPacket);
    } while (status != SPI_OK);

    /* Wait for transmission to complete. */
    while (imu_dataPacket.complete == false) {
    }
}

ISR(SPIC_INT_vect)
{
	SPI_MasterInterruptHandler(&spiMasterE);
}

/**********************************************/

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
    printf("%c", c);
    if(c == '\r')
    {
        usb_rx_buf[usb_rx_count] = '\0';
        if (strcmp(usb_rx_buf, "reboot") == 0)
        {
            printf("\n\rFCU is shutting down\n\r");
            CCPWrite(&RST_CTRL, RST_SWRST_bm);
        }
        else if(strcmp(usb_rx_buf, "clear") == 0)
        {
            printf("%c", 12);
        }
        else if(strcmp(usb_rx_buf, "help") == 0)
        {
            printf("Commands:\n\rreboot\n\rclear\n\rhelp\n\r");
        }
        else if(strlen(usb_rx_buf) > 0)
            printf("\n\rcommand not found: %s", usb_rx_buf);
        printf("\n\rroot@fcu: ");
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
    init_clk();
    //init_spi();

    //set led pins as outputs
    PORTA.DIRSET=0b11110000;
    PORTF.DIRSET=0b11110000;

    PORTD.DIRSET=PIN5_bm; //drive rs232 enable low
    PORTD.OUTCLR=PIN5_bm;

    init_xbee_uart  (10, 1047); //32MHz, 115200 baud
    init_usb_uart   (10, 1047); //32MHz, 115200 baud
    init_rs232_uart (10, 1047); //32MHz, 115200 baud
    init_sonar_uart (10, 1047); //32MHz, 115200 baud

    LED_4_GREEN_ON();
    LED_4_RED_OFF();
    
    LED_1_GREEN_ON();
    LED_2_GREEN_ON();
    LED_3_GREEN_ON();

    //mot_tx_pkt_init(&mot_tx);

    stdout = &usb_out;
    stdout = &rs232_out;
    stdout = &xbee_out;
    stdout = &sonar_out;

    sei();

    /************** Main Loop ***************/
    while(1)
    {
    }
    return 0;
}
