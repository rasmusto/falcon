;================================================================================
;	PFC2PhILHR_DRV  Power Factor Correction 2 phase interleaved with HiRes
;================================================================================
;	FILE:			PFC2PhILHR_PwmDrv.asm
;
;	Description:	Power Factor Correction 2 phase interleaved with HiRes
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
;  08/22/07	| Release 1.0  		New release.
;--------------------------------------------------------------------------------
;			______________________
;			|	PFC2PhILHR_DRV	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In		   EPWM1A |--> (PFC Phase A switch)
;		 	| 		  	     	  |
;		    |   	  	   EPWM2A |--> (PFC Phase B switch)
;			|_____________________|
;
;	In, is a pointer to signal nets.
;   Peripheral Resources used: EPWM(n) and EPWM(n+1) modules
;
; Description:
; ------------
; PWM peripheral Driver interface for PFC 2 phase interleaved modulation
; using HiResolution PWM feature
; n = 1, 2, 3, ... 16
;
;================================================================================
;-------------------------------------
PFC2PhILHR_DRV_INIT	.macro	n
;-------------------------------------
; Variable Declarations
_PFC2Ph_In:n:		.usect "Net_terminals",2,1,1	; Input Terminal 1
PFC_period:n:		.usect "Net_terminals",1 		; PFC full period count value
_HRSF:n:			.usect "Net_terminals",1 		; HR Scale factor for EPWMn

				;Publish Terminal Pointers for access from the C environment
				;-----------------------------------------------------------
				.def 	_PFC2Ph_In:n:
				.def 	_HRSF:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PFC2Ph_In:n:
			MOVL	@_PFC2Ph_In:n:, XAR2

			MOVW 	DP,#TBPRD:n:>>6
			MOV		ACC, @TBPRD:n:
			MOVW	DP,#PFC_period:n:
			MOV		@PFC_period:n:, ACC		; PFC_period=(Timer:n: Period)
			MOV		@_HRSF:n:, #(70*256)	; Initial HiRes value for 100MHz case
					.endm

;-------------------------------------
PFC2PhILHR_DRV		.macro	n
;-------------------------------------
			MOVW	DP, #_PFC2Ph_In:n:
			MOVL 	XAR1,@_PFC2Ph_In:n:		; Net pointer to In (XAR1)
			MOVL 	XAR2,#CMPAHR:n:			
	
		; Output for EPWM(n)A (Hi Res)		
			MOV 	T,*XAR1
			MPYU 	ACC,T,@PFC_period:n:
			MOV		T,@_HRSF:n:
			MPYU	P,T,@AL                 ; P = T * AL
			MOVH	@AL,P
			ADD		ACC, #0x17F				; Optimize by Round up
			MOVL	*XAR2,ACC 				; CMPA:CMPAHR(31:8) = ACC
		; Output for EPWM(n+1)A (Hi Res)		
			ADDB	XAR2, #0x40				; Point to next EPWM module
			MOVL 	*XAR2,ACC				; output Duty to CMPA:CMPAHR(n+1)
					.endm


