#include "pid.h"

void pidSetKp (struct pid_info* pid, volatile float kp) {
	pid->kp = kp;
}

void pidSetKi (struct pid_info* pid, volatile float ki) {
	pid->ki = ki;
}

void pidSetKd (struct pid_info* pid, volatile float kd) {
	pid->kd = kd;
}

void pidSetTarget (struct pid_info* pid, volatile float target) {
	pid->target = target;
}

void resetI (struct pid_info* pid) {
	pid->i = 0;
}

float pidIteration (struct pid_info* pid, volatile float value, uint32_t time_stamp) {
	float error = value - pid->target;
	pid->i += error/*(float)(time_stamp - pid->prev_time)*/;
	float deltaError = (error - pid->prev_error)/*/(float)(time_stamp - pid->prev_time)*/;
	
	float output = pid->kp*error + pid->ki*pid->i + pid->kd*deltaError;
	
	pid->prev_error = error;
	pid->prev_time = time_stamp;
	
	return output;
}

void printpid_info(struct pid_info * pid)
{
	printf("kp = *%f\n", (double)pid->kp);
	printf("ki = *%f\n", (double)pid->ki);
	printf("kd = *%f\n", (double)pid->kd);
	printf("i = *%f\n", (double)pid->i);
	printf("prev_error = *%f\n", (double)pid->prev_error);
	printf("prev_time = *%ld\n", pid->prev_time);
	printf("target = *%f\n", (double)pid->target);
}
