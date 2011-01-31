;----------------------------------------------------------------------------------
;	FILE:			BuckN8Loop.ASM
;
;	Description:	A selection (1 to N=8) of independent control loops.
;					Macro includes ADC, 2pole/2Zero compensator and ePWM driver
;
;	Version: 		1.0
;
;   Target:  		TMS320F280xx
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2007
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date	     | Description
;----------------------------------------------------------------------------------
;  29 Aug 07 | Release 0.1  		Uses Pre/Post calc method (DAF)
;----------------------------------------------------------------------------------
		.include "Eperipheral_registers.h"

;=================================================================================
;	BuckN8Loop_DRV  macro module - 1~8 channel Buck loops
;=================================================================================
;			______________________
;			|	 BuckN8Loop_DRV   |
;			|~~~~~~~~~~~~~~~~~~~~~|
;	  [N]-->| *Ref		   EPWMn  |--> 1A,2A,3A,4A,5A,6A,7A,8A
;		 	|_____________________|Ch= 1  2  3  4  5  6  7  8
;		 	|		  	     	  |
;	  [N]<--| *Out		   		  |
;		 	|		  	     	  |
;	  [N]-->| *CoefPtr1,2..6   	  |
;			|_____________________|
;
; Description:
; ------------
;	Note: This version is "Hardwired" to following EPWM outputs:
;		  1A,2A,3A,4A,5A,6A,7A,8A
;	*Ref -		Reference Inputs (up to 8), Q15, pointer to Net bus,
;				i.e. 8 consectutive memory locations, e.g. an Array
;
;	*Out -		Controller Outputs (up to 8), Q15, pointer to Net bus
;	*CoefPtrN -	Coefficient pointers (N=1..8), Q26, pointer to a coefficient Array
;====================================================================================

;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  I N I T - START  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;===============================
BuckN8Loop_DRV_INIT		.macro n
;===============================
; Variable Declarations
; Note: "Buck1Loop" - loops 1 to 4, is on 1st DP boundary
_Buck_Ref			.usect "Buck1Loop",2,1,1	; Input Terminal ptr to "Array Bus"
_Buck_Out			.usect "Buck1Loop",2 		; Output Terminal ptr to "Array Bus"
_Buck_CoefPtr1		.usect "Buck1Loop",2 		; Pointer to Coefficients Loop1
_Buck_CoefPtr2		.usect "Buck1Loop",2 		; Pointer to Coefficients Loop2
_Buck_CoefPtr3		.usect "Buck1Loop",2 		; Pointer to Coefficients Loop3
_Buck_CoefPtr4		.usect "Buck1Loop",2 		; Pointer to Coefficients Loop4
buck_period1		.usect "Buck1Loop",1 		; BUCK period value, used locally
												; Note: only one used, other is dummy
;_SFBUCKn			.usect "Buck1Loop",1 		; ScaleFactor for all Channels --> not used here
CNTL_2P2Z_DBUFF1 	.usect "Buck1Loop",10		; Controller history, used locally 
CNTL_2P2Z_DBUFF2 	.usect "Buck1Loop",10		; Controller history, used locally 
CNTL_2P2Z_DBUFF3 	.usect "Buck1Loop",10		; Controller history, used locally 
CNTL_2P2Z_DBUFF4 	.usect "Buck1Loop",10		; Controller history, used locally 

; Note: "Buck2Loop" - loops 5 to 8, is on 2nd DP boundary
buck_period2		.usect "Buck2Loop",2,1,1	; BUCK period, duplicate of buck_period1
_Buck_CoefPtr5		.usect "Buck2Loop",2 		; Pointer to Coefficients Loop5
_Buck_CoefPtr6		.usect "Buck2Loop",2 		; Pointer to Coefficients Loop6
_Buck_CoefPtr7		.usect "Buck2Loop",2 		; Pointer to Coefficients Loop7
_Buck_CoefPtr8		.usect "Buck2Loop",2 		; Pointer to Coefficients Loop8

