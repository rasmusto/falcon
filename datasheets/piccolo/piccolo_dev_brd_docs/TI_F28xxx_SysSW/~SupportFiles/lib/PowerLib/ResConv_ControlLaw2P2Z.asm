;----------------------------------------------------------------------------------
;	FILE:			ControlLaw2P2Z.h
;
;	Description:	2nd Order Control Law Macro Module, based on IIR filter structure
;
;	Version: 		1.0
;
;   Target:  		TMS320F28xx 
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2007
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date	     | Description
;----------------------------------------------------------------------------------
;  12/04/05  | Release 1.0  		New release with pointer to coefficients.
;  05/25/05  | Release 1.1  		u(n) clamped before storing as history
;----------------------------------------------------------------------------------

;============================================================================
;	Control Law Macro module - 2 Pole / 2 Zero compensator
;============================================================================
;			______________________
;			|	ControlLaw_2P2Z	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| Ref			  	  |
;			|				  Out |-->
;		 -->| Fdbk			  	  |
;			|					  |
;		 <--| Coef			  	  |
;			|_____________________|
;
;		Ref, Fdbk, Coef, Out: pointers to Signal Nets
;
; Description:
; ------------
; Performs a second order difference equation of the form:
;
;       		B2 z^-2 + B1 z^-1 + B0
; U(z)/E(z) = --------------------------
;       		-A2 z^-2 - A1 z^1 + 1	
;
; u(n)= A1*u(n-1)+A2*u(n-2)+B0*e(n)+B1*e(n-1)+B2*e(n-2)
;
; where	u(n-1) => output from last sample cycle
;		u(n-2) => output from 2 samples past
;		e(n)   => present error
;		e(n-1) => error from last sample cycle
;		e(n-2) => error from 2 samples past
;
;		|--------|
;		| u(n-1) |0  CNTL_2P2Z_DBUFF
;		|--------|
;		| u(n-2) |2
; 		|--------|	
;		|  e(n)  |4	
;		|--------|	
;		| e(n-1) |6
;		|--------|
;		| e(n-2) |8
;		|--------|
;
;====================================
ControlLaw_2P2Z_INIT	.macro n
;====================================
; Variable Declarations
_CNTL_2P2Z_Ref:n:	.usect "Controller",2,1,1		; Input Terminal 1
_CNTL_2P2Z_Fdbk:n:	.usect "Controller",2 			; Input Terminal 2
_CNTL_2P2Z_Out:n:	.usect "Controller",2 			; Output Terminal
_CNTL_2P2Z_Coef:n:	.usect "Controller",2 			; Pointer to filter Coefficients
CNTL_2P2Z_DBUFF:n: 	.usect "Controller",10			; "Local" memory (history) 
DMAX:n: 			.usect "Controller",2			; "Local" Max clamp on ADC
DMIN:n: 			.usect "Controller",2			; "Local" Min clamp on ADC

;Publish Terminal Pointers for access from the C environment (optional)
					.def 	_CNTL_2P2Z_Ref:n:
					.def 	_CNTL_2P2Z_Fdbk:n:
					.def 	_CNTL_2P2Z_Out:n:
					.def 	_CNTL_2P2Z_Coef:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_CNTL_2P2Z_Ref:n:
			MOVL	@_CNTL_2P2Z_Ref:n:, XAR2
			MOVL	@_CNTL_2P2Z_Fdbk:n:, XAR2
			MOVL	@_CNTL_2P2Z_Coef:n:, XAR2
			MOVL	XAR2, #DummyNet
			MOVL	@_CNTL_2P2Z_Out:n:, XAR2

		; Zero the Data Buffer (10 locations)
			MOVL 	XAR2,#CNTL_2P2Z_DBUFF:n:
			RPT		#9 ; 10 times
			||MOV	*XAR2++, #0
						.endm

;====================================
ControlLaw_2P2Z		.macro n
;====================================

; Set up address pointers:
	MOVW	DP, #_CNTL_2P2Z_Ref:n:
	MOVL 	XAR0, @_CNTL_2P2Z_Ref:n:	; Net pointer to Ref (XAR0) **opto linear
	MOVL 	XAR1, @_CNTL_2P2Z_Fdbk:n:	; Net pointer to Fdbk(XAR1) **opto linear
	MOVL 	XAR2, @_CNTL_2P2Z_Out:n:	; Net pointer to Out (XAR2)
	MOVL    XAR3, @_CNTL_2P2Z_Coef:n:	; Net pointer to Coefficients (XAR3)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0<<11				; ACC = Ref		 	(Q15 to Q26)
	SUB		ACC, *XAR1<<11				; ACC = Ref - Fdbk 	(Q15 to Q26)
	MOVL	@CNTL_2P2Z_DBUFF:n:+4, ACC	; e(n) = ACC = error (Q26)
		
; Calculate 2p-2z filter:	Note: IIR engine is Q independent
	MOVL	XT, @CNTL_2P2Z_DBUFF:n:+8	; XT  = e(n-2)
	QMPYL	P, XT, *XAR3++				; P   = e(n-2)*B2
	MOVB	ACC, #0						; ACC = 0
	MOVDL	XT, @CNTL_2P2Z_DBUFF:n:+6	; XT  = e(n-1), e(n-2) = e(n-1)
	QMPYAL	P, XT, *XAR3++ 				; P   = e(n-1)*B1, ACC=e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF:n:+4	; XT  = e(n), e(n-1) = e(n) 
	QMPYAL	P, XT, *XAR3++ 				; P   = e(n)*B0, ACC = e(n-2)*B2 + e(n-1)*B1
	MOVL	XT, @CNTL_2P2Z_DBUFF:n:+2	; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2, ACC = e(n-2)*B2 + e(n-1)*B1 + e(n)*B0
	MOVDL	XT, @CNTL_2P2Z_DBUFF:n:+0	; XT  = u(n-1), u(n-2) = u(n-1)
	QMPYAL	P, XT, *XAR3++ 				; P   = u(n-1)*A1, ACC = e(n-2)*B2 + e(n-1)*B1 + e(n)*B0 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + e(n)*B0 + u(n-2)*A2 + u(n-1)*A1

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26)
	MAXL	ACC, *XAR3 					; Saturate to > 0.000000.. in (Q26)
	MOVL	@CNTL_2P2Z_DBUFF:n:, ACC	; u(n-1) = u(n) = ACC (Q26)

; move to Uout as a Q15
	LSL 	ACC, #1 					; Convert from Q26 to Q31
	MOV		*XAR2, AH					; Output Duty (Q15) to terminal net
			.endm