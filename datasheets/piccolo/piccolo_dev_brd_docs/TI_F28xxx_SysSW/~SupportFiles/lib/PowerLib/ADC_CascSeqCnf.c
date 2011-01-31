//================================================================================
//	ADC_CascSeqCNF(int ChSel[], int ACQPS, int NumConvSEQ1, int mode)
//================================================================================
//	FILE:			ADC_CascSeqCnf.C
//
//	Description:	ADC configuration to support up to 16 conversions in Cascaded mode
//					Functions allows Channel selections and S/H acquisition window
//					width programming.
//
//	Version: 		1.1
//
//  Revision Date:	03 Dec 08
//
//  Target:  		TMS320F280x, F2802x(Piccolo) or F2833x
//
//================================================================================

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
// TARGET is F2802x (Piccolo device)
#if defined(DSP2802x_DEVICE_H)

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


// **TARGET is F280x, F2804x or F2833x device
#else 
// ADC power-up sequence		
	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;	// Power up bandgap/reference circuitry
	AdcRegs.ADCTRL3.bit.ADCPWDN = 0x1;		// Power up rest of ADC

// ADC Acquisition window select and Channel allocation
	AdcRegs.ADCTRL3.bit.ADCCLKPS=0;			// ADCCLK=12.5 MHz @ HSCLK=25MHz
	AdcRegs.ADCTRL1.bit.ACQ_PS= ACQPS; 		// Window aperture

// ADC Sequencer and Interrupt Init
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;		// Single 16 state sequencer
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;		// Wrap at MaxConv

// # of Conversions & Input channel Allocation
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = (NumConvSEQ1-1);		// Number of conversions

	AdcRegs.ADCCHSELSEQ1.bit.CONV00=ChSel[0];		// 1st conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ1.bit.CONV01=ChSel[1];		// 2nd conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ1.bit.CONV02=ChSel[2];		// 3rd conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ1.bit.CONV03=ChSel[3];		// 4th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ2.bit.CONV04=ChSel[4];		// 5th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ2.bit.CONV05=ChSel[5];		// 6th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ2.bit.CONV06=ChSel[6];		// 7th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ2.bit.CONV07=ChSel[7];		// 8th conv - Sequencer 1

	AdcRegs.ADCCHSELSEQ3.bit.CONV08=ChSel[8];		// 9th conv - Sequencer  1
	AdcRegs.ADCCHSELSEQ3.bit.CONV09=ChSel[9];		// 10th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ3.bit.CONV10=ChSel[10];		// 11th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ3.bit.CONV11=ChSel[11];		// 12th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ4.bit.CONV12=ChSel[12];		// 13th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ4.bit.CONV13=ChSel[13];		// 14th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ4.bit.CONV14=ChSel[14];		// 15th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ4.bit.CONV15=ChSel[15];		// 16th conv - Sequencer 1

	if (mode==0)
    {
    	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;		// Start-Stop Conv mode
    	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;	// Start Conv via ePWM SOCA trigger event
	}
	if (mode==1)
    {
    	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;		// Continuous Conv mode
    	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;		// Kick-start the ADC now
	}
	#endif
}





