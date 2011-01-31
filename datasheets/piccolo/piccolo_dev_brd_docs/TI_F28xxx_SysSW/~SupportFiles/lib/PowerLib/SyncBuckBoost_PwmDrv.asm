;================================================================================
;	SYNCBUCKBOOST_DRV n   1 channel BuckBoost converter with dead-band
;================================================================================
;	FILE:			SyncBuckBoost_PwmDrv.asm
;
;	Description:	1 channel BuckBoost converter with dead-band
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
;				_______________________
;				|  SYNCBUCKBOOST_DRV  |
;				|~~~~~~~~~~~~~~~~~~~~~|
;			 -->| In 	   	   EPWMnA |--> output H1
;			 	|			   EPWMnB |--> output L1
;			 	|		   EPWM(n+1)A |--> output H2
;			 	|		   EPWM(n+1)B |--> output L2
;				|_____________________|
;
;
;	In, is a pointer to signal net.
;   Peripheral Resources used: EPWMn module
;
; Description:
; ------------
; SyncBuckBoost converter peripheral Driver interface
; n = 1, 2, 3, 4, 5, 6,...16
;
;================================================================================
;-------------------------------------
SYNCBUCKBOOST_DRV_INIT	.macro	n
;-------------------------------------
; Variable Declarations
_SYNCBB_In:n:		.usect "Net_terminals",2,1,1	; Terminal 1 (Input)
SyncBB_period:n:	.usect "Net_terminals",1 		; Period value

				;Publish Terminal Pointers for access from the C environment
				;-----------------------------------------------------------
				.def 	_SYNCBB_In:n:

	; set terminal to point to ZeroNet
	MOVL	XAR2, #ZeroNet
	MOVW	DP, #_SYNCBB_In:n:
	MOVL	@_SYNCBB_In:n:, XAR2

	MOVW 	DP,#TBPRD:n:>>6
	MOV		ACC, @TBPRD:n:
	LSL		ACC,#1						; used instead of PM shift of 1
	MOVW	DP,#SyncBB_period:n:
	MOV		@SyncBB_period:n:, ACC		; SyncBB_period=(TBPRDn x 2)
			.endm

;-------------------------------------
SYNCBUCKBOOST_DRV	.macro	n
;-------------------------------------
	MOVW	DP, #_SYNCBB_In:n:
	MOVL 	XAR0,@_SYNCBB_In:n:			; Net pointer for In	(XAR0)
	MOVL 	XAR1,#CMPA:n:				; point to CMP(n)A		(XAR1)

	; Output for EPWMnA
	MOV 	T,*XAR0
	MPYU 	ACC,T,@SyncBB_period:n:
	MOV 	*XAR1,AH					; output value to CMP(n)A

	ADDB	XAR1, #0x40					; Point to next EPWM module
	MOV 	*XAR1,AH					; output Duty to CMP(n+1)A

			.endm
