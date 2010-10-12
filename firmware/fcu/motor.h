#include <inttypes.h>
#include "usart_driver.h"

#define MOTOR_MIN_POWER 0
#define MOTOR_MAX_POWER 200

volatile struct motor {
    int16_t speed;
    USART_t * usart;
    uint8_t killFlag;
    char packet[25];
};

void setMotorSpeed (volatile struct motor * motor, int8_t speed);
void initMotor (volatile struct motor * motor, USART_t * usart);
