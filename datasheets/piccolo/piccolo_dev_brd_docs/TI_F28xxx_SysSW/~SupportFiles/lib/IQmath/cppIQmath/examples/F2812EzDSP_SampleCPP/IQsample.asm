;***************************************************************
;* TMS320C2000 C/C++ Codegen                   PC Version 3.06 *
;* Date/Time created: Sun Mar 30 20:31:15 2003                 *
;***************************************************************
FP	.set	XAR2

DWCU	.dwtag  DW_TAG_compile_unit
	.dwattr DWCU, DW_AT_name("IQsample.cpp")
	.dwattr DWCU, DW_AT_producer("TMS320C2000 C/C++ Codegen PC Version 3.06 Copyright (c) 1996-2002 Texas Instruments Incorporated")
	.dwattr DWCU, DW_AT_stmt_list(0x00)
	.dwattr DWCU, DW_AT_TI_VERSION(0x01)

DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("printf"), DW_AT_symbol_name("_printf")
	.dwattr DW$1, DW_AT_type(*DWT$11)
	.dwattr DW$1, DW_AT_declaration(0x01)
	.dwattr DW$1, DW_AT_external(0x01)
DW$2	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1021)
DW$3	.dwtag  DW_TAG_unspecified_parameters
	.dwendtag DW$1


	.sect	".cinit"
	.align	1
	.field  	-2,16
	.field  	_GlobalQ+0,32
	.field  	24,32			; _GlobalQ @ 0

	.sect	".text"
	.global	_GlobalQ
_GlobalQ:	.usect	".ebss",2,1,1
DW$4	.dwtag  DW_TAG_variable, DW_AT_name("GlobalQ"), DW_AT_symbol_name("_GlobalQ")
	.dwattr DW$4, DW_AT_type(*DWT$13)
	.dwattr DW$4, DW_AT_location[DW_OP_addr _GlobalQ]
	.dwattr DW$4, DW_AT_external(0x01)

DW$5	.dwtag  DW_TAG_subprogram, DW_AT_name("operator new"), DW_AT_symbol_name("___nw__FUl")
	.dwattr DW$5, DW_AT_type(*DWT$3)
	.dwattr DW$5, DW_AT_declaration(0x01)
	.dwattr DW$5, DW_AT_external(0x01)
DW$6	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$12)
	.dwendtag DW$5


DW$7	.dwtag  DW_TAG_subprogram, DW_AT_name("__anew"), DW_AT_symbol_name("___anew")
	.dwattr DW$7, DW_AT_type(*DWT$3)
	.dwattr DW$7, DW_AT_declaration(0x01)
	.dwattr DW$7, DW_AT_external(0x01)

DW$8	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24atan2PU"), DW_AT_symbol_name("__IQ24atan2PU")
	.dwattr DW$8, DW_AT_type(*DWT$13)
	.dwattr DW$8, DW_AT_declaration(0x01)
	.dwattr DW$8, DW_AT_external(0x01)
DW$9	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$10	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DW$8


DW$11	.dwtag  DW_TAG_subprogram, DW_AT_name("_atoIQN"), DW_AT_symbol_name("__atoIQN")
	.dwattr DW$11, DW_AT_type(*DWT$13)
	.dwattr DW$11, DW_AT_declaration(0x01)
	.dwattr DW$11, DW_AT_external(0x01)
DW$12	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1021)
DW$13	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DW$11


DW$14	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24mpyI32int"), DW_AT_symbol_name("__IQ24mpyI32int")
	.dwattr DW$14, DW_AT_type(*DWT$13)
	.dwattr DW$14, DW_AT_declaration(0x01)
	.dwattr DW$14, DW_AT_external(0x01)
DW$15	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$16	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DW$14


DW$17	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24mag"), DW_AT_symbol_name("__IQ24mag")
	.dwattr DW$17, DW_AT_type(*DWT$13)
	.dwattr DW$17, DW_AT_declaration(0x01)
	.dwattr DW$17, DW_AT_external(0x01)
DW$18	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$19	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DW$17


DW$20	.dwtag  DW_TAG_subprogram, DW_AT_name("__IQmpy"), DW_AT_symbol_name("___IQmpy")
	.dwattr DW$20, DW_AT_type(*DWT$13)
	.dwattr DW$20, DW_AT_declaration(0x01)
	.dwattr DW$20, DW_AT_external(0x01)
DW$21	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$22	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$23	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$11)
	.dwendtag DW$20


DW$24	.dwtag  DW_TAG_subprogram, DW_AT_name("labs"), DW_AT_symbol_name("_labs")
	.dwattr DW$24, DW_AT_type(*DWT$13)
	.dwattr DW$24, DW_AT_declaration(0x01)
	.dwattr DW$24, DW_AT_external(0x01)
DW$25	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DW$24


DW$26	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24div"), DW_AT_symbol_name("__IQ24div")
	.dwattr DW$26, DW_AT_type(*DWT$13)
	.dwattr DW$26, DW_AT_declaration(0x01)
	.dwattr DW$26, DW_AT_external(0x01)
DW$27	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$28	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DW$26


DW$29	.dwtag  DW_TAG_subprogram, DW_AT_name("gets"), DW_AT_symbol_name("_gets")
	.dwattr DW$29, DW_AT_type(*DWT$1027)
	.dwattr DW$29, DW_AT_declaration(0x01)
	.dwattr DW$29, DW_AT_external(0x01)
DW$30	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1027)
	.dwendtag DW$29


DW$31	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24sin"), DW_AT_symbol_name("__IQ24sin")
	.dwattr DW$31, DW_AT_type(*DWT$13)
	.dwattr DW$31, DW_AT_declaration(0x01)
	.dwattr DW$31, DW_AT_external(0x01)
DW$32	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DW$31

	.global	_Step
_Step:	.usect	".ebss",18,1,1
DW$33	.dwtag  DW_TAG_variable, DW_AT_name("Step"), DW_AT_symbol_name("_Step")
	.dwattr DW$33, DW_AT_type(*DWT$1133)
	.dwattr DW$33, DW_AT_location[DW_OP_addr _Step]
	.dwattr DW$33, DW_AT_external(0x01)
	.global	_Dlog
_Dlog:	.usect	".ebss",2048,1,1
DW$34	.dwtag  DW_TAG_variable, DW_AT_name("Dlog"), DW_AT_symbol_name("_Dlog")
	.dwattr DW$34, DW_AT_type(*DWT$1119)
	.dwattr DW$34, DW_AT_location[DW_OP_addr _Dlog]
	.dwattr DW$34, DW_AT_external(0x01)
;	C:\ti\c2000\cgtools\bin\opt2000.exe -m -v28 -q -O3 C:\DOCUME~1\a0875026\LOCALS~1\Temp\TI2984_2 C:\DOCUME~1\a0875026\LOCALS~1\Temp\TI2984_5 -w C:/tidcs/c28/IQmath/cppIQmath/examples/F2812EzDSP_SampleCPP/Debug 
;	C:\ti\c2000\cgtools\bin\ac2000.exe -@C:\DOCUME~1\a0875026\LOCALS~1\Temp\TI2984_4 

	.sect	".text"

DW$35	.dwtag  DW_TAG_subprogram, DW_AT_name("iq"), DW_AT_symbol_name("___ct__2iqFv")
	.dwattr DW$35, DW_AT_low_pc(___ct__2iqFv)
	.dwattr DW$35, DW_AT_high_pc(0x00)
	.dwpsn	"../../include/IQmathCPP.h",37,17

	.dwfde DW$CIE

;***************************************************************
;* FNAME: ___ct__2iqFv                  FR SIZE:   0           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            0 Parameter,  0 Auto,  0 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
___ct__2iqFv:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
;* AR4   assigned to _this
DW$36	.dwtag  DW_TAG_formal_parameter, DW_AT_name("this"), DW_AT_symbol_name("_this")
	.dwattr DW$36, DW_AT_type(*DWT$1066)
	.dwattr DW$36, DW_AT_location[DW_OP_reg12]
