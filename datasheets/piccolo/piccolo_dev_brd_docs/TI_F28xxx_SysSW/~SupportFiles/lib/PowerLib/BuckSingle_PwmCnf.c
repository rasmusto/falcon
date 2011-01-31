//----------------------------------------------------------------------------------
//	FILE:			BuckSingle_PwmCnf.c
//
//	Description:	EPWM Interface driver Config to support a single (A output) Buck
//					Note: HiRes feature enabled, even though .asm driver may not use.
//
//	Version: 		1.0
//
//  Target:  		TMS320F280xx or F2833x
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2007
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description
//----------------------------------------------------------------------------------
//  08/01/07  | Release 1.0  		New release.
//----------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"
#include "DSP280x_EPWM_defines.h" 		// useful defines specific to EPWM

extern volatile struct EPWM_REGS *ePWM[];

//============================================================================
//	BuckSingle_CNF  configuration function for BuckSingle_DRV asm macro
//============================================================================
//						SyncIn
//						   |
//				___________|___________
//				|	 BuckSingle_CNF   |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| InA 	   	   EPWMnA |--> regular output A
//			 	|			 	      |
//				|_____________________|
//						   |
//						   |
//						SyncOut
//
// Description:
// ------------
// PWM peripheral Driver Configuration for BuckSingle_DRV assembly macro
// Has 1 independent Buck channel with configurable Period (Frequency)
// The function call is:
//
// BuckSingle_CNF(int16 n, int16 period, int16 mode, int16 phase)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
// mode =	Master/Slave mode, e.g. mode=1 for master, mode=0 for slave
// phase =	phase offset from upstream master in Sysclks,
//			applicable only if mode=0, i.e. slave
//
//---------------------------------------------------------------------------
void BuckSingle_CNF(int16 n, int16 period, int16 mode, int16 phase)
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

	if(mode == 0) // config as a Slave (Note: Phase+2 value used to compensate for logic delay)
	{
		(*ePWM[n]).TBCTL.bit.PHSEN = TB_ENABLE;
		(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;

		if( 0 <= phase <= 2)	(*ePWM[n]).TBPHS.half.TBPHS = (2-phase);
		if( phase > 2 )			(*ePWM[n]).TBPHS.half.TBPHS = (period-phase+2);
	}

	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	
	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;

	(*ePWM[n]).AQCTLB.bit.ZRO = AQ_NO_ACTION;
	(*ePWM[n]).AQCTLB.bit.CAU = AQ_NO_ACTION;
	(*ePWM[n]).AQCTLB.bit.PRD = AQ_NO_ACTION;

//	Enable HiRes option
	EALLOW;		
	(*ePWM[n]).HRCNFG.all = 0x0;	
	(*ePWM[n]).HRCNFG.bit.EDGMODE = HR_FEP;
	(*ePWM[n]).HRCNFG.bit.CTLMODE = HR_CMP;
	(*ePWM[n]).HRCNFG.bit.HRLOAD = HR_CTR_PRD;
	//(*ePWM[n]).HRCNFG.bit.HRLOAD = HR_CTR_ZERO;
	EDIS;	

}



