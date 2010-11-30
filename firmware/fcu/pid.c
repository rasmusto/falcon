#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "pid.h"

/*
// example main function
int main (void) {
	struct pidInfo* pid = (struct pidInfo*) malloc(sizeof(struct pidInfo));
	pidSetKp (pid, 123.456);
	pidSetKi (pid, 123.456);
	pidSetKd (pid, 123.456);
	pidSetTarget (pid, 123.456);
	float initialValue = 1111.1111;
	float initialTime = 22222222;
	pidIteration (pid, initialValue, initialTime); // call pidIteration once and ignore return to initialize the i accumulator, previous error and previous timestamp tracking
	while (1) {
		float value = 12345.67890;
		uint32_t timeStamp = 1234567890;
		float pidOutput = pidIteration (pid, value, timeStamp); // call pidIteration with the value of the new data and a timestamp every time data is recieved.
	}
}
*/

void pidSetKp (volatile struct pidInfo* pid, volatile float kp) {
	pid->kp = kp;
}

void pidSetKi (volatile struct pidInfo* pid, volatile float ki) {
	pid->ki = ki;
}

void pidSetKd (volatile struct pidInfo* pid, volatile float kd) {
	pid->kd = kd;
}

void pidSetTarget (volatile struct pidInfo* pid, volatile float target) {
	pid->target = target;
}

void resetI (volatile struct pidInfo* pid) {
	pid->i = 0;
}

float pidIteration (volatile struct pidInfo* pid, volatile float value, uint32_t timeStamp) {
	float error = value - pid->target;
	pid->i += error/*(float)(timeStamp - pid->previousTime)*/;
	float deltaError = (error - pid->previousError)/*/(float)(timeStamp - pid->previousTime)*/;

	float output = pid->kp*error + pid->ki*pid->i + pid->kd*deltaError;

	pid->previousError = error;
	pid->previousTime = timeStamp;

	return output;
}

void printPidInfo(volatile struct pidInfo * pid)
{
	printf("kp = *%f\n", (double)pid->kp);
	printf("ki = *%f\n", (double)pid->ki);
	printf("kd = *%f\n", (double)pid->kd);
	printf("i = *%f\n", (double)pid->i);
	printf("previousError = *%f\n", (double)pid->previousError);
	printf("previousTime = *%ld\n", pid->previousTime);
	printf("target = *%f\n", (double)pid->target);
}
