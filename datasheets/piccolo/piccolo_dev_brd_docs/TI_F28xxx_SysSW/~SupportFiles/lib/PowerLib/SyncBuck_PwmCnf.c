//=================================================================================
//	SyncBuckDrvCnf(n, period, RED, FED, mode, phase)
//=================================================================================
//	FILE:			SyncBuck_PwmCnf.c
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
//				|	 SYNCBUCK_DRV     |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| In 	   	   EPWMnA |--> output A
//			 	|			 	      |
//			 	|			   EPWMnB |--> output B
//				|_____________________|
//						   |
//						   |
//						SyncOut
//
// Description:
// ------------
// PWM peripheral Driver Configuration for SyncBuck converter modulation
// Has 1 independent Buck channel with configurable Period (Frequency)
// The function call is:
//
// SyncBuckDrvCnf(int16 n, int16 period, int16 RED, int16 FED, int16 mode, int16 phase)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module,  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
// RED =	Rising edge dead-band delay (RED x 10nS)
// FED =	Falling edge dead-band delay (FED x 10nS)
// mode =	Master/Slave mode, e.g. mode=1 for master, mode=0 for slave
// phase =	phase offset from upstream master in Sysclks,
//			applicable only if mode=0, i.e. slave
//
//==================================================================================
#include "DSP280x_Device.h"     	// DSP280x Headerfile Include File
#include "DSP280x_EPWM_defines.h"	// useful defines for initialization

extern volatile struct EPWM_REGS *ePWM[];

void SyncBuckDrvCnf(int16 n, int16 period, int16 RED, int16 FED, int16 mode, int16 phase)
{
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD = period;					// PWM frequency = 1 / period
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).CMPA.half.CMPA = 100;				// set duty 0% initially
	(*ePWM[n]).CMPB = 100;						// set duty 0% initially
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
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	
	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;

	// Dead-band config
	(*ePWM[n]).DBCTL.bit.IN_MODE = DBA_ALL;		// DB delay applied only to ePWM-A
	(*ePWM[n]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC;	// Active Hi Complimentary
	(*ePWM[n]).DBRED = RED;
	(*ePWM[n]).DBFED = FED; 

}

