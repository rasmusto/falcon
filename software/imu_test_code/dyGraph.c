#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>

#include <sys/stat.h>
#include <sys/unistd.h>

#include <errno.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

#include <gtk/gtk.h>
#include <glib-object.h>
#include "gtkgraph.h"
#include "dyGraph.h"

#define INITIAL_TRACE_DATA_LENGTH 10000
#define MAX_TRACE_DATA_LENGTH 10000000
#define MAX_TRACE_GRAPH_LENGTH 1000

static void traceEnableToggleCB (GtkToggleButton* checkBox, struct handlerData* data);
static void globalEnableToggleCB (GtkToggleButton* checkBox, struct dyGraph* graphInfo);
static gint scrollWheelCB (GtkWidget *widget, GdkEventScroll *event, struct dyGraph* graphInfo);
void findZoomedLimits (float axisMin, float axisMax, int value, int minPix, int maxPix, float ZoomFactor, float* min, float* max);
static gint buttonPressCB (GtkWidget *widget, GdkEventButton *event, struct dyGraph* graphInfo);
static gint buttonReleaseCB (GtkWidget *widget, GdkEventButton *event, struct dyGraph* graphInfo);
static gint pointerMotionCB (GtkWidget *widget, GdkEventMotion *event, struct dyGraph* graphInfo);
static void scaleXToggleCB (GtkToggleButton* toggleButton, struct dyGraph* graphInfo);
static void scaleYToggleCB (GtkToggleButton* toggleButton, struct dyGraph* graphInfo);
static void panXToggleCB (GtkToggleButton* toggleButton, struct dyGraph* graphInfo);

void dyGraphRedrawAll (struct dyGraph * graphInfo);
void dyGraphRedrawTrace (struct dyGraph* graphInfo, struct dyTrace* trace);

struct dyGraph * dyGraphInit (char* title, char* subTitle, char* xLabel, char* yLabel, float xMax, float yMin, float yMax) {
	
	struct dyGraph * graphInfo = malloc(sizeof(struct dyGraph));
	
	graphInfo->xZoomFactor = 1.2;
	graphInfo->yZoomFactor = 1.2;
	

	//******************* Enable Trace Checkboxes **********************
	
	// make a vbox to put enable trace checkboxes in.  individual trace checkboxes will be added after init function
	GtkWidget* enableBox = gtk_vbox_new (FALSE, 3);	
	
	
	// add enable toggle
	
	GtkWidget* globalEnableToggle = gtk_toggle_button_new_with_label ("Global Enable");
	gtk_toggle_button_set_active ((GtkToggleButton*)globalEnableToggle, TRUE);
	GtkWidget* globalEnableToggleAlign = gtk_alignment_new (0,1,1,0); // align left, bottom   y - dont fill, x - dont fill
	gtk_container_add(GTK_CONTAINER(globalEnableToggleAlign), globalEnableToggle); // add checkbox to the align container
	g_signal_connect (globalEnableToggle, "toggled", G_CALLBACK (globalEnableToggleCB), graphInfo);
	
	gtk_box_pack_start ((GtkBox*)enableBox, globalEnableToggleAlign, FALSE, FALSE, 0);
	
	gtk_widget_show_all (globalEnableToggleAlign);
	
	// add autoScale Y toggle
	
	GtkWidget* scaleYToggle = gtk_toggle_button_new_with_label ("Auto Scale Y");
	gtk_toggle_button_set_active ((GtkToggleButton*)scaleYToggle, TRUE);
	GtkWidget* scaleYToggleAlign = gtk_alignment_new (0,1,1,0); // align left, bottom   y - dont fill, x - dont fill
	//~ gtk_alignment_set_padding ((GtkAlignment*)scaleYToggleAlign, 0, 10, 0, 0);
	gtk_container_add(GTK_CONTAINER(scaleYToggleAlign), scaleYToggle); // add checkbox to the align container
	g_signal_connect (scaleYToggle, "toggled", G_CALLBACK (scaleYToggleCB), graphInfo);
	