CNTL_2P2Z_DBUFF5 	.usect "Buck2Loop",10		; Controller history, used locally 
CNTL_2P2Z_DBUFF6 	.usect "Buck2Loop",10		; Controller history, used locally 
CNTL_2P2Z_DBUFF7 	.usect "Buck2Loop",10		; Controller history, used locally 
CNTL_2P2Z_DBUFF8 	.usect "Buck2Loop",10		; Controller history, used locally 

;Publish Terminal Pointers for access from the C environment (optional)

					.def 	_Buck_Ref			; Pointer
					.def 	_Buck_Out			; Pointer
					.def 	_Buck_CoefPtr1		; Pointer
					.def 	_Buck_CoefPtr2		; Pointer
					.def 	_Buck_CoefPtr3		; Pointer
					.def 	_Buck_CoefPtr4		; Pointer
					.def 	_Buck_CoefPtr5		; Pointer
					.def 	_Buck_CoefPtr6		; Pointer
					.def 	_Buck_CoefPtr7		; Pointer
					.def 	_Buck_CoefPtr8		; Pointer
;					.def 	_SFBUCKn			; Variable

;For debug at this stage
					.def 	CNTL_2P2Z_DBUFF1	;

; set Input terminals to point to ZeroNet
	MOVW	DP, #_Buck_Ref
	MOVL	XAR2, #ZeroNet
	MOVL	@_Buck_Ref, XAR2
	MOVL	@_Buck_CoefPtr1, XAR2
	MOVL	@_Buck_CoefPtr2, XAR2
	MOVL	@_Buck_CoefPtr3, XAR2
	MOVL	@_Buck_CoefPtr4, XAR2
	MOVW	DP, #buck_period2
	MOVL	@_Buck_CoefPtr5, XAR2
	MOVL	@_Buck_CoefPtr6, XAR2
	MOVL	@_Buck_CoefPtr7, XAR2
	MOVL	@_Buck_CoefPtr8, XAR2

; set Output terminals to point to DummyNet
	MOVL	XAR2, #DummyNet
	MOVL	@_Buck_Out, XAR2

; Zero Data Buffer x 3 (i.e. 30 locations)	**May not need
	MOVL 	XAR2,#CNTL_2P2Z_DBUFF1
	RPT		#(:n:*10+3)
	||MOV	*XAR2++, #0

; Copy Period value set by Cnf function for Q15 to Q0 mapping
	MOVW 	DP,#TBPRD1>>6
	MOV		ACC, @TBPRD1
	LSL		ACC,#1						; used instead of PM shift of 1
	MOVW	DP,#buck_period1
	MOV		@buck_period1, ACC			; buck_period1=(TBPRDn x 2)
	MOVW	DP,#buck_period2
	MOV		@buck_period2, ACC			; buck_period2=(TBPRDn x 2)
; Used as starting value for HiRes ScaleFactor
;	MOV		@_SFBUCKn, #(70*256)		; Initial value for 100MHz case
					.endm

;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  R U N - START  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;========================
BuckN8Loop_DRV	.macro n
;========================
;================================  L O O P - 1  =======================================
; Set up address pointers: (30 cycles)
Loop1:
	;SETC    SXM,OVM
	MOVW	DP, #_Buck_Ref				; *****  FIRST DP BOUNDARY  *******
	MOVL 	XAR0, @_Buck_Ref			; Net "Bus" pointer to Ref in array (XAR0)
	MOVL 	XAR1, #ADCPF0R0				; Pointer to Fdbk, i.e. ADC Mirror regs (XAR1)
	MOVL 	XAR2, #CMPA1				; point to Compare 1A	(XAR2)
	MOVL    XAR3, @_Buck_CoefPtr1		; Net pointer to coefficients (XAR3)

	; For debug or to monitor Uout - comment to save cycle
	MOVL    XAR4, @_Buck_Out			; Net "Bus" pointer to Out in array (XAR4)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0++<<11			; ACC = Ref1		 (Q15 to Q26)
	SUB		ACC, *XAR1++<<14			; ACC = Ref1 - Fdbk1 (Q12 to Q26)	<-- ADC Result (8)
	MOVL	@CNTL_2P2Z_DBUFF1+4, ACC	; e(n) = ACC = error (Q26)