;* AR4   assigned to _this
DW$37	.dwtag  DW_TAG_variable, DW_AT_name("this"), DW_AT_symbol_name("_this")
	.dwattr DW$37, DW_AT_type(*DWT$1066)
	.dwattr DW$37, DW_AT_location[DW_OP_reg12]
        MOVL      ACC,XAR4              ; |37| 
        BF        L1,NEQ                ; |37| 
        ; branch occurs ; |37| 
        MOVB      ACC,#2
        LCR       #___nw__FUl           ; |37| 
        ; call occurs [#___nw__FUl] ; |37| 
        MOVL      ACC,XAR4              ; |37| 
        BF        L2,EQ                 ; |37| 
        ; branch occurs ; |37| 
L1:    
        MOVB      ACC,#0
        MOVL      *+XAR4[0],ACC         ; |37| 
L2:    
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag DW$35




	.sect	".text"

DW$38	.dwtag  DW_TAG_subprogram, DW_AT_name("IQmag"), DW_AT_symbol_name("_IQmag__F2iqT1")
	.dwattr DW$38, DW_AT_low_pc(_IQmag__F2iqT1)
	.dwattr DW$38, DW_AT_high_pc(0x00)
	.dwpsn	"../../include/IQmathCPP.h",3058,1

	.dwfde DW$CIE

;***************************************************************
;* FNAME: _IQmag__F2iqT1                FR SIZE:   8           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter,  0 Auto,  6 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
_IQmag__F2iqT1:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
        MOVL      *SP++,XAR1
	.dwcfa	0x80, 7, 2
	.dwcfa	0x1d, -4
        MOVL      *SP++,XAR2
	.dwcfa	0x80, 9, 4
	.dwcfa	0x1d, -6
        MOVL      *SP++,XAR3
	.dwcfa	0x80, 11, 6
	.dwcfa	0x1d, -8
        ADDB      SP,#2
	.dwcfa	0x1d, -10
;* AR4   assigned to _$T6
DW$39	.dwtag  DW_TAG_formal_parameter, DW_AT_name("$T6"), DW_AT_symbol_name("_$T6")
	.dwattr DW$39, DW_AT_type(*DWT$1066)
	.dwattr DW$39, DW_AT_location[DW_OP_reg12]
;* AR5   assigned to _y
DW$40	.dwtag  DW_TAG_formal_parameter, DW_AT_name("y"), DW_AT_symbol_name("_y")
	.dwattr DW$40, DW_AT_type(*DWT$1066)
	.dwattr DW$40, DW_AT_location[DW_OP_reg14]
DW$41	.dwtag  DW_TAG_formal_parameter, DW_AT_name("x"), DW_AT_symbol_name("_x")
	.dwattr DW$41, DW_AT_type(*DWT$1066)
	.dwattr DW$41, DW_AT_location[DW_OP_breg20 -12]
;* AR4   assigned to _this
DW$42	.dwtag  DW_TAG_variable, DW_AT_name("this"), DW_AT_symbol_name("_this")
	.dwattr DW$42, DW_AT_type(*DWT$1066)
	.dwattr DW$42, DW_AT_location[DW_OP_reg12]
;* AR2   assigned to _x
DW$43	.dwtag  DW_TAG_variable, DW_AT_name("x"), DW_AT_symbol_name("_x")
	.dwattr DW$43, DW_AT_type(*DWT$1092)
	.dwattr DW$43, DW_AT_location[DW_OP_reg8]
;* AR3   assigned to _y
DW$44	.dwtag  DW_TAG_variable, DW_AT_name("y"), DW_AT_symbol_name("_y")
	.dwattr DW$44, DW_AT_type(*DWT$1092)
	.dwattr DW$44, DW_AT_location[DW_OP_reg10]
;* AR1   assigned to _$T6
DW$45	.dwtag  DW_TAG_variable, DW_AT_name("$T6"), DW_AT_symbol_name("_$T6")
	.dwattr DW$45, DW_AT_type(*DWT$1092)
	.dwattr DW$45, DW_AT_location[DW_OP_reg6]
        MOVL      XAR1,XAR4             ; |3058| 
        MOVL      XAR2,*-SP[12]         ; |3058| 
        MOVL      XAR3,XAR5             ; |3058| 
	.dwpsn	"../../include/IQmathCPP.h",3059,7
        MOVL      XAR4,XAR1             ; |3059| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVL      ACC,XAR4
        BF        L3,NEQ                ; |37| 
        ; branch occurs ; |37| 
        MOVB      ACC,#2
        LCR       #___nw__FUl           ; |37| 
        ; call occurs [#___nw__FUl] ; |37| 
        MOVL      ACC,XAR4              ; |37| 
        BF        L4,EQ                 ; |37| 
        ; branch occurs ; |37| 
L3:    
        MOVB      ACC,#0
        MOVL      *+XAR4[0],ACC         ; |37| 
L4:    
	.dwpsn	"../../include/IQmathCPP.h",3060,4
        MOVL      ACC,*+XAR2[0]         ; |3060| 
        MOVL      *-SP[2],ACC           ; |3060| 
        MOVL      ACC,*+XAR3[0]         ; |3060| 
        LCR       #__IQ24mag            ; |3060| 
        ; call occurs [#__IQ24mag] ; |3060| 
        MOVL      *+XAR1[0],ACC         ; |3060| 
	.dwpsn	"../../include/IQmathCPP.h",3061,4
	.dwpsn	"../../include/IQmathCPP.h",3062,1
        SUBB      SP,#2
	.dwcfa	0x1d, -8
        MOVL      XAR3,*--SP
	.dwcfa	0x1d, -6
	.dwcfa	0xc0, 11
        MOVL      XAR2,*--SP
	.dwcfa	0x1d, -4
	.dwcfa	0xc0, 9
        MOVL      XAR1,*--SP
	.dwcfa	0x1d, -2
	.dwcfa	0xc0, 7
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag DW$38




	.sect	".text"

DW$46	.dwtag  DW_TAG_subprogram, DW_AT_name("IQsin"), DW_AT_symbol_name("_IQsin__F2iq")
	.dwattr DW$46, DW_AT_low_pc(_IQsin__F2iq)
	.dwattr DW$46, DW_AT_high_pc(0x00)
	.dwpsn	"../../include/IQmathCPP.h",2052,1

	.dwfde DW$CIE

;***************************************************************
;* FNAME: _IQsin__F2iq                  FR SIZE:   4           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            0 Parameter,  0 Auto,  4 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
_IQsin__F2iq:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
        MOVL      *SP++,XAR1
	.dwcfa	0x80, 7, 2
	.dwcfa	0x1d, -4
        MOVL      *SP++,XAR2
	.dwcfa	0x80, 9, 4
	.dwcfa	0x1d, -6
;* AR4   assigned to _$T4
DW$47	.dwtag  DW_TAG_formal_parameter, DW_AT_name("$T4"), DW_AT_symbol_name("_$T4")
	.dwattr DW$47, DW_AT_type(*DWT$1066)
	.dwattr DW$47, DW_AT_location[DW_OP_reg12]
;* AR5   assigned to _x
DW$48	.dwtag  DW_TAG_formal_parameter, DW_AT_name("x"), DW_AT_symbol_name("_x")
	.dwattr DW$48, DW_AT_type(*DWT$1066)
	.dwattr DW$48, DW_AT_location[DW_OP_reg14]
;* AR4   assigned to _this
DW$49	.dwtag  DW_TAG_variable, DW_AT_name("this"), DW_AT_symbol_name("_this")
	.dwattr DW$49, DW_AT_type(*DWT$1066)
	.dwattr DW$49, DW_AT_location[DW_OP_reg12]
;* AR2   assigned to _x
DW$50	.dwtag  DW_TAG_variable, DW_AT_name("x"), DW_AT_symbol_name("_x")
	.dwattr DW$50, DW_AT_type(*DWT$1092)
	.dwattr DW$50, DW_AT_location[DW_OP_reg8]
;* AR1   assigned to _$T4
DW$51	.dwtag  DW_TAG_variable, DW_AT_name("$T4"), DW_AT_symbol_name("_$T4")
	.dwattr DW$51, DW_AT_type(*DWT$1092)
	.dwattr DW$51, DW_AT_location[DW_OP_reg6]
        MOVL      XAR1,XAR4             ; |2052| 
        MOVL      XAR2,XAR5             ; |2052| 
	.dwpsn	"../../include/IQmathCPP.h",2053,7
        MOVL      XAR4,XAR1             ; |2053| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVL      ACC,XAR4
        BF        L5,NEQ                ; |37| 
        ; branch occurs ; |37| 
        MOVB      ACC,#2
        LCR       #___nw__FUl           ; |37| 
        ; call occurs [#___nw__FUl] ; |37| 
        MOVL      ACC,XAR4              ; |37| 
        BF        L6,EQ                 ; |37| 
        ; branch occurs ; |37| 
L5:    
        MOVB      ACC,#0
        MOVL      *+XAR4[0],ACC         ; |37| 
L6:    
	.dwpsn	"../../include/IQmathCPP.h",2054,4
        MOVL      ACC,*+XAR2[0]         ; |2054| 
        LCR       #__IQ24sin            ; |2054| 
        ; call occurs [#__IQ24sin] ; |2054| 
        MOVL      *+XAR1[0],ACC         ; |2054| 
	.dwpsn	"../../include/IQmathCPP.h",2055,4
	.dwpsn	"../../include/IQmathCPP.h",2056,1
	.dwcfa	0x1d, -6
        MOVL      XAR2,*--SP
	.dwcfa	0x1d, -4
	.dwcfa	0xc0, 9
        MOVL      XAR1,*--SP
	.dwcfa	0x1d, -2
	.dwcfa	0xc0, 7
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag DW$46




	.sect	".text"

DW$52	.dwtag  DW_TAG_subprogram, DW_AT_name("IQabs"), DW_AT_symbol_name("_IQabs__F2iq")
	.dwattr DW$52, DW_AT_low_pc(_IQabs__F2iq)
	.dwattr DW$52, DW_AT_high_pc(0x00)
	.dwpsn	"../../include/IQmathCPP.h",3181,1

	.dwfde DW$CIE

;***************************************************************
;* FNAME: _IQabs__F2iq                  FR SIZE:   4           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            0 Parameter,  0 Auto,  4 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
_IQabs__F2iq:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
        MOVL      *SP++,XAR1
	.dwcfa	0x80, 7, 2
	.dwcfa	0x1d, -4
        MOVL      *SP++,XAR2
	.dwcfa	0x80, 9, 4
	.dwcfa	0x1d, -6
;* AR4   assigned to _$T7
DW$53	.dwtag  DW_TAG_formal_parameter, DW_AT_name("$T7"), DW_AT_symbol_name("_$T7")
	.dwattr DW$53, DW_AT_type(*DWT$1066)
	.dwattr DW$53, DW_AT_location[DW_OP_reg12]
;* AR5   assigned to _y
DW$54	.dwtag  DW_TAG_formal_parameter, DW_AT_name("y"), DW_AT_symbol_name("_y")
	.dwattr DW$54, DW_AT_type(*DWT$1066)
	.dwattr DW$54, DW_AT_location[DW_OP_reg14]
;* AR4   assigned to _this
DW$55	.dwtag  DW_TAG_variable, DW_AT_name("this"), DW_AT_symbol_name("_this")
	.dwattr DW$55, DW_AT_type(*DWT$1066)
	.dwattr DW$55, DW_AT_location[DW_OP_reg12]
;* AR2   assigned to _y
DW$56	.dwtag  DW_TAG_variable, DW_AT_name("y"), DW_AT_symbol_name("_y")
	.dwattr DW$56, DW_AT_type(*DWT$1092)
	.dwattr DW$56, DW_AT_location[DW_OP_reg8]
;* AR1   assigned to _$T7
DW$57	.dwtag  DW_TAG_variable, DW_AT_name("$T7"), DW_AT_symbol_name("_$T7")
	.dwattr DW$57, DW_AT_type(*DWT$1092)
	.dwattr DW$57, DW_AT_location[DW_OP_reg6]
        MOVL      XAR1,XAR4             ; |3181| 
        MOVL      XAR2,XAR5             ; |3181| 
	.dwpsn	"../../include/IQmathCPP.h",3182,7
        MOVL      XAR4,XAR1             ; |3182| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVL      ACC,XAR4
        BF        L7,NEQ                ; |37| 
        ; branch occurs ; |37| 
        MOVB      ACC,#2
        LCR       #___nw__FUl           ; |37| 
        ; call occurs [#___nw__FUl] ; |37| 
        MOVL      ACC,XAR4              ; |37| 
        BF        L8,EQ                 ; |37| 
        ; branch occurs ; |37| 
L7:    
        MOVB      ACC,#0
        MOVL      *+XAR4[0],ACC         ; |37| 
L8:    
	.dwpsn	"../../include/IQmathCPP.h",3183,4
        MOVL      ACC,*+XAR2[0]         ; |3183| 
        ABS       ACC                   ; |3183| 
        MOVL      *+XAR1[0],ACC         ; |3183| 
	.dwpsn	"../../include/IQmathCPP.h",3184,4
	.dwpsn	"../../include/IQmathCPP.h",3185,1
	.dwcfa	0x1d, -6
        MOVL      XAR2,*--SP
	.dwcfa	0x1d, -4
	.dwcfa	0xc0, 9
        MOVL      XAR1,*--SP
	.dwcfa	0x1d, -2
	.dwcfa	0xc0, 7
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag DW$52




	.sect	".text"

DW$58	.dwtag  DW_TAG_subprogram, DW_AT_name("IQatan2PU"), DW_AT_symbol_name("_IQatan2PU__F2iqT1")
	.dwattr DW$58, DW_AT_low_pc(_IQatan2PU__F2iqT1)
	.dwattr DW$58, DW_AT_high_pc(0x00)
	.dwpsn	"../../include/IQmathCPP.h",2667,1

	.dwfde DW$CIE

;***************************************************************
;* FNAME: _IQatan2PU__F2iqT1            FR SIZE:   8           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter,  0 Auto,  6 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
_IQatan2PU__F2iqT1:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
        MOVL      *SP++,XAR1
	.dwcfa	0x80, 7, 2
	.dwcfa	0x1d, -4
        MOVL      *SP++,XAR2
	.dwcfa	0x80, 9, 4
	.dwcfa	0x1d, -6
        MOVL      *SP++,XAR3
	.dwcfa	0x80, 11, 6
	.dwcfa	0x1d, -8
        ADDB      SP,#2
	.dwcfa	0x1d, -10
;* AR4   assigned to _$T5
DW$59	.dwtag  DW_TAG_formal_parameter, DW_AT_name("$T5"), DW_AT_symbol_name("_$T5")
	.dwattr DW$59, DW_AT_type(*DWT$1066)
	.dwattr DW$59, DW_AT_location[DW_OP_reg12]
;* AR5   assigned to _y
DW$60	.dwtag  DW_TAG_formal_parameter, DW_AT_name("y"), DW_AT_symbol_name("_y")
	.dwattr DW$60, DW_AT_type(*DWT$1066)
	.dwattr DW$60, DW_AT_location[DW_OP_reg14]
DW$61	.dwtag  DW_TAG_formal_parameter, DW_AT_name("x"), DW_AT_symbol_name("_x")
	.dwattr DW$61, DW_AT_type(*DWT$1066)
	.dwattr DW$61, DW_AT_location[DW_OP_breg20 -12]
;* AR4   assigned to _this
DW$62	.dwtag  DW_TAG_variable, DW_AT_name("this"), DW_AT_symbol_name("_this")
	.dwattr DW$62, DW_AT_type(*DWT$1066)
	.dwattr DW$62, DW_AT_location[DW_OP_reg12]
;* AR2   assigned to _x
DW$63	.dwtag  DW_TAG_variable, DW_AT_name("x"), DW_AT_symbol_name("_x")
	.dwattr DW$63, DW_AT_type(*DWT$1092)
	.dwattr DW$63, DW_AT_location[DW_OP_reg8]
;* AR3   assigned to _y
DW$64	.dwtag  DW_TAG_variable, DW_AT_name("y"), DW_AT_symbol_name("_y")
	.dwattr DW$64, DW_AT_type(*DWT$1092)
	.dwattr DW$64, DW_AT_location[DW_OP_reg10]
;* AR1   assigned to _$T5
DW$65	.dwtag  DW_TAG_variable, DW_AT_name("$T5"), DW_AT_symbol_name("_$T5")
	.dwattr DW$65, DW_AT_type(*DWT$1092)
	.dwattr DW$65, DW_AT_location[DW_OP_reg6]
        MOVL      XAR1,XAR4             ; |2667| 
        MOVL      XAR2,*-SP[12]         ; |2667| 
        MOVL      XAR3,XAR5             ; |2667| 
	.dwpsn	"../../include/IQmathCPP.h",2668,7
        MOVL      XAR4,XAR1             ; |2668| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVL      ACC,XAR4
        BF        L9,NEQ                ; |37| 
        ; branch occurs ; |37| 
        MOVB      ACC,#2
        LCR       #___nw__FUl           ; |37| 
        ; call occurs [#___nw__FUl] ; |37| 
        MOVL      ACC,XAR4              ; |37| 
        BF        L10,EQ                ; |37| 
        ; branch occurs ; |37| 
L9:    
        MOVB      ACC,#0
        MOVL      *+XAR4[0],ACC         ; |37| 
L10:    
	.dwpsn	"../../include/IQmathCPP.h",2669,4
        MOVL      ACC,*+XAR2[0]         ; |2669| 
        MOVL      *-SP[2],ACC           ; |2669| 
        MOVL      ACC,*+XAR3[0]         ; |2669| 
        LCR       #__IQ24atan2PU        ; |2669| 
        ; call occurs [#__IQ24atan2PU] ; |2669| 
        MOVL      *+XAR1[0],ACC         ; |2669| 
	.dwpsn	"../../include/IQmathCPP.h",2670,4
	.dwpsn	"../../include/IQmathCPP.h",2671,1
        SUBB      SP,#2
	.dwcfa	0x1d, -8
        MOVL      XAR3,*--SP
	.dwcfa	0x1d, -6
	.dwcfa	0xc0, 11
        MOVL      XAR2,*--SP
	.dwcfa	0x1d, -4
	.dwcfa	0xc0, 9
        MOVL      XAR1,*--SP
	.dwcfa	0x1d, -2
	.dwcfa	0xc0, 7
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag DW$58




	.sect	".text"
	.global	_main

DW$66	.dwtag  DW_TAG_subprogram, DW_AT_name("main"), DW_AT_symbol_name("_main")
	.dwattr DW$66, DW_AT_low_pc(_main)
	.dwattr DW$66, DW_AT_high_pc(0x00)
	.dwpsn	"IQsample.cpp",57,1

	.dwfde DW$CIE

;***************************************************************
;* FNAME: _main                         FR SIZE:  54           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter, 46 Auto,  6 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
_main:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
        MOVL      *SP++,XAR1
	.dwcfa	0x80, 7, 2
	.dwcfa	0x1d, -4
        MOVL      *SP++,XAR2
	.dwcfa	0x80, 9, 4
	.dwcfa	0x1d, -6
        MOVL      *SP++,XAR3
	.dwcfa	0x80, 11, 6
	.dwcfa	0x1d, -8
        ADDB      SP,#48
	.dwcfa	0x1d, -56
;* AR3   assigned to C$33
;* AR2   assigned to C$34
;* AR3   assigned to C$35
;* AR4   assigned to C$36
;* AR4   assigned to C$37
;* AR4   assigned to C$38
;* AR6   assigned to C$39
;* AR6   assigned to C$40
;* AR6   assigned to C$41
;* XT    assigned to C$42
;* AR4   assigned to C$43
;* AR4   assigned to K$31
;* AR4   assigned to K$34
;* AR4   assigned to K$93
;* AR6   assigned to L$1
;* AR4   assigned to _WatchdogWDCR
DW$67	.dwtag  DW_TAG_variable, DW_AT_name("WatchdogWDCR"), DW_AT_symbol_name("_WatchdogWDCR")
	.dwattr DW$67, DW_AT_type(*DWT$1018)
	.dwattr DW$67, DW_AT_location[DW_OP_reg12]
;* AL    assigned to R$2
;* AR5   assigned to U$51
;* AR7   assigned to _i
DW$68	.dwtag  DW_TAG_variable, DW_AT_name("i"), DW_AT_symbol_name("_i")
	.dwattr DW$68, DW_AT_type(*DWT$10)
	.dwattr DW$68, DW_AT_location[DW_OP_reg18]
;* AR1   assigned to _i
DW$69	.dwtag  DW_TAG_variable, DW_AT_name("i"), DW_AT_symbol_name("_i")
	.dwattr DW$69, DW_AT_type(*DWT$10)
	.dwattr DW$69, DW_AT_location[DW_OP_reg6]
DW$70	.dwtag  DW_TAG_variable, DW_AT_name("$T8"), DW_AT_symbol_name("_$T8")
	.dwattr DW$70, DW_AT_type(*DWT$1041)
	.dwattr DW$70, DW_AT_location[DW_OP_breg20 -4]
;* AL    assigned to _$T9
DW$71	.dwtag  DW_TAG_variable, DW_AT_name("$T9"), DW_AT_symbol_name("_$T9")
	.dwattr DW$71, DW_AT_type(*DWT$1044)
	.dwattr DW$71, DW_AT_location[DW_OP_reg0]
DW$72	.dwtag  DW_TAG_variable, DW_AT_name("$T10"), DW_AT_symbol_name("_$T10")
	.dwattr DW$72, DW_AT_type(*DWT$1041)
	.dwattr DW$72, DW_AT_location[DW_OP_breg20 -6]
DW$73	.dwtag  DW_TAG_variable, DW_AT_name("$T11"), DW_AT_symbol_name("_$T11")
	.dwattr DW$73, DW_AT_type(*DWT$1041)
	.dwattr DW$73, DW_AT_location[DW_OP_breg20 -8]
;* AL    assigned to _tempX
DW$74	.dwtag  DW_TAG_variable, DW_AT_name("tempX"), DW_AT_symbol_name("_tempX")
	.dwattr DW$74, DW_AT_type(*DWT$1041)
	.dwattr DW$74, DW_AT_location[DW_OP_reg0]
;* AR3   assigned to _tempY
DW$75	.dwtag  DW_TAG_variable, DW_AT_name("tempY"), DW_AT_symbol_name("_tempY")
	.dwattr DW$75, DW_AT_type(*DWT$1041)
	.dwattr DW$75, DW_AT_location[DW_OP_reg10]
;* AL    assigned to _tempP
DW$76	.dwtag  DW_TAG_variable, DW_AT_name("tempP"), DW_AT_symbol_name("_tempP")
	.dwattr DW$76, DW_AT_type(*DWT$1041)
	.dwattr DW$76, DW_AT_location[DW_OP_reg0]
;* AL    assigned to _tempM
DW$77	.dwtag  DW_TAG_variable, DW_AT_name("tempM"), DW_AT_symbol_name("_tempM")
	.dwattr DW$77, DW_AT_type(*DWT$1041)
	.dwattr DW$77, DW_AT_location[DW_OP_reg0]
DW$78	.dwtag  DW_TAG_variable, DW_AT_name("tempMmax"), DW_AT_symbol_name("_tempMmax")
	.dwattr DW$78, DW_AT_type(*DWT$1041)
	.dwattr DW$78, DW_AT_location[DW_OP_breg20 -44]
DW$79	.dwtag  DW_TAG_variable, DW_AT_name("buffer"), DW_AT_symbol_name("_buffer")
	.dwattr DW$79, DW_AT_type(*DWT$1053)
	.dwattr DW$79, DW_AT_location[DW_OP_breg20 -28]
;* PL    assigned to _$T12
DW$80	.dwtag  DW_TAG_variable, DW_AT_name("$T12"), DW_AT_symbol_name("_$T12")
	.dwattr DW$80, DW_AT_type(*DWT$1044)
	.dwattr DW$80, DW_AT_location[DW_OP_reg2]
;* AL    assigned to _$T13
DW$81	.dwtag  DW_TAG_variable, DW_AT_name("$T13"), DW_AT_symbol_name("_$T13")
	.dwattr DW$81, DW_AT_type(*DWT$1041)
	.dwattr DW$81, DW_AT_location[DW_OP_reg0]
;* AL    assigned to _$T14
DW$82	.dwtag  DW_TAG_variable, DW_AT_name("$T14"), DW_AT_symbol_name("_$T14")
	.dwattr DW$82, DW_AT_type(*DWT$1041)
	.dwattr DW$82, DW_AT_location[DW_OP_reg0]
;* AL    assigned to _$T15
DW$83	.dwtag  DW_TAG_variable, DW_AT_name("$T15"), DW_AT_symbol_name("_$T15")
	.dwattr DW$83, DW_AT_type(*DWT$1041)
	.dwattr DW$83, DW_AT_location[DW_OP_reg0]
;* AL    assigned to _$T16
DW$84	.dwtag  DW_TAG_variable, DW_AT_name("$T16"), DW_AT_symbol_name("_$T16")
	.dwattr DW$84, DW_AT_type(*DWT$1041)
	.dwattr DW$84, DW_AT_location[DW_OP_reg0]
DW$85	.dwtag  DW_TAG_variable, DW_AT_name("$T17"), DW_AT_symbol_name("_$T17")
	.dwattr DW$85, DW_AT_type(*DWT$1041)
	.dwattr DW$85, DW_AT_location[DW_OP_breg20 -30]
DW$86	.dwtag  DW_TAG_variable, DW_AT_name("$T18"), DW_AT_symbol_name("_$T18")
	.dwattr DW$86, DW_AT_type(*DWT$1041)
	.dwattr DW$86, DW_AT_location[DW_OP_breg20 -32]
DW$87	.dwtag  DW_TAG_variable, DW_AT_name("$T19"), DW_AT_symbol_name("_$T19")
	.dwattr DW$87, DW_AT_type(*DWT$1041)
	.dwattr DW$87, DW_AT_location[DW_OP_breg20 -34]
DW$88	.dwtag  DW_TAG_variable, DW_AT_name("$T20"), DW_AT_symbol_name("_$T20")
	.dwattr DW$88, DW_AT_type(*DWT$1041)
	.dwattr DW$88, DW_AT_location[DW_OP_breg20 -36]
;* AL    assigned to _$T21
DW$89	.dwtag  DW_TAG_variable, DW_AT_name("$T21"), DW_AT_symbol_name("_$T21")
	.dwattr DW$89, DW_AT_type(*DWT$1041)
	.dwattr DW$89, DW_AT_location[DW_OP_reg0]
;* AL    assigned to _$T22
DW$90	.dwtag  DW_TAG_variable, DW_AT_name("$T22"), DW_AT_symbol_name("_$T22")
	.dwattr DW$90, DW_AT_type(*DWT$1041)
	.dwattr DW$90, DW_AT_location[DW_OP_reg0]
	.dwpsn	"../../include/IQmathCPP.h",37,17
	.dwpsn	"IQsample.cpp",66,5
 EALLOW 
	.dwpsn	"IQsample.cpp",67,5
        MOVL      XAR4,#28713           ; |67| 
        MOV       *+XAR4[0],#104        ; |67| 
	.dwpsn	"IQsample.cpp",68,5
 EDIS 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       AH,#80
        MOV       AL,#27837
        MOVL      *-SP[4],ACC           ; |38| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[4]           ; |3530| 
        MOVL      XAR4,#_Step           ; |3530| 
        MOVL      *+XAR4[0],ACC         ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       AH,#80
        MOV       AL,#27837
        MOVL      *-SP[4],ACC           ; |38| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[4]           ; |3530| 
        MOVL      *+XAR4[2],ACC         ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOVB      ACC,#0
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      *+XAR4[4],ACC         ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVW      DP,#_Step+4
        MOVL      *+XAR4[6],ACC         ; |3530| 
        MOVB      XAR0,#8               ; |3530| 
        MOVL      ACC,@_Step+4          ; |3530| 
        MOVL      *+XAR4[AR0],ACC       ; |3530| 
        MOVL      XAR4,#_Dlog
        MOVL      *-SP[38],XAR4
        MOVL      XAR4,#512
        MOVL      ACC,*-SP[38]
        ADDL      XAR4,ACC
        MOVL      *-SP[40],XAR4
        MOVL      ACC,*-SP[38]
        MOVL      XAR4,#1024
        ADDL      XAR4,ACC
        MOVL      XAR5,XAR4
        MOVL      ACC,*-SP[38]
        MOVL      XAR4,#1536
        ADDL      XAR4,ACC
        MOVL      *-SP[42],XAR4
	.dwpsn	"IQsample.cpp",76,6
        MOVB      XAR6,#255
        MOVB      XAR7,#0
L11:    
DWL$_main$2$B:
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       PH,#0
        MOV       PL,#0
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVU      ACC,AR7
        LSL       ACC,1                 ; |3530| 
        MOVL      XAR0,ACC              ; |3530| 
        MOVL      XT,ACC                ; |3530| 
        MOVL      ACC,*-SP[38]          ; |3530| 
        ADDL      XAR0,ACC
        MOVL      *+XAR0[0],P           ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      XAR4,XT               ; |3530| 
        MOVL      ACC,*-SP[40]          ; |3530| 
        ADDL      XAR4,ACC
        MOVL      *+XAR4[0],P           ; |3530| 
	.dwpsn	"IQsample.cpp",80,3
        MOVB      ACC,#0
        MOVL      *XAR5++,ACC           ; |80| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      XAR4,XT               ; |3530| 
        MOVL      ACC,*-SP[42]          ; |3530| 
        ADDL      XAR4,ACC
        MOVL      *+XAR4[0],P           ; |3530| 
	.dwpsn	"IQsample.cpp",82,3
        ADDB      XAR7,#1               ; |82| 
        BANZ      L11,AR6--             ; |82| 
        ; branch occurs ; |82| 
DWL$_main$2$E:
	.dwpsn	"IQsample.cpp",85,2
        MOVL      XAR4,#FSL1            ; |85| 
        MOVL      *-SP[2],XAR4          ; |85| 
        LCR       #_printf              ; |85| 
        ; call occurs [#_printf] ; |85| 
	.dwpsn	"IQsample.cpp",86,2
        MOVZ      AR4,SP                ; |86| 
        SUBB      XAR4,#28              ; |86| 
        LCR       #_gets                ; |86| 
        ; call occurs [#_gets] ; |86| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVZ      AR4,SP                ; |37| 
        MOVB      ACC,#0
        SUBB      XAR4,#28              ; |37| 
        MOVL      *-SP[4],ACC           ; |37| 
        MOVB      ACC,#24
        LCR       #__atoIQN             ; |37| 
        ; call occurs [#__atoIQN] ; |37| 
        MOVL      *-SP[4],ACC           ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      XAR6,*-SP[4]          ; |3530| 
        MOVW      DP,#_Step+10
        MOVL      @_Step+10,XAR6        ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOVB      ACC,#0
	.dwpsn	"../../include/IQmathCPP.h",4427,58
        CMPL      ACC,XAR6              ; |4427| 
        BF        L12,NEQ               ; |4427| 
        ; branch occurs ; |4427| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       ACC,#512 << 15
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      @_Step+10,ACC         ; |3530| 
L12:    
	.dwpsn	"IQsample.cpp",90,2
        MOVL      XAR4,#FSL2            ; |90| 
        MOVL      *-SP[2],XAR4          ; |90| 
        LCR       #_printf              ; |90| 
        ; call occurs [#_printf] ; |90| 
	.dwpsn	"IQsample.cpp",91,2
        MOVZ      AR4,SP                ; |91| 
        SUBB      XAR4,#28              ; |91| 
        LCR       #_gets                ; |91| 
        ; call occurs [#_gets] ; |91| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVZ      AR4,SP                ; |37| 
        MOVB      ACC,#0
        SUBB      XAR4,#28              ; |37| 
        MOVL      *-SP[4],ACC           ; |37| 
        MOVB      ACC,#24
        LCR       #__atoIQN             ; |37| 
        ; call occurs [#__atoIQN] ; |37| 
        MOVL      *-SP[4],ACC           ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      XAR6,*-SP[4]          ; |3530| 
        MOVW      DP,#_Step+14
        MOVL      @_Step+14,XAR6        ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOVB      ACC,#0
	.dwpsn	"../../include/IQmathCPP.h",4427,58
        CMPL      ACC,XAR6              ; |4427| 
        BF        L13,NEQ               ; |4427| 
        ; branch occurs ; |4427| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       ACC,#512 << 15
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      @_Step+14,ACC         ; |3530| 
L13:    
	.dwpsn	"IQsample.cpp",96,2
        MOVL      XAR4,#FSL3            ; |96| 
        MOVL      *-SP[2],XAR4          ; |96| 
        LCR       #_printf              ; |96| 
        ; call occurs [#_printf] ; |96| 
	.dwpsn	"IQsample.cpp",97,2
        MOVZ      AR4,SP                ; |97| 
        SUBB      XAR4,#28              ; |97| 
        LCR       #_gets                ; |97| 
        ; call occurs [#_gets] ; |97| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVZ      AR4,SP                ; |37| 
        MOVB      ACC,#0
        SUBB      XAR4,#28              ; |37| 
        MOVL      *-SP[4],ACC           ; |37| 
        MOVB      ACC,#24
        LCR       #__atoIQN             ; |37| 
        ; call occurs [#__atoIQN] ; |37| 
        MOVL      *-SP[4],ACC           ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      XAR6,*-SP[4]          ; |3530| 
        MOVW      DP,#_Step+12
        MOVL      @_Step+12,XAR6        ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOVB      ACC,#0
	.dwpsn	"../../include/IQmathCPP.h",4427,58
        CMPL      ACC,XAR6              ; |4427| 
        BF        L14,NEQ               ; |4427| 
        ; branch occurs ; |4427| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       ACC,#512 << 15
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      @_Step+12,ACC         ; |3530| 
L14:    
	.dwpsn	"IQsample.cpp",101,2
        MOVL      XAR4,#FSL4            ; |101| 
        MOVL      *-SP[2],XAR4          ; |101| 
        LCR       #_printf              ; |101| 
        ; call occurs [#_printf] ; |101| 
	.dwpsn	"IQsample.cpp",102,2
        MOVZ      AR4,SP                ; |102| 
        SUBB      XAR4,#28              ; |102| 
        LCR       #_gets                ; |102| 
        ; call occurs [#_gets] ; |102| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVZ      AR4,SP                ; |37| 
        MOVB      ACC,#0
        SUBB      XAR4,#28              ; |37| 
        MOVL      *-SP[4],ACC           ; |37| 
        MOVB      ACC,#24
        LCR       #__atoIQN             ; |37| 
        ; call occurs [#__atoIQN] ; |37| 
        MOVL      *-SP[4],ACC           ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[4]           ; |3530| 
        MOVL      XAR4,#_Step+16        ; |3530| 
        MOVL      *+XAR4[0],ACC         ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOVB      ACC,#0
	.dwpsn	"../../include/IQmathCPP.h",4427,58
        CMPL      ACC,*-SP[4]           ; |4427| 
        BF        L15,NEQ               ; |4427| 
        ; branch occurs ; |4427| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       ACC,#512 << 15
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      *+XAR4[0],ACC         ; |3530| 
L15:    
	.dwpsn	"../../include/IQmathCPP.h",41,33
        MOVB      XAR0,#10              ; |41| 
        MOVL      XAR4,#_Step           ; |41| 
        MOVL      ACC,*+XAR4[AR0]       ; |41| 
        MOVB      XAR0,#12              ; |41| 
        MOVL      *-SP[6],ACC           ; |41| 
        MOVL      ACC,*+XAR4[AR0]       ; |41| 
        MOVZ      AR4,SP                ; |41| 
        MOVZ      AR5,SP                ; |41| 
        MOVL      *-SP[8],ACC           ; |41| 
        SUBB      XAR4,#8               ; |41| 
        MOVL      *-SP[2],XAR4          ; |41| 
        MOVZ      AR4,SP                ; |41| 
        SUBB      XAR5,#6               ; |41| 
        SUBB      XAR4,#4               ; |41| 
        LCR       #_IQmag__F2iqT1       ; |41| 
        ; call occurs [#_IQmag__F2iqT1] ; |41| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[4]           ; |3530| 
        MOVL      *-SP[44],ACC          ; |3530| 
        MOVL      XAR4,#1024
        MOVL      ACC,*-SP[38]
        ADDL      XAR4,ACC
        MOVL      *-SP[46],XAR4
	.dwpsn	"IQsample.cpp",110,6
        MOVB      XAR1,#0
L16:    
DWL$_main$12$B:
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVW      DP,#_Step
        MOVB      ACC,#0
        MOVB      XAR0,#14              ; |37| 
        MOVL      XAR4,#_Step           ; |37| 
        MOVL      XT,@_Step             ; |37| 
        MOVL      *-SP[32],ACC          ; |37| 
        IMPYL     P,XT,*+XAR4[AR0]      ; |37| 
        QMPYL     ACC,XT,*+XAR4[AR0]    ; |37| 
        LSL64     ACC:P,#8              ; |37| 
        ADDB      XAR4,#6               ; |37| 
        MOVL      *-SP[32],ACC          ; |37| 
        ADDL      ACC,*+XAR4[0]         ; |37| 
        MOVL      *-SP[30],ACC          ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[30]          ; |3530| 
        MOVL      *+XAR4[0],ACC         ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       AH,#1608
        MOV       AL,#32472
        MOVL      *-SP[32],ACC          ; |38| 
	.dwpsn	"../../include/IQmathCPP.h",4481,58
        MOVL      ACC,*-SP[32]          ; |4481| 
        CMPL      ACC,*+XAR4[0]         ; |4481| 
        BF        L17,GEQ               ; |4481| 
        ; branch occurs ; |4481| 
DWL$_main$12$E:
DWL$_main$13$B:
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       AH,#1608
        MOV       AL,#32472
	.dwpsn	"../../include/IQmathCPP.h",3650,4
        SUBL      *+XAR4[0],ACC         ; |3650| 
DWL$_main$13$E:
L17:    
DWL$_main$14$B:
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVB      ACC,#0
        MOVL      XAR4,#_Step           ; |37| 
        MOVB      XAR0,#16              ; |37| 
        MOVL      *-SP[30],ACC          ; |37| 
        MOVL      XT,*+XAR4[2]          ; |37| 
        IMPYL     P,XT,*+XAR4[AR0]      ; |37| 
        QMPYL     ACC,XT,*+XAR4[AR0]    ; |37| 
        LSL64     ACC:P,#8              ; |37| 
        ADDB      XAR4,#8               ; |37| 
        MOVL      *-SP[30],ACC          ; |37| 
        ADDL      ACC,*+XAR4[0]         ; |37| 
        MOVL      *-SP[32],ACC          ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[32]          ; |3530| 
        MOVL      *+XAR4[0],ACC         ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       AH,#1608
        MOV       AL,#32472
        MOVL      *-SP[32],ACC          ; |38| 
	.dwpsn	"../../include/IQmathCPP.h",4481,58
        MOVL      ACC,*-SP[32]          ; |4481| 
        CMPL      ACC,*+XAR4[0]         ; |4481| 
        BF        L18,GEQ               ; |4481| 
        ; branch occurs ; |4481| 
DWL$_main$14$E:
DWL$_main$15$B:
	.dwpsn	"../../include/IQmathCPP.h",38,23
        MOV       AH,#1608
        MOV       AL,#32472
	.dwpsn	"../../include/IQmathCPP.h",3650,4
        SUBL      *+XAR4[0],ACC         ; |3650| 
DWL$_main$15$E:
L18:    
DWL$_main$16$B:
	.dwpsn	"../../include/IQmathCPP.h",41,33
        MOVZ      AR5,SP                ; |41| 
        MOVZ      AR4,SP                ; |41| 
        MOVL      XAR3,#_Step           ; |41| 
        MOVL      ACC,*+XAR3[6]         ; |41| 
        SUBB      XAR5,#34              ; |41| 
        SUBB      XAR4,#30              ; |41| 
        MOVL      *-SP[34],ACC          ; |41| 
        LCR       #_IQsin__F2iq         ; |41| 
        ; call occurs [#_IQsin__F2iq] ; |41| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVB      XAR0,#10              ; |37| 
        MOVB      ACC,#0
        MOVL      *-SP[32],ACC          ; |37| 
        MOVL      XT,*-SP[30]           ; |37| 
        IMPYL     P,XT,*+XAR3[AR0]      ; |37| 
        QMPYL     ACC,XT,*+XAR3[AR0]    ; |37| 
        LSL64     ACC:P,#8              ; |37| 
        MOVL      *-SP[32],ACC          ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[32]          ; |3530| 
        MOVL      *-SP[48],ACC          ; |3530| 
        MOVU      ACC,AR1
        LSL       ACC,1                 ; |3530| 
        MOVL      XAR4,ACC              ; |3530| 
        MOVL      XAR2,ACC              ; |3530| 
        MOVL      ACC,*-SP[38]          ; |3530| 
        ADDL      XAR4,ACC
        MOVL      ACC,*-SP[48]          ; |3530| 
        MOVL      *+XAR4[0],ACC         ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",41,33
        MOVZ      AR5,SP                ; |41| 
        MOVB      XAR0,#8               ; |41| 
        MOVZ      AR4,SP                ; |41| 
        MOVL      ACC,*+XAR3[AR0]       ; |41| 
        SUBB      XAR5,#36              ; |41| 
        MOVL      *-SP[36],ACC          ; |41| 
        SUBB      XAR4,#30              ; |41| 
        LCR       #_IQsin__F2iq         ; |41| 
        ; call occurs [#_IQsin__F2iq] ; |41| 
	.dwpsn	"IQsample.cpp",122,3
        MOVZ      AR5,SP                ; |122| 
        MOVZ      AR4,SP                ; |122| 
        SUBB      XAR5,#30              ; |122| 
        SUBB      XAR4,#32              ; |122| 
        LCR       #_IQabs__F2iq         ; |122| 
        ; call occurs [#_IQabs__F2iq] ; |122| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVB      ACC,#0
        MOVL      *-SP[34],ACC          ; |37| 
        MOVL      XT,*-SP[32]           ; |37| 
        MOVB      XAR0,#12              ; |37| 
        IMPYL     P,XT,*+XAR3[AR0]      ; |37| 
        QMPYL     ACC,XT,*+XAR3[AR0]    ; |37| 
        LSL64     ACC:P,#8              ; |37| 
        MOVL      *-SP[34],ACC          ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      XAR4,XAR2             ; |3530| 
        MOVL      ACC,*-SP[40]          ; |3530| 
        ADDL      XAR4,ACC
        MOVL      XAR3,*-SP[34]         ; |3530| 
        MOVL      *+XAR4[0],XAR3        ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",41,33
        MOVL      ACC,*-SP[48]
        MOVZ      AR4,SP                ; |41| 
        MOVL      *-SP[34],ACC          ; |41| 
        MOVL      *-SP[32],XAR3         ; |41| 
        MOVZ      AR5,SP                ; |41| 
        SUBB      XAR4,#32              ; |41| 
        MOVL      *-SP[2],XAR4          ; |41| 
        MOVZ      AR4,SP                ; |41| 
        SUBB      XAR5,#34              ; |41| 
        SUBB      XAR4,#36              ; |41| 
        LCR       #_IQmag__F2iqT1       ; |41| 
        ; call occurs [#_IQmag__F2iqT1] ; |41| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[36]          ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVB      XAR6,#0
        MOVL      *-SP[36],XAR6         ; |37| 
        MOVL      XAR6,*-SP[44]         ; |37| 
        MOVL      *-SP[2],XAR6          ; |37| 
        LCR       #__IQ24div            ; |37| 
        ; call occurs [#__IQ24div] ; |37| 
        MOVL      *-SP[36],ACC          ; |37| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[42]          ; |3530| 
        ADDL      XAR2,ACC
        MOVL      ACC,*-SP[36]          ; |3530| 
        MOVL      *+XAR2[0],ACC         ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",41,33
        MOVZ      AR4,SP                ; |41| 
        MOVL      ACC,*-SP[48]          ; |41| 
        MOVL      *-SP[34],XAR3         ; |41| 
        MOVL      *-SP[32],ACC          ; |41| 
        SUBB      XAR4,#32              ; |41| 
        MOVL      *-SP[2],XAR4          ; |41| 
        MOVZ      AR4,SP                ; |41| 
        MOVZ      AR5,SP                ; |41| 
        SUBB      XAR4,#36              ; |41| 
        SUBB      XAR5,#34              ; |41| 
        LCR       #_IQatan2PU__F2iqT1   ; |41| 
        ; call occurs [#_IQatan2PU__F2iqT1] ; |41| 
	.dwpsn	"../../include/IQmathCPP.h",3530,4
        MOVL      ACC,*-SP[36]          ; |3530| 
	.dwpsn	"../../include/IQmathCPP.h",41,33
        MOVL      *-SP[36],ACC          ; |41| 
	.dwpsn	"../../include/IQmathCPP.h",1770,41
        MOVL      ACC,*-SP[36]          ; |1770| 
        MOVL      XAR4,#360             ; |1770| 
        MOVL      *-SP[2],XAR4          ; |1770| 
        LCR       #__IQ24mpyI32int      ; |1770| 
        ; call occurs [#__IQ24mpyI32int] ; |1770| 
        MOVL      XAR4,*-SP[46]         ; |1770| 
        MOVL      *XAR4++,ACC           ; |1770| 
        MOVL      *-SP[46],XAR4         ; |1770| 
	.dwpsn	"IQsample.cpp",135,3
        ADDB      XAR1,#1               ; |135| 
        CMP       AR1,#256              ; |135| 
        BF        L16,LO                ; |135| 
        ; branch occurs ; |135| 
DWL$_main$16$E:
        MOVB      AL,#0
	.dwpsn	"IQsample.cpp",136,1
        SUBB      SP,#48                ; |135| 
	.dwcfa	0x1d, -8
        MOVL      XAR3,*--SP            ; |135| 
	.dwcfa	0x1d, -6
	.dwcfa	0xc0, 11
        MOVL      XAR2,*--SP            ; |135| 
	.dwcfa	0x1d, -4
	.dwcfa	0xc0, 9
        MOVL      XAR1,*--SP            ; |135| 
	.dwcfa	0x1d, -2
	.dwcfa	0xc0, 7
        LRETR
        ; return occurs

DW$91	.dwtag  DW_TAG_loop
	.dwattr DW$91, DW_AT_name("C:\tidcs\c28\IQmath\cppIQmath\examples\F2812EzDSP_SampleCPP\IQsample.asm:L16:1:1049077875")
	.dwattr DW$91, DW_AT_begin_file("IQsample.cpp")
	.dwattr DW$91, DW_AT_begin_line(0x6e)
	.dwattr DW$91, DW_AT_end_line(0x87)
DW$92	.dwtag  DW_TAG_loop_range
	.dwattr DW$92, DW_AT_low_pc(DWL$_main$12$B)
	.dwattr DW$92, DW_AT_high_pc(DWL$_main$12$E)
DW$93	.dwtag  DW_TAG_loop_range
	.dwattr DW$93, DW_AT_low_pc(DWL$_main$13$B)
	.dwattr DW$93, DW_AT_high_pc(DWL$_main$13$E)
DW$94	.dwtag  DW_TAG_loop_range
	.dwattr DW$94, DW_AT_low_pc(DWL$_main$14$B)
	.dwattr DW$94, DW_AT_high_pc(DWL$_main$14$E)
DW$95	.dwtag  DW_TAG_loop_range
	.dwattr DW$95, DW_AT_low_pc(DWL$_main$15$B)
	.dwattr DW$95, DW_AT_high_pc(DWL$_main$15$E)
DW$96	.dwtag  DW_TAG_loop_range
	.dwattr DW$96, DW_AT_low_pc(DWL$_main$16$B)
	.dwattr DW$96, DW_AT_high_pc(DWL$_main$16$E)
	.dwendtag DW$91


DW$97	.dwtag  DW_TAG_loop
	.dwattr DW$97, DW_AT_name("C:\tidcs\c28\IQmath\cppIQmath\examples\F2812EzDSP_SampleCPP\IQsample.asm:L11:1:1049077875")
	.dwattr DW$97, DW_AT_begin_file("IQsample.cpp")
	.dwattr DW$97, DW_AT_begin_line(0x4c)
	.dwattr DW$97, DW_AT_end_line(0x52)
DW$98	.dwtag  DW_TAG_loop_range
	.dwattr DW$98, DW_AT_low_pc(DWL$_main$2$B)
	.dwattr DW$98, DW_AT_high_pc(DWL$_main$2$E)
	.dwendtag DW$97

	.dwendentry
	.dwendtag DW$66



***	Parameter deleted: this == &Dlog;

	.sect	".text"

DW$99	.dwtag  DW_TAG_subprogram, DW_AT_name("DATA_LOG_C"), DW_AT_symbol_name("___ct__10DATA_LOG_CFv")
	.dwattr DW$99, DW_AT_low_pc(___ct__10DATA_LOG_CFv)
	.dwattr DW$99, DW_AT_high_pc(0x00)

	.dwfde DW$CIE

;***************************************************************
;* FNAME: ___ct__10DATA_LOG_CFv         FR SIZE:   6           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter,  0 Auto,  4 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
___ct__10DATA_LOG_CFv:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
        MOVL      *SP++,XAR1
	.dwcfa	0x80, 7, 2
	.dwcfa	0x1d, -4
        MOVL      *SP++,XAR3
	.dwcfa	0x80, 11, 4
	.dwcfa	0x1d, -6
        ADDB      SP,#2
	.dwcfa	0x1d, -8
;* AR1   assigned to C$1
;* AR3   assigned to C$2
        MOVB      ACC,#2
        MOVL      XAR4,#_Dlog           ; |136| 
        MOVL      XAR3,#___ct__2iqFv    ; |136| 
        MOVL      *-SP[2],ACC           ; |136| 
        MOVL      XAR5,XAR3             ; |136| 
        MOVL      XAR1,XAR4             ; |136| 
        MOV       ACC,#1 << 8
        LCR       #___anew              ; |136| 
        ; call occurs [#___anew] ; |136| 
        MOVB      ACC,#2
        MOVL      XAR4,#512             ; |136| 
        MOVL      *-SP[2],ACC           ; |136| 
        MOVL      XAR5,XAR3             ; |136| 
        MOVL      ACC,XAR1              ; |136| 
        ADDL      XAR4,ACC
        MOV       ACC,#1 << 8
        LCR       #___anew              ; |136| 
        ; call occurs [#___anew] ; |136| 
        MOVB      ACC,#2
        MOVL      *-SP[2],ACC           ; |136| 
        MOVL      XAR4,#1536            ; |136| 
        MOVL      ACC,XAR1              ; |136| 
        ADDL      XAR4,ACC
        MOVL      XAR5,XAR3             ; |136| 
        MOV       ACC,#1 << 8
        LCR       #___anew              ; |136| 
        ; call occurs [#___anew] ; |136| 
        SUBB      SP,#2
	.dwcfa	0x1d, -6
        MOVL      XAR3,*--SP
	.dwcfa	0x1d, -4
	.dwcfa	0xc0, 11
        MOVL      XAR1,*--SP
	.dwcfa	0x1d, -2
	.dwcfa	0xc0, 7
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag DW$99



***	Parameter deleted: this == &Step;

	.sect	".text"

DW$100	.dwtag  DW_TAG_subprogram, DW_AT_name("STEP"), DW_AT_symbol_name("___ct__4STEPFv")
	.dwattr DW$100, DW_AT_low_pc(___ct__4STEPFv)
	.dwattr DW$100, DW_AT_high_pc(0x00)

	.dwfde DW$CIE

;***************************************************************
;* FNAME: ___ct__4STEPFv                FR SIZE:   0           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            0 Parameter,  0 Auto,  0 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
___ct__4STEPFv:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
;* AR4   assigned to C$1
	.dwpsn	"../../include/IQmathCPP.h",37,17
        MOVB      ACC,#0
        MOVL      XAR4,#_Step           ; |37| 
        MOVL      *+XAR4[0],ACC         ; |37| 
        MOVL      *+XAR4[2],ACC         ; |37| 
        MOVL      *+XAR4[4],ACC         ; |37| 
        MOVB      XAR0,#8               ; |37| 
        MOVL      *+XAR4[6],ACC         ; |37| 
        MOVL      *+XAR4[AR0],ACC       ; |37| 
        MOVB      XAR0,#10              ; |37| 
        MOVL      *+XAR4[AR0],ACC       ; |37| 
        MOVB      XAR0,#12              ; |37| 
        MOVL      *+XAR4[AR0],ACC       ; |37| 
        MOVB      XAR0,#14              ; |37| 
        MOVL      *+XAR4[AR0],ACC       ; |37| 
        MOVB      XAR0,#16              ; |37| 
        MOVL      *+XAR4[AR0],ACC       ; |37| 
	.dwpsn	"IQsample.cpp",136,1
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag DW$100




	.sect	".pinit"
	.align	2
	.field	___sti__IQsample_cpp_GlobalQ, 22

	.sect	".text"
	.global	___sti__IQsample_cpp_GlobalQ

DW$101	.dwtag  DW_TAG_subprogram, DW_AT_name("__sti__IQsample_cpp_GlobalQ"), DW_AT_symbol_name("___sti__IQsample_cpp_GlobalQ")
	.dwattr DW$101, DW_AT_low_pc(___sti__IQsample_cpp_GlobalQ)
	.dwattr DW$101, DW_AT_high_pc(0x00)

	.dwfde DW$CIE

;***************************************************************
;* FNAME: ___sti__IQsample_cpp_GlobalQ  FR SIZE:   0           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            0 Parameter,  0 Auto,  0 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
___sti__IQsample_cpp_GlobalQ:
	.dwcfa	0x1c, 26, 0
	.dwcfa	0x09, 38, 26
	.dwpsn	"IQsample.cpp",38,3
        LCR       #___ct__10DATA_LOG_CFv ; |38| 
        ; call occurs [#___ct__10DATA_LOG_CFv] ; |38| 
	.dwpsn	"IQsample.cpp",51,3
        LCR       #___ct__4STEPFv       ; |51| 
        ; call occurs [#___ct__4STEPFv] ; |51| 
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag DW$101



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
	.global	___nw__FUl
	.global	___anew
	.global	__IQ24atan2PU
	.global	__atoIQN
	.global	__IQ24mpyI32int
	.global	__IQ24mag
	.global	__IQ24div
	.global	_gets
	.global	__IQ24sin

;***************************************************************
;* TYPE INFORMATION                                            *
;***************************************************************
DWT$11	.dwtag  DW_TAG_base_type, DW_AT_name("int")
	.dwattr DWT$11, DW_AT_encoding(DW_ATE_signed)
	.dwattr DWT$11, DW_AT_byte_size(0x01)
DWT$1018	.dwtag  DW_TAG_pointer_type, DW_AT_type(*DWT$11)
	.dwattr DWT$1018, DW_AT_address_class(0x16)
DWT$1027	.dwtag  DW_TAG_pointer_type, DW_AT_type(*DWT$1019)
	.dwattr DWT$1027, DW_AT_address_class(0x16)
DWT$1021	.dwtag  DW_TAG_pointer_type, DW_AT_type(*DWT$1020)
	.dwattr DWT$1021, DW_AT_address_class(0x16)

DWT$1053	.dwtag  DW_TAG_array_type, DW_AT_type(*DWT$1019)
	.dwattr DWT$1053, DW_AT_byte_size(0x14)
DW$102	.dwtag  DW_TAG_subrange_type
	.dwattr DW$102, DW_AT_upper_bound(0x13)
	.dwendtag DWT$1053

DWT$10	.dwtag  DW_TAG_base_type, DW_AT_name("unsigned int")
	.dwattr DWT$10, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr DWT$10, DW_AT_byte_size(0x01)
DWT$13	.dwtag  DW_TAG_base_type, DW_AT_name("long")
	.dwattr DWT$13, DW_AT_encoding(DW_ATE_signed)
	.dwattr DWT$13, DW_AT_byte_size(0x02)
DWT$12	.dwtag  DW_TAG_base_type, DW_AT_name("unsigned long")
	.dwattr DWT$12, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr DWT$12, DW_AT_byte_size(0x02)
DWT$3	.dwtag  DW_TAG_pointer_type
	.dwattr DWT$3, DW_AT_address_class(0x16)

DWT$1072	.dwtag  DW_TAG_subroutine_type

DWT$1075	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$3)
DW$103	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$12)
	.dwendtag DWT$1075


DWT$1077	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$3)

DWT$1079	.dwtag  DW_TAG_subroutine_type
DW$104	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
DW$105	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1021)
	.dwendtag DWT$1079


DWT$1080	.dwtag  DW_TAG_subroutine_type
DW$106	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
DW$107	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
	.dwendtag DWT$1080


DWT$1082	.dwtag  DW_TAG_subroutine_type
DW$108	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
DW$109	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
DW$110	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
	.dwendtag DWT$1082


DWT$1084	.dwtag  DW_TAG_subroutine_type
DW$111	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
DW$112	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1043)
DW$113	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1043)
	.dwendtag DWT$1084

DWT$1019	.dwtag  DW_TAG_base_type, DW_AT_name("signed char")
	.dwattr DWT$1019, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr DWT$1019, DW_AT_byte_size(0x01)
DW$114	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$1019)
DWT$1020	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$114)

DWT$1106	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$1027)
DW$115	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1027)
	.dwendtag DWT$1106


DWT$1041	.dwtag  DW_TAG_structure_type
	.dwattr DWT$1041, DW_AT_name("iq")
	.dwattr DWT$1041, DW_AT_byte_size(0x02)
DW$116	.dwtag  DW_TAG_member, DW_AT_type(*DWT$13)
	.dwattr DW$116, DW_AT_name("val"), DW_AT_symbol_name("_val")
	.dwattr DW$116, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr DW$116, DW_AT_accessibility(DW_ACCESS_public)

DW$117	.dwtag  DW_TAG_subprogram, DW_AT_name("iq"), DW_AT_symbol_name("___ct__2iqFv")
	.dwattr DW$117, DW_AT_declaration(0x01)
	.dwattr DW$117, DW_AT_accessibility(DW_ACCESS_public)

DW$118	.dwtag  DW_TAG_subprogram, DW_AT_name("iq"), DW_AT_symbol_name("___ct__2iqFl")
	.dwattr DW$118, DW_AT_declaration(0x01)
	.dwattr DW$118, DW_AT_accessibility(DW_ACCESS_public)
DW$119	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DW$118


DW$120	.dwtag  DW_TAG_subprogram, DW_AT_name("iq"), DW_AT_symbol_name("___ct__2iqFRC2iq")
	.dwattr DW$120, DW_AT_declaration(0x01)
	.dwattr DW$120, DW_AT_accessibility(DW_ACCESS_public)
DW$121	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1036)
	.dwendtag DW$120


DW$122	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ="), DW_AT_symbol_name("___as__2iqFRC2iq")
	.dwattr DW$122, DW_AT_declaration(0x01)
	.dwattr DW$122, DW_AT_accessibility(DW_ACCESS_public)
DW$123	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1036)
	.dwendtag DW$122


DW$124	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +="), DW_AT_symbol_name("___apl__2iqFRC2iq")
	.dwattr DW$124, DW_AT_declaration(0x01)
	.dwattr DW$124, DW_AT_accessibility(DW_ACCESS_public)
DW$125	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1036)
	.dwendtag DW$124


DW$126	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -="), DW_AT_symbol_name("___ami__2iqFRC2iq")
	.dwattr DW$126, DW_AT_declaration(0x01)
	.dwattr DW$126, DW_AT_accessibility(DW_ACCESS_public)
DW$127	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1036)
	.dwendtag DW$126


DW$128	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *="), DW_AT_symbol_name("___amu__2iqFRC2iq")
	.dwattr DW$128, DW_AT_declaration(0x01)
	.dwattr DW$128, DW_AT_accessibility(DW_ACCESS_public)
DW$129	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1036)
	.dwendtag DW$128


DW$130	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /="), DW_AT_symbol_name("___adv__2iqFRC2iq")
	.dwattr DW$130, DW_AT_declaration(0x01)
	.dwattr DW$130, DW_AT_accessibility(DW_ACCESS_public)
DW$131	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1036)
	.dwendtag DW$130


DW$132	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &="), DW_AT_symbol_name("___aad__2iqFRCl")
	.dwattr DW$132, DW_AT_declaration(0x01)
	.dwattr DW$132, DW_AT_accessibility(DW_ACCESS_public)
DW$133	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1039)
	.dwendtag DW$132


DW$134	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |="), DW_AT_symbol_name("___aor__2iqFRCl")
	.dwattr DW$134, DW_AT_declaration(0x01)
	.dwattr DW$134, DW_AT_accessibility(DW_ACCESS_public)
DW$135	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1039)
	.dwendtag DW$134


DW$136	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^="), DW_AT_symbol_name("___aer__2iqFRCl")
	.dwattr DW$136, DW_AT_declaration(0x01)
	.dwattr DW$136, DW_AT_accessibility(DW_ACCESS_public)
DW$137	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1039)
	.dwendtag DW$136

	.dwendtag DWT$1041

DWT$1036	.dwtag  DW_TAG_reference_type, DW_AT_type(*DWT$1035)
	.dwattr DWT$1036, DW_AT_address_class(0x16)
DWT$1043	.dwtag  DW_TAG_reference_type, DW_AT_type(*DWT$1042)
	.dwattr DWT$1043, DW_AT_address_class(0x16)
DW$138	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$1041)
DWT$1044	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$138)
DWT$1066	.dwtag  DW_TAG_pointer_type, DW_AT_type(*DWT$1041)
	.dwattr DWT$1066, DW_AT_address_class(0x16)

DWT$1087	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$13)
DW$139	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DWT$1087


DWT$1088	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$13)
DW$140	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$141	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$142	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$11)
	.dwendtag DWT$1088


DWT$1089	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$13)
DW$143	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
DW$144	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DWT$1089


DWT$1090	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$13)
DW$145	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1021)
DW$146	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DWT$1090


DWT$1091	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$13)
DW$147	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
DW$148	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DWT$1091

DW$149	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$1066)
DWT$1092	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$149)

DWT$1095	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$1032)
DW$150	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
	.dwendtag DWT$1095


DWT$1097	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$1032)
DW$151	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
DW$152	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$13)
	.dwendtag DWT$1097


