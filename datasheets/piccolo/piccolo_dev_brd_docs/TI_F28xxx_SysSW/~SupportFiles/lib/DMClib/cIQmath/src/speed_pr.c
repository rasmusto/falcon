/*=====================================================================================
 File name:        SPEED_PR.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  Speed measurement computation based capture input                  

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "speed_pr.h"

void speed_prd_calc(SPEED_MEAS_CAP *v)
{
   
   if (v->InputSelect == 0)  
   {
     v->OldTimeStamp = v->NewTimeStamp;
     v->NewTimeStamp = v->TimeStamp; 
     v->EventPeriod = v->NewTimeStamp - v->OldTimeStamp; 
   
     if (v->EventPeriod < 0)
       v->EventPeriod += 32767;   // 0x7FFF = 32767
    }

     v->Speed = _IQdiv(v->SpeedScaler,v->EventPeriod); 
   
// Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
   v->SpeedRpm = _IQmpy(v->BaseRpm,v->Speed); 
   
}
