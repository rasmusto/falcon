
#include "imu_main.h"

volatile union SENSOR_DATA sensors;
volatile union IMU_FLAGS flags;
volatile struct FCU_PACKET * fcu_tx_packet;
volatile struct FCU_PACKET sensor_tx_packet;
volatile Uint16 rx_packet[9];
volatile Uint16 tx_counter = 0;

void main(void)
{
	int i = 0;
	InitMicrocontroller();

	//initialize variables to known state
	for(i=0;i<8;i++){
		if(i%2)
			sensors.sensor[i] = 1988;
		else
			sensors.sensor[i] = 7705;
	}
	flags.bit.start_new_transmit = 1;
	flags.bit.wait_for_master = 1;
	init_fcu_packet(&sensor_tx_packet, RAW_SENSOR_DATA);
	fcu_tx_packet = &sensor_tx_packet;

	InitGpio(); //set gpio for general i/o pins, not peripheral pins.	
	InitSpi();  //sets gpio and all registers for spiA and spiB
	
	IER |= M_INT6; //turn on group 6 interrupts
	PieCtrlRegs.PIEIER6.all = 0x0F; // turn on all spi interrupts
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM //not sure what this is for

//	IMU_PWR_ON();
//	//wait for IMU_SENSE to power up
//	while(ADC_DRDY())
//		;

	//loop forever
	for(;;){
		if(flags.bit.start_new_transmit){
			SpiaRegs.SPITXBUF = 0xFA00;
			while(!SpiaRegs.SPISTS.bit.INT_FLAG){} //wait for tranfer to finish
			SpiaRegs.SPIRXBUF; //throw away data, clear INT_FLAG
			SpiaRegs.SPITXBUF = 0xCE00; //finish sending FACE
			while(!SpiaRegs.SPISTS.bit.INT_FLAG){} //wait for tranfer to finish
			SpiaRegs.SPIRXBUF; //throw away data, clear INT_FLAG
			
			SpiaRegs.SPICTL.bit.SPIINTENA = 1; //enable interrupts, the rest is interrupt driven.
			SpiaRegs.SPITXBUF = 0x0000; //start next transmission, will cause interrupt at finish.
			flags.bit.start_new_transmit = 0;
			tx_counter++;
		}
		//only modify packet when we want to make a new packet and the SPI FIFO is 
		//disabled(means we are not in the middle of a transmission)
//		if(flags.bit.make_new_fcu_packet && !SpibRegs.SPIFFTX.bit.SPIFFENA){
//			flags.bit.make_new_fcu_packet = 0;	
//			make_fcu_packet(&sensor_tx_packet);
//		}
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
