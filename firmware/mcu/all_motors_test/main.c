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
#include "spi_driver.h"

#define MOT1
//~ #define MOT2
//~ #define MOT3
//~ #define MOT4

#define RFCOUNT 2

// Macros

	#include "setPhaseMacros.c"

// functions

	void configClock (void);
	void configPWMTimer (volatile TC0_t * tc, HIRES_t * hires, uint16_t period); // configure timer used to generate pwm
	void configHalfPWMTimer (volatile TC0_t * tc, HIRES_t * hires, uint16_t period); // configure timer used to generate interrupt half way into pwm high period
    void initAdc (ADC_t * adc); // use to initialize adcs
	void configDelayTimer (volatile TC0_t * tc); // configure timer used to generate delays
	void spiInit (void);


	#ifdef MOT1
	void setMotor1State (uint8_t state); // motors to their a commutation state based on an integ 
	#endif
	
	#ifdef MOT2
	void setMotor2State (uint8_t state); // -- used instead of macros to allow numerical indexing of states
	#endif
	
	#ifdef MOT3
	void setMotor3State (uint8_t state);
	#endif
	
	#ifdef MOT4
	void setMotor4State (uint8_t state);
	#endif

	void startup(void); // run startup commutation routine, then transition to automatic comutation

// Constant Things

	// these are constants that define which direction the back emf slope goes during each state
	// 0 = falling
	// 1 = rising
	#define STATE_SLOPE 0b00101010

	// these are constants that define the index of the pin to look at for back emf during each state
	// middle thresholds for back emf "zero" crossing for each motor.  I'm not sure if this needs to vary with pwm or not...
	#ifdef MOT1
	const uint8_t motor1StateSenseIndex[6] = {2,1,0,2,1,0};
	#define MOTOR_1_THRESH 92
	#endif
	
	#ifdef MOT2
	const uint8_t motor2StateSenseIndex[6] = {5,4,3,5,4,3};
	#define MOTOR_2_THRESH 92
	#endif
	
	#ifdef MOT3
	const uint8_t motor3StateSenseIndex[6] = {0,7,6,0,7,6};
	#define MOTOR_3_THRESH 92
	#endif
	
	#ifdef MOT4
	const uint8_t motor4StateSenseIndex[6] = {3,2,1,3,2,1};
	#define MOTOR_4_THRESH 92
	#endif

	#define LOCK_PWM 500 // PWM to use to lock rotor to initial position
	#define STARTUP_PWM 1200 // PWM to use for startup push

// Global variables 

	// these variables keep track of which pins should be driven during the high and low parts of the pwm cycle
	#define phaseOutputsEHigh GPIO0 // keep track of which pins should be driven high during high part of pwm
	#define phaseOutputsFHigh GPIO1 // keep track of which pins should be driven high during high part of pwm
	#define phaseOutputsDHigh GPIO2 // keep track of which pins should be driven high during high part of pwm

	#define phaseOutputsELow GPIO3 // keep track of which pins should be driven high during low part of pwm
	#define phaseOutputsFLow GPIO4 // keep track of which pins should be driven high during low part of pwm
	#define phaseOutputsDLow GPIO5 // keep track of which pins should be driven high during low part of pwm


	#define passedCenterFlags GPIOA // holds flags for each motor telling wether they are half way through the state yet
	#define missedCommFlags GPIOB // holds flags for each motor telling wether they are half way through the state yet
	
	#ifdef MOT1
	volatile uint8_t risingCount1;
	volatile uint8_t fallingCount1;
	// holds current motor state (1-6)
	#define motor1State GPIO6 
	#endif
	
	#ifdef MOT2
	volatile uint8_t risingCount2;
	volatile uint8_t fallingCount2;
	#define motor2State GPIO7
	#endif
	
	#ifdef MOT3
	volatile uint8_t risingCount3;
	volatile uint8_t fallingCount3;
	#define motor3State GPIO8
	#endif
	
	#ifdef MOT4
	volatile uint8_t risingCount4;
	volatile uint8_t fallingCount4;
	#define motor4State GPIO9
	#endif
	
    volatile uint8_t spiWriteBuffer[9];
    volatile uint8_t spiBuffer[8];
	
