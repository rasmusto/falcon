/*==================================================================================*/
/*	User specific Linker command file for running from FLASH						*/
/*==================================================================================*/
/*	FILE:			F2806_FLASH_DPFW.CMD                                            */
/*                                                                                  */
/*	Description:	Linker command file for User custom sections targetted to run   */
/*					from FLASH.  			                                        */
/*                                                                                  */
/*  Target:  		TMS320F2806 or larger mem device                                */
/*                                                                                  */
/*	Version: 		1.00                                							*/
/*                                                                                  */
/*----------------------------------------------------------------------------------*/
/*  Copyright Texas Instruments © 2007                                			    */	
/*----------------------------------------------------------------------------------*/
/*  Revision History:                                                               */
/*----------------------------------------------------------------------------------*/
/*  Date	  | Description                                                         */
/*----------------------------------------------------------------------------------*/
/*  08/30/07  | Release 1.0  		New release.                                    */
/*----------------------------------------------------------------------------------*/
 MEMORY
{
PAGE 0:
   /* For this example, H0 is split between PAGE 0 and PAGE 1 */  
   RAMM0      : origin = 0x000002, length = 0x0003FE
/*   PRAMH0     : origin = 0x3FA000, length = 0x001800	*/
/*   PRAML0	  : origin = 0x3F8000, length = 0x001A00	*/
	progRAM		: origin = 0x008000,	length = 0x001800

	OTP         : origin = 0x3D7800, length = 0x000800     /* on-chip OTP */
	FLASHD      : origin = 0x3E8000, length = 0x004000     /* on-chip FLASH */
	FLASHC      : origin = 0x3EC000, length = 0x004000     /* on-chip FLASH */
	FLASHA      : origin = 0x3F4000, length = 0x003F80     /* on-chip FLASH */
	CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
	BEGIN       : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
	CSM_PWL     : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */
	BOOTROM     : origin = 0x3FF000, length = 0x000FC0     /* Boot ROM */
	RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
	VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */

PAGE 1 : 

   /* For this example, H0 is split between PAGE 0 and PAGE 1 */

   RAMM1    : origin = 0x000400, length = 0x000400
/*	DRAMH0   : origin = 0x3FB800, length = 0x000800	*/         
/*	DRAML1   : origin = 0x3F9800, length = 0x000600	*/
	dataRAM		: origin = 0x009800,	length = 0x000800
}
 
 
SECTIONS
{
   /* Allocate program areas: */
   .cinit              	: > FLASHA,     PAGE = 0
   .pinit              	: > FLASHA,     PAGE = 0
   .text               	: > FLASHA,     PAGE = 0

   codestart           : > BEGIN       PAGE = 0
   ramfuncs            : LOAD = FLASHA, 
                         RUN = progRAM, 
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         PAGE = 0

   csmpasswds          : > CSM_PWL     PAGE = 0
   csm_rsvd            : > CSM_RSVD    PAGE = 0
   
   /* Allocate uninitalized data sections: */
   .stack           : > RAMM1,      PAGE = 1
   .ebss            : > dataRAM,    PAGE = 1
   .esysmem         : > RAMM1,      PAGE = 1

   /* Initalized sections go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > FLASHA      PAGE = 0
   .switch             : > FLASHA      PAGE = 0      

   /* Allocate IQ math areas: */
   IQmath              : > FLASHC      PAGE = 0                  /* Math Code */
   IQmathTables        : > BOOTROM     PAGE = 0, TYPE = NOLOAD   /* Math Tables In ROM */

   .reset              : > RESET,      PAGE = 0, TYPE = DSECT
   vectors             : > VECTORS     PAGE = 0, TYPE = DSECT
}
    
    
SECTIONS
{
	Net_terminals:	> dataRAM,PAGE = 1
	Controller:		> dataRAM,PAGE = 1
	IBx_addr: 		> dataRAM,PAGE = 1
	DataLogTST: 	> dataRAM,PAGE = 1
	Buck1Loop:		> dataRAM,PAGE = 1
	Buck2Loop:		> dataRAM,PAGE = 1
	GraphData: 		> dataRAM,PAGE = 1
}



 
