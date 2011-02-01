// Possible avr-gcc xmega bug?
// Author: Joey Tomlinson
// Date: 1/27/11

// Expected Behavior:

	// With BLOCK A removed:
	//   Output PWM signal on PORTC for ever.
	
	// With BLOCK B removed:
	//   Output PWM signal on PORTC for 2 seconds.  Then output high on PORTC.
	
	// With BLOCK B and BLOCK C removed:
	//   Output PWM signal on PORTC for 2 seconds.  Then output high on PORTC.
	//   (Same as just BLOCK B removed)
	
// Observed Behavior (Compiled with GCC 4.3.4, Binutils 2.20):

	// With BLOCK A removed:
	//   Output PWM signal on PORTC for ever. (As expected)

	// With BLOCK B removed:
	//   Output *low* on PORTC for 2 seconds.  Then output high on PORTC.

	// With BLOCK B and BLOCK C removed:
	//   Output PWM signal on PORTC for 2 seconds.  Then output high on PORTC. (As expected)

#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "avr_compiler.h"
#include "TC_driver.h"

void configurePwmTimer (volatile TC0_t * tc, uint16_t period);

unsigned char phaseOutputsEHigh = 0;
unsigned char phaseOutputsELow = 0; 

int main (void) {
	PORTC.DIR = 0xFF;
	configurePwmTimer (&TCF0, 5000);
	sei();
	TCF0.CCBBUF = 500;
	
	phaseOutputsEHigh = 0xFF;
	phaseOutputsELow = 0x00;
	
	// ** BLOCK A ** 
		int i;
		for (i=0;i<20;i++) {
			_delay_ms (100);
		}
	// ** /BLOCK A ** 
	
	// ** BLOCK B ** 
		while (1) {
			_delay_ms (20);
		}
	//  ** /BLOCK B ** 
	
	// ** BLOCK C ** 
		phaseOutputsEHigh = 0x00;
		phaseOutputsELow = 0x00;
	// ** /BLOCK C ** 

	cli();
	PORTC.OUT = 0xFF;
	
	while (1);
}

void configurePwmTimer (volatile TC0_t * tc, uint16_t period) {
	TC_SetPeriod (tc, period);
	TC0_EnableCCChannels (tc, TC0_CCBEN_bm);

	TC0_SetCCBIntLevel (tc, TC_CCBINTLVL_HI_gc);
	TC0_SetOverflowIntLevel (tc, TC_OVFINTLVL_HI_gc);
	
	PMIC.CTRL |= PMIC_HILVLEN_bm;

	TC0_ConfigClockSource (tc, TC_CLKSEL_DIV1_gc);
}

ISR (TCF0_CCB_vect) {
	PORTC.OUT = phaseOutputsELow;
}

ISR (TCF0_OVF_vect) {
	PORTC.OUT = phaseOutputsEHigh;
}
