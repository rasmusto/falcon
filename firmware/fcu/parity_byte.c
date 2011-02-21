/****************************************************
 * parity_byte
 * Takes an array of Uint16's and a length.
 * XOR's all Uint16's together,
 * then XOR's the top of the result with the bottom,
 * effectively creating an 8-bit parity byte.
 * **************************************************/
#include "parity_byte.h"

uint16_t parity_byte(uint16_t * data, uint16_t length)
{
	uint16_t i, temp=0;
	for(i=0;i<length;i++)
		temp ^= data[i];
	return ((temp & 0x00FF)^(temp >> 8)); 		
}
