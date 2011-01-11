#include "fcu.h"

/* One USART for all motors */
static USART_t * motorUSART = &USARTD0;  

/* Buffers for receiving serial packets */
char imuRxBuffer[1000];
char packetBuffer[100];
char commandPacketBuffer[9];
char debugRxBuffer[500];

/* Important Variables */
volatile struct pidInfo rollPid;
volatile struct pidInfo pitchPid;
volatile struct pidInfo yawPid;
volatile int16_t motorPower = 0;
volatile uint8_t zeroYawTargetFlag = 0;

volatile uint8_t rollEnableFlag = 0;
volatile uint8_t pitchEnableFlag = 0;
volatile uint8_t yawEnableFlag = 0;

volatile struct Euler_aar_pkt *eulerPkt = (struct Euler_aar_pkt*) malloc(sizeof(struct Euler_aar_pkt));

volatile uint8_t imuDataFlag;
volatile uint8_t commandFlag;
volatile uint8_t noCommandCounter;

volatile struct motor * motor1;
volatile struct motor * motor2;
volatile struct motor * motor3;
volatile struct motor * motor4;

int main(void)
{
    /* Set up system clock */
    ConfigClock();

    /* Set all ports as outputs */
    PORTA.DIR = 0xFF;
    PORTB.DIR = 0xFF;
    PORTC.DIR = 0xFF;
    PORTD.DIR = 0xFF;
    PORTE.DIR = 0xFF;
    PORTF.DIR = 0xFF;

    /* Set up serial communication */
    initMotorUart();
    initIMUUart();
    initDebugUart();

    /* Wait to receive IMU data packet */
    /*
    while (1)
    {
    }
    */

    /* Reset timer to 0 to time PID iteration */
    TCC1.CNT = 0;

    /* Main while loop */
    while (1)
    {
        if(TCC1.CNT >= 10000)
        {
            /* PID is taking too long */
        }

        /* Run the while loop every 20ms */
        while(TCC1.CNT < 5000){}
        TCC1.CNT = 0;

        if (imuDataFlag) 
        {
            /* Process IMU data */

            imuDataFlag = 0;
        }

        /* KILL THE MOTORS IF ANGLE IS TOO GREAT */
        if(eulerPkt->roll > 0.50 || eulerPkt->pitch > 0.50)
        {
            motor1->killFlag = 1;
            motor2->killFlag = 1;
            motor3->killFlag = 1;
            motor4->killFlag = 1;
        }
        if(eulerPkt->roll < -0.50 || eulerPkt->pitch < -0.50)
        {
            motor1->killFlag = 1;
            motor2->killFlag = 1;
            motor3->killFlag = 1;
            motor4->killFlag = 1;
        }

        /* ROLL PID */
        float rollPidOutput;
        rollPidOutput = pidIteration(&rollPid, eulerPkt->roll, eulerPkt->timer);
        motor1->speed = motorPower + (int16_t)rollPidOutput;
        motor3->speed = motorPower - (int16_t)rollPidOutput;
        /* END ROLL PID */

        /* PITCH PID */
        float pitchPidOutput;
        pitchPidOutput = pidIteration(&pitchPid, eulerPkt->pitch, eulerPkt->timer);
        motor2->speed = motorPower + (int16_t)pitchPidOutput;
        motor4->speed = motorPower - (int16_t)pitchPidOutput;
        /* END PITCH PID */

        /* YAW PID */
        float yawPidOutput;
        yawPidOutput = pidIteration(&yawPid, eulerPkt->yaw, eulerPkt->timer);

        motor1->speed -= (int16_t)yawPidOutput;
        motor2->speed += (int16_t)yawPidOutput;

        motor3->speed -= (int16_t)yawPidOutput;
        motor4->speed += (int16_t)yawPidOutput;
        /* END YAW PID */

        /* Check if motor speeds overflow */
        if (motor1->speed > 255)
            motor1->speed = 255;
        if (motor1->speed < 0)
            motor1->speed = 0;

        if (motor2->speed > 255)
            motor2->speed = 255;
        if (motor2->speed < 0)
            motor2->speed = 0;

        if (motor3->speed > 255)
            motor3->speed = 255;
        if (motor3->speed < 0)
            motor3->speed = 0;

        if (motor4->speed > 255)
            motor4->speed = 255;
        if (motor4->speed < 0)
            motor4->speed = 0;

        if(rollEnableFlag){
            setMotorSpeed(motor1, (uint8_t)motor1->speed);
            setMotorSpeed(motor3, (uint8_t)motor3->speed);
        }else{
            setMotorSpeed(motor1, 0);
            setMotorSpeed(motor3, 0);
        }

        if(pitchEnableFlag){
            setMotorSpeed(motor2, (uint8_t)motor2->speed);
            setMotorSpeed(motor2, (uint8_t)motor4->speed);
        }else{
            setMotorSpeed(motor2, 0);
            setMotorSpeed(motor2, 0);
        }

        /* Check for commands, kill if >100 haven't been received */
        if (commandFlag) {
            readPacket(commandPacketBuffer);
            commandFlag = 0;
            noCommandCounter = 0;
        } else {
            noCommandCounter++;
            if (noCommandCounter > 100) {
                motor1->killFlag = 1;
                motor2->killFlag = 1;
                motor3->killFlag = 1;
                motor4->killFlag = 1;
            }
        }

    return 0;
}

