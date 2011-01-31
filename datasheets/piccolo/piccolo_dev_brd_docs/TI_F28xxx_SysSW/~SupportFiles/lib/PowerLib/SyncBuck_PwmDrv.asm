;================================================================================
;	SYNCBUCK_DRV n    1 channel SyncBuck converter with dead-band
;================================================================================
;	FILE:			SyncBuck_PwmDrv.asm
;
;	Description:	1 channel SyncBuck converter with dead-band
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
;			|	  SYNCBUCK_DRV 	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In		   EPWMnA |--> PWM-A output
;		 	|		  	     	  |
;		 	|		  	   EPWMnB |--> PWM-B output
;			|_____________________|
;
;	In, is a pointer to signal net.
;   Peripheral Resources used: EPWMn module
;
; Description:
; ------------
; SyncBuck converter peripheral Driver interface
; n = 1, 2, 3, 4, 5, 6,...16
;
;================================================================================
;-------------------------------------
SYNCBUCK_DRV_INIT	.macro	n
;-------------------------------------
; Variable Declarations
_SYNCBUCK_In:n:		.usect "Net_terminals",2,1,1	; Terminal 1 (Input)
SyncBuck_period:n:	.usect "Net_terminals",1 		; Period value

				;Publish Terminal Pointers for access from the C environment
				;-----------------------------------------------------------
				.def 	_SYNCBUCK_In:n:

	; set terminal to point to ZeroNet
	MOVL	XAR2, #ZeroNet
	MOVW	DP, #_SYNCBUCK_In:n:
	MOVL	@_SYNCBUCK_In:n:, XAR2

	MOVW 	DP,#TBPRD:n:>>6
	MOV		ACC, @TBPRD:n:
	LSL		ACC,#1						; used instead of PM shift of 1
	MOVW	DP,#SyncBuck_period:n:
	MOV		@SyncBuck_period:n:, ACC	; SyncBuck_period=(TBPRDn x 2)
			.endm

;-------------------------------------
SYNCBUCK_DRV	.macro	n
;-------------------------------------
	MOVW	DP, #_SYNCBUCK_In:n:
	MOVL 	XAR0,@_SYNCBUCK_In:n:	; Net pointer for In	(XAR0)
	MOVL 	XAR1,#CMPA:n:			; point to Compare A	(XAR1)

	; Output for EPWMnA
	MOV 	T,*XAR0
	MPYU 	ACC,T,@SyncBuck_period:n:
	MOV 	*XAR1,AH				; output value to CMPAn
			.endm

			
			