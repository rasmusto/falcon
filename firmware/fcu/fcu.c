#include "fcu.h"

volatile char usb_rx_buf[128];
volatile uint8_t usb_rx_count = 0;
volatile uint8_t usb_rx_buf_rdy = 0;

volatile char xbee_rx_buf[128];
volatile uint8_t xbee_rx_count = 0;
volatile uint8_t xbee_rx_buf_rdy = 0;

volatile struct mcu_tx_pkt_t mcu_tx;
volatile struct mcu_rx_pkt_t mcu_rx;

volatile struct imu_tx_pkt_t imu_tx;
volatile struct imu_rx_pkt_t imu_rx;

volatile struct pid_info roll_pid;
volatile struct pid_info pitch_pid;
volatile struct pid_info yaw_pid;

volatile float roll;
volatile float pitch;
volatile float yaw;

volatile uint8_t print_status_flag = 1;

volatile uint8_t bat_voltage_raw;
volatile float bat_voltage_human;

volatile int imu_rx_index = 0;
uint16_t real_imu_parity;

volatile int mcu_tx_index = 0;
volatile int mcu_rx_index = 0;

volatile uint8_t slave;
volatile uint8_t request_imu_pkt_flag = 0;
volatile uint8_t receive_imu_pkt_flag = 0;

volatile uint8_t send_mcu_pkt_flag = 0;
volatile uint8_t receive_mcu_pkt_flag = 0;
volatile uint8_t mcu_rx_first_packet_flag = 0;

volatile uint8_t first_spi_interrupt_flag = 0;
volatile uint8_t stream_data_flag = 0;
volatile uint8_t request_new_pkt_flag = 0;

volatile float roll_pid_output = 0;
volatile float pitch_pid_output = 0;
volatile float yaw_pid_output = 0;