; Pre-calc portion of 2p-2z	filter
	MOVL	XT, ACC						; XT  = e(n)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n)*B0
	ADDL	ACC, @CNTL_2P2Z_DBUFF1+8	; ACC = e(n)*B0 + postcalc (for convenience use "e(n-2)" location)

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26) - Hi Lim
	MAXL	ACC, *XAR3++ 				; Saturate to > 0.000000.. in (Q26)	- Lo lim
	MOVL	@CNTL_2P2Z_DBUFF1, ACC		; u(n-1)<-- u(n) = ACC (Q26)
	LSL 	ACC, #5 					; Convert from Q26 to Q31 (Duty in Q31)
	; For debug or to monitor Uout - comment to save cycle
	MOV		*XAR4++, AH					; Output Duty (Q15) to terminal net

; Output to EPWM1A - Regular Res (3 cyc)
	MOV 	T,@AH						; Need only use upper 16 bits of Duty
	MPYU 	ACC,T,@buck_period1
	MOV 	*XAR2, AH					; output value to CMPA3
U1:
; Postcalc portion of 2p-2z filter: 	; Postcalc for next time = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	XT, @CNTL_2P2Z_DBUFF1+6		; XT  = e(n-2)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF1+4		; XT  = e(n-1),  e(n-2)<-- e(n-1)
	QMPYL	P, XT, *XAR3++ 				; P   = e(n-1)*B1,  ACC = e(n-2)*B2

	MOVL	XT, @CNTL_2P2Z_DBUFF1+2		; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2,  ACC = e(n-2)*B2 + e(n-1)*B1
	MOVDL	XT, @CNTL_2P2Z_DBUFF1+0		; XT  = u(n-1),  u(n-2)<-- u(n-1)
	QMPYAL	P, XT, *XAR3 				; P   = u(n-1)*A1,  ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	@CNTL_2P2Z_DBUFF1+8, ACC	; "e(n-2)" location is holding place for postcalc

;================================  L O O P - 2  =======================================
	.if(n>1);Loop2
Loop2:
; Set up address pointers: (26 cycles)
	MOVL 	XAR2, #CMPA2				; point to Compare 2A	(XAR2)
	MOVL    XAR3, @_Buck_CoefPtr2		; Local coefficient pointer (XAR3)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0++<<11			; ACC = Ref1		 (Q15 to Q26)
	SUB		ACC, *XAR1++<<14			; ACC = Ref1 - Fdbk1 (Q12 to Q26)	<-- ADC Result (4)
	MOVL	@CNTL_2P2Z_DBUFF2+4, ACC	; e(n) = ACC = error (Q26)
		
; Pre-calc portion of 2p-2z	filter
	MOVL	XT, ACC						; XT  = e(n)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n)*B0
	ADDL	ACC, @CNTL_2P2Z_DBUFF2+8	; ACC = e(n)*B0 + postcalc (for convenience use "e(n-2)" location)

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26) - Hi Lim
	MAXL	ACC, *XAR3++ 				; Saturate to > 0.000000.. in (Q26)	- Lo lim
	MOVL	@CNTL_2P2Z_DBUFF2, ACC		; u(n-1)<-- u(n) = ACC (Q26)
	LSL 	ACC, #5 					; Convert from Q26 to Q31 (Duty in Q31)
	; For debug or to monitor Uout - comment to save cycle
	MOV		*XAR4++, AH					; Output Duty (Q15) to terminal net

; Output to EPWM2A
	MOV 	T,@AH						; Need only use upper 16 bits of Duty
	MPYU 	ACC,T,@buck_period1
	MOV 	*XAR2, AH					; output value
U2:
; Postcalc portion of 2p-2z filter: 	; Postcalc for next time = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	XT, @CNTL_2P2Z_DBUFF2+6		; XT  = e(n-2)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF2+4		; XT  = e(n-1),  e(n-2)<-- e(n-1)
	QMPYL	P, XT, *XAR3++ 				; P   = e(n-1)*B1,  ACC = e(n-2)*B2

	MOVL	XT, @CNTL_2P2Z_DBUFF2+2		; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2,  ACC = e(n-2)*B2 + e(n-1)*B1
	MOVDL	XT, @CNTL_2P2Z_DBUFF2+0		; XT  = u(n-1),  u(n-2)<-- u(n-1)
	QMPYAL	P, XT, *XAR3 				; P   = u(n-1)*A1,  ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	@CNTL_2P2Z_DBUFF2+8, ACC	; "e(n-2)" location is holding place for postcalc
	.endif