	gtk_box_pack_start ((GtkBox*)enableBox, scaleYToggleAlign, FALSE, FALSE, 0);
	
	gtk_widget_show_all (scaleYToggleAlign);	
	
	// add autoScale X toggle
	
	GtkWidget* scaleXToggle = gtk_toggle_button_new_with_label ("Auto Scale X");
	gtk_toggle_button_set_active ((GtkToggleButton*)scaleXToggle, TRUE);
	GtkWidget* scaleXToggleAlign = gtk_alignment_new (0,1,1,0); // align left, bottom   y - dont fill, x - dont fill
	gtk_container_add(GTK_CONTAINER(scaleXToggleAlign), scaleXToggle); // add checkbox to the align container
	g_signal_connect (scaleXToggle, "toggled", G_CALLBACK (scaleXToggleCB), graphInfo);
	
	gtk_box_pack_start ((GtkBox*)enableBox, scaleXToggleAlign, FALSE, FALSE, 0);
	
	gtk_widget_show_all (scaleXToggleAlign);
	
	// add autoPan X toggle
	
	GtkWidget* panXToggle = gtk_toggle_button_new_with_label ("Auto Pan X");
	gtk_toggle_button_set_active ((GtkToggleButton*)panXToggle, TRUE);
	GtkWidget* panXToggleAlign = gtk_alignment_new (0,1,1,0); // align left, bottom   y - dont fill, x - dont fill
	gtk_alignment_set_padding ((GtkAlignment*)panXToggleAlign, 0, 10, 0, 0);
	gtk_container_add(GTK_CONTAINER(panXToggleAlign), panXToggle); // add checkbox to the align container
	g_signal_connect (panXToggle, "toggled", G_CALLBACK (panXToggleCB), graphInfo);
	
	gtk_box_pack_start ((GtkBox*)enableBox, panXToggleAlign, FALSE, FALSE, 0);
	
	gtk_widget_show_all (panXToggleAlign);
	
	//******************* The Graph *********************
	
	GtkGraph* graph = (GtkGraph*)gtk_graph_new (XY);
	graph->legend_visible = FALSE;
	gtk_signal_connect (GTK_OBJECT (&graph->drawing_area), "motion_notify_event", (GtkSignalFunc) pointerMotionCB, graphInfo);
	gtk_signal_connect (GTK_OBJECT (&graph->drawing_area), "button_press_event", (GtkSignalFunc) buttonPressCB, graphInfo);
	gtk_signal_connect (GTK_OBJECT (&graph->drawing_area), "button_release_event", (GtkSignalFunc) buttonReleaseCB, graphInfo);
	gtk_signal_connect (GTK_OBJECT (&graph->drawing_area), "scroll_event", (GtkSignalFunc) scrollWheelCB, graphInfo);
	gtk_widget_set_events ((GtkWidget*)graph, GDK_BUTTON1_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
	gchar graphTitle[30];
	strcpy(graphTitle, title);
	gchar graphSubTitle[30];
	strcpy(graphSubTitle, subTitle);
	gtk_graph_set_title (graph, graphTitle, graphSubTitle);	
	
	GtkWidget* graphAlign = gtk_alignment_new (1,1,1,1); // fill everything
	gtk_container_add(GTK_CONTAINER(graphAlign), (GtkWidget*)graph); // add graph to the align container
	gtk_alignment_set_padding ((GtkAlignment*)graphAlign, 1, 0, 0, 0);	
	//******************* Axis *********************
	
	gtk_graph_axis_format(graph, GTK_GRAPH_AXIS_DEPENDANT, FLOATING_POINT, 2, yLabel);
	gtk_graph_axis_format(graph, GTK_GRAPH_AXIS_INDEPENDANT, FLOATING_POINT, 2, xLabel);

	gtk_graph_axis_set_limits (graph, GTK_GRAPH_AXIS_INDEPENDANT, xMax, 0);
	gtk_graph_axis_set_limits (graph, GTK_GRAPH_AXIS_DEPENDANT, yMax, yMin);
	gtk_graph_axis_format_grid (graph, GTK_GRAPH_AXIS_INDEPENDANT, TRUE);
	gtk_graph_axis_format_grid (graph, GTK_GRAPH_AXIS_DEPENDANT, TRUE);
	
	
	//******************* Traces *********************
	
	// traces added later
	
	//******************* Table that holds everything **********************
	
	GtkWidget* graphTable = gtk_table_new(1, 2, FALSE);
	
	// add all of the widgets to the table 
	gtk_table_attach((GtkTable*)graphTable, (GtkWidget*)enableBox, 0, 1, 0, 1, GTK_SHRINK, GTK_FILL, 5, 5);
	gtk_table_attach((GtkTable*)graphTable, (GtkWidget*)graphAlign, 1, 2, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 5, 5);
	
	gtk_widget_show_all (graphTable); // show everything in table
	
	graphInfo->table = graphTable;
	graphInfo->graph = graph;
	graphInfo->enableBox = enableBox;
	
	graphInfo->globalEnable = 1;
	graphInfo->autoScaleX = 1;
	graphInfo->autoScaleY = 1;
	graphInfo->autoPanX = 1;
	
	graphInfo->xDataMax = 0;
	graphInfo->xDataMin = 0;
	graphInfo->yDataMax = 0;
	graphInfo->yDataMin = 0;

	graphInfo->traces = (struct dyTrace**)malloc(sizeof(struct dyTrace*)*256);
	graphInfo->traceCount = 0;
	
	return graphInfo;
}

struct dyTrace * dyGraphAddTrace (struct dyGraph * graphInfo, GtkGraphLineType type, gint width, GdkColor line_color, char * name) {

//******************* Stuff to do after initialization **********************
	
