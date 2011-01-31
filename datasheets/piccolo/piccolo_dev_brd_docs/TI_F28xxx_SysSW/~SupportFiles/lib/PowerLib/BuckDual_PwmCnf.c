//=================================================================================
//	BuckDual_CNF(...)    configuration function for BuckDual_DRV asm macro
//=================================================================================
//	FILE:			BuckDual_PwmCnf.c
//
//	Description:	EPWM Interface driver Config to support a Dual
//					(A & B output)	Buck topology.
//
//	Version: 		1.00
//  Target:  		TMS320F280x 
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2007
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description
//----------------------------------------------------------------------------------
//  06/30/05  | Release 1.0  		New release.
//----------------------------------------------------------------------------------
//
//						SyncIn
//						   |
//				___________|___________
//				|	BuckDual_CNF      |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| InA 	   	   EPWMnA |--> regular output A
//			 	|			 	      |
//			 -->| InB	  	   EPWMnB |--> regular output B
//				|_____________________|
//						   |
//						   |
//						SyncOut
//
// Description:
// ------------
// PWM peripheral Driver Configuration for BuckDual_DRV assembly macro
// Has 2 independent Buck channels with same configurable Period (Frequency)
// The function call is:
//
// BuckDual_CNF(int16 n, int16 period, int16 mode, int16 phase)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
// mode =	Master/Slave mode, e.g. mode=1 for master, mode=0 for slave
// phase =	phase offset from upstream master in Sysclks,
//			applicable only if mode=0, i.e. slave
//
//==================================================================================
#include "DSP280x_Device.h"     	// DSP280x Headerfile Include File
#include "DSP280x_EPWM_defines.h"	// useful defines for initialization

extern volatile struct EPWM_REGS *ePWM[];


void BuckDual_CNF(int16 n, int16 period, int16 mode, int16 phase)
{
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD = period;					// PWM frequency = 1 / period
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).CMPA.half.CMPA = 0;				// set duty 0% initially
	(*ePWM[n]).CMPB = 0;						// set duty 0% initially
	(*ePWM[n]).TBCTR = 0;
	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	if(mode == 1) // config as a Master
	{
		(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
		(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream" 
	}

	if(mode == 0) // config as a Slave
	{
		(*ePWM[n]).TBCTL.bit.PHSEN = TB_ENABLE;
		(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
		(*ePWM[n]).TBPHS.half.TBPHS = (period - phase);	// set phase = 360 - lag
	}

	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	(*ePWM[n]).CMPCTL.bit.LOADBMODE = CC_CTR_PRD;
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	
	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
	(*ePWM[n]).AQCTLB.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLB.bit.CBU = AQ_CLEAR; 
}



