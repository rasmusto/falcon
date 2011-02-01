#define F_CPU 32000000UL
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "avr_compiler.h"
#include "clksys_driver.h"
#include "usart_driver.h"
#include "TC_driver.h"
#include "hires_driver.h"
#include "awex_driver.h"
#include "adc_driver.h"

#define STARTUP_LOCK_TIME
#define STARTUP_PWM
#define TRANSITION_VOLTAGE

// map putchar to mystdout for use with printf (stdout needs to be set to &debug in main)
static int putcharDebug(char c, FILE *stream);
static void initUarts (void);
static FILE debug = FDEV_SETUP_STREAM (PutcharDebug, NULL, _FDEV_SETUP_WRITE);

void configClock (void);
void initUarts (void);
void configPWM (volatile TC0_t * tc, HIRES_t * hires, uint16_t period);
void setPwmA (volatile TC0_t* tc, uint16_t duty);
void setPwmB (volatile TC0_t* tc, uint16_t duty);
void setPwmC (volatile TC0_t* tc, uint16_t duty);
uint8_t initAdc (ADC_t * adc);

uint8_t adcOffsetA;
uint8_t adcOffsetB;
uint8_t samplingGroup = 0;

uint8_t previousSenseValues[12];
uint8_t senseValues[12];
uint8_t phaseOutputs[3];

int main (void) {
	configClock ();
	initUarts ();
	stdout = &debug;
	
	configPWM (&TCF0, &HIRESF, 5000);

	adcOffsetA = initAdc (&ADCA);
	adcOffsetB = initAdc (&ADCB);
	
	sei();
	
	TCF0.CCABUF = STARTUP_PWM;
	TCF0.CCBBUF = STARTUP_PWM;
	TCF0.CCCBUF = STARTUP_PWM;
	TCF0.CCDBUF = STARTUP_PWM;
	
	// lock all phase As to magnet - starting position
	phaseOutputs[0] = 0b10000010;
	phaseOutputs[1] = 0b00100000;
	phaseOutputs[2] = 0b00001000;
	
	_delay_ms (STARTUP_LOCK_TIME);

	// pull rotor towards next step
	phaseOutputs[0] = ??;
	phaseOutputs[1] = ??;
	phaseOutputs[2] = ??;

	while (1) {
		if (previousSenseValues[0] < TRANSITION_VOLTAGE && senseValues[0] > TRANSITION_VOLTAGE)
			// transition to new step
		previousSenseValues[0] = senseValues[0];
		if (previousSenseValues[1] < TRANSITION_VOLTAGE && senseValues[1] > TRANSITION_VOLTAGE)
			// transition to new step
		previousSenseValues[0] = senseValues[0];
		// ...
	}
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
	
	// output clock on port d pin 7
	//~ PORTCFG.CLKEVOUT = PORTCFG_CLKOUT_PD7_gc; 
}

static void initUarts (void) {
    // Set the TxD pin high - set PORTD DIR register bit 3 to 1
    PORTC.OUTSET = PIN3_bm;
 
    // Set the TxD pin as an output - set PORTD OUT register bit 3 to 1
    PORTC.DIRSET = PIN3_bm;
 
    // BSEL = 51 so at 32mhz clock, baud rate should be 38400
	
    USARTC0.BAUDCTRLB = 0;			// BSCALE = 0 as well
    USARTC0.BAUDCTRLA = 51;
 
    // Set mode of operation
    USARTC0.CTRLA = 0;				// no interrupts please
    USARTC0.CTRLC = 0x03;			// async, no parity, 8 bit data, 1 stop bit
 
    // Enable transmitter only
    USARTC0.CTRLB = USART_TXEN_bm;
}

// Configures PWM output on compare a b and c for single slope pwm, with hires, and clk source as sys clk
void configPWM (volatile TC0_t * tc, HIRES_t * hires, uint16_t period) {
	TC_SetPeriod (tc, period ); // set TCC0 period
	TC0_ConfigWGM (tc, TC_WGMODE_NORMAL_gc ); // set to single slope pwm generation mode
	TC0_EnableCCChannels (tc, TC0_CCAEN_bm); // enable compare A
	TC0_EnableCCChannels (tc, TC0_CCBEN_bm); // enable compare B
	TC0_EnableCCChannels (tc, TC0_CCCEN_bm); // enable compare C
	TC0_EnableCCChannels (tc, TC0_CCCEN_bm); // enable compare D

	TC0_SetCCAIntLevel (tc, TC_CCAINTLVL_LO_gc);
	TC0_SetCCBIntLevel (tc, TC_CCAINTLVL_LO_gc);
	TC0_SetCCCIntLevel (tc, TC_CCAINTLVL_LO_gc);
	TC0_SetCCDIntLevel (tc, TC_CCAINTLVL_LO_gc);
	
	TC0_SetOverflowIntLevel (tc, TC_OVFINTLVL_LO_gc);
	
	PMIC.CTRL |= PMIC_LOLVLEN_bm;

	TC0_ConfigClockSource (tc, TC_CLKSEL_DIV1_gc);
	HIRES_Enable (hires, HIRES_HREN_TC0_gc);
}

