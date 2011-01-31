//----------------------------------------------------------------------------------
//	FILE:			FlashingLeds-Main.C
//
//	Description:	Empty Framework ready for customization
//
//	Version: 		1.3
//
//  Target:  		TMS320F280x, TMS320F2804x, TMS320F2802x(PiccoloA), 
//					TMS320F2803x(PiccoloB)-no CLA, TMS320F2804x, TMS320F2833x, 
//					or TMS320C2834x families
//
//	Type: 			Device Independent
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2009
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// 01 Apr 2009 - BRL
//----------------------------------------------------------------------------------
//
// PLEASE READ - Useful notes about this Project

// Although this project is made up of several files, the most important ones are:
//	 "FlashingLeds-Main.C"	- this file
//		- Application Initialization, Peripheral config,
//		- Application management
//		- Slower background code loops and Task scheduling
//	 "FlashingLeds-DevInit_F28xxx.C
//		- Device Initialization, e.g. Clock, PLL, WD, GPIO mapping
//		- Peripheral clock enables
//		- DevInit file will differ per each F28xxx device series, e.g. F280x, F2833x,
//	 "FlashingLeds-ISR.asm
//		- Assembly level library Macros and any cycle critical functions are found here
//	 "FlashingLeds-Settings.h"
//		- Global defines (settings) project selections are found here
//		- This file is referenced by both C and ASM files.

// Code is made up of sections, e.g. "FUNCTION PROTOTYPES", "VARIABLE DECLARATIONS" ,..etc
//	each section has FRAMEWORK and USER areas.
//  FRAMEWORK areas provide useful ready made "infrastructure" code which for the most part
//	does not need modification, e.g. Task scheduling, ISR call, GUI interface support,...etc
//  USER areas have functional example code which can be modified by USER to fit their appl.
//
// Variables or parameters used for Multiple Channels are stored in Arrays,
//	the array index is the channel number, note: element zero (index=0) is not used
//
// Code can be compiled with various build options (Incremental Builds IBx), these
//  options are selected in file "FlashingLeds-Settings.h".  Note: "Rebuild All" compile
//  tool bar button must be used if this file is modified.

//----------------------------------------------------------------------------------
//This program blinks LED3 on the controlCARD at a frequency given by the variable 
// Gui_LEDPrd. If an external GUI is connected LD2 will blink as well.
// 
//----------------------------------------------------------------------------------

#include "FlashingLeds-Settings.h"
#include "PeripheralHeaderIncludes.h"
#include "DSP280x_EPWM_defines.h"		//OK to use 280x file
																		 

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// FUNCTION PROTOTYPES
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// -------------------------------- FRAMEWORK --------------------------------------
void DeviceInit(void);
void SCIA_Init();
void SerialHostComms();
void InitFlash();


// State Machine function prototypes
//------------------------------------
// Alpha states
void A0(void);	//state A0
void B0(void);	//state B0
void C0(void);	//state C0

// A branch states
void A1(void);	//state A1
void A2(void);	//state A2
void A3(void);	//state A3
void A4(void);	//state A4

// B branch states
void B1(void);	//state B1
void B2(void);	//state B2
void B3(void);	//state B3
void B4(void);	//state B4

// C branch states
void C1(void);	//state C1
void C2(void);	//state C2
void C3(void);	//state C3
void C4(void);	//state C4

// Variable declarations
void (*Alpha_State_Ptr)(void);	// Base States pointer
void (*A_Task_Ptr)(void);		// State pointer A branch
void (*B_Task_Ptr)(void);		// State pointer B branch
void (*C_Task_Ptr)(void);		// State pointer C branch


// ---------------------------------- USER -----------------------------------------




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// VARIABLE DECLARATIONS - GENERAL
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// -------------------------------- FRAMEWORK --------------------------------------

int16	VTimer0[4];					// Virtual Timers slaved off CPU Timer 0
int16	VTimer1[4];					// Virtual Timers slaved off CPU Timer 1
int16	VTimer2[4];					// Virtual Timers slaved off CPU Timer 2
int16	SerialCommsTimer;
int16	CommsOKflg;
int16	HRmode;
int16	BlinkStatePtr, LED_TaskPtr;

// Used to indirectly access all EPWM modules, very useful!
volatile struct EPWM_REGS *ePWM[] = 
 				  { &EPwm1Regs,			//intentional: (ePWM[0] not used)
				  	&EPwm1Regs,
					&EPwm2Regs,
					&EPwm3Regs,
					&EPwm4Regs,
					#if (!DSP2802x_DEVICE_H)
					&EPwm5Regs,
					&EPwm6Regs,
					#if (DSP2803x_DEVICE_H || DSP2804x_DEVICE_H)
					&EPwm7Regs,
					#if (DSP2804x_DEVICE_H)
					&EPwm8Regs
					#endif 
					#endif 
					#endif
				  };

