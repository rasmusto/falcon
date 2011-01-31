// TI File $Revision: /main/5 $
// Checkin $Date: August 19, 2008   17:06:08 $
//###########################################################################
//
// FILE:   DSP2834x_Device.h
//
// TITLE:  DSP2834x Device Definitions.
//
//###########################################################################
// $TI Release: 2834x Header Files Internal Release 3 $
// $Release Date: August 29, 2008 $
//###########################################################################

#ifndef DSP2834x_DEVICE_H
#define DSP2834x_DEVICE_H


#ifdef __cplusplus
extern "C" {
#endif


#define   TARGET   1
//---------------------------------------------------------------------------
// User To Select Target Device:

#define   DSP28_28345   TARGET
#define   DSP28_28344   0
#define   DSP28_28343   0
#define   DSP28_28342   0


//---------------------------------------------------------------------------
// Common CPU Definitions:
//

extern cregister volatile unsigned int IFR;
extern cregister volatile unsigned int IER;

#define  EINT   asm(" clrc INTM")
#define  DINT   asm(" setc INTM")
#define  ERTM   asm(" clrc DBGM")
#define  DRTM   asm(" setc DBGM")
#define  EALLOW asm(" EALLOW")
#define  EDIS   asm(" EDIS")
#define  ESTOP0 asm(" ESTOP0")

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0    0x0001
#define BIT1    0x0002
#define BIT2    0x0004
#define BIT3    0x0008
#define BIT4    0x0010
#define BIT5    0x0020
#define BIT6    0x0040
#define BIT7    0x0080
#define BIT8    0x0100
#define BIT9    0x0200
#define BIT10   0x0400
#define BIT11   0x0800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000



//---------------------------------------------------------------------------
// For Portability, User Is Recommended To Use Following Data Type Size
// Definitions For 16-bit and 32-Bit Signed/Unsigned Integers:
//

#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int                int16;
typedef long               int32;
typedef long long          int64;
typedef unsigned int       Uint16;
typedef unsigned long      Uint32;
typedef unsigned long long Uint64;
typedef float              float32;
typedef long double        float64;
#endif


//---------------------------------------------------------------------------
// Include All Peripheral Header Files:
//

#include "DSP2834x_DevEmu.h"             // Device Emulation Registers
#include "DSP2834x_CpuTimers.h"          // 32-bit CPU Timers
#include "DSP2834x_ECan.h"               // Enhanced eCAN Registers
#include "DSP2834x_ECap.h"               // Enhanced Capture
#include "DSP2834x_DMA.h"                // DMA Registers
#include "DSP2834x_EPwm.h"               // Enhanced PWM
#include "DSP2834x_EQep.h"               // Enhanced QEP
#include "DSP2834x_Gpio.h"               // General Purpose I/O Registers
#include "DSP2834x_I2c.h"                // I2C Registers
#include "DSP2834x_McBSP.h"              // McBSP
#include "DSP2834x_PieCtrl.h"            // PIE Control Registers
#include "DSP2834x_PieVect.h"            // PIE Vector Table
#include "DSP2834x_Spi.h"                // SPI Registers
#include "DSP2834x_Sci.h"                // SCI Registers
#include "DSP2834x_SysCtrl.h"            // System Control/Power Modes
#include "DSP2834x_XIntrupt.h"           // External Interrupts
#include "DSP2834x_Xintf.h"              // XINTF External Interface

#if DSP28_28345
#define DSP28_EPWM1  1
#define DSP28_EPWM2  1
#define DSP28_EPWM3  1
#define DSP28_EPWM4  1
#define DSP28_EPWM5  1
#define DSP28_EPWM6  1
#define DSP28_EPWM7  1
#define DSP28_EPWM8  1
#define DSP28_EPWM9  1
#define DSP28_ECAP1  1
#define DSP28_ECAP2  1
#define DSP28_ECAP3  1
#define DSP28_ECAP4  1
#define DSP28_ECAP5  1
#define DSP28_ECAP6  1
#define DSP28_EQEP1  1
#define DSP28_EQEP2  1
#define DSP28_EQEP3  1
#define DSP28_ECANA  1
#define DSP28_ECANB  1
#define DSP28_MCBSPA 1
#define DSP28_MCBSPB 1
#define DSP28_SPIA   1
#define DSP28_SPID   1
#define DSP28_SCIA   1
#define DSP28_SCIB   1
#define DSP28_SCIC   1
#define DSP28_I2CA   1
#endif  // end DSP28_28345

#if DSP28_28344
#define DSP28_EPWM1  1
#define DSP28_EPWM2  1
#define DSP28_EPWM3  1
#define DSP28_EPWM4  1
#define DSP28_EPWM5  1
#define DSP28_EPWM6  1
#define DSP28_EPWM7  1
#define DSP28_EPWM8  1
#define DSP28_EPWM9  1
#define DSP28_ECAP1  1
#define DSP28_ECAP2  1
#define DSP28_ECAP3  1
#define DSP28_ECAP4  1
#define DSP28_ECAP5  0
#define DSP28_ECAP6  0
#define DSP28_EQEP1  1
#define DSP28_EQEP2  1
#define DSP28_EQEP3  1
#define DSP28_ECANA  1
#define DSP28_ECANB  1
#define DSP28_MCBSPA 1
#define DSP28_MCBSPB 1
#define DSP28_SPIA   1
#define DSP28_SPID   1
#define DSP28_SCIA   1
#define DSP28_SCIB   1
#define DSP28_SCIC   1
#define DSP28_I2CA   1

#endif  // end DSP28_28344

#if DSP28_28343
#define DSP28_EPWM1  0
#define DSP28_EPWM2  0
#define DSP28_EPWM3  0
#define DSP28_EPWM4  0
#define DSP28_EPWM5  0
#define DSP28_EPWM6  0
#define DSP28_EPWM7  0
#define DSP28_EPWM8  0
#define DSP28_EPWM9  0
#define DSP28_ECAP1  0
#define DSP28_ECAP2  0
#define DSP28_ECAP3  0
#define DSP28_ECAP4  0
#define DSP28_ECAP5  0
#define DSP28_ECAP6  0
#define DSP28_EQEP1  0
#define DSP28_EQEP2  0
#define DSP28_EQEP3  0
#define DSP28_ECANA  0
#define DSP28_ECANB  0
#define DSP28_MCBSPA 1
#define DSP28_MCBSPB 1
#define DSP28_SPIA   1
#define DSP28_SPID   1
#define DSP28_SCIA   1
#define DSP28_SCIB   1
#define DSP28_SCIC   1
#define DSP28_I2CA   1

#endif  // end DSP28_28343

#if DSP28_28342
#define DSP28_EPWM1  1
#define DSP28_EPWM2  1
#define DSP28_EPWM3  1
#define DSP28_EPWM4  1
#define DSP28_EPWM5  1
#define DSP28_EPWM6  1
#define DSP28_EPWM7  0
#define DSP28_EPWM8  0
#define DSP28_EPWM9  0
#define DSP28_ECAP1  1
#define DSP28_ECAP2  1
#define DSP28_ECAP3  1
#define DSP28_ECAP4  1
#define DSP28_ECAP5  0
#define DSP28_ECAP6  0
#define DSP28_EQEP1  1
#define DSP28_EQEP2  1
#define DSP28_EQEP3  0
#define DSP28_ECANA  1
#define DSP28_ECANB  1
#define DSP28_MCBSPA 1
#define DSP28_MCBSPB 0
#define DSP28_SPIA   1
#define DSP28_SPID   1
#define DSP28_SCIA   1
#define DSP28_SCIB   1
#define DSP28_SCIC   1
#define DSP28_I2CA   1
#endif  // end DSP28_28342

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2834x_DEVICE_H definition


//===========================================================================
// End of file.
//===========================================================================
