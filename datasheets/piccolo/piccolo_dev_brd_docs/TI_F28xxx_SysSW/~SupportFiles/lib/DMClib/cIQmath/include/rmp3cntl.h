/* =================================================================================
File name:        RMP3CNTL.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the RMP3 module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                  
------------------------------------------------------------------------------*/
#ifndef __RMP3_CNTL_H__
#define __RMP3_CNTL_H__

typedef struct { Uint32 DesiredInput; 		// Input: Desired ramp input (Q0) - independently with global Q
				 Uint32 Ramp3Delay;			// Parameter: Ramp3 delay expressed in no of sampling period (Q0) - independently with global Q		
		 	 	 Uint32 Ramp3DelayCount;	// Variable: Counter for rmp3 delay (Q0) - independently with global Q
				 int32 Out;					// Output: Ramp3 output (Q0) - independently with global Q
				 int32 Ramp3Min;	    	// Parameter: Minimum ramp output (Q0) - independently with global Q
				 Uint32 Ramp3DoneFlag;		// Output: Flag output (Q0) - independently with global Q
		  	  	 void (*calc)();	  		// Pointer to calculation function 
				 } RMP3;	            

typedef RMP3 *RMP3_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the RMP3 object.
-----------------------------------------------------------------------------*/                     
#define RMP3_DEFAULTS { 0, \
                        0, \
                        0, \
                        0, \
                        0x00000050, \
                       	0, \
             			(void (*)(Uint32))rmp3_cntl_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in RMP3CNTL.C
------------------------------------------------------------------------------*/
void rmp3_cntl_calc(RMP3_handle);

#endif // __RMP3_CNTL_H__

