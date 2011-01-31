//=================================================================================
//	PFC2PhIL_CNF(int n, int period)    configuration function for PFC driver
//=================================================================================
//	FILE:			PFC2PhIL_PwmCnf.c
//
//	Description:	Driver Config to support a 2 phase PFC with Interleave and HiRes
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
//  08/22/07  | Release 1.0  		New release.
//----------------------------------------------------------------------------------
//
//						SyncIn
//						   |
//				___________|__________
//				|	 PFC2PhILx_DRV	  |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| Duty		   EPWM1A |--> (PFC Phase A switch)
//			 	| 		  	     	  |
//			 -->| Adj	  	   EPWM2A |--> (PFC Phase B switch)
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
// Uses 2 EPWM modules
// The function call is:
//
// PFC2PhIL_CNF(int n, int period)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
//
//==================================================================================
#include "DSP280x_Device.h"     	// DSP280x Headerfile Include File
#include "DSP280x_EPWM_defines.h"	// useful defines for initialization

extern volatile struct EPWM_REGS *ePWM[];


void PFC2PhIL_CNF(int n, int period)
{
// EPWM(n) init.  Note EPWM(n) is the Master
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD = period;
	(*ePWM[n]).CMPA.half.CMPA = 0; 	// set duty 0% initially
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.PHSDIR = TB_DOWN;
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; //sync EPWM(n+1) "down-stream"
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;

	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
	
//	Enable HiRes option
	EALLOW;		
	(*ePWM[n]).HRCNFG.all = 0x0;	
	(*ePWM[n]).HRCNFG.bit.EDGMODE = HR_FEP;
	(*ePWM[n]).HRCNFG.bit.CTLMODE = HR_CMP;
	(*ePWM[n]).HRCNFG.bit.HRLOAD = HR_CTR_PRD;
	EDIS;	


// EPWM(n+1) init.  EPWM(n+1) is a slave
	(*ePWM[n+1]).TBCTL.bit.PRDLD = TB_IMMEDIATE;// set Immediate load
	(*ePWM[n+1]).TBPRD = period;
	(*ePWM[n+1]).CMPA.half.CMPA = 0; 			// set duty 0% initially
	(*ePWM[n+1]).TBPHS.half.TBPHS = period/2;	// fix phase at 180 deg
	(*ePWM[n+1]).TBCTR = 0;

	(*ePWM[n+1]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n+1]).TBCTL.bit.PHSDIR = TB_DOWN;
	(*ePWM[n+1]).TBCTL.bit.PHSEN = TB_ENABLE;
	(*ePWM[n+1]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Sync "flow through" mode
	(*ePWM[n+1]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n+1]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n+1]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	(*ePWM[n+1]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;

	(*ePWM[n+1]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n+1]).AQCTLA.bit.CAU = AQ_CLEAR;

//	Enable HiRes option
	EALLOW;		
	(*ePWM[n+1]).HRCNFG.all = 0x0;	
	(*ePWM[n+1]).HRCNFG.bit.EDGMODE = HR_FEP;
	(*ePWM[n+1]).HRCNFG.bit.CTLMODE = HR_CMP;
	(*ePWM[n+1]).HRCNFG.bit.HRLOAD = HR_CTR_PRD;
	EDIS;	

}

