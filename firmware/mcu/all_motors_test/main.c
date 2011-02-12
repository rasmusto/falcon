#define F_CPU 32000000UL
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "avr_compiler.h"
#include "clksys_driver.h"
#include "usart_driver.h"
#include "TC_driver.h"
#include "hires_driver.h"
#include "awex_driver.h"
#include "adc_driver.h"
#include "usart_driver.h"

// Macros

	#include "setPhaseMacros.c"

// functions

	void configClock (void);
	void configPWMTimer (volatile TC0_t * tc, HIRES_t * hires, uint16_t period); // configure timer used to generate pwm
	void configHalfPWMTimer (volatile TC0_t * tc, HIRES_t * hires, uint16_t period); // configure timer used to generate interrupt half way into pwm high period
	void configDelayTimer (volatile TC0_t * tc); // configure timer used to generate delays
	void configAdc (ADC_t * adc); // use to initialize adcs

	void setMotor1State (uint8_t state); // motors to their a commutation state based on an integ 
	void setMotor2State (uint8_t state); // -- used instead of macros to allow numerical indexing of states
	void setMotor3State (uint8_t state);
	void setMotor4State (uint8_t state);

	void startup(void); // run startup commutation routine, then transition to automatic comutation

// Constant Things

	// these are constants that define which direction the back emf slope goes during each state
	// 0 = falling
	// 1 = rising
	#define STATE_SLOPE 0b00101010

	// these are constants that define the index of the pin to look at for back emf during each state
	const uint8_t motor1StateSenseIndex[6] = {2,1,0,2,1,0};
	const uint8_t motor2StateSenseIndex[6] = {5,4,3,5,4,3};
	const uint8_t motor3StateSenseIndex[6] = {0,7,6,0,7,6};
	const uint8_t motor4StateSenseIndex[6] = {3,2,1,3,2,1};

	// middle thresholds for back emf "zero" crossing for each motor.  I'm not sure if this needs to vary with pwm or not...
	#define MOTOR_1_THRESH 88
	#define MOTOR_2_THRESH 88
	#define MOTOR_3_THRESH 88
	#define MOTOR_4_THRESH 88
	
	// PWM to use to lock rotor to initial position
	#define STARTUP_PWM 500

	// PWMs and delays to use during and after each manual commutation cycle
	const uint16_t startupPwms[6] = {800, 800, 900, 900, 1200, 1200};
	const uint8_t startupDelays[6] = {250, 150, 105, 80, 75, 65};

// Global variables 

	// these variables keep track of which pins should be driven during the high and low parts of the pwm cycle

		#define phaseOutputsEHigh GPIO0 // keep track of which pins should be driven high during high part of pwm
		#define phaseOutputsFHigh GPIO1 // keep track of which pins should be driven high during high part of pwm
		#define phaseOutputsDHigh GPIO2 // keep track of which pins should be driven high during high part of pwm

		#define phaseOutputsELow GPIO3 // keep track of which pins should be driven high during low part of pwm
		#define phaseOutputsFLow GPIO4 // keep track of which pins should be driven high during low part of pwm
		#define phaseOutputsDLow GPIO5 // keep track of which pins should be driven high during low part of pwm

		// holds current motor state (1-6)
		#define motor1State GPIO6
		#define motor2State GPIO7
		#define motor3State GPIO8
		#define motor4State GPIO9

	#define passedCenterFlags GPIOA // holds flags for each motor telling wether they are half way through the state yet
	
int main (void) {
	
	configClock (); // set up 32mhz internal oscillator 
	
	PORTC.DIR = 0b00000001; // led on PORTC0
	
	PORTE.DIR = 0xFF; // all motor lines outputs
	PORTF.DIR = 0xFF;
	PORTD.DIR = 0xFF;
	
	configPWMTimer (&TCF0, &HIRESF, 5000);
	configHalfPWMTimer (&TCE0, &HIRESE, 5000);
	TCF0.CNT = 0;
	TCE0.CNT = 0;
	
	configDelayTimer (&TCC0);
	
	configAdc (&ADCA);
	configAdc (&ADCB);
	
	PMIC.CTRL |= PMIC_HILVLEN_bm; // Enable HI Level Interrupts - all interrupts are high level in this application
	sei();
	
	startup(); // blocking forever
	
	while (1);
}

