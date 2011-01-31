/*=====================================================================================
 File name:        RMP2CNTL.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  The ramp2 output control                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "rmp2cntl.h"

void rmp2_cntl_calc(RMP2 *v)
{	

   if (v->Out != v->DesiredInput)
   {

      v->Ramp2DelayCount++;
      
      if (v->Ramp2DelayCount >= v->Ramp2Delay)   
      {
        v->Ramp2DelayCount = 0; 
       
       if (v->Out < v->DesiredInput) 
        {  
         v->Out++;
         if (v->Out > v->Ramp2Max) 
            v->Out = v->Ramp2Max;
        }
        else
        { 
         v->Out--;
         if (v->Out < v->Ramp2Min) 
            v->Out = v->Ramp2Min;
        }
      }                          
    } 
}