// Used for running BackGround in flash, and ISR in RAM
extern Uint16 *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;


// ---------------------------------- USER -----------------------------------------
int16	Gui_LEDPrd;
int16	temp_LEDDelay;
	

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// VARIABLE DECLARATIONS - CCS WatchWindow / GUI support
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// -------------------------------- FRAMEWORK --------------------------------------

//GUI support variables
// sets a limit on the amount of external GUI controls - increase as necessary
int16 	*varSetTxtList[16];					//16 textbox controlled variables
int16 	*varSetBtnList[16];					//16 button controlled variables
int16 	*varSetSldrList[16];				//16 slider controlled variables
int16 	*varGetList[16];					//16 variables sendable to GUI
int16 	*arrayGetList[16];					//16 arrays sendable to GUI				

// ---------------------------------- USER -----------------------------------------




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void main(void)
{
//=================================================================================
//	INITIALISATION - General
//=================================================================================

//-------------------------------- FRAMEWORK --------------------------------------

	DeviceInit();	// Device Life support & GPIO
	SCIA_Init();  	// Initalize the Serial Comms A peripheral

// Only used if running from FLASH
// Note that the variable FLASH is defined by the compiler with -d FLASH
// (see TwoChannelBuck.pjt file)
#ifdef FLASH		
// Copy time critical code and Flash setup code to RAM
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the linker files. 
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
	InitFlash();	// Call the flash wrapper init function
#endif //(FLASH)

// Timing sync for background loops
// Timer period definitions found in PeripheralHeaderIncludes.h
	CpuTimer0Regs.PRD.all =  mSec1;		// A tasks
	CpuTimer1Regs.PRD.all =  mSec50;	// B tasks
	CpuTimer2Regs.PRD.all =  mSec100;	// C tasks

// Tasks State-machine init
	Alpha_State_Ptr = &A0;
	A_Task_Ptr = &A1;
	B_Task_Ptr = &B1;
	C_Task_Ptr = &C1;

	BlinkStatePtr = 0;
	VTimer0[0] = 0;	
	VTimer1[0] = 0;
	VTimer2[0] = 0;
	CommsOKflg = 0;
	SerialCommsTimer = 0;
	HRmode = 1;		// Default to HR mode enabled
	LED_TaskPtr = 0;

// ---------------------------------- USER -----------------------------------------
//  put common initialization/variable definitions here

	Gui_LEDPrd = 1000;	//Default to 1 blink every second (Q0)
	temp_LEDDelay = 0;


//=================================================================================
//	INITIALISATION - GUI connections
//=================================================================================
// Use this section only if you plan to "Instrument" your application using the 
// Microsoft C# freeware GUI Template provided by TI

	//"Set" variables
	//---------------------------------------
	// assign GUI variable Textboxes to desired "setable" parameter addresses
	//varSetTxtList[0] = &Var1;

	// assign GUI Buttons to desired flag addresses
	//varSetBtnList[0] = &Var2;

	// assign GUI Sliders to desired "setable" parameter addresses
	varSetSldrList[0] = &Gui_LEDPrd;


	//"Get" variables
	//---------------------------------------
	// assign a GUI "getable" parameter address
	//varGetList[0] = &Var3;

	// assign a GUI "getable" parameter array address
	// 		only need to set initial position of array, program will run through it 
	//       based on the array length specified in the GUI
	//arrayGetList[0] = &Var4[0];



//==================================================================================
//	INITIALISATION - Peripherals used for support
//==================================================================================

// ---------------------------------- USER -----------------------------------------
//  Put peripheral initialisation here




//==================================================================================
//	INITIALISATION - BUILD OPTIONS - NOTE: select via ProjectSettings.h
//==================================================================================

// ---------------------------------- USER -----------------------------------------
//  Put build specific initialisation here




//=================================================================================
//	BACKGROUND (BG) LOOP
//=================================================================================

//--------------------------------- FRAMEWORK -------------------------------------
	for(;;)  //infinite loop
	{
		// State machine entry & exit point
		//===========================================================
		(*Alpha_State_Ptr)();	// jump to an Alpha state (A0,B0,...)
		//===========================================================

	}
} //END MAIN CODE



//=================================================================================
//	STATE-MACHINE SEQUENCING AND SYNCRONIZATION
//=================================================================================

