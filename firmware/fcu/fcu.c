#include "fcu.h"

volatile char usb_rx_buf[128];
volatile uint8_t usb_rx_count = 0;

volatile char xbee_rx_buf[128];
volatile uint8_t xbee_rx_count = 0;

volatile struct mot_tx_pkt_t mot_tx;
volatile struct mot_rx_pkt_t mot_rx;

volatile struct imu_tx_pkt_t imu_tx;
volatile struct imu_rx_pkt_t imu_rx;

volatile struct pid_info pid;

volatile uint8_t bat_voltage_raw;
volatile float bat_voltage_human;

void init_mot_tx_pkt(volatile struct mot_tx_pkt_t * pkt)
{
    pkt->start = MOT_TX_START;
    pkt->tgt_1 = 0;
    pkt->tgt_2 = 0;
    pkt->tgt_3 = 0;
    pkt->tgt_4 = 0;
    pkt->crc = crc((char *)pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
}

void init_mot_rx_pkt(volatile struct mot_rx_pkt_t * pkt)
{
    pkt->start = MOT_RX_START;
    pkt->spd_1 = 0;
    pkt->spd_2 = 0;
    pkt->spd_3 = 0;
    pkt->spd_4 = 0;
    pkt->crc = crc((char *)pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
}

void print_mot_tx_pkt(volatile struct mot_tx_pkt_t * pkt)
{
    pkt->crc = crc((char *)pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
    printf("\n\r");
    printf("mot_tx_pkt:\n\r");
    printf("\tstart:   %#02x\n\r", pkt->start);
    printf("\ttgt_1:  %6d\n\r", pkt->tgt_1);
    printf("\ttgt_2:  %6d\n\r", pkt->tgt_2);
    printf("\ttgt_3:  %6d\n\r", pkt->tgt_3);
    printf("\ttgt_4:  %6d\n\r", pkt->tgt_4);
    printf("\tcrc:    %6d", pkt->crc);
}

void print_mot_rx_pkt(volatile struct mot_rx_pkt_t * pkt)
{
    pkt->crc = crc((char *)pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
    printf("\n\r");
    printf("mot_rx_pkt:\n\r");
    printf("\tstart:   %#02x\n\r", pkt->start);
    printf("\tspd_1:  %6d\n\r", pkt->spd_1);
    printf("\tspd_2:  %6d\n\r", pkt->spd_2);
    printf("\tspd_3:  %6d\n\r", pkt->spd_3);
    printf("\tspd_4:  %6d\n\r", pkt->spd_4);
    printf("\tcrc:    %6d", pkt->crc);
}

void process_rx_buf(volatile char * rx_buf)
{
    char cmd[64];
    int16_t val = 0;
    cmd[0] = '\0';
    sscanf(rx_buf, "%s%d", cmd, &val);
    //printf("\n\rcommand: %s\n\rvalue: %d", cmd, val);
    if(cmd[0] == '\0') { } //do nothing
    else if(strcmp(cmd, "reboot") == 0) { printf("\n\rrebooting..."); CCPWrite(&RST_CTRL, RST_SWRST_bm); }
    else if(strcmp(cmd, "print") == 0) { print_mot_tx_pkt(&mot_tx); print_mot_rx_pkt(&mot_rx); }
    else if(strcmp(cmd, "print_mot_tx") == 0) { print_mot_tx_pkt(&mot_tx); }
    else if(strcmp(cmd, "print_mot_rx") == 0) { print_mot_rx_pkt(&mot_rx); }
    else if(strcmp(cmd, "mot1") == 0) { mot_tx.tgt_1 = (uint8_t)val; }
    else if(strcmp(cmd, "mot2") == 0) { mot_tx.tgt_2 = (uint8_t)val; }
    else if(strcmp(cmd, "mot3") == 0) { mot_tx.tgt_3 = (uint8_t)val; }
    else if(strcmp(cmd, "mot4") == 0) { mot_tx.tgt_4 = (uint8_t)val; }
    else if(strcmp(cmd, "motcrc") == 0) { mot_tx.crc = 47; }
    else if(strcmp(cmd, "led1g_on") == 0) { LED_1_GREEN_ON(); }
    else if(strcmp(cmd, "led2g_on") == 0) { LED_2_GREEN_ON(); }
    else if(strcmp(cmd, "led3g_on") == 0) { LED_3_GREEN_ON(); }
    else if(strcmp(cmd, "led4g_on") == 0) { LED_4_GREEN_ON(); }
    else if(strcmp(cmd, "led1r_on") == 0) { LED_1_RED_ON(); }
    else if(strcmp(cmd, "led2r_on") == 0) { LED_2_RED_ON(); }
    else if(strcmp(cmd, "led3r_on") == 0) { LED_3_RED_ON(); }
    else if(strcmp(cmd, "led4r_on") == 0) { LED_4_RED_ON(); }
    else if(strcmp(cmd, "led1g_off") == 0) { LED_1_GREEN_OFF(); }
    else if(strcmp(cmd, "led2g_off") == 0) { LED_2_GREEN_OFF(); }
    else if(strcmp(cmd, "led3g_off") == 0) { LED_3_GREEN_OFF(); }
    else if(strcmp(cmd, "led4g_off") == 0) { LED_4_GREEN_OFF(); }
    else if(strcmp(cmd, "led1r_off") == 0) { LED_1_RED_OFF(); }
    else if(strcmp(cmd, "led2r_off") == 0) { LED_2_RED_OFF(); }
    else if(strcmp(cmd, "led3r_off") == 0) { LED_3_RED_OFF(); }
    else if(strcmp(cmd, "led4r_off") == 0) { LED_4_RED_OFF(); }
    else if(strcmp(cmd, "bat") == 0) { printf("\n\rbat_voltage_raw: %d", bat_voltage_raw); printf("\n\rbat_voltage_human: %0.4f", (double)bat_voltage_human); }
    else if(strcmp(cmd, "help") == 0) { printf("\n\r\n\rAvailable commands:\n\r\treboot - reboot the mcu\n\r\tprint - print all packet information\n\r\tprint_mot - print motor packet\n\r\tmot[1-4] val - set motor target value (0-65536)\n\r\tled[1-4][r, g]_[on, off] - turn led on or off\n\r\tbat - print battery voltage\n\r\thelp - print this message\n\r"); }
    else if(strcmp(cmd, "clear") == 0) { printf("%c", 12); }
    else if(strcmp(cmd, "kp") == 0) { pid_set_kp(&pid, val); }
    else if(strcmp(cmd, "ki") == 0) { pid_set_ki(&pid, val); }
    else if(strcmp(cmd, "kd") == 0) { pid_set_kd(&pid, val); }
    else if(strcmp(cmd, "target") == 0) { pid_set_target(&pid, val); }
    else if(strcmp(cmd, "print_pid") == 0) { print_pid_info(&pid); }
    else if(strcmp(cmd, "reset_i") == 0) { pid_reset_i(&pid); }
    else { printf("\n\rcommand not found: %s", cmd); }
    printf("\n\rfcu: ");
}

/********* INTERRUPTS **********/

/***** spi *****/
ISR(SPIC_INT_vect)
{
    LED_3_RED_ON();
	SPI_MasterInterruptHandler(&spiMasterE);
}

/***** xbee *****/
ISR(USARTF0_TXC_vect)
{
}

ISR(USARTF0_RXC_vect) 
{
    unsigned char c = USARTF0.DATA;
    stdout = &xbee_out;
    printf("%c", c);
    if(c == '\r')
    {
        xbee_rx_buf[xbee_rx_count] = '\0';
        process_rx_buf(xbee_rx_buf);
        xbee_rx_count = 0;
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
    printf("%c", c);
    if(c == '\r')
    {
        usb_rx_buf[usb_rx_count] = '\0';
        process_rx_buf(usb_rx_buf);
        usb_rx_count = 0;
    }
    else if(c == '\b')
    {
        //printf("got a backspace!\n\r");
        printf(" \b");
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

    init_mot_tx_pkt(&mot_tx);
    init_mot_rx_pkt(&mot_rx);

    stdout = &usb_out;
    printf("%c", 12);
    stdout = &rs232_out;
    stdout = &xbee_out;
    stdout = &sonar_out;

    sei();

    /************** Main Loop ***************/
    while(1)
    {
        //mot_tx_rx(&mot_tx, &mot_rx);
        cli();
        stdout = &rs232_out;
        printf("rs232\n\r");
        sei();
        ADC_Ch_Conversion_Start (&ADCA.CH0);

        //mot_tx.crc = crc((char *)&mot_tx, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
        //spi_write_multi(tx, sizeof(tx), SS0);
        //imu_tx.crc = crc((char *)&imu_tx, 9, 7); //calculate the crc on the first 9 bytes of imu packet with divisor 7
        //spi_write_multi(imu_tx, sizeof(imu_tx), SS1);
    }
    return 0;
}
