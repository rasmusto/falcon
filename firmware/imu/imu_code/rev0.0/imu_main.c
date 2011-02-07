
#include "imu_main.h"

volatile union SENSOR_DATA sensors;
volatile union IMU_FLAGS flags;

void main(void)
{
	int i = 0;
	//copy InitFlash() to ram
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();

	for(i=0;i<8;i++){
		sensors.sensor[i] = 0;
	}
	flags.all = 0x0001; //set 'want_new_adc_data' flag, clear the rest
	
	
	InitSysCtrl();	//calibrate ADC, enable peripheral clocks, etc.
	// Disable CPU interrupts
	DINT;

	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags
	// are cleared.
	// This function is found in the DSP2803x_PieCtrl.c file.
   	InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
   	IER = 0x0000;
   	IFR = 0x0000;

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table.
	// The shell ISR routines are found in ISR.c.
	// This function is found in DSP2803x_PieVect.c.
	InitPieVectTable();
	
	InitGpio(); //set gpio for general i/o pins, not peripheral pins.	
	InitSpi();  //sets gpio and all registers for spiA and spiB
	
	IER |= M_INT6; //turn on group 6 interrupts
	PieCtrlRegs.PIEIER6.all = 0x0F; // turn on all spi interrupts
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM //not sure what this is for
	
	IMU_PWR_ON();
	//wait for IMU_SENSE to power up
	while(ADC_DRDY())
		;
	//loop forever
	for(;;){
		if(flags.bit.want_new_adc_data && ADC_DRDY()){
			//load SPI TX FIFO to get ADC data.
			SpiaRegs.SPITXBUF = 0x0000;	
			SpiaRegs.SPITXBUF = 0x0000;	
			SpiaRegs.SPITXBUF = 0x0000;	
			SpiaRegs.SPITXBUF = 0x0000;	
		}
	}
}
