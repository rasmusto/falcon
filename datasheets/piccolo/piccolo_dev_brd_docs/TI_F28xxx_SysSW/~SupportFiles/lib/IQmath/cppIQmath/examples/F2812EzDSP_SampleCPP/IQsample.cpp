//############################################################################
//
// FILE:    IQsample.cpp
//
// TITLE:   IQ Math Sample Program In C++ (for V1.4+ of library)
// 
// TARGET:  F2812 EzDSP
//
//############################################################################

// Select the global Q value to use:
#define	GLOBAL_Q	24
long GlobalQ = GLOBAL_Q;      // Used for GEL & Graph Debug.

// Include The Following Definition Files:
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "IQmathLib.h"
}
#include "IQmathCPP.h"

// Specify the data logging size:
#define	DATA_LOG_SIZE	256

// Define constants used:
#define	PI2				1.570796327
#define	PI				3.141592654
#define	STEP_X_SIZE		0.314159265
#define	STEP_Y_SIZE		0.314159265

// Allocate data log buffers:
struct	DATA_LOG_C {
	iq   Xwaveform[DATA_LOG_SIZE];
	iq   Ywaveform[DATA_LOG_SIZE];
	long  Phase[DATA_LOG_SIZE];
	iq   Mag[DATA_LOG_SIZE];
} Dlog;	

// Define waveform global variables:
struct	STEP {
	iq   Xsize;
	iq   Ysize;
	iq   Yoffset;
	iq   X;
	iq   Y;
	iq   GainX;
	iq   GainY;
	iq   FreqX;
	iq   FreqY;
} Step;
	
//----------------------------------------------------------------------------			
// Main code:
//----------------------------------------------------------------------------			
int main(void)
{
	unsigned int  i;

	iq	tempX, tempY, tempP, tempM, tempMmax;
	char buffer[20];

	int *WatchdogWDCR = (int *) 0x7029;

    // Disable the watchdog:
    asm(" EALLOW ");
    *WatchdogWDCR = 0x0068;
    asm(" EDIS ");	
			
	Step.Xsize = IQ(STEP_X_SIZE);
	Step.Ysize = IQ(STEP_Y_SIZE);
	Step.Yoffset = 0;
	Step.X = 0;
	Step.Y = Step.Yoffset;
	
	for(i=0; i < DATA_LOG_SIZE; i++)
		{
		Dlog.Xwaveform[i] = 0;
		Dlog.Ywaveform[i] = 0;
		Dlog.Phase[i]     = 0;
		Dlog.Mag[i]       = 0;
		}		
	
	// Get user input for gain for X and Y waveform:
	printf("\nEnter waveform X gain (default = 1.0)= ");
	gets(buffer);
	Step.GainX = atoIQ(buffer);
	if( Step.GainX == 0 )
		Step.GainX = IQ(1.0);
	printf("\nEnter waveform X freq (default = 1.0)= ");
	gets(buffer);
	Step.FreqX = atoIQ(buffer);
	if( Step.FreqX == 0 )
		Step.FreqX = IQ(1.0);

	printf("\nEnter waveform Y gain (default = 1.0)= ");
	gets(buffer);
	Step.GainY = atoIQ(buffer);
	if( Step.GainY == 0 )
		Step.GainY = IQ(1.0);
	printf("\nEnter waveform Y freq (default = 1.0)= ");
	gets(buffer);
	Step.FreqY = atoIQ(buffer);
	if( Step.FreqY == 0 )
		Step.FreqY = IQ(1.0);

	// Calculate maximum magnitude value:
	tempMmax = IQmag(Step.GainX, Step.GainY);

	for(i=0; i < DATA_LOG_SIZE; i++)
		{
		// Calculate waveforms:
		Step.X = Step.X + Step.Xsize * Step.FreqX;
		if( Step.X >  IQ(2*PI) )
			Step.X -= IQ(2*PI);

		Step.Y = Step.Y + Step.Ysize * Step.FreqY;
		if( Step.Y >  IQ(2*PI) )
			Step.Y -= IQ(2*PI);
								
		Dlog.Xwaveform[i] = tempX = IQsin(Step.X) * Step.GainX;
		Dlog.Ywaveform[i] = tempY = IQabs(IQsin(Step.Y)) * Step.GainY;
			
		// Calculate normalized magnitude:
		//
		// Mag = sqrt(X^2 + Y^2)/sqrt(GainX^2 + GainY^2);
		tempM = IQmag(tempX, tempY);
		Dlog.Mag[i] = tempM / tempMmax;
			
		// Calculate normalized phase:
		//
		// Phase = (long) (atan2PU(X,Y) * 360);
		tempP = IQatan2PU(tempY,tempX);
		Dlog.Phase[i] = IQmpyI32int(tempP, 360);							
		}
}

//############################################################################
// No more.
//############################################################################
