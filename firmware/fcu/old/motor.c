#include "motor.h"

void setMotorSpeed (volatile struct motor * motor, int8_t speed)
{
    if(speed > MOTOR_MAX_POWER){ speed = MOTOR_MAX_POWER; }

    if(!motor->killFlag){	

        motor->packet[0] = '#';
        motor->packet[1] = 'b';
        motor->packet[2] = 't';

        motor->packet[3] = motor->speed >> 2;
        motor->packet[4] = motor->speed%4 << 4;
        motor->packet[3] += '=';
        motor->packet[4] += '=';

        int i;
        for (i=5;i<19;i++)
            motor->packet[i] = '=';	

        // checksum
        unsigned int tmpCRC = 0;

        for(i=0; i<19; i++) {
            tmpCRC += motor->packet[i];
        }

        tmpCRC %= 4096;
        motor->packet[19] = '=' + tmpCRC / 64;
        motor->packet[20] = '=' + tmpCRC % 64;

        motor->packet[21] = '\r';
        motor->packet[22] = '\r';
        motor->packet[23] = '\r';
        motor->packet[24] = '\0';

        USART_DreInterruptLevel_Set (motor->usart, USART_DREINTLVL_LO_gc);
    }
}

void initMotor (volatile struct motor * motor, USART_t * usart)
{
    motor->speed = 0;
    motor->usart = usart;
    motor-> killFlag = 0;
}
