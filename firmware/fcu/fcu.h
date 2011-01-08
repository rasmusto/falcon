#define F_CPU 32000000UL
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "usart_driver.h"
#include "clksys_driver.h"
#include "pid.h"
#include "TC_driver.h"
#include "crc.h"
#include "motor.h"

void ConfigClock (void);
void ConfigClk64Timer (volatile TC0_t * tc);

static void initMotorUart (void);
static void initIMUUart (void);
static void initDebugUart (void);

static int putcharIMU(char c, FILE *stream);
static int putcharDebug(char c, FILE *stream);
static int putcharCtrl(char c, FILE *stream);

void readPacket(char *rxBuffer);  //debug

//usb to serial
#define usb_rx USARTC1.RXD1
#define usb_tx USARTC1.TXD1

//xbee
#define xbee_rx USARTF0.RXD0
#define xbee_tx USARTF0.TXD0

//sonar
#define sonar_rx USARTE0.RXD0
#define sonar_tx USARTE0.TXD0

//spi chip select
#define SS0 PB0
#define SS1 PB1
#define SS2 PB2
#define SS3 PB3
#define SS4 PB4
#define SS5 PB5
#define SS6 PB6
#define SS7 PB7

//rc receiver
#define rc1 PD3
#define rc2 PD2
#define rc3 PD1
#define rc4 PD0
#define rc5 PC3
#define rc6 PC2
#define rc7 PC1
#define rc8 PC0

//leds
#define led0 PA4
#define led1 PA3
#define led2 PA2
#define led3 PA1
#define led4 PF4
#define led5 PF5
#define led6 PF6
#define led7 PF7
