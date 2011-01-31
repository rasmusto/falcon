;----------------------------------------------------------------------------------
;	FILE:			Rectifier_MiscDrv.ASM
;
;	Description:	Contains s/w drivers for SLEW_LIMIT, PFC_ICMD, INV_SQR and some other modules
;					that are not being used
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
; 12 Mar-08  | Release 0.1			PFC2PHIL Internal release (HRN)
;----------------------------------------------------------------------------------

;----------------------------------------------------------------------------------


;==================================================================================
;	SLEW_LIMIT module
;==================================================================================
;			______________________
;			|	   SLEW_LIMIT	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In			   	  |
;		 	|	 			  Out |-->
;		 -->| Incr		  		  |
;			|_____________________|
;
;			In, Incr, Out: pointers to Signal Nets
;
; Description:
; ------------
; Function to control slewrate. 
;
; Change History:
;-------------------------------------------------------------------------------
; Date		| Description
;-------------------------------------------------------------------------------
; 01/20/04	| Original
; 05/05/04	| Modified for Signal Net interface & converted to Macro
; 06/27/06  | Fixed bug reported against v1.0 re. roll overs.
; ______________________________________________________________________________

;===============================================================================
SLEW_LIMIT_INIT	.macro x
;=======================
; Variable Definitions
_SLEW_LIMIT_In:x:	.usect "SL_data",2,1,1		; Input Terminal 1
_SLEW_LIMIT_Incr:x:	.usect "SL_data",2 			; Input Terminal 2
_SLEW_LIMIT_Out:x:	.usect "SL_data",2 			; Output Terminal


;Publish Terminal Pointers for access from the C environment (optional)
;======================================================================
					.def 	_SLEW_LIMIT_In:x:				
					.def 	_SLEW_LIMIT_Incr:x:				
					.def 	_SLEW_LIMIT_Out:x:				

		; actual macro code starts here
		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_SLEW_LIMIT_In:x:
			MOVL	@_SLEW_LIMIT_In:x:, XAR2
			MOVL	@_SLEW_LIMIT_Incr:x:, XAR2
			MOVL	@_SLEW_LIMIT_Out:x:, XAR2

				.endm

;=======================
SLEW_LIMIT		.macro x
;=======================

	.if(!NET_DEBUG) ; i.e. normal operation
			MOVW	DP, #_SLEW_LIMIT_In:x:
			MOVL 	XAR4, @_SLEW_LIMIT_In:x:	; Net pointer to In (XAR4)
			MOVL 	XAR5, @_SLEW_LIMIT_Incr:x:	; Net pointer to Incr (XAR5)
			MOVL 	XAR6, @_SLEW_LIMIT_Out:x:	; Net pointer to Out (XAR6)

			MOV		ACC, *XAR4<<16				; load the setpoint
			SUB		ACC, *XAR6<<16				; compare with the latest output command
			B		SS_DONE? ,EQ				; if EQ, setpoint = previous output already.  Just exit.
			SETC	TC							; Going to use the TC bit for positive slewing.
			B		LEAVE_BIT?, LT
			CLRC	TC							; ACC was negative, clear the TC bit.
LEAVE_BIT?
			ABS		ACC							; Asking for this much change.
			MIN		AH, *XAR5					; Limit change to Incr.
			B		INCREASE_CMD?, NTC			; if difference was positive, slew command up
REDUCE_CMD?										; else diff is negative, slew command down
			NEG		ACC							; for negative slewing just invert amount to add. 
INCREASE_CMD?
			ADD		ACC, *XAR6<<16				; Add in limited, sign correct change in value
			MOV		*XAR6, AH					; Store to output.
SS_DONE?

	.endif ; !NET_DEBUG

	; Used for debug only - checks module connectivity.
	.if(NET_DEBUG)
			MOV 	ACC,*XAR4					; Move Ref directly to Out
			MOV		*XAR6, AL					; i.e. "In" to "Out" bypass
	.endif ; NET_DEBUG

				.endm

