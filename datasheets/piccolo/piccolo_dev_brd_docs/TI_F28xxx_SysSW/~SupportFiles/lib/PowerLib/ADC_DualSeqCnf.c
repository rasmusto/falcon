//================================================================================
//	ADC_DualSeqCNF(int ChSel[], int ACQPS, int NumConvSEQ1, int NumConvSEQ2)
//================================================================================
//	FILE:			ADC_DualSeqCnf.C
//
//	Description:	ADC Interface driver config to supports up to 16 conversions.
//					These functions allow Channel selections and S/H
//					acquisition window width programming.
//					Note: Not continuous conversion mode, each Seq needs SOC trigger
//
//	Version: 		1.00
//
//  Target:  		TMS320F280xx or F2833x
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2007
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description
//----------------------------------------------------------------------------------
//  08/30/07  | Release 1.0  		New release.
//----------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"	// Include all Peripheral Headers

//============================================================================
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
// ADC peripheral Driver Configuration for a Dual conversion session (Seq1 and Seq2)
// Channel selection made via a channel # array passed as an argument
// NumConvSEQ1 = number of conversions in a session for Seq1
// NumConvSEQ2 = number of conversions in a session for Seq2
// Argument AcqWidth is the S/H aperture in #ADCCLKS, i.e.
// 							AcqWidth = 1 gives = 1 ADCCLK
// 							AcqWidth = 2 gives = 2 ADCCLK
// 							AcqWidth = 3 gives = 3 ADCCLK....etc
//							Note: valid values are 1-16
//============================================================================

void ADC_DualSeqCNF(int ChSel[], int ACQPS, int NumConvSEQ1, int NumConvSEQ2)
{

// ADC power-up sequence		
	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;	// Power up bandgap/reference circuitry
	AdcRegs.ADCTRL3.bit.ADCPWDN = 0x1;		// Power up rest of ADC

// ADC Acquisition window select and Channel allocation
	AdcRegs.ADCTRL3.bit.ADCCLKPS=0;			// ADCCLK=12.5 MHz @ HSCLK=25MHz
	AdcRegs.ADCTRL1.bit.ACQ_PS= ACQPS; 		// Window aperture

// ADC Sequencer and Interrupt Init
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;		// Dual Sequencer Mode
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;		// A "Don't care" if Start-stop mode used
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;		// Start-Stop mode

// # of Conversions & Input channel Allocation
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = (NumConvSEQ1-1);	// Number of conversions
    AdcRegs.ADCMAXCONV.bit.MAX_CONV2 = (NumConvSEQ2-1);	// Number of conversions

	AdcRegs.ADCCHSELSEQ1.bit.CONV00=ChSel[0];		// 1st conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ1.bit.CONV01=ChSel[1];		// 2nd conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ1.bit.CONV02=ChSel[2];		// 3rd conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ1.bit.CONV03=ChSel[3];		// 4th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ2.bit.CONV04=ChSel[4];		// 5th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ2.bit.CONV05=ChSel[5];		// 6th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ2.bit.CONV06=ChSel[6];		// 7th conv - Sequencer 1
	AdcRegs.ADCCHSELSEQ2.bit.CONV07=ChSel[7];		// 8th conv - Sequencer 1

	AdcRegs.ADCCHSELSEQ3.bit.CONV08=ChSel[8];		// 1st conv - Sequencer 2
	AdcRegs.ADCCHSELSEQ3.bit.CONV09=ChSel[9];		// 2nd conv - Sequencer 2
	AdcRegs.ADCCHSELSEQ3.bit.CONV10=ChSel[10];		// 3rd conv - Sequencer 2
	AdcRegs.ADCCHSELSEQ3.bit.CONV11=ChSel[11];		// 4th conv - Sequencer 2
	AdcRegs.ADCCHSELSEQ4.bit.CONV12=ChSel[12];		// 5th conv - Sequencer 2
	AdcRegs.ADCCHSELSEQ4.bit.CONV13=ChSel[13];		// 6th conv - Sequencer 2
	AdcRegs.ADCCHSELSEQ4.bit.CONV14=ChSel[14];		// 7th conv - Sequencer 2
	AdcRegs.ADCCHSELSEQ4.bit.CONV15=ChSel[15];		// 8th conv - Sequencer 2

    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;	// Start Conv via ePWM SOCA trigger event
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 1;	// Start Conv via ePWM SOCB trigger event
}





