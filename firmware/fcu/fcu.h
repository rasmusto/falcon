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

//#include "/usr/lib/avr/include/avr/iox128a3.h"

/* LED bitmasks */
#define LED_1_RED_ON()      PORTA.OUTSET=PIN4_bm;
#define LED_1_RED_OFF()     PORTA.OUTCLR=PIN4_bm;
#define LED_1_GREEN_ON()    PORTF.OUTSET=PIN4_bm;
#define LED_1_GREEN_OFF()   PORTF.OUTCLR=PIN4_bm;
#define LED_2_RED_ON()      PORTA.OUTSET=PIN5_bm;
#define LED_2_RED_OFF()     PORTA.OUTCLR=PIN5_bm;
#define LED_2_GREEN_ON()    PORTF.OUTSET=PIN5_bm;
#define LED_2_GREEN_OFF()   PORTF.OUTCLR=PIN5_bm;
#define LED_3_RED_ON()      PORTA.OUTSET=PIN6_bm;
#define LED_3_RED_OFF()     PORTA.OUTCLR=PIN6_bm;
#define LED_3_GREEN_ON()    PORTF.OUTSET=PIN6_bm;
#define LED_3_GREEN_OFF()   PORTF.OUTCLR=PIN6_bm;
#define LED_4_RED_ON()      PORTA.OUTSET=PIN7_bm;
#define LED_4_RED_OFF()     PORTA.OUTCLR=PIN7_bm;
#define LED_4_GREEN_ON()    PORTF.OUTSET=PIN7_bm;
#define LED_4_GREEN_OFF()   PORTF.OUTCLR=PIN7_bm;

#define MOT_TX_START 0b01011111
#define MOT_RX_START 0b11110101

/* Global Variables */

static FILE xbee_out    = FDEV_SETUP_STREAM (putchar_xbee,  NULL, _FDEV_SETUP_WRITE);
static FILE usb_out     = FDEV_SETUP_STREAM (putchar_usb,   NULL, _FDEV_SETUP_WRITE);
static FILE rs232_out   = FDEV_SETUP_STREAM (putchar_rs232, NULL, _FDEV_SETUP_WRITE);
static FILE sonar_out   = FDEV_SETUP_STREAM (putchar_sonar, NULL, _FDEV_SETUP_WRITE);

/* Data Structures */
struct mot_tx_pkt_t
{
    volatile uint8_t start;
    volatile uint16_t tgt_1;
    volatile uint16_t tgt_2;
    volatile uint16_t tgt_3;
    volatile uint16_t tgt_4;
    volatile uint8_t crc;
};

struct mot_rx_pkt_t
{
    volatile uint8_t start;
    volatile uint16_t spd_1;
    volatile uint16_t spd_2;
    volatile uint16_t spd_3;
    volatile uint16_t spd_4;
    volatile uint8_t crc;
};

struct imu_tx_pkt_t
{
    volatile uint8_t start;
    volatile uint8_t request;
    volatile uint8_t crc;
    char garbage[11];
};

struct imu_rx_pkt_t
{
    volatile uint8_t start;
    volatile int16_t pitch;
    volatile int16_t roll;
    volatile int16_t yaw;
    volatile int16_t x_accel;
    volatile int16_t y_accel;
    volatile int16_t z_accel;
    volatile uint8_t crc;
};

/* Function Prototypes */
void init_mot_tx_pkt(volatile struct mot_tx_pkt_t * pkt);
void init_imu_tx_pkt(volatile struct imu_tx_pkt_t * pkt);

void print_mot_tx_pkt(volatile struct mot_tx_pkt_t * pkt);
void print_mot_rx_pkt(volatile struct mot_rx_pkt_t * pkt);
void print_imu_tx_pkt(volatile struct imu_tx_pkt_t * pkt);
void print_imu_rx_pkt(volatile struct imu_rx_pkt_t * pkt);

void process_rx_buf(volatile char * rx_buf);
