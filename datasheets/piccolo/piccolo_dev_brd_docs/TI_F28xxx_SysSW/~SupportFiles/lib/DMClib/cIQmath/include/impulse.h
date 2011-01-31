/* =================================================================================
File name:        IMPULSE.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the IMPULSE module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                            
------------------------------------------------------------------------------*/
#ifndef __IMPULSE_H__
#define __IMPULSE_H__

typedef struct { Uint32  Period;		// Input: Period of output impulse in a number of sampling cycles (Q0)			
				 Uint32  Out;      		// Output: Impulse generator output - Q0 (0x00000000 or 0x00007FFF)
		  	  	 Uint32  Counter;   	// Variable: Impulse generator counter (Q0)
				 void  (*calc)();	  	// Pointer to calculation function
				 } IMPULSE;	            

typedef IMPULSE *IMPULSE_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the IMPULSE object.
-----------------------------------------------------------------------------*/                     
#define IMPULSE_DEFAULTS { 1000,0,0, \
                   	      (void (*)(Uint32))impulse_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in IMPULSE.C
------------------------------------------------------------------------------*/
void impulse_calc(IMPULSE_handle);

#endif // __IMPULSE_H__
