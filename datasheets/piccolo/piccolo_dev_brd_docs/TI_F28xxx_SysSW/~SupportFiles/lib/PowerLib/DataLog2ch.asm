;----------------------------------------------------------------------------------
;	FILE:			DataLog2ch.ASM
;
;	Description:	2 channel Data logging macro with Trigger input
;					Trigger event controlled via C code
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
;	DATA_LOG2  module - 
;=================================================================================
;			______________________
;			|	   DATA_LOG2	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| InA		  Output1 |--> Memory Buffer1
;		 	|		  	     	  |
;		 -->| InB	  	  Output2 |--> Memory Buffer2
;		 	|		  	     	  |
;		 -->| Trig	  	   		  |
;			|_____________________|
;
;	InA - Input data stream A (16 bit) Pointer to Net
;	InB - Input data stream B (16 bit) Pointer to Net
;	Trig - Capture Data Trigger (16 bit flag) C visible variable
;
; Revision History:
;----------------------------------------------------------------------------------
; Date		| Author	| Description
;----------------------------------------------------------------------------------
; 09/13/06	| DAF		| Original
;
; _________________________________________________________________________________
;=============================
DATA_LOG2_INIT		.macro x
;=============================
; Variable Declarations
_DATA_LOG2_InA:x:		.usect "Net_terminals",2,1,1	; Input Terminal 1
_DATA_LOG2_InB:x:		.usect "Net_terminals",2		; Input Terminal 2
DLogPtrA:x:				.usect "Net_terminals",2		; DataLog Mem Pointer A
DLogPtrB:x:				.usect "Net_terminals",2		; DataLog Mem Pointer B
DLcntr:x:				.usect "Net_terminals",1 		; DataLog Counter
_DATA_LOG2_Trig:x:		.usect "Net_terminals",1 		; DataLog Trigger flag

;Publish Terminal Pointers for access from the C environment
;===========================================================
					.def 	_DATA_LOG2_InA:x:
					.def 	_DATA_LOG2_InB:x:
					.def 	_DATA_LOG2_Trig:x:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_DATA_LOG2_InA:x:
			MOVL	@_DATA_LOG2_InA:x:, XAR2
			MOVL	@_DATA_LOG2_InB:x:, XAR2

		; Init the Memory Buffer pointers
			MOVL 	XAR2, #_DLogBufferA:x:
			MOVL 	@DLogPtrA:x:, XAR2				
			MOVL 	XAR2, #_DLogBufferB:x:
			MOVL 	@DLogPtrB:x:, XAR2				
			MOV		@DLcntr:x:, #0				; reset counter
			MOV		@_DATA_LOG2_Trig:x:, #0		; clear Trigger flag
					.endm

;============================
DATA_LOG2			.macro x
;============================
			MOVW	DP, #_DATA_LOG2_InA:x:
			CMP 	@_DATA_LOG2_Trig:x:, #1		; Is Trigger flag Set ?
			B		DLSkip:x:, NEQ							
			MOVL 	XAR1, @_DATA_LOG2_InA:x:	; Net pointer for InA  (XAR1)
			MOVL 	XAR2, @_DATA_LOG2_InB:x:	; Net pointer for InB  (XAR2)
			MOVL 	XAR3, @DLogPtrA:x:			; Retrieve current bufferA address
			MOVL 	XAR4, @DLogPtrB:x:			; Retrieve current bufferB address

			MOV		AL, *XAR1
			MOV		*XAR3++ , AL				; InA --> [DLogPtrA]
			MOV		AL, *XAR2
			MOV		*XAR4++ , AL				; InB --> [DLogPtrB]

			MOVL 	@DLogPtrA:x:, XAR3			; Save current address A
			MOVL 	@DLogPtrB:x:, XAR4			; Save current address B

			INC 	@DLcntr:x:
			CMP 	@DLcntr:x:, #200			; Log 200 samples
			B		DLSkip:x:, LT							
			MOV		@DLcntr:x:, #0				; reset counter
			MOVL 	XAR5, #_DLogBufferA:x:		; point to start of buffer
			MOVL 	@DLogPtrA:x:, XAR5
			MOVL 	XAR5, #_DLogBufferB:x:		; point to start of buffer
			MOVL 	@DLogPtrB:x:, XAR5
			MOV		@_DATA_LOG2_Trig:x:, #0		; clear Trigger flag
DLSkip:x:	NOP									; Re-armed for next Trigger
					.endm
