#include "fcu.h"

#define NUM_CMDS 4

volatile char usb_rx_buf[128];
volatile uint8_t usb_rx_count = 0;

volatile char xbee_rx_buf[128];
volatile uint8_t xbee_rx_count = 0;

volatile struct mot_tx_pkt_t mot_tx;
volatile struct mot_rx_pkt_t mot_rx;

volatile struct imu_tx_pkt_t imu_tx;
volatile struct imu_rx_pkt_t imu_rx;

volatile uint8_t bat_voltage;

void init_mot_tx_pkt(volatile struct mot_tx_pkt_t * mot_tx)
{
    mot_tx->start = MOT_START;
    mot_tx->tgt_1 = 0;
    mot_tx->tgt_2 = 0;
    mot_tx->tgt_3 = 0;
    mot_tx->tgt_4 = 0;
    mot_tx->crc = crc((char *)&mot_tx, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
}

void print_mot_tx_pkt(volatile struct mot_tx_pkt_t * mot_tx)
{
    printf("%c\n\r", mot_tx->start);
    printf("%d\n\r", mot_tx->tgt_1);
    printf("%d\n\r", mot_tx->tgt_2);
    printf("%d\n\r", mot_tx->tgt_3);
    printf("%d\n\r", mot_tx->tgt_4);
    printf("%d", mot_tx->crc);
}
    

void mot_tx_rx(volatile struct mot_tx_pkt_t * mot_tx, volatile struct mot_rx_pkt_t * mot_rx)
{
    mot_tx->crc = crc((char *)&mot_tx, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
    spi_write_multi(mot_tx, sizeof(mot_tx), SS0);
}

void imu_tx_rx(volatile struct imu_tx_pkt_t * imu_tx, volatile struct imu_rx_pkt_t * imu_rx)
{
    imu_tx->crc = crc((char *)&imu_tx, 9, 7); //calculate the crc on the first 9 bytes of imu packet with divisor 7
    spi_write_multi(imu_tx, sizeof(imu_tx), SS1);
}

void process_rx_buf(volatile char * rx_buf)
{
    char cmd[64];
    char cmds[NUM_CMDS][64] = {"reboot", "print_mot", "help"};
    cmds[NUM_CMDS-1][0] = '\0';
    cmd[0] = '\0';
    int16_t val = 0;
    sscanf(rx_buf, "%s%d", cmd, &val);
    //printf("\n\rcommand: %s\n\rvalue: %d\n\r", command, value);
    int cmd_num = NUM_CMDS;
    int i;
    if(cmd[0] != '\0')
    {
        for(i = 0; i < NUM_CMDS; i++)
        {
            if(strcmp(cmd, cmds[i]) == 0)
                cmd_num = i;
        }
    }
    switch(cmd_num)
    {
        case 0:
            printf("\n\rrebooting...");
            CCPWrite(&RST_CTRL, RST_SWRST_bm);
            break;
        case 1:
            print_mot_tx_pkt(&mot_tx);
            break;
        case 2:
            printf("\n\rreboot\n\rprint\n\rhelp");
            break;
        case 3:
            break;
        case NUM_CMDS:
            printf("\n\rcommand not found: %s", cmd);
            break;
    }
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
    /*
    if(c == '\r')
    {
        xbee_rx_buf[xbee_rx_count] = '\0';
        if (strcmp(xbee_rx_buf, "reboot") == 0)
        {
            printf("\n\rdown :(   \n\r");
            CCPWrite(&RST_CTRL, RST_SWRST_bm);
        }
        else if(strcmp(xbee_rx_buf, "clear") == 0)
        {
            printf("%c", 12);
        }
        else if(strcmp(xbee_rx_buf, "help") == 0)
        {
            printf("\n\rCommands:\n\rreboot\n\rclear\n\rprint_mot\n\rhelp");
        }
        else if(strcmp(xbee_rx_buf, "print_mot") == 0)
        {
            print_mot_tx_pkt(&mot_tx);
        }
        else if(strlen(xbee_rx_buf) > 0)
            printf("\n\rcommand not found: %s", xbee_rx_buf);
        printf("\n\rroot@fcu: ");
        xbee_rx_count = 0;
    }
    else 
    { 
        xbee_rx_buf[xbee_rx_count] = c; 
        xbee_rx_count++;
    }
    */
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
    else
    {
        usb_rx_buf[usb_rx_count] = c; 
        usb_rx_count++;
    }

    /*
    if(c == '\r')
    {
        usb_rx_buf[usb_rx_count] = '\0';
        if (strcmp(usb_rx_buf, "reboot") == 0)
        {
            printf("\n\rdown :(   \n\r");
            CCPWrite(&RST_CTRL, RST_SWRST_bm);
        }
        else if(strcmp(usb_rx_buf, "clear") == 0)
        {
            printf("%c", 12);
        }
        else if(strcmp(usb_rx_buf, "help") == 0)
        {
            printf("\n\rCommands:\n\rreboot\n\rclear\n\rprint_mot\n\rhelp");
        }
        else if(strcmp(usb_rx_buf, "print_mot") == 0)
        {
            print_mot_tx_pkt(&mot_tx);
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
    */
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
/*
ISR(ADCA_CH0_vect)
{
    bat_voltage = (ADCA.CH0RES - adc_offset);
}
*/

int main (void) 
{
    LED_1_GREEN_OFF();
    LED_2_GREEN_OFF();
    LED_3_GREEN_OFF();
    LED_4_GREEN_OFF();

    init_clk();
    init_spi();

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

    stdout = &usb_out;
    printf("%c", 12);
    printf("up :)\n\r");
    stdout = &rs232_out;
    stdout = &xbee_out;
    stdout = &sonar_out;

    sei();

    /************** Main Loop ***************/
    while(1)
    {
        mot_tx_rx(&mot_tx, &mot_rx);
        stdout = &rs232_out;
        printf("rs232\n\r");
    }
    return 0;
}
