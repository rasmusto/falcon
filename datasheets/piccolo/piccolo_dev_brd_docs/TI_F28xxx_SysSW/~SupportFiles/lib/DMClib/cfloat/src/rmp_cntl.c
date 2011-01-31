/*=====================================================================================
 File name:        RMP_CNTL.C                   
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  Ramp control          

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "dmctype.h"
#include "rmp_cntl.h"

void rmp_cntl_calc(RMPCNTL *v)
{	

      if (v->TargetValue != v->SetpointValue)
      {
         v->RampDelayCount += 1.0;
         if (v->RampDelayCount >= v->RampDelayMax)
         {
           if (v->TargetValue >= v->SetpointValue)
           {
            v->SetpointValue += 0.0000305;           // 0.0000305 is resolution of Q15
            if (v->SetpointValue > v->RampHighLimit)
              v->SetpointValue = v->RampHighLimit;           
            v->RampDelayCount = 0;
           }
           else
           {
            v->SetpointValue -= 0.0000305;           // 0.0000305 is resolution of Q15
            if (v->SetpointValue < v->RampLowLimit)
              v->SetpointValue = v->RampLowLimit;           
            v->RampDelayCount = 0;
           }
         }
         
      }
      else  v->EqualFlag = 1; 
}


