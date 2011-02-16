#include "crc.h"

Uint16 crc(Uint16 * packet, Uint16 length, Uint16 divisor){
	
	int i, j, result;
	long count = 0; //just for scotts test
	char carryFlag = 0, nextCarryFlag = 0;
	Uint16 * temp = (Uint16 *) malloc (length+1);
	
	for (i=0;i<length;i++) // copy packet to temp
		temp[i] = packet[i];
	temp[length] = 0;
	
	for (j=((length*16)-1);j>=0;j--) {	
		carryFlag = 0;
		for (i=j/16;i>=0;i--) { // shift
			nextCarryFlag = (temp[i]>>15);
			temp[i] *= 2;
			temp[i] += carryFlag;
			carryFlag = nextCarryFlag;
			count++;	//just scotts test
		} // carryFlag now holds last carry
		
		if (nextCarryFlag)
			temp[0] ^= divisor; // xor
	}

	result = (Uint16) temp[0];
	result = count;
	free(temp);
	return result;
}
