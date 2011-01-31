/* =================================================================================
File name:       ATAN2_TAB.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the ATAN2TAB.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                  
------------------------------------------------------------------------------*/

typedef struct {  float32  X;      		// Input: x argument 
	              float32  Y;		  	// Input: y argument  
	              float32  Angle;      	// Output: angle (pu)  
		 	 	  void  (*calc)();	  	// Pointer to calculation function
				 } ATAN2TAB;	            

typedef ATAN2TAB *ATAN2TAB_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the ATAN2TAB object.
-----------------------------------------------------------------------------*/                     
#define ATAN2TAB_DEFAULTS {  0,0,0, \
             			 (void (*)(Uint32))atan2_tab_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in ATAN2_TAB.C
------------------------------------------------------------------------------*/
void atan2_tab_calc(ATAN2TAB_handle);

