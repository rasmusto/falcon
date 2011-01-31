//----------------------------------------------------------------------------------
//	FILE:			TimeBaseGen_PwmCnf.C
//
//	Description:	Contains the time base intialization for the PWM driver.
//					converter driver
//
//	Version: 		1.00
//
//  Target:  		TMS320F280x 
//
//	Type: 			Device dependent
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2005                                				
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description
//----------------------------------------------------------------------------------
//  06/30/05  | Release 1.0  		New release.
//----------------------------------------------------------------------------------

#include "DSP280x_Device.h"     	// DSP280x Headerfile Include File
#include "DSP280x_EPWM_defines.h"	// useful defines for initialization

extern volatile struct EPWM_REGS *ePWM[];


//============================================================================
//	TimeBasePeriodCnf - Simple Timebase only config for ePWMn module
//============================================================================
//
// Description:
// ------------
// Init ePWMn to run at a given period.  Useful for slaving ISRs.
//
// Revision History:
//---------------------------------------------------------------------------
// Date		| Author	| Description
//---------------------------------------------------------------------------
// 11 Feb05	| DAF		| Original
// __________________________________________________________________________

void TimeBaseGenCNF(int16 n, int16 period)
{
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD = period;					// PWM frequency = 1 / period
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;		
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;
}