;===============================   L O O P - 3  =======================================
	.if(n>2);Loop3
Loop3:
; Set up address pointers: (26 cycles)
	MOVL 	XAR2, #CMPA3				; point to Compare 3A	(XAR2)
	MOVL    XAR3, @_Buck_CoefPtr3		; Local coefficient pointer (XAR3)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0++<<11			; ACC = Ref1		 (Q15 to Q26)
	SUB		ACC, *XAR1++<<14			; ACC = e(n) = Ref1 - Fdbk1 (Q12 to Q26)	<-- ADC Result
	MOVL	@CNTL_2P2Z_DBUFF3+4, ACC	; Note: e(n) is really e(n-1) in post calc next sample period

; Pre-calc portion of 2p-2z	filter
	MOVL	XT, ACC						; XT  = e(n)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n)*B0
	ADDL	ACC, @CNTL_2P2Z_DBUFF3+8	; ACC = e(n)*B0 + postcalc (for convenience use "e(n-2)" location)

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26) - Hi Lim
	MAXL	ACC, *XAR3++ 				; Saturate to > 0.000000.. in (Q26)	- Lo lim
	MOVL	@CNTL_2P2Z_DBUFF3, ACC		; u(n-1)<-- u(n) = ACC (Q26)
	LSL 	ACC, #5 					; Convert from Q26 to Q31 (Duty in Q31)
	; For debug or to monitor Uout - comment to save cycle
	MOV		*XAR4++, AH					; Output Duty (Q15) to terminal net

; Output to EPWM3A
	MOV 	T,@AH						; Need only use upper 16 bits of Duty
	MPYU 	ACC,T,@buck_period1
	MOV 	*XAR2, AH					; output value
U3:
; Postcalc portion of 2p-2z filter: 	; Postcalc for next time = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	XT, @CNTL_2P2Z_DBUFF3+6		; XT  = e(n-2)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF3+4		; XT  = e(n-1),  e(n-2)<-- e(n-1)
	QMPYL	P, XT, *XAR3++ 				; P   = e(n-1)*B1,  ACC = e(n-2)*B2

	MOVL	XT, @CNTL_2P2Z_DBUFF3+2		; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2,  ACC = e(n-2)*B2 + e(n-1)*B1
	MOVDL	XT, @CNTL_2P2Z_DBUFF3+0		; XT  = u(n-1),  u(n-2)<-- u(n-1)
	QMPYAL	P, XT, *XAR3 				; P   = u(n-1)*A1,  ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	@CNTL_2P2Z_DBUFF3+8, ACC	; "e(n-2)" location is holding place for postcalc
	.endif

;================================  L O O P - 4  =======================================
	.if(n>3);Loop4
Loop4:
; Set up address pointers: (26 cycles)
	MOVL 	XAR2, #CMPA4				; point to Compare 4A	(XAR2)
	MOVL    XAR3, @_Buck_CoefPtr4		; Local coefficient pointer (XAR3)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0++<<11			; ACC = Ref1		 (Q15 to Q26)
	SUB		ACC, *XAR1++<<14			; ACC = Ref1 - Fdbk1 (Q12 to Q26)
	MOVL	@CNTL_2P2Z_DBUFF4+4, ACC	; e(n) = ACC = error (Q26)
		
; Pre-calc portion of 2p-2z	filter
	MOVL	XT, ACC						; XT  = e(n)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n)*B0
	ADDL	ACC, @CNTL_2P2Z_DBUFF4+8	; ACC = e(n)*B0 + postcalc (for convenience use "e(n-2)" location)

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26) - Hi Lim
	MAXL	ACC, *XAR3++ 				; Saturate to > 0.000000.. in (Q26)	- Lo lim
	MOVL	@CNTL_2P2Z_DBUFF4, ACC		; u(n-1)<-- u(n) = ACC (Q26)
	LSL 	ACC, #5 					; Convert from Q26 to Q31 (Duty in Q31)
	; For debug or to monitor Uout - comment to save cycle
	MOV		*XAR4++, AH					; Output Duty (Q15) to terminal net

