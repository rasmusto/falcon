/*==================================================================================*/
/*	User specific Linker command file for running from RAM							*/
/*==================================================================================*/
/*	FILE:			F28027_RAM_BlinkingLED.CMD                                      */
/*                                                                                  */
/*	Description:	Linker command file for User custom sections targetted to run   */
/*					from RAM.  			                                            */
/*                                                                                  */
/*  Target:  		TMS320F28027					                                */
/*                                                                                  */
/*	Version: 		1.1                               								*/
/*                                                                                  */
/*----------------------------------------------------------------------------------*/
/*  Copyright Texas Instruments © 2007                                			    */	
/*----------------------------------------------------------------------------------*/
/*  Revision History:                                                               */
/*----------------------------------------------------------------------------------*/
/*  Date	  | Description                                                         */
/*----------------------------------------------------------------------------------*/
/*  04/23/09  | Release 1.1  					                                    */
/*----------------------------------------------------------------------------------*/


/* Define the memory block start/length for the DSP2802x 
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes: 
         Memory blocks on F28022 are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.  
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program 
         and/or data. 
         
         The L0 memory blocks is mirrored - that is
         it can be accessed in high memory or low memory.
         For simplicity only one instance is used in this
         linker file. 
         
         Contiguous SARAM memory blocks can be combined 
         if required to create a larger memory block. 
*/

MEMORY
{
PAGE 0 :
   
	BEGIN		: origin = 0x000000,	length = 0x000002
	BOOT_RSVD	: origin = 0x000002,	length = 0x00004E             
	RAMM0		: origin = 0x000050,	length = 0x0003B0
	progRAM		: origin = 0x008000,	length = 0x000800

	IQTABLES   : origin = 0x3FE000, length = 0x000B50     /* IQ Math Tables in Boot ROM */
	IQTABLES2  : origin = 0x3FEB50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
	IQTABLES3  : origin = 0x3FEBDC, length = 0x0000AA	 /* IQ Math Tables in Boot ROM */

	RESET      : origin = 0x3FFFC0, length = 0x000002
	BOOTROM    : origin = 0x3FF27C, length = 0x000D44               

         
PAGE 1 : 

	RAMM1		: origin = 0x000480,	length = 0x000380
	dataRAM		: origin = 0x008800,	length = 0x000800
}
 
 
SECTIONS
{

   codestart        : > BEGIN,      PAGE = 0
   ramfuncs         : > progRAM,       PAGE = 0  

   .text            : > progRAM,     PAGE = 0

   .cinit           : > RAMM0,      PAGE = 0
   .pinit           : > RAMM0,      PAGE = 0
   .switch          : > RAMM0,      PAGE = 0
   .reset           : > RESET,      PAGE = 0, TYPE = DSECT
   
   .stack           : > RAMM1,      PAGE = 1

   .ebss            : > dataRAM,     PAGE = 1
   .econst          : > dataRAM,     PAGE = 1      

   .esysmem         : > RAMM1,      PAGE = 1

   IQmath           : >  progRAM,   PAGE = 0
   IQmathTables     : >  IQTABLES, 	PAGE = 0, TYPE = NOLOAD
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



 
