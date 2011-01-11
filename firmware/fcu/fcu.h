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

/* Function Prototypes */
static void init_spi (void);

static void init_usb_uart (void);
static void inti_cpu_uart (void);
static void inti_xbee_uart (void);
static void inti_sonar_uart (void);

static USART_t usbUSART = &USART<XX>
static USART_t cpuUSART = &USART<XX>
static USART_t xbeeUSART = &USART<XX>
static USART_t sonarUSART = &USART<XX>

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
