
#include "DSP28x_Project.h"

void InitGpio(void);
interrupt void cpu_timer_0_isr(void);
interrupt void cpu_timer_1_isr(void);

void main (void)
{
	// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2803x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2803x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
	InitGpio();  


// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2803x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2803x_DefaultIsr.c.
// This function is found in DSP2803x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 = &cpu_timer_0_isr;
   PieVectTable.TINT1 = &cpu_timer_1_isr;
//   PieVectTable.TINT2 = &cpu_timer2_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize the Device Peripheral. This function can be
//         found in DSP2803x_CpuTimers.c
   InitCpuTimers();   // For this example, only initialize the Cpu Timers

// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
// 60MHz CPU Freq, 1 second Period (in uSeconds)

   ConfigCpuTimer(&CpuTimer0, 60, 500000); //.5 sec
   ConfigCpuTimer(&CpuTimer1, 60, 1000000); // 1 sec
//   ConfigCpuTimer(&CpuTimer2, 60, 1000000);

// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2803x_CpuTimers.h), the
// below settings must also be updated.

   CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
   CpuTimer1Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
//   CpuTimer2Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0

// Step 5. User specific code, enable interrupts:


// Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
// which is connected to CPU-Timer 1, and CPU int 14, which is connected
// to CPU-Timer 2:
   IER |= M_INT1;
   IER |= M_INT13;
//   IER |= M_INT14;

// Enable TINT0 in the PIE: Group 1 interrupt 7
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

// Step 6. Loop.
	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;	//turn on LED3
   for(;;){
   	
   }
}

//---------------------------------------------------------------------------
// InitGpio:
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example.
void InitGpio(void)
{
   EALLOW;

   // Each GPIO pin can be:
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs
   GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
   GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
   GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO44
   GpioCtrlRegs.AIOMUX1.all = 0x0000;     // Dig.IO funct. applies to AIO2,4,6,10,12,14

	GpioDataRegs.GPASET.bit.GPIO31 = 1;	//set output high (turn off led)
	GpioDataRegs.GPBSET.bit.GPIO34 = 1;	//set output high (turn off led)

   GpioCtrlRegs.GPADIR.all = 0x80000000;      // GPIO0-GPIO30 are GP inputs, GPIO31 is output (for LED2)
   GpioCtrlRegs.GPBDIR.all = 0x00000004;      // GPIO32-GPIO44 are inputs, except GPIO34 is output (for LED3)
   GpioCtrlRegs.AIODIR.all = 0x0000;      // AIO2,4,6,19,12,14 are digital inputs

   // Each input can have different qualification
   // a) input synchronized to SYSCLKOUT
   // b) input qualified by a sampling window
   // c) input sent asynchronously (valid for peripheral inputs only)
   GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT
   GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
   GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO44 Synch to SYSCLKOUT

   // Pull-ups can be enabled or disabled.
   GpioCtrlRegs.GPAPUD.all = 0x80000000;      // Pullup's enabled GPIO0-GPIO30, pullup disabled on GPIO31
   GpioCtrlRegs.GPBPUD.all = 0x00000004;      // Pullup's enabled GPIO32-GPIO44, except GPIO34.
   //GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
   //GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO44
   EDIS;

}

interrupt void cpu_timer_0_isr(void)
{
	GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;	//toggle bit (blink LED2)
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; //writes of 0 are ignored, so writing mask PIEACK_GROUP1 just acks that group
}
interrupt void cpu_timer_1_isr(void)
{
	GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;	//turn on LED3
}