// use these to set duty cycle:

// TCF0.CCABUF = value
// TCF0.CCBBUF = value
// TCF0.CCCBUF = value
// TCF0.CCDBUF = value

}

// 8 bit, Unsigned, Single Ended, 125khz
// ref = vcc/1.6 = 3.3v/1.6 = 2.0625v
// 1X Gain
// Initialize to channels pins 0,1,2,3 on channels 0,1,2,3

uint8_t initAdc (ADC_t * adc) {
	ADC_CalibrationValues_Load (adc);
  	ADC_ConvMode_and_Resolution_Config (adc, ADC_ConvMode_Unsigned, ADC_RESOLUTION_8BIT_gc);
	ADC_Prescaler_Config (adc, ADC_PRESCALER_DIV256_gc); // Fadc = 125khz
	ADC_Reference_Config (adc, ADC_REFSEL_VCC_gc); // vref = vcc/1.6

   	/* Get offset value */
   	
	ADC_Ch_InputMode_and_Gain_Config (&(adc->CH0),
	                                 ADC_CH_INPUTMODE_DIFF_gc,
	                                 ADC_CH_GAIN_64X_gc);

   	ADC_Ch_InputMux_Config (&(adc->CH0), ADC_CH_MUXPOS_PIN1_gc, ADC_CH_MUXNEG_PIN1_gc);
	ADC_Enable (adc);
	ADC_Wait_32MHz (adc); // Wait until common mode voltage is stable.
 	int offset = ADC_Offset_Get_Signed (&ADCA, &ADCA.CH0, false);
    ADC_Disable (adc);
    
    /* Setup channel 0, 1, 2 and 3 to have single ended input and 1x gain. */
	ADC_Ch_InputMode_and_Gain_Config (&(adc->CH0),
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_CH_GAIN_1X_gc);

	ADC_Ch_InputMode_and_Gain_Config (&(adc->CH1),
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_CH_GAIN_1X_gc);

	ADC_Ch_InputMode_and_Gain_Config (&(adc->CH2),
	                                 ADC_CH_INPUTMODE_DIFF_gc,
	                                 ADC_CH_GAIN_1X_gc);

	ADC_Ch_InputMode_and_Gain_Config (&(adc->CH3),
	                                 ADC_CH_INPUTMODE_DIFF_gc,
	                                 ADC_CH_GAIN_1X_gc);
    
	/* Set input to the channels in ADC A to be PIN 0, 1, 2 and 3. */
	ADC_Ch_InputMux_Config (&(adc->CH0), ADC_CH_MUXPOS_PIN0_gc, ADC_CH_MUXPOS_PIN0_gc);
	ADC_Ch_InputMux_Config (&(adc->CH1), ADC_CH_MUXPOS_PIN1_gc, ADC_CH_MUXPOS_PIN1_gc);
	ADC_Ch_InputMux_Config (&(adc->CH2), ADC_CH_MUXPOS_PIN2_gc, ADC_CH_MUXPOS_PIN2_gc);
	ADC_Ch_InputMux_Config (&(adc->CH3), ADC_CH_MUXPOS_PIN3_gc, ADC_CH_MUXPOS_PIN3_gc);
	samplingGroup = 0; // Keep trak of which group of pins this adc is sampling from.  Start with group 0 (pins 0,1,2,3)

	ADC_SweepChannels_Config (adc, ADC_SWEEP_0123_gc); // Setup sweep of all four virtual channels.

	/* Enable low level sample complete interrupt for all 4 channels */
	ADC_Ch_Interrupts_Config (&(adc->CH0), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_LO_gc);
	ADC_Ch_Interrupts_Config (&(adc->CH1), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_LO_gc);
	ADC_Ch_Interrupts_Config (&(adc->CH2), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_LO_gc);
	ADC_Ch_Interrupts_Config (&(adc->CH3), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_LO_gc);

	PMIC.CTRL |= PMIC_LOLVLEN_bm; // Enable low level interrupts
	ADC_Enable (adc); // Enable ADC A with free running mode
	ADC_Wait_32MHz (adc); // Wait until common mode voltage is stable
	ADC_FreeRunning_Enable (adc); // Enable free running mode
	
	return offset;
}

ISR(ADCA_CH0_vect) {
	ADCA.CH0.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
	if (samplingGroup == 0)
		senseValues[0] = ADCA.CH0.RES-adcOffsetA;
	else
		senseValues[4] = ADCA.CH0.RES-adcOffsetA;
}

