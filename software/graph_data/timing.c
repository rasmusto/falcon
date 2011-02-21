#include "timing.h"

long get_time_ms() {
	struct timeval curtime;
	struct timezone curzone;
	gettimeofday(&curtime, &curzone);
	long time_msec = curtime.tv_usec/1000;
	long time_sec = curtime.tv_sec;
	long this_time = time_sec * 1000 + time_msec;
	return this_time;
}
