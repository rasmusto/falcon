#define F_CPU 32000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <util/delay.h>
#include <string.h>

#include "avr_compiler.h"
#include "spi.h"
#include "uart.h"
#include "clk.h"
#include "crc.h"
#include "adc.h"
#include "adc_driver.h"
#include "pid.h"
#include "cli.h"
#include "shared.h"

//#include "/usr/lib/avr/include/avr/iox128a3.h"

/* Global Variables */

static FILE xbee_out    = FDEV_SETUP_STREAM (putchar_xbee,  NULL, _FDEV_SETUP_WRITE);
static FILE usb_out     = FDEV_SETUP_STREAM (putchar_usb,   NULL, _FDEV_SETUP_WRITE);
static FILE rs232_out   = FDEV_SETUP_STREAM (putchar_rs232, NULL, _FDEV_SETUP_WRITE);
static FILE sonar_out   = FDEV_SETUP_STREAM (putchar_sonar, NULL, _FDEV_SETUP_WRITE);

/* Function Prototypes */
void init_mot_tx_pkt(volatile struct mot_tx_pkt_t * pkt);
void init_mot_rx_pkt(volatile struct mot_rx_pkt_t * pkt);

void init_imu_tx_pkt(volatile struct imu_tx_pkt_t * pkt);
void init_imu_rx_pkt(volatile struct imu_rx_pkt_t * pkt);
void request_imu_pkt();
