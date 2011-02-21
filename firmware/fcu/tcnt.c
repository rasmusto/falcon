#include "TC_driver.h"
#include "tcnt.h"
//#include "/usr/lib/avr/include/avr/iox128a3.h"
void init_tcnt()
{
    TCC0.CTRLA = TC_CLKSEL_DIV64_gc; 
    TCD0.CTRLA = TC_CLKSEL_DIV64_gc; 

    TCC0.CTRLB = TC0_CCDEN_bm | TC0_CCCEN_bm | TC0_CCBEN_bm | TC0_CCAEN_bm | TC0_WGMODE0_bm; 
    TCD0.CTRLB = TC0_CCDEN_bm | TC0_CCCEN_bm | TC0_CCBEN_bm | TC0_CCAEN_bm | TC0_WGMODE0_bm; 

    //PWN input capture on event channel (N+2)%8 = 2
    TCC0.CTRLD = TC0_EVACT2_bm | TC0_EVACT1_bm | TC0_EVSEL3_bm; 
    //PWM input capture on event channel (N+3)%8 = 3
    TCD0.CTRLD = TC0_EVACT2_bm | TC0_EVACT1_bm | TC0_EVSEL3_bm;

    TCC0.PER = 0x7FFF;
    TCD0.PER = 0x7FFF;

    /*
       6. Wait for Input Capture Interrupt Flag A in INTFLAGS to be set.
       7. Read input capture value from the CCA[H:L] register into ‘thisCapture’.
       8. Check bit 15 of ‘thisCapture’.
       9. If bit 15 of ‘thisCapture’ is 1
       a. Save ‘thisCapture’ in ‘lastRising’
       10. else
       a. Calculate total period:
       */

}
