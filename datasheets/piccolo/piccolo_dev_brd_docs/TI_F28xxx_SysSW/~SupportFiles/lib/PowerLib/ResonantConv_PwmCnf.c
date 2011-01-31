//----------------------------------------------------------------------------------
//	FILE:			ResonantConv_PwmCnf.c
//
//	Description:	EPWM Interface driver Config to support a single (A output) 
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
//  11/08  | Release 1.0  		
//----------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"
#include "DSP280x_EPWM_defines.h" 		// useful defines specific to EPWM

extern volatile struct EPWM_REGS *ePWM[];

//============================================================================
//	ResonantConv_CNF  configuration function for ResonantConv_DRV asm macro
//============================================================================
//						SyncIn
//						   |
//				___________|___________
//				|	 ResonantConv_CNF |
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
// PWM peripheral Driver Configuration for ResonantConv_DRV assembly macro
// Has 1 independent ResonantConv channel with configurable Period (Frequency)
// The function call is:
//
// ResonantConv_CNF(int16 n, int16 period, int16 deadband)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
// deadband = PWM deadband
//---------------------------------------------------------------------------
void ResonantConv_CNF(int16 n, int16 period, int16 deadband)
{

	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// Set immediate load
	(*ePWM[n]).TBPRD = period;					// PWM frequency = 1 / period
	(*ePWM[n]).CMPA.half.CMPA = period/2;		// Set duty as initial period (Lower Left)
	(*ePWM[n]).CMPB = period/4;						// Set duty as initial period/2 (Upper Left)
	(*ePWM[n]).TBPHS.half.TBPHS = 0;			// Set as master, phase =0
	(*ePWM[n]).TBCTR = 0;						// Time base counter =0

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count-up mode: used for asymmetric PWM
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;	// Disable phase loading
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;// Used to sync EPWM(n+1) "down-stream"
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;	// Set the clock rate
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;		// Set the clock rate

	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD; // Load on CTR=PRD
	(*ePWM[n]).CMPCTL.bit.LOADBMODE = CC_CTR_PRD; // Load on CTR=PRD
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;  // Shadow mode. Operates as a double buffer.
	(*ePWM[n]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;  // Shadow mode. Operates as a double buffer.

	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;			  // Set PWM1A on Zero
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;		  // Clear PWM1A on event A, up count
	(*ePWM[n]).AQCTLB.bit.CAU = AQ_SET; 		  // Set PWM1B on event B, up count
	(*ePWM[n]).AQCTLB.bit.PRD = AQ_CLEAR;		  // Clear PWM1B on PRD

	(*ePWM[n]).DBCTL.bit.IN_MODE = DBA_ALL;          // EPWM1A is the source for both falling-edge and rising-edge delay		
	(*ePWM[n]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // Both the falling-edge dealy (FED) and rising-edge delay (RED) are applied to the input signals	
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC; 		 // Active High Complementary (AHC) 	
	(*ePWM[n]).DBRED = deadband;					 // Set DeadBand time for rising edge
	(*ePWM[n]).DBFED = deadband;					 // Set DeadBand time for falling edge


//	Configure TZ1 for short cct protection


   EALLOW;
   (*ePWM[n]).TZSEL.bit.OSHT1 = 1;	// one-shot source
   (*ePWM[n]).TZCTL.bit.TZA = TZ_FORCE_LO;	// set EPWM1A to low at fault instant 
   (*ePWM[n]).TZCTL.bit.TZB = TZ_FORCE_LO;	// set EPWM1B to low at fault instant 
   (*ePWM[n]).TZEINT.bit.OST = 1; 	// Enable TZ interrupt
   EDIS;

//	Enable HiRes option
	EALLOW;		
	(*ePWM[n+1]).HRCNFG.all = 0x0;	
	(*ePWM[n+1]).HRCNFG.bit.EDGMODE = HR_FEP;
	(*ePWM[n+1]).HRCNFG.bit.CTLMODE = HR_CMP;
	(*ePWM[n+1]).HRCNFG.bit.HRLOAD = HR_CTR_PRD;
	EDIS;	

}



