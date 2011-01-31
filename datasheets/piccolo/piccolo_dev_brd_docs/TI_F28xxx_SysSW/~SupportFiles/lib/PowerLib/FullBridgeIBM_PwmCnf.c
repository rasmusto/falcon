//----------------------------------------------------------------------------------
//	FILE:			FullBridgeIBM_PwmCnf.c
//
//	Description:	EPWM Interface driver config to support a Full bridge topology
//					with IBM method of modulation.  2 x EPWM modules used
//					This version supports HiResolution PWM
//
//	Version: 		1.00
//
//  Target:  		TMS320F280xx
//
//	Type: 			Device dependent
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2007
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description
//----------------------------------------------------------------------------------
//  06/30/05  | Release 1.0  		New release.
//----------------------------------------------------------------------------------

#include "GenericIncludes.h"			// Some Useful items
#include "DSP280x_EPwm.h"				// Ok to use F280xx header for F2833x
#include "DSP280x_EPWM_defines.h" 		// useful defines specific to EPWM

extern volatile struct EPWM_REGS *ePWM[];
//===============================================================================
//	FullBridgeIBM_CNF(...)  configuration function for FullBridge IBM ver. driver
//===============================================================================
//
//						SyncIn
//						   |
//				___________|___________
//				|  FullBridgeIBM_CNF  |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| duty		   EPWMnA |--> (right leg upper switch)
//			 -->| delLL  	   EPWMnB |--> (right leg Lower switch)
//			 -->| delLR    EPWM(n+1)A |--> (left leg upper switch)
//			 	| 		   EPWM(n+1)B |--> (left leg Lower switch)
//				|_____________________|
//						   |
//						   |
//						SyncOut
//
// Description:
// ------------
// PWM peripheral Driver Configuration for FB IBM ver. modulation
// Config can be targetted to any consecutive pairs of ePWM modules
// The function call is:
// 
// FullBridgeIBM_CNF(int16 n, int16 period)
//
// Function arguments defined as:
//-------------------------------
// n: 1st ePWM target module (i.e. Master)
// Period: defines the PWM period or frequency of EPWM(n) and (n+1)
// e.g. if n=2, Then EPWM2 and EPWM3 become the left and right legs
//
//---------------------------------------------------------------------------
void FullBridgeIBM_CNF(int16 n, int16 period)
{
// n = the ePWM module number, i.e. selects the target module for init.
// ePWM(n) init.  Note EPWM(n) is the Master
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD = period;					// PWM frequency = 1 / period
	(*ePWM[n]).CMPA.half.CMPA = 0;				// set duty 0% initially (Lower Left)
	(*ePWM[n]).CMPB = period/2;					// set duty 50% initially (Upper Left)
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; //used to sync EPWM(n+1) "down-stream"
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	(*ePWM[n]).CMPCTL.bit.LOADBMODE = CC_CTR_PRD;
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
	(*ePWM[n]).AQCTLB.bit.ZRO = AQ_CLEAR;
	(*ePWM[n]).AQCTLB.bit.CBU = AQ_SET; 
	
	(*ePWM[n]).DBCTL.bit.IN_MODE = DBA_ALL;		// DB delay applied only to ePWM-A
	(*ePWM[n]).DBCTL.bit.OUT_MODE = 2;			// Delay A, but not B
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HI;	// Active Hi
	(*ePWM[n]).DBRED = 0;						// Rising edge delay for ePWM-A

//	Enable HiRes option
	EALLOW;		
	(*ePWM[n]).HRCNFG.all = 0x0;	
	(*ePWM[n]).HRCNFG.bit.EDGMODE = HR_FEP;
	(*ePWM[n]).HRCNFG.bit.CTLMODE = HR_CMP;
	(*ePWM[n]).HRCNFG.bit.HRLOAD = HR_CTR_PRD;
	EDIS;	


// ePWM(n+1) init.  EPWM(n+1) is a slave
	(*ePWM[n+1]).TBCTL.bit.PRDLD = TB_IMMEDIATE;// set Immediate load
	(*ePWM[n+1]).TBPRD = period;
	(*ePWM[n+1]).CMPA.half.CMPA = 0;			// set duty 0% initially (Lower Right)
	(*ePWM[n+1]).CMPB = period/2;				// set duty 50% initially (Upper Right)
	(*ePWM[n+1]).TBPHS.half.TBPHS = period/2; 	// 180 deg phase
	(*ePWM[n+1]).TBCTR = 0;

	(*ePWM[n+1]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n+1]).TBCTL.bit.PHSEN = TB_ENABLE;
	(*ePWM[n+1]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Sync "flow through" mode
	(*ePWM[n+1]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n+1]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n+1]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	(*ePWM[n+1]).CMPCTL.bit.LOADBMODE = CC_CTR_PRD;
	(*ePWM[n+1]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n+1]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	(*ePWM[n+1]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n+1]).AQCTLA.bit.CAU = AQ_CLEAR;
	(*ePWM[n+1]).AQCTLB.bit.ZRO = AQ_CLEAR;
	(*ePWM[n+1]).AQCTLB.bit.CBU = AQ_SET; 	

	(*ePWM[n+1]).DBCTL.bit.IN_MODE = DBA_ALL;	// DB delay applied only to ePWM-A
	(*ePWM[n+1]).DBCTL.bit.OUT_MODE = 2;		// Delay A, but not B
	(*ePWM[n+1]).DBCTL.bit.POLSEL = DB_ACTV_HI;	// Active Hi
	(*ePWM[n+1]).DBRED = 0;						// Rising edge delay for ePWM-A

//	Enable HiRes option
	EALLOW;		
	(*ePWM[n+1]).HRCNFG.all = 0x0;	
	(*ePWM[n+1]).HRCNFG.bit.EDGMODE = HR_FEP;
	(*ePWM[n+1]).HRCNFG.bit.CTLMODE = HR_CMP;
	(*ePWM[n+1]).HRCNFG.bit.HRLOAD = HR_CTR_PRD;
	EDIS;	
}

