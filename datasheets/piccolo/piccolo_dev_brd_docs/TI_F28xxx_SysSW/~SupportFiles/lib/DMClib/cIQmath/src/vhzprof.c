/*=====================================================================================
 File name:        VHZPROF.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:   V/f Profile for Scalar Control of Induction Motor

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library 
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file 
#include "dmctype.h"
#include "vhzprof.h"
#include <stdlib.h>

void vhz_prof_calc(VHZPROF *v)
{	
	_iq VfSlope, AbsFreq;

// Take absolute frequency to allow the operation of both rotational directions
    AbsFreq = labs(v->Freq);

	if (AbsFreq <= v->LowFreq)   
        // Compute output voltage in profile #1
        v->VoltOut = v->VoltMin; 
	else if ((AbsFreq > v->LowFreq)&(AbsFreq <= v->HighFreq))      
       {
        // Compute slope of V/f profile
        VfSlope = _IQdiv((v->VoltMax - v->VoltMin),(v->HighFreq - v->LowFreq));
        // Compute output voltage in profile #2
        v->VoltOut = v->VoltMin + _IQmpy(VfSlope,(AbsFreq-v->LowFreq));
       }
    else if ((AbsFreq > v->HighFreq)&(AbsFreq < v->FreqMax))      
        // Compute output voltage in profile #3
        v->VoltOut = v->VoltMax;
}


