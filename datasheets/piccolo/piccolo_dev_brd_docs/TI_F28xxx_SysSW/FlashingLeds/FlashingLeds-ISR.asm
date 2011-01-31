;----------------------------------------------------------------------------------
;	FILE:			FlashingLeds-ISR.ASM
;
;	Description:	8 Output DC/DC closed loop control system, with ADC
;					s/w drivers, and a 2-pole/2-zero compensation/control law.
;
;	Version: 		1.0
;
;   Target:  		TMS320F280x / F2808
;
;	Type: 			Device Independent
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2004-2007
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date	     | Description
;----------------------------------------------------------------------------------
; 24 Apr-07  | Release 0.1  		8 Channel Internal release (DAF)
;----------------------------------------------------------------------------------

;----------------------------------------------------------------------------------

	;include Device specific PeripheralAddress_ASM
	;sets DSP_DEVICE for device specific ISR code and gives peripheral addresses
	.include "PeripheralAddress_ASM.h"

	;include C header file - sets INCR_BUILD (used in conditional builds)
	.cdecls C,NOLIST, "FlashingLeds-Settings.h"

	; MACRO includes
	.include "BuckSingle_PwmDrv.asm"


;**********************************************************************************
; Declare Public functions for External Reference
;**********************************************************************************
				.def 	_ISR_Init
				.def 	_ISR_Run

;**********************************************************************************
; Variable declaration
;**********************************************************************************	
tsPtr			.usect "Net_terminals",2

; All Terminal modules initially point to the ZeroNet to ensure a known
; start state. Pad extra locations to accomodate unwanted ADC results.
ZeroNet			.usect "Net_terminals",8,1,1
DummyNet	 	.usect "Net_terminals",7,1,1
IsrClkCtr		.usect "Net_terminals",1


				.text
;---------------------------------------------------------
; ISR Initialisation
;---------------------------------------------------------
_ISR_Init:

	; Clear the ZeroNet
	MOVL 	XAR2,#ZeroNet
	RPT		#7 ; 8 times
	||MOV	*XAR2++, #0

	;BuckSingle_DRV_INIT	1	; EPWM1A

	LRETR

	.sect "ramfuncs"

;---------------------------------------------------------
; ISR Run
;---------------------------------------------------------
_ISR_Run:	;(13 cycles to get to here from ISR trigger)

			;CONTEXT_SAVE
			PUSH AR1H:AR0H ; 32-bit
			PUSH XAR2 ; 32-bit
			PUSH XAR3 ; 32-bit
			PUSH XAR4 ; 32-bit
		;-- Comment these to save cycles --------
			PUSH XAR5 ; 32-bit
			PUSH XAR6 ; 32-bit
			PUSH XAR7 ; 32-bit
		;----------------------------------------
			PUSH XT	  ; 32-bit
			NOP		
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
; ALL TIME SLICES - Code executed every Interrupt
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	;BuckSingle_DRV	1			; EPWM1A


;===================================
EXIT_ISR
;===================================
; Interrupt management before exit
			MOVW 	DP,#ETCLR1>>6
			MOV 	@ETCLR1,#0x01			; Clear EPWM1 Int flag
			MOVW 	DP,#PIEACK>>6			; Acknowledge PIE interrupt Group 3
			MOV 	@PIEACK,#PIEACK_GROUP3

; Restore context & return
			;CONTEXT_REST
			POP XT
		;-- Comment these to save cycles ---
			POP XAR7
			POP XAR6
			POP XAR5
		;-----------------------------------
			POP XAR4
			POP XAR3
			POP XAR2
			POP AR1H:AR0H

			IRET						