; Output to EPWM4A
	MOV 	T,@AH						; Need only use upper 16 bits of Duty
	MPYU 	ACC,T,@buck_period1
	MOV 	*XAR2, AH					; output value
U4:
; Postcalc portion of 2p-2z filter: 	; Postcalc for next time = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	XT, @CNTL_2P2Z_DBUFF4+6		; XT  = e(n-2)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF4+4		; XT  = e(n-1),  e(n-2)<-- e(n-1)
	QMPYL	P, XT, *XAR3++ 				; P   = e(n-1)*B1,  ACC = e(n-2)*B2

	MOVL	XT, @CNTL_2P2Z_DBUFF4+2		; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2,  ACC = e(n-2)*B2 + e(n-1)*B1
	MOVDL	XT, @CNTL_2P2Z_DBUFF4+0		; XT  = u(n-1),  u(n-2)<-- u(n-1)
	QMPYAL	P, XT, *XAR3 				; P   = u(n-1)*A1,  ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	@CNTL_2P2Z_DBUFF4+8, ACC	; "e(n-2)" location is holding place for postcalc
	.endif

;================================  L O O P - 5  =======================================
	.if(n>4);Loop5
Loop5:
; Set up address pointers: (27 cycles)
	MOVW	DP, #buck_period2			; *****  SECOND DP BOUNDARY  *******
	MOVL 	XAR2, #CMPA5				; point to Compare 5A	(XAR2)
	MOVL    XAR3, @_Buck_CoefPtr5		; Local coefficient pointer (XAR3)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0++<<11			; ACC = Ref1		 (Q15 to Q26)
	SUB		ACC, *XAR1++<<14			; ACC = Ref1 - Fdbk1 (Q12 to Q26)
	MOVL	@CNTL_2P2Z_DBUFF5+4, ACC	; e(n) = ACC = error (Q26)
		
; Pre-calc portion of 2p-2z	filter
	MOVL	XT, ACC						; XT  = e(n)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n)*B0
	ADDL	ACC, @CNTL_2P2Z_DBUFF5+8	; ACC = e(n)*B0 + postcalc (for convenience use "e(n-2)" location)

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26) - Hi Lim
	MAXL	ACC, *XAR3++ 				; Saturate to > 0.000000.. in (Q26)	- Lo lim
	MOVL	@CNTL_2P2Z_DBUFF5, ACC		; u(n-1)<-- u(n) = ACC (Q26)
	LSL 	ACC, #5 					; Convert from Q26 to Q31 (Duty in Q31)
	; For debug or to monitor Uout - comment to save cycle
	MOV		*XAR4++, AH					; Output Duty (Q15) to terminal net

; Output to EPWM5A
	MOV 	T,@AH						; Need only use upper 16 bits of Duty
	MPYU 	ACC,T,@buck_period2
	MOV 	*XAR2, AH					; output value
U5:
; Postcalc portion of 2p-2z filter: 	; Postcalc for next time = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	XT, @CNTL_2P2Z_DBUFF5+6		; XT  = e(n-2)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF5+4		; XT  = e(n-1),  e(n-2)<-- e(n-1)
	QMPYL	P, XT, *XAR3++ 				; P   = e(n-1)*B1,  ACC = e(n-2)*B2

	MOVL	XT, @CNTL_2P2Z_DBUFF5+2		; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2,  ACC = e(n-2)*B2 + e(n-1)*B1
	MOVDL	XT, @CNTL_2P2Z_DBUFF5+0		; XT  = u(n-1),  u(n-2)<-- u(n-1)
	QMPYAL	P, XT, *XAR3 				; P   = u(n-1)*A1,  ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	@CNTL_2P2Z_DBUFF5+8, ACC	; "e(n-2)" location is holding place for postcalc
	.endif

;================================  L O O P - 6  =======================================
	.if(n>5);Loop6
