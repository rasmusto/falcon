/* =================================================================================
File name:       PARK.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the PARK.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                 
------------------------------------------------------------------------------*/

typedef struct {  float32  Alpha;  	// Input: stationary d-axis stator variable 
				  float32  Beta;	// Input: stationary q-axis stator variable 
				  float32  Angle;	// Input: rotating angle (rad) 
				  float32  Ds;		// Output: rotating d-axis stator variable 
				  float32  Qs;		// Output: rotating q-axis stator variable 
		 	 	  void  (*calc)();	// Pointer to calculation function 
				 } PARK;	            

typedef PARK *PARK_handle;

/*-----------------------------------------------------------------------------
Default initalizer for the PARK object.
-----------------------------------------------------------------------------*/                     
#define PARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  (void (*)(Uint32))park_calc }
              			  
/*------------------------------------------------------------------------------
Prototypes for the functions in PARK.C
------------------------------------------------------------------------------*/
void park_calc(PARK_handle);


