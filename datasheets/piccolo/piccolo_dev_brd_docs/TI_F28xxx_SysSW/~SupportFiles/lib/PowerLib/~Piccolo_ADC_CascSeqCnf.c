//================================================================================
//	ADC_CascSeqCNF(int ChSel[], int ACQPS, int NumConvSEQ1, int mode)
//================================================================================
//	FILE:			ADC_CascSeqCnf.C
//
//	Description:	ADC configuration to support up to 16 conversions in Cascaded mode
//					Functions allows Channel selections and S/H acquisition window
//					width programming.
//
//	Version: 		1.00
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
//  08/30/07  | Release 1.0  		New release.
//----------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"

//================================================================================
//			_______________________
//			|	  ADC???_DRV	   |
//			|~~~~~~~~~~~~~~~~~~~~~~|
//		 <--| Rslt[0~15]   ADC-A0  |<--
//		 	|		  	   ADC-A1  |<--
//		 	|		  	      "    |<--
//		 	|		  	   ADC-A7  |<--
//		 	|		  	    	   |<--
//	ChSel-->|		  	   ADC-B0  |<--
//		 	|		  	      "    |<--
//		 	|		  	   ADC-B7  |<--
//			|______________________|
//
// Description:
// ------------
// ADC peripheral Driver Configuration for a Cascaded Sequencer conversion session
// ChSel[] = Channel selection made via a channel # array passed as an argument
// NumConvSEQ1 = number of conversions in a session or wrap-around of state pointer
// ACQPS = AcqWidth is the S/H aperture in #ADCCLKS, i.e.
// 							AcqWidth = 1 gives = 1 ADCCLK
// 							AcqWidth = 2 gives = 2 ADCCLK
// 							AcqWidth = 3 gives = 3 ADCCLK....etc
//							Note: valid values are 1-16
// Mode = Operating mode: 	0 = Start / Stop mode, needs SOCA trigger event
//							1 = Continuous mode, no trigger needed
//============================================================================
void ADC_CascSeqCNF(int ChSel[], int ACQPS, int NumConvSEQ1, int mode)
{

    EALLOW;
	AdcRegs.ADCCTL1.bit.ADCREFSEL	= 0;
   	AdcRegs.ADCCTL1.bit.ADCBGPWD	= 1;	// Power up band gap
   	AdcRegs.ADCCTL1.bit.ADCREFPWD	= 1;	// Power up reference
   	AdcRegs.ADCCTL1.bit.ADCPWDN 	= 1;	// Power up rest of ADC
	AdcRegs.ADCCTL1.bit.ADCENABLE	= 1;	// Enable ADC
    asm(" RPT#100 || NOP");

	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;

	AdcRegs.ADCSOC0CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC1CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC2CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC3CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC4CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC5CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC6CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC7CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC8CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC9CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC10CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC11CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC12CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC13CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC14CTL.bit.ACQPS = ACQPS;
   	AdcRegs.ADCSOC15CTL.bit.ACQPS = ACQPS;

	AdcRegs.INTSEL1N2.bit.INT1SEL = 14;		// ADCCH14 (ADC-B6) EOC causes ADCInterrupt 1

	if (mode == 0)		// Start-Stop conv mode
	{
		AdcRegs.ADCINTFLG.bit.ADCINT1 = 0;
		AdcRegs.INTSEL1N2.bit.INT1CONT = 0;	// clear ADCINT1 flag to begin a new 
											//  set of conversions
	}
	if (mode == 1)		// Continuous conv mode
	{
		AdcRegs.INTSEL1N2.bit.INT1CONT = 1;	// set ADCInterrupt 1 to auto clr
	}

	AdcRegs.INTSEL1N2.bit.INT1E = 1;		// enable ADC interrupt 1

	//EOC = end of conversion event; SOC = start of conversion event
   	AdcRegs.ADCINTSOCSEL1.bit.SOC0 = 1;		// ADCInterrupt 1 causes SOC0
   	AdcRegs.ADCINTSOCSEL1.bit.SOC1 = 1;
   	AdcRegs.ADCINTSOCSEL1.bit.SOC2 = 1;
   	AdcRegs.ADCINTSOCSEL1.bit.SOC3 = 1;
   	AdcRegs.ADCINTSOCSEL1.bit.SOC4 = 1;
   	AdcRegs.ADCINTSOCSEL1.bit.SOC5 = 1;
   	AdcRegs.ADCINTSOCSEL1.bit.SOC6 = 1;
   	AdcRegs.ADCINTSOCSEL1.bit.SOC7 = 1;
   	AdcRegs.ADCINTSOCSEL2.bit.SOC8 = 1;
   	AdcRegs.ADCINTSOCSEL2.bit.SOC9 = 1;
   	AdcRegs.ADCINTSOCSEL2.bit.SOC10 = 1;
   	AdcRegs.ADCINTSOCSEL2.bit.SOC11 = 1;
   	AdcRegs.ADCINTSOCSEL2.bit.SOC12 = 1;
   	AdcRegs.ADCINTSOCSEL2.bit.SOC13 = 1;
   	AdcRegs.ADCINTSOCSEL2.bit.SOC14 = 1;
   	AdcRegs.ADCINTSOCSEL2.bit.SOC15 = 1;


// Select the channel to be converted when SOCx is received
	AdcRegs.ADCSOC0CTL.bit.CHSEL= ChSel[0];
	AdcRegs.ADCSOC1CTL.bit.CHSEL= ChSel[1];
	AdcRegs.ADCSOC2CTL.bit.CHSEL= ChSel[2];
	AdcRegs.ADCSOC3CTL.bit.CHSEL= ChSel[3];
	AdcRegs.ADCSOC4CTL.bit.CHSEL= ChSel[4];
	AdcRegs.ADCSOC5CTL.bit.CHSEL= ChSel[5];
	AdcRegs.ADCSOC6CTL.bit.CHSEL= ChSel[6];
	AdcRegs.ADCSOC7CTL.bit.CHSEL= ChSel[7];
	AdcRegs.ADCSOC8CTL.bit.CHSEL= ChSel[8];
	AdcRegs.ADCSOC9CTL.bit.CHSEL= ChSel[9];
	AdcRegs.ADCSOC10CTL.bit.CHSEL= ChSel[10];
	AdcRegs.ADCSOC11CTL.bit.CHSEL= ChSel[11];
	AdcRegs.ADCSOC12CTL.bit.CHSEL= ChSel[12];
	AdcRegs.ADCSOC13CTL.bit.CHSEL= ChSel[13];
	AdcRegs.ADCSOC14CTL.bit.CHSEL= ChSel[14];
	AdcRegs.ADCSOC15CTL.bit.CHSEL= ChSel[15];

	EDIS;


	AdcRegs.ADCSOCFRC1.all = 0xFFFF;		// kick-start ADC

}