void configClock (void) {
	// enable 32mhz oscillator 
	CLKSYS_Enable( OSC_RC32MEN_bm );
	do {} while ( CLKSYS_IsReady( OSC_RC32MRDY_bm ) == 0 );

	// configure pll source = 32mhz oscillator/4 * 16 = 4*32mhz = 128mhz output
	CLKSYS_PLL_Config( OSC_PLLSRC_RC32M_gc, 16 );

	// enable pll
	CLKSYS_Enable( OSC_PLLEN_bm );
	do {} while ( CLKSYS_IsReady( OSC_PLLEN_bm ) == 0 );

	// enable prescale by 2 and 2 again to generate 2x and 4x clocks
	CCP = CCP_IOREG_gc;
	CLK.PSCTRL = CLK_PSBCDIV_2_2_gc;

	// select main clock source as pll output
	CLKSYS_Main_ClockSource_Select( CLK_SCLKSEL_PLL_gc );
}

// *************** PWM **********************

	// Configures PWM output on compare a b and c for single slope pwm, with hires, and clk source as sys clk
	void configPWMTimer (volatile TC0_t * tc, HIRES_t * hires, uint16_t period) {
		TC_SetPeriod (tc, period );
		TC0_ConfigWGM (tc, TC_WGMODE_NORMAL_gc ); // set to single slope pwm generation mode
		TC0_EnableCCChannels (tc, TC0_CCAEN_bm); // enable compare A
		TC0_EnableCCChannels (tc, TC0_CCBEN_bm); // enable compare B
		TC0_EnableCCChannels (tc, TC0_CCCEN_bm); // enable compare C
		TC0_EnableCCChannels (tc, TC0_CCDEN_bm); // enable compare D

		TC0_SetCCAIntLevel (tc, TC_CCAINTLVL_HI_gc);
		TC0_SetCCBIntLevel (tc, TC_CCBINTLVL_HI_gc);
		TC0_SetCCCIntLevel (tc, TC_CCCINTLVL_HI_gc);
		TC0_SetCCDIntLevel (tc, TC_CCDINTLVL_HI_gc);

		TC0_SetOverflowIntLevel (tc, TC_OVFINTLVL_HI_gc);

		TC0_ConfigClockSource (tc, TC_CLKSEL_DIV1_gc);
		HIRES_Enable (hires, HIRES_HREN_TC0_gc);
	}

	// When TCF0 compare interrupts are triggered, set the set of 6 outputs which
	// controls the motor assigned to that interrupt to low

	// Motor 1
	ISR (TCF0_CCA_vect) {	
		// motor 1 on pe0-5
		
		// force bits 6 and 7 to 1 (for phaseOutputsEHighInv) and 0 (for phaseOutputsEHighInv) so that only pins for motor 1 are turned off 
		PORTE.OUTCLR = (phaseOutputsEHigh & 0b00111111); // turn off all high bits in phaseOutputsELowInv
		PORTE.OUTSET = (phaseOutputsELow & 0b00111111); // turn on all low bits in phaseOutputsEHigh	
	}

	// Motor 2
	ISR (TCF0_CCB_vect) {
		// motor 2 on pe6-7 and pf0-3
		
		PORTE.OUTCLR = (phaseOutputsEHigh & 0b11000000); // turn off all high bits in phaseOutputsELowInv
		PORTE.OUTSET = (phaseOutputsELow & 0b11000000); // turn on all low bits in phaseOutputsEHigh	
		
		PORTF.OUTCLR = (phaseOutputsFHigh & 0b00001111); // turn off all high bits in phaseOutputsELowInv
		PORTF.OUTSET = (phaseOutputsFLow & 0b00001111); // turn on all low bits in phaseOutputsEHigh
	}

	// Motor 3
	ISR (TCF0_CCC_vect) {
		// motor 3 on pf4-7 and pd0-1
		
		PORTF.OUTCLR = (phaseOutputsFHigh & 0b11110000); // turn off all high bits in phaseOutputsELowInv
		PORTF.OUTSET = (phaseOutputsFLow & 0b11110000); // turn on all low bits in phaseOutputsEHigh	
		
		PORTD.OUTCLR = (phaseOutputsDHigh & 0b00000011); // turn off all high bits in phaseOutputsELowInv
		PORTD.OUTSET = (phaseOutputsDLow & 0b00000011); // turn on all low bits in phaseOutputsEHigh	
	}
	
	// Motor 4
	ISR (TCF0_CCD_vect) {
		// motor 4 on pd2-7
		
		PORTD.OUTCLR = (phaseOutputsDHigh & 0b11111100); // turn off all high bits in phaseOutputsELowInv
		PORTD.OUTSET = (phaseOutputsDLow & 0b11111100); // turn on all low bits in phaseOutputsEHigh	
	}

	// When TCF0 overflows, high part of pwm cycle starts
	ISR (TCF0_OVF_vect) {
		PORTE.OUTCLR = phaseOutputsELow; // turn off all high bits in phaseOutputsELow
		PORTE.OUTSET = phaseOutputsEHigh; // turn on all high bits in phaseOutputsEHigh
		PORTF.OUTCLR = phaseOutputsFLow; // turn off all high bits in phaseOutputsFLow
		PORTF.OUTSET = phaseOutputsFHigh; // turn on all high bits in phaseOutputsFHigh
		PORTD.OUTCLR = phaseOutputsDLow; // turn off all high bits in phaseOutputsDLow
		PORTD.OUTSET = phaseOutputsDHigh; // turn on all high bits in phaseOutputsDHigh
	}