Loop6:
; Set up address pointers: (26 cycles)
	MOVL 	XAR2, #CMPA6				; point to Compare 6A	(XAR2)
	MOVL    XAR3, @_Buck_CoefPtr6		; Local coefficient pointer (XAR3)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0++<<11			; ACC = Ref1		 (Q15 to Q26)
	SUB		ACC, *XAR1++<<14			; ACC = Ref1 - Fdbk1 (Q12 to Q26)
	MOVL	@CNTL_2P2Z_DBUFF6+4, ACC	; e(n) = ACC = error (Q26)
		
; Pre-calc portion of 2p-2z	filter
	MOVL	XT, ACC						; XT  = e(n)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n)*B0
	ADDL	ACC, @CNTL_2P2Z_DBUFF6+8	; ACC = e(n)*B0 + postcalc (for convenience use "e(n-2)" location)

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26) - Hi Lim
	MAXL	ACC, *XAR3++ 				; Saturate to > 0.000000.. in (Q26)	- Lo lim
	MOVL	@CNTL_2P2Z_DBUFF6, ACC		; u(n-1)<-- u(n) = ACC (Q26)
	LSL 	ACC, #5 					; Convert from Q26 to Q31 (Duty in Q31)
	; For debug or to monitor Uout - comment to save cycle
	MOV		*XAR4++, AH					; Output Duty (Q15) to terminal net

; Output to EPWM6A
	MOV 	T,@AH						; Need only use upper 16 bits of Duty
	MPYU 	ACC,T,@buck_period2
	MOV 	*XAR2, AH					; output value
U6:
; Postcalc portion of 2p-2z filter: 	; Postcalc for next time = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	XT, @CNTL_2P2Z_DBUFF6+6		; XT  = e(n-2)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF6+4		; XT  = e(n-1),  e(n-2)<-- e(n-1)
	QMPYL	P, XT, *XAR3++ 				; P   = e(n-1)*B1,  ACC = e(n-2)*B2

	MOVL	XT, @CNTL_2P2Z_DBUFF6+2		; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2,  ACC = e(n-2)*B2 + e(n-1)*B1
	MOVDL	XT, @CNTL_2P2Z_DBUFF6+0		; XT  = u(n-1),  u(n-2)<-- u(n-1)
	QMPYAL	P, XT, *XAR3 				; P   = u(n-1)*A1,  ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	@CNTL_2P2Z_DBUFF6+8, ACC	; "e(n-2)" location is holding place for postcalc
	.endif

;================================  L O O P - 7  =======================================
	.if(n>6);Loop7
Loop7:
; Set up address pointers: (26 cycles)
	MOVL 	XAR2, #CMPA7				; point to Compare 7A	(XAR2)
	MOVL    XAR3, @_Buck_CoefPtr7		; Local coefficient pointer (XAR3)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0++<<11			; ACC = Ref1		 (Q15 to Q26)
	SUB		ACC, *XAR1++<<14			; ACC = Ref1 - Fdbk1 (Q12 to Q26)
	MOVL	@CNTL_2P2Z_DBUFF7+4, ACC	; e(n) = ACC = error (Q26)
		
; Pre-calc portion of 2p-2z	filter
	MOVL	XT, ACC						; XT  = e(n)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n)*B0
	ADDL	ACC, @CNTL_2P2Z_DBUFF7+8	; ACC = e(n)*B0 + postcalc (for convenience use "e(n-2)" location)

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26) - Hi Lim
	MAXL	ACC, *XAR3++ 				; Saturate to > 0.000000.. in (Q26)	- Lo lim
	MOVL	@CNTL_2P2Z_DBUFF7, ACC		; u(n-1)<-- u(n) = ACC (Q26)
	LSL 	ACC, #5 					; Convert from Q26 to Q31 (Duty in Q31)
	; For debug or to monitor Uout - comment to save cycle
	MOV		*XAR4++, AH					; Output Duty (Q15) to terminal net

; Output to EPWM7A
	MOV 	T,@AH						; Need only use upper 16 bits of Duty
	MPYU 	ACC,T,@buck_period2
	MOV 	*XAR2, AH					; output value
