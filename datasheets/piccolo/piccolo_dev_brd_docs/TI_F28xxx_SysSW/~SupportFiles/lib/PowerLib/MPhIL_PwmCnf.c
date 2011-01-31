//=================================================================================
//	MPhILDrvCnf(n, N, period, SyncIn)  configuration function for MPhIL_DRV driver
//=================================================================================
//	FILE:			MPhIL_PwmCnf.c
//
//	Description:	peripheral Driver Config for Multiphase interleaved modulation
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
//				|	   MPHIL_DRV	  |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 	| 		     EPWM(n)A |--> (phase1)
//			 	| 		  	     	  |
//			 -->| Duty	   EPWM(n+1)A |--> (phase2)
//			 	| 		  	   :  	  |
//			 	| 		  	   : 	  |
//			 	| 		 EPWM(n+N-1)A |--> (phaseN)
//				|_____________________|
//						   |
//						   |
//						SyncOut
// Description:
// ------------
// PWM peripheral Driver Configuration for Multiphase interleaved modulation
// The function call is:
//
// MPILDrvCnf(int16 n, int16 N, int16 period, int16 SyncIn)
//
// Note: Although this module is configuted as a Master (i.e. sends sync strobe
//		 down-stream, it also can sync to up-stream strobes if needed.
//
// Where:
// n: 1st ePWM target module (i.e. Master)
// N: number of phases
// 		e.g. if n=2, N=3, then  ePWM2 (phase1), ePWM3 (phase2), ePWM4 (phase3)
// Period: defines the PWM period or frequency. See Module doc.
// SyncIn: 0 - disregard SyncIn strobe.  1 - Sync to incomming Up-stream strob.
//
//==================================================================================
#include "DSP280x_Device.h"     	// DSP280x Headerfile Include File
#include "DSP280x_EPWM_defines.h"	// useful defines for initialization

extern volatile struct EPWM_REGS *ePWM[];

void MPhIL_CNF(int16 n, int16 N, int16 period, int16 SyncIn)
{
int16	i,j;

	j=0;

	// Configure all modules as slaves initially, & set correct phase
	for (i=n; i<(n+N); i++)
	{
		(*ePWM[i]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
		(*ePWM[i]).TBPRD = period;		// set PWM operating frequency
		(*ePWM[i]).CMPA.half.CMPA = 0; 	// set duty 0% initially
		(*ePWM[i]).TBPHS.half.TBPHS = period - period*j/N;
		(*ePWM[i]).TBCTR = 0;

		(*ePWM[i]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
		(*ePWM[i]).TBCTL.bit.PHSDIR = TB_DOWN;
		(*ePWM[i]).TBCTL.bit.PHSEN = TB_ENABLE;
		(*ePWM[i]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
		(*ePWM[i]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
		(*ePWM[i]).TBCTL.bit.CLKDIV = TB_DIV1;

		(*ePWM[i]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
		(*ePWM[i]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	
		(*ePWM[i]).AQCTLA.bit.ZRO = AQ_SET;
		(*ePWM[i]).AQCTLA.bit.CAU = AQ_CLEAR;
		j++;
	}

	// Configure 1st module as Master

	if (SyncIn == 1)	(*ePWM[n]).TBCTL.bit.PHSEN = TB_ENABLE;	 	 // sync "Up-stream" 
	if (SyncIn == 0)	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;		 // Disregard SyncIn

	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream" 
	(*ePWM[n]).TBPHS.half.TBPHS = 0;			 // Reference phase = 0
}