;============================================================================
;	PFC_ICMD  Macro module - PFC Current Command
;============================================================================
;			______________________
;			|	   PFC_ICMD	  	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| V1			  	  |
;		 -->| V2			  Out |-->
;		 -->| Vac			  	  |
;			|_____________________|
;
;			V1, V2, Vac, Out: pointers to Signal Nets
;
; Description:
; ------------
; Calclulates the PFC current loop command according to:
;
;	Out = V1*V2*Vac*Km
;
;	Where:	V1 is the output of the Voltage controller Q15
;			V2 is the inverse of the Average AC line, squared
;			Vac is the instantaneous value of the AC line
;			Km is a constant = Vmax/Vmin
;
; Revision History:
;-------------------------------------------------------------------------------
; Date		| Author	| Description
;-------------------------------------------------------------------------------
; 01/26/04	| DSZ		| Original
; 06/06/04	| DAF		| Modified for Signal Net interface & converted to Macro
; 03/15/05	| DSZ		| Verification
; 06/27/06  | KAG       | Rescaled and fixed some of the math with PFC proto board.
; 04/14/08	| HRN		| Fixed the Max/Min Current command values and VMAX/VMIN
; ______________________________________________________________________________
;============================
PFC_ICMD_INIT		.macro x
;============================
; Constant Definitions
;VMAX_OVER_VMIN		.set  	0x3000			; 33V/11V = 3.000 in 4.12  
;VMAX_OVER_VMIN		.set  	0x36F0			; 48Vpk/13.98Vpk (Ratio of Peaks) = 3.433 in Q12  
VMAX_OVER_VMIN		.set  	0x34A6			; 46Vpk/13.98Vpk (Ratio of Peaks) = 3.290 in Q12  
MAX_CURRENT_CMDH	.set 	0x0800	 		; MAX Q27 
MAX_CURRENT_CMDL	.set	0x0000
MIN_CURRENT_CMDH	.set 	0x0000	 		; MIN Q27
MIN_CURRENT_CMDL	.set	0x0000

; Variable Declarations
_PFC_ICMD_V1:x:			.usect "PIC_data",2,1,1		; Input Terminal 1
_PFC_ICMD_V2:x:			.usect "PIC_data",2 		; Input Terminal 2
_PFC_ICMD_Vac:x:		.usect "PIC_data",2 		; Input Terminal 3
_PFC_ICMD_Out:x:		.usect "PIC_data",2 		; Output Terminal 1
MaxCurrentCmd:x:		.usect "PIC_data",2			; "Local" memory Long
MinCurrentCmd:x:		.usect "PIC_data",2			; "Local" memory Long
VmaxOverVmin:x:			.usect "PIC_data",1			; "Local" memory

;Publish Terminal Pointers for access from the C environment (optional)
;======================================================================
					.def 	_PFC_ICMD_V1:x:
					.def 	_PFC_ICMD_V2:x:
					.def 	_PFC_ICMD_Vac:x:
					.def 	_PFC_ICMD_Out:x:

		; actual macro code starts here
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PFC_ICMD_V1:x:
			MOVL	@_PFC_ICMD_V1:x:, XAR2
			MOVL	@_PFC_ICMD_V2:x:, XAR2
			MOVL	@_PFC_ICMD_Vac:x:, XAR2
			MOVL	@_PFC_ICMD_Out:x:, XAR2

			MOV		@VmaxOverVmin:x:,    #VMAX_OVER_VMIN

			MOV		@MaxCurrentCmd:x:,   #MAX_CURRENT_CMDL
			MOV		@MaxCurrentCmd:x:+1, #MAX_CURRENT_CMDH

			MOV		@MinCurrentCmd:x:,   #MIN_CURRENT_CMDL
			MOV		@MinCurrentCmd:x:+1, #MIN_CURRENT_CMDH

				.endm

