#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "joystick.h"

static int joystick_fd = -1;

int open_joystick()
{
	joystick_fd = open(JOYSTICK_DEVNAME, O_RDONLY | O_NONBLOCK); /* read write for force feedback? */
	if (joystick_fd < 0)
		return joystick_fd;

	return joystick_fd;
}

int read_joystick_event(struct js_event *jse)
{
	int bytes;

	bytes = read(joystick_fd, jse, sizeof(*jse)); 

	if (bytes == -1)
		return 0;

	if (bytes == sizeof(*jse))
		return 1;

	printf("Unexpected bytes from joystick:%d\n", bytes);

	return -1;
}

void close_joystick()
{
	close(joystick_fd);
}

int get_joystick_status(struct wwvi_js_event *wjse)
{
	int rc;
	struct js_event jse;
	if (joystick_fd < 0)
		return -1;

	while ((rc = read_joystick_event(&jse) == 1)) {
		jse.type &= ~JS_EVENT_INIT; /* ignore synthetic events */
		if (jse.type == JS_EVENT_AXIS) {
			switch (jse.number) {
			case 0: wjse->stick_x = jse.value;
				break;
			case 1: wjse->stick_y = jse.value;
				break;
			default:
				break;
			}
		} else if (jse.type == JS_EVENT_BUTTON) {
			if (jse.number < 10) {
				switch (jse.value) {
				case 0:
				case 1: wjse->button[jse.number] = jse.value;
					break;
				default:
					break;
				}
			}
		}
	}
	return 0;
}

/* a little test program */
int main(int argc, char *argv[])
{
	int fd, rc;
	int done = 0;
    
    int16_t roll, pitch, yaw, power;

	struct js_event jse;

	fd = open_joystick();
	if (fd < 0) {
		printf("open failed.\n");
		exit(1);
	}

	while (!done) {
		rc = read_joystick_event(&jse);
		usleep(100);
		if (rc == 1) {
			printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n", 
				jse.time, jse.value, jse.type, jse.number);
            if (jse.number == 0) { 
                //printf("roll = %d at time = %d\n", jse.value, jse.time);
                roll = jse.value;
            }
            if (jse.number == 1) {
                //printf("pitch = %d at time = %d\n", jse.value, jse.time);
                pitch = jse.value;
            }
            if (jse.number == 2) {
                //printf("yaw? = %d at time = %d\n", jse.value, jse.time);
                yaw = jse.value;
            }
            if (jse.number == 3) {
                //printf("power = %d at time = %d\n", jse.value, jse.time);
                power = jse.value;
            }
			//printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n", 
			//	jse.time, jse.value, jse.type, jse.number);
		}
        system("clear");
        printf("roll\t=\t%d\npitch\t=\t%d\nyaw\t=\t%d\npower\t=\t%d\n", roll, pitch, yaw, power);
	}
}
