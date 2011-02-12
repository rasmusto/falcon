#include <avr/io.h>
#include "TC_driver.h"

int main (void) {
	PORTC.DIRSET = 1;
	
	PORTC.OUTSET = 1;
	TC_SetPeriod( &TCD1, 1000 );
	TC1_ConfigClockSource( &TCD1, TC_CLKSEL_DIV1_gc );
	
	TC0_SetOverflowIntLevel (&TCD1, TC_OVFINTLVL_HI_gc);
	
	PMIC.CTRL |= PMIC_HILVLEN_bm;
	sei();
	
	while (1);
}

//~ ISR (TCD1_CCA_vect) {
	//~ TCD1.INTFLAGS |= TC1_CCAIF_bm;
	//~ PORTC.OUTCLR = 1;
	//~ TC1_DisableCCChannels( &TCD1, TC1_CCAEN_bm );
	//~ TC1_SetCCAIntLevel( &TCD1, TC_CCAINTLVL_OFF_gc );
//~ }

ISR (TCD1_OVF_vect) {
	PORTC.OUTCLR = 1;
}
