/*==================================================================================*/
/*	User specific Linker command file for running from RAM							*/
/*==================================================================================*/
/*	FILE:			F2806_RAM_DPFW.CMD                                              */
/*                                                                                  */
/*	Description:	Linker command file for User custom sections targetted to run   */
/*					from RAM.  			                                            */
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
PAGE 0 :
   
	BEGIN		: origin = 0x000000,	length = 0x000002             
	RAMM0		: origin = 0x000002,	length = 0x0003FE
	progRAM		: origin = 0x008000,	length = 0x001800

	RESET      : origin = 0x3FFFC0, length = 0x000002
	BOOTROM    : origin = 0x3FF000, length = 0x000FC0               

         
PAGE 1 : 

	RAMM1		: origin = 0x000400,	length = 0x000400
	dataRAM		: origin = 0x009800,	length = 0x000800
}
 
 
SECTIONS
{

   codestart        : > BEGIN,      PAGE = 0
   ramfuncs         : > progRAM       PAGE = 0  

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
   IQmathTables     : >  BOOTROM, type = NOLOAD, PAGE = 0
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



 
