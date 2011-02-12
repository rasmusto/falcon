#include "fcu.h"

volatile char usb_rx_buf[128];
volatile uint8_t usb_rx_count = 0;
volatile uint8_t usb_rx_buf_rdy = 0;

volatile char xbee_rx_buf[128];
volatile uint8_t xbee_rx_count = 0;
volatile uint8_t xbee_rx_buf_rdy = 0;

volatile struct mot_tx_pkt_t mot_tx;
volatile struct mot_rx_pkt_t mot_rx;

volatile struct imu_tx_pkt_t imu_tx;
volatile struct imu_rx_pkt_t imu_rx;

volatile struct pid_info pid;

volatile uint8_t bat_voltage_raw;
volatile float bat_voltage_human;

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
    int i;
    pkt->start = IMU_START;
    for(i = 0; i < 16; i++)
        pkt->garbage[i] = i;
    pkt->crc = crc((char *)pkt, 17, 7);
}

void init_imu_rx_pkt(volatile struct imu_rx_pkt_t * pkt)
{
    pkt->start = 0;
    pkt->pitch_tmp = 0;
    pkt->pitch = 0;
    pkt->yaw = 0;
    pkt->yaw_tmp = 0;
    pkt->z_accel = 0;
    pkt->y_accel = 0;
    pkt->x_accel = 0;
    pkt->roll = 0;
    pkt->crc = 0;
}

