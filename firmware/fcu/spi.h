#include "spi_driver.h"

/* Signal select defines */
#define SS0     PIN0_bm
#define SS1     PIN1_bm
#define SS2     PIN2_bm
#define SS3     PIN3_bm
#define SS4     PIN4_bm
#define SS5     PIN5_bm
#define SS6     PIN6_bm
#define SS7     PIN7_bm

void init_spi (void);

/* Global variables. */
/*! \brief Number of test data bytes. */
#define NUM_BYTES   2

/*! \brief SPI master on PORT E. */
SPI_Master_t spiMasterE;

/*! \brief Data packet. */
SPI_DataPacket_t mot_dataPacket;
SPI_DataPacket_t imu_dataPacket;