;=======================
PFC_ICMD		.macro x
;=======================
			MOVW	DP, #_PFC_ICMD_V1:x:
			MOVL 	XAR3,@_PFC_ICMD_V1:x:		; Net pointer to V1 (XAR3)
			MOVL 	XAR4,@_PFC_ICMD_V2:x:		; Net pointer to V2 (XAR4)
			MOVL 	XAR5,@_PFC_ICMD_Vac:x:		; Net pointer to Vac (XAR5)
			MOVL 	XAR6,@_PFC_ICMD_Out:x:		; Net pointer to Out (XAR6)

	.if(!NET_DEBUG) ; i.e. normal operation

			MOV 	T,*XAR3						; T = V1
			MPY		ACC,T,*XAR4					; ACC = V1*V2  Q15*Q15=Q30
			NORM 	ACC,*						; ACC now in Q31
			MOV		*XAR6,AH					; temporarily save to Out as Q15
			MOV		T,*XAR6						;
		
			MPY		ACC,T,*XAR5					; ACC = V1*V2*Vac  Q15*Q15=Q30
			NORM 	ACC,*						; ACC now in Q31
			MOV		*XAR6, AH					; temporarily save as Q15
			MOV		T, *XAR6
			MPY		ACC,T,@VmaxOverVmin:x:		; Q27 ACC = [V1*V2*Vac]*Km Q15*Q12
		
		; Saturate the result [0,1]
			MINL 	ACC,@MaxCurrentCmd:x:					
			MAXL 	ACC,@MinCurrentCmd:x:
			LSL		ACC,#4						; Convert to Q31	
			MOV		*XAR6,AH					; Save result as a Q15

	.endif ; !NET_DEBUG

	; Used for debug only - checks module connectivity.
	.if(NET_DEBUG)
			MOV 	ACC,*XAR3			; Mov V1 directly to Out
			MOV		*XAR6, AL			; i.e. "V1" to "Out" bypass
	.endif ; NET_DEBUG

				.endm


;============================================================================
;	INV_SQR  Macro module - Inverse Squared function
;============================================================================
;			______________________
;			|	 	INV_SQR	      |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In			  Out |-->
;			|_____________________|
;
;			In, Out: pointers to Signal Nets
;
; Description:
; ------------
; Performs Inverse Squared function.  The Average AC line value can be derived
; upstream by a filtering function, e.g. EMA_AVG.
;
; Revision History:
;-------------------------------------------------------------------------------
; Date		| Author	| Description
;-------------------------------------------------------------------------------
; 01/26/04	| DSZ		| Original
; 04/29/04	| DAF		| Modified for Signal Net interface & converted to Macro
; 03/16/06  | KAG       | Fixed endian convention and some other errors in 
;           |           | INV_AVG
; ______________________________________________________________________________
;===============================================================================
INV_SQR_INIT		.macro x
;===========================
; Below constants are application dependent.
; Copy the lines below to your application file (where this module is used)
; and set to an appropriate value.
;-------------------------------------------------------------------------------
;VMIN_OVER_VMAXH	.set 	0x0000	; 12V/36V Long in Q15 format
;VMIN_OVER_VMAXL	.set	0x2a30
;MIN_AVG_ACLINE		.set	0x1B22		; Q15 format, 51V full scale

PI_OVER2_Q14	.set	0x6488

; Variable Declarations
_INV_SQR_In:x:		.usect "ISQR_data",2,1,1	; Input Terminal 1
_INV_SQR_Out:x:		.usect "ISQR_data",2 		; Output Terminal 1
INV_LongTemp:x:		.usect "ISQR_data",2 		; "local" memory - Long
VminOverVmax:x:		.usect "ISQR_data",2		; "Local" memory - Long
INV_SQR_Temp:x:		.usect "ISQR_data",1 		; "Local" memory

;Publish Terminal Pointers for access from the C environment (optional)
;======================================================================
					.def 	_INV_SQR_In:x:		
					.def 	_INV_SQR_Out:x:

			MOVW	DP, #_INV_SQR_In:x:
			MOV		@_INV_SQR_In:x:, #0
			MOV		@(_INV_SQR_In:x:+1), #0
			MOV		@_INV_SQR_Out:x:, #0
			MOV		@(_INV_SQR_Out:x:+1), #0

			MOV		@VminOverVmax:x:,   #VMIN_OVER_VMAXL
			MOV		@VminOverVmax:x:+1, #VMIN_OVER_VMAXH

					.endm