void print_mot_pkts(volatile struct mot_tx_pkt_t * tx_pkt, volatile struct mot_rx_pkt_t * rx_pkt)
{   
    printf("\n\r");
    tx_pkt->crc = crc((char *)tx_pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
    printf("\n\r");
    printf("mot_tx_pkt:\t\tmot_rx_pkt\n\r");
    printf("\tstart:   %#02x\t\tstart:   %#02x\n\r", tx_pkt->start, rx_pkt->start);
    printf("\ttgt_1: %6lu\t\tspd_1: %6lu\n\r", (uint32_t)tx_pkt->tgt_1, (uint32_t)rx_pkt->spd_1);
    printf("\ttgt_1: %6lu\t\tspd_2: %6lu\n\r", (uint32_t)tx_pkt->tgt_2, (uint32_t)rx_pkt->spd_2);
    printf("\ttgt_1: %6lu\t\tspd_3: %6lu\n\r", (uint32_t)tx_pkt->tgt_3, (uint32_t)rx_pkt->spd_3);
    printf("\ttgt_1: %6lu\t\tspd_4: %6lu\n\r", (uint32_t)tx_pkt->tgt_4, (uint32_t)rx_pkt->spd_4);
    printf("\tcrc:   %6d\t\tcrc:   %6d\n\r", tx_pkt->crc, rx_pkt->crc);
}

void print_imu_pkts(volatile struct imu_tx_pkt_t * tx_pkt, volatile struct imu_rx_pkt_t * rx_pkt)
{
    printf("\n\r\n\r");
    printf("imu_tx_pkt:\t\t\timu_rx_pkt:\n\r");
    printf("\tstart:         %#02x\t\tstart:   %#02x\n\r", tx_pkt->start,                 rx_pkt->start);
    printf("\tgarbage[0]:  %6d\t\tpitch_tmp: %6d\n\r",     (int16_t)tx_pkt->garbage[0],   rx_pkt->pitch_tmp);
    printf("\tgarbage[2]:  %6d\t\tpitch:     %6d\n\r",     (int16_t)tx_pkt->garbage[2],   rx_pkt->pitch);
    printf("\tgarbage[4]:  %6d\t\tyaw:       %6d\n\r",     (int16_t)tx_pkt->garbage[4],   rx_pkt->yaw);
    printf("\tgarbage[6]:  %6d\t\tyaw_tmp:   %6d\n\r",     (int16_t)tx_pkt->garbage[6],   rx_pkt->yaw_tmp);
    printf("\tgarbage[8]:  %6d\t\tz_accel:   %6d\n\r",     (int16_t)tx_pkt->garbage[8],   rx_pkt->z_accel);
    printf("\tgarbage[10]: %6d\t\ty_accel:   %6d\n\r",     (int16_t)tx_pkt->garbage[10],  rx_pkt->y_accel);
    printf("\tgarbage[12]: %6d\t\tx_accel:   %6d\n\r",     (int16_t)tx_pkt->garbage[12],  rx_pkt->x_accel);
    printf("\tgarbage[14]: %6d\t\troll:      %6d\n\r",     (int16_t)tx_pkt->garbage[14],  rx_pkt->roll);
    printf("\tcrc:         %6d\t\tcrc:       %6d\n\r",     tx_pkt->crc,                   rx_pkt->crc);
}

void process_rx_buf(volatile char * rx_buf)
{
    char cmd[64];
    float val = 0;
    cmd[0] = '\0';
    sscanf(rx_buf, "%s%f", cmd, &val);
    //printf("\n\rcommand: %s\n\rvalue: %d", cmd, val);
    char * help;
    help = "\n\r\n\rAvailable commands:\n\r\
            \r\treboot - reboot the mcu\n\r\
            \r\tprint - display the print commands\n\r\
            \r\tprintpid - print pid structs\n\r\
            \r\tprintmot - print motor packets\n\r\
            \r\tprintimu - print imu packets\n\r\
            \r\tprintbat - print battery voltage\n\r\
            \r\tmot[1-4] <uint16_t> - set motor target value (0-65536)\n\r\
            \r\tled[1-4][r, g]_[on, off] - turn led on or off\n\r\
            \r\tclear - clear the screen\n\r\
            \r\tkp <float> - set kp\n\r\
            \r\tki <float> - set ki\n\r\
            \r\tkd <float> - set kd\n\r\
            \r\thelp - print this message\n\r";
    if(cmd[0] == '\0') { } //do nothing
    else if(strcmp(cmd, "reboot") == 0) { printf("\n\rrebooting..."); CCPWrite(&RST_CTRL, RST_SWRST_bm); }
    else if(strcmp(cmd, "print") == 0) { printf("\n\r\n\rAvailable print commands:\n\r\tprintpid\n\r\tprintmot\n\r\tprintimu\n\r\tprintbat\n\r"); }
    else if(strcmp(cmd, "printpid") == 0) { print_pid_info(&pid); }
    else if(strcmp(cmd, "printmot") == 0) { print_mot_pkts(&mot_tx, &mot_rx); }
    else if(strcmp(cmd, "printimu") == 0) { print_imu_pkts(&imu_tx, &imu_rx); }
    else if(strcmp(cmd, "printbat") == 0) { printf("\n\rbat_voltage_raw: %d", bat_voltage_raw); printf("\n\rbat_voltage_human: %0.4f", (double)bat_voltage_human); }
    else if(strcmp(cmd, "start") == 0) { mot_tx.start = (uint8_t)val; }
    else if(strcmp(cmd, "mot1") == 0) { mot_tx.tgt_1 = (uint16_t)val; }
    else if(strcmp(cmd, "mot2") == 0) { mot_tx.tgt_2 = (uint16_t)val; }
    else if(strcmp(cmd, "mot3") == 0) { mot_tx.tgt_3 = (uint16_t)val; }
    else if(strcmp(cmd, "mot4") == 0) { mot_tx.tgt_4 = (uint16_t)val; }
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
    else if(strcmp(cmd, "help") == 0) { printf(help); }
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
    printf("%c", c);
    if(c == '\r')
    {
        xbee_rx_buf[xbee_rx_count] = '\0';
        xbee_rx_buf_rdy = 1;
        xbee_rx_count = 0;
    }
    else if(c == '\b')
    {
        printf(" \b");
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
    printf("%c", c);
    if(c == '\r')
    {
        usb_rx_buf[usb_rx_count] = '\0';
        //process_rx_buf(usb_rx_buf);
        usb_rx_buf_rdy = 1;
        usb_rx_count = 0;
    }
    else if(c == '\b')
    {
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

    init_imu_tx_pkt(&imu_tx);
    init_imu_rx_pkt(&imu_rx);

    stdout = &usb_out;
    printf("%c", 12);
    stdout = &rs232_out;
    stdout = &xbee_out;
    stdout = &sonar_out;

    sei();

    /************** Main Loop ***************/
    while(1)
    {
        ADC_Ch_Conversion_Start (&ADCA.CH0);
        spi_write_read_multi((char *)&mot_tx, (char *)&mot_rx, 10, SS0);
        spi_write_read_multi((char *)&imu_tx, (char *)&imu_rx, 10, SS1);
        if(usb_rx_buf_rdy)
        {
            stdout = &usb_out;
            process_rx_buf(usb_rx_buf);
            usb_rx_buf_rdy = 0;
        }
        if(xbee_rx_buf_rdy)
        {
            stdout = &xbee_out;
            process_rx_buf(xbee_rx_buf);
            xbee_rx_buf_rdy = 0;
        }
    }
    return 0;
}
