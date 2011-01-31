;================================================================================
;	PFC2PHIL_OneEPwmChDrv Power Factor Correction 2 phase interleaved with Adjust
;================================================================================
;	FILE:			PFC2PHIL_OneEPwmChDrv.asm
;
;	Description:	Power Factor Correction 2 phase interleaved
;
;	Version: 		1.0
;   Target:  		TMS320F280xx
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2008
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  03/13/08	| Release 1.0  		New release.
;--------------------------------------------------------------------------------
;			______________________
;			|PFC2PHIL_OneEPwmChDrv|
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| Duty		   EPWM1A |--> (PFC Phase A switch)
;		 	| 		  	     	  |
;		 -->| Adj	  	   EPWM1B |--> (PFC Phase B switch)
;			|_____________________|
;
;	Duty, Adj, are pointers to signal nets.
;   Peripheral Resources used: EPWM1 module
;
; Description:
; ------------
; PWM peripheral Driver interface for PFC 2 phase interleaved modulation
; n = 1, 2, 3, ... 16
;
;================================================================================
;-------------------------------------
PFC2PHIL_OneEPwmChDrv_INIT	.macro	nEPWMChannel
;==========================
; Variable Declarations
_PFC2PHIL_ONECH_Duty	.usect "PFCIL_data",2,1,1	; Input Terminal 1
_PFC2PHIL_ONECH_Adj		.usect "PFCIL_data",2 		; Input Terminal 2
pfc_onech_period		.usect "PFCIL_data",1 		; PFC full period count value
pfc_onech_temp			.usect "PFCIL_data",1 		; temp storage value


;Publish Terminal Pointers for access from the C environment
;===========================================================
					.def 	_PFC2PHIL_ONECH_Duty
					.def 	_PFC2PHIL_ONECH_Adj

		; actual macro code starts here
		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PFC2PHIL_ONECH_Duty
			MOVL	@_PFC2PHIL_ONECH_Duty, XAR2
			MOVL	@_PFC2PHIL_ONECH_Adj, XAR2

			MOVW 	DP,#TBPRD:nEPWMChannel:>>6
			MOV		ACC, @TBPRD:nEPWMChannel:
			MOVW	DP,#pfc_onech_period
			ADD		ACC, #1
			MOV		@pfc_onech_period, ACC		;pfc_period=(Timer2 Period)
					.endm

;======================
PFC2PHIL_OneEPwmChDrv	.macro	nEPWMChannel
;======================
			MOVW	DP, #_PFC2PHIL_ONECH_Duty
			MOVL 	XAR4,@_PFC2PHIL_ONECH_Duty		; Net pointer to Duty (XAR4)
			MOVL 	XAR5,@_PFC2PHIL_ONECH_Adj		; Net pointer to Adj (XAR5)

			MOVL 	XAR2,#CMPA:nEPWMChannel:		; Pointer to EPWM1-CMPA compare reg (XAR2)
			MOVL 	XAR3,#CMPB:nEPWMChannel:		; Pointer to EPWM2-CMPA compare reg (XAR3)
	
	; Normalize and update Phase A duty cycle comparator
			MOV 	T,*XAR4
			MPY 	ACC,T,@pfc_onech_period
			LSL		ACC,#1
			MOV 	*XAR2,AH					; Write to CMPA1

	; Update Phase B duty cycle comparator
			
		; Adjust the phase B duty cycle using the offset calculated elsewhere
			MOV 	AH, #07fffh
			MOV		AL, #0ffffh
			SUB 	AH, *XAR4				; Acc = Duty * 512
			SUB 	AH, *XAR5				; Acc = (Duty + Adj) * 512
			MOV		@pfc_onech_temp, AH

		; Normalize and update Phase B duty cycle comparator
			MOV 	T,@pfc_onech_temp
			MPY 	ACC,T,@pfc_onech_period
			LSL		ACC,#1
			MOV 	*XAR3,AH				; Write to CMPA2
			
				.endm