//--------------------------------- FRAMEWORK -------------------------------------
void A0(void)
{
	// loop rate synchronizer for A-tasks
	if(CpuTimer0Regs.TCR.bit.TIF == 1)
	{
		CpuTimer0Regs.TCR.bit.TIF = 1;	// clear flag

		//-----------------------------------------------------------
		(*A_Task_Ptr)();		// jump to an A Task (A1,A2,A3,...)
		//-----------------------------------------------------------

		VTimer0[0]++;			// virtual timer 0, instance 0 (spare)
		SerialCommsTimer++;
	}

	Alpha_State_Ptr = &B0;		// Comment out to allow only A tasks
}

void B0(void)
{
	// loop rate synchronizer for B-tasks
	if(CpuTimer1Regs.TCR.bit.TIF == 1)
	{
		CpuTimer1Regs.TCR.bit.TIF = 1;				// clear flag

		//-----------------------------------------------------------
		(*B_Task_Ptr)();		// jump to a B Task (B1,B2,B3,...)
		//-----------------------------------------------------------
		VTimer1[0]++;			// virtual timer 1, instance 0 (spare)
	}

	Alpha_State_Ptr = &C0;		// Allow C state tasks
}

void C0(void)
{
	// loop rate synchronizer for C-tasks
	if(CpuTimer2Regs.TCR.bit.TIF == 1)
	{
		CpuTimer2Regs.TCR.bit.TIF = 1;				// clear flag

		//-----------------------------------------------------------
		(*C_Task_Ptr)();		// jump to a C Task (C1,C2,C3,...)
		//-----------------------------------------------------------
		VTimer2[0]++;			//virtual timer 2, instance 0 (spare)
	}

	Alpha_State_Ptr = &A0;	// Back to State A0
}


//=================================================================================
//	A - TASKS
//=================================================================================
//--------------------------------------------------------
void A1(void) // SCI-GUI
//--------------------------------------------------------
{
	SerialHostComms();		// Serialport controls LED2 (GPIO-31)
							// Will not blink until GUI is connected
	
	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A2
	A_Task_Ptr = &A2;
	//-------------------
}

//-----------------------------------------------------------------
void A2(void) //** Toggle GPIO-34 (LD3)
//-----------------------------------------------------------------
{	
	// task runs every 2ms = 1ms (CpuTimer0 period) * 2 (# of A Tasks)
	if(Gui_LEDPrd < temp_LEDDelay)
	{ 
		//LED blink period = Gui_LEDPrd (Q0 in ms)
		GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

		#if DSP2834x_DEVICE_H               // for C2834x dim100 CC
		GpioDataRegs.GPBTOGGLE.bit.GPIO54 = 1;   
		#endif

		temp_LEDDelay = 0;
	}
	//LED toggles once each 4ms => task frq (2ms) * toggle 2x to get a period (2)
	else temp_LEDDelay = temp_LEDDelay + 4;  

	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A1;
	//-------------------
}

//-----------------------------------------
void A3(void) // SPARE (not used)
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A1;
	//-----------------
}


//-----------------------------------------
void A4(void) // SPARE (not used)
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A1;
	//-----------------
}


//=================================================================================
//	B - TASKS
//=================================================================================

//----------------------------------- USER ----------------------------------------

//----------------------------------------
void B1(void) // Toggle GPIO-00
//----------------------------------------
{
	// task runs every 200ms = 50ms (CpuTimer1 period) * 4 (# of B Tasks)
	GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B2
	B_Task_Ptr = &B2;	
	//-----------------
}

//----------------------------------------
void B2(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B3
	B_Task_Ptr = &B3;
	//-----------------
}

//----------------------------------------
void B3(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B4
	B_Task_Ptr = &B4;	
	//-----------------
}

//----------------------------------------
void B4(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B1
	B_Task_Ptr = &B1;	
	//-----------------
}


//=================================================================================
//	C - TASKS
//=================================================================================

//--------------------------------- USER ------------------------------------------

//----------------------------------------
void C1(void) 	// Toggle GPIO-01 
//----------------------------------------
{
	// task runs every 400ms = 100ms (CpuTimer2 period) * 4 (# of C Tasks)
	GpioDataRegs.GPATOGGLE.bit.GPIO1 = 1;

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C2
	C_Task_Ptr = &C2;	
	//-----------------

}

//----------------------------------------
void C2(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C3
	C_Task_Ptr = &C3;	
	//-----------------
}


//-----------------------------------------
void C3(void) //  SPARE
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C4
	C_Task_Ptr = &C4;	
	//-----------------
}


//-----------------------------------------
void C4(void) //  SPARE
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C1
	C_Task_Ptr = &C1;	
	//-----------------
}
