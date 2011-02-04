
#include "imu_main.h"

void main(void)
{
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
	// The shell ISR routines are found in DSP2803x_DefaultIsr.c.
	// This function is found in DSP2803x_PieVect.c.
	InitPieVectTable();
	
	InitGpio(); //set to know state, all gpio inputs pullups enabled.	
	InitSpi();  //sets gpio and all registers for spiA and spiB
	
	IER |= M_INT6; //turn on group 6 interrupts
	PieCtrlRegs.PIEIER6.all = 0x0F; // turn on all spi interrupts
	EINT;   // Enable Global interrupt INTM
//	ERTM;   // Enable Global realtime interrupt DBGM //not sure what this is for
	
	//write to spia
	SpiaRegs.SPIDAT = 0x22AA;
	for(;;){} //loop forever
}

interrupt void spia_rx_isr(void)
{
	SpiaRegs.SPIRXBUF; //read buffer to clear interrupt flag.
	SpiaRegs.SPIDAT = 0x0000; //write to spi line every time its done.
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		
}
interrupt void spia_tx_isr(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;	
}
interrupt void spib_rx_isr(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		
}
interrupt void spib_tx_isr(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;	
}
