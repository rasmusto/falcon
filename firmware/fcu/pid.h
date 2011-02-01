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

float pid_iteration(struct pid_info* pid, float value, uint32_t time_stamp);
void pid_set_kp(struct pid_info* pid, float kp);
void pid_set_ki(struct pid_info* pid, float ki);
void pid_set_kd(struct pid_info* pid, float kd);
void pid_set_target(struct pid_info* pid, float target);
void print_pid_info(struct pid_info * pid);
void pid_reset_i(struct pid_info* pid);
