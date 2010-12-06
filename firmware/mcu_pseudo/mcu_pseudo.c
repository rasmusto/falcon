#include "mcu_pseudo.h"

uint8_t spi_init();
uint8_t adc_init();

char fcu_buff[FCU_PACKET_SIZE];
char mcu_buff[MCU_PACKET_SIZE];
uint16_t mot1_speed, mot2_speed, mot3_speed, mot4_speed;

int main(void)
{
    if (spi_init() == -1)
        error("spi");
    if (adc_init() == -1)
        error("adc");
    while(1)
    {
        //read packet from fcu over SPI
        fcu_read(fcu_buff);
        //process packet from fcu
        fcu_process(fcu_buff, mcu_buff);
        //read back emf from adc
        read_emf();
        //update motor targets
        set_target(mcu_buff);
    }
}
