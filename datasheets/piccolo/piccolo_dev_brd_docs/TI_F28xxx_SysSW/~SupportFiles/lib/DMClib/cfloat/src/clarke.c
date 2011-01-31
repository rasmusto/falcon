/*=====================================================================================
 File name:        CLARKE.C                   
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  The Clarke Transformation                 

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "dmctype.h"
#include "clarke.h"

void clarke_calc(CLARKE *v)
{	
   v->Alpha = v->As;

   v->Beta = (v->As + 2*v->Bs)*0.57735026918963;  // 1/sqrt(3) = 0.57735026918963
}


