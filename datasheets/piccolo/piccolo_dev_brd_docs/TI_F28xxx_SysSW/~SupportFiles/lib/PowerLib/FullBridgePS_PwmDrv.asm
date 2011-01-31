;--------------------------------------------------------------------------------
;	FILE:			FullBridgePS_PwmDrv.asm
;
;	Description:	Phase Shifted Full Bridge PWM driver macro
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
;	FullBridgePS_DRV  n   Macro module driver
;============================================================================
;			______________________
;			|  FullBridgePS_DRV   |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| phase		   EPWMnA |--> (right leg upper switch)
;		 -->| dbLeft  	   EPWMnB |--> (right leg Lower switch)
;		 -->| dbRight  EPWM(n+1)A |--> (left leg upper switch)
;		 	| 		   EPWM(n+1)B |--> (left leg Lower switch)
;			|_____________________|
;
;	phase, dbLeft, dbRight, are pointers to signal nets.
;   Peripheral Resources used: EPWMn and EPWM(n+1) modules
;
; Description:
; ------------
;	phase 	- phase relationship between EPWM(n) and EPWM(n+1)
;	dbLeft	- Left Leg deadband time between A and B outputs
;	dbRight	- Right Leg deadband time between A and B outputs
;
;=================================================================================
;=================================
FullBridgePS_DRV_INIT	.macro	n
;=================================
; Variable Declarations
_FBPS_phase:n:		.usect "Net_terminals",2,1,1	; Input Terminal 1
_FBPS_dbLeft:n:		.usect "Net_terminals",2		; Input Terminal 2
_FBPS_dbRight:n:	.usect "Net_terminals",2		; Input Terminal 3
FBPS_Period:n:		.usect "Net_terminals",1 		; EPWM(n) & EPWM(n+1) period value


;Publish Terminal Pointers for access from the C environment
;===========================================================
				.def 	_FBPS_phase:n:
				.def 	_FBPS_dbLeft:n:
				.def 	_FBPS_dbRight:n:

		; set terminals to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_FBPS_phase:n:
			MOVL	@_FBPS_phase:n:, XAR2
			MOVL	@_FBPS_dbLeft:n:, XAR2
			MOVL	@_FBPS_dbRight:n:, XAR2

			MOVW 	DP,#TBPRD:n:>>6			
			MOV		ACC, @TBPRD:n:				; fetch Period value set by C code
			LSR		AL,#1						; Div by 2
			MOVW	DP,#FBPS_Period:n:
			MOV		@FBPS_Period:n:, ACC		; Period=(TBPRD period value)/2
				.endm

;==========================
FullBridgePS_DRV		.macro	n
;==========================
			MOVW	DP, #_FBPS_phase:n:
			MOVL 	XAR2,@_FBPS_phase:n:	; Net pointer for phase (XAR2)
			MOVL 	XAR3,@_FBPS_dbLeft:n:	; Net pointer for dbLeft (XAR3)
			MOVL 	XAR4,@_FBPS_dbRight:n:	; Net pointer for dbRight (XAR4)

; Phase Adjustment between Left and Right Legs
			MOVL 	XAR5,#(TBPHS:n: + 0x40)	; Point to Phase register (n+1)
			MOV 	T,*XAR2
			MPY 	ACC,T,@FBPS_Period:n:
			LSL 	ACC,#1
			MOV 	*XAR5,AH

; Deadband Adjustment for Right leg (module EPWM(n+1) )
			MOVL 	XAR5,#(DBRED:n: + 0x40)	; Point to DBRED in module EPWM(N+1)
			MOV		ACC, *XAR4				; Fetch Right leg Deadband value
			MOV		*XAR5++, AL				; update DBRED(n+1)
			MOV		*XAR5, AL				; update DBFED(n+1)

; Deadband Adjustment for Left leg (module EPWMn)
			MOVL 	XAR5,#DBRED:n:			; Point to DBRED in module EPWMn
			MOV		ACC, *XAR3				; Fetch Left leg Deadband value
			MOV		*XAR5++, AL				; update DBREDn
			MOV		*XAR5, AL				; update DBFEDn
				.endm