int main (void) {
	
	PORTC.DIRSET = (1<<5);
	
	configClock (); // set up 32mhz internal oscillator 
	
	#ifdef MOT1
	PORTE.DIRSET = 0b00111111; // all motor lines outputs
	#endif
	
	#ifdef MOT2
	PORTE.DIRSET = 0b11000000; // all motor lines outputs
	PORTF.DIRSET = 0b00001111;
	#endif
	
	#ifdef MOT3
	PORTF.DIRSET = 0b11110000;
	PORTD.DIRSET = 0b00000011;
	#endif
	
	#ifdef MOT4
	PORTD.DIRSET = 0b11111100;
	#endif
	
	configPWMTimer (&TCF0, &HIRESF, 5000);
	configHalfPWMTimer (&TCE0, &HIRESE, 5000);
	
	configDelayTimer (&TCC0);
	
	initAdc (&ADCA);
	initAdc (&ADCB);
	
	PMIC.CTRL |= PMIC_HILVLEN_bm;
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	
	#ifdef MOT1
	TCF0.CCABUF = LOCK_PWM;
	TCE0.CCABUF = LOCK_PWM/2;
	#endif
	
	#ifdef MOT2
	TCF0.CCBBUF = LOCK_PWM;
	TCE0.CCBBUF = LOCK_PWM/2;
	#endif
	
	#ifdef MOT3
	TCF0.CCCBUF = LOCK_PWM;
	TCE0.CCCBUF = LOCK_PWM/2;
	#endif
	
	#ifdef MOT4
	TCF0.CCDBUF = LOCK_PWM;
	TCE0.CCDBUF = LOCK_PWM/2;
	#endif
	
	sei();
	
	startup();
	//~ spiInit();
	
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
		
		#ifdef MOT1
		TC0_EnableCCChannels (tc, TC0_CCAEN_bm); // enable compare A
		TC0_SetCCAIntLevel (tc, TC_CCAINTLVL_HI_gc);
		#endif
		
		#ifdef MOT2
		TC0_EnableCCChannels (tc, TC0_CCBEN_bm); // enable compare B
		TC0_SetCCBIntLevel (tc, TC_CCBINTLVL_HI_gc);
		#endif
		
		#ifdef MOT3		
		TC0_EnableCCChannels (tc, TC0_CCCEN_bm); // enable compare C
		TC0_SetCCCIntLevel (tc, TC_CCCINTLVL_HI_gc);
		#endif
		
		#ifdef MOT4
		TC0_EnableCCChannels (tc, TC0_CCDEN_bm); // enable compare D
		TC0_SetCCDIntLevel (tc, TC_CCDINTLVL_HI_gc);
		#endif
		
		TC0_SetOverflowIntLevel (tc, TC_OVFINTLVL_HI_gc);

		TC0_ConfigClockSource (tc, TC_CLKSEL_DIV1_gc);
		HIRES_Enable (hires, HIRES_HREN_TC0_gc);
	}

	// When TCF0 compare interrupts are triggered, set the set of 6 outputs which
	// controls the motor assigned to that interrupt to low

	#ifdef MOT1
	// Motor 1
	ISR (TCF0_CCA_vect) {	
		// motor 1 on pe0-5
		
		// force bits 6 and 7 to 1 (for phaseOutputsEHighInv) and 0 (for phaseOutputsEHighInv) so that only pins for motor 1 are turned off 
		PORTE.OUTCLR = (phaseOutputsEHigh & 0b00111111); // turn off all high bits in phaseOutputsELowInv
		PORTE.OUTSET = (phaseOutputsELow & 0b00111111); // turn on all low bits in phaseOutputsEHigh	
	}
	#endif

	#ifdef MOT2
	// Motor 2
	ISR (TCF0_CCB_vect) {
		// motor 2 on pe6-7 and pf0-3
		
		PORTE.OUTCLR = (phaseOutputsEHigh & 0b11000000); // turn off all high bits in phaseOutputsELowInv
		PORTE.OUTSET = (phaseOutputsELow & 0b11000000); // turn on all low bits in phaseOutputsEHigh	
		
		PORTF.OUTCLR = (phaseOutputsFHigh & 0b00001111); // turn off all high bits in phaseOutputsELowInv
		PORTF.OUTSET = (phaseOutputsFLow & 0b00001111); // turn on all low bits in phaseOutputsEHigh
	}
	#endif
	
	#ifdef MOT3
	// Motor 3
	ISR (TCF0_CCC_vect) {
		// motor 3 on pf4-7 and pd0-1
		
		PORTF.OUTCLR = (phaseOutputsFHigh & 0b11110000); // turn off all high bits in phaseOutputsELowInv
		PORTF.OUTSET = (phaseOutputsFLow & 0b11110000); // turn on all low bits in phaseOutputsEHigh	
		
		PORTD.OUTCLR = (phaseOutputsDHigh & 0b00000011); // turn off all high bits in phaseOutputsELowInv
		PORTD.OUTSET = (phaseOutputsDLow & 0b00000011); // turn on all low bits in phaseOutputsEHigh	
	}
	#endif
	
	#ifdef MOT4
	// Motor 4
	ISR (TCF0_CCD_vect) {
		// motor 4 on pd2-7
		
		PORTD.OUTCLR = (phaseOutputsDHigh & 0b11111100); // turn off all high bits in phaseOutputsELowInv
		PORTD.OUTSET = (phaseOutputsDLow & 0b11111100); // turn on all low bits in phaseOutputsEHigh	
	}
	#endif
	
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
		TC_SetPeriod (tc, period);
		TC0_ConfigWGM (tc, TC_WGMODE_NORMAL_gc); // set to single slope pwm generation mode
		
		#ifdef MOT1
		TC0_EnableCCChannels (tc, TC0_CCAEN_bm); // enable compare A
		TC0_SetCCAIntLevel (tc, TC_CCAINTLVL_HI_gc);
		#endif
		
		#ifdef MOT2
		TC0_EnableCCChannels (tc, TC0_CCBEN_bm); // enable compare B
		TC0_SetCCBIntLevel (tc, TC_CCBINTLVL_HI_gc);
		#endif
		
		#ifdef MOT3		
		TC0_EnableCCChannels (tc, TC0_CCCEN_bm); // enable compare C
		TC0_SetCCCIntLevel (tc, TC_CCCINTLVL_HI_gc);
		#endif
		
		#ifdef MOT4
		TC0_EnableCCChannels (tc, TC0_CCDEN_bm); // enable compare D
		TC0_SetCCDIntLevel (tc, TC_CCDINTLVL_HI_gc);
		#endif
		
		TC0_ConfigClockSource (tc, TC_CLKSEL_DIV1_gc);
		HIRES_Enable (hires, HIRES_HREN_TC0_gc);
		
	}
	
	#ifdef MOT1
	// Motor 1
	ISR (TCE0_CCA_vect) {
		// half way into high part of motor 1 pwm
		// start adc conversion on adca ch1 (this channel is dedicated to this motor)
		ADC_Ch_InputMux_Config (&ADCA.CH0, motor1StateSenseIndex[motor1State]<<3, 0);
		ADC_Ch_Conversion_Start (&(ADCA.CH0));
	}
	#endif
	
	#ifdef MOT2
	// Motor 2
	ISR (TCE0_CCB_vect) {
		// half way into high part of motor 2 pwm
		// start adc conversion on adca ch1 (this channel is dedicated to this motor)
		ADC_Ch_InputMux_Config (&ADCA.CH1, motor2StateSenseIndex[motor2State]<<3, 0);
		ADC_Ch_Conversion_Start (&(ADCA.CH1));
	}
	#endif
	
	#ifdef MOT3
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
	#endif
	
	#ifdef MOT4
	// Motor 4
	ISR (TCE0_CCD_vect) {
		// half way into high part of motor 4 pwm
		// start adc conversion on adca ch1 (this channel is dedicated to this motor)
		ADC_Ch_InputMux_Config (&ADCB.CH3, motor4StateSenseIndex[motor4State]<<3, 0);
		ADC_Ch_Conversion_Start (&(ADCB.CH3));
	}
	#endif
	