// *************** /PWM **********************

// *************** PWM/2 **********************

	// Configures PWM output on compare a b and c for single slope pwm, with hires, and clk source as sys clk
	void configHalfPWMTimer (volatile TC0_t * tc, HIRES_t * hires, uint16_t period) {
		TC_SetPeriod (tc, period );
		TC0_ConfigWGM (tc, TC_WGMODE_NORMAL_gc ); // set to single slope pwm generation mode
		TC0_EnableCCChannels (tc, TC0_CCAEN_bm); // enable compare A
		TC0_EnableCCChannels (tc, TC0_CCBEN_bm); // enable compare B
		TC0_EnableCCChannels (tc, TC0_CCCEN_bm); // enable compare C
		TC0_EnableCCChannels (tc, TC0_CCDEN_bm); // enable compare D

		TC0_SetCCAIntLevel (tc, TC_CCAINTLVL_HI_gc);
		TC0_SetCCBIntLevel (tc, TC_CCBINTLVL_HI_gc);
		TC0_SetCCCIntLevel (tc, TC_CCCINTLVL_HI_gc);
		TC0_SetCCDIntLevel (tc, TC_CCDINTLVL_HI_gc);
		
		TC0_ConfigClockSource (tc, TC_CLKSEL_DIV1_gc);
		HIRES_Enable (hires, HIRES_HREN_TC0_gc);
		
	}
	
	// Motor 1
	ISR (TCE0_CCA_vect) {
		// half way into high part of motor 1 pwm
		// start adc conversion on adca ch1 (this channel is dedicated to this motor)
		ADC_Ch_InputMux_Config (&ADCA.CH0, motor1StateSenseIndex[motor1State]<<3, 0);
		ADC_Ch_Conversion_Start (&(ADCA.CH0));
	}

	// Motor 2
	ISR (TCE0_CCB_vect) {
		// half way into high part of motor 2 pwm
		// start adc conversion on adca ch1 (this channel is dedicated to this motor)
		ADC_Ch_InputMux_Config (&ADCA.CH1, motor2StateSenseIndex[motor2State]<<3, 0);
		ADC_Ch_Conversion_Start (&(ADCA.CH1));
	}

	// Motor 3
	ISR (TCE0_CCC_vect) {
		// half way into high part of motor 3 pwm
		// start adc conversion on adca ch1 (this channel is dedicated to this motor)
		if (motor3StateSenseIndex[motor3State] == 0) { // sense c3 is on adcb, sense a3 and b3 are on adca
			ADC_Ch_InputMux_Config (&ADCB.CH2, motor3StateSenseIndex[motor3State]<<3, 0);
			ADC_Ch_Conversion_Start (&(ADCB.CH2));
		} else {
			ADC_Ch_InputMux_Config (&ADCA.CH2, motor3StateSenseIndex[motor3State]<<3, 0);
			ADC_Ch_Conversion_Start (&(ADCA.CH2));			
		}
	}

	// Motor 4
	ISR (TCE0_CCD_vect) {
		// half way into high part of motor 4 pwm
		// start adc conversion on adca ch1 (this channel is dedicated to this motor)
		ADC_Ch_InputMux_Config (&ADCB.CH3, motor4StateSenseIndex[motor4State]<<3, 0);
		ADC_Ch_Conversion_Start (&(ADCB.CH3));
	}