;=======================
INV_SQR			.macro x
;=======================
		MOVW	DP, #_INV_SQR_In:x:
		MOVL 	XAR3,@_INV_SQR_In:x:			; Net pointer to In (XAR3)
		MOVL 	XAR4,@_INV_SQR_Out:x:			; Net pointer to Out (XAR4)

	.if(!NET_DEBUG) ; i.e. normal operation
		
	; Clamp the minimum Average AC Line to allow the normalization to work
	; at very low inputs. i.e. using a Variac during debug.
		MOV 	ACC,*XAR3						; ACC = "In"
		MOV		@INV_SQR_Temp:x:, AL
		SUB 	ACC,#MIN_AVG_ACLINE
		B 		LINE_INRANGE:x:,GEQ				; if ACC>=0 don't clamp
		MOV		ACC,#MIN_AVG_ACLINE				; if ACC<0 clamp to a minimum
		MOV		@INV_SQR_Temp:x:,AL				; temporarily store it
							
LINE_INRANGE:x::		
	; Renormalize the Average AC Line measurement to it's own max by multiplying by pi/2
		MOV		ACC,@INV_SQR_Temp:x:<<16			; reload the clamped value
		MPY		ACC,@INV_SQR_Temp:x:,#PI_OVER2_Q14	; Q15*Q14 = Q29
		LSL		ACC,#2								; shift into Q15
		MOV		@INV_SQR_Temp:x:,AH					; temporarily store it
		
	; Calculate 1/In^2 --> do divide
	; Numerator of 1/period is treated as a Q31 value, result of this
	; division is in Q16(=Q31/Q15)
  		CLRC    TC								; Clear TC flag, used as sign flag	
		MOV		ACC,#07FFFh						; AH = 0, AL = high 16-bits of Numerator
  		RPT     #15		
  		||SUBCU ACC,@INV_SQR_Temp:x:			; Conditional subtract with period_cntr(denominator)	
		MOV     @INV_LongTemp:x:+1,AL			; Store higher 16-bit of the result				
		MOV		AL,#0FFFFh						; AL = low 16-bits of Numerator(32-bit)
  		RPT     #15	
  		||SUBCU ACC,@INV_SQR_Temp:x:			; Conditional subtract with period_cntr(denominator)
  		MOV     ACC,@AL << 16					; AH = low 16-bits of the result, AL = 0	
		MOV     @INV_LongTemp:x:,AH				; Store lower 16-bit of the result		
			
	; Renormalize the Inverse Avg AC Line measurement to it's own max by multiplying by Vmin/Vmax
		MOVL	XT,@INV_LongTemp:x:				; Multiply Inverse of In value by Vmin/Vmax in Q15
		IMPYL	ACC,XT,@VminOverVmax:x:			; Q16*Q15 = Q31

	; Now Square 1/In		
		MOVL	@INV_LongTemp:x:,ACC			; inv_avgAC now has Q31 result
		MOVL	XT,@INV_LongTemp:x:
		QMPYL	ACC,XT,@INV_LongTemp:x:			; square inv_avgAC, ACC has Q30
		NORM 	ACC,*
		MOV	    *XAR4,AH						; save as Q15 to output Net		
	.endif ; !NET_DEBUG

	; Used for debug only - checks module connectivity.
	.if(NET_DEBUG)
			MOV 	ACC,*XAR3					; Mov In directly to Out
			MOV		*XAR4, AL					; i.e. "In" to "Out" bypass
	.endif ; NET_DEBUG

				.endm



