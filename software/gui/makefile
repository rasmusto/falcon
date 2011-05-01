CC      = gcc
CFLAGS  = -Wall -ggdb
LDFLAGS = -Wall -lm
DEF     = -DDEBUG_LEVEL=0

all: graph

lib: gtkgraph.o axis.o annotation.o polar.o polar_util.o trace.o smith.o dyGraph.o

graph: main.o uart.o gtkgraph.o axis.o annotation.o polar.o polar_util.o trace.o smith.o dyGraph.o
	$(CC) $(LDFLAGS) -lrt main.o uart.o gtkgraph.o axis.o annotation.o polar.o polar_util.o trace.o smith.o dyGraph.o `pkg-config gtk+-2.0 --cflags --libs` -o graph 

main.o: main.c
	$(CC) $(DEF) $(CFLAGS) -c main.c `pkg-config gtk+-2.0 --cflags`
	
uart.o: uart.c
	$(CC) $(DEF) $(CFLAGS) -c uart.c
	
#gtkgraph

dyGraph.o: dyGraph.c
	$(CC) $(DEF) $(CFLAGS) -c dyGraph.c `pkg-config gtk+-2.0 --cflags`

gtkgraph.o: gtkgraph.c
	$(CC) $(DEF) $(CFLAGS) -c gtkgraph.c `pkg-config gtk+-2.0 --cflags`

axis.o: axis.c
	$(CC) $(DEF) $(CFLAGS) -c axis.c `pkg-config gtk+-2.0 --cflags`

annotation.o: annotation.c
	$(CC) $(DEF) $(CFLAGS) -c annotation.c `pkg-config gtk+-2.0 --cflags`

polar.o: polar.c
	$(CC) $(DEF) $(CFLAGS) -c polar.c `pkg-config gtk+-2.0 --cflags`

polar_util.o: polar_util.c
	$(CC) $(DEF) $(CFLAGS) -c polar_util.c `pkg-config gtk+-2.0 --cflags`

trace.o: trace.c
	$(CC) $(DEF) $(CFLAGS) -c trace.c `pkg-config gtk+-2.0 --cflags`

smith.o: smith.c
	$(CC) $(DEF) $(CFLAGS) -c smith.c `pkg-config gtk+-2.0 --cflags`

clean:
	rm -f graph
	rm -f *.o
