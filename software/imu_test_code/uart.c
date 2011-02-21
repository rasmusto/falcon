#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/signal.h>
#include <sys/types.h>

#include "uart.h"

#define TRUE 1
#define FALSE 0

void uartSignalHandler (int status);    /* definition of signal handler */
void timeoutSignalHandler(int status);  /* definition of signal handler */
volatile int dataReadyFlag=FALSE;       /* FALSE while no signal received */
volatile int timeoutFlag=TRUE;		    /* FALSE while no signal received */

int initUART(char *devicePath){

	struct termios newtio;
	struct sigaction saio;           /* definition of signal action */

	/* open the device to be non-blocking (read will return immediatly) */
	//int fd = open(devicePath, O_RDWR | O_NOCTTY | O_NONBLOCK);
    
    int fd = open(devicePath, O_RDWR | O_NOCTTY );

	if (fd < 0) { 
		printf("IMU: could not open serial port\n");
		printf("IMU: devicePath = %s\n", devicePath);
		exit(-1); 
	}


	/* install the signal handler before making the device asynchronous */
	//saio.sa_handler = uartSignalHandler;
	//saio.sa_flags = 0;
	//saio.sa_restorer = NULL;
	//sigaction(SIGIO,&saio,NULL);
	  
	/* allow the process to receive SIGIO */
	//fcntl(fd, F_SETOWN, getpid());

	/* Make the file descriptor asynchronous (the manual page says only 
	   O_APPEND and O_NONBLOCK, will work with F_SETFL...) */

	//fcntl(fd, F_SETFL, FASYNC);

	/* set new port settings for canonical input processing */
	newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VMIN] = 0;
	newtio.c_cc[VTIME] = 0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);

	return fd;
}

void initTimeout(void){

	struct sigaction alarmSignal;           /* definition of signal action */

	alarmSignal.sa_handler = timeoutSignalHandler;
	alarmSignal.sa_flags = 0;
	alarmSignal.sa_restorer = NULL;
	sigaction(SIGALRM, &alarmSignal, NULL);
	alarm(0);

}

int getDataReadyFlag(void){
	return dataReadyFlag;
}

void clearDataReadyFlag(void){
	dataReadyFlag = FALSE;
}

int getTimeoutFlag(void){
	return timeoutFlag;
}

void setTimeoutFlag(void){
	timeoutFlag = TRUE;
}

void clearTimeoutFlag(void){
	timeoutFlag = FALSE;
}

void stopTimeout(void){
	alarm(0);
}

void startTimeout(void){
	alarm(1);
}


/***************************************************************************
* signal handler. sets timeoutFlag to TRUE, to indicate above loop that  *
* characters have been received.                                           *
***************************************************************************/

void timeoutSignalHandler(int status){
	timeoutFlag = TRUE;
}

/***************************************************************************
* signal handler. sets dataReadyFlag to TRUE, to indicate above loop that  *
* characters have been received.                                           *
***************************************************************************/

void uartSignalHandler(int status){
	dataReadyFlag = TRUE;
}