// *************** /PWM/2 **********************

// *************** Commutation Timing **********************
	
	#ifdef MOT1
	// Motor 1
	ISR (TCC1_OVF_vect) {
		// time to change motor1 state
		missedCommFlags |= (1<<1);
		TCC1.PER = 65000;
		if (motor1State < 5)
			motor1State++;
		else
			motor1State=0;

		passedCenterFlags &= ~(1<<1); // clear motor 1 passedCenterFlag	
		risingCount1 = 0;
		fallingCount1 = 0;
		setMotor1State(motor1State);
	}
	#endif
	
	#ifdef MOT2
	// Motor 2
	ISR (TCD1_OVF_vect) {
		// time to change motor2 state
		missedCommFlags |= (1<<2);
		TCD1.PER = 65000;
		if (motor2State < 5)
			motor2State++;
		else
			motor2State=0;

		passedCenterFlags &= ~(1<<2); // clear motor 2 passedCenterFlag	
		risingCount2 = 0;
		fallingCount2 = 0;
		setMotor2State(motor2State);
	}
	#endif

	#ifdef MOT3
	// Motor 3
	ISR (TCE1_OVF_vect) {
		missedCommFlags |= (1<<3);
		TCE1.PER = 65000;
		if (motor3State < 5)
			motor3State++;
		else
			motor3State=0;

		passedCenterFlags &= ~(1<<3); // clear motor 3 passedCenterFlag	
		risingCount3 = 0;
		fallingCount3 = 0;
		setMotor3State(motor3State);
	}
	#endif

	#ifdef MOT4
	// Motor 4
	ISR (TCD0_OVF_vect) {
		missedCommFlags |= (1<<4);
		TCD0.PER = 65000;
		if (motor4State < 5)
			motor4State++;
		else
			motor4State=0;

		passedCenterFlags &= ~(1<<4); // clear motor 4 passedCenterFlag	
		risingCount4 = 0;
		fallingCount4 = 0;
		setMotor4State(motor4State);
	}
	#endif
	
