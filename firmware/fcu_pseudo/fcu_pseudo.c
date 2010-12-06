#include "fcu_pseudo.h"

uint8_t spi_init();
uint8_t uart_init();

char * imu_buff[IMU_PACKET_SIZE];
char * mcu_buff[MCU_PACKET_SIZE];

int main(void)
{
    if (spi_init() == -1)
        error("spi");
    if (uart_init() == -1)
        error("uart");
    while(1)
    {
        //read in sensor packet over SPI
        imu_read(imu_buff);
        //process data and store in mcu packet buffer
        imu_process(imu_buff, mcu_buff);
        //write mcu packet over SPI
        mcu_write(mcu_buff);
    }
    return 0;
}