// *************** /PWM/2 **********************

// *************** Commutation Timing **********************
	
	// Motor 1
	ISR (TCC1_OVF_vect) {
		// time to change motor1 state
		TCC1.PER = 65000;
		if (motor1State < 5)
			motor1State++;
		else
			motor1State=0;

		passedCenterFlags &= ~(1<<1); // clear motor 2 passedCenterFlag	
		setMotor1State(motor1State);

		TC1_SetOverflowIntLevel (&TCC1, TC_OVFINTLVL_OFF_gc);
	}

	// Motor 2
	ISR (TCD1_OVF_vect) {
		// time to change motor2 state
		TCD1.PER = 65000;
		if (motor2State < 5)
			motor2State++;
		else
			motor2State=0;

		passedCenterFlags &= ~(1<<2); // clear motor 2 passedCenterFlag	
		setMotor2State(motor2State);
		
		PORTC.OUTSET = 1;
		TC1_SetOverflowIntLevel (&TCD1, TC_OVFINTLVL_OFF_gc);
	}

	// Motor 3
	ISR (TCE1_OVF_vect) {
		TCE1.PER = 65000;
		if (motor3State < 5)
			motor3State++;
		else
			motor3State=0;

		passedCenterFlags &= ~(1<<3); // clear motor 2 passedCenterFlag	
		setMotor3State(motor3State);

		TC1_SetOverflowIntLevel (&TCE1, TC_OVFINTLVL_OFF_gc);
	}

	// Motor 4
	ISR (TCD0_OVF_vect) {
		TCD0.PER = 65000;
		if (motor4State < 5)
			motor4State++;
		else
			motor4State=0;

		passedCenterFlags &= ~(1<<4); // clear motor 2 passedCenterFlag	
		setMotor4State(motor4State);
		
		TC0_SetOverflowIntLevel (&TCD0, TC_OVFINTLVL_OFF_gc);
	}

// *************** /Commutation Timing **********************