;============================================================================
;	AC_LINE_RECT  Macro module - Absolute value function
;============================================================================
;			______________________
;			|	  AC_LINE_RECT	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In			  Out |-->
;			|_____________________|
;
;			In, Out: pointers to Signal Nets
;
; Description:
; ------------
; Rectifies input AC line
;
; Change History:
;-------------------------------------------------------------------------------
; Date		| Author	| Description
;-------------------------------------------------------------------------------
; 01/20/04	| Zendzian	| Original
; 05/05/04	| DAF		| Modified for Signal Net interface & converted to Macro
; ______________________________________________________________________________
;===============================================================================
AC_LINE_RECT_INIT	.macro x
;===========================
; Variable Definitions
_AC_LINE_RECT_In:x:		.usect "ALR_data",2,1,1		; Input Terminal 1
_AC_LINE_RECT_Out:x:	.usect "ALR_data",2 		; Output Terminal 1

;Publish Terminal Pointers for access from the C environment 
;======================================================================
			.def 	_AC_LINE_RECT_In:x:				
			.def 	_AC_LINE_RECT_Out:x:				

		; actual macro code starts here
			MOVW	DP, #_AC_LINE_RECT_In:x:
			MOV		@_AC_LINE_RECT_In:x:, #0
			MOV		@(_AC_LINE_RECT_In:x:+1), #0
			MOV		@_AC_LINE_RECT_Out:x:, #0
			MOV		@(_AC_LINE_RECT_Out:x:+1), #0
					.endm

;=======================
AC_LINE_RECT	.macro x
;=======================
			MOVW	DP, #_AC_LINE_RECT_In:x:
			MOVL 	XAR4,@_AC_LINE_RECT_In:x:		; Net pointer to In (XAR4)
			MOVL 	XAR5,@_AC_LINE_RECT_Out:x:		; Net pointer to Out (XAR5)


	.if(!NET_DEBUG) ; i.e. normal operation
			MOV 	ACC,*XAR4<<16					;left justify inside ACC
			
		; Rectify the filtered AC Line sample by taking Absolute Value														
			ABS 	ACC
			MOV 	*XAR5,AH						;Output ABS value			
	.endif ; !NET_DEBUG


	; Used for debug only - checks module connectivity.
	.if(NET_DEBUG)
			MOV 	ACC,*XAR4			; Mov Ref directly to Out
			MOV		*XAR5, AL			; i.e. "In" to "Out" bypass
	.endif ; NET_DEBUG

				.endm


;============================================================================
;	PFC_OVP  Macro module - PFC Over Voltage Protection
;============================================================================
;			______________________
;			|	 	PFC_OVP	  	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| In			  Out |-->
;			|					  |
;		 -->| Vmon			  	  |
;			|_____________________|
;
;			In, Vmon, Out: pointers to Signal Nets
;
; Description:
; ------------
; Monitors Input for Over-voltage conditions (i.e. S/W Over-voltage Protection)
; Clamp the input to the multiplier to zero if the feedback is over the OVP
; threshold.
;		
; Revision History:
;-------------------------------------------------------------------------------
; Date		| Author	| Description
;-------------------------------------------------------------------------------
; 01/20/04	| Zendzian	| Original
; 05/06/04	| DAF		| Modified for Signal Net interface & converted to Macro
; ______________________________________________________________________________
;===========================
PFC_OVP_INIT	.macro x
;===========================
; Constant Definitions
PFC_FIXED_VCMD			.set   	0x51B5	; Q15 600 Volts full scale
OVP_TRIP_THOLD			.set 	0x6888	; set trip threshold to 40% high	
OVP_RECOVER_THOLD		.set	PFC_FIXED_VCMD

; Variable Declarations
_PFC_OVP_In:x:		.usect "POVP_data",2,1,1		; Input Terminal 1
_PFC_OVP_Vmon:x:	.usect "POVP_data",2 			; Input Terminal 2
_PFC_OVP_Out:x:		.usect "POVP_data",2 			; Output Terminal 1
PFC_OVP_State:x:	.usect "POVP_data",1 			; Local Memory (history)

