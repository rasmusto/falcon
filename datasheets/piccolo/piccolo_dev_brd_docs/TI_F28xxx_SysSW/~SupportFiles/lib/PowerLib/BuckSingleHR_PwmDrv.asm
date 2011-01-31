;----------------------------------------------------------------------------------
;	FILE:			BuckSingleHR_PwmDrv.asm
;
;	Description:	Single (A output) channel Buck HiRes PWM driver macro
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
;  08/22/07	| Release 1.0  		New release.
;--------------------------------------------------------------------------------

;================================================================================
;	BuckSingleHR_DRV  n  driver module - ePWM-A output HiRes Buck s/w driver
;================================================================================
;			______________________
;			|  BuckSingleHR_DRV	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In		   EPWMnA |--> HiRes PWM output
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
BuckSingleHR_DRV_INIT		.macro	n
;=================================
; Variable Declarations
_Buck_In:n:			.usect "Net_terminals",2,1,1	; Input Terminal 1
BS_Period:n:		.usect "Net_terminals",1 		; EPWMn period value
_HRSF:n:			.usect "Net_terminals",1 		; HiRes Scale Factor

;Publish Terminal Pointers for access from the C environment
;===========================================================
					.def 	_Buck_In:n:
					.def 	_HRSF:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_Buck_In:n:
			MOVL	@_Buck_In:n:, XAR2

			MOVW 	DP,#TBPRD:n:>>6
			MOV		ACC, @TBPRD:n:
			LSL		ACC,#1					; used instead of PM shift of 1
			MOVW	DP,#BS_Period:n:
			MOV		@BS_Period:n:, ACC		; Period=(TBPRDn x 2)
			MOV		@_HRSF:n:, #(68*256)	; Initial value for 100MHz case
					.endm

;=========================
BuckSingleHR_DRV	.macro	n
;=========================
			MOVW	DP, #_Buck_In:n:
			MOVL 	XAR0,@_Buck_In:n:		; Net pointer for In	(XAR0)
			MOVL 	XAR1,#CMPAHR:n:			; point to CompareHr nA	(XAR1)

		; Output for EPWMnA (Hi Res)		
			MOV 	T,*XAR0
			MPYU 	ACC,T,@BS_Period:n:
			MOV		T,@_HRSF:n:
			MPYU	P,T,@AL                 ; P = T * AL
			MOVH	@AL,P
			ADD		ACC, #0x17F				; Optimize by Round up
			MOVL	*XAR1,ACC 				; CMPA:CMPAHR(31:8) = ACC

		; Output for EPWMnB (Regular Res) Optional - for comparison purpose only
;			MOV		*+XAR1[2],AH			; Store ACCH to regular CMPB
				.endm
