	// add trace
	
	gint trace = gtk_graph_trace_new(graphInfo->graph);

	gtk_graph_trace_format_line(graphInfo->graph, trace, type, width, &line_color, TRUE);
	gtk_graph_trace_format_title(graphInfo->graph, trace, name);	
	
	// add enable checkbox
	
	int satVal = 20000;
	
	if (line_color.red < (65535-satVal))
		line_color.red = line_color.red + satVal;
	else
		line_color.red = 65535;
		
	if (line_color.green < (65535-satVal))
		line_color.green = line_color.green + satVal;
	else
		line_color.green = 65535;
		
	if (line_color.blue < (65535-satVal))
		line_color.blue = line_color.blue + satVal;
	else
		line_color.blue = 65535;

	line_color.pixel = ((uint32_t)(line_color.red/256)<<16) + ((uint32_t)(line_color.green/256)<<8) + ((uint32_t)(line_color.blue/256));
	
	GdkColor line_color_inact;
	
	satVal = 30000;
	
	if (line_color.red < (65535-satVal))
		line_color_inact.red = line_color.red + satVal;
	else
		line_color_inact.red = 65535;
		
	if (line_color.green < (65535-satVal))
		line_color_inact.green = line_color.green + satVal;
	else
		line_color_inact.green = 65535;
		
	if (line_color.blue < (65535-satVal))
		line_color_inact.blue = line_color.blue + satVal;
	else
		line_color_inact.blue = 65535;

	line_color_inact.pixel = ((uint32_t)(line_color_inact.red/256)<<16) + ((uint32_t)(line_color_inact.green/256)<<8) + ((uint32_t)(line_color_inact.blue/256));
	
	char buttonText[256];
	
	if (type == DASHED)
		sprintf(buttonText, "-- %s --", name);
	else if (type == DOTTED)
		sprintf(buttonText, ".. %s ..", name);
	else if (type == DASH_DOT)
		sprintf(buttonText, "-. %s -.", name);
	else
		sprintf(buttonText, "%s", name);
	
