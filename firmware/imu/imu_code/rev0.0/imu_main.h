#ifndef IMU_MAIN_H_
#define IMU_MAIN_H_

#include "DSP28x_Project.h"
#include "CLAShared.h"
#include <stdlib.h>

enum PACKET_TYPE{ RAW_SENSOR_DATA, EULER_ANGLES, STATUS};

#define IMU_PWR_ON() GpioDataRegs.GPBSET.bit.GPIO34 = 1; GpioDataRegs.GPASET.bit.GPIO21 = 1
#define IMU_PWR_OFF() GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; GpioDataRegs.GPACLEAR.bit.GPIO21 = 1
#define ADC_DRDY() !GpioDataRegs.GPADAT.bit.GPIO20

//multipliers for sensors.
//results in gyro readings in deg/sec or rad/sec
//accelerometer readings in m/(s^2)
#define GYRO_RAD_MULT	0.00022193686
#define GYRO_DEG_MULT 	0.012716046
#define TEMP_MULT		1
#define ACCEL_MULT		0.0039091476

//spi defines
#define SPIA_CHAR_LNGTH_MSK 0x0F //16-bit
#define SPIB_CHAR_LNGTH_MSK 0x0F //16-bit
#define FCU_START 0xFACE

struct SENSOR_VALUES {
	int roll;
	int	pitch_temp;
	int pitch;
	int yaw;
	int yaw_temp;
	int z_accel;
	int x_accel;
	int y_accel;
};
union SENSOR_DATA {
	int	sensor[8];
	struct SENSOR_VALUES value;
};

struct FCU_PACKET {
	Uint16 * data;
	enum PACKET_TYPE type;
	Uint16 length; //length of data in bytes, not including crc
};

struct MY_FLAGS {
	Uint16 want_new_adc_data:1;
	Uint16 rx_half_adc_words:1;
	Uint16 tx_half_adc_words:1;
	Uint16 wait_for_master:1;
	Uint16 make_new_fcu_packet:1;
	Uint16 other_stuff:11;
};
union IMU_FLAGS{
	Uint16 all;
	struct MY_FLAGS bit;
};
	
extern volatile union SENSOR_DATA sensors;
extern volatile union IMU_FLAGS flags;
extern volatile struct FCU_PACKET * fcu_tx_packet;
extern volatile struct FCU_PACKET sensor_tx_packet;

// These are defined by the linker file and used to copy
// the CLA code from its load address to its run address
// in CLA program memory in the CLA initalization function
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadEnd;
extern Uint16 Cla1funcsRunStart;
//Cla data memory locations
extern Uint16 Cla1DataLoadStart;
extern Uint16 Cla1DataLoadEnd;
extern Uint16 Cla1DataRunStart;

//function prototypes
void InitMicrocontroller(void);
void make_fcu_packet(volatile struct FCU_PACKET * fcu_pkt);
void init_fcu_packet(volatile struct FCU_PACKET * fcu_pkt, enum PACKET_TYPE type);
Uint16 parity_byte(Uint16 * data, Uint16 length);

#endif /*IMU_MAIN_H_*/