DWT$1098	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$1032)
DW$153	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1066)
DW$154	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1043)
	.dwendtag DWT$1098


DWT$1101	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$1032)
DW$155	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1099)
DW$156	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1043)
	.dwendtag DWT$1101


DWT$1108	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$11)
DW$157	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1021)
DW$158	.dwtag  DW_TAG_unspecified_parameters
	.dwendtag DWT$1108


DWT$1109	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$11)

DWT$1112	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$4)
DW$159	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1043)
DW$160	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1043)
	.dwendtag DWT$1112


DWT$1119	.dwtag  DW_TAG_structure_type
	.dwattr DWT$1119, DW_AT_name("DATA_LOG_C")
	.dwattr DWT$1119, DW_AT_byte_size(0x800)
DW$161	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1102)
	.dwattr DW$161, DW_AT_name("Xwaveform"), DW_AT_symbol_name("_Xwaveform")
	.dwattr DW$161, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr DW$161, DW_AT_accessibility(DW_ACCESS_public)
DW$162	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1102)
	.dwattr DW$162, DW_AT_name("Ywaveform"), DW_AT_symbol_name("_Ywaveform")
	.dwattr DW$162, DW_AT_data_member_location[DW_OP_plus_uconst 0x200]
	.dwattr DW$162, DW_AT_accessibility(DW_ACCESS_public)