	GtkWidget* enableToggle = gtk_toggle_button_new_with_label (buttonText);
	gtk_toggle_button_set_active ((GtkToggleButton*)enableToggle, TRUE);

	gtk_widget_modify_bg(enableToggle, GTK_STATE_NORMAL, &line_color_inact);
	gtk_widget_modify_bg(enableToggle, GTK_STATE_ACTIVE, &line_color);
	gtk_widget_modify_bg(enableToggle, GTK_STATE_PRELIGHT, &line_color_inact);
	gtk_widget_modify_bg(enableToggle, GTK_STATE_SELECTED, &line_color_inact);
	gtk_widget_modify_bg(enableToggle, GTK_STATE_INSENSITIVE, &line_color_inact);


	// align container for enableACheck
	GtkWidget* enableToggleAlign = gtk_alignment_new (0,0,1,0); // align left, top   y - dont fill, x - dont fill
	gtk_container_add(GTK_CONTAINER(enableToggleAlign), enableToggle); // add hZoomScale to the align container
	
	gtk_box_pack_start ((GtkBox*)graphInfo->enableBox, enableToggleAlign, FALSE, FALSE, 0);

	gtk_widget_show_all (graphInfo->enableBox); // show everything we just added to enableBox
	
	// make trace struct

	graphInfo->traces[graphInfo->traceCount] = (struct dyTrace*)malloc(sizeof(struct dyTrace));
	
	graphInfo->traces[graphInfo->traceCount]->trace = trace;
	graphInfo->traces[graphInfo->traceCount]->name = name;
	graphInfo->traces[graphInfo->traceCount]->enableToggle = enableToggle;
	graphInfo->traces[graphInfo->traceCount]->enableToggleAlign = enableToggleAlign;
	graphInfo->traces[graphInfo->traceCount]->xData = (float*)malloc(sizeof(float)*INITIAL_TRACE_DATA_LENGTH);
	graphInfo->traces[graphInfo->traceCount]->yData = (float*)malloc(sizeof(float)*INITIAL_TRACE_DATA_LENGTH);
	graphInfo->traces[graphInfo->traceCount]->dataLength = INITIAL_TRACE_DATA_LENGTH;
	graphInfo->traces[graphInfo->traceCount]->dataCurr = 0;
	
	graphInfo->traces[graphInfo->traceCount]->xDataMax = 0;
	graphInfo->traces[graphInfo->traceCount]->xDataMin = 0;
	graphInfo->traces[graphInfo->traceCount]->yDataMax = 0;
	graphInfo->traces[graphInfo->traceCount]->yDataMin = 0;
	
	graphInfo->traces[graphInfo->traceCount]->enabled = 1;	
	
	// set up handler for enable checkbox
	struct handlerData* data = malloc(sizeof(struct handlerData));
	data->graphInfo = graphInfo;
	data->trace = graphInfo->traces[graphInfo->traceCount];
	g_signal_connect (enableToggle, "toggled", G_CALLBACK (traceEnableToggleCB), data);
	