// *************** /Commutation Timing **********************

// *************** ADC **********************

	void initAdc (ADC_t * adc) {
		ADC_CalibrationValues_Load (adc);
		ADC_ConvMode_and_Resolution_Config (adc, ADC_ConvMode_Unsigned, ADC_RESOLUTION_8BIT_gc);
		ADC_Prescaler_Config (adc, ADC_PRESCALER_DIV32_gc); // Fadc = 125khz
		ADC_Reference_Config (adc, ADC_REFSEL_INT1V_gc); // vref = internal 1v
		
		/* Setup channel 0, 1, 2 and 3 to have single ended input and 1x gain. */
		
		#ifdef MOT1
		ADC_Ch_InputMode_and_Gain_Config (&(adc->CH0),
										 ADC_CH_INPUTMODE_SINGLEENDED_gc,
										 ADC_CH_GAIN_1X_gc);
		ADC_Ch_Interrupts_Config (&(adc->CH0), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);
		#endif
		
		#ifdef MOT2
		ADC_Ch_InputMode_and_Gain_Config (&(adc->CH1),
										 ADC_CH_INPUTMODE_SINGLEENDED_gc,
										 ADC_CH_GAIN_1X_gc);
		ADC_Ch_Interrupts_Config (&(adc->CH1), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);
		#endif

		#ifdef MOT3	
		ADC_Ch_InputMode_and_Gain_Config (&(adc->CH2),
										 ADC_CH_INPUTMODE_SINGLEENDED_gc,
										 ADC_CH_GAIN_1X_gc);
		ADC_Ch_Interrupts_Config (&(adc->CH2), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);
		#endif
		
		#ifdef MOT4
		ADC_Ch_InputMode_and_Gain_Config (&(adc->CH3),
										 ADC_CH_INPUTMODE_SINGLEENDED_gc,
										 ADC_CH_GAIN_1X_gc);
		ADC_Ch_Interrupts_Config (&(adc->CH3), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);
		#endif
		
		ADC_Enable (adc); // Enable ADC
		ADC_Wait_32MHz (adc); // Wait until common mode voltage is stable
	}

	#ifdef MOT1
	// Motor 1
	ISR (ADCA_CH0_vect) {
		ADCA.CH0.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCA.CH0.RES;
		
		if (!(passedCenterFlags & (1<<1)))
		{
			if (STATE_SLOPE & (1<<motor1State))
			{ // rising
				if (risingCount1 > RFCOUNT)
				{
					if (result > MOTOR_1_THRESH)
					{
						TCC1.PER = TCC1.CNT*2;
						missedCommFlags &= ~(1<<1);
						passedCenterFlags |= (1<<1); 
					}
				}
				risingCount1++;
			} else 
			{ // falling
				if (fallingCount1 > RFCOUNT)
				{
					if (result < MOTOR_1_THRESH)
					{
						TCC1.PER = TCC1.CNT*2;
						missedCommFlags &= ~(1<<1);
						passedCenterFlags |= (1<<1);
					}
				}
				fallingCount1++;
			}
		}
	}
	#endif
	
	#ifdef MOT2
	// Motor 2
	ISR (ADCA_CH1_vect) {
		ADCA.CH1.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCA.CH1.RES;
		
		if (!(passedCenterFlags & (1<<2))) 
		{
			if (STATE_SLOPE & (1<<motor2State)) 
			{ // rising
				if (risingCount2 > RFCOUNT) 
				{
					if (result > MOTOR_2_THRESH)
					{
						TCD1.PER = TCD1.CNT*2;
						missedCommFlags &= ~(1<<2);
						passedCenterFlags |= (1<<2); 
					}
				}
				risingCount2++;
			} else 
			{ // falling
				if (fallingCount2 > RFCOUNT) 
				{
					if (result < MOTOR_2_THRESH) 
					{
						TCD1.PER = TCD1.CNT*2;
						missedCommFlags &= ~(1<<2);
						passedCenterFlags |= (1<<2);
					}
				}
				fallingCount2++;
			}
		}
	}
	#endif
	
	#ifdef MOT3
	// Motor 3
	ISR (ADCA_CH2_vect) {
		ADCA.CH2.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCA.CH2.RES;
		
		if (!(passedCenterFlags & (1<<3))) 
		{
			if (STATE_SLOPE & (1<<motor3State)) 
			{ // rising
				if (risingCount3 > RFCOUNT) 
				{
					if (result > MOTOR_3_THRESH)
					{
						TCE1.PER = TCE1.CNT*2;
						missedCommFlags &= ~(1<<3);
						passedCenterFlags |= (1<<3); 
					}
				}
				risingCount3++;
			} else 
			{ // falling
				if (fallingCount3 > RFCOUNT) 
				{
					if (result < MOTOR_3_THRESH) 
					{
						TCE1.PER = TCE1.CNT*2;
						missedCommFlags &= ~(1<<3);
						passedCenterFlags |= (1<<3);
					}
				}
				fallingCount3++;
			}
		}
	}
	#endif
	
	#ifdef MOT3
	// Motor 3 - called for phase c (phase c feedback is on adcb)
	ISR (ADCB_CH2_vect) {
		ADCB.CH2.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCB.CH2.RES;

		if (!(passedCenterFlags & (1<<3))) 
		{
			if (STATE_SLOPE & (1<<motor3State)) 
			{ // rising
				if (risingCount3 > RFCOUNT) 
				{
					if (result > MOTOR_3_THRESH)
					{
						TCE1.PER = TCE1.CNT*2;
						missedCommFlags &= ~(1<<3);
						passedCenterFlags |= (1<<3); 
					}
				}
				risingCount3++;
			} else 
			{ // falling
				if (fallingCount3 > RFCOUNT) 
				{
					if (result < MOTOR_3_THRESH) 
					{
						TCE1.PER = TCE1.CNT*2;
						missedCommFlags &= ~(1<<3);
						passedCenterFlags |= (1<<3);
					}
				}
				fallingCount3++;
			}
		}
	}
	#endif
	
	#ifdef MOT4
	// Motor 4
	ISR (ADCB_CH3_vect) {
		ADCB.CH3.INTFLAGS = ADC_CH_CHIF_bm; // clear interrupt flag

		uint8_t result = ADCB.CH3.RES;

		if (!(passedCenterFlags & (1<<4)))
		{
			if (STATE_SLOPE & (1<<motor4State))
			{ // rising
				if (risingCount4 > RFCOUNT) 
				{
					if (result > MOTOR_4_THRESH)
					{
						TCD0.PER = TCD0.CNT*2;
						missedCommFlags &= ~(1<<4);
						passedCenterFlags |= (1<<4); 
					}
				}
				risingCount4++;
			} else 
			{ // falling
				if (fallingCount4 > RFCOUNT)
				{
					if (result < MOTOR_4_THRESH) 
					{
						TCD0.PER = TCD0.CNT*2;
						missedCommFlags &= ~(1<<4);
						passedCenterFlags |= (1<<4);
					}
				}
				fallingCount4++;
			}
		}
	}
	#endif
	
