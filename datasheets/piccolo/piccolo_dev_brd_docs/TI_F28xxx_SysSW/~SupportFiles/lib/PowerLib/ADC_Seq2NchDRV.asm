;----------------------------------------------------------------------------------
;	FILE:			ADC_Seq2NchDRV.ASM
;
;	Description:	ADC Result register interface macro
;
;	Version: 		1.0
;
;   Target:  		TMS320F280xx
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2008
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  03/07/08	| Release 1.0  		Created
;--------------------------------------------------------------------------------
		
;============================================================================
;	ADC_Seq2NchDRV  Macro module (uses ADC mirror regs in PF0)
;============================================================================
;			______________________
;			|	  ADC_NchDRV	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 <--| Rslt[8:15]   Rslt-8 |<-- Conv8
;		 	|		  	   Rslt-9 |<-- Conv9
;		 	|		  	      "   |
;		 	|		  	      "   |
;		 	|		  	  Rslt-15 |<-- Conv15
;			|_____________________|
;
;	Rslt[8:15] is a pointer to a Signal Net Bus (up to 8 consecutively addressed Nets)
;
; Description:
; ------------
; ADC peripheral Driver interface.
; Assumes address of 1st Net Bus Address is in Rslt
;
;============================
ADC_Seq2NchDRV_INIT	.macro n
;============================
; Variable Definitions
_ADC_Rslt_seq2			.usect "Net_terminals",2,1,1		; Output Terminal 1

;Publish Terminal Pointers for access from the C environment (optional)
;======================================================================
					.def 	_ADC_Rslt_seq2

		; macro code starts here
	MOVL	XAR2, #DummyNet			; set terminal to point to ZeroNet
	MOVW	DP, #_ADC_Rslt_seq2
	MOVL	@_ADC_Rslt_seq2, XAR2
					.endm

;=========================
ADC_Seq2NchDRV		.macro	n
;=========================
; uses PF0 (0WS mem)
	MOVW	DP, #_ADC_Rslt_seq2
	MOVL 	XAR0,@_ADC_Rslt_seq2			; XAR0: pointer to Net Bus (SEQ2 Results)

	MOVW	DP,#ADCPF0R0>>6
	MOVL 	XAR1,#(ADCPF0R0+8)			; XAR1: pointer to ADC buffer regs

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

	.endm

