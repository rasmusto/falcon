#include "imu.h"
#include <stdio.h>
#include <util/delay.h>

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
    //spi_write((char)IMU_START>>8, SS1); 
    //spi_write((char)IMU_START>>0, SS1); 
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
