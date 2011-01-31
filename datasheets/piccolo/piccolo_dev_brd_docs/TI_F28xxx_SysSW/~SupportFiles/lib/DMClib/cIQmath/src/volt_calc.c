/*=====================================================================================
 File name:        VOLT_CALC.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  The Voltage Reconstruction based on switching functions and DC-Bus voltage                    

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "volt_calc.h"

void phase_voltage_calc(PHASEVOLTAGE *v)
{	
     if (v->OutOfPhase > 0)
     {
        v->MfuncV1 = -v->MfuncV1;
        v->MfuncV2 = -v->MfuncV2;
        v->MfuncV3 = -v->MfuncV3;     
     }

// scale the incomming Modulation functions with the DC bus voltage value
     v->MfuncV1 = _IQmpy(v->DcBusVolt,v->MfuncV1);
     v->MfuncV2 = _IQmpy(v->DcBusVolt,v->MfuncV2);    
     v->MfuncV3 = _IQmpy(v->DcBusVolt,v->MfuncV3);

// calculate the 3 Phase voltages       
     // Phase A
     v->VphaseA = _IQmpy(TWO_THIRD,v->MfuncV1);
     v->VphaseA -= _IQmpy(ONE_THIRD,v->MfuncV2);
     v->VphaseA -= _IQmpy(ONE_THIRD,v->MfuncV3);

     // Phase B
     v->VphaseB = _IQmpy(TWO_THIRD,v->MfuncV2);
     v->VphaseB -= _IQmpy(ONE_THIRD,v->MfuncV1); 
     v->VphaseB -= _IQmpy(ONE_THIRD,v->MfuncV3); 
               
     // Phase C
     v->VphaseC = _IQmpy(TWO_THIRD,v->MfuncV3);
     v->VphaseC -= _IQmpy(ONE_THIRD,v->MfuncV1); 
     v->VphaseC -= _IQmpy(ONE_THIRD,v->MfuncV2);  

// Voltage transformation (a,b,c)  ->  (Alpha,Beta)
     // Alpha-axis
     v->Valpha = v->VphaseA;
     
     // Beta-axis
     v->Vbeta = _IQmpy((v->VphaseA + _IQmpy(_IQ(2),v->VphaseB)),INV_SQRT3);

}



