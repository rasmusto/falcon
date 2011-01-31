;***************************************************************
;* TMS320C2000 C/C++ Codegen                   PC Version 3.06 *
;* Date/Time created: Sun Apr 27 16:39:25 2003                 *
;***************************************************************
FP	.set	XAR2
	.file	"IQsample.c"

	.sect	".cinit"
	.align	1
	.field  	-2,16
	.field  	_GlobalQ+0,32
	.field  	24,32			; _GlobalQ @ 0

	.sect	".text"
	.global	_GlobalQ
_GlobalQ:	.usect	".ebss",2,1,1
	.sym	_GlobalQ,_GlobalQ, 5, 2, 32
	.global	_Step
_Step:	.usect	".ebss",18,1,1
	.sym	_Step,_Step, 8, 2, 288, _STEP
	.global	_Dlog
_Dlog:	.usect	".ebss",2048,1,1
	.sym	_Dlog,_Dlog, 8, 2, 32768, _DATA_LOG_C
;	C:\ti\c2000\cgtools\bin\opt2000.exe -m -v28 -q -O3 C:\DOCUME~1\a0875026\LOCALS~1\Temp\TI1204_2 C:\DOCUME~1\a0875026\LOCALS~1\Temp\TI1204_5 -w C:/tidcs/c28/IQmath/cIQmath/examples/F2812EzDSP_Sample/Debug 
;	C:\ti\c2000\cgtools\bin\ac2000.exe -@C:\DOCUME~1\a0875026\LOCALS~1\Temp\TI1204_4 

	.sect	".text"
	.global	_main
	.sym	_main,_main, 36, 2, 0
	.func	53

;***************************************************************
;* FNAME: _main                         FR SIZE:  32           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter, 24 Auto,  6 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
_main:
	.line	2
;* AR6   assigned to L$1
;* AR2   assigned to L$2
;* AR4   assigned to _WatchdogWDCR
	.sym	_WatchdogWDCR,12, 20, 4, 22
;* AR1   assigned to _tempMmax
	.sym	_tempMmax,6, 5, 4, 32
;* AL    assigned to _tempM
	.sym	_tempM,0, 5, 4, 32
;* AL    assigned to _tempP
	.sym	_tempP,0, 5, 4, 32
	.sym	_tempY,-26, 5, 1, 32
	.sym	_tempX,-24, 5, 1, 32
;* AR4   assigned to U$21
;* AR3   assigned to U$21
	.sym	_buffer,-22, 50, 1, 320,, 20
        MOVL      *SP++,XAR1
        MOVL      *SP++,XAR2
        MOVL      *SP++,XAR3
        ADDB      SP,#26
	.line	11
 EALLOW 
	.line	12
        MOVL      XAR4,#28713           ; |64| 
        MOV       *+XAR4[0],#104        ; |64| 
	.line	13
 EDIS 
	.line	15
        MOV       AH,#80
        MOV       AL,#27837
        MOVW      DP,#_Step
        MOVL      @_Step,ACC            ; |67| 
	.line	16
        MOV       AH,#80
        MOV       AL,#27837
        MOVL      @_Step+2,ACC          ; |68| 
	.line	17
        MOVB      ACC,#0
        MOVL      @_Step+4,ACC          ; |69| 
	.line	18
        MOVL      @_Step+6,ACC          ; |70| 
	.line	19
        MOVL      XAR4,#_Dlog
        MOVL      ACC,@_Step+4          ; |71| 
        MOVL      @_Step+8,ACC          ; |71| 
        MOVB      XAR6,#255