// *************** /ADC **********************

void configDelayTimer (volatile TC0_t * tc) {
	TC_SetPeriod (tc, (uint16_t)65535); // set tc period
	TC0_ConfigWGM (tc, TC_WGMODE_NORMAL_gc); // normal timer countermode
	TC0_ConfigClockSource (tc, TC_CLKSEL_DIV1024_gc);
}

void startup(void) {
	
	#ifdef MOT1
	TCF0.CCABUF = LOCK_PWM;
	SET_PHASE_STATE_5_MOT1();
	#endif
	
	#ifdef MOT2
	TCF0.CCBBUF = LOCK_PWM;
	SET_PHASE_STATE_5_MOT2();
	#endif
	
	#ifdef MOT3
	TCF0.CCCBUF = LOCK_PWM;
	SET_PHASE_STATE_5_MOT3();
	#endif
	
	#ifdef MOT4
	TCF0.CCDBUF = LOCK_PWM;
	SET_PHASE_STATE_5_MOT4();
	#endif
	
	TCC0.CNT = 0;
	while (TCC0.CNT < 65000) {}

	#ifdef MOT1
	TCF0.CCABUF = STARTUP_PWM;
	TCE0.CCABUF = STARTUP_PWM/2;
	
	TC_SetPeriod (&TCC1, 65000);
	TC1_ConfigClockSource (&TCC1, TC_CLKSEL_DIV8_gc);
	TC1_SetOverflowIntLevel (&TCC1, TC_OVFINTLVL_HI_gc);
	
	SET_PHASE_STATE_0_MOT1();
	motor1State = 0;
	
	
	missedCommFlags |= (1<<1);
	passedCenterFlags &= ~(1<<1);
	risingCount1 = 0;
	fallingCount1 = 0;
	#endif
	
	#ifdef MOT2
	TCF0.CCBBUF = STARTUP_PWM;
	TCE0.CCBBUF = STARTUP_PWM/2;
	
	TC_SetPeriod (&TCD1, 65000 );
	TC1_ConfigClockSource (&TCD1, TC_CLKSEL_DIV8_gc );
	TC1_SetOverflowIntLevel (&TCD1, TC_OVFINTLVL_HI_gc);
	
	SET_PHASE_STATE_0_MOT2();
	motor2State = 0;
	
	missedCommFlags |= (1<<2);
	passedCenterFlags &= ~(1<<2);
	risingCount2 = 0;
	fallingCount2 = 0;
	#endif
	
	#ifdef MOT3
	TCF0.CCCBUF = STARTUP_PWM;
	TCE0.CCCBUF = STARTUP_PWM/2;
	
	TC_SetPeriod (&TCE1, 65000);
	TC1_ConfigClockSource (&TCE1, TC_CLKSEL_DIV8_gc);
	TC1_SetOverflowIntLevel (&TCE1, TC_OVFINTLVL_HI_gc);
	
	SET_PHASE_STATE_0_MOT3();
	motor3State = 0;
	
	missedCommFlags |= (1<<3);
	passedCenterFlags &= ~(1<<3);
	risingCount3 = 0;
	fallingCount3 = 0;
	#endif
	
	#ifdef MOT4
	TCF0.CCDBUF = STARTUP_PWM;
	TCE0.CCDBUF = STARTUP_PWM/2;

	TC_SetPeriod (&TCD0, 65000);
	TC0_ConfigClockSource (&TCD0, TC_CLKSEL_DIV8_gc);
	TC0_SetOverflowIntLevel (&TCD0, TC_OVFINTLVL_HI_gc);
	
	SET_PHASE_STATE_0_MOT4();
	motor4State = 0;
	
	missedCommFlags |= (1<<4);
	passedCenterFlags &= ~(1<<4);
	risingCount4 = 0;
	fallingCount4 = 0;
	#endif
	
	PORTC.OUTSET = (1<<5);
}