DW$163	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1113)
	.dwattr DW$163, DW_AT_name("Phase"), DW_AT_symbol_name("_Phase")
	.dwattr DW$163, DW_AT_data_member_location[DW_OP_plus_uconst 0x400]
	.dwattr DW$163, DW_AT_accessibility(DW_ACCESS_public)
DW$164	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1102)
	.dwattr DW$164, DW_AT_name("Mag"), DW_AT_symbol_name("_Mag")
	.dwattr DW$164, DW_AT_data_member_location[DW_OP_plus_uconst 0x600]
	.dwattr DW$164, DW_AT_accessibility(DW_ACCESS_public)

DW$165	.dwtag  DW_TAG_subprogram, DW_AT_name("DATA_LOG_C"), DW_AT_symbol_name("___ct__10DATA_LOG_CFv")
	.dwattr DW$165, DW_AT_declaration(0x01)
	.dwattr DW$165, DW_AT_accessibility(DW_ACCESS_public)

DW$166	.dwtag  DW_TAG_subprogram, DW_AT_name("DATA_LOG_C"), DW_AT_symbol_name("___ct__10DATA_LOG_CFRC10DATA_LOG_C")
	.dwattr DW$166, DW_AT_declaration(0x01)
	.dwattr DW$166, DW_AT_accessibility(DW_ACCESS_public)
