
;// Include variables and constants that will be shared in the
;// C28x C-code and CLA assembly code.  This is accomplished by
;// using .cdecls to include a C-code header file that contains
;// these variables and constants

      .cdecls   C,LIST,"CLAShared.h"

;// To include an MDEBUGSTOP (CLA breakpoint) as the first instruction
;// of each task, set CLA_DEBUG to 1.  Use any other value to leave out
;// the MDEBUGSTOP instruction.

CLA_DEBUG .set  0

;// CLA code must be within its own assembly section and must be
;// even aligned.  Note: since all CLA instructions are 32-bit
;// this alignment naturally occurs and the .align 2 is most likely
;// redundant

       .sect        "Cla1Prog"
_Cla1Prog_Start
       .align       2


_Cla1Task1:
;convert sensors.sensor[0-3] to standard units
; 
;
; X and A are arrays of 32-bit float (i.e. 2 words)
; Use these defines to make the code easier to read
;
_MULT7  .set _sensor_multipliers+14
_MULT6  .set _sensor_multipliers+12
_MULT5  .set _sensor_multipliers+10
_MULT4  .set _sensor_multipliers+8  
_MULT3  .set _sensor_multipliers+6  
_MULT2  .set _sensor_multipliers+4  
_MULT1  .set _sensor_multipliers+2  
_MULT0  .set _sensor_multipliers+0  
	MSTOP
	MNOP
    MNOP
    MNOP
_Cla1T1End:


_Cla1Task2:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T2End:

_Cla1Task3:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T3End:
    

_Cla1Task4:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T4End:
    
    
_Cla1Task5:  
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T5End:
    
_Cla1Task6:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T6End:    

_Cla1Task7:
    MSTOP
    MNOP
    MNOP
    MNOP                                  ; End task
_Cla1T7End:
          
_Cla1Task8:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T8End:

    
    
_Cla1Prog_End:


    .end
    .include "CLAShared.h"


