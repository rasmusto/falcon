#include <stdint.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <math.h>
#include "gtkgraph.h"
#include "dyGraph.h"

#include "uart.h"

#define RX_BUFFER_LENGTH 10000

struct dyTrace* acclXTrace;
struct dyTrace* acclYTrace;
struct dyTrace* acclZTrace;

struct dyTrace* gyroXTrace;
struct dyTrace* gyroYTrace;
struct dyTrace* gyroZTrace;

struct dyTrace* eulerRollTrace;
struct dyTrace* eulerPitchTrace;
struct dyTrace* eulerYawTrace;

struct dyTrace* pidRollTrace;
struct dyTrace* pidPitchTrace;
struct dyTrace* pidYawTrace;

struct dyTrace* pidRollTargetTrace;
struct dyTrace* pidPitchTargetTrace;
struct dyTrace* pidYawTargetTrace;

struct dyTrace* motor1Trace;
struct dyTrace* motor2Trace;
struct dyTrace* motor3Trace;
struct dyTrace* motor4Trace;

struct dyGraph * dyGraphRawAccelerometer;
struct dyGraph * dyGraphRawGyro;
struct dyGraph * dyGraphOrientation;
struct dyGraph * dyGraphPid;

static gint testUpdate (void);

// ***************** Serial Stuff *********************

struct fcu_pkt_t
{
    volatile uint8_t start;
    volatile uint8_t parity;
    volatile int16_t x_gyro;
    volatile int16_t x_gyro_tmp;
    volatile int16_t y_gyro;
    volatile int16_t z_gyro;
    volatile int16_t z_gyro_tmp;
    volatile int16_t z_accel;
    volatile int16_t x_accel;
    volatile int16_t y_accel;
    volatile int16_t roll;
    volatile int16_t pitch;
    volatile int16_t yaw;
    volatile int16_t rollTarget;
    volatile int16_t pitchTarget;
    volatile int16_t yawTarget;
    volatile int16_t motor1;
    volatile int16_t motor2;
    volatile int16_t motor3;
    volatile int16_t motor4;
};

float graphTime = 0;
int uartfd; 
struct dyGraph* graph;

void graphPacket (struct fcu_pkt_t * packet, float time);
guint readSerial (void);

