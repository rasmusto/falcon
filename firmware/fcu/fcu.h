#define F_CPU 32000000UL
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#include "spi_driver.h"
#include "avr_compiler.h"

/* Led bitmasks */
//#define LED_MISC_4_GREEN() PORTF.OUTCLR=PIN4_bm;PORTF.OUTSET=PIN5_bm
#define LED_1_RED_ON()      PORTA.OUTCLR=PIN4_bm;
#define LED_1_RED_OFF()     PORTA.OUTSET=PIN4_bm;
#define LED_1_GREEN_ON()    PORTA.OUTCLR=PIN5_bm;
#define LED_1_GREEN_OFF()   PORTA.OUTSET=PIN5_bm;

#define LED_2_RED_ON()      PORTA.OUTCLR=PIN6_bm;
#define LED_2_RED_OFF()     PORTA.OUTSET=PIN6_bm;
#define LED_2_GREEN_ON()    PORTA.OUTCLR=PIN7_bm;
#define LED_2_GREEN_OFF()   PORTA.OUTSET=PIN7_bm;

#define LED_3_RED_ON()      PORTF.OUTCLR=PIN4_bm;
#define LED_3_RED_OFF()     PORTF.OUTSET=PIN4_bm;
#define LED_3_GREEN_ON()    PORTF.OUTCLR=PIN5_bm;
#define LED_3_GREEN_OFF()   PORTF.OUTSET=PIN5_bm;

#define LED_4_RED_ON()      PORTF.OUTCLR=PIN6_bm;
#define LED_4_RED_OFF()     PORTF.OUTSET=PIN6_bm;
#define LED_4_GREEN_ON()    PORTF.OUTCLR=PIN7_bm;
#define LED_4_GREEN_OFF()   PORTF.OUTSET=PIN7_bm;

/* Function Prototypes */
static void spi_init (void);

static void uart_usb_init (void);
static void uart_cpu_init (void);
static void uart_xbee_init (void);
static void uart_sonar_init (void);

/*
static USART_t usbUSART = &USART<XX>
static USART_t cpuUSART = &USART<XX>
static USART_t xbeeUSART = &USART<XX>
static USART_t sonarUSART = &USART<XX>
*/

volatile uint8_t mcu_tx_packet[8];
volatile uint8_t mcu_rx_packet[8];

volatile uint8_t imu_tx_packet[1];
volatile uint8_t imu_rx_packet[16];

/*** APP NOTE CODE ***/
/*! \brief Number of test data bytes. */
#define NUM_BYTES   2
/* Global variables. */
/*! \brief SPI master on PORT C. */
SPI_Master_t spiMasterC;
/*! \brief SPI slave on PORT D. */
SPI_Slave_t spiSlaveD = {NULL, NULL};
/*! \brief Data packet. */
SPI_DataPacket_t dataPacket;
/*! \brief Test data to send. */
const uint8_t sendData[NUM_BYTES + 1] = { 0x55, 0xaa, 0x00 };
/*! \brief Buffer for test data reception. */
uint8_t receivedData[NUM_BYTES + 1];
/*! \brief Result of the example test. */
bool success;
/*** END APP NOTE CODE ***/

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

void mot_tx(mot_tx_pkt mot);
void imu_tx(imu_tx_pkt imu);
void imu_rx(imu_rx_pkt imu);
