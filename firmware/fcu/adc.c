#define F_CPU 32000000UL
#include <stdio.h>
#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "adc.h"
#include "adc_driver.h"

volatile int gADC_CH0_ZeroOffset=0;
