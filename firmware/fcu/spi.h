#include "spi_driver.h"

void init_spi(void);
void spi_write(char data, uint8_t pin);
void spi_write_read_multi(char * tx_pkt, char * rx_pkt, uint8_t len, uint8_t pin);
char spi_read(uint8_t pin);
char spi_write_read(char data, uint8_t pin);

/* Global variables. */
/*! \brief Number of test data bytes. */
#define NUM_BYTES   2

/*! \brief SPI master on PORT E. */
SPI_Master_t spiMasterE;

/*! \brief Data packet. */
SPI_DataPacket_t mot_dataPacket;
SPI_DataPacket_t imu_dataPacket;
