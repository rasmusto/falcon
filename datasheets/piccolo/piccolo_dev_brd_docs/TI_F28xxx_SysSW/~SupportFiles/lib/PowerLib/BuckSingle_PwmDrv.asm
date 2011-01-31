;----------------------------------------------------------------------------------
;	FILE:			BuckSingle_PwmDrv.asm
;
;	Description:	Single (A output) channel Buck PWM driver macro
;
;	Version: 		1.0
;
;   Target:  		TMS320F280xx
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2007
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  08/01/07	| Release 1.0  		New release.
;--------------------------------------------------------------------------------

;================================================================================
;	BuckSingle_DRV  n  driver module - ePWM-A output Buck s/w driver
;================================================================================
;			______________________
;			|	 BuckSingle_DRV	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In		   EPWMnA |--> Regular PWM output
;		 	|		  	     	  |
;			|_____________________|
;
;	In, is a pointer to signal net.
;   Peripheral Resources used: EPWMn module
;
; Description:
; ------------
; Buck converter peripheral Driver interface
; n = 1, 2, 3, ... 16
;
;================================================================================
;=================================
BuckSingle_DRV_INIT		.macro	n
;=================================
; Variable Declarations
_Buck_In:n:			.usect "Net_terminals",2,1,1	; Input Terminal 1
BS_Period:n:		.usect "Net_terminals",1 		; EPWMn period value

;Publish Terminal Pointers for access from the C environment
;===========================================================
					.def 	_Buck_In:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_Buck_In:n:
			MOVL	@_Buck_In:n:, XAR2

			MOVW 	DP,#TBPRD:n:>>6
			MOV		ACC, @TBPRD:n:
			LSL		ACC,#1					; used instead of PM shift of 1
			MOVW	DP,#BS_Period:n:
			MOV		@BS_Period:n:, ACC		; Period=(TBPRDn x 2)
					.endm

;=========================
BuckSingle_DRV		.macro	n
;=========================
			MOVW	DP, #_Buck_In:n:
			MOVL 	XAR0,@_Buck_In:n:		; Net pointer for InA	(XAR0)
			MOVL 	XAR1,#CMPA:n:			; point to Compare A	(XAR1)

		; Output for EPWMnA
			MOV 	T,*XAR0
			MPYU 	ACC,T,@BS_Period:n:
			MOV 	*XAR1++,AH				; output value to CMPAn
				.endm
