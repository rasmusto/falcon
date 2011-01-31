//=================================================================================
//	SyncBuckBoostCNF(n, period, RED, FED, mode)
//=================================================================================
//	FILE:			SyncBuckBoost_PwmCnf.c
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
//				___________|___________
//				|  SYNCBUCKBOOST_DRV  |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| In 	   	   EPWMnA |--> output H1
//			 	|			   EPWMnB |--> output L1
//			 	|		   EPWM(n+1)A |--> output H2
//			 	|		   EPWM(n+1)B |--> output L2
//				|_____________________|
//						   |
//
//	NOTE:
//	This driver is based on EPWM(n+1)A signal controlling Q4 gate and
//	EPWM(n+1)B signal controlling Q3 gate. As per PCB D-Amp4ChSBB Rel-1. 
//
// Description:
// ------------
// PWM peripheral Driver Configuration for SyncBuckBoost converter modulation
// Has 1 independent BuckBoost channel with configurable Period (Frequency)
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
// phase =	phase offset from upstream master in Sysclks, (NOT USED YET)
//			applicable only if mode=0, i.e. slave
//
//=================================================================================
#include "PeripheralHeaderIncludesIndus.h"	// Include all Peripheral Headers
//#include "DSP280x_Device.h"     	// DSP280x Headerfile Include File
#include "DSP280x_EPWM_defines.h"	// useful defines for initialization

extern volatile struct EPWM_REGS *ePWM[];

void SyncBuckBoostCNF(int16 n, int16 period, int16 RED, int16 FED, int16 mode)
{
	//--------------------------------------
	// High side 1 and Low side 1 control
	//--------------------------------------
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_SHADOW;		// set Shadow load
//	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD = (period-1);				// PWM frequency = 1 / (period-1)
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
//		(*ePWM[n]).TBPHS.half.TBPHS = (period - phase);	// set phase = 360 - lag
	}

	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	
	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;

	// Dead-band config
	(*ePWM[n]).DBCTL.bit.IN_MODE = DBA_ALL;	
	(*ePWM[n]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC;	// Active Hi Complimentary
	(*ePWM[n]).DBRED = RED;
	(*ePWM[n]).DBFED = FED; 

	//--------------------------------------
	// High Side 2 and Low Side 2 control
	//--------------------------------------
	(*ePWM[n+1]).TBCTL.bit.PRDLD = TB_SHADOW;		// set Shadow load
//	(*ePWM[n+1]).TBCTL.bit.PRDLD = TB_IMMEDIATE;// set Immediate load
	(*ePWM[n+1]).TBPRD = (period-1);				// PWM frequency = 1 / (period-1)
	(*ePWM[n+1]).TBPHS.half.TBPHS = 0;
	(*ePWM[n+1]).CMPA.half.CMPA = 0;			// set duty 0% initially
	(*ePWM[n+1]).CMPB = 0;						// set duty 0% initially
	(*ePWM[n+1]).TBCTR = 0;
	(*ePWM[n+1]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n+1]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n+1]).TBCTL.bit.CLKDIV = TB_DIV1;

//	if(mode == 1) // config as a Master
//	{
//		(*ePWM[n+1]).TBCTL.bit.PHSEN = TB_DISABLE;
//		(*ePWM[n+1]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream" 
//	}

//	if(mode == 0) // config as a Slave
//	{
		(*ePWM[n+1]).TBCTL.bit.PHSEN = TB_ENABLE;
		(*ePWM[n+1]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
		(*ePWM[n+1]).TBPHS.half.TBPHS = 2;			// set phase = 0 deg (2 clk align)
//	}

	(*ePWM[n+1]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	(*ePWM[n+1]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	
//	Use this option as per above NOTE:
	(*ePWM[n+1]).AQCTLA.bit.ZRO = AQ_CLEAR;
	(*ePWM[n+1]).AQCTLA.bit.CAU = AQ_SET;

	// Dead-band config
	(*ePWM[n+1]).DBCTL.bit.IN_MODE = DBA_ALL;	
	(*ePWM[n+1]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n+1]).DBCTL.bit.POLSEL = DB_ACTV_HIC;	// Active Hi Complimentary
	(*ePWM[n+1]).DBRED = FED;
	(*ePWM[n+1]).DBFED = RED; 


//	Use this option when A & B connections reversed (i.e. as it should be)
//	(*ePWM[n+1]).AQCTLA.bit.ZRO = AQ_SET;
//	(*ePWM[n+1]).AQCTLA.bit.CAU = AQ_CLEAR;

	// Dead-band config
//	(*ePWM[n+1]).DBCTL.bit.IN_MODE = DBA_ALL;	
//	(*ePWM[n+1]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
//	(*ePWM[n+1]).DBCTL.bit.POLSEL = DB_ACTV_HIC;	// Active Hi Complimentary
//	(*ePWM[n+1]).DBRED = RED;
//	(*ePWM[n+1]).DBFED = FED; 

}

