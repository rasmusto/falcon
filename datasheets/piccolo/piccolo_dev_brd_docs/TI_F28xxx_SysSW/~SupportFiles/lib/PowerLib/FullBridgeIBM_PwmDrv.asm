;--------------------------------------------------------------------------------
;	FILE:			FullBridgeIBM_PwmDrv.asm
;
;	Description:	Full Bridge PWM driver Macro with IBM method of modulation
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

;============================================================================
;	FullBridgeIBM_DRV  n   Macro module driver
;============================================================================
;			______________________
;			|  FullBridgeIBM_DRV  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In		   EPWMnA |--> (right leg upper switch)
;		 -->| delLL  	   EPWMnB |--> (right leg Lower switch)
;		 -->| delLR    EPWM(n+1)A |--> (left leg upper switch)
;		 	| 		   EPWM(n+1)B |--> (left leg Lower switch)
;			|_____________________|
;
;	duty, delLL, delLR, are pointers to signal nets.
;   Peripheral Resources used: EPWMn and EPWM(n+1) modules
;
; Description:
; ------------
;	In 		- ?
;	delLL	- ?
;	delLR	- ?
;
;=================================================================================
;=================================
FullBridgeIBM_DRV_INIT	.macro	n
;=================================
; Variable Declarations
_FBI_In:n:			.usect "Net_terminals",2,1,1	; Input Terminal 1
_FBI_delLL:n:		.usect "Net_terminals",2		; Input Terminal 2
_FBI_delLR:n:		.usect "Net_terminals",2		; Input Terminal 3
_FBI_HRSF:n:		.usect "Net_terminals",1 		; HR Scale factor for EPWMn
FBI_Period:n:		.usect "Net_terminals",1 		; Period value for EPWM(n) & (n+1)

;Publish Terminal Pointers for access from the C environment
;===========================================================
				.def 	_FBI_In:n:
				.def 	_FBI_delLL:n:
				.def 	_FBI_delLR:n:
				.def 	_FBI_HRSF:n:

		; set terminals to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_FBI_In:n:
			MOVL	@_FBI_In:n:, XAR2
			MOVL	@_FBI_delLL:n:, XAR2
			MOVL	@_FBI_delLR:n:, XAR2

			MOVW 	DP,#TBPRD:n:>>6
			MOV		ACC, @TBPRD:n:
			LSL		ACC,#1					; used instead of PM shift of 1
			MOVW	DP,#FBI_Period:n:
			MOV		@FBI_Period:n:, ACC		; Period=(TBPRDn x 2)
			MOV		@_FBI_HRSF:n:, #(70*256); Initial HiRes value for 100MHz case

				.endm

;=================================
FullBridgeIBM_DRV		.macro	n
;=================================
			MOVW	DP, #_FBI_In:n:
			MOVL 	XAR2,@_FBI_In:n:		; Net pointer for phase (XAR2)
			MOVL 	XAR3,@_FBI_delLL:n:		; Net pointer for Lower Left (XAR3)
			MOVL 	XAR4,@_FBI_delLR:n:		; Net pointer for Lower Right (XAR4)
			MOVL 	XAR5,#CMPAHR:n:			

; Duty Adjustment between UL(xB) and LL(xA)
			MOVW	DP, #_FBI_In:n:
			MOVL 	XAR2,@_FBI_In:n:		; Net pointer for Input  (XAR2)
			MOVL 	XAR5,#CMPAHR:n:			

		; Output for EPWM(n)A (Hi Res)		
			MOV 	T,*XAR2
			MPYU 	ACC,T,@FBI_Period:n:
			MOV		T,@_FBI_HRSF:n:
			MPYU	P,T,@AL                 ; P = T * AL
			MOVH	@AL,P
			ADD		ACC, #0x17F				; Optimize by Round up
			MOVL	*XAR5,ACC 				; CMPA:CMPAHR(31:8) = ACC
		; Output for EPWM(n+1)A (Hi Res)		
			ADDB	XAR5, #0x40				; Point to next EPWM module
			MOVL 	*XAR5,ACC				; output Duty to CMPA:CMPAHR(n+1)

; Delay Adjustment for Lower Left leg - module EPWM(n)
			MOVL 	XAR5,#DBRED:n:			; Point to DBRED in module EPWM(n)
			MOV		ACC, *XAR3				; Fetch Left leg delay value
			MOV		*XAR5, AL				; update DBRED(n)

; Delay Adjustment for Lower Right leg - module EPWM(n+1)
			ADDB	XAR5, #0x40				; Point to next EPWM module
			MOV		ACC, *XAR4				; Fetch Right leg delay value
			MOV		*XAR5, AL				; update DBRED(n+1)
				.endm

