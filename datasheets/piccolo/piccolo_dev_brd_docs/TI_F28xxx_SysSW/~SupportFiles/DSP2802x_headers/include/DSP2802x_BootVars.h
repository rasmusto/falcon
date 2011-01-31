// TI File $Revision: /main/1 $
// Checkin $Date: September 9, 2008   16:11:53 $
//###########################################################################
//
// FILE:    DSP2802x_BootVars.h
//
// TITLE:   DSP2802x Boot Variable Definitions.
//
// NOTES:
//
//###########################################################################
// $TI Release:$
// $Release Date:$
//###########################################################################

#ifndef DSP2802x_BOOT_VARS_H
#define DSP2802x_BOOT_VARS_H

#ifdef __cplusplus
extern "C" {
#endif



//---------------------------------------------------------------------------
// Boot Variables Files:
//
struct BOOT_VARS {
   Uint16 EMU_KEY;      // EMU boot mode - Key value
   Uint16 EMU_BMODE;    // EMU boot mode - Boot Mode Selection
   Uint32 FLASH_rsvd1;  // Initialized to 0 by Boot ROM (Reserved for Flash API)
   Uint32 FLASH_rsvd2;  // Initialized to 0 by Boot ROM (Reserved for Flash API)
};

//---------------------------------------------------------------------------
// Function prototypes and external definitions:
//
extern volatile struct BOOT_VARS BootVars;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2802x_BOOT_VARS_H definition

//===========================================================================
// End of file.
//===========================================================================