DW$167	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1117)
	.dwendtag DW$166


DW$168	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ="), DW_AT_symbol_name("___as__10DATA_LOG_CFRC10DATA_LOG_C")
	.dwattr DW$168, DW_AT_declaration(0x01)
	.dwattr DW$168, DW_AT_accessibility(DW_ACCESS_public)
DW$169	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1117)
	.dwendtag DW$168

	.dwendtag DWT$1119

DWT$1117	.dwtag  DW_TAG_reference_type, DW_AT_type(*DWT$1116)
	.dwattr DWT$1117, DW_AT_address_class(0x16)

DWT$1125	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$1114)
DW$170	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1123)
	.dwendtag DWT$1125

DWT$1123	.dwtag  DW_TAG_pointer_type, DW_AT_type(*DWT$1119)
	.dwattr DWT$1123, DW_AT_address_class(0x16)

DWT$1133	.dwtag  DW_TAG_structure_type
	.dwattr DWT$1133, DW_AT_name("STEP")
	.dwattr DWT$1133, DW_AT_byte_size(0x12)
DW$171	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$171, DW_AT_name("Xsize"), DW_AT_symbol_name("_Xsize")
	.dwattr DW$171, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr DW$171, DW_AT_accessibility(DW_ACCESS_public)
DW$172	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$172, DW_AT_name("Ysize"), DW_AT_symbol_name("_Ysize")
	.dwattr DW$172, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr DW$172, DW_AT_accessibility(DW_ACCESS_public)
