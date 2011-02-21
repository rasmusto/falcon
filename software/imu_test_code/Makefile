BINNAME = imu_test
CC      = gcc
#CC      = $(HOME)/overo-oe/tmp/cross/armv7a/bin/arm-angstrom-linux-gnueabi-gcc
#CC		 = $(HOME)/overo-oe/tmp/cross/armv7a/bin/arm-angstrom-linux-gnueabi-g++
CFLAGS   = -Wall -ggdb
LDFLAGS  = -Wall -lm -lrt -ggdb

default: imu_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) imu_test.c uart.c timing.c -o $(BINNAME)

clean:
	rm -f $(BINNAME)
