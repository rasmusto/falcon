/*=====================================================================================
 File name:        IMPULSE.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  Periodic impulse function                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "impulse.h"

void impulse_calc(IMPULSE *v)
{	
  
  v->Out = 0;      // Always clear impulse output at entry
  v->Counter++;    // Increment the skip counter

  if (v->Counter >= v->Period)
  {
     v->Out = 0x00007FFF;
     v->Counter = 0;        // Reset counter
  }
   
}


