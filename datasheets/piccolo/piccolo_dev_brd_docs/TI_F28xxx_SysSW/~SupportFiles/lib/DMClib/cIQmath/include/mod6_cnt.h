/* =================================================================================
File name:        MOD6_CNT.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the MOD6CNT module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                             
------------------------------------------------------------------------------*/
#ifndef __MOD6_CNT_H__
#define __MOD6_CNT_H__

typedef struct { Uint32  TrigInput;   	// Input: Modulo 6 counter trigger input - Q0 (0x00000000 or 0x00007FFF)
				 Uint32  Counter;	    // Output: Modulo 6 counter output - Q0 (0,1,2,3,4,5)			
		  	  	 void  (*calc)();	  	// Pointer to calculation function
				 } MOD6CNT;	            

typedef MOD6CNT *MOD6CNT_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the MOD6CNT object.
-----------------------------------------------------------------------------*/                     
#define MOD6CNT_DEFAULTS { 0,0, \
                   	      (void (*)(Uint32))mod6cnt_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in MOD6_CNT.C
------------------------------------------------------------------------------*/
void mod6cnt_calc(MOD6CNT_handle);

#endif // __MOD_6CNT_H__ 
