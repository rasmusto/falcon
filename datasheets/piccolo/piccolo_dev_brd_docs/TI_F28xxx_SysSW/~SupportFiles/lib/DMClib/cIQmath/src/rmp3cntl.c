/*=====================================================================================
 File name:        RMP3CNTL.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  The ramp3 down control                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library 
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file 
#include "dmctype.h"
#include "rmp3cntl.h"

void rmp3_cntl_calc(RMP3 *v)
{	
   
   if (v->Out == v->DesiredInput)
      v->Ramp3DoneFlag = 0x7FFFFFFF;
   else
    {

      v->Ramp3DelayCount++;
      
      if (v->Ramp3DelayCount >= v->Ramp3Delay)   
      {
        v->Out--;

        if (v->Out < v->Ramp3Min)
           v->Out = v->Ramp3Min; 

        v->Ramp3DelayCount = 0; 
      }                          
    
    } 
}


