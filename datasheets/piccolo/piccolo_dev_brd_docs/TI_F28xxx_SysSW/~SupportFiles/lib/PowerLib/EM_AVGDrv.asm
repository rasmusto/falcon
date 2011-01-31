;----------------------------------------------------------------------------------
;	FILE:			EM_AVGDrv.ASM
;
;	Description:	Averaging Filter function via exponential moving average
;
;	Version: 		1.0
;
;   Target:  		TMS320F280x or F2833x
;
;	Type: 			Device dependent
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2004-2008                                			
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date	     | Description
;----------------------------------------------------------------------------------
; 12 Mar-08  | Release 0.1		PFC2PHIL Internal release (HRN)
; 06 May-08  | Release 1.0		PFC2PHIL Internal release (HRN)
;----------------------------------------------------------------------------------

;============================================================================
;	EMA Macro module - Exponential moving average (filter)
;============================================================================
;			______________________
;			|	  EMA        	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In			  Out |-->
;			|_____________________|
;
;		In, Out: pointers to Signal Nets
;
; Description:
; ------------
; Averaging Filter function via exponential moving average
; EMA(n) = (Data(n) - EMA(n-1))*MULTIPLER + EMA(n-1);
; Revision History:
;-------------------------------------------------------------------------------
; Date		| Author	| Description
;-------------------------------------------------------------------------------
; 08/19/05	| KAG		| Created new module 
; ______________________________________________________________________________
;============================
EM_AVG_INIT	.macro x
;============================
; Constant Definitions
;============================
; EMA_PERIOD is an application dependent constant.
; Copy the line below to your application file (where this macro module is used)
; and set to an appropriate value.
;
;EMA_PERIOD			.set 	16			 		 ; Set period to EMA
;

;Multiplier coeff used in equation: Q31
MULTIPLIER          .set    0x7fff/(1+EMA_PERIOD) 


; Variable Declarations
_EMA_In:x:		.usect "BCA_data",2,1,1		; Input Terminal 1
_EMA_Out:x:		.usect "BCA_data",2 		; Output Terminal 1

EMA_Avg:x:		.usect "BCA_data",2,1,1		; Exponential mov avg store
EMA_Temp:x:		.usect "BCA_data",2 		; Temp var
EMA_Mult:x: 	.usect "BCA_data",2			; Multipler


;Publish Terminal Pointers for access from the C environment (optional)
;======================================================================
				.def 	_EMA_In:x:
				.def 	_EMA_Out:x:

		; set terminals to point to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_EMA_In:x:
		MOVL	@_EMA_In:x:, XAR2
		MOVL	XAR2, #DummyNet
		MOVL	@_EMA_Out:x:, XAR2

		; Initialize the buffer pointer to the begining & clear counter
		MOV		@EMA_Avg:x:, #0
		MOV		ACC, #MULTIPLIER	; Store multipler
		MOVL	@EMA_Mult:x:, ACC	; Store multipler
		MOV		ACC, #0x00000000	; Store multipler
		MOVL	@EMA_Avg:x:, ACC
		MOVL	@EMA_Temp:x:, ACC
				.endm

; EMA(n) = (Data(n) - EMA(n-1))*MULTIPLER + EMA(n-1);
;========================
EM_AVG		.macro x
;========================
		MOVW	DP, #_EMA_In:x:
		MOVL 	XAR3,@_EMA_In:x:			; Net pointer to In  (XAR3)
		MOVL 	XAR4,@_EMA_Out:x:			; Net pointer to Out (XAR4)
		MOVL	XAR7,#EMA_Temp:x:

	.if(!NET_DEBUG) ; i.e. normal operation

; Load the buffers with the input					
		MOV 	ACC, *XAR3					; Fetch "In" value from Net		
		LSL		ACC,#16
		SUBL    ACC,@EMA_Avg:x:				; Compute the Data - EMA_Avg term

		SFR		ACC,#16
		MOVL  	*XAR7,ACC					; Store difference in EMA_temp

		MOVL	XT,@EMA_Mult:x:				; XT = Multipler
		IMPYL   ACC, XT, *XAR7			; Compute the product (diff)*MULTIPLIER

		ADDL	ACC, @EMA_Avg:x:			; Add the prev EMA to the product
; This above step is the key wherein we add the lower 16-bits of EMA_AVG.
; This way this algorithm will work even when the difference (DATA - EMA_AVG) is 
; less than 0x00010000/Multiplier
		
		MOVH	*XAR4, ACC					; Store output to net.
		
		MOVL	XAR7,#EMA_Avg:x:			; Point XAR7 to EMA_Avg
		MOVL	*XAR7, ACC             		; Store new EMA in EMA_Avg
		

	.endif ; !NET_DEBUG

	; Used for debug only - checks module connectivity.
	.if(NET_DEBUG)
		MOV 	ACC,*XAR3					; Mov In directly to Out
		MOV		*XAR4, AL					; i.e. "In" to "Out" bypass
	.endif ; NET_DEBUG

			.endm
