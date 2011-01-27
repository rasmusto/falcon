#define F_CPU 32000000UL
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

#include "spi_driver.h"
#include "avr_compiler.h"
#include "usart_driver.h"
#include "clksys_driver.h"

//#include "/usr/lib/avr/include/avr/iox128a3.h"

/* Led bitmasks */
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

/* Function Prototypes */
static void spi_init (void);

void init_xbee_uart (int8_t bScale, uint16_t bSel);
void init_usb_uart (int8_t bScale, uint16_t bSel);
void init_rs232_uart (int8_t bScale, uint16_t bSel);
void init_sonar_uart (int8_t bScale, uint16_t bSel);

void putchar_xbee (char c);
void putchar_usb (char c);
void putchar_rs232 (char c);
void putchar_sonar (char c);

volatile uint8_t mcu_tx_packet[8];
volatile uint8_t mcu_rx_packet[8];

volatile uint8_t imu_tx_packet[1];
volatile uint8_t imu_rx_packet[16];

/*
typedef struct
{
    uint8_t start;
    uint8_t mot_num;
    uint8_t target;
    uint8_t * crc;
} mot_tx_pkt;

typedef struct
{
    uint8_t start;
    uint8_t request;
    uint8_t * crc;
} imu_tx_pkt;

typedef struct
{
    uint8_t start;
    uint8_t * data;
    uint8_t * crc;
} imu_rx_pkt;
*/

/*
void mot_tx(mot_tx_pkt mot);
void imu_tx(imu_tx_pkt imu);
void imu_rx(imu_rx_pkt imu);
*/
