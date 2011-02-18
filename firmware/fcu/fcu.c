#include "fcu.h"

void init_mot_tx_pkt(volatile struct mot_tx_pkt_t * pkt)
{
    pkt->start = MOT_START;
    pkt->tgt_1 = 0;
    pkt->tgt_2 = 0;
    pkt->tgt_3 = 0;
    pkt->tgt_4 = 0;
    pkt->crc = crc((char *)pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
}

void init_mot_rx_pkt(volatile struct mot_rx_pkt_t * pkt)
{
    pkt->start = 0;
    pkt->spd_1 = 0;
    pkt->spd_2 = 0;
    pkt->spd_3 = 0;
    pkt->spd_4 = 0;
    pkt->crc = 0;
}

void init_imu_tx_pkt(volatile struct imu_tx_pkt_t * pkt)
{
    pkt->start = IMU_START;
}

void init_imu_rx_pkt(volatile struct imu_rx_pkt_t * pkt)
{
    pkt->start = 2;
    pkt->chksum = 2;
    pkt->pitch_tmp = 2;
    pkt->pitch = 2;
    pkt->yaw = 2;
    pkt->yaw_tmp = 2;
    pkt->z_accel = 2;
    pkt->y_accel = 2;
    pkt->x_accel = 2;
    pkt->roll = 2;
}

void request_imu_pkt()
{ 
    int i;
    spi_write((char)IMU_START>>8, SS1); 
    spi_write((char)IMU_START>>0, SS1); 
    _delay_us(10);
    cli();
    while(spi_read(SS1) != IMU_START)
    {
    }
    char * ptr = (char *)&imu_rx;
    for(i = 1; i < sizeof(struct imu_rx_pkt_t); i++)
    {
        ptr[i] = spi_read(SS1);
    }
    sei();
}

/********* INTERRUPTS **********/

/***** spi *****/
/*
ISR(SPIC_INT_vect)
{
    LED_3_RED_ON();
	SPI_MasterInterruptHandler(&spiMasterE);
}
*/

/***** xbee *****/
ISR(USARTF0_TXC_vect)
{
}

ISR(USARTF0_RXC_vect) 
{
    unsigned char c = USARTF0.DATA;
    stdout = &xbee_out;
    if(c == '\r')
    {
        xbee_rx_buf[xbee_rx_count] = '\0';
        xbee_rx_buf_rdy = 1;
    }
    else if(c == '\b')
    {
        xbee_rx_count--;
        xbee_rx_buf[xbee_rx_count] = '\0';
    }
    else
    {
        xbee_rx_buf[xbee_rx_count] = c; 
        xbee_rx_count++;
    }
}

/***** usb *****/
ISR(USARTC1_TXC_vect) 
{
}

ISR(USARTC1_RXC_vect) 
{
    unsigned char c = USARTC1.DATA;
    stdout = &usb_out;
    if(c == '\r')
    {
        usb_rx_buf[usb_rx_count] = '\0';
        usb_rx_buf_rdy = 1;
    }
    else if(c == '\b')
    {
        usb_rx_count--;
        usb_rx_buf[usb_rx_count] = '\0';
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

/***** adc *****/
// interrupt should be called after each ADC conversion is complete
ISR(ADCA_CH0_vect)
{
    bat_voltage_raw = ADCA.CH0.RES;
    bat_voltage_human = (float)bat_voltage_raw / 16;
}

int main (void) 
{
    LED_1_GREEN_OFF();
    LED_2_GREEN_OFF();
    LED_3_GREEN_OFF();
    LED_4_GREEN_OFF();

    init_clk();
    init_spi();
    init_adc(&ADCA);

    //set led pins as outputs
    PORTA.DIRSET=0b11110000;
    PORTF.DIRSET=0b11110000;

    PORTD.DIRSET=PIN5_bm; //drive rs232 enable low
    PORTD.OUTCLR=PIN5_bm;

    init_xbee_uart  (-5, 3301); //32MHz, 19200 baud
    init_usb_uart   (10, 1047); //32MHz, 115200 baud
    init_rs232_uart (10, 1047); //32MHz, 115200 baud
    init_sonar_uart (10, 1047); //32MHz, 115200 baud

    LED_4_GREEN_ON();
    LED_4_RED_OFF();

    stdout = &usb_out;

    init_mot_tx_pkt(&mot_tx);
    init_mot_rx_pkt(&mot_rx);

    init_imu_tx_pkt(&imu_tx);
    init_imu_rx_pkt(&imu_rx);

    stdout = &usb_out;
    printf("%c", 12);
    stdout = &rs232_out;
    stdout = &xbee_out;
    stdout = &sonar_out;

    uint8_t loop_count = 0;

    sei();

    /************** Main Loop ***************/
    while(1)
    {
        ADC_Ch_Conversion_Start (&ADCA.CH0);

        if(usb_rx_buf_rdy)
        {
            stdout = &usb_out;
            process_rx_buf(usb_rx_buf);
            usb_rx_buf[0] = '\0';
            while(usb_rx_count > 0)
            {
                usb_rx_buf[usb_rx_count] = '\0';
                usb_rx_count--;
            }
            printf("\n\r");
            usb_rx_buf_rdy = 0;
        }
        if(xbee_rx_buf_rdy)
        {
            stdout = &xbee_out;
            process_rx_buf(xbee_rx_buf);
            xbee_rx_buf[0] = '\0';
            while(xbee_rx_count > 0)
            {
                xbee_rx_buf[xbee_rx_count] = '\0';
                xbee_rx_count--;
            }
            xbee_rx_buf_rdy = 0;
        }
        stdout = &usb_out;
        if(loop_count == 25)
        {
            if(print_status_flag)
            {
                request_imu_pkt();
                print_status();
            }
            loop_count = 0;
        }
        printf("\r");
        printf("fcu: %s", usb_rx_buf);

        _delay_ms(50);
        loop_count++;
    }
    return 0;
}
