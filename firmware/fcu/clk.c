#include "clk.h"

void init_clk (void) 
{
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