U7:
; Postcalc portion of 2p-2z filter: 	; Postcalc for next time = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	XT, @CNTL_2P2Z_DBUFF7+6		; XT  = e(n-2)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF7+4		; XT  = e(n-1),  e(n-2)<-- e(n-1)
	QMPYL	P, XT, *XAR3++ 				; P   = e(n-1)*B1,  ACC = e(n-2)*B2

	MOVL	XT, @CNTL_2P2Z_DBUFF7+2		; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2,  ACC = e(n-2)*B2 + e(n-1)*B1
	MOVDL	XT, @CNTL_2P2Z_DBUFF7+0		; XT  = u(n-1),  u(n-2)<-- u(n-1)
	QMPYAL	P, XT, *XAR3 				; P   = u(n-1)*A1,  ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	@CNTL_2P2Z_DBUFF7+8, ACC	; "e(n-2)" location is holding place for postcalc
	.endif

;================================  L O O P - 8  =======================================
	.if(n>7);Loop8
Loop8:
; Set up address pointers: (26 cycles)
	MOVL 	XAR2, #CMPA8				; point to Compare 8A
	MOVL    XAR3, @_Buck_CoefPtr8		; Local coefficient pointer (XAR3)
		
; Calculate input (Ref - Fdbk):
	MOV		ACC, *XAR0++<<11			; ACC = Ref1		 (Q15 to Q26)
	SUB		ACC, *XAR1++<<14			; ACC = Ref1 - Fdbk1 (Q12 to Q26)
	MOVL	@CNTL_2P2Z_DBUFF8+4, ACC	; e(n) = ACC = error (Q26)
		
; Pre-calc portion of 2p-2z	filter
	MOVL	XT, ACC						; XT  = e(n)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n)*B0
	ADDL	ACC, @CNTL_2P2Z_DBUFF8+8	; ACC = e(n)*B0 + postcalc (for convenience use "e(n-2)" location)

; Scale u(n) Q20 to Q26, Saturate(1>u(n)>0), and save history
	LSL 	ACC, #6 					; ACC = Q26, based on Q26 coef & e(n)
	MINL	ACC, *XAR3++ 				; Saturate to < 0.999999.. in (Q26) - Hi Lim
	MAXL	ACC, *XAR3++ 				; Saturate to > 0.000000.. in (Q26)	- Lo lim
	MOVL	@CNTL_2P2Z_DBUFF8, ACC		; u(n-1)<-- u(n) = ACC (Q26)
	LSL 	ACC, #5 					; Convert from Q26 to Q31 (Duty in Q31)
	; For debug or to monitor Uout - comment to save cycle
	MOV		*XAR4++, AH					; Output Duty (Q15) to terminal net

; Output to EPWM8A
	MOV 	T,@AH						; Need only use upper 16 bits of Duty
	MPYU 	ACC,T,@buck_period2
	MOV 	*XAR2, AH					; output value
U8:
; Postcalc portion of 2p-2z filter: 	; Postcalc for next time = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	XT, @CNTL_2P2Z_DBUFF8+6		; XT  = e(n-2)
	QMPYL	ACC, XT, *XAR3++			; ACC = e(n-2)*B2
	MOVDL	XT, @CNTL_2P2Z_DBUFF8+4		; XT  = e(n-1),  e(n-2)<-- e(n-1)
	QMPYL	P, XT, *XAR3++ 				; P   = e(n-1)*B1,  ACC = e(n-2)*B2

	MOVL	XT, @CNTL_2P2Z_DBUFF8+2		; XT  = u(n-2)
	QMPYAL	P, XT, *XAR3++				; P   = u(n-2)*A2,  ACC = e(n-2)*B2 + e(n-1)*B1
	MOVDL	XT, @CNTL_2P2Z_DBUFF8+0		; XT  = u(n-1),  u(n-2)<-- u(n-1)
	QMPYAL	P, XT, *XAR3 				; P   = u(n-1)*A1,  ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2
	ADDL	ACC, @P						; ACC = e(n-2)*B2 + e(n-1)*B1 + u(n-2)*A2 + u(n-1)*A1
	MOVL	@CNTL_2P2Z_DBUFF8+8, ACC	; "e(n-2)" location is holding place for postcalc
	.endif
;=============================  E N D  L O O P S  =====================================
	.endm


