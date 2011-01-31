/*=====================================================================================
 File name:        MOD6_CNT.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  Modulo 6 counter module                  

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "mod6_cnt.h"

void mod6cnt_calc(MOD6CNT *v)
{	
   
   if (v->TrigInput > 0)
   {
     if (v->Counter == 5)    // Reset the counter when it is 5
       v->Counter = 0;       
     else
       v->Counter++;         // Otherwise, increment by 1
   }
   
}


