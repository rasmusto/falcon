#ifndef IMU_MAIN_H_
#define IMU_MAIN_H_

#include "DSP28x_Project.h"
#include <stdlib.h>

#define CRC_DIVISOR	7
#define START_BYTE

#define uint8_t unsigned char

//function prototypes
void InitMicrocontroller(void);
void make_fcu_packet(struct FCU_PACKET * fcu_pkt, enum PACKET_TYPE type);


#define IMU_PWR_ON() GpioDataRegs.GPBSET.bit.GPIO34 = 1; GpioDataRegs.GPASET.bit.GPIO21 = 1
#define IMU_PWR_OFF() GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; GpioDataRegs.GPACLEAR.bit.GPIO21 = 1
#define ADC_DRDY() !GpioDataRegs.GPADAT.bit.GPIO20

//spi defines
#define SPIA_CHAR_LNGTH_MSK 0x0F //16-bit
#define SPIB_CHAR_LNGTH_MSK 0x07 //8-bit

enum PACKET_TYPE{ RAW_SENSOR_DATA, EULER_ANGLES, STATUS};



struct SENSOR_VALUES {
	int	pitch_temp;
	int pitch;
	int yaw;
	int yaw_temp;
	int z_accel;
	int y_accel;
	int x_accel;
	int roll;
};
union SENSOR_DATA {
	int	sensor[8];
	struct SENSOR_VALUES value;
};

struct FCU_PACKET {
	char * data;
	uint8_t crc;
	enum PACKET_TYPE type;
	uint8_t length; //length of data in bytes, not including crc
};

struct MY_FLAGS {
	Uint16 want_new_adc_data:1;
	Uint16 rx_half_adc_words:1;
	Uint16 tx_half_adc_words:1;
	Uint16 make_new_fcu_packet:1;
	Uint16 other_stuff:12;
};
union IMU_FLAGS{
	Uint16 all;
	struct MY_FLAGS bit;
};
	
extern volatile union SENSOR_DATA sensors;
extern volatile union IMU_FLAGS flags;
extern volatile struct FCU_PACKET fcu_tx_packet;

#endif /*IMU_MAIN_H_*/