int main (int argc, char **argv)
{	
	if (argc != 2) {
		printf ("Usage: graph <serial port device (ex /dev/ttyUSB0)\n>");
		exit(-1);
	} 

	uartfd = initUART(argv[1]);
	
	//******************* Set up GTK window **********************
	
	GtkWidget *windowRawAccelerometer;
	GtkWidget *windowRawGyro;
	GtkWidget *windowOrientation;
	GtkWidget *windowPid;
	
	gtk_init (&argc, &argv);
	
	windowRawAccelerometer = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	windowRawGyro = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	windowOrientation = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	windowPid = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_title (GTK_WINDOW(windowRawAccelerometer), "Falcon - Accelerometer");
	gtk_window_set_title (GTK_WINDOW(windowRawGyro), "Falcon - Gyroscopes");
	gtk_window_set_title (GTK_WINDOW(windowOrientation), "Falcon - Kalman Filter Output");
	gtk_window_set_title (GTK_WINDOW(windowPid), "Falcon - Kalman Filter Output");
	
	gtk_widget_show(windowRawAccelerometer);
	gtk_widget_show(windowRawGyro);
	gtk_widget_show(windowOrientation);
	gtk_widget_show(windowPid);
	
	//~ g_signal_connect (windowRawAccelerometer, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	//~ g_signal_connect (windowRawGyro, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	//~ g_signal_connect (windowOrientation, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	//~ 
    //~ g_signal_connect (G_OBJECT (windowRawAccelerometer), "delete_event", G_CALLBACK (gtk_main_quit), NULL);
    //~ g_signal_connect (G_OBJECT (windowRawGyro), "delete_event", G_CALLBACK (gtk_main_quit), NULL);
    //~ g_signal_connect (G_OBJECT (windowOrientation), "delete_event", G_CALLBACK (gtk_main_quit), NULL);
    
    //******************* Make dyGraphs **********************
    
    dyGraphRawAccelerometer = dyGraphInit ("Raw Accelerometer Readings", "", "Time", "", 100, -100, 100, DYGRAPH_SIMPLE, DYGRAPH_AUTO_PAN_X | DYGRAPH_AUTO_SCALE_Y );
    dyGraphRawGyro = dyGraphInit ("Raw Gyroscope Readings", "", "Time", "", 100, -100, 100, DYGRAPH_SIMPLE, DYGRAPH_AUTO_PAN_X | DYGRAPH_AUTO_SCALE_Y);
    dyGraphOrientation = dyGraphInit ("Orientation Estimate", "", "Time", "", 100, -100, 100, DYGRAPH_SIMPLE, DYGRAPH_AUTO_PAN_X | DYGRAPH_AUTO_SCALE_Y);
    dyGraphPid = dyGraphInit ("PID Feedback Control", "", "Time", "", 100, -100, 100, DYGRAPH_SIMPLE, DYGRAPH_AUTO_PAN_X | DYGRAPH_AUTO_SCALE_Y);
	
	gtk_container_add(GTK_CONTAINER(windowRawAccelerometer), (GtkWidget*)dyGraphRawAccelerometer->table); // add the graph to the window
	gtk_container_add(GTK_CONTAINER(windowRawGyro), (GtkWidget*)dyGraphRawGyro->table); // add the graph to the window
	gtk_container_add(GTK_CONTAINER(windowOrientation), (GtkWidget*)dyGraphOrientation->table); // add the graph to the window
	gtk_container_add(GTK_CONTAINER(windowPid), (GtkWidget*)dyGraphPid->table); // add the graph to the window
	
    gtk_widget_show(dyGraphRawAccelerometer->table);
    gtk_widget_show(dyGraphRawGyro->table);
    gtk_widget_show(dyGraphOrientation->table);
    gtk_widget_show(dyGraphPid->table);
    
    //******************** Add Traces **********************
    
    acclXTrace = dyGraphAddTrace (dyGraphRawAccelerometer, SOLID, 2, BLUE, "Accel X");
    acclYTrace = dyGraphAddTrace (dyGraphRawAccelerometer, SOLID, 2, GREEN, "Accel Y");
    acclZTrace = dyGraphAddTrace (dyGraphRawAccelerometer, SOLID, 2, RED, "Accel Z");
    
    gyroXTrace = dyGraphAddTrace (dyGraphRawGyro, SOLID, 2, BLUE, "Gyro X");
    gyroYTrace = dyGraphAddTrace (dyGraphRawGyro, SOLID, 2, GREEN, "Gyro Y");
    gyroZTrace = dyGraphAddTrace (dyGraphRawGyro, SOLID, 2, RED, "Gyro Z");
    
    eulerRollTrace = dyGraphAddTrace (dyGraphOrientation, SOLID, 2, BLUE, "Roll");
    eulerPitchTrace = dyGraphAddTrace (dyGraphOrientation, SOLID, 2, GREEN, "Pitch");
    eulerYawTrace = dyGraphAddTrace (dyGraphOrientation, SOLID, 2, RED, "Yaw");
    
    pidRollTrace = dyGraphAddTrace (dyGraphPid, SOLID, 2, BLUE, "Roll");
    pidPitchTrace = dyGraphAddTrace (dyGraphPid, SOLID, 2, GREEN, "Pitch");
    pidYawTrace = dyGraphAddTrace (dyGraphPid, SOLID, 2, RED, "Yaw");
    
    pidRollTargetTrace = dyGraphAddTrace (dyGraphPid, DOTTED, 2, BLUE, "Roll Target");
    pidPitchTargetTrace = dyGraphAddTrace (dyGraphPid, DOTTED, 2, GREEN, "Pitch Target");
    pidYawTargetTrace = dyGraphAddTrace (dyGraphPid, DOTTED, 2, RED, "Yaw Target");
    
    motor1Trace = dyGraphAddTrace (dyGraphPid, DOTTED, 2, BLACK, "Roll Target");
    motor2Trace = dyGraphAddTrace (dyGraphPid, DOTTED, 2, BLACK, "Pitch Target");
    motor3Trace = dyGraphAddTrace (dyGraphPid, DOTTED, 2, BLACK, "Yaw Target");
    motor4Trace = dyGraphAddTrace (dyGraphPid, DOTTED, 2, BLACK, "Yaw Target");
    
    //******************* Add timeout to add more data to traces **********************
    
	acclXTrace = acclXTrace;
	acclYTrace = acclYTrace;
	acclZTrace = acclZTrace;

	gyroXTrace = gyroXTrace;
	gyroYTrace = gyroYTrace;
	gyroZTrace = gyroZTrace;

	eulerRollTrace = eulerRollTrace;
	eulerPitchTrace = eulerPitchTrace;
	eulerYawTrace = eulerYawTrace;

	pidRollTrace = pidRollTrace;
	pidPitchTrace = pidPitchTrace;
	pidYawTrace = pidYawTrace;

	pidRollTargetTrace = pidRollTargetTrace;
	pidPitchTargetTrace = pidPitchTargetTrace;
	pidYawTargetTrace = pidYawTargetTrace;

	motor1Trace = motor1Trace;
	motor2Trace = motor2Trace;
	motor3Trace = motor3Trace;
	motor4Trace = motor4Trace;

	dyGraphRawAccelerometer = dyGraphRawAccelerometer;
	dyGraphRawGyro = dyGraphRawGyro;
	dyGraphOrientation = dyGraphOrientation;
	dyGraphPid = dyGraphPid;

    //~ g_timeout_add (100, (GSourceFunc) testUpdate, NULL);    
    g_timeout_add(1, (GSourceFunc) readSerial, NULL);   
    
    //******************* GTK main **********************
    
    gtk_main ();

	return 0;
}

