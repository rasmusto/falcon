/*=====================================================================================
 File name:        SPEED_EST.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  Speed computation based estimated rotor angle                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file 
#include "dmctype.h"
#include "speed_est.h"

void speed_est_calc(SPEED_ESTIMATION *v)
{

   _iq Temp1;

// Synchronous speed computation 
   if ((v->EstimatedTheta < DIFF_MAX_LIMIT)&(v->EstimatedTheta > DIFF_MIN_LIMIT))
		// Q21 = Q21*(GLOBAL_Q-GLOBAL_Q)
   		Temp1 = _IQmpy(v->K1,(v->EstimatedTheta - v->OldEstimatedTheta));
   else Temp1 = _IQtoIQ21(v->EstimatedSpeed);

// Low-pass filter
   // Q21 = GLOBAL_Q*Q21 + GLOBAL_Q*Q21
   Temp1 = _IQmpy(v->K2,_IQtoIQ21(v->EstimatedSpeed))+_IQmpy(v->K3,Temp1);  

   if (Temp1>_IQ21(1))
     v->EstimatedSpeed = _IQ(1);
   else if (Temp1<_IQ21(-1))
     v->EstimatedSpeed = _IQ(-1);      
   else
     v->EstimatedSpeed = _IQ21toIQ(Temp1);

// Update the electrical angle
    v->OldEstimatedTheta = v->EstimatedTheta;

// Change motor speed from pu value to rpm value (GLOBAL_Q -> Q0)
// Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
   v->EstimatedSpeedRpm = _IQmpy(v->BaseRpm,v->EstimatedSpeed); 

}

