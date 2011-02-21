#ifndef __NODE_COM_DEFS_H
#define __NODE_COM_DEFS_H

//IMU Commands
#define RAW_ACCELEROMETER_GYRO       0xC1 //--------
#define ACCELERATION_ANGULAR_RATES   0xC2
#define DELTA_ANGLE_DELTA_VELOCITY   0xC3
#define SET_CONTINUOUS_MODE          0xC4
#define ORIENTATION_MATRIX           0xC5
#define ORIENTATION_UPDATE_MATRIX    0xC6
#define SCALED_MAGNETOMETYER_VECTOR  0xC7
#define ACCEL_ANG_RATE_ORIENTATION   0xC8
#define WRTIE_ACCEL_BIAS_CORRECTION  0xC9
#define WRITE_GYRO_BIAS_CORRECTION   0xCA
#define ACCELERATION_ANG_RATE_MAG    0xCB
#define ACCEL_ANG_RATE_MAG_ORIENT    0xCC //--------
#define CAPTURE_GYRO_BIAS            0xCD
#define EULER_ANGLES                 0xCE
#define EULER_ANGLES_ANGULAR_RATES   0xCF
#define DATA_TO_MEMORY               0xD0
#define	TEMPURATURES                 0xD1
#define GYRO_STAB_ACCEL_ANG_RATE_MAG 0xD2
#define DELTA_ANGLE_DELTA_VEL_MAG    0xD3
#define WRITE_EEPROM			     0xE4
#define READ_EEPROM				     0xE5
#define READ_FIRMWARE_VERSION        0xE9
#define READ_DEVICE_ID               0xEA
#define STOP_CONTINUOUS_MODE         0xFA
#define TEST                         0xFB

//IMU Confirm bytes
#define CONFIRM_BYTE_1 0xC1
#define CONFIRM_BYTE_2 0x29

//IMU response packet lengths (NOT transmit lengths)
#define RAW_ACCELEROMETER_GYRO_LEN       31
#define ACCELERATION_ANGULAR_RATES_LEN   31
#define DELTA_ANGLE_DELTA_VELOCITY_LEN   31
#define SET_CONTINUOUS_MODE_LEN          8
#define ORIENTATION_MATRIX_LEN           43
#define ORIENTATION_UPDATE_MATRIX_LEN    43
#define SCALED_MAGNETOMETYER_VECTOR_LEN  19
#define ACCEL_ANG_RATE_ORIENTATION_LEN   67
#define WRTIE_ACCEL_BIAS_CORRECTION_LEN  19
#define WRITE_GYRO_BIAS_CORRECTION_LEN   19
#define ACCELERATION_ANG_RATE_MAG_LEN    43
#define ACCEL_ANG_RATE_MAG_ORIENT_LEN    79
#define CAPTURE_GYRO_BIAS_LEN            19
#define EULER_ANGLES_LEN                 19
#define EULER_ANGLES_ANGULAR_RATES_LEN   31
#define DATA_TO_MEMORY_LEN               9
#define	TEMPURATURES_LEN                 15
#define GYRO_STAB_ACCEL_ANG_RATE_MAG_LEN 43
#define DELTA_ANGLE_DELTA_VEL_MAG_LEN    43
#define WRITE_EEPROM_LEN			     5
#define READ_EEPROM_LEN				     5
#define READ_FIRMWARE_VERSION_LEN        7
#define READ_DEVICE_ID_LEN               20
#define STOP_CONTINUOUS_MODE_LEN         0
#define TEST_LEN                         8

//EEPROM addresses
#define SAMPLE_RATE_ADDRESS 0xFCA2

//EEPROM timing values (for address 0xFCA2)
#define T_50_HZ 		1024
#define T_100_HZ 		512
#define T_128_HZ 		400
#define T_160_HZ 		320
#define T_200_HZ 		256
#define T_300_HZ 		170

#endif
