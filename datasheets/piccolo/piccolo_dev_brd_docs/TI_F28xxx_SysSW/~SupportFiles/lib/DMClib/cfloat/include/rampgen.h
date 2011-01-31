/* =================================================================================
File name:        RAMPGEN.H                   
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
This file contains type definitions, constants and initializers for
the ramp generation functions contained in RAMPGEN.C
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                
------------------------------------------------------------------------------*/

typedef struct { float32  Freq; 		// Input: Ramp frequency (pu)
		 	     float32  StepAngleMax;	// Parameter: Maximum step angle (pu)		
	 	 	     float32  Angle;		// Variable: Step angle (pu) 				  
			     float32  Gain;			// Input: Ramp gain (pu) 
			     float32  Out;			// Output: Ramp signal (pu)
			     float32  Offset;		// Input: Ramp offset (pu)				 
	  	  	     void  (*calc)();	  	// Pointer to calculation function
			   } RAMPGEN;	            

typedef RAMPGEN *RAMPGEN_handle;  
/*------------------------------------------------------------------------------
      Object Initializers
------------------------------------------------------------------------------*/                       
#define RAMPGEN_DEFAULTS {0,0,0,1,0,1, \
                         (void (*)(Uint32))rampgen_calc }

/*------------------------------------------------------------------------------
      Funtion prototypes
------------------------------------------------------------------------------*/                                               
void rampgen_calc(RAMPGEN_handle);

