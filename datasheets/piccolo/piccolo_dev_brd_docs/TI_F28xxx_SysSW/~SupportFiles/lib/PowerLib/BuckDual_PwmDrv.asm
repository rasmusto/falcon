;================================================================================
;	BuckDual_DRV  n 	Dual Buck, single ePWM module, same freq and phase
;================================================================================
;	FILE:			BuckDual_PwmDrv.asm
;
;	Description:	Dual (A & B outputs) channel Buck PWM driver macro
;
;	Version: 		1.0
;   Target:  		TMS320F280xx
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2007
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  08/01/07	| Release 1.0  		New release.
;--------------------------------------------------------------------------------
;			______________________
;			|	 BuckDual_DRV 	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| InA		   EPWMnA |--> Regular PWM output
;		 	|		  	     	  |
;		 -->| InB	  	   EPWMnB |--> Regular PWM output
;			|_____________________|
;
;	InA, InB, are pointers to signal nets.
;   Peripheral Resources used: EPWMn module
;
; Description:
; ------------
; Buck converter peripheral Driver interface
; n = 1, 2, 3, ... 16
;
;================================================================================
;-------------------------------------
BuckDual_DRV_INIT	.macro	n
;-------------------------------------
; Variable Declarations
_Buck_InA:n:		.usect "Net_terminals",2,1,1	; Input Terminal 1
_Buck_InB:n:		.usect "Net_terminals",2		; Input Terminal 2
BD_Period:n:		.usect "Net_terminals",1 		; EPWMn period value

				;Publish Terminal Pointers for access from the C environment
				;-----------------------------------------------------------
				.def 	_Buck_InA:n:
				.def 	_Buck_InB:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_Buck_InA:n:
			MOVL	@_Buck_InA:n:, XAR2
			MOVL	@_Buck_InB:n:, XAR2

			MOVW 	DP,#TBPRD:n:>>6
			MOV		ACC, @TBPRD:n:
			LSL		ACC,#1					; used instead of PM shift of 1
			MOVW	DP,#BD_Period:n:
			MOV		@BD_Period:n:, ACC		; Period=(TBPRDn x 2)
					.endm

;-------------------------------------
BuckDual_DRV		.macro	n
;-------------------------------------
			MOVW	DP, #_Buck_InA:n:
			MOVL 	XAR2,@_Buck_InA:n:		; Net pointer for InA  (XAR2)
			MOVL 	XAR3,@_Buck_InB:n:		; Net pointer for InB  (XAR3)
			MOVL 	XAR4,#CMPA:n:			; point to Compare A (XAR4)

		; Output for EPWMnA
			MOV 	T,*XAR2
			MPYU 	ACC,T,@BD_Period:n:
			MOV 	*XAR4++,AH				; output value to CMPAn

		; Output for EPWMnB
			MOV 	T,*XAR3
			MPYU 	ACC,T,@BD_Period:n:
			MOV 	*XAR4,AH				; output value to CMPBn
					.endm