	if (graphInfo->traceCount <255) {
		return graphInfo->traces[graphInfo->traceCount];
		graphInfo->traceCount++;
	}
	else {
		perror("\n***** DYGRAPH ERROR: Too many traces\n\n");
		return 0;
	}
}

void dyGraphAddData (struct dyGraph * graphInfo, struct dyTrace * trace, float x, float y) {
	
	if (trace->dataCurr > MAX_TRACE_DATA_LENGTH) {
		perror("\n***** DYGRAPH ERROR: Too many data points\n\n");
		return;
	}
	
	// keep track of min and max data in x and y
	if (x > trace->xDataMax) {
		trace->xDataMax = x;
		if (x > graphInfo->xDataMax) {
			float oldXDataMax = graphInfo->xDataMax;
			float oldXDataMin = graphInfo->xDataMin;
			graphInfo->xDataMax = x;
			if (graphInfo->globalEnable && trace->enabled && graphInfo->autoPanX)
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, graphInfo->xDataMax, graphInfo->xDataMax - (graphInfo->graph->independant->axis_max - graphInfo->graph->independant->axis_min));
			else if (graphInfo->globalEnable && trace->enabled && graphInfo->autoScaleX)
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, graphInfo->xDataMax, graphInfo->xDataMin);
		}
	}
	
	if (x < trace->xDataMin) {
		trace->xDataMin = x;
		if (x < graphInfo->xDataMin) {
			graphInfo->xDataMin = x;
			if (graphInfo->globalEnable && trace->enabled && graphInfo->autoScaleX  && !graphInfo->autoPanX)
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, graphInfo->xDataMax, graphInfo->xDataMin);
		}
	}

	if (y > trace->yDataMax) {
		trace->yDataMax = y;
		if (y > graphInfo->yDataMax) {
			graphInfo->yDataMax = y;
			float oldYDataMax = graphInfo->yDataMax;
			float oldYDataMin = graphInfo->yDataMin;
			if (graphInfo->globalEnable && trace->enabled && graphInfo->autoScaleY)
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, graphInfo->yDataMax, graphInfo->yDataMin);
		}
	}
		
	if (y < trace->yDataMin) {
		trace->yDataMin = y;
		if (y < graphInfo->yDataMin) {
			graphInfo->yDataMin = y;
			if (graphInfo->globalEnable && trace->enabled && graphInfo->autoScaleY)
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, graphInfo->yDataMax, graphInfo->yDataMin);
		}
	}
	
	// dynamic array basically - grow by factor of 2 if too small
	if (trace->dataCurr < trace->dataLength) {
		trace->xData[trace->dataCurr] = x;
		trace->yData[trace->dataCurr] = y;
		trace->dataCurr++;
	} else {
		trace->dataLength = trace->dataLength*2;
		trace->xData = realloc(trace->xData, trace->dataLength);
		
		trace->xData[trace->dataCurr] = x;
		trace->yData[trace->dataCurr] = y;
		trace->dataCurr++;
	}
	
	if (graphInfo->globalEnable && trace->enabled)
		dyGraphRedrawTrace (graphInfo, trace);
}

// does not reload data from xData and yData
void dyGraphRedrawAll (struct dyGraph* graphInfo) {
	gtk_graph_redraw_all((GtkWidget*)graphInfo->graph);
}

// reloads data from xData and yData
void dyGraphRedrawTrace (struct dyGraph* graphInfo, struct dyTrace* trace) {
	gtk_graph_trace_set_data(graphInfo->graph, trace->trace, trace->xData, trace->yData, trace->dataCurr);
	gtk_graph_redraw_all((GtkWidget*)graphInfo->graph);
}

//this will have to serve for all trace enable checkboxes
static void traceEnableToggleCB (GtkToggleButton* toggleButton, struct handlerData* data) {
	data->trace->enabled = gtk_toggle_button_get_active (toggleButton);
	dyGraphRedrawAll(data->graphInfo);
}

static void globalEnableToggleCB (GtkToggleButton* toggleButton, struct dyGraph* graphInfo) {
	graphInfo->globalEnable = gtk_toggle_button_get_active (toggleButton);
	gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, graphInfo->yDataMax, graphInfo->yDataMin);
	dyGraphRedrawAll(graphInfo);
}

static void scaleXToggleCB (GtkToggleButton* toggleButton, struct dyGraph* graphInfo) {
	graphInfo->autoScaleX = gtk_toggle_button_get_active (toggleButton);
	gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, graphInfo->xDataMax, graphInfo->xDataMin);
	dyGraphRedrawAll(graphInfo);
}

static void scaleYToggleCB (GtkToggleButton* toggleButton, struct dyGraph* graphInfo) {
	graphInfo->autoScaleY = gtk_toggle_button_get_active (toggleButton);
	gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, graphInfo->yDataMax, graphInfo->yDataMin);
	dyGraphRedrawAll(graphInfo);
}

