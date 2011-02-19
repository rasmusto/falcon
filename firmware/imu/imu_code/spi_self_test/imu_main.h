#ifndef IMU_MAIN_H_
#define IMU_MAIN_H_

#include "DSP28x_Project.h"
#include "crc.h"
#include <stdlib.h>

#define CRC_DIVISOR	0x0007

enum PACKET_TYPE{ RAW_SENSOR_DATA, EULER_ANGLES, STATUS};

#define IMU_PWR_ON() GpioDataRegs.GPBSET.bit.GPIO34 = 1; GpioDataRegs.GPASET.bit.GPIO21 = 1
#define IMU_PWR_OFF() GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; GpioDataRegs.GPACLEAR.bit.GPIO21 = 1
#define ADC_DRDY() !GpioDataRegs.GPADAT.bit.GPIO20

//spi defines
#define SPIA_CHAR_LNGTH_MSK 0x07 //8-bit
#define SPIB_CHAR_LNGTH_MSK 0x0F //16-bit

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
	Uint16 * data;
	Uint16 crc;
	enum PACKET_TYPE type;
	Uint16 length; //length of data in bytes, not including crc
};

struct MY_FLAGS {
	Uint16 want_new_adc_data:1;
	Uint16 rx_half_adc_words:1;
	Uint16 tx_half_adc_words:1;
	Uint16 make_new_fcu_packet:1;
	Uint16 start_new_transmit:1;
	Uint16 wait_for_master:1;
	Uint16 just_for_now:1;
	Uint16 other_stuff:9;
};
union IMU_FLAGS{
	Uint16 all;
	struct MY_FLAGS bit;
};
	
extern volatile union SENSOR_DATA sensors;
extern volatile union IMU_FLAGS flags;
extern volatile struct FCU_PACKET * fcu_tx_packet;
extern volatile struct FCU_PACKET sensor_tx_packet;
extern volatile Uint16 rx_packet[9];

//function prototypes
void InitMicrocontroller(void);
void make_fcu_packet(volatile struct FCU_PACKET * fcu_pkt);
void init_fcu_packet(volatile struct FCU_PACKET * fcu_pkt, enum PACKET_TYPE type);

#endif /*IMU_MAIN_H_*/