DW$173	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$173, DW_AT_name("Yoffset"), DW_AT_symbol_name("_Yoffset")
	.dwattr DW$173, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr DW$173, DW_AT_accessibility(DW_ACCESS_public)
DW$174	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$174, DW_AT_name("X"), DW_AT_symbol_name("_X")
	.dwattr DW$174, DW_AT_data_member_location[DW_OP_plus_uconst 0x6]
	.dwattr DW$174, DW_AT_accessibility(DW_ACCESS_public)
DW$175	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$175, DW_AT_name("Y"), DW_AT_symbol_name("_Y")
	.dwattr DW$175, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr DW$175, DW_AT_accessibility(DW_ACCESS_public)
DW$176	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$176, DW_AT_name("GainX"), DW_AT_symbol_name("_GainX")
	.dwattr DW$176, DW_AT_data_member_location[DW_OP_plus_uconst 0xa]
	.dwattr DW$176, DW_AT_accessibility(DW_ACCESS_public)
DW$177	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$177, DW_AT_name("GainY"), DW_AT_symbol_name("_GainY")
	.dwattr DW$177, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr DW$177, DW_AT_accessibility(DW_ACCESS_public)
DW$178	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$178, DW_AT_name("FreqX"), DW_AT_symbol_name("_FreqX")
	.dwattr DW$178, DW_AT_data_member_location[DW_OP_plus_uconst 0xe]
	.dwattr DW$178, DW_AT_accessibility(DW_ACCESS_public)
