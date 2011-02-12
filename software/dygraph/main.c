#include <stdint.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <math.h>
#include "gtkgraph.h"
#include "dyGraph.h"

struct testUpdateData {
	struct dyGraph* graphInfo;
	struct dyTrace* trace;
};

static gint testUpdate (struct testUpdateData* data);

int main (int argc, char **argv)
{	
	//******************* Set up GTK window **********************
	
	GtkWidget *window;
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Test Graph");
	
	gtk_widget_show(window);
	
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (gtk_main_quit), NULL);
    
    
    //******************* Make dyGraph **********************
    struct dyGraph * dyGraphInfo = dyGraphInit ("Title1", "Subtitle1", "xLab1", "yLab1", 100, -100, 100);
    
    //******************* Add table to the window and show everything **********************
	
	gtk_container_add(GTK_CONTAINER(window), (GtkWidget*)dyGraphInfo->table); // add the graph to the window
    gtk_widget_show(dyGraphInfo->table);
    
    struct dyTrace* redTrace = dyGraphAddTrace (dyGraphInfo, DASHED, 1, RED, "Red Trace");
    struct dyTrace* greenTrace = dyGraphAddTrace (dyGraphInfo, SOLID, 1, GREEN, "Green Trace");
    struct dyTrace* blueTrace = dyGraphAddTrace (dyGraphInfo, SOLID, 1, BLUE, "Blue Trace");
    struct dyTrace* blackTrace = dyGraphAddTrace (dyGraphInfo, SOLID, 1, BLACK, "Black Trace");
    
    
    //******************* Add data to traces **********************
    //~ 
    //~ dyGraphAddData(dyGraphInfo, redTrace, 1.23, 3.45);
    //~ dyGraphAddData(dyGraphInfo, redTrace, 2.34, 7.987);
    //~ dyGraphAddData(dyGraphInfo, redTrace, 1.2, 7);
    //~ dyGraphAddData(dyGraphInfo, redTrace, 5.53, 5);
    
    
    //******************* Add timeout to add more data to traces **********************
    
    struct testUpdateData* data = malloc(sizeof(struct testUpdateData));
    
    data->trace = redTrace;
    data->graphInfo = dyGraphInfo;
    
    guint testTimer = g_timeout_add (50, (GSourceFunc) testUpdate, data);
    
    
    //******************* GTK main **********************
    
    gtk_main ();

	return 0;
}

// testUpdate is called every time the testTimer timeout is triggered (every 500mS currently)
static gint testUpdate (struct testUpdateData* data) 
{
	struct dyGraph* graphInfo = data->graphInfo;
	struct dyTrace* trace = data->trace;
	dyGraphAddData(graphInfo, trace, (float)(trace->dataCurr), (100.)*sin((float)(trace->dataCurr/10.)) );
	return TRUE; // return true to continue timeout
}
