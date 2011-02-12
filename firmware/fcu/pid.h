#include <inttypes.h>
#include <stdio.h>

volatile struct pid_info 
{
	float kp;
	float ki;
	float kd;
	float i;
	float prev_error;
	uint32_t prev_time;
	float target;
};

float pid_iteration(volatile struct pid_info* pid, float value, uint32_t time_stamp);
void pid_set_kp(volatile struct pid_info* pid, float kp);
void pid_set_ki(volatile struct pid_info* pid, float ki);
void pid_set_kd(volatile struct pid_info* pid, float kd);
void pid_set_target(volatile struct pid_info* pid, float target);
void print_pid_info(volatile struct pid_info * pid);
void pid_reset_i(volatile struct pid_info* pid);