void init_mcu_tx_pkt(volatile struct mcu_tx_pkt_t * pkt)
{
    pkt->start = MCU_START;
    //~ pkt->tgt_1 = 0xF1F2;
    //~ pkt->tgt_2 = 0xF3F4;
    //~ pkt->tgt_3 = 0xF5F6;
    //~ pkt->tgt_4 = 0xF7F8;
    pkt->tgt_1 = 1000;
    pkt->tgt_2 = 1000;
    pkt->tgt_3 = 1000;
    pkt->tgt_4 = 1000;
    pkt->crc = crc((char *)pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
}

void init_mcu_rx_pkt(volatile struct mcu_rx_pkt_t * pkt)
{
    pkt->spd_1 = 0;
    pkt->spd_2 = 0;
    pkt->spd_3 = 0;
    pkt->spd_4 = 0;
}

void init_imu_tx_pkt(volatile struct imu_tx_pkt_t * pkt)
{
    pkt->start = IMU_TX_START;
}

void init_imu_rx_pkt(volatile struct imu_rx_pkt_t * pkt)
{
    pkt->start      =   0xAD;
    pkt->parity     =   0xAD;
    pkt->pitch_tmp  =   0xBAD;
    pkt->pitch      =   0xBAD;
    pkt->yaw        =   0xBAD;
    pkt->yaw_tmp    =   0xBAD;
    pkt->z_accel    =   0xBAD;
    pkt->y_accel    =   0xBAD;
    pkt->x_accel    =   0xBAD;
    pkt->roll       =   0xBAD;
}

void request_imu_pkt()
{ 
    receive_imu_pkt_flag = 1;
    slave = IMU_SPI;

    cli();
    SPIE.INTCTRL = SPI_INTLVL_OFF_gc;
    PORTB.OUTCLR = 1<<SS1;

    //write first byte of request
    SPIE.DATA = IMU_TX_START_H;
    while(!(SPIE.STATUS & (1<<7)));

    //write second byte of request
    SPIE.DATA = IMU_TX_START_L;
    while(!(SPIE.STATUS & (1<<7)));

    SPIE.INTCTRL = SPI_INTLVL_LO_gc;
    first_spi_interrupt_flag = 1;
    imu_rx_index = 0;
    sei();

    SPIE.DATA = 0;
}

void send_mcu_pkt()
{
    slave = MCU_SPI;

    cli();
    SPIE.INTCTRL = SPI_INTLVL_OFF_gc;
    PORTB.OUTCLR = 1<<SS0;

    //write first byte of packet
    SPIE.INTCTRL = SPI_INTLVL_LO_gc;
    SPIE.DATA = MCU_START;
    mcu_tx_index = 1;
    mcu_rx_index = 0;
    send_mcu_pkt_flag = 1;
    sei();
}

void print_mcu_pkts(volatile struct mcu_tx_pkt_t * tx_pkt, volatile struct mcu_rx_pkt_t * rx_pkt)
{   
    //printf("\n\r");
    //tx_pkt->crc = crc((char *)tx_pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
    printf("\n\r");
    printf("mcu_tx_pkt:\t\tmcu_rx_pkt:\n\r");
    printf("\ttgt_1: %6lu\t\tspd_1: %6lu\n\r", (uint32_t)tx_pkt->tgt_1, (uint32_t)rx_pkt->spd_1);
    printf("\ttgt_2: %6lu\t\tspd_2: %6lu\n\r", (uint32_t)tx_pkt->tgt_2, (uint32_t)rx_pkt->spd_2);
    printf("\ttgt_3: %6lu\t\tspd_3: %6lu\n\r", (uint32_t)tx_pkt->tgt_3, (uint32_t)rx_pkt->spd_3);
    printf("\ttgt_4: %6lu\t\tspd_4: %6lu\n\r", (uint32_t)tx_pkt->tgt_4, (uint32_t)rx_pkt->spd_4);
    /*
    printf("%X\n\r", rx_pkt->spd_1);
    printf("%X\n\r", rx_pkt->spd_2);
    printf("%X\n\r", rx_pkt->spd_3);
    printf("%X\n\r", rx_pkt->spd_4);
    */
    printf("%04X %04X %04X %04X %02X\n\r", tx_pkt->tgt_1, tx_pkt->tgt_2, tx_pkt->tgt_3, tx_pkt->tgt_4, tx_pkt->crc);
    printf("%04X %04X %04X %04X %02X\n\r", rx_pkt->spd_1, rx_pkt->spd_2, rx_pkt->spd_3, rx_pkt->spd_4, rx_pkt->crc);
}

void print_imu_pkts(volatile struct imu_tx_pkt_t * tx_pkt, volatile struct imu_rx_pkt_t * rx_pkt)
{
    printf("\n\r\n\r");
    printf("imu_tx_pkt:\t\timu_rx_pkt:\n\r");
    printf("\tstart:   %#02x\t        start:     %#02x\n\r",     tx_pkt->start,      rx_pkt->start);
    printf("\t                        parity:    %#02x\n\r",     rx_pkt->parity);
    printf("\t               real_imu_parity:    %#02x\n\r",     real_imu_parity);
    printf("\t                        roll:      %6d\n\r",     rx_pkt->roll);
    printf("\t                        pitch:     %6d\n\r",     rx_pkt->pitch);
    printf("\t                        yaw:       %6d\n\r",     rx_pkt->yaw);
    printf("\t                        x_accel:   %6d\n\r",     rx_pkt->x_accel);
    printf("\t                        y_accel:   %6d\n\r",     rx_pkt->y_accel);
    printf("\t                        z_accel:   %6d\n\r",     rx_pkt->z_accel);
    printf("\t                        pitch_tmp: %6d\n\r",     rx_pkt->pitch_tmp);
    printf("\t                        yaw_tmp:   %6d\n\r",     rx_pkt->yaw_tmp);

    printf("\n\r%02X %02X %04X %04X %04X %04X %04X %04X %04X %04X\n\r", rx_pkt->start, rx_pkt->parity, rx_pkt->pitch_tmp, rx_pkt->pitch, rx_pkt->yaw, rx_pkt->yaw_tmp, rx_pkt->z_accel, rx_pkt->y_accel, rx_pkt->x_accel, rx_pkt->roll);
}


void print_bat(void)
{
    printf("\n\rbattery: %0.4fV\n\r", (double)bat_voltage_human);
}

void print_status(void)
{
    if(stream_data_flag == 0)
    {
        FILE * tmp = stdout;
        stdout = &usb_out;
        printf("%c", 12);

        /*
        print_pid_info(&roll_pid);
        printf("roll_pid_output = %f\n\r", roll_pid_output);
        print_pid_info(&pitch_pid);
        printf("pitch_pid_output = %f\n\r", pitch_pid_output);
        print_pid_info(&yaw_pid);
        printf("yaw_pid_output = %f\n\r", yaw_pid_output);
        */

        print_mcu_pkts(&mcu_tx, &mcu_rx);
        print_imu_pkts(&imu_tx, &imu_rx);

        printf("roll = %f\n\r", roll);
        printf("pitch = %f\n\r", pitch);
        printf("yaw = %f\n\r", yaw);

        print_bat();
        stdout = tmp;
    }
}
 
void process_rx_buf(volatile char * rx_buf)
{
    char cmd[64];
    float val = 0;
    cmd[0] = '\0';
    sscanf(rx_buf, "%s%f", cmd, &val);
    char * help;
    help = "\n\r\n\rAvailable commands:\n\r\
            \r\treboot - reboot the mcu\n\r\
            \r\tprint - display the print commands\n\r\
            \r\tprintpid - print pid structs\n\r\
            \r\tprintmcu - print motor packets\n\r\
            \r\tprintimu - print imu packets\n\r\
            \r\tprintbat - print battery voltage\n\r\
            \r\tmcu[1-4] <uint16_t> - set motor target value (0-65536)\n\r\
            \r\tled[1-4][r, g]_[on, off] - turn led on or off\n\r\
            \r\tclear - clear the screen\n\r\
            \r\tkp <float> - set kp\n\r\
            \r\tki <float> - set ki\n\r\
            \r\tkd <float> - set kd\n\r\
            \r\thelp - print this message\n\r";
    if(cmd[0] == '\0') { } //do nothing
    else if(strcmp(cmd, "reboot") == 0) { printf("\n\rrebooting..."); CCPWrite(&RST_CTRL, RST_SWRST_bm); }
    else if(strcmp(cmd, "print_status") == 0) { if(print_status_flag == 0)print_status_flag = 1; else print_status_flag = 0; }
    else if(strcmp(cmd, "start") == 0) { mcu_tx.start = (uint8_t)val; }
    else if(strcmp(cmd, "mot1") == 0) { mcu_tx.tgt_1 = (uint16_t)val; }
    else if(strcmp(cmd, "mot2") == 0) { mcu_tx.tgt_2 = (uint16_t)val; }
    else if(strcmp(cmd, "mot3") == 0) { mcu_tx.tgt_3 = (uint16_t)val; }
    else if(strcmp(cmd, "mot4") == 0) { mcu_tx.tgt_4 = (uint16_t)val; }
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
    else if(strcmp(cmd, "rkp") == 0) {      pid_set_kp(     &roll_pid,  val); }
    else if(strcmp(cmd, "rki") == 0) {      pid_set_ki(     &roll_pid,  val); }
    else if(strcmp(cmd, "rkd") == 0) {      pid_set_kd(     &roll_pid,  val); }
    else if(strcmp(cmd, "rtarget") == 0) {  pid_set_target( &roll_pid,  val); }
    else if(strcmp(cmd, "rreset_i") == 0) { pid_reset_i(    &roll_pid); }
    else if(strcmp(cmd, "pkp") == 0) {      pid_set_kp(     &pitch_pid, val); }
    else if(strcmp(cmd, "pki") == 0) {      pid_set_ki(     &pitch_pid, val); }
    else if(strcmp(cmd, "pkd") == 0) {      pid_set_kd(     &pitch_pid, val); }
    else if(strcmp(cmd, "ptarget") == 0) {  pid_set_target( &pitch_pid, val); }
    else if(strcmp(cmd, "preset_i") == 0) { pid_reset_i(    &pitch_pid); }
    else if(strcmp(cmd, "ykp") == 0) {      pid_set_kp(     &yaw_pid,   val); }
    else if(strcmp(cmd, "yki") == 0) {      pid_set_ki(     &yaw_pid,   val); }
    else if(strcmp(cmd, "ykd") == 0) {      pid_set_kd(     &yaw_pid,   val); }
    else if(strcmp(cmd, "ytarget") == 0) {  pid_set_target( &yaw_pid,   val); }
    else if(strcmp(cmd, "yreset_i") == 0) { pid_reset_i(    &yaw_pid); }
    //else if(strcmp(cmd, "print_pid") == 0) { print_pid_info(&pid); }
    else if(strcmp(cmd, "request_imu") == 0) { request_imu_pkt(); }
    else if(strcmp(cmd, "init_imu_rx") == 0) { init_imu_rx_pkt(&imu_rx); }
    else if(strcmp(cmd, "stream") == 0) { stream_data_flag ^= 1; }
    else { printf("\n\rcommand not found: %s", cmd); }
}

/********* INTERRUPTS **********/

/***** spi *****/
ISR(SPIE_INT_vect)
{
    stdout = &usb_out;
    if(first_spi_interrupt_flag)
    {
        first_spi_interrupt_flag = 0;
        return;
    }
    /*** Handle IMU Transfer ***/
    if(slave == IMU_SPI)
    {
        if(receive_imu_pkt_flag == 1)
        {
            char * ptr = (char *)&imu_rx;
            ptr[imu_rx_index] = SPIE.DATA;
            imu_rx_index++;
            if(imu_rx_index > sizeof(struct imu_rx_pkt_t))
            {
                receive_imu_pkt_flag = 0;
                PORTB.OUTSET = 1<<SS1;

                real_imu_parity = parity_byte(&imu_rx, sizeof(struct imu_rx_pkt_t)/2 -1);
                
                //reverse order of bytes
                int i;
                char tmp;
                for(i = 2; i < sizeof(struct imu_rx_pkt_t); i+=2)
                {
                    tmp = ptr[i];
                    ptr[i] = ptr[i+1];
                    ptr[i+1] = tmp;
                }
                imu_rx.roll += ROLL_OFFSET;
                roll += (float)imu_rx.roll/1000;
                imu_rx.pitch += PITCH_OFFSET;
                pitch += (float)imu_rx.pitch/1000;
                imu_rx.yaw += YAW_OFFSET;
                yaw += (float)imu_rx.yaw/1000;

                imu_rx.x_accel += X_OFFSET;
                imu_rx.y_accel += Y_OFFSET;
                imu_rx.z_accel += Z_OFFSET;

                if(stream_data_flag)
                {
                    FILE * tmp_ptr = stdout;
                    stdout = &usb_out;
                    int j;
                    for(j = 0; j < sizeof(struct imu_rx_pkt_t); j++)
                    {
                        printf("%c", ptr[j]);
                    }
                    stdout = tmp_ptr;
                }
            }
            else
                SPIE.DATA = 0;
        }
    }
    /*** Handle MCU Transfer ***/
    else if(slave == MCU_SPI)
    {
        if(send_mcu_pkt_flag == 1)
        {
            char * mcu_tx_ptr = (char *)&mcu_tx;
            _delay_us(1);
            SPIE.DATA = mcu_tx_ptr[mcu_tx_index];
            mcu_tx_index++;
            if(mcu_tx_index > sizeof(struct mcu_tx_pkt_t))
            {
                send_mcu_pkt_flag = 0;
                receive_mcu_pkt_flag = 1;
                mcu_rx_first_packet_flag = 1;
            }
        }
        if(receive_mcu_pkt_flag == 1)
        {
            char * mcu_rx_ptr = (char *)&mcu_rx;
            _delay_us(1);
            mcu_rx_ptr[mcu_rx_index] = SPIE.DATA;
            if(mcu_rx_first_packet_flag)
            {
                SPIE.DATA = 0;
                mcu_rx_first_packet_flag = 0;
            }
            else{
                mcu_rx_index++;
                if(mcu_rx_index > sizeof(struct mcu_rx_pkt_t))
                {
                    receive_mcu_pkt_flag = 0;
                    PORTB.OUTSET = 1<<SS0;

                    //reverse order of bytes
                    /*
                    int j;
                    char tmp2;
                    for(j = 0; j < sizeof(struct mcu_rx_pkt_t)-1; j+=2)
                    {
                        tmp2 = mcu_rx_ptr[j];
                        mcu_rx_ptr[j] = mcu_rx_ptr[j+1];
                        mcu_rx_ptr[j+1] = tmp2;
                    }
                    */

                }
                else
                    SPIE.DATA = 0;
            }
        }
    }
}

/***** xbee *****/
ISR(USARTF0_TXC_vect)
{
}

ISR(USARTF0_RXC_vect) 
{
    unsigned char c = USARTF0.DATA;
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
    //stdout = &usb_out;
    //printf("Received: %c via rs232.\n\r", c);
}

/***** sonar *****/
ISR(USARTE0_TXC_vect)
{
}

ISR(USARTE0_RXC_vect)
{
    unsigned char c = USARTE0.DATA;
    //stdout = &usb_out;
    //printf("Received: %c via sonar.\n\r", c);
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
    cli();
    PORTB.DIRSET = 1<<SS0;

    LED_1_GREEN_OFF();
    LED_2_GREEN_OFF();
    LED_3_GREEN_OFF();
    LED_4_GREEN_OFF();

    init_clk();
    init_spi();
    init_adc(&ADCA);

    //set led pins as outputs
    PORTA.DIRSET = 0b11110000;
    PORTF.DIRSET = 0b11110000;

    LED_4_RED_OFF();

    PORTD.DIRSET=PIN5_bm; //drive rs232 enable low
    PORTD.OUTCLR=PIN5_bm;

    init_xbee_uart  (-5, 3301); //32MHz, 19200 baud
    init_usb_uart   (10, 1047); //32MHz, 115200 baud
    init_rs232_uart (10, 1047); //32MHz, 115200 baud
    init_sonar_uart (10, 1047); //32MHz, 115200 baud

    LED_4_GREEN_ON();

    init_mcu_tx_pkt(&mcu_tx);
    init_mcu_rx_pkt(&mcu_rx);

    init_imu_tx_pkt(&imu_tx);
    init_imu_rx_pkt(&imu_rx);

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
        if(loop_count == 100)
        {
            if(print_status_flag)
            {
                stdout = &usb_out;
                print_status();
            }
            loop_count = 0;
        }
        printf("\r");
        printf("fcu: %s", usb_rx_buf);

        request_imu_pkt();
        roll_pid_output  = pid_iteration (&roll_pid, imu_rx.roll, 0);
        pitch_pid_output = pid_iteration (&pitch_pid, imu_rx.pitch, 0);
        yaw_pid_output   = pid_iteration (&yaw_pid, imu_rx.yaw, 0);
        send_mcu_pkt();
        char * mcu_ptr = &mcu_tx;
        mcu_ptr++;
        //mcu_tx.crc = crc((char *)mcu_ptr, 8, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
        _delay_us(100);
        loop_count++;
    }
    return 0;
}
