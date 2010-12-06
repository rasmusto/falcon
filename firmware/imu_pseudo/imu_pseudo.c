#include "imu_pseudo.h"

uint8_t spi_init();
uint8_t adc_init();

char imu_buff[IMU_PACKET_SIZE];
uint16_t mag_x,mag_y,mag_z,gyro_x,gyro_y,gyro_z,accel_x,accel_y,accel_z;

int main(void)
{
    if (spi_init() == -1)
        error("spi");
    if (adc_init() == -1)
        error("adc");
    while(1)
    {
        //read digital accelerometer values
        read_accel(accel_x, accel_y, accel_z);
        //read digital gyroscope values
        read_gyro(gyro_x, gyro_y, gyro_z);
        //read analog magnetometer values
        read_mag(mag_x, mag_y, mag_z);
        //run kalman filter on data
        kalman_filter(  accel_x, accel_y, accel_z, 
                        gyro_x, gyro_y, gyro_z, 
                        mag_x, mag_y, mag_z);
        //create data packet
        create_packet(imu_buff);
        //send data packet to fcu over SPI
        imu_write(imu_buff);
    }
    return 0;
}
