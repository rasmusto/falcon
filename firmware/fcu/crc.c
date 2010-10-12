#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "crc.h"

//~ int main () {
	//~ char* buffer = "1234qa78";
	//~ int result = crc(buffer, 8, 7);
	//~ printf ("crc:0x%x %c\n", result, result);
//~ }

uint8_t crc (char * packet, uint8_t length, char divisor) {
	uint8_t * temp = (uint8_t*) malloc (length+1);
	int i;
	int j;
	char carryFlag = 0;
	char nextCarryFlag = 0;
	
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

	int result = (uint8_t) temp[0];
	free (temp);
	return result;
}
	
void printBinaryArray (char* array, int length) {
	int i;
	char* buf = (char*) malloc (length+1);
	
	for (i=0;i<length;i++)
		buf[i] = array[i];
		
	for (i=0;i<length;i++) {
		printf ("%c", (buf[i]/128)?'1':'0');
		buf[i] %= 128;
		printf ("%c", (buf[i]/64)?'1':'0');
		buf[i] %= 64;
		printf ("%c", (buf[i]/32)?'1':'0');
		buf[i] %= 32;
		printf ("%c", (buf[i]/16)?'1':'0');
		buf[i] %= 16;
		printf ("%c", (buf[i]/8)?'1':'0');
		buf[i] %= 8;
		printf ("%c", (buf[i]/4)?'1':'0');
		buf[i] %= 4;
		printf ("%c", (buf[i]/2)?'1':'0');
		buf[i] %= 2;
		printf ("%c", (buf[i])?'1':'0');
		printf (" ");
	}
	
	free (buf);
}
