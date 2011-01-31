/* =================================================================================
File name:       CLARKE.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the CLARKE.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                
------------------------------------------------------------------------------*/

typedef struct {  float32  As;  	// Input: phase-a stator variable  
				  float32  Bs;		// Input: phase-b stator variable  
				  float32  Alpha;	// Output: stationary d-axis stator variable 
				  float32  Beta;	// Output: stationary q-axis stator variable 
		 	 	  void  (*calc)();	// Pointer to calculation function
				 } CLARKE;	            

typedef CLARKE *CLARKE_handle;

/*-----------------------------------------------------------------------------
Default initalizer for the CLARKE object.
-----------------------------------------------------------------------------*/                     
#define CLARKE_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
              			  (void (*)(Uint32))clarke_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in CLARKE.C
------------------------------------------------------------------------------*/
void clarke_calc(CLARKE_handle);
