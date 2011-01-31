/* =================================================================================
File name:        VOLT_CAL.H (IQ version)                      
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
         Header file containing constants, data type definitions, and 
         function prototypes for the VOLT_CAL module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                               
------------------------------------------------------------------------------*/
#ifndef __VOLT_CAL_H__
#define __VOLT_CAL_H__

typedef struct 	{ _iq  DcBusVolt;		// Input: DC-bus voltage (pu)
			  	  _iq  MfuncV1;  		// Input: Modulation voltage phase A (pu)
		  	  	  _iq  MfuncV2;			// Input: Modulation voltage phase B (pu)	
		   	  	  _iq  MfuncV3;			// Input: Modulation voltage phase C (pu) 
                  Uint32  OutOfPhase; 	// Parameter: Out of Phase adjustment (0 or 1) (Q0) - independently with global Q
	  	  	  	  _iq  VphaseA;			// Output: Phase voltage phase A (pu)
		   	  	  _iq  VphaseB;			// Output: Phase voltage phase B (pu) 
		  	  	  _iq  VphaseC;			// Output: Phase voltage phase C (pu) 
		  	  	  _iq  Valpha;			// Output: Stationary d-axis phase voltage (pu)
		  	  	  _iq  Vbeta;  			// Output: Stationary q-axis phase voltage (pu)
		  	  	  void  (*calc)();		// Pointer to calculation function 
				} PHASEVOLTAGE;	                   

typedef PHASEVOLTAGE *PHASEVOLTAGE_handle; 

/*
OutOfPhase = 1 for the out of phase correction if
* MfuncV1 is out of phase with PWM1,
* MfuncV2 is out of phase with PWM3,
* MfuncV3 is out of phase with PWM5,
otherwise, set 0 if their phases are correct.
*/

/*-----------------------------------------------------------------------------
Default initalizer for the PHASEVOLTAGE object.
-----------------------------------------------------------------------------*/                     
#define PHASEVOLTAGE_DEFAULTS { 0, \
                          		0, \
                          		0, \
                          		0, \
                          		1, \
                          		0, \
                          		0, \
                          		0, \
		         				0, \
 		          				0, \
                  				(void (*)(Uint32))phase_voltage_calc }

#define ONE_THIRD  _IQ(0.33333333333333)
#define TWO_THIRD  _IQ(0.66666666666667)
#define INV_SQRT3  _IQ(0.57735026918963)
/*------------------------------------------------------------------------------
Prototypes for the functions in VOLT_CAL.C
------------------------------------------------------------------------------*/
void phase_voltage_calc(PHASEVOLTAGE_handle);

#endif // __VOLT_CAL_H__