void spiInit () {
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MODE_2_gc;
	SPIC.INTCTRL = SPI_INTLVL_HI_gc;
	PORTC.DIRSET = SPI_MISO_bm;
}

// ********* SPI *************

ISR (SPIC_INT_vect) {
    static uint8_t spi_index = 0;
    static uint8_t readPacketFlag = 0;
    static uint8_t writePacketFlag = 0;
	uint8_t data = SPIC.DATA;
    if(data == 0xB5)
    {
        readPacketFlag = 1;
        writePacketFlag = 0;
        spi_index = 0;
    }
    if(readPacketFlag)
    {
        if(data != 0xB5)
        {
            spiBuffer[spi_index] = data;
            spi_index++;
            SPIC.DATA = 0;
            if (spi_index == 9) {
				TCF0.CCABUF = *((uint16_t *)(spiBuffer+0));
				TCF0.CCBBUF = *((uint16_t *)(spiBuffer+2));
				TCF0.CCCBUF = *((uint16_t *)(spiBuffer+4));
				TCF0.CCDBUF = *((uint16_t *)(spiBuffer+6));
				
				TCE0.CCBBUF = TCF0.CCABUF/2;
				TCE0.CCBBUF = TCF0.CCBBUF/2;
				TCE0.CCBBUF = TCF0.CCCBUF/2;
				TCE0.CCBBUF = TCF0.CCDBUF/2;
				
				if (TCF0.CCABUF == 0 || TCF0.CCBBUF == 0 || TCF0.CCCBUF == 0 || TCF0.CCDBUF == 0)
				{
					PORTD.DIR = 0;
					PORTE.DIR = 0;
					PORTF.DIR = 0;
					cli();
					while(1);
				}
			}
        }
    }
    if(readPacketFlag && spi_index >= 9)
    {
        readPacketFlag = 0;
        writePacketFlag = 1;
        spi_index = 0;
    }
    if(writePacketFlag && spi_index <= 8)
    {
        SPIC.DATA = spiWriteBuffer[spi_index];
        //SPIC.DATA = 0xAA;
        spi_index++;
    }
}

// ********* /SPI *************


#ifdef MOT1
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
#endif

#ifdef MOT2
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
#endif

#ifdef MOT3
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
#endif

#ifdef MOT4
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
#endif
