/*
      Filename:      imu_test.c
      Authors:       Joey Tomlinson
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "imu_test.h"
#include "uart.h"
#include "timing.h"

#define TX_BUFFER_LENGTH 10000
#define RX_BUFFER_LENGTH 10000

struct AccelArMagMPacket {
	float accelX;
	float accelY;
	float accelZ;
	float angRateX;
	float angRateY;
	float angRateZ;
	float magX;
	float magY;
	float magZ;
	float m11;
	float m12;
	float m13;
	float m21;
	float m22;
	float m23;
	float m31;
	float m32;
	float m33;
	unsigned long timer;
};

struct RawPacket {
	float accelX;
	float accelY;
	float accelZ;
	float gyroX;
	float gyroY;
	float gyroZ;
	unsigned long timer;
};

struct AccelEuler {
	float accelX;
	float accelY;
	float accelZ;
	float roll;
	float pitch;
	float yaw;
	unsigned long timer;
};

void terminate(int sig);

//~ int findRawPacket (char* rxBuffer, struct RawPacket* packet);
int findAccelArMagMPacket (unsigned char * rxBuffer, int bufferTail, int startIndex, struct AccelArMagMPacket* packet);

int main (int argc, char *argv[]) {
	
	if (argc != 2) {
		printf ("Usage: imu_test <serial port device (ex /dev/ttyUSB0)\n>");
		exit(-1);
	} 

	int uartfd = initUART(argv[1]);
	
	//Set up termination signal routine (when user hits Ctrl-c or SIGINT is sent to this process)
	signal(SIGINT, terminate);

    //Create packet structs for storing packet data
	struct RawPacket* raw = (struct RawPacket*) malloc(sizeof(struct RawPacket));
	struct AccelArMagMPacket* accelArMagM = (struct AccelArMagMPacket*)malloc(sizeof(struct AccelArMagMPacket));
	struct AccelEuler* accelEuler = (struct AccelEuler *)malloc(sizeof(struct AccelEuler));
    	
    unsigned char* txBuffer = (unsigned char*)malloc(TX_BUFFER_LENGTH);
	unsigned char* rxBuffer = (unsigned char*)malloc(RX_BUFFER_LENGTH);
	
	int bufferTail = 0;
	int charsRead = 0;
	int startIndex = 0;
    
    // Stop Continuous Mode
    //~ txBuffer[0] = SET_CONTINUOUS_MODE;
    //~ txBuffer[1] = CONFIRM_BYTE_1;
    //~ txBuffer[2] = CONFIRM_BYTE_2;
    //~ txBuffer[3] = STOP_CONTINUOUS_MODE;
    //~ write(uartfd, txBuffer, 4);
	
	// Start Continuous Mode with ACCEL_ANG_RATE_MAG_ORIENT
    txBuffer[0] = 0xE9;
    write(uartfd, txBuffer, 1);
    
	//~ while (bufferTail < 1000) {
	int i;
	for (i=0;i<1000;i++) {
		usleep(100); //Make sure we don't use up too much processing power
		charsRead = read(uartfd, rxBuffer + bufferTail, (TX_BUFFER_LENGTH-bufferTail-1)); // read from serial port
		bufferTail = bufferTail + charsRead; // add new stuff read to the tail of the serial data buffer
		
		//~ startIndex = findAccelArMagMPacket (rxBuffer, bufferTail, startIndex, accelArMagM);
		//~ if (startIndex == -1) {
			//~ printf ("\n***findAccelArMagMPacket says it found a packet***\n");
			//~ return 0;
		//~ }
	}
	//~ int i;
	
	printf ("Buffer Tail = %d\n", bufferTail);
	for (i=0; i<bufferTail; i++) {
		printf("%02X ", rxBuffer[i]);
		if ((i+1)%10 == 0)
			printf ("\n");
	}
	printf ("\n");
	
	short checksum = 0;
	if (bufferTail == 15) {
		for (i=1; i<13; i++)
			checksum += rxBuffer[i];
	printf ("Checksum = 0x%X\n", checksum);
	}
	return 0;
}

//Callback for ctrl-c signal (SIGINT)
void terminate(int sig) {
	exit(0);
}

//~ int findRawPacket (char* rxBuffer, struct RawPacket * packet) {}

// returns -1 if packet is found.  Otherwise returns position to start searching next time
int findAccelArMagMPacket (unsigned char * rxBuffer, int bufferTail, int startIndex, struct AccelArMagMPacket* packet) {
	
	//~ printf ("Stepping through buffer... sop=0xCC\n");
	// go through buffer looking for sop
	int i;
	for (i=0; i<bufferTail; i++) {
		//~ printf ("%02X ", rxBuffer[i]);
		if (rxBuffer[i] == ACCEL_ANG_RATE_MAG_ORIENT) {
			if (i+ACCEL_ANG_RATE_MAG_ORIENT_LEN-1 > bufferTail) {
				printf ("\nFound sop but not enough room in buffer for complete packet.\nReturning with header index.\n");
				return i; // if incomplete packet has not been recieved, return sop index to start searching from next time
			} else {
				// check checksum
				short checksum = 0;
				int j;
				for (j=i+1;j<=(i+ACCEL_ANG_RATE_MAG_ORIENT_LEN);j++) {
					checksum += rxBuffer[j];
				}
				if ( ((short*)rxBuffer)[i+ACCEL_ANG_RATE_MAG_ORIENT_LEN] == checksum) {
					// parse packet
					printf ("\nFound sop and checksum matched.\nReturning packet\n");
					return -1;
				}
				printf ("\nFound sop but checksum didnt match.\nContinuing Search\n");
			}
		}
	}
	//~ printf ("\nDid not find sop.\nReturn last searched position\n");
	return i; // if no sop found, return last searched position
}
