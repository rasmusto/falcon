#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

void init_xbee_uart (int8_t bScale, uint16_t bSel);
void init_usb_uart (int8_t bScale, uint16_t bSel);
void init_rs232_uart (int8_t bScale, uint16_t bSel);
void init_sonar_uart (int8_t bScale, uint16_t bSel);

void putchar_xbee (char c);
void putchar_usb (char c);
void putchar_rs232 (char c);
void putchar_sonar (char c);