;Publish Terminal Pointers for access from the C environment (optional)
;======================================================================
					.def 	_PFC_OVP_In:x:				
					.def 	_PFC_OVP_Vmon:x:				
					.def 	_PFC_OVP_Out:x:				

		; actual macro code starts here
			MOVW	DP, #_PFC_OVP_In:x:
			MOV		@_PFC_OVP_In:x:, #0
			MOV		@(_PFC_OVP_In:x:+1), #0
			MOV		@_PFC_OVP_Vmon:x:, #0
			MOV		@(_PFC_OVP_Vmon:x:+1), #0
			MOV		@_PFC_OVP_Out:x:, #0
			MOV		@(_PFC_OVP_Out:x:+1), #0
			MOV		@PFC_OVP_State:x:, #0

					.endm

;=======================
PFC_OVP			.macro x
;=======================
			MOVW	DP, #_PFC_OVP_In:x:
			MOVL 	XAR4,@_PFC_OVP_In:x:			; Net pointer to In (XAR4)
			MOVL 	XAR5,@_PFC_OVP_Vmon:x:		; Net pointer to Out (XAR5)
			MOVL 	XAR6,@_PFC_OVP_Out:x:		; Net pointer to Out (XAR6)

	.if(!NET_DEBUG) ; i.e. normal operation

			MOV 	ACC,*XAR4					; mov "In" directly to "Out" 
			MOV		*XAR6, AL					;  initially, clamp later if req'd
		; Check if already in OVP tripped state
			MOV		ACC,@PFC_OVP_State:x:<<16
			B 		OVP_NORMAL?, EQ 			; if ovp_state=0, then normal
OVP_TRIPPED?
			MOV 	ACC,*XAR5					; Load Vmon input value				
			SUB 	ACC,#OVP_RECOVER_THOLD
			B 		CLAMP_MINPUT?, GT			; if fdbk-thold>0 remain clamped
			MOV		@PFC_OVP_State:x:, #0			; set OVP state to normal=0
			B 		PFC_OVP_EXIT?, UNC			; update multiplier			
OVP_NORMAL?
			MOV 	ACC,*XAR5				
			SUB 	ACC,#OVP_TRIP_THOLD
			B 		PFC_OVP_EXIT?, LT			; if fdbk-thold<0 use loop output
			MOV		@PFC_OVP_State:x:, #1		; set OVP state to tripped=1			
CLAMP_MINPUT?
			MOV		*XAR6, #0					; Clamp output to zero			
PFC_OVP_EXIT?
			NOP		; Not sure if NOP is needed?

	.endif ; !NET_DEBUG


	; Used for debug only - checks module connectivity.
	.if(NET_DEBUG)
			MOV 	ACC,*XAR4			; Mov In directly to Out
			MOV		*XAR6, AL			; i.e. "In" to "Out" bypass
	.endif ; NET_DEBUG

				.endm


;============================================================================
;	PFC_ISHARE  Macro module - PFC Current share
;============================================================================
;			______________________
;			|	   PFC_ISHARE  	  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| Ia			  	  |
;			|				  Out |-->
;		 -->| Ib			  	  |
;			|_____________________|
;
;			Ia, Ib, Out: pointers to Signal Nets
;
; Description:
; ------------
; Calclulates the PFC interleaved current share adjustment. at 1/500th the 
; calling rate; at 50kHz ==> 100Hz.
; Phase currents can be filtered "up-steam" at the calling rate using
; a Box Car averager, i.e. module BOX_CAR_AVG
;
; Revision History:
;-------------------------------------------------------------------------------
; Date		| Author	| Description
;-------------------------------------------------------------------------------
; 02/20/04	| DSZ		| Original
; 04/29/04	| DAF		| Modified for Signal Net interface & converted to Macro
; ______________________________________________________________________________
;===============================================================================
PFC_ISHARE_INIT	.macro x
;===========================
; Constant Definitions
MAX_ISHARE_ADJH		.set 	0x07FF	 		; MAX Q27
MAX_ISHARE_ADJL		.set	0xFFFF
MIN_ISHARE_ADJH		.set 	0x0000	 		; MAX Q27
MIN_ISHARE_ADJL		.set	0x0000
ISHARE_GAIN			.set	0x0FFF			; Proportional gain constant in Q12 format
EXECUTION_PSCALE	.set	500				; Execution rate pre-scale amount

