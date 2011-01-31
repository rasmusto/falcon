;================================================================================
;	MPhIL_DRV n, N  	MultiPhase Interleaved Buck PWM 
;================================================================================
;	FILE:			MPhIL_PwmDrv.asm
;
;	Description:	MultiPhase Interleaved Buck PWM 
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
;				|	  MPhIL_DRV	  	  |
;				|~~~~~~~~~~~~~~~~~~~~~|
;			 	| 		     EPWM(n)A |--> (phase1)
;			 	| 		  	     	  |
;			 -->| In	   EPWM(n+1)A |--> (phase2)
;			 	| 		  	   :  	  |
;			 	| 		  	   : 	  |
;			 	| 		 EPWM(n+N-1)A |--> (phaseN)
;				|_____________________|
;
; Description:
; ------------
; PWM peripheral Driver Configuration for Multiphase interleaved modulation
; n = 1st ePWM module (i.e. Master)
; N = number of phases, depends on device.  For 2808 N=6 max, 28044 N=16 max
; e.g. if n=2, N=3, then  ePWM2 (phase1), ePWM3 (phase2), ePWM4 (phase3)
;
;================================================================================
;-------------------------------------
MPhIL_DRV_INIT	.macro	n, N
;-------------------------------------
; Variable Declarations
_MPhIL_In:n:		.usect "Net_terminals",2,1,1	; Input Terminal 1
MP_period:n:		.usect "Net_terminals",1 		; MPIL period value

				;Publish Terminal Pointers for access from the C environment
				;-----------------------------------------------------------
				.def 	_MPhIL_In:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_MPhIL_In:n:
			MOVL	@_MPhIL_In:n:, XAR2

			MOVW 	DP,#TBPRD:n:>>6
			MOV		ACC, @TBPRD:n:
			MOVW	DP,#MP_period:n:
			MOV		@MP_period:n:, ACC		;MP_period=TBPRD1
				.endm

;-------------------------------------
MPhIL_DRV		.macro	n, N
;-------------------------------------
			MOVW	DP, #_MPhIL_In:n:
			MOVL 	XAR3,@_MPhIL_In:n:	; Net pointer for Duty (XAR3)
			MOVL 	XAR2,#CMPA:n:			; point to Compare An  (XAR2)

; Output same Duty value to all phases			
			MOV 	T,*XAR3
			MPY 	ACC,T,@MP_period:n:
			LSL		ACC,#1
			;phase 1
			MOV 	*XAR2,AH				; output Duty to CMPA(n)

	.if(N>1);phase 2
			ADDB	XAR2, #0x40				; Point to next EPWM module
			MOV 	*XAR2,AH				; output Duty to CMPA(n+1)
	.endif

	.if(N>2);phase 3
			ADDB	XAR2, #0x40				; Point to next EPWM module
			MOV 	*XAR2,AH				; output Duty to CMPA(n+2)
	.endif

	.if(N>3);phase 4
			ADDB	XAR2, #0x40				; Point to next EPWM module
			MOV 	*XAR2,AH				; output Duty to CMPA(n+3)
	.endif

	.if(N>4);phase 5
			ADDB	XAR2, #0x40				; Point to next EPWM module
			MOV 	*XAR2,AH				; output Duty to CMPA(n+4)
	.endif

	.if(N>5);phase 6
			ADDB	XAR2, #0x40				; Point to next EPWM module
			MOV 	*XAR2,AH				; output Duty to CMPA(n+5)
	.endif
				.endm