L1:    
	.line	23
        MOVB      ACC,#0
        MOVL      *+XAR4[0],ACC         ; |75| 
	.line	24
        MOVL      XAR0,#512             ; |76| 
        MOVL      *+XAR4[AR0],ACC       ; |76| 
	.line	25
        MOVL      XAR0,#1024            ; |77| 
        MOVL      *+XAR4[AR0],ACC       ; |77| 
	.line	26
        MOVL      XAR0,#1536            ; |78| 
        MOVL      *+XAR4[AR0],ACC       ; |78| 
	.line	27
        ADDB      XAR4,#2               ; |79| 
        BANZ      L1,AR6--              ; |79| 
        ; branch occurs ; |79| 
	.line	30
        MOVL      XAR4,#FSL1            ; |82| 
        MOVL      *-SP[2],XAR4          ; |82| 
        LCR       #_printf              ; |82| 
        ; call occurs [#_printf] ; |82| 
	.line	31
        MOVZ      AR4,SP                ; |83| 
        SUBB      XAR4,#22              ; |83| 
        LCR       #_gets                ; |83| 
        ; call occurs [#_gets] ; |83| 
	.line	32
        MOVZ      AR4,SP                ; |84| 
        SUBB      XAR4,#22              ; |84| 
        MOVB      ACC,#24
        LCR       #__atoIQN             ; |84| 
        ; call occurs [#__atoIQN] ; |84| 
        MOVW      DP,#_Step+10
        MOVL      @_Step+10,ACC         ; |84| 
	.line	33
        MOVL      ACC,@_Step+10         ; |85| 
        BF        L2,NEQ                ; |85| 
        ; branch occurs ; |85| 
	.line	34
        MOV       ACC,#512 << 15
        MOVL      @_Step+10,ACC         ; |86| 
L2:    
	.line	35
        MOVL      XAR4,#FSL2            ; |87| 
        MOVL      *-SP[2],XAR4          ; |87| 
        LCR       #_printf              ; |87| 
        ; call occurs [#_printf] ; |87| 
	.line	36
        MOVZ      AR4,SP                ; |88| 
        SUBB      XAR4,#22              ; |88| 
        LCR       #_gets                ; |88| 
        ; call occurs [#_gets] ; |88| 
	.line	37
        MOVZ      AR4,SP                ; |89| 
        SUBB      XAR4,#22              ; |89| 
        MOVB      ACC,#24
        LCR       #__atoIQN             ; |89| 
        ; call occurs [#__atoIQN] ; |89| 
        MOVW      DP,#_Step+14
        MOVL      @_Step+14,ACC         ; |89| 
	.line	38
        MOVL      ACC,@_Step+14         ; |90| 
        BF        L3,NEQ                ; |90| 
        ; branch occurs ; |90| 
	.line	39
        MOV       ACC,#512 << 15
        MOVL      @_Step+14,ACC         ; |91| 
L3:    
	.line	41
        MOVL      XAR4,#FSL3            ; |93| 
        MOVL      *-SP[2],XAR4          ; |93| 
        LCR       #_printf              ; |93| 
        ; call occurs [#_printf] ; |93| 
	.line	42
        MOVZ      AR4,SP                ; |94| 
        SUBB      XAR4,#22              ; |94| 
        LCR       #_gets                ; |94| 
        ; call occurs [#_gets] ; |94| 
	.line	43
        MOVZ      AR4,SP                ; |95| 
        SUBB      XAR4,#22              ; |95| 
        MOVB      ACC,#24
        LCR       #__atoIQN             ; |95| 
        ; call occurs [#__atoIQN] ; |95| 
        MOVW      DP,#_Step+12
        MOVL      @_Step+12,ACC         ; |95| 
	.line	44
        MOVL      ACC,@_Step+12         ; |96| 
        BF        L4,NEQ                ; |96| 
        ; branch occurs ; |96| 
	.line	45
        MOV       ACC,#512 << 15
        MOVL      @_Step+12,ACC         ; |97| 
L4:    
	.line	46
        MOVL      XAR4,#FSL4            ; |98| 
        MOVL      *-SP[2],XAR4          ; |98| 
        LCR       #_printf              ; |98| 
        ; call occurs [#_printf] ; |98| 
	.line	47
        MOVZ      AR4,SP                ; |99| 
        SUBB      XAR4,#22              ; |99| 
        LCR       #_gets                ; |99| 
        ; call occurs [#_gets] ; |99| 
	.line	48
        MOVZ      AR4,SP                ; |100| 
        SUBB      XAR4,#22              ; |100| 
        MOVB      ACC,#24
        LCR       #__atoIQN             ; |100| 
        ; call occurs [#__atoIQN] ; |100| 
        MOVW      DP,#_Step+16
        MOVL      @_Step+16,ACC         ; |100| 
	.line	49
        MOVL      ACC,@_Step+16         ; |101| 
        BF        L5,NEQ                ; |101| 
        ; branch occurs ; |101| 
	.line	50
        MOV       ACC,#512 << 15
        MOVL      @_Step+16,ACC         ; |102| 
L5:    
	.line	53
        MOVL      ACC,@_Step+12         ; |105| 
        MOVL      *-SP[2],ACC           ; |105| 
        MOVL      ACC,@_Step+10         ; |105| 
        LCR       #__IQ24mag            ; |105| 
        ; call occurs [#__IQ24mag] ; |105| 
        MOVB      XAR2,#255
        MOVL      XAR1,ACC              ; |105| 
        MOVL      XAR3,#_Dlog
L6:    
	.line	58
        MOVW      DP,#_Step
        MOVL      XT,@_Step             ; |110| 
        IMPYL     P,XT,@_Step+14        ; |110| 
        QMPYL     ACC,XT,@_Step+14      ; |110| 
        LSL64     ACC:P,#8              ; |110| 
        ADDL      @_Step+6,ACC          ; |110| 
	.line	59
        MOV       AL,#32472
        MOV       AH,#1608
        CMPL      ACC,@_Step+6          ; |111| 
        BF        L7,GEQ                ; |111| 
        ; branch occurs ; |111| 
	.line	60
        MOV       PH,#1608
        MOV       PL,#32472
        MOVL      ACC,@_Step+6          ; |112| 
        SUBL      ACC,P
        MOVL      @_Step+6,ACC          ; |112| 
L7:    
	.line	62
        MOVL      XT,@_Step+2           ; |114| 
        IMPYL     P,XT,@_Step+16        ; |114| 
        QMPYL     ACC,XT,@_Step+16      ; |114| 
        LSL64     ACC:P,#8              ; |114| 
        ADDL      @_Step+8,ACC          ; |114| 
	.line	63
        MOV       AL,#32472
        MOV       AH,#1608
        CMPL      ACC,@_Step+8          ; |115| 
        BF        L8,GEQ                ; |115| 
        ; branch occurs ; |115| 
	.line	64
        MOV       PH,#1608
        MOV       PL,#32472
        MOVL      ACC,@_Step+8          ; |116| 
        SUBL      ACC,P
        MOVL      @_Step+8,ACC          ; |116| 
L8:    
	.line	66
        MOVL      ACC,@_Step+6          ; |118| 
        LCR       #__IQ24sin            ; |118| 
        ; call occurs [#__IQ24sin] ; |118| 
        MOVW      DP,#_Step+10
        MOVL      XT,ACC                ; |118| 
        QMPYL     ACC,XT,@_Step+10      ; |118| 
        IMPYL     P,XT,@_Step+10        ; |118| 
        MOVL      *-SP[24],ACC          ; |118| 
        LSL64     ACC:P,#8              ; |118| 
        MOVL      *-SP[24],ACC          ; |118| 
        MOVL      *+XAR3[0],ACC         ; |118| 
	.line	67
        MOVL      ACC,@_Step+8          ; |119| 
        LCR       #__IQ24sin            ; |119| 
        ; call occurs [#__IQ24sin] ; |119| 
        ABS       ACC                   ; |119| 
        MOVW      DP,#_Step+12
        MOVL      XT,ACC                ; |119| 
        IMPYL     P,XT,@_Step+12        ; |119| 
        MOVL      XT,ACC                ; |119| 
        QMPYL     ACC,XT,@_Step+12      ; |119| 
        MOVL      XAR0,#512             ; |119| 
        MOVL      *-SP[26],ACC          ; |119| 
        LSL64     ACC:P,#8              ; |119| 
        MOVL      *-SP[26],ACC          ; |119| 
        MOVL      *+XAR3[AR0],ACC       ; |119| 
	.line	72
        MOVL      ACC,*-SP[26]
        MOVL      *-SP[2],ACC           ; |124| 
        MOVL      ACC,*-SP[24]          ; |124| 
        LCR       #__IQ24mag            ; |124| 
        ; call occurs [#__IQ24mag] ; |124| 
	.line	73
        MOVL      *-SP[2],XAR1          ; |125| 
        LCR       #__IQ24div            ; |125| 
        ; call occurs [#__IQ24div] ; |125| 
        MOVL      XAR0,#1536            ; |125| 
        MOVL      *+XAR3[AR0],ACC       ; |125| 
	.line	78
        MOVL      ACC,*-SP[24]
        MOVL      *-SP[2],ACC           ; |130| 
        MOVL      ACC,*-SP[26]          ; |130| 
        LCR       #__IQ24atan2PU        ; |130| 
        ; call occurs [#__IQ24atan2PU] ; |130| 
	.line	79
        MOVL      XAR4,#360             ; |131| 
        MOVL      *-SP[2],XAR4          ; |131| 
        LCR       #__IQ24mpyI32int      ; |131| 
        ; call occurs [#__IQ24mpyI32int] ; |131| 
        MOVL      XAR0,#1024            ; |131| 
        MOVL      *+XAR3[AR0],ACC       ; |131| 
	.line	80
        ADDB      XAR3,#2               ; |132| 
        BANZ      L6,AR2--              ; |132| 
        ; branch occurs ; |132| 
        MOVB      AL,#0
	.line	81
        SUBB      SP,#26                ; |132| 
        MOVL      XAR3,*--SP            ; |132| 
        MOVL      XAR2,*--SP            ; |132| 
        MOVL      XAR1,*--SP            ; |132| 
        LRETR
        ; return occurs
	.endfunc	133,000000fc0h,32


;***************************************************************
;* FAR STRINGS                                                 *
;***************************************************************
	.sect	".econst"
	.align	2
FSL1:	.string	10,"Enter waveform X gain (default = 1.0)= ",0
	.align	2
FSL2:	.string	10,"Enter waveform X freq (default = 1.0)= ",0
	.align	2
FSL3:	.string	10,"Enter waveform Y gain (default = 1.0)= ",0
	.align	2
FSL4:	.string	10,"Enter waveform Y freq (default = 1.0)= ",0
;***************************************************************
;* UNDEFINED EXTERNAL REFERENCES                               *
;***************************************************************
	.global	_printf
	.global	__IQ24mpyI32int
	.global	__IQ24atan2PU
	.global	__atoIQN
	.global	__IQ24mag
	.global	_gets
	.global	__IQ24sin
	.global	__IQ24div

;***************************************************************
;* TYPE INFORMATION                                            *
;***************************************************************
	.sym	__iq, 0, 5, 13, 32
	.stag	_DATA_LOG_C, 32768
	.member	_Xwaveform, 0, 53, 8, 8192, , 256
	.member	_Ywaveform, 8192, 53, 8, 8192, , 256
	.member	_Phase, 16384, 53, 8, 8192, , 256
	.member	_Mag, 24576, 53, 8, 8192, , 256
	.eos
	.stag	_STEP, 288
	.member	_Xsize, 0, 5, 8, 32
	.member	_Ysize, 32, 5, 8, 32
	.member	_Yoffset, 64, 5, 8, 32
	.member	_X, 96, 5, 8, 32
	.member	_Y, 128, 5, 8, 32
	.member	_GainX, 160, 5, 8, 32
	.member	_GainY, 192, 5, 8, 32
	.member	_FreqX, 224, 5, 8, 32
	.member	_FreqY, 256, 5, 8, 32
	.eos
