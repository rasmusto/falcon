/*=====================================================================================
 File name:        RAMPGEN.C                 
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  The Ramp Generation                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "dmctype.h"
#include "rampgen.h"

void rampgen_calc(RAMPGEN *v)
{	

        v->Angle += v->StepAngleMax*v->Freq;       
        
        if (v->Angle>1.0)
          v->Angle -= 1.0;
        else if (v->Angle<-1.0)
          v->Angle += 1.0;

       v->Out = v->Angle*v->Gain + v->Offset;

       if (v->Out>1.0)
          v->Out -= 1.0;
        else if (v->Out<-1.0)
          v->Out += 1.0;

}




