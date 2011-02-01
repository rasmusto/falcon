#define F_CPU 32000000UL
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "avr_compiler.h"
#include "clksys_driver.h"

void configClock (void);

// A1 high porte0
// A1 low porte1

int main (void) {
	configClock ();
	
	PORTE.DIR = 0b11000000;
	PORTF.DIR = 0b00001111;
	
	while (1) {
		PORTE.OUT = 0b00000000; // set floating
		PORTF.OUT = 0b00000000; // set floating
		__asm__ volatile ( "nop" ); // wait a bit (hundredish nanoseconds)
		__asm__ volatile ( "nop" );
		__asm__ volatile ( "nop" );
		__asm__ volatile ( "nop" );
		PORTE.OUT = 0b01000000; // set channel 2 outputs high
		PORTF.OUT = 0b00000101; // set channel 2 outputs high
		_delay_us (20);
		
		PORTE.OUT = 0b00000000; // set floating
		PORTF.OUT = 0b00000000; // set floating
		__asm__ volatile ( "nop" ); // wait a bit (hundredish nanoseconds)
		__asm__ volatile ( "nop" );
		__asm__ volatile ( "nop" );
		__asm__ volatile ( "nop" );
		PORTE.OUT = 0b10000000; // set channel 2 outputs low
		PORTF.OUT = 0b00001010; // set channel 2 outputs high
		_delay_us (20);	
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
