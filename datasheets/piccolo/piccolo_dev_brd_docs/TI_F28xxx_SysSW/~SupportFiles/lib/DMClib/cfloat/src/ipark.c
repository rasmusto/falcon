/*=====================================================================================
 File name:        IPARK.C                   
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  Inverse Park Transformation               

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "dmctype.h"
#include "ipark.h"

extern float32 sin_tab[];

void ipark_calc(IPARK *v)
{	
   
   float32 Cosine,Sine;
   
// Using look-up sine table 
// (PI/2)/(2*PI) = 0.25
// ((PI/2)/(2*PI))*256 = 0.25*256 = 64
// ((PI/2)-2*PI)/(2*PI) = -0.75
// (((PI/2)-2*PI)/(2*PI))*256 = -0.75*256 = -192

    if (v->Angle+0.25 > 1.0) 
     {
     Sine = sin_tab[(int16)(v->Angle*256)];
     Cosine = sin_tab[(int16)(v->Angle*256) - 192];  
     }
    else
    { 
     Sine = sin_tab[(int16)(v->Angle*256)];
     Cosine = sin_tab[(int16)(v->Angle*256) + 64];
    }
 
     v->Alpha = v->Ds*Cosine - v->Qs*Sine;
     v->Beta = v->Qs*Cosine + v->Ds*Sine;  
}
