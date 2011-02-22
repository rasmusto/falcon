#include "imu_main.h"

void init_cla()
{
   // Copy the CLA program code from its load address to the CLA program memory
	MemCopy(&Cla1funcsLoadStart, &Cla1funcsLoadEnd, &Cla1funcsRunStart); 
	//copy the CLA initialized data to the CLA RAM
	MemCopy(&Cla1DataLoadStart, &Cla1DataLoadEnd, &Cla1DataRunStart);
	
	EALLOW;
	
	//enable the CLA clock
	SysCtrlRegs.PCLKCR3.bit.CLA1ENCLK = 1;
	
   // The symbols used in this calculation are defined in the CLA 
   // assembly code and in the CLAShared.h header file
   // set task vector pointer registers (memory offset from Cla1Prog_Start)
	Cla1Regs.MVECT1 = (Uint16) (&Cla1Task1 - &Cla1Prog_Start)*sizeof(Uint32);
	Cla1Regs.MVECT2 = (Uint16) (&Cla1Task2 - &Cla1Prog_Start)*sizeof(Uint32);
    
    //configure all tasks to be trigger by software (IACK) only.
	Cla1Regs.MPISRCSEL1.bit.PERINT1SEL = CLA_INT1_NONE; 
	Cla1Regs.MPISRCSEL1.bit.PERINT2SEL = CLA_INT2_NONE;
   
	// Make sure there are at least two SYSCLKOUT cycles between assigning
    // the memory to the CLA and when an interrupt comes in
    //
	//assign the program memory to the CLA
	Cla1Regs.MMEMCFG.bit.PROGE = 1;
    //assign the data memory RAML2 (CLA DATA RAM1) to the CLA
    Cla1Regs.MMEMCFG.bit.RAM1E = 1;
   
   // Enable the IACK instruction use
   // Enable the CLA interrupts (tasks)
   
	Cla1Regs.MCTL.bit.IACKE = 1;            
	Cla1Regs.MIER.all = (M_INT1 | M_INT2);
	
	EDIS;
}