// *************** ADC **********************

	void configAdc (ADC_t * adc) {
		ADC_CalibrationValues_Load (adc);
		ADC_ConvMode_and_Resolution_Config (adc, ADC_ConvMode_Unsigned, ADC_RESOLUTION_8BIT_gc);
		ADC_Prescaler_Config (adc, ADC_PRESCALER_DIV32_gc); // Fadc = 125khz
		ADC_Reference_Config (adc, ADC_REFSEL_INT1V_gc); // vref = internal 1v
		
		/* Setup channel 0, 1, 2 and 3 to have single ended input and 1x gain. */
		ADC_Ch_InputMode_and_Gain_Config (&(adc->CH0),
										 ADC_CH_INPUTMODE_SINGLEENDED_gc,
										 ADC_CH_GAIN_1X_gc);

		ADC_Ch_InputMode_and_Gain_Config (&(adc->CH1),
										 ADC_CH_INPUTMODE_SINGLEENDED_gc,
										 ADC_CH_GAIN_1X_gc);

		ADC_Ch_InputMode_and_Gain_Config (&(adc->CH2),
										 ADC_CH_INPUTMODE_SINGLEENDED_gc,
										 ADC_CH_GAIN_1X_gc);

		ADC_Ch_InputMode_and_Gain_Config (&(adc->CH3),
										 ADC_CH_INPUTMODE_SINGLEENDED_gc,
										 ADC_CH_GAIN_1X_gc);

		/* Enable high level sample complete interrupt for channel 3 */
		ADC_Ch_Interrupts_Config (&(adc->CH0), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);
		ADC_Ch_Interrupts_Config (&(adc->CH1), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);
		ADC_Ch_Interrupts_Config (&(adc->CH2), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);
		ADC_Ch_Interrupts_Config (&(adc->CH3), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);

		ADC_Enable (adc); // Enable ADC
		ADC_Wait_32MHz (adc); // Wait until common mode voltage is stable
	}

	// Motor 1
	ISR (ADCA_CH0_vect) {
		ADCA.CH0.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCA.CH0.RES;
		if (STATE_SLOPE & (1<<motor1State)) { // rising
			if (result > MOTOR_1_THRESH  && result < 205) {
				if (!(passedCenterFlags & (1<<1))) {
					TCC1.PER = TCC1.CNT*2;
					TC1_SetOverflowIntLevel (&TCC1, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<1); 
				}
			}
		} else { // falling
			if (result < MOTOR_1_THRESH && result > 50) {
				if (!(passedCenterFlags & (1<<1))) {
					TCC1.PER = TCC1.CNT*2;
					TC1_SetOverflowIntLevel (&TCC1, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<1);
				}
			}
		}
	}
	
	// Motor 2
	ISR (ADCA_CH1_vect) {
		ADCA.CH1.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCA.CH1.RES;
		if (STATE_SLOPE & (1<<motor2State)) { // rising
			if (result > MOTOR_2_THRESH  && result < 205) {
				if (!(passedCenterFlags & (1<<2))) {
					PORTC.OUTCLR = 1;
					TCD1.PER = TCD1.CNT*2;
					TC1_SetOverflowIntLevel (&TCD1, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<2); 
				}
			}
		} else { // falling
			if (result < MOTOR_2_THRESH && result > 50) {
				if (!(passedCenterFlags & (1<<2))) {
					PORTC.OUTCLR = 1;
					TCD1.PER = TCD1.CNT*2;
					TC1_SetOverflowIntLevel (&TCD1, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<2);
				}
			}
		}
	}
	
	// Motor 3
	ISR (ADCA_CH2_vect) {
		ADCA.CH2.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCA.CH2.RES;
		if (STATE_SLOPE & (1<<motor3State)) { // rising
			if (result > MOTOR_3_THRESH  && result < 205) {
				if (!(passedCenterFlags & (1<<3))) {
					TCE1.PER = TCE1.CNT*2;
					TC1_SetOverflowIntLevel (&TCE1, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<3); 
				}
			}
		} else { // falling
			if (result < MOTOR_3_THRESH && result > 50) {
				if (!(passedCenterFlags & (1<<3))) {
					TCE1.PER = TCE1.CNT*2;
					TC1_SetOverflowIntLevel (&TCE1, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<3);
				}
			}
		}
	}

	// Motor 2 - called for phase c (phase c feedback is on adcb)
	ISR (ADCB_CH2_vect) {
		ADCB.CH2.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCB.CH2.RES;
		if (STATE_SLOPE & (1<<motor3State)) { // rising
			if (result > MOTOR_3_THRESH  && result < 205) {
				if (!(passedCenterFlags & (1<<3))) {
					TCE1.PER = TCE1.CNT*2;
					TC1_SetOverflowIntLevel (&TCE1, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<3); 
				}
			}
		} else { // falling
			if (result < MOTOR_3_THRESH && result > 50) {
				if (!(passedCenterFlags & (1<<3))) {
					TCE1.PER = TCE1.CNT*2;
					TC1_SetOverflowIntLevel (&TCE1, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<3);
				}
			}
		}
	}
	
	// Motor 4
	ISR (ADCB_CH3_vect) {
		ADCB.CH3.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCB.CH3.RES;
		if (STATE_SLOPE & (1<<motor4State)) { // rising
			if (result > MOTOR_4_THRESH  && result < 205) {
				if (!(passedCenterFlags & (1<<4))) {
					TCD0.PER = TCD0.CNT*2;
					TC0_SetOverflowIntLevel (&TCD0, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<4); 
				}
			}
		} else { // falling
			if (result < MOTOR_4_THRESH && result > 50) {
				if (!(passedCenterFlags & (1<<4))) {
					TCD0.PER = TCD0.CNT*2;
					TC0_SetOverflowIntLevel (&TCD0, TC_OVFINTLVL_HI_gc);
					passedCenterFlags |= (1<<4);
				}
			}
		}
	}
	