static void panXToggleCB (GtkToggleButton* toggleButton, struct dyGraph* graphInfo) {
	graphInfo->autoPanX = gtk_toggle_button_get_active (toggleButton);
}

static gint buttonPressCB (GtkWidget *widget, GdkEventButton *event, struct dyGraph* graphInfo) {
	if (event->button == 1) {
		graphInfo->translateOriginX = event->x;
		graphInfo->translateOriginY = event->y;
		
		graphInfo->translateOrigionalMinX = graphInfo->graph->independant->axis_min;
		graphInfo->translateOrigionalMaxX = graphInfo->graph->independant->axis_max;
		
		graphInfo->translateOrigionalMinY = graphInfo->graph->dependant->axis_min;
		graphInfo->translateOrigionalMaxY = graphInfo->graph->dependant->axis_max;
	}
	return TRUE;
}

static gint buttonReleaseCB (GtkWidget *widget, GdkEventButton *event, struct dyGraph* graphInfo) {
	if (event->button == 1) {
		//~ translateOriginX = event->x;
		//~ translateOriginY = event->y;		
	}
	return TRUE;
}

static gint pointerMotionCB (GtkWidget *widget, GdkEventMotion *event, struct dyGraph* graphInfo) {
	int x = event->x;
	int y = event->y;	
	int minXPix = graphInfo->graph->user_origin_x;
	int minYPix = graphInfo->graph->user_origin_y;
	int maxXPix = minXPix + graphInfo->graph->user_width;
	int maxYPix = minYPix + graphInfo->graph->user_height;
	
	if (!graphInfo->autoScaleX || !graphInfo->globalEnable || graphInfo->autoPanX) {
		float xNumsPerPixel = (graphInfo->graph->independant->axis_max - graphInfo->graph->independant->axis_min) / (maxXPix - minXPix);
		float newXMin = graphInfo->translateOrigionalMinX - (x - graphInfo->translateOriginX)*xNumsPerPixel;
		float newXMax = graphInfo->translateOrigionalMaxX - (x - graphInfo->translateOriginX)*xNumsPerPixel;
		gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, newXMax, newXMin);
	}
	
	if (!graphInfo->autoScaleY || !graphInfo->globalEnable) {
		float yNumsPerPixel = (graphInfo->graph->dependant->axis_max - graphInfo->graph->dependant->axis_min) / (maxYPix - minYPix);		
		float newYMin = graphInfo->translateOrigionalMinY + (y - graphInfo->translateOriginY)*yNumsPerPixel;
		float newYMax = graphInfo->translateOrigionalMaxY + (y - graphInfo->translateOriginY)*yNumsPerPixel;
		gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, newYMax, newYMin);
	}
	
	if (!graphInfo->autoScaleX || !graphInfo->autoScaleY || !graphInfo->globalEnable || graphInfo->autoPanX)
		dyGraphRedrawAll(graphInfo);
		
	return TRUE;	
}

