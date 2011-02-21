
#include "imu_main.h"

volatile union SENSOR_DATA sensors;
volatile union IMU_FLAGS flags;
volatile struct FCU_PACKET * fcu_tx_packet;
volatile struct FCU_PACKET sensor_tx_packet;

void main(void)
{
	int i = 0;
	InitMicrocontroller();

	//initialize variables to known state
	for(i=0;i<8;i++){
		sensors.sensor[i] = i;
	}
	flags.all = 0x0000; //clear flags
	flags.bit.want_new_adc_data = 1;
	flags.bit.wait_for_master = 1;
	
	init_fcu_packet(&sensor_tx_packet, RAW_SENSOR_DATA);
	fcu_tx_packet = &sensor_tx_packet;

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
		//only modify packet when we want to make a new packet and we are not tx with master
		if(flags.bit.make_new_fcu_packet && flags.bit.wait_for_master){
			flags.bit.make_new_fcu_packet = 0;	
			make_fcu_packet(&sensor_tx_packet);
		}
	}
}

void InitMicrocontroller(void)
{
	//copy InitFlash() to ram
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();
	InitSysCtrl();	//calibrate ADC, enable peripheral clocks, etc.
	DINT; // Disable CPU interrupts
   	// Initialize PIE control registers to all PIE interrupts disabled and flags clear
   	InitPieCtrl();
	// Disable CPU interrupts and clear all CPU interrupt flags:
   	IER = 0x0000;
   	IFR = 0x0000;
   	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
   	InitPieVectTable();
}