ISR(ADCA_CH1_vect) {
	ADCA.CH1.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
	if (samplingGroup == 0)
		senseValues[1] = ADCA.CH1.RES-adcOffsetA;
	else
		senseValues[5] = ADCA.CH1.RES-adcOffsetA;
}

ISR(ADCA_CH2_vect) {
	ADCA.CH2.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
	if (samplingGroup == 0)
		senseValues[2] = ADCA.CH2.RES-adcOffsetA;
	else
		senseValues[6] = ADCA.CH2.RES-adcOffsetA;
}

ISR(ADCA_CH3_vect) {
	ADCA.CH3.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
	if (samplingGroup == 0)
		senseValues[3] = ADCA.CH3.RES-adcOffsetA;
	else
		senseValues[7] = ADCA.CH3.RES-adcOffsetA;
	
	// Flip between sampling groups for adcA, because we need to sample all 8 pins and there are only 4 adc channels
	if (samplingGroup = 0) {
		// Set input to the channels in ADC A to be PIN 4, 5, 6 and 7
		ADC_Ch_InputMux_Config(&(adc->CH0), ADC_CH_MUXPOS_PIN4_gc, ADC_CH_MUXPOS_PIN4_gc);
		ADC_Ch_InputMux_Config(&(adc->CH1), ADC_CH_MUXPOS_PIN5_gc, ADC_CH_MUXPOS_PIN5_gc);
		ADC_Ch_InputMux_Config(&(adc->CH2), ADC_CH_MUXPOS_PIN6_gc, ADC_CH_MUXPOS_PIN6_gc);
		ADC_Ch_InputMux_Config(&(adc->CH3), ADC_CH_MUXPOS_PIN7_gc, ADC_CH_MUXPOS_PIN7_gc);
		samplingGroup = 1; // keep track of sampleingGroup.  Group 1 = Pins 4,5,6,7
	} else {
		// Set input to the channels in ADC A to be PIN 0, 1, 2 and 3
		ADC_Ch_InputMux_Config(&(adc->CH0), ADC_CH_MUXPOS_PIN0_gc, ADC_CH_MUXPOS_PIN0_gc);
		ADC_Ch_InputMux_Config(&(adc->CH1), ADC_CH_MUXPOS_PIN1_gc, ADC_CH_MUXPOS_PIN1_gc);
		ADC_Ch_InputMux_Config(&(adc->CH2), ADC_CH_MUXPOS_PIN2_gc, ADC_CH_MUXPOS_PIN2_gc);
		ADC_Ch_InputMux_Config(&(adc->CH3), ADC_CH_MUXPOS_PIN3_gc, ADC_CH_MUXPOS_PIN3_gc);
		samplingGroup = 0; // keep track of sampleingGroup.  Group 1 = Pins 0,1,2,3
	}
}

ISR(ADCB_CH0_vect) {
	ADCB.CH0.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
	senseValues[8] = ADCB.CH0.RES-adcOffsetB;
}

ISR(ADCB_CH1_vect) {
	ADCB.CH1.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
	senseValues[9] = ADCB.CH1.RES-adcOffsetB;
}

ISR(ADCB_CH2_vect) {
	ADCB.CH2.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
	senseValues[10] = ADCB.CH2.RES-adcOffsetB;
}

ISR(ADCB_CH3_vect) {
	ADCB.CH3.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
	senseValues[11] = ADCB.CH3.RES-adcOffsetB;
}

// When TCF0 compare interrupts are triggered, turn off the set of 6 outputs which
// controls the phase assigned to that interrupt

ISR (TCF0_CCA_vect) {
	PORTE.OUT &= 0b11000000; // turn off porte bits 0-5
}

ISR (TCF0_CCB_vect) {
	PORTE.OUT &= 0b00111111; // turn off porte bits 6-7
	PORTF.OUT &= 0b11110000; // turn off portf bits 0-3
}

ISR (TCF0_CCC_vect) {
	PORTF.OUT &= 0b00001111; // turn off portf bits 4-7
	PORTF.OUT &= 0b00001111; // turn off portf bits 4-7
}

ISR (TCF0_CCD_vect) {
	PORTD.OUT &= 0b00000011; // turn off portf bits 2-7
}

// When TCF0 overflows, set all phase outputs to their commutation value
ISR (TCF0_OVF_vect) {
	PORTE.OUT &= phaseOutputs[0];
	PORTF.OUT &= phaseOutputs[1];
	PORTD.OUT &= phaseOutputs[2];
}

static int putcharDebug (char c, FILE *stream) {
	if (c == '\n')
		PutcharDebug('\r', stream);
 
    // Wait for the transmit buffer to be empty
    while ( !( USARTC0.STATUS & USART_DREIF_bm) );
 
    // Put our character into the transmit buffer
    USARTDC.DATA = c; 
 
    return 0;
}
