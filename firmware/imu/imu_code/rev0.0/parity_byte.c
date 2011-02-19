/****************************************************
 * parity_byte
 * Takes an array of Uint16's and a length.
 * XOR's all Uint16's together,
 * then XOR's the top of the result with the bottom,
 * effectively creating an 8-bit parity byte.
 * **************************************************/
#include "imu_main.h"


Uint16 parity_byte(Uint16 * data, Uint16 length)
{
	Uint16 i, temp=0;
	for(i=0;i<length;i++)
		temp ^= data[i];
	return ((temp & 0x00FF)^(temp >> 8)); 		
}
