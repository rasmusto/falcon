;----------------------------------------------------------------------------------
;	FILE:			ResonantConv_PwmDrv.asm
;
;	Description:	Single channel Resonant PWM driver macro
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
;  11/08	| Release 1.0  		New release.
;--------------------------------------------------------------------------------

;================================================================================
;	ResonantConv_DRV  n  driver module - ePWM-A output s/w driver
;================================================================================
;			______________________
;			|	 ResonantConv_DRV |
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
; ResonantConv peripheral Driver interface
; n = 1, 2, 3, ... 16
;
;================================================================================
;=================================
ResonantConv_DRV_INIT		.macro	n
;=================================
; Variable Declarations
_Duty_In:n:			.usect "Net_terminals",2,1,1	; Input Terminal 1
_Period_In:n:		.usect "Net_terminals",2 		; Rsnt
_DB_In:n:			.usect "Net_terminals",1
BS_Period:n:		.usect "Net_terminals",1 		; EPWMn period value

;Publish Terminal Pointers for access from the C environment
;===========================================================
					.def 	_Duty_In:n:
					.def	_Period_In:n:	
					.def	_DB_In:n:
	; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_Duty_In:n:
			MOVL	@_Duty_In:n:, XAR2
			MOVL	@_Period_In:n:, XAR2
			MOVL	@_DB_In:n:, XAR2
		
	
		 	MOVW 	DP,#TBPRD:n:>>6
			MOV		ACC, @TBPRD:n:
			LSL		ACC,#1					; used instead of PM shift of 1
			MOVW	DP,#BS_Period:n:
			MOV		@BS_Period:n:, ACC		; Period=(TBPRDn x 2)
					.endm

;=========================
ResonantConv_DRV		.macro	n
;=========================
			MOVW	DP,#_Period_In:n:		;
			MOVL 	XAR3,@_Period_In:n:		;
			MOV		ACC,*XAR3				;
			MOVW 	DP,#TBPRD:n:>>6			;
			MOV		@TBPRD:n:,ACC			;Recent Period_In->TBPRD

			MOVW	DP, #_Duty_In:n:
			MOVL 	XAR0,@_Duty_In:n:		; Net pointer for InA	(XAR0)
			MOVL 	XAR1,#CMPA:n:			; point to Compare A	(XAR1)
			MOV 	T,*XAR0												  
			MPYU 	ACC,T,*XAR3 			; Period*DutyCycle->CMPA	  

			LSL		ACC,#1					; Period=(TBPRDn x 2)
			MOV 	*XAR1++,AH 				; output value to CMPAn

			LSR		AH,#1					; CMPB=CMPA/2 to set ISR trigger
			MOV 	*XAR1,AH 				; output value to CMPBn

			MOVL 	XAR4,@_DB_In:n:			; Update the deadband value
			MOV		ACC,*XAR4				; This part is not needed if constant DB is preferred
			MOVL 	XAR5,#DBRED:n:
			MOV		*XAR5++,ACC
			MOV		*XAR5,ACC
				.endm
