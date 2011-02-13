#include "crc.h"

uint8_t crc (char * packet, uint8_t length, char divisor) {
	
	int i, j, result;
	char carryFlag = 0, nextCarryFlag = 0;
	uint8_t * temp = (uint8_t *) malloc (length+1);
	
	for (i=0;i<length;i++) // copy packet to temp
		temp[i] = packet[i];
	temp[length] = 0;
	
	for (j=((length*8)-1);j>=0;j--) {	
		carryFlag = 0;
		for (i=j/8;i>=0;i--) { // shift
			nextCarryFlag = (temp[i]/128);
			temp[i] *= 2;
			temp[i] += carryFlag;
			carryFlag = nextCarryFlag;
		} // carryFlag now holds last carry
		
		if (nextCarryFlag)
			temp[0] ^= divisor; // xor
	}

	result = (uint8_t) temp[0];
	free(temp);
	return result;
}