// *************** /ADC **********************

void configDelayTimer (volatile TC0_t * tc) {
	TC_SetPeriod (tc, (uint16_t)65535); // set tc period
	TC0_ConfigWGM (tc, TC_WGMODE_NORMAL_gc); // normal timer countermode
	TC0_ConfigClockSource (tc, TC_CLKSEL_DIV1024_gc);
}

void startup(void) {
	
	TCF0.CCABUF = STARTUP_PWM;
	TCF0.CCBBUF = STARTUP_PWM;
	TCF0.CCCBUF = STARTUP_PWM;
	TCF0.CCDBUF = STARTUP_PWM;
	
	SET_PHASE_STATE_5_MOT1();
	SET_PHASE_STATE_5_MOT2();
	SET_PHASE_STATE_5_MOT3();
	SET_PHASE_STATE_5_MOT4();
	TCC0.CNT = 0;
	
	PORTC.OUTSET = 1;
	while (TCC0.CNT < 65000) {}
	PORTC.OUTCLR = 1;
	
	TCF0.CCABUF = startupPwms[0];
	TCF0.CCBBUF = startupPwms[0];
	TCF0.CCCBUF = startupPwms[0];
	TCF0.CCDBUF = startupPwms[0];
	SET_PHASE_STATE_0_MOT1();
	SET_PHASE_STATE_0_MOT2();
	SET_PHASE_STATE_0_MOT3();
	SET_PHASE_STATE_0_MOT4();
	TCC0.CNT = 0;
	while (TCC0.CNT < startupDelays[0]) {}
	
	TCF0.CCABUF = startupPwms[1];
	TCF0.CCBBUF = startupPwms[1];
	TCF0.CCCBUF = startupPwms[1];
	TCF0.CCDBUF = startupPwms[1];
	SET_PHASE_STATE_1_MOT1();
	SET_PHASE_STATE_1_MOT2();
	SET_PHASE_STATE_1_MOT3();
	SET_PHASE_STATE_1_MOT4();
	TCC0.CNT = 0;
	while (TCC0.CNT < startupDelays[1]) {}
	
	TCF0.CCABUF = startupPwms[2];
	TCF0.CCBBUF = startupPwms[2];
	TCF0.CCCBUF = startupPwms[2];
	TCF0.CCDBUF = startupPwms[2];
	SET_PHASE_STATE_2_MOT1();	
	SET_PHASE_STATE_2_MOT2();	
	SET_PHASE_STATE_2_MOT3();	
	SET_PHASE_STATE_2_MOT4();	
	TCC0.CNT = 0;
	while (TCC0.CNT < startupDelays[2]) {}
		
	TCF0.CCABUF = startupPwms[3];
	TCF0.CCBBUF = startupPwms[3];
	TCF0.CCCBUF = startupPwms[3];
	TCF0.CCDBUF = startupPwms[3];
	SET_PHASE_STATE_3_MOT1();
	SET_PHASE_STATE_3_MOT2();
	SET_PHASE_STATE_3_MOT3();
	SET_PHASE_STATE_3_MOT4();
	TCC0.CNT = 0;
	while (TCC0.CNT < startupDelays[3]) {}
	
	TCF0.CCABUF = startupPwms[4];
	TCF0.CCBBUF = startupPwms[4];
	TCF0.CCCBUF = startupPwms[4];
	TCF0.CCBBUF = startupPwms[4];
	SET_PHASE_STATE_4_MOT1();
	SET_PHASE_STATE_4_MOT2();
	SET_PHASE_STATE_4_MOT3();
	SET_PHASE_STATE_4_MOT4();
	TCC0.CNT = 0;
	while (TCC0.CNT < startupDelays[4]) {}

	TCF0.CCABUF = startupPwms[5];
	TCF0.CCBBUF = startupPwms[5];
	TCF0.CCCBUF = startupPwms[5];
	TCF0.CCDBUF = startupPwms[5];
	
	TCE0.CCABUF = startupPwms[5]/2;
	TCE0.CCBBUF = startupPwms[5]/2;
	TCE0.CCCBUF = startupPwms[5]/2;
	TCE0.CCDBUF = startupPwms[5]/2;
	
	TC_SetPeriod( &TCC1, 6500 );
	TC1_ConfigClockSource( &TCC1, TC_CLKSEL_DIV64_gc );
	
	TC_SetPeriod( &TCD1, 6500 );
	TC1_ConfigClockSource( &TCD1, TC_CLKSEL_DIV64_gc );
	
	TC_SetPeriod( &TCE1, 6500 );
	TC1_ConfigClockSource( &TCE1, TC_CLKSEL_DIV64_gc );
	
	TC_SetPeriod( &TCD0, 6500 );
	TC0_ConfigClockSource( &TCD0, TC_CLKSEL_DIV64_gc );
	
	//~ PORTC.OUTSET = 1;
	
	SET_PHASE_STATE_5_MOT1();
	SET_PHASE_STATE_5_MOT2();
	SET_PHASE_STATE_5_MOT3();
	SET_PHASE_STATE_5_MOT4();
	motor1State = 5;
	motor2State = 5;
	motor3State = 5;
	motor4State = 5;
	
	while (1);
}

