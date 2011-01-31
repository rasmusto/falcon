/*=====================================================================================
 File name:        RMP_CNTL.H                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description: Header file containing constants, data type definitions, and 
 function prototypes for the RMPCNTL module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

typedef struct { float32  TargetValue; 		// Input: Target input (pu)
				 float32  RampDelayMax;		// Parameter: Maximum delay rate (Q0)		
		 	 	 float32  RampLowLimit;		// Parameter: Minimum limit (pu)				  
				 float32  RampHighLimit;	// Parameter: Maximum limit (pu)
				 float32  RampDelayCount; 	// Variable: Incremental delay (Q0)	
				 float32  SetpointValue;	// Output: Target output (pu)				 
				 float32  EqualFlag;		// Output: Flag output (Q0)
		  	  	 void  (*calc)();	  		// Pofloater to calculation function
				 } RMPCNTL;	            

typedef RMPCNTL *RMPCNTL_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the RMPCNTL object.
-----------------------------------------------------------------------------*/                     
#define RMPCNTL_DEFAULTS { 0, \
                           5, \
                          	-1, \
                          	1, \
                          	0, \
                          	0, \
                          	0, \
                   			(void (*)(Uint32))rmp_cntl_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in RMP_CNTL.C
------------------------------------------------------------------------------*/
void rmp_cntl_calc(RMPCNTL_handle);

