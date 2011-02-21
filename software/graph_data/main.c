/*
      Filename:      imu_test.c
      Authors:       Joey Tomlinson
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <glib.h>

#include "uart.h"
#include "gtkgraph.h"
#include "dyGraph.h"

#define RX_BUFFER_LENGTH 10000


struct imu_rx_pkt_t
{
    volatile uint8_t start;
    volatile uint8_t parity;
    volatile int16_t roll;
    volatile int16_t pitch_tmp;
    volatile int16_t pitch;
    volatile int16_t yaw;
    volatile int16_t yaw_tmp;
    volatile int16_t z_accel;
    volatile int16_t x_accel;
    volatile int16_t y_accel;
};

void terminate(int sig);
void graphPacket (struct imu_rx_pkt_t * packet, float time);
guint readSerial (void);

struct dyGraph* graph;

struct dyTrace* rollTrace;
struct dyTrace* pitchTrace;
struct dyTrace* yawTrace;
struct dyTrace* xAccelTrace;
struct dyTrace* yAccelTrace;
struct dyTrace* zAccelTrace;
struct dyTrace* pitchTempTrace;
struct dyTrace* yawTempTrace;

float graphTime = 0;
int uartfd; 

int main (int argc, char *argv[]) {
	
	if (argc != 2) {
		printf ("Usage: graph <serial port device (ex /dev/ttyUSB0)\n>");
		exit(-1);
	} 

	uartfd = initUART(argv[1]);
	
	//Set up termination signal routine (when user hits Ctrl-c or SIGINT is sent to this process)
	signal(SIGINT, terminate);
	
	//******************* Set up GTK window **********************
	
	GtkWidget *window;
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Graph Test");
	
	gtk_widget_show(window);
	
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (gtk_main_quit), NULL);
    
    
    //******************* Make dyGraph **********************
	graph = dyGraphInit ("IMU AWESOMENESS", "", "Time", "Acceleration/Velocity", 100, -100, 100);
    
    //******************* Add table to the window and show everything **********************
	
	gtk_container_add(GTK_CONTAINER(window), (GtkWidget*)graph->table); // add the graph to the window
    gtk_widget_show(graph->table);
    
    rollTrace = dyGraphAddTrace (graph, SOLID, 1, RED, "Roll");
    pitchTrace = dyGraphAddTrace (graph, SOLID, 1, GREEN, "Pitch");
    yawTrace = dyGraphAddTrace (graph, SOLID, 1, BLUE, "Yaw");
    xAccelTrace = dyGraphAddTrace (graph, DOTTED, 1, RED, "X");
    yAccelTrace = dyGraphAddTrace (graph, DOTTED, 1, GREEN, "Y");
    zAccelTrace = dyGraphAddTrace (graph, DOTTED, 1, BLUE, "Z");
    pitchTempTrace = dyGraphAddTrace (graph, DASHED, 1, GREEN, "P Temp");
    yawTempTrace = dyGraphAddTrace (graph, DASHED, 1, BLUE, "Y Temp");
    
    
    g_timeout_add(1, (GSourceFunc) readSerial, NULL);
	
	gtk_main();
	return 0;
}

void graphPacket (struct imu_rx_pkt_t * packet, float time) {
	dyGraphAddData(graph, rollTrace, time, packet->roll);
	dyGraphAddData(graph, pitchTrace, time, packet->pitch);
	dyGraphAddData(graph, yawTrace, time, packet->yaw);
	dyGraphAddData(graph, yawTempTrace, time, packet->yaw_tmp);
	dyGraphAddData(graph, pitchTempTrace, time, packet->pitch_tmp);
	dyGraphAddData(graph, zAccelTrace, time, packet->z_accel);
	dyGraphAddData(graph, xAccelTrace, time, packet->x_accel);
	dyGraphAddData(graph, yAccelTrace, time, packet->y_accel);
}

guint readSerial (void) {
	unsigned char rxBuffer[RX_BUFFER_LENGTH];
	
	int bytesRead = read (uartfd, rxBuffer, RX_BUFFER_LENGTH-1);
	int i;
	for (i=0; i<bytesRead; i++) {
		if (rxBuffer[i] == 0xAA) {
			int j=0;
			while (i<bytesRead) { // if 0xAA was found at index in rxBuffer other than 0, shift everything over so that 0xAA is at 0
				rxBuffer[j] = rxBuffer[i];
				j++;
				i++;
			}
			while (j<18) {
				int dataBytesRead = read (uartfd, rxBuffer+j, RX_BUFFER_LENGTH-j-1);
				j += dataBytesRead;
				usleep(100);
			}
			graphTime += 0.001;
			graphPacket ((struct imu_rx_pkt_t*)rxBuffer, graphTime);
			break;
		}
	}
	return TRUE;
}

//Callback for ctrl-c signal (SIGINT)
void terminate(int sig) {
	exit(0);
}

