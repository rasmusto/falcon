// TI File $Revision: /main/5 $
// Checkin $Date: July 29, 2008   17:19:44 $
//###########################################################################
//
// FILE:   DSP2834x_SysCtrl.h
//
// TITLE:  DSP2834x Device System Control Register Definitions.
//
//###########################################################################
// $TI Release: 2834x Header Files Internal Release 3 $
// $Release Date: August 29, 2008 $
//###########################################################################

#ifndef DSP2834x_SYS_CTRL_H
#define DSP2834x_SYS_CTRL_H


#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// System Control Individual Register Bit Definitions:
//


// PLL Status Register
struct PLLSTS_BITS   {    // bits  description
   Uint16 PLLLOCKS:1;     // 0     PLL lock status
   Uint16 rsvd1:1;        // 1     reserved
   Uint16 PLLOFF:1;       // 2     PLL off bit
   Uint16 rsvd2:1;        // 3     Missing clock status bit
   Uint16 rsvd3:1;        // 4     Missing clock clear bit
   Uint16 rsvd4:1;        // 5     Oscillator clock off
   Uint16 rsvd5:1;        // 6     Missing clock detect
   Uint16 DIVSEL:2;       // 8:7   Divide Select
   Uint16 rsvd6:7;        // 15:9  reserved
};

union PLLSTS_REG {
   Uint16              all;
   struct PLLSTS_BITS  bit;
};

// High speed peripheral clock register bit definitions:
struct HISPCP_BITS  {   // bits  description
   Uint16 HSPCLK:5;     // 4:0   Rate relative to SYSCLKOUT
   Uint16 rsvd1:11;     // 15:5  reserved
};

union HISPCP_REG {
   Uint16              all;
   struct HISPCP_BITS  bit;
};

// Low speed peripheral clock register bit definitions:
struct LOSPCP_BITS  {   // bits  description
   Uint16 LSPCLK:3;     // 2:0   Rate relative to SYSCLKOUT
   Uint16 rsvd1:13;     // 15:3  reserved
};

union LOSPCP_REG {
   Uint16              all;
   struct LOSPCP_BITS  bit;
};

// Peripheral clock control register 0 bit definitions:
struct PCLKCR0_BITS  {   // bits  description
   Uint16 rsvd1:2;       // 1:0   reserved
   Uint16 TBCLKSYNC:1;   // 2     EWPM Module TBCLK enable/sync
   Uint16 rsvd2:1;       // 3     reserved
   Uint16 I2CAENCLK:1;   // 4     Enable SYSCLKOUT to I2C-A
   Uint16 SCICENCLK:1;   // 5     Enalbe low speed clk to SCI-C
   Uint16 rsvd3:1;       // 6     reserved
   Uint16 SPIDENCLK:1;   // 7     Enable low speed clk to SPI-D
   Uint16 SPIAENCLK:1;   // 8     Enable low speed clk to SPI-A
   Uint16 rsvd4:1;       // 9     reserved
   Uint16 SCIAENCLK:1;   // 10    Enable low speed clk to SCI-A
   Uint16 SCIBENCLK:1;   // 11    Enable low speed clk to SCI-B
   Uint16 MCBSPAENCLK:1; // 12    Enable low speed clk to McBSP-A
   Uint16 MCBSPBENCLK:1; // 13    Enable low speed clk to McBSP-B
   Uint16 ECANAENCLK:1;  // 14    Enable system clk to eCAN-A
   Uint16 ECANBENCLK:1;  // 15    Enable system clk to eCAN-B
};

union PCLKCR0_REG {
   Uint16              all;
   struct PCLKCR0_BITS bit;
};

// Peripheral clock control register 1 bit definitions:
struct PCLKCR1_BITS  {    // bits  description
   Uint16 EPWM1ENCLK:1;   // 0     Enable SYSCLKOUT to EPWM1
   Uint16 EPWM2ENCLK:1;   // 1     Enable SYSCLKOUT to EPWM2
   Uint16 EPWM3ENCLK:1;   // 2     Enable SYSCLKOUT to EPWM3
   Uint16 EPWM4ENCLK:1;   // 3     Enable SYSCLKOUT to EPWM4
   Uint16 EPWM5ENCLK:1;   // 4     Enable SYSCLKOUT to EPWM5
   Uint16 EPWM6ENCLK:1;   // 5     Enable SYSCLKOUT to EPWM6
   Uint16 EPWM7ENCLK:1;   // 6     Enable SYSCLKOUT to EPWM7
   Uint16 EPWM8ENCLK:1;   // 7     Enable SYSCLKOUT to EPWM8
   Uint16 ECAP1ENCLK:1;   // 8     Enable SYSCLKOUT to ECAP1
   Uint16 ECAP2ENCLK:1;   // 9     Enable SYSCLKOUT to ECAP2
   Uint16 ECAP3ENCLK:1;   // 10    Enable SYSCLKOUT to ECAP3
   Uint16 ECAP4ENCLK:1;   // 11    Enable SYSCLKOUT to ECAP4
   Uint16 ECAP5ENCLK:1;   // 12    Enable SYSCLKOUT to ECAP5
   Uint16 ECAP6ENCLK:1;   // 13    Enable SYSCLKOUT to ECAP6
   Uint16 EQEP1ENCLK:1;   // 14    Enable SYSCLKOUT to EQEP1
   Uint16 EQEP2ENCLK:1;   // 15    Enable SYSCLKOUT to EQEP2
};

