#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "crc.h"
#include "pid.h"
#include "spi.h"

void print_status(void)
{
    printf("%c", 12);
    print_pid_info(&pid);
    print_mot_pkts(&mot_tx, &mot_rx);
    print_imu_pkts(&imu_tx, &imu_rx);
    print_bat();
}
 
void print_bat(void)
{
    printf("\n\rbattery: %0.4fV\n\r", (double)bat_voltage_human);
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
    else if(strcmp(cmd, "print_status") == 0) { if(print_status_flag == 0)print_status_flag = 1; else print_status_flag = 0; }
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
    else if(strcmp(cmd, "request_imu") == 0) { request_imu_pkt(); }
    else if(strcmp(cmd, "init_imu_rx") == 0) { init_imu_rx_pkt(&imu_rx); }
    else if(strcmp(cmd, "write") == 0) { printf("\n\r\n\r%d\n\r", spi_write_read((uint8_t)val, SS1)); }
    else { printf("\n\rcommand not found: %s", cmd); }
}

void print_imu_pkts(volatile struct imu_tx_pkt_t * tx_pkt, volatile struct imu_rx_pkt_t * rx_pkt)
{
    printf("\n\r\n\r");
    printf("imu_tx_pkt:\t\timu_rx_pkt:\n\r");
    printf("\tstart:   %#02x\t        start:       %#02x\n\r",     tx_pkt->start,      rx_pkt->start);
    printf("\t                        chksum:    %6d\n\r",     rx_pkt->chksum);
    printf("\t                        pitch_tmp: %6d\n\r",     rx_pkt->pitch_tmp);
    printf("\t                        pitch:     %6d\n\r",     rx_pkt->pitch);
    printf("\t                        yaw:       %6d\n\r",     rx_pkt->yaw);
    printf("\t                        yaw_tmp:   %6d\n\r",     rx_pkt->yaw_tmp);
    printf("\t                        z_accel:   %6d\n\r",     rx_pkt->z_accel);
    printf("\t                        y_accel:   %6d\n\r",     rx_pkt->y_accel);
    printf("\t                        x_accel:   %6d\n\r",     rx_pkt->x_accel);
    printf("\t                        roll:      %6d\n\r",     rx_pkt->roll);

    printf("\n\r%02X %02X %04X %04X %04X %04X %04X %04X %04X %04X\n\r", rx_pkt->start, rx_pkt->chksum, rx_pkt->pitch_tmp, rx_pkt->pitch, rx_pkt->yaw, rx_pkt->yaw_tmp, rx_pkt->z_accel, rx_pkt->y_accel, rx_pkt->x_accel, rx_pkt->roll);
}

void print_mot_pkts(volatile struct mot_tx_pkt_t * tx_pkt, volatile struct mot_rx_pkt_t * rx_pkt)
{   
    printf("\n\r");
    tx_pkt->crc = crc((char *)tx_pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
    printf("\n\r");
    printf("mot_tx_pkt:\t\tmot_rx_pkt:\n\r");
    printf("\tstart:   %#02x\t\tstart:   %#02x\n\r", tx_pkt->start, rx_pkt->start);
    printf("\ttgt_1: %6lu\t\tspd_1: %6lu\n\r", (uint32_t)tx_pkt->tgt_1, (uint32_t)rx_pkt->spd_1);
    printf("\ttgt_1: %6lu\t\tspd_2: %6lu\n\r", (uint32_t)tx_pkt->tgt_2, (uint32_t)rx_pkt->spd_2);
    printf("\ttgt_1: %6lu\t\tspd_3: %6lu\n\r", (uint32_t)tx_pkt->tgt_3, (uint32_t)rx_pkt->spd_3);
    printf("\ttgt_1: %6lu\t\tspd_4: %6lu\n\r", (uint32_t)tx_pkt->tgt_4, (uint32_t)rx_pkt->spd_4);
    printf("\tcrc:   %6d\t\tcrc:   %6d\n\r", tx_pkt->crc, rx_pkt->crc);
}

void run_cmd(float val, char * (*function_ptr)(float))
{
    char * result = function_ptr(val);
    printf("%s\n\r", result);
}
