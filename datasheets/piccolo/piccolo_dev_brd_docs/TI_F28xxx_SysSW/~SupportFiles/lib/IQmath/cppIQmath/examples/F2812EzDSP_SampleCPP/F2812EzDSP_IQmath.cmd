/****************************************************************************/
/* Sample Link Command File For, Target Processor(s): F2812 EzDSP
/****************************************************************************/

MEMORY
{
PAGE 0 : RAMH0   (RW)   : origin = 0x3f8000, length = 0x002000
         BOOTROM (RW)   : origin = 0x3ff000, length = 0x000fc0
         VECTORS (RW)   : origin = 0x3fffc2, length = 0x00003e
         RESET   (RW)   : origin = 0x3fffc0, length = 0x000002
         
PAGE 1 : RAMM0M1 (RW)   : origin = 0x000000, length = 0x000800
         RAML0L1 (RW)   : origin = 0x008000, length = 0x002000
}
 
SECTIONS
{
      .reset        : load = RESET,   type = DSECT, PAGE = 0
      
      /* .text needs to be the first section into RAMH0 for */
      /*  boot to H0 to work properly. */

      .text         : load = RAMH0,   PAGE = 0
      .cinit        : load = RAMH0,   PAGE = 0
      .econst       : load = RAMH0,   PAGE = 0
      .bss          : load = RAML0L1, PAGE = 1
      .ebss         : load = RAML0L1, PAGE = 1
      .data         : load = RAML0L1, PAGE = 1
      .const        : load = RAML0L1, PAGE = 1
      .stack        : load = RAMM0M1, PAGE = 1
      .sysmem       : load = RAML0L1, PAGE = 1

      /*==========================================================*/
      /* Tables for IQ math functions:                            */
      /*==========================================================*/
      /* For K1 device (no tables in boot ROM), use this:         */
/*    
      IQmathTables  : load = BOOTROM, PAGE = 0                    
*/
      /* For F2810/12 devices (with tables in Boot ROM) use this: */
    
      IQmathTables  : load = BOOTROM, type = NOLOAD, PAGE = 0     

      /*==========================================================*/
      /* IQ math functions:                                       */
      /*==========================================================*/
      IQmath        : load = RAMH0,   PAGE = 0
}