union PCLKCR1_REG {
   Uint16              all;
   struct PCLKCR1_BITS bit;
};

// Peripheral clock control register 2 bit definitions:
struct PCLKCR2_BITS  {    // bits  description
   Uint16 EPWM9ENCLK:1;   // 0     Enable SYSCLKOUT to EPWM9
   Uint16 rsvd1:7;        // 7:1   reserved
   Uint16 EQEP3ENCLK:1;   // 8     Enable SYSCLKOUT to ECAP1
   Uint16 rsvd2:7;        // 15:9  reserved
};

union PCLKCR2_REG {
   Uint16              all;
   struct PCLKCR2_BITS bit;
};

// Peripheral clock control register 3 bit definitions:
struct PCLKCR3_BITS  {        // bits  description
   Uint16 rsvd1:8;            // 7:0   reserved
   Uint16 CPUTIMER0ENCLK:1;   // 8     Enable SYSCLKOUT to CPU-Timer 0
   Uint16 CPUTIMER1ENCLK:1;   // 9     Enable SYSCLKOUT to CPU-Timer 1
   Uint16 CPUTIMER2ENCLK:1;   // 10    Enable SYSCLKOUT to CPU-Timer 2
   Uint16 DMAENCLK:1;         // 11    Enable the DMA clock
   Uint16 XINTFENCLK:1;       // 12    Enable SYSCLKOUT to XINTF
   Uint16 GPIOINENCLK:1;      // 13    Enable GPIO input clock
   Uint16 rsvd2:2;            // 15:14 reserved
};

union PCLKCR3_REG {
   Uint16              all;
   struct PCLKCR3_BITS bit;
};



// PLL control register bit definitions:
struct PLLCR_BITS {      // bits  description
   Uint16 DIV:5;         // 4:0   Set clock ratio for the PLL
   Uint16 rsvd1:11;      // 15:5  reserved
};

union PLLCR_REG {
   Uint16             all;
   struct PLLCR_BITS  bit;
};

// Low Power Mode 0 control register bit definitions:
struct LPMCR0_BITS {     // bits  description
   Uint16 LPM:2;         // 1:0   Set the low power mode
   Uint16 QUALSTDBY:6;   // 7:2   Qualification
   Uint16 rsvd1:7;       // 14:8  reserved
   Uint16 WDINTE:1;      // 15    Enables WD to wake the device from STANDBY
};

union LPMCR0_REG {
   Uint16              all;
   struct LPMCR0_BITS  bit;
};

struct EXTSOCCFG_BITS {         // bits  description
    Uint16 EXTSOCAG1POLSEL:1;   // 0     External ADC SOCA Group 1 polarity select
    Uint16 EXTSOCAG1EN:1;       // 1     External ADC SOCA Group 1 enable
    Uint16 EXTSOCBG1POLSEL:1;   // 2     External ADC SOCB Group 1 polarity select
    Uint16 EXTSOCBG1EN:1;       // 3     External ADC SOCB Group 1 enable
    Uint16 EXTSOCAG4POLSEL:1;   // 4     External ADC SOCA Group 4 polarity select
    Uint16 EXTSOCAG4EN:1;       // 5     External ADC SOCA Group 4 enable
    Uint16 EXTSOCBG4POLSEL:1;   // 6     External ADC SOCB Group 4 polarity select
    Uint16 EXTSOCBG4EN:1;       // 7     External ADC SOCB Group 4 enable
    Uint16 EXTSOCAG7POLSEL:1;   // 8     External ADC SOCA Group 7 polarity select
    Uint16 EXTSOCAG7EN:1;       // 9     External ADC SOCA Group 7 enable
    Uint16 EXTSOCBG7POLSEL:1;   // 10    External ADC SOCB Group 7 polarity select
    Uint16 EXTSOCBG7EN:1;       // 11    External ADC SOCB Group 7 enable
    Uint16 rsvd1:4;             // 15:12  reserved
};

union EXTSOCCFG_REG {
	Uint16                 all;
	struct EXTSOCCFG_BITS  bit;
};


