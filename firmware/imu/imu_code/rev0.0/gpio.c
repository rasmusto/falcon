//###########################################################################
//
// FILE:	gpio.c
//
// TITLE:	General Purpose I/O Initialization & Support Functions.
//
//###########################################################################

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

//---------------------------------------------------------------------------
// InitGpio:
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known state. Pins for peripherals are 
// configured in the respective peripherals Init function. 
//
void InitGpio(void)
{
   	EALLOW;

//34 is PWR_EN for control of power on IMU_SENSE //output
//20 is ADC_DRDY //input //pu on //default
//21 is ADC_SYNCH //output //keep high for normal operation
//22 is MAG_SR	//output


   	// Each GPIO pin can be:
   	// a) a GPIO input/output
   	// b) peripheral function 1
   	// c) peripheral function 2
   	// d) peripheral function 3
   	// By default, all are GPIO Inputs
   	GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
   	GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
   	GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO44
   	GpioCtrlRegs.AIOMUX1.all = 0x0000;     // Dig.IO funct. applies to AIO2,4,6,10,12,14
   
   	// Each input can have different qualification
   	// a) input synchronized to SYSCLKOUT
   	// b) input qualified by a sampling window
   	// c) input sent asynchronously (valid for peripheral inputs only)
   	GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT
   	GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
   	GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO44 Synch to SYSCLKOUT

   	// Pull-ups can be enabled or disabled.
   	GpioCtrlRegs.GPAPUD.all = 0x00600000;      // Pullup's disabled on outputs. Pullup's enabled for inputs.
   	GpioCtrlRegs.GPBPUD.all = 0x00000004;      // Pullup's disabled on outputs. Pullup's enabled for inputs.
      
   	GpioDataRegs.GPACLEAR.all = 0x00600000; 	//ADC_SYNC and MAG_SR outputs set to 0.
   	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;	//clear PWR_EN output.
	
	//set inputs/outputs
   	GpioCtrlRegs.GPADIR.all = 0x00600000;  // GPIO21 is ADC_SYNC output, GPIO22 is MAG_SR output, rest GPIO0-GPIO31 inputs
   	GpioCtrlRegs.GPBDIR.all = 0x00000004;      //GPIO34 is PWR_EN output to IMU_SENSE board. rest GPIO32-GPIO44 are inputs
   	GpioCtrlRegs.AIODIR.all = 0x0000;      // AIO2,4,6,19,12,14 are digital inputs


   	EDIS;

}
//USING MACROS INSTEAD, THEY ARE IN imu_main.h
//void ImuPwrOn(void)
//{
//	GpioDataRegs.GPBSET.bit.GPIO34 = 1;	//PWR_EN high
//	GpioDataRegs.GPASET.bit.GPIO21 = 1; //ADC_SYNC high
//}
//void ImuPwrOff(void)
//{
//	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;	//PWR_EN high
//	GpioDataRegs.GPACLEAR.bit.GPIO21 = 1; //ADC_SYNC high
//}
//===========================================================================
// End of file.
//===========================================================================
