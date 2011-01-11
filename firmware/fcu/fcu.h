#define F_CPU 32000000UL
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#include "spi_driver.h"
#include "avr_compiler.h"

//Led bitmasks
//#define LED_MISC_4_GREEN() PORTF.OUTCLR=PIN4_bm;PORTF.OUTSET=PIN5_bm
