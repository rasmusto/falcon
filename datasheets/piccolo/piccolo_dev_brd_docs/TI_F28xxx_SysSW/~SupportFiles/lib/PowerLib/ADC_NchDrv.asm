;----------------------------------------------------------------------------------
;	FILE:			ADC_NchDrv.ASM
;
;	Description:	ADC Result register interface macro
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
;	ADC_NchDRV  Macro module (uses ADC mirror regs in PF0)
;============================================================================
;			______________________
;			|	  ADC_NchDRV	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 <--| Rslt[0:15]   Rslt-0 |<-- Conv0
;		 	|		  	   Rslt-2 |<-- Conv1
;		 	|		  	      "   |
;		 	|		  	      "   |
;		 	|		  	  Rslt-15 |<-- Conv15
;			|_____________________|
;
;	Rslt[0:15] is a pointer to a Signal Net Bus (up to 16 consecutively addressed Nets)
;
; Description:
; ------------
; ADC peripheral Driver interface.
; Assumes address of 1st Net Bus Address is in Rslt
;
;============================
ADC_NchDRV_INIT	.macro n
;============================
; Variable Definitions
_ADC_Rslt			.usect "Net_terminals",2,1,1		; Output Terminal 1

;Publish Terminal Pointers for access from the C environment (optional)
;======================================================================
					.def 	_ADC_Rslt

		; macro code starts here
	MOVL	XAR2, #DummyNet			; set terminal to point to ZeroNet
	MOVW	DP, #_ADC_Rslt
	MOVL	@_ADC_Rslt, XAR2
					.endm

;=========================
ADC_NchDRV		.macro	n
;=========================
; uses PF0 (0WS mem)
	MOVW	DP, #_ADC_Rslt
	MOVL 	XAR0,@_ADC_Rslt			; XAR0: pointer to Net Bus

	MOVW	DP,#ADCPF0R0>>6
	MOVL 	XAR1,#ADCPF0R0			; XAR1: pointer to ADC buffer regs

	; Read Result0 		   (1st conversion)
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input

	.if(n>1); Read Result1 (2nd conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>2); Read Result2 (3rd conversion)
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>3); Read Result3 (4th conversion)
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>4); Read Result4 (5th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>5); Read Result5 (6th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>6); Read Result6 (7th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>7); Read Result7 (8th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>8); Read Result8 (9th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>9); Read Result9 (10th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>10); Read Result10 (11th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>11); Read Result11 (12th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>12); Read Result12 (13th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>13); Read Result13 (14th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>14); Read Result14 (15th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.if(n>15); Read Result15 (16th conversion)		
	MOV 	ACC,*XAR1++<<3
	MOV 	*XAR0++,AL				; Q15 format, Unipolar input
	.endif

	.endm

