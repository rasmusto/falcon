;----------------------------------------------------------------------------------
;	FILE:			DataLogTST.ASM
;
;	Description:	1 channel Data logging macro with TimeStamp trigger input.
;					TimeStamp compared to a Timebase
;
;	Version: 		1.0
;
;   Target:  		TMS320F280x 
;
;	Type: 			Device dependent
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2007
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date	     | Description
;----------------------------------------------------------------------------------
;  24 Apr 07 | Release 0.1  		New Release (DAF)
;----------------------------------------------------------------------------------

;=================================================================================
;	DataLogTST  module
;=================================================================================
;			______________________
;			|	  DataLogTST	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In		   	  Out |--> Memory Buffer
;		 	|		  	     	  |
;		 -->| TimeBase 	   		  |
;		 -->| TimeStampTrig		  |
;			|_____________________|
;
;	In - 			Input data stream A Pointer to integer
;	TimeBase -		A 32 bit time base input, usually ECAP or CPU timers
;	TimeStampTrig -	A 32 bit TimeStamp which is compared to the TimeBase

; Revision History:
;----------------------------------------------------------------------------------
; Date		| Author	| Description
;----------------------------------------------------------------------------------
; 09/13/06	| DAF		| Original
;
; _________________________________________________________________________________
;========================================================================
DataLogTST_INIT		.macro x
;========================================================================
; Variable Declarations
_DLTST_In:x:			.usect "DataLogTST",2,1,1	; Input Terminal
_DLTST_TimeBase:x:		.usect "DataLogTST",2 		; DataLog Time Base pointer to Long
_DLTST_TimeStampTrig:x:	.usect "DataLogTST",2 		; DataLog Time Stamp Trigger pointer to Long
DLptr:x:				.usect "DataLogTST",2		; DataLog Buffer Pointer
StatePtr:x:				.usect "DataLogTST",2		; State Pointer
DLcntr:x:				.usect "DataLogTST",1 		; DataLog Counter
_DLTST_DcOffset:x:		.usect "DataLogTST",1 		; DC offset value
_DLTST_Gain:x:			.usect "DataLogTST",1 		; Gain value
;DLtrgflg:x:			.usect "DataLogTST",1 		; DataLog Trigger Flag (not needed?)

;Publish Terminal Pointers for access from the C environment
;-----------------------------------------------------------
	.def 	_DLTST_In:x:
	.def 	_DLTST_TimeBase:x:
	.def 	_DLTST_TimeStampTrig:x:
	.def 	_DLTST_DcOffset:x:
	.def 	_DLTST_Gain:x:

	; set terminal to point to ZeroNet
	MOVL	XAR2, #ZeroNet
	MOVW	DP, #_DLTST_In:x:
	MOVL	@_DLTST_In:x:, XAR2
	MOVL	@_DLTST_TimeBase:x:, XAR2
	MOVL	@_DLTST_TimeStampTrig:x:, XAR2

	; Init the Memory Buffer pointers
	MOVL 	XAR2, #_DLogBuffer:x:
	MOVL 	@DLptr:x:, XAR2				
	MOV		@DLcntr:x:, #0					; reset counter

	; State Machine support init
	MOVW 	DP,#StatePtr:x:
	MOVL 	XAR7,#ST1:x:
	MOVL 	@StatePtr:x:, XAR7
					.endm

;========================================================================
DataLogTST		.macro x
;========================================================================
					
;------------------------------------------------------------------------
;  State Machine Entry Point
;------------------------------------------------------------------------
	MOVW 	DP,#StatePtr:x:
	MOVL 	XAR7,@StatePtr:x:
	LB 		*XAR7
;------------------------------------------------------------------------
; State 1 - Wait for Trigger
;------------------------------------------------------------------------
ST1:x:	
	MOVW	DP, #_DLTST_In:x:
	MOVL 	XAR3, @_DLTST_TimeBase:x:		; Net pointer for TimeBase
	MOVL 	XAR4, @_DLTST_TimeStampTrig:x:	; Net pointer for TimeStamp
	MOVL	ACC, *XAR3						; ACC = TimeBase
	CMPL 	ACC, *XAR4						; Compare TimeBase to TimeStamp
	B		DL_Exit:x:, LT					; Skip if TimeBase < TimeStamp
	MOVL 	XAR7,#ST2:x:					; If TimeBase >= TimeStamp
	MOVL 	@StatePtr:x:, XAR7				; 	go to next state
	LB 		DL_Exit:x:

;------------------------------------------------------------------------
; State 2 - Collect Data
;------------------------------------------------------------------------
ST2:x:	
	MOVL 	XAR1, @_DLTST_In:x:			; Net pointer for In
	MOVL 	XAR2, @DLptr:x:				; Retrieve current buffer address

	MOV		AL, *XAR1
	SUB		AL, @_DLTST_DcOffset:x:		; Remove DC offset
	MOV		T, @_DLTST_Gain:x:			; T = Gain Value (1,2,4,8,16,...)
	LSL		ACC, T						; Gain (xT) on Amplitute
	MOV		*XAR2++ , AL				; In --> [DLptr]
	MOVL 	@DLptr:x:, XAR2				; Save current Ptr address

	INC 	@DLcntr:x:
	CMP 	@DLcntr:x:, #300			; check if 300 samples
	B		DL_Exit:x:, LT				; If not, exit
	MOVL 	XAR7,#ST3:x:				; If yes go to next state
	MOVL 	@StatePtr:x:, XAR7			;
	LB 		DL_Exit:x:

;------------------------------------------------------------------------
; TIME SLICE 3 - Re-Arm for next trigger
;------------------------------------------------------------------------
ST3:x:	
	MOV		@DLcntr:x:, #0				; Reset Counter
	MOVL 	XAR5, #_DLogBuffer:x:		; point to start of buffer again
	MOVL 	@DLptr:x:, XAR5
	MOVL 	XAR7,#ST1:x:				; Go back to State-1
	MOVL 	@StatePtr:x:, XAR7			;
	LB 		DL_Exit:x:

;------------------------------------------------------------------------
; TIME SLICE 4 - Spare (not used)
;------------------------------------------------------------------------
ST4:x:
DL_Exit:x:
				.endm