// testUpdate is called every time the testTimer timeout is triggered (every 500mS currently)
static gint testUpdate (void) 
{
	dyGraphAddData(dyGraphRawAccelerometer, acclXTrace, (float)(acclXTrace->dataCurr), (90.)*sin((float)(acclXTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphRawAccelerometer, acclYTrace, (float)(acclYTrace->dataCurr), (60.)*sin((float)(acclYTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphRawAccelerometer, acclZTrace, (float)(acclZTrace->dataCurr), (30.)*sin((float)(acclZTrace->dataCurr/10.)) );
    
	dyGraphAddData(dyGraphRawGyro, gyroXTrace, (float)(gyroXTrace->dataCurr), (90.)*sin((float)(gyroXTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphRawGyro, gyroYTrace, (float)(gyroYTrace->dataCurr), (60.)*sin((float)(gyroYTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphRawGyro, gyroZTrace, (float)(gyroZTrace->dataCurr), (30.)*sin((float)(gyroZTrace->dataCurr/10.)) );

	dyGraphAddData(dyGraphOrientation, eulerRollTrace, (float)(eulerRollTrace->dataCurr), (90.)*sin((float)(eulerRollTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphOrientation, eulerPitchTrace, (float)(eulerPitchTrace->dataCurr), (60.)*sin((float)(eulerPitchTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphOrientation, eulerYawTrace, (float)(eulerYawTrace->dataCurr), (30.)*sin((float)(eulerYawTrace->dataCurr/10.)) );	

	dyGraphAddData(dyGraphPid, pidRollTrace, (float)(pidRollTrace->dataCurr), (90.)*sin((float)(pidRollTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphPid, pidPitchTrace, (float)(pidPitchTrace->dataCurr), (60.)*sin((float)(pidPitchTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphPid, pidYawTrace, (float)(pidYawTrace->dataCurr), (30.)*sin((float)(pidYawTrace->dataCurr/10.)) );	
	dyGraphAddData(dyGraphPid, pidRollTargetTrace, (float)(pidRollTargetTrace->dataCurr), (90.)*sin((float)(pidRollTargetTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphPid, pidPitchTargetTrace, (float)(pidPitchTargetTrace->dataCurr), (60.)*sin((float)(pidPitchTargetTrace->dataCurr/10.)) );
	dyGraphAddData(dyGraphPid, pidYawTargetTrace, (float)(pidYawTargetTrace->dataCurr), (30.)*sin((float)(pidYawTargetTrace->dataCurr/10.)) );	
	dyGraphAddData(dyGraphPid, motor1Trace, (float)(motor1Trace->dataCurr), (90.)*sin((float)(motor1Trace->dataCurr/10.)) );
	dyGraphAddData(dyGraphPid, motor2Trace, (float)(motor2Trace->dataCurr), (60.)*sin((float)(motor2Trace->dataCurr/10.)) );
	dyGraphAddData(dyGraphPid, motor3Trace, (float)(motor3Trace->dataCurr), (30.)*sin((float)(motor3Trace->dataCurr/10.)) );	
	dyGraphAddData(dyGraphPid, motor4Trace, (float)(motor4Trace->dataCurr), (30.)*sin((float)(motor4Trace->dataCurr/10.)) );	
	
	return TRUE; // return true to continue timeout
}

void graphPacket (struct fcu_pkt_t * packet, float time) {
    
	dyGraphAddData(dyGraphRawAccelerometer, acclXTrace, time, (float)(packet->x_accel) );
	dyGraphAddData(dyGraphRawAccelerometer, acclYTrace, time, (float)(packet->y_accel) );
	dyGraphAddData(dyGraphRawAccelerometer, acclZTrace, time, (float)(packet->z_accel) );
    
	dyGraphAddData(dyGraphRawGyro, gyroXTrace, time, (float)(packet->x_gyro) );
	dyGraphAddData(dyGraphRawGyro, gyroYTrace, time, (float)(packet->y_gyro) );
	dyGraphAddData(dyGraphRawGyro, gyroZTrace, time, (float)(packet->z_gyro) );

	dyGraphAddData(dyGraphOrientation, eulerRollTrace, time, (float)(packet->roll) );
	dyGraphAddData(dyGraphOrientation, eulerPitchTrace, time, (float)(packet->pitch) );
	dyGraphAddData(dyGraphOrientation, eulerYawTrace, time, (float)(packet->yaw) );

	dyGraphAddData(dyGraphPid, pidRollTrace, time, (float)(packet->roll) );
	dyGraphAddData(dyGraphPid, pidPitchTrace, time, (float)(packet->pitch) );
	dyGraphAddData(dyGraphPid, pidYawTrace, time, (float)(packet->yaw) );
	dyGraphAddData(dyGraphPid, pidRollTargetTrace, time, (float)(packet->rollTarget) );
	dyGraphAddData(dyGraphPid, pidPitchTargetTrace, time, (float)(packet->pitchTarget) );
	dyGraphAddData(dyGraphPid, pidYawTargetTrace, time, (float)(packet->yawTarget) );
	dyGraphAddData(dyGraphPid, motor1Trace, time, (float)(packet->motor1) );
	dyGraphAddData(dyGraphPid, motor2Trace, time, (float)(packet->motor2) );
	dyGraphAddData(dyGraphPid, motor3Trace, time, (float)(packet->motor3) );
	dyGraphAddData(dyGraphPid, motor4Trace, time, (float)(packet->motor4) );

	printf ("%d\t%d\t%d\n", packet->x_accel, packet->y_accel, packet->z_accel);
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
			while (j<sizeof(struct fcu_pkt_t)) {
				int dataBytesRead = read (uartfd, rxBuffer+j, RX_BUFFER_LENGTH-j-1);
				j += dataBytesRead;
				usleep(100);
			}
			graphTime += 1;
			graphPacket ((struct fcu_pkt_t*)rxBuffer, graphTime);
			//~ printf ("packet\n");
			break;
		}
	}
	return TRUE;
}
