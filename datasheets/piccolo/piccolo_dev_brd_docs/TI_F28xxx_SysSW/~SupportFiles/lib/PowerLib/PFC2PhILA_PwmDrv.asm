;================================================================================
;	PFC2PhILA_DRV  	Power Factor Correction 2 phase interleaved with Adjust
;================================================================================
;	FILE:			PFC2PhIL_PwmDrv.asm
;
;	Description:	Power Factor Correction 2 phase interleaved
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
;			|	 PFC2PhILA_DRV	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| Duty		   EPWM1A |--> (PFC Phase A switch)
;		 	| 		  	     	  |
;		 -->| Adj	  	   EPWM2A |--> (PFC Phase B switch)
;			|_____________________|
;
;	Duty, Adj, are pointers to signal nets.
;   Peripheral Resources used: EPWM1 and EPWM2 modules
;
; Description:
; ------------
; PWM peripheral Driver interface for PFC 2 phase interleaved modulation
; Buck converter peripheral Driver interface
; n = 1, 2, 3, ... 16
;
;================================================================================
;-------------------------------------
PFC2PhILA_DRV_INIT	.macro	n
;-------------------------------------
; Variable Declarations
_PFC2Ph_In:n:		.usect "PFCIL_data",2,1,1	; Input Terminal 1
_PFC2Ph_Adj:n:		.usect "PFCIL_data",2 		; Input Terminal 2
PFC_period:n:		.usect "PFCIL_data",1 		; PFC full period count value
pfc_temp:n:			.usect "PFCIL_data",1 		; temp storage value

				;Publish Terminal Pointers for access from the C environment
				;-----------------------------------------------------------
				.def 	_PFC2Ph_In:n:
				.def 	_PFC2Ph_Adj:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PFC2Ph_In:n:
			MOVL	@_PFC2Ph_In:n:, XAR2
			MOVL	@_PFC2Ph_Adj:n:, XAR2

			MOVW 	DP,#TBPRD:n:>>6
			MOV		ACC, @TBPRD:n:
			MOVW	DP,#PFC_period:n:
			MOV		@PFC_period:n:, ACC			;pfc_period=(Timer:n: Period)
					.endm

;-------------------------------------
PFC2PhILA_DRV		.macro	n
;-------------------------------------
			MOVW	DP, #_PFC2Ph_In:n:
			MOVL 	XAR1,@_PFC2Ph_In:n:			; Net pointer to Duty (XAR1)
			MOVL 	XAR2,@_PFC2Ph_Adj:n:		; Net pointer to Adj (XAR2)

			MOVL 	XAR3,#CMPA:n:				; Pointer to CMPA:n:
;			MOVL 	XAR3,#CMPA2					; Pointer to CMPA:n+1:
	
	; Normalize and update Phase A duty cycle comparator
			MOV 	T,*XAR1
			MPY 	ACC,T,@PFC_period
			LSL		ACC,#1
			MOV 	*XAR3,AH					; Write to CMPA1

	; Update Phase B duty cycle comparator
			
		; Adjust the phase B duty cycle using the offset calculated elsewhere
			MOV 	ACC,*XAR1<<9				; Acc = In * 512
			ADD 	ACC,*XAR2<<9				; Acc = (In + Adj) * 512

		; Normalize and update Phase B duty cycle comparator
;			MOV 	T,@pfc_temp				; load "adjusted" duty in T
			MOV 	T,*XAR4
			MPY 	ACC,T,@PFC_period
			LSL		ACC,#1
			MOV 	*XAR3,AH				; Write to CMPA2
					.endm