; Variable Declarations
_PFC_ISHARE_Ia:x:		.usect "PIS_data",2,1,1		; Input Terminal 1
_PFC_ISHARE_Ib:x:		.usect "PIS_data",2 		; Input Terminal 2
_PFC_ISHARE_Out:x:		.usect "PIS_data",2 		; Output Terminal 1
MaxIShareAdj:x:			.usect "PIS_data",2			; "Local" memory Long
MinIShareAdj:x:			.usect "PIS_data",2			; "Local" memory Long
IshareCntr:x:			.usect "PIS_data",1			; "Local" memory
PFC_ISHARE_Temp:x:		.usect "PIS_data",1 		; "Local" memory

;Publish Terminal Pointers for access from the C environment (optional)
;======================================================================
					.def 	_PFC_ISHARE_Ia:x:		
					.def 	_PFC_ISHARE_Ib:x:
					.def 	_PFC_ISHARE_Out:x:

		; actual macro code starts here
			MOVW	DP, #_PFC_ISHARE_Ia:x:
			MOV		@_PFC_ISHARE_Ia:x:, #0
			MOV		@(_PFC_ISHARE_Ia:x:+1), #0
			MOV		@_PFC_ISHARE_Ib:x:, #0
			MOV		@(_PFC_ISHARE_Ib:x:+1), #0
			MOV		@_PFC_ISHARE_Out:x:, #0
			MOV		@(_PFC_ISHARE_Out:x:+1), #0

;NOTE: Need to check the "endian" convention here
			MOV		@MaxIShareAdj:x:, #MAX_ISHARE_ADJH
			MOV		@MaxIShareAdj:x:+1, #MAX_ISHARE_ADJL
			MOV		@MinIShareAdj:x:, #MIN_ISHARE_ADJH
			MOV		@MinIShareAdj:x:+1, #MIN_ISHARE_ADJL

					.endm

;=======================
PFC_ISHARE		.macro x
;=======================
			MOVW	DP, #_PFC_ISHARE_Ia:x:
			MOVL 	XAR3,@_PFC_ISHARE_Ia:x:			; Net pointer to Ia (XAR3)
			MOVL 	XAR4,@_PFC_ISHARE_Ib:x:			; Net pointer to Ib (XAR4)
			MOVL 	XAR5,@_PFC_ISHARE_Out:x:		; Net pointer to Ib (XAR5)

	.if(!NET_DEBUG) ; i.e. normal operation

; Check the loop counter and execute the algorithm at 1/EXECUTION_PSCALE the calling freq.
			MOV		ACC,@IshareCntr:x:
			ADD		ACC,#1
			MOV 	@IshareCntr:x:,AL
			SUB 	ACC, #EXECUTION_PSCALE
			B 		ISHARE_DONE?,LT 		; Skip share if ACC<0				
			MOV		@IshareCntr:x:,#0		; reset counter

; Execute the Share Algorithm			
			MOV 	ACC,*XAR3
			SUB 	ACC,*XAR4				; ACC = Difference in PFC Phase currents
			MOV 	@PFC_ISHARE_Temp:x:,AL	
			MPY 	ACC,@PFC_ISHARE_Temp:x:,#ISHARE_GAIN

; Saturate the result [0,1] and output value via Out terminal
			MINL 	ACC,@MaxIShareAdj:x:
			MAXL 	ACC,@MinIShareAdj:x:
			LSL		ACC,#4					; put back into Q15 format						

			MOV		*XAR5, AH
		
ISHARE_DONE?		
		NOP

	.endif ; !NET_DEBUG


	; Used for debug only - checks module connectivity.
	.if(NET_DEBUG)
			MOV 	ACC,*XAR3			; Mov Ia directly to Out
			MOV		*XAR5, AL			; i.e. "Ia" to "Out" bypass
	.endif ; NET_DEBUG

				.endm








