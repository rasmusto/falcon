//=================================================================================
//	PFC2PHIL_OneEwmChCNF(int n, int period)    configuration function for PFC driver
//=================================================================================
//	FILE:			PFC2PhIL_OneEwmChCnf.c
//
//	Description:	Driver Config to support a 2 phase Interleaved PFC
//
//	Version: 		1.00
//  Target:  		TMS320F280x 
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2008
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description
//----------------------------------------------------------------------------------
//  03/12/08  | Release 1.0  		New release.
//----------------------------------------------------------------------------------
//
//						SyncIn
//						   |
//				___________|__________
//				|	 PFC2PhILx_DRV	  |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| Duty		   EPWM1A |--> (PFC Phase A switch)
//			 	| 		  	     	  |
//			 -->| Adj	  	   EPWM1B |--> (PFC Phase B switch)
//				|_____________________|
//						   |
//						   |
//						SyncOut
//
// Description:
// ------------
// PWM peripheral Driver Configuration func for the following assembly macro drivers:
//	1) PFC2PhILA_DRV -	with Duty balance Adjustment but Non HiRes 
//	2) PFC2PhILHR_DRV -	with HiRes, but no Duty balance Adjustment
//
// Uses 1 EPWM module
// The function call is:
//
// PFC2PHIL_OneEwmChCNF(int n, int period)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
//
//==================================================================================
#include "PeripheralHeaderIncludes.h"
//#include "GenericIncludes.h"			// Some Useful items
//#include "DSP280x_EPwm.h"				// Ok to use F280xx header for F2833x
#include "DSP280x_EPWM_defines.h" 		// useful defines specific to EPWM 

extern volatile struct EPWM_REGS *ePWM[];


void PFC2PHIL_OneEPwmChCNF(int16 nChannel, int16 nPeriod)
{
	ePWM[nChannel]->TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	ePWM[nChannel]->TBPRD = ((nPeriod>>1)-1);
	ePWM[nChannel]->TBPHS.half.TBPHS = 0;
	ePWM[nChannel]->TBCTR = 0;

	ePWM[nChannel]->TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	ePWM[nChannel]->TBCTL.bit.PHSEN = TB_DISABLE;
	ePWM[nChannel]->TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; //sync EPWM(n+1) "down-stream"
	ePWM[nChannel]->TBCTL.bit.HSPCLKDIV = TB_DIV1;
	ePWM[nChannel]->TBCTL.bit.CLKDIV = TB_DIV1;

	ePWM[nChannel]->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	ePWM[nChannel]->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	ePWM[nChannel]->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	ePWM[nChannel]->CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	ePWM[nChannel]->AQCTLA.bit.CAU = AQ_CLEAR;
	ePWM[nChannel]->AQCTLA.bit.CAD = AQ_SET;

	ePWM[nChannel]->AQCTLB.bit.CBU = AQ_SET;
	ePWM[nChannel]->AQCTLB.bit.CBD = AQ_CLEAR;

// Configure the Trip Mechanism for the PFC
	EALLOW;

	ePWM[nChannel]->TZSEL.all = 0x0;
	ePWM[nChannel]->TZSEL.bit.OSHT3 = TZ_ENABLE;	// Enable TZ3 -- PFC Overvoltage Trip
	ePWM[nChannel]->TZSEL.bit.OSHT2 = TZ_ENABLE;	// Enable TZ2 -- PFC Overcurrent Trip
	ePWM[nChannel]->TZCTL.bit.TZA = TZ_FORCE_LO;	// Low on shutdown
	ePWM[nChannel]->TZCTL.bit.TZB = TZ_FORCE_LO;	// Low on shutdown

	EDIS;


}

