/*=====================================================================================
 File name:        ATAN2_TAB.C                   
                    
 Originator:	Digital Control SYstems Group
			TeXas Instruments

 Description:  Computation of atan2 based on look-up atan table                
               
               Note that Anglele = atan2(Y/X) in pu (1 pu = 360 degree)
=====================================================================================
 HistorY:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "dmctype.h"
#include "atan2_tab.h"

extern float32 atan_tab[];

void atan2_tab_calc(ATAN2TAB *v)
{	
     float32 Y_X;
     
     Y_X = v->Y/v->X;
     if ((Y_X < 0)&(Y_X >= -1))
      {
         Y_X = -Y_X;
         v->Angle = atan_tab[(int16)(Y_X*256)];
      }
     else if ((Y_X < 0)&(Y_X < -1))
      {
         Y_X = -1/Y_X;
         v->Angle = 0.25 - atan_tab[(int16)(Y_X*256)];
      }
     else if ((Y_X > 0)&(Y_X > 1))
      {
         Y_X = 1/Y_X;
         v->Angle = 0.25 - atan_tab[(int16)(Y_X*256)];
      }
     else if ((Y_X > 0)&(Y_X <= 1))        
      {
         v->Angle = atan_tab[(int16)(Y_X*256)];
      }
     
     if ((v->X<0)&(v->Y>=0))              // Second-quadrant
       v->Angle = 0.5 - v->Angle;
     else if ((v->X<0)&(v->Y<0))          // Third-quadrant
       v->Angle = 0.5 + v->Angle;
     else if ((v->X>=0)&(v->Y<0))         // Fourth-quadrant
       v->Angle = 1.0 - v->Angle;
}


