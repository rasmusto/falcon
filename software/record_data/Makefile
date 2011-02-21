BINNAME = record
CC      = gcc
CFLAGS  = -Wall -ggdb
LDFLAGS = -Wall -lm -lrt -ggdb

all: graph

graph: main.o uart.o
	$(CC) $(LDFLAGS) -lrt main.o uart.o -o $(BINNAME) 

main.o: main.c
	$(CC) $(DEF) $(CFLAGS) -c main.c `pkg-config gtk+-2.0 --cflags`

uart.o: uart.c
	$(CC) $(DEF) $(CFLAGS) -c uart.c

clean:
	rm -f $(BINNAME)
	rm -f *.o