DW$179	.dwtag  DW_TAG_member, DW_AT_type(*DWT$1041)
	.dwattr DW$179, DW_AT_name("FreqY"), DW_AT_symbol_name("_FreqY")
	.dwattr DW$179, DW_AT_data_member_location[DW_OP_plus_uconst 0x10]
	.dwattr DW$179, DW_AT_accessibility(DW_ACCESS_public)

DW$180	.dwtag  DW_TAG_subprogram, DW_AT_name("STEP"), DW_AT_symbol_name("___ct__4STEPFv")
	.dwattr DW$180, DW_AT_declaration(0x01)
	.dwattr DW$180, DW_AT_accessibility(DW_ACCESS_public)

DW$181	.dwtag  DW_TAG_subprogram, DW_AT_name("STEP"), DW_AT_symbol_name("___ct__4STEPFRC4STEP")
	.dwattr DW$181, DW_AT_declaration(0x01)
	.dwattr DW$181, DW_AT_accessibility(DW_ACCESS_public)
DW$182	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1131)
	.dwendtag DW$181


DW$183	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ="), DW_AT_symbol_name("___as__4STEPFRC4STEP")
	.dwattr DW$183, DW_AT_declaration(0x01)
	.dwattr DW$183, DW_AT_accessibility(DW_ACCESS_public)
DW$184	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1131)
	.dwendtag DW$183

	.dwendtag DWT$1133

DWT$1131	.dwtag  DW_TAG_reference_type, DW_AT_type(*DWT$1130)
	.dwattr DWT$1131, DW_AT_address_class(0x16)

DWT$1138	.dwtag  DW_TAG_subroutine_type, DW_AT_type(*DWT$1128)
DW$185	.dwtag  DW_TAG_formal_parameter, DW_AT_type(*DWT$1136)
	.dwendtag DWT$1138

DWT$1136	.dwtag  DW_TAG_pointer_type, DW_AT_type(*DWT$1133)
	.dwattr DWT$1136, DW_AT_address_class(0x16)
DWT$4	.dwtag  DW_TAG_base_type, DW_AT_name("bool")
	.dwattr DWT$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr DWT$4, DW_AT_byte_size(0x01)
DWT$1039	.dwtag  DW_TAG_reference_type, DW_AT_type(*DWT$1038)
	.dwattr DWT$1039, DW_AT_address_class(0x16)
DW$186	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$13)
DWT$1038	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$186)