//---------------------------------------------------------------------------
// System Control Register File:
//
struct SYS_CTRL_REGS {
   Uint16                rsvd1;     // 0
   union   PLLSTS_REG    PLLSTS;    // 1
   Uint16                rsvd2[7];  // 2-8
   union   PCLKCR2_REG   PCLKCR2;   // 9 : Peripheral clock control register
   union   HISPCP_REG    HISPCP;    // 10: High-speed peripheral clock pre-scaler
   union   LOSPCP_REG    LOSPCP;    // 11: Low-speed peripheral clock pre-scaler
   union   PCLKCR0_REG   PCLKCR0;   // 12: Peripheral clock control register
   union   PCLKCR1_REG   PCLKCR1;   // 13: Peripheral clock control register
   union   LPMCR0_REG    LPMCR0;    // 14: Low-power mode control register 0
   Uint16                rsvd3;     // 15: reserved
   union   PCLKCR3_REG   PCLKCR3;   // 16: Peripheral clock control register
   union   PLLCR_REG     PLLCR;     // 17: PLL control register
   // No bit definitions are defined for SCSR because
   // a read-modify-write instruction can clear the WDOVERRIDE bit
   Uint16                SCSR;      // 18: System control and status register
   Uint16                WDCNTR;    // 19: WD counter register
   Uint16                rsvd4;     // 20
   Uint16                WDKEY;     // 21: WD reset key register
   Uint16                rsvd5[3];  // 22-24
   // No bit definitions are defined for WDCR because
   // the proper value must be written to the WDCHK field
   // whenever writing to this register.
   Uint16                WDCR;      // 25: WD timer control register
   Uint16                rsvd6[3];  // 26-28
   union   EXTSOCCFG_REG EXTSOCCFG; // 29: External ADC polarity select register
   Uint16                rsvd7;     // 30
   Uint16                rsvd8;     // 31: Reserved
};


/* --------------------------------------------------- */
/* CSM Registers                                       */
/*                                                     */
/* ----------------------------------------------------*/

/* CSM Status & Control register bit definitions */
struct  CSMSCR_BITS {      // bit   description
   Uint16     SECURE:1;    // 0     Secure flag
   Uint16     rsvd1:14;    // 14-1  reserved
   Uint16     FORCESEC:1;  // 15    Force Secure control bit

};

/* Allow access to the bit fields or entire register */
union CSMSCR_REG {
   Uint16             all;
   struct CSMSCR_BITS bit;
};

/* CSM Register File                                                     */
/* These registers exist for compatibility with legacy C28x designs only */
struct  CSM_REGS {
   Uint16           KEY0;    // KEY reg bits 15-0    - Exists for compatibility with legacy C28x designs only
   Uint16           KEY1;    // KEY reg bits 31-16   - Exists for compatibility with legacy C28x designs only
   Uint16           KEY2;    // KEY reg bits 47-32   - Exists for compatibility with legacy C28x designs only
   Uint16           KEY3;    // KEY reg bits 63-48   - Exists for compatibility with legacy C28x designs only
   Uint16           KEY4;    // KEY reg bits 79-64   - Exists for compatibility with legacy C28x designs only
   Uint16           KEY5;    // KEY reg bits 95-80   - Exists for compatibility with legacy C28x designs only
   Uint16           KEY6;    // KEY reg bits 111-96  - Exists for compatibility with legacy C28x designs only
   Uint16           KEY7;    // KEY reg bits 127-112 - Exists for compatibility with legacy C28x designs only
   Uint16           rsvd1;   // reserved
   Uint16           rsvd2;   // reserved
   Uint16           rsvd3;   // reserved
   Uint16           rsvd4;   // reserved
   Uint16           rsvd5;   // reserved
   Uint16           rsvd6;   // reserved
   Uint16           rsvd7;   // reserved
   union CSMSCR_REG CSMSCR;  // CSM Status & Control register
};


/* Password locations  - these will always read back 0xFFFF. These locations support
   compatibility with legacy C28x designs.                                              */
struct  CSM_PWL {
   Uint16   PSWD0;  // PSWD bits 15-0
   Uint16   PSWD1;  // PSWD bits 31-16
   Uint16   PSWD2;  // PSWD bits 47-32
   Uint16   PSWD3;  // PSWD bits 63-48
   Uint16   PSWD4;  // PSWD bits 79-64
   Uint16   PSWD5;  // PSWD bits 95-80
   Uint16   PSWD6;  // PSWD bits 111-96
   Uint16   PSWD7;  // PSWD bits 127-112
};



//---------------------------------------------------------------------------
// System Control External References & Function Declarations:
//
extern volatile struct SYS_CTRL_REGS SysCtrlRegs;
extern volatile struct CSM_REGS CsmRegs;
extern volatile struct CSM_PWL CsmPwl;




#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2834x_SYS_CTRL_H definition

//===========================================================================
// End of file.
//===========================================================================

