#include "flight_controller.h"

void green()
{

	LED_MOT_1_GREEN();
	LED_MOT_2_GREEN();	
	LED_MOT_3_GREEN();
	LED_MOT_4_GREEN();

	LED_MISC_1_GREEN();
	LED_MISC_2_GREEN();	
	LED_MISC_3_GREEN();
	LED_MISC_4_GREEN();
}

void alternate()
{
	LED_MOT_1_YELLOW();
	LED_MOT_2_RED();	
	LED_MOT_3_YELLOW();
	LED_MOT_4_RED();

	LED_MISC_1_YELLOW();
	LED_MISC_2_RED();	
	LED_MISC_3_YELLOW();
	LED_MISC_4_RED();
}

void yellow()
{

	LED_MOT_1_YELLOW();
	LED_MOT_2_YELLOW();	
	LED_MOT_3_YELLOW();
	LED_MOT_4_YELLOW();

	LED_MISC_1_YELLOW();
	LED_MISC_2_YELLOW();	
	LED_MISC_3_YELLOW();
	LED_MISC_4_YELLOW();
}
void red()
{

	LED_MOT_1_RED();
	LED_MOT_2_RED();	
	LED_MOT_3_RED();
	LED_MOT_4_RED();

	LED_MISC_1_RED();
	LED_MISC_2_RED();	
	LED_MISC_3_RED();
	LED_MISC_4_RED();
}

void off()
{

	LED_MOT_1_OFF();
	LED_MOT_2_OFF();	
	LED_MOT_3_OFF();
	LED_MOT_4_OFF();

	LED_MISC_1_OFF();
	LED_MISC_2_OFF();	
	LED_MISC_3_OFF();
	LED_MISC_4_OFF();
}


void fancyColors()
{
	LED_MISC_1_GREEN();
	_delay_ms(50);
	LED_MISC_2_GREEN();	
	_delay_ms(50);
	LED_MISC_3_GREEN();
	_delay_ms(50);
	LED_MISC_4_GREEN();
	_delay_ms(50);

	LED_MOT_1_GREEN();
	_delay_ms(50);
	LED_MOT_2_GREEN();	
	_delay_ms(50);
	LED_MOT_3_GREEN();
	_delay_ms(50);
	LED_MOT_4_GREEN();
	_delay_ms(50);
	
	LED_MISC_1_YELLOW();
	_delay_ms(50);
	LED_MISC_2_YELLOW();	
	_delay_ms(50);
	LED_MISC_3_YELLOW();
	_delay_ms(50);
	LED_MISC_4_YELLOW();
	_delay_ms(50);

	LED_MOT_1_YELLOW();
	_delay_ms(50);
	LED_MOT_2_YELLOW();	
	_delay_ms(50);
	LED_MOT_3_YELLOW();
	_delay_ms(50);
	LED_MOT_4_YELLOW();
	_delay_ms(50);

	LED_MISC_1_RED();
	_delay_ms(50);
	LED_MISC_2_RED();	
	_delay_ms(50);
	LED_MISC_3_RED();
	_delay_ms(50);
	LED_MISC_4_RED();
	_delay_ms(50);
	
	LED_MOT_1_RED();
	_delay_ms(50);
	LED_MOT_2_RED();	
	_delay_ms(50);
	LED_MOT_3_RED();
	_delay_ms(50);
	LED_MOT_4_RED();
	_delay_ms(50);

	LED_MOT_4_GREEN();
	_delay_ms(50);
	LED_MOT_3_GREEN();
	_delay_ms(50);
	LED_MOT_2_GREEN();	
	_delay_ms(50);
	LED_MOT_1_GREEN();
	_delay_ms(50);

	LED_MISC_4_GREEN();
	_delay_ms(50);
	LED_MISC_3_GREEN();
	_delay_ms(50);
	LED_MISC_2_GREEN();	
	_delay_ms(50);
	LED_MISC_1_GREEN();
	_delay_ms(50);
}
