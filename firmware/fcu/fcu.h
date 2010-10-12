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