DWT$1113	.dwtag  DW_TAG_array_type, DW_AT_type(*DWT$13)
	.dwattr DWT$1113, DW_AT_byte_size(0x200)
DW$187	.dwtag  DW_TAG_subrange_type
	.dwattr DW$187, DW_AT_upper_bound(0xff)
	.dwendtag DWT$1113

DWT$1032	.dwtag  DW_TAG_reference_type, DW_AT_type(*DWT$1041)
	.dwattr DWT$1032, DW_AT_address_class(0x16)
DW$188	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$1041)
DWT$1035	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$188)
DW$189	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$1041)
DWT$1042	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$189)
DW$190	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$1066)
DWT$1099	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$190)

DWT$1102	.dwtag  DW_TAG_array_type, DW_AT_type(*DWT$1041)
	.dwattr DWT$1102, DW_AT_byte_size(0x200)
DW$191	.dwtag  DW_TAG_subrange_type
	.dwattr DW$191, DW_AT_upper_bound(0xff)
	.dwendtag DWT$1102

DWT$1114	.dwtag  DW_TAG_reference_type, DW_AT_type(*DWT$1119)
	.dwattr DWT$1114, DW_AT_address_class(0x16)
DW$192	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$1119)
DWT$1116	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$192)
DWT$1128	.dwtag  DW_TAG_reference_type, DW_AT_type(*DWT$1133)
	.dwattr DWT$1128, DW_AT_address_class(0x16)
DW$193	.dwtag  DW_TAG_far_type, DW_AT_type(*DWT$1133)
DWT$1130	.dwtag  DW_TAG_const_type, DW_AT_type(*DW$193)

	.dwattr DW$132, DW_AT_type(*DWT$1032)
	.dwattr DW$130, DW_AT_type(*DWT$1032)
	.dwattr DW$136, DW_AT_type(*DWT$1032)
	.dwattr DW$126, DW_AT_type(*DWT$1032)
	.dwattr DW$128, DW_AT_type(*DWT$1032)
	.dwattr DW$134, DW_AT_type(*DWT$1032)
	.dwattr DW$124, DW_AT_type(*DWT$1032)
	.dwattr DW$168, DW_AT_type(*DWT$1114)
	.dwattr DW$122, DW_AT_type(*DWT$1032)
	.dwattr DW$183, DW_AT_type(*DWT$1128)
	.dwattr DW$166, DW_AT_type(*DWT$1114)
	.dwattr DW$99, DW_AT_specification(*DW$165)
	.dwattr DW$165, DW_AT_type(*DWT$1114)
	.dwattr DW$120, DW_AT_type(*DWT$1032)
	.dwattr DW$118, DW_AT_type(*DWT$1032)
	.dwattr DW$35, DW_AT_specification(*DW$117)
	.dwattr DW$117, DW_AT_type(*DWT$1032)
	.dwattr DW$181, DW_AT_type(*DWT$1128)
	.dwattr DW$100, DW_AT_specification(*DW$180)
	.dwattr DW$180, DW_AT_type(*DWT$1128)
	.dwattr DW$101, DW_AT_external(0x01)
	.dwattr DW$66, DW_AT_external(0x01)
	.dwattr DW$66, DW_AT_type(*DWT$11)
	.dwattr DWCU, DW_AT_language(DW_LANG_C_plus_plus)

;***************************************************************
;* DWARF CIE ENTRIES                                           *
;***************************************************************

DW$CIE	.dwcie 1, 38
	.dwcfa	0x0c, 20, 0
	.dwcfa	0x1d, -2
	.dwcfa	0x07, 0
	.dwcfa	0x07, 1
	.dwcfa	0x07, 2
	.dwcfa	0x07, 3
	.dwcfa	0x07, 4
	.dwcfa	0x07, 5
	.dwcfa	0x08, 6
	.dwcfa	0x08, 7
	.dwcfa	0x08, 8
	.dwcfa	0x08, 9
	.dwcfa	0x08, 10
	.dwcfa	0x08, 11
	.dwcfa	0x07, 12
	.dwcfa	0x07, 13
	.dwcfa	0x07, 14
	.dwcfa	0x07, 15
	.dwcfa	0x07, 16
	.dwcfa	0x07, 17
	.dwcfa	0x07, 18
	.dwcfa	0x07, 19
	.dwcfa	0x07, 20
	.dwcfa	0x07, 21
	.dwcfa	0x07, 22
	.dwcfa	0x07, 23
	.dwcfa	0x07, 24
	.dwcfa	0x07, 25
	.dwcfa	0x07, 26
	.dwcfa	0x08, 27
	.dwcfa	0x07, 28
	.dwcfa	0x07, 29
	.dwcfa	0x07, 30
	.dwcfa	0x07, 31
	.dwcfa	0x07, 32
	.dwcfa	0x07, 33
	.dwcfa	0x07, 34
	.dwcfa	0x07, 35
	.dwcfa	0x07, 36
	.dwcfa	0x07, 37
	.dwcfa	0x07, 38

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

DW$194	.dwtag  DW_TAG_assign_register, DW_AT_name("AL")
	.dwattr DW$194, DW_AT_location[DW_OP_reg0]
DW$195	.dwtag  DW_TAG_assign_register, DW_AT_name("AH")
	.dwattr DW$195, DW_AT_location[DW_OP_reg1]
DW$196	.dwtag  DW_TAG_assign_register, DW_AT_name("PL")
	.dwattr DW$196, DW_AT_location[DW_OP_reg2]
DW$197	.dwtag  DW_TAG_assign_register, DW_AT_name("PH")
	.dwattr DW$197, DW_AT_location[DW_OP_reg3]
DW$198	.dwtag  DW_TAG_assign_register, DW_AT_name("AR0")
	.dwattr DW$198, DW_AT_location[DW_OP_reg4]
DW$199	.dwtag  DW_TAG_assign_register, DW_AT_name("XAR0")
	.dwattr DW$199, DW_AT_location[DW_OP_reg5]
DW$200	.dwtag  DW_TAG_assign_register, DW_AT_name("AR1")
	.dwattr DW$200, DW_AT_location[DW_OP_reg6]
DW$201	.dwtag  DW_TAG_assign_register, DW_AT_name("XAR1")
	.dwattr DW$201, DW_AT_location[DW_OP_reg7]
DW$202	.dwtag  DW_TAG_assign_register, DW_AT_name("AR2")
	.dwattr DW$202, DW_AT_location[DW_OP_reg8]
DW$203	.dwtag  DW_TAG_assign_register, DW_AT_name("XAR2")
	.dwattr DW$203, DW_AT_location[DW_OP_reg9]
DW$204	.dwtag  DW_TAG_assign_register, DW_AT_name("AR3")
	.dwattr DW$204, DW_AT_location[DW_OP_reg10]
DW$205	.dwtag  DW_TAG_assign_register, DW_AT_name("XAR3")
	.dwattr DW$205, DW_AT_location[DW_OP_reg11]
DW$206	.dwtag  DW_TAG_assign_register, DW_AT_name("AR4")
	.dwattr DW$206, DW_AT_location[DW_OP_reg12]
DW$207	.dwtag  DW_TAG_assign_register, DW_AT_name("XAR4")
	.dwattr DW$207, DW_AT_location[DW_OP_reg13]
DW$208	.dwtag  DW_TAG_assign_register, DW_AT_name("AR5")
	.dwattr DW$208, DW_AT_location[DW_OP_reg14]
DW$209	.dwtag  DW_TAG_assign_register, DW_AT_name("XAR5")
	.dwattr DW$209, DW_AT_location[DW_OP_reg15]
DW$210	.dwtag  DW_TAG_assign_register, DW_AT_name("AR6")
	.dwattr DW$210, DW_AT_location[DW_OP_reg16]
DW$211	.dwtag  DW_TAG_assign_register, DW_AT_name("XAR6")
	.dwattr DW$211, DW_AT_location[DW_OP_reg17]
DW$212	.dwtag  DW_TAG_assign_register, DW_AT_name("AR7")
	.dwattr DW$212, DW_AT_location[DW_OP_reg18]
DW$213	.dwtag  DW_TAG_assign_register, DW_AT_name("XAR7")
	.dwattr DW$213, DW_AT_location[DW_OP_reg19]
DW$214	.dwtag  DW_TAG_assign_register, DW_AT_name("SP")
	.dwattr DW$214, DW_AT_location[DW_OP_reg20]
DW$215	.dwtag  DW_TAG_assign_register, DW_AT_name("XT")
	.dwattr DW$215, DW_AT_location[DW_OP_reg21]
DW$216	.dwtag  DW_TAG_assign_register, DW_AT_name("T")
	.dwattr DW$216, DW_AT_location[DW_OP_reg22]
DW$217	.dwtag  DW_TAG_assign_register, DW_AT_name("ST0")
	.dwattr DW$217, DW_AT_location[DW_OP_reg23]
DW$218	.dwtag  DW_TAG_assign_register, DW_AT_name("ST1")
	.dwattr DW$218, DW_AT_location[DW_OP_reg24]
DW$219	.dwtag  DW_TAG_assign_register, DW_AT_name("PC")
	.dwattr DW$219, DW_AT_location[DW_OP_reg25]
DW$220	.dwtag  DW_TAG_assign_register, DW_AT_name("RPC")
	.dwattr DW$220, DW_AT_location[DW_OP_reg26]
DW$221	.dwtag  DW_TAG_assign_register, DW_AT_name("FP")
	.dwattr DW$221, DW_AT_location[DW_OP_reg27]
DW$222	.dwtag  DW_TAG_assign_register, DW_AT_name("DP")
	.dwattr DW$222, DW_AT_location[DW_OP_reg28]
DW$223	.dwtag  DW_TAG_assign_register, DW_AT_name("SXM")
	.dwattr DW$223, DW_AT_location[DW_OP_reg29]
DW$224	.dwtag  DW_TAG_assign_register, DW_AT_name("PM")
	.dwattr DW$224, DW_AT_location[DW_OP_reg30]
DW$225	.dwtag  DW_TAG_assign_register, DW_AT_name("OVM")
	.dwattr DW$225, DW_AT_location[DW_OP_reg31]
DW$226	.dwtag  DW_TAG_assign_register, DW_AT_name("PAGE0")
	.dwattr DW$226, DW_AT_location[DW_OP_regx 0x20]
DW$227	.dwtag  DW_TAG_assign_register, DW_AT_name("IFR")
	.dwattr DW$227, DW_AT_location[DW_OP_regx 0x21]
DW$228	.dwtag  DW_TAG_assign_register, DW_AT_name("IER")
	.dwattr DW$228, DW_AT_location[DW_OP_regx 0x22]
DW$229	.dwtag  DW_TAG_assign_register, DW_AT_name("PSEUDO")
	.dwattr DW$229, DW_AT_location[DW_OP_regx 0x23]
DW$230	.dwtag  DW_TAG_assign_register, DW_AT_name("PSEUDOH")
	.dwattr DW$230, DW_AT_location[DW_OP_regx 0x24]
DW$231	.dwtag  DW_TAG_assign_register, DW_AT_name("VOL")
	.dwattr DW$231, DW_AT_location[DW_OP_regx 0x25]
DW$232	.dwtag  DW_TAG_assign_register, DW_AT_name("CIE_RETA")
	.dwattr DW$232, DW_AT_location[DW_OP_regx 0x26]
	.dwendtag DWCU

