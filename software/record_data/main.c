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
#include <inttypes.h>

#include "uart.h"

#define RX_BUFFER_LENGTH 10000

struct imu_rx_pkt_t
{
    volatile uint8_t start;
    volatile uint8_t parity;
    volatile int16_t roll;
    volatile int16_t pitch_tmp;
    volatile int16_t pitch;
    volatile int16_t yaw;
    volatile int16_t yaw_tmp;
    volatile int16_t z_accel;
    volatile int16_t x_accel;
    volatile int16_t y_accel;
};

void terminate(int sig);

float graphTime = 0;
int uartfd; 
FILE * file;

int main (int argc, char *argv[]) {
	
	if (argc != 3) {
		printf ("Usage: graph <serial port device (ex /dev/ttyUSB0)> <csv filename>\n");
		exit(-1);
	} 

	uartfd = initUART(argv[1]);
	file = fopen(argv[2], "w");
		
	fprintf (file, "roll, ");
	fprintf (file, "pitch, ");
	fprintf (file, "yaw, ");
	fprintf (file, "x accel, ");
	fprintf (file, "y accel, ");
	fprintf (file, "z accel\n");
	
	//Set up termination signal routine (when user hits Ctrl-c or SIGINT is sent to this process)
	signal(SIGINT, terminate);
		
	unsigned char rxBuffer[RX_BUFFER_LENGTH];
	int counter = 0;
	while (1) {
	
		int bytesRead = read (uartfd, rxBuffer, RX_BUFFER_LENGTH-1);
		int i;
		for (i=0; i<bytesRead; i++) {
			if (rxBuffer[i] == 0xAA) {
				int j=0;
				while (i<bytesRead) { // if 0xAA was found at index in rxBuffer other than 0, shift everything over so that 0xAA is at 0
					rxBuffer[j] = rxBuffer[i];
					j++;
					i++;
				}
				while (j<18) {
					int dataBytesRead = read (uartfd, rxBuffer+j, RX_BUFFER_LENGTH-j-1);
					j += dataBytesRead;
					usleep(100);
				}
				fprintf (file, "%d, ", ((struct imu_rx_pkt_t*)rxBuffer)->roll);
				fprintf (file, "%d, ", ((struct imu_rx_pkt_t*)rxBuffer)->pitch);
				fprintf (file, "%d, ", ((struct imu_rx_pkt_t*)rxBuffer)->yaw);
				fprintf (file, "%d, ", ((struct imu_rx_pkt_t*)rxBuffer)->x_accel);
				fprintf (file, "%d, ", ((struct imu_rx_pkt_t*)rxBuffer)->y_accel);
				fprintf (file, "%d\n", ((struct imu_rx_pkt_t*)rxBuffer)->z_accel);
				break;
			}
		}
	}
}

//Callback for ctrl-c signal (SIGINT)
void terminate(int sig) {
	fclose(file);
	exit(0);
}
