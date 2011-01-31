/* =================================================================================
File name:        SPEED_EST.H  (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
    Header file containing the data types, constants for the estimated rotor angle 
    based speed calculation function. Also contains the prototypes for the 
    functions implemented in SPEED_EST.C
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                 
------------------------------------------------------------------------------*/
#ifndef __SPEED_EST_H__
#define __SPEED_EST_H__

typedef struct {
       _iq EstimatedTheta;  	// Input: Electrical angle (pu) 
       _iq OldEstimatedTheta;   // History: Electrical angle at previous step (pu)
       _iq EstimatedSpeed;      // Output: Estimated speed in per-unit  (pu)
       Uint32 BaseRpm;     		// Parameter: Base speed in rpm (Q0) - independently with global Q
       _iq21 K1;       			// Parameter: Constant for differentiator (Q21) - independently with global Q
       _iq K2;     				// Parameter: Constant for low-pass filter (pu)
       _iq K3;     				// Parameter: Constant for low-pass filter (pu)
       int32 EstimatedSpeedRpm; // Output : Estimated speed in rpm  (Q0) - independently with global Q
       void (*calc)();  		// Pointer to the calculation function
       } SPEED_ESTIMATION;  	// Data type created 

typedef SPEED_ESTIMATION *SPEED_ESTIMATION_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_ESTIMATION object.
-----------------------------------------------------------------------------*/                     
#define SPEED_ESTIMATION_DEFAULTS   { 0, \
                                0, \
                                0, \
                                0, \
                                0, \
                                0, \
                                0, \
                                0, \
                               (void (*)(Uint32))speed_est_calc }

#define DIFF_MAX_LIMIT  	_IQ(0.80)
#define DIFF_MIN_LIMIT  	_IQ(0.20)
/*------------------------------------------------------------------------------
Prototypes for the functions in SPEED_EST.C
------------------------------------------------------------------------------*/
void speed_est_calc(SPEED_ESTIMATION_handle); 

#endif // __SPEED_EST_H__