void setMotor1State (uint8_t state) {
	if (state == 0) {
		SET_PHASE_STATE_0_MOT1();
	} else if (state == 1) {
		SET_PHASE_STATE_1_MOT1();
	} else if (state == 2) {
		SET_PHASE_STATE_2_MOT1();
	} else if (state == 3) {
		SET_PHASE_STATE_3_MOT1();
	} else if (state == 4) {
		SET_PHASE_STATE_4_MOT1();
	} else if (state == 5) {
		SET_PHASE_STATE_5_MOT1();
	}
}

void setMotor2State (uint8_t state) {
	if (state == 0) {
		SET_PHASE_STATE_0_MOT2();
	} else if (state == 1) {
		SET_PHASE_STATE_1_MOT2();
	} else if (state == 2) {
		SET_PHASE_STATE_2_MOT2();
	} else if (state == 3) {
		SET_PHASE_STATE_3_MOT2();
	} else if (state == 4) {
		SET_PHASE_STATE_4_MOT2();
	} else if (state == 5) {
		SET_PHASE_STATE_5_MOT2();
	}
}

void setMotor3State (uint8_t state) {
	if (state == 0) {
		SET_PHASE_STATE_0_MOT3();
	} else if (state == 1) {
		SET_PHASE_STATE_1_MOT3();
	} else if (state == 2) {
		SET_PHASE_STATE_2_MOT3();
	} else if (state == 3) {
		SET_PHASE_STATE_3_MOT3();
	} else if (state == 4) {
		SET_PHASE_STATE_4_MOT3();
	} else if (state == 5) {
		SET_PHASE_STATE_5_MOT3();
	}
}

void setMotor4State (uint8_t state) {
	if (state == 0) {
		SET_PHASE_STATE_0_MOT4();
	} else if (state == 1) {
		SET_PHASE_STATE_1_MOT4();
	} else if (state == 2) {
		SET_PHASE_STATE_2_MOT4();
	} else if (state == 3) {
		SET_PHASE_STATE_3_MOT4();
	} else if (state == 4) {
		SET_PHASE_STATE_4_MOT4();
	} else if (state == 5) {
		SET_PHASE_STATE_5_MOT4();
	}
}
