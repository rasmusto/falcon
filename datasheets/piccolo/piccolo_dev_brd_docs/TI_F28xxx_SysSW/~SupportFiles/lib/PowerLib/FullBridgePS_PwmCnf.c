//----------------------------------------------------------------------------------
//	FILE:			FullBridgePS_PwmCnf.c
//
//	Description:	EPWM Interface driver config to support a Phase Shifted Full bridge
//					topology.  2 x EPWM modules used
//	Version: 		1.00
//
//  Target:  		TMS320F280x
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2008
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description
//----------------------------------------------------------------------------------
//  03/19/08  | Release 1.0  		New release.
//----------------------------------------------------------------------------------
//============================================================================
//	FullBridgePS_CNF(...)  configuration function for FullBridgePS_DRV macro
//============================================================================
//
//						SyncIn
//						   |
//						   |
//				___________|___________
//				|  FullBridgePS_CNF   |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| phase		   EPWMnA |--> (right leg upper switch)
//			 -->| dbLeft  	   EPWMnB |--> (right leg Lower switch)
//			 -->| dbRight  EPWM(n+1)A |--> (left leg upper switch)
//			 	| 		   EPWM(n+1)B |--> (left leg Lower switch)
//				|_____________________|
//						   |
//						   |
//						SyncOut
//
// Description:
// ------------
// PWM peripheral Driver Configuration for Full Bridge Phase shifted modulation
// Config is targetted to any consecutive pairs of ePWM modules
// The function call is:
// 
// FullBridgePS_CNF(int16 n, int16 period)
//
// Function arguments defined as:
//-------------------------------
// n: 1st ePWM target module (i.e. Master)
// Period: defines the PWM period or frequency of EPWM(n) and (n+1)
// e.g. if n=2, Then EPWM2 and EPWM3 become the left and right legs
//

#include "PeripheralHeaderIncludes.h"
//#include "GenericIncludes.h"			// Some Useful items
//#include "DSP280x_EPwm.h"				// Ok to use F280xx header for F2833x
#include "DSP280x_EPWM_defines.h" 		// useful defines specific to EPWM 

extern volatile struct EPWM_REGS *ePWM[];

//---------------------------------------------------------------------------
void FullBridgePS_CNF(int16 n, int16 period)
{
// n = the ePWM module number, i.e. selects the target module for init.
// ePWM(n) init.  Note EPWM(n) is the Master
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD = period;
	(*ePWM[n]).CMPA.half.CMPA = period/2;		// Fix duty at 50%
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; //used to sync EPWM(n+1) "down-stream"
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
	
	(*ePWM[n]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC;	// Active Hi Complimentary
	(*ePWM[n]).DBRED = 50;	// dummy value for now
	(*ePWM[n]).DBFED = 50;	// dummy value for now

// ePWM(n+1) init.  EPWM(n+1) is a slave
	(*ePWM[n+1]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n+1]).TBPRD = period;
	(*ePWM[n+1]).CMPA.half.CMPA = period/2;	// Fix duty at 50%
	(*ePWM[n+1]).TBPHS.half.TBPHS = 0; 		// zero phase initially
	(*ePWM[n+1]).TBCTR = 0;

	(*ePWM[n+1]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n+1]).TBCTL.bit.PHSEN = TB_ENABLE;
	(*ePWM[n+1]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Sync "flow through" mode
	(*ePWM[n+1]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n+1]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n+1]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n+1]).AQCTLA.bit.CAU = AQ_CLEAR;
	
	(*ePWM[n+1]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n+1]).DBCTL.bit.POLSEL = DB_ACTV_HIC;	// Active Hi Complimentary
	(*ePWM[n+1]).DBRED = 50;	// dummy value for now
	(*ePWM[n+1]).DBFED = 50;	// dummy value for now


// Configure the Trip Mechanism for the FB
	EALLOW;

	ePWM[n]->TZSEL.all = 0x0;
	ePWM[n]->TZSEL.bit.OSHT4 = TZ_ENABLE;	// Enable TZ4 -- FB Overcurrent Trip
	ePWM[n]->TZCTL.bit.TZA = TZ_FORCE_LO;	// Low on shutdown
	ePWM[n]->TZCTL.bit.TZB = TZ_FORCE_LO;	// Low on shutdown

	ePWM[n+1]->TZSEL.all = 0x0;
	ePWM[n+1]->TZSEL.bit.OSHT4 = TZ_ENABLE;	// Enable TZ4 -- FB Overcurrent Trip
	ePWM[n+1]->TZCTL.bit.TZA = TZ_FORCE_LO;	// Low on shutdown
	ePWM[n+1]->TZCTL.bit.TZB = TZ_FORCE_LO;	// Low on shutdown

	EDIS;


}
