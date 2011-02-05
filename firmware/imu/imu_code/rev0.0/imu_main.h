#ifndef IMU_MAIN_H_
#define IMU_MAIN_H_

#include "DSP28x_Project.h"

//function prototypes
//void ImuPwrOn(void);
//void ImuPwrOff(void);
#define IMU_PWR_ON() GpioDataRegs.GPBSET.bit.GPIO34 = 1; GpioDataRegs.GPASET.bit.GPIO21 = 1
#define IMU_PWR_OFF() GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; GpioDataRegs.GPACLEAR.bit.GPIO21 = 1

//spi defines
#define SPIA_CHAR_LNGTH_MSK 0x04
#define SPIB_CHAR_LNGTH_MSK 0x04

#endif /*IMU_MAIN_H_*/
