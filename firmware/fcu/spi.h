#include "spi_driver.h"

/* Signal select defines */
#define SS0     PIN0_bp
#define SS1     PIN1_bp
#define SS2     PIN2_bp
#define SS3     PIN3_bp
#define SS4     PIN4_bp
#define SS5     PIN5_bp
#define SS6     PIN6_bp
#define SS7     PIN7_bp

void init_spi(void);
void spi_write(char data, uint8_t pin);
void spi_write_multi(char * packet, uint8_t length, uint8_t pin);
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
