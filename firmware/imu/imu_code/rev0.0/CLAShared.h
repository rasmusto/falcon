#ifndef CLASHARED_H_
#define CLASHARED_H_


//  #include "IQmathLib.h"
	#include "DSP2803x_Device.h"     

	extern volatile union SENSOR_DATA sensors;
	extern float32 converted_sensors[8];
	extern Uint16 uint16_conv_sensors[8];
	extern const float32 sensor_multipliers[8];

// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them 
// .global and the main CPU can make use of them. 

	extern Uint32 Cla1Task1;
	extern Uint32 Cla1Task2;
	extern Uint32 Cla1Task3;
	extern Uint32 Cla1Task4;
	extern Uint32 Cla1Task5;
	extern Uint32 Cla1Task6;
	extern Uint32 Cla1Task7;
	extern Uint32 Cla1Task8;
	extern Uint32 Cla1Prog_Start;
	extern Uint32 Cla1T1End;
	extern Uint32 Cla1T2End;
	extern Uint32 Cla1T3End;
	extern Uint32 Cla1T4End;
	extern Uint32 Cla1T5End;
	extern Uint32 Cla1T6End;
	extern Uint32 Cla1T7End;
	extern Uint32 Cla1T8End;


#endif /*CLASHARED_H_*/
