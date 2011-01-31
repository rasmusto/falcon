/* =================================================================================
File name:        RMP2CNTL.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the RMP2 module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                 
------------------------------------------------------------------------------*/
#ifndef __RMP2_CNTL_H__
#define __RMP2_CNTL_H__

typedef struct { _iq15 DesiredInput; 	// Input: Desired ramp input (Q15) - independently with global Q
                 _iq15 Ramp2Max; 		// Parameter: Maximum limit (Q15) - independently with global Q
				 _iq15 Ramp2Min;		// Parameter: Minimum limit (Q15) - independently with global Q			
				 Uint32 Ramp2DelayCount; // Variable: Incremental delay (Q0) - independently with global Q	
				 Uint32 Ramp2Delay;		// Parameter: Ramp2 delay expressed in no of sampling period (Q0) - independently with global Q			
				 _iq15 Out;				// Output: Ramp2 output (Q15)
		  	  	 void (*calc)();	  	// Pointer to calculation function  
				 } RMP2;

typedef RMP2 *RMP2_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the RMP2 object.
-----------------------------------------------------------------------------*/                     
#define RMP2_DEFAULTS { 0, \
                        0x00007FFF, \
                        0x0000000F, \
                        0, \
                        50, \
                       	0, \
             			(void (*)(Uint32))rmp2_cntl_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in RMP2CNTL.C
------------------------------------------------------------------------------*/
void rmp2_cntl_calc(RMP2_handle);

#endif // __RMP2_CNTL_H__
