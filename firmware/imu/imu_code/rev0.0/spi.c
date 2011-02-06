// TI File $Revision: /main/2 $
// Checkin $Date: February 24, 2009   15:54:34 $
//###########################################################################
//
// FILE:   DSP2803x_Spi.c
//
// TITLE:  DSP2803x SPI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: 2803x C/C++ Header Files V1.21 $
// $Release Date: December 1, 2009 $
//###########################################################################

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File
#include "imu_main.h"

void InitSpiARegs(void);
void InitSpiBRegs(void);

//---------------------------------------------------------------------------
// InitSPI:
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void InitSpi(void)
{
	InitSpiGpio(); //set gpio for spia and spib
	InitSpiARegs();
	InitSpiBRegs();
}

void InitSpiARegs(void)
{
	
	//setup SPI_A  (IMU_SENSE SPI, master)
	SpiaRegs.SPICCR.bit.SPISWRESET = 0; //changing configuration
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 1; //sclk high when idle, input read on rising
	SpiaRegs.SPICCR.all |= SPIA_CHAR_LNGTH_MSK; //set data length
	
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1; //master
	SpiaRegs.SPICTL.bit.TALK = 0; //the ADC is read only, so i dont need to talk
	SpiaRegs.SPICTL.bit.SPIINTENA = 1; //enbable interrupts
	
	SpiaRegs.SPIBRR = 0x10; //BRR of 16 is ~1.765MHz.
	
	SpibRegs.SPIPRI.bit.SOFT = 1;
	SpibRegs.SPIPRI.bit.FREE = 0;
	
	SpiaRegs.SPIFFTX.bit.SPIFFENA = 1; //use FIFO on TX buffer
	SpiaRegs.SPIFFRX.all = 0x0024; //enable RX FIFO interrupt when 4 words are in FIFO.
	
	//reset spi 
	SpiaRegs.SPICCR.bit.SPISWRESET = 1; //everything is configured, begin
}
void InitSpiBRegs(void)
{
	//setup SPI_B  (FCU SPI, slave)
	SpibRegs.SPICCR.bit.SPISWRESET = 0;//changing configuration...
	SpibRegs.SPICCR.bit.CLKPOLARITY = 0; //sclk low when idle.
	SpibRegs.SPICCR.all |= SPIB_CHAR_LNGTH_MSK; //set data length
	
	SpibRegs.SPICTL.bit.MASTER_SLAVE = 0; //slave
	SpibRegs.SPICTL.bit.TALK = 1; //enable transmit to FCU
	SpibRegs.SPICTL.bit.SPIINTENA = 1; //enable interrupts

	SpibRegs.SPIBRR = 0x0E;	//BRR of 14 is 2MHz.
	
	//allow some control when running with emulator, will stop transmissions when halted
	SpibRegs.SPIPRI.bit.SOFT = 1;
	SpibRegs.SPIPRI.bit.FREE = 0;
	
	//reset spi 
	SpibRegs.SPICCR.bit.SPISWRESET = 1; //everything is configured, begin
}
//---------------------------------------------------------------------------
// Example: InitSpiGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SPI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each SPI peripheral
// Only one GPIO pin should be enabled for SPISOMO operation.
// Only one GPIO pin should be enabled for SPISOMI operation.
// Only one GPIO pin should be enabled for SPICLK  operation.
// Only one GPIO pin should be enabled for SPISTE  operation.
// Comment out other unwanted lines.

void InitSpiGpio()
{
   InitSpiaGpio();
   InitSpibGpio();
}

void InitSpiaGpio()
{

   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

/* Configure SPI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    EDIS;
}

void InitSpibGpio()
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.
// This will enable the pullups for the specified pins.
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;     // Enable pull-up on GPIO13 (SPISOMIB)
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;     // Enable pull-up on GPIO14 (SPICLKB)
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;     // Enable pull-up on GPIO15 (SPISTEB)
	GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;     // Enable pull-up on GPIO24 (SPISIMOB)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;   // Asynch input GPIO13 (SPISOMIB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;   // Asynch input GPIO14 (SPICLKB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;   // Asynch input GPIO15 (SPISTEB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3;   // Asynch input GPIO24 (SPISIMOB)
	
/* Configure SPI-B pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3;    // Configure GPIO13 as SPISOMIB
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;    // Configure GPIO14 as SPICLKB
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3;    // Configure GPIO15 as SPISTEB
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;    // Configure GPIO24 as SPISIMOB
    
    EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
