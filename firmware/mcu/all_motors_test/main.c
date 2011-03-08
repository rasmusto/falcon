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

// Macros

	#include "setPhaseMacros.c"

// functions

	void configClock (void);
	void configPWMTimer (volatile TC0_t * tc, HIRES_t * hires, uint16_t period); // configure timer used to generate pwm
    void spiInit (void);

// globals
    volatile uint8_t spiBuffer[8];

// vars
	#define phaseOutputsEHigh GPIO0 // keep track of which pins should be driven high during high part of pwm
	#define phaseOutputsFHigh GPIO1 // keep track of which pins should be driven high during high part of pwm
	#define phaseOutputsDHigh GPIO2 // keep track of which pins should be driven high during high part of pwm

	#define phaseOutputsELow GPIO3 // keep track of which pins should be driven high during low part of pwm
	#define phaseOutputsFLow GPIO4 // keep track of which pins should be driven high during low part of pwm
	#define phaseOutputsDLow GPIO5 // keep track of which pins should be driven high during low part of pwm

	#define getSpiPktFlag GPIOD
    #define spiIndex GPIOE

#define writeBackFlag GPIOF
		
int main (void) {
	
	PMIC.CTRL |= PMIC_HILVLEN_bm; // Enable HI Level Interrupts - all interrupts are high level in this application
	spiInit ();
    sei();
    while(1){}
	configClock (); // set up 32mhz internal oscillator 
	
	PORTE.DIR = 0xFF; // all motor lines outputs
	PORTF.DIR = 0xFF;
	PORTD.DIR = 0xFF;
	
	configPWMTimer (&TCF0, &HIRESF, 5000);	
	
	PMIC.CTRL |= PMIC_HILVLEN_bm; // Enable HI Level Interrupts - all interrupts are high level in this application
	sei();
	
	TCF0.CCABUF = 500;
	TCF0.CCBBUF = 1000;
	TCF0.CCCBUF = 1500;
	TCF0.CCDBUF = 2000;
	
	while(1) {
		SET_PHASE_STATE_0_MOT1();
		SET_PHASE_STATE_0_MOT2();
		SET_PHASE_STATE_0_MOT3();
		SET_PHASE_STATE_0_MOT4();
		_delay_ms(2);
		SET_PHASE_STATE_1_MOT1();
		SET_PHASE_STATE_1_MOT2();
		SET_PHASE_STATE_1_MOT3();
		SET_PHASE_STATE_1_MOT4();
		_delay_ms(2);
		SET_PHASE_STATE_2_MOT1();
		SET_PHASE_STATE_2_MOT2();
		SET_PHASE_STATE_2_MOT3();
		SET_PHASE_STATE_2_MOT4();
		_delay_ms(2);
		SET_PHASE_STATE_3_MOT1();
		SET_PHASE_STATE_3_MOT2();
		SET_PHASE_STATE_3_MOT3();
		SET_PHASE_STATE_3_MOT4();
		_delay_ms(2);
		SET_PHASE_STATE_4_MOT1();
		SET_PHASE_STATE_4_MOT2();
		SET_PHASE_STATE_4_MOT3();
		SET_PHASE_STATE_4_MOT4();
		_delay_ms(2);
		SET_PHASE_STATE_5_MOT1();
		SET_PHASE_STATE_5_MOT2();
		SET_PHASE_STATE_5_MOT3();
		SET_PHASE_STATE_5_MOT4();
		_delay_ms(2);
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

// *************** SPI **********************
void spiInit () 
{
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MODE_2_gc;
	SPIC.INTCTRL = SPI_INTLVL_HI_gc;
	PORTC.DIRSET = SPI_MISO_bm;
    PORTC.DIRCLR = 0b10111111;
}
// *************** /SPI **********************
ISR(SPIC_INT_vect) 
{
	uint8_t data = SPIC.DATA;
	if (writeBackFlag) {
		if (spiIndex == 0)
			SPIC.DATA = ((uint8_t*)(&(TCF0.CCABUF)))[0];
		if (spiIndex == 1)
			SPIC.DATA = ((uint8_t*)(&(TCF0.CCABUF)))[1];
		if (spiIndex == 2)
			SPIC.DATA = ((uint8_t*)(&(TCF0.CCBBUF)))[0];
		if (spiIndex == 3)
			SPIC.DATA = ((uint8_t*)(&(TCF0.CCBBUF)))[1];
		if (spiIndex == 4)
			SPIC.DATA = ((uint8_t*)(&(TCF0.CCCBUF)))[0];
		if (spiIndex == 5)
			SPIC.DATA = ((uint8_t*)(&(TCF0.CCCBUF)))[1];
		if (spiIndex == 6)
			SPIC.DATA = ((uint8_t*)(&(TCF0.CCDBUF)))[0];
		if (spiIndex == 7) {
			SPIC.DATA = ((uint8_t*)(&(TCF0.CCDBUF)))[1];
			writeBackFlag = 0;
		}
	} else {
		if (data == 0xB5) {
			getSpiPktFlag = 1;
			spiIndex = 0;
		} else if (getSpiPktFlag) {
			spiBuffer[spiIndex] = data;
			spiIndex++;
			if (spiIndex == 8) {
				getSpiPktFlag = 0;
				TCF0.CCABUF = ((uint16_t *)spiBuffer)[0];
				TCF0.CCBBUF = ((uint16_t *)spiBuffer)[1];
				TCF0.CCCBUF = ((uint16_t *)spiBuffer)[2];
				TCF0.CCDBUF = ((uint16_t *)spiBuffer)[3];
				writeBackFlag = 1;
			}
		}
	}
}
