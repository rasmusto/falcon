/* =================================================================================
File name:       IPARK.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the IPARK.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                
------------------------------------------------------------------------------*/

typedef struct {  float32  Alpha;  	// Output: stationary d-axis stator variable 
				  float32  Beta;	// Output: stationary q-axis stator variable 
				  float32  Angle;	// Input: rotating angle (rad) 
				  float32  Ds;		// Input: rotating d-axis stator variable 
				  float32  Qs;		// Input: rotating q-axis stator variable 
		 	 	  void  (*calc)();	// Pointer to calculation function 
				 } IPARK;	            

typedef IPARK *IPARK_handle;

/*-----------------------------------------------------------------------------
Default initalizer for the IPARK object.
-----------------------------------------------------------------------------*/                     
#define IPARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  (void (*)(Uint32))ipark_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in IPARK.C
------------------------------------------------------------------------------*/
void ipark_calc(IPARK_handle);

