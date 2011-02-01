#include "pid.h"

void pid_set_kp (struct pid_info* pid, volatile float kp) {
	pid->kp = kp;
}

void pid_set_ki (struct pid_info* pid, volatile float ki) {
	pid->ki = ki;
}

void pid_set_kd (struct pid_info* pid, volatile float kd) {
	pid->kd = kd;
}

void pid_set_target (struct pid_info* pid, volatile float target) {
	pid->target = target;
}

void pid_reset_i (struct pid_info* pid) {
	pid->i = 0;
}

float pid_iteration (struct pid_info* pid, volatile float value, uint32_t time_stamp) {
	float error = value - pid->target;
	pid->i += error/*(float)(time_stamp - pid->prev_time)*/;
	float deltaError = (error - pid->prev_error)/*/(float)(time_stamp - pid->prev_time)*/;
	
	float output = pid->kp*error + pid->ki*pid->i + pid->kd*deltaError;
	
	pid->prev_error = error;
	pid->prev_time = time_stamp;
	
	return output;
}

void print_pid_info(struct pid_info * pid)
{
    printf("\n\r");
    printf("pid_info:\n\r");
	printf("\tkp = *%f\n\r", (double)pid->kp);
	printf("\tki = *%f\n\r", (double)pid->ki);
	printf("\tkd = *%f\n\r", (double)pid->kd);
	printf("\ti  = *%f\n\r", (double)pid->i);
	printf("\tprev_error = *%f\n\r", (double)pid->prev_error);
	printf("\tprev_time  = *%ld\n\r", pid->prev_time);
	printf("\ttarget     = *%f\n\r", (double)pid->target);
}