static gint scrollWheelCB (GtkWidget *widget, GdkEventScroll *event, struct dyGraph* graphInfo) {
	int x = event->x;
	int y = event->y;
	int minXPix = graphInfo->graph->user_origin_x;
	int minYPix = graphInfo->graph->user_origin_y;
	int maxXPix = minXPix + graphInfo->graph->user_width;
	int maxYPix = minYPix + graphInfo->graph->user_height;
	if (y > minYPix && y < maxYPix && x > minXPix && x < maxXPix) {
		if (event->direction == GDK_SCROLL_UP) {
			if ((event->state & GDK_SHIFT_MASK) && (!graphInfo->autoScaleX || !graphInfo->globalEnable || graphInfo->autoPanX)) {
				// Zoom in x axis
				float min, max;
				findZoomedLimits (graphInfo->graph->independant->axis_min, graphInfo->graph->independant->axis_max, x, minXPix, maxXPix, graphInfo->xZoomFactor, &min, &max);				
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, max, min);
				dyGraphRedrawAll(graphInfo);
			} else if ((event->state & GDK_CONTROL_MASK) && (!graphInfo->autoScaleY || !graphInfo->globalEnable)) {
				// zoom in y axis
				float min, max;
				findZoomedLimits (graphInfo->graph->dependant->axis_min, graphInfo->graph->dependant->axis_max, maxYPix-y+minYPix, minYPix, maxYPix, graphInfo->yZoomFactor, &min, &max);				
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, max, min);
				dyGraphRedrawAll(graphInfo);
			} else {
				// Zoom in x and y axis
				float min, max;
				if (!graphInfo->autoScaleX || !graphInfo->globalEnable || graphInfo->autoPanX) {
					findZoomedLimits (graphInfo->graph->independant->axis_min, graphInfo->graph->independant->axis_max, x, minXPix, maxXPix, graphInfo->xZoomFactor, &min, &max);				
					gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, max, min);
					dyGraphRedrawAll(graphInfo);
				}
				if (!graphInfo->autoScaleY || !graphInfo->globalEnable) {
					findZoomedLimits (graphInfo->graph->dependant->axis_min, graphInfo->graph->dependant->axis_max, maxYPix-y+minYPix, minYPix, maxYPix, graphInfo->yZoomFactor, &min, &max);				
					gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, max, min);
					dyGraphRedrawAll(graphInfo);
				}
			}
		} else if (event->direction == GDK_SCROLL_DOWN) {
			if ((event->state & GDK_SHIFT_MASK) && (!graphInfo->autoScaleX || !graphInfo->globalEnable || graphInfo->autoPanX)) {
				// Zoom out x axis
				float min, max;
				findZoomedLimits (graphInfo->graph->independant->axis_min, graphInfo->graph->independant->axis_max, x, minXPix, maxXPix, 1/graphInfo->xZoomFactor, &min, &max);				
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, max, min);
				dyGraphRedrawAll(graphInfo);
			} else if ((event->state & GDK_CONTROL_MASK) && (!graphInfo->autoScaleY || !graphInfo->globalEnable)) {
				// Zoom out y axis
				float min, max;
				findZoomedLimits (graphInfo->graph->dependant->axis_min, graphInfo->graph->dependant->axis_max, maxYPix-y+minYPix, minYPix, maxYPix, 1/graphInfo->yZoomFactor, &min, &max);				
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, max, min);
				dyGraphRedrawAll(graphInfo);
			} else {
				// Zoom out x and y axis
				float min, max;
				if (!graphInfo->autoScaleX || !graphInfo->globalEnable || graphInfo->autoPanX) {
					findZoomedLimits (graphInfo->graph->independant->axis_min, graphInfo->graph->independant->axis_max, x, minXPix, maxXPix, 1/graphInfo->xZoomFactor, &min, &max);				
					gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, max, min);
					dyGraphRedrawAll(graphInfo);
				} 
				if (!graphInfo->autoScaleY || !graphInfo->globalEnable) {
					findZoomedLimits (graphInfo->graph->dependant->axis_min, graphInfo->graph->dependant->axis_max, maxYPix-y+minYPix, minYPix, maxYPix, 1/graphInfo->yZoomFactor, &min, &max);				
					gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, max, min);
					dyGraphRedrawAll(graphInfo);
				}
			}
		}
	}
	
	return TRUE;
}

void findZoomedLimits (float axisMin, float axisMax, int value, int minPix, int maxPix, float zoomFactor, float* min, float* max) {
	float numsPerPixel = (axisMax - axisMin) / (maxPix - minPix);
	
	float newLeftPixels = (value - minPix) / zoomFactor;
	float newRightPixels = (maxPix - value) / zoomFactor;
	
	float newLeftNums = newLeftPixels * numsPerPixel;
	float newRightNums = newRightPixels * numsPerPixel;
	
	float pointerNum = axisMin + (value - minPix)*numsPerPixel;
	
	*max = pointerNum+newRightNums;
	*min = pointerNum-newLeftNums;
}
