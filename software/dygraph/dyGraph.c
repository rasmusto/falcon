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

static void hZoomAdjustCB (GtkAdjustment* adjust, struct dyGraph* graphInfo);
static void vZoomAdjustCB (GtkAdjustment* adjust, struct dyGraph* graphInfo);
static void hScrollAdjustCB (GtkAdjustment* adjust, struct dyGraph* graphInfo);
static void vScrollAdjustCB (GtkAdjustment* adjust, struct dyGraph* graphInfo);
static void hMaxCheckCB (GtkToggleButton* checkBox, struct dyGraph* graphInfo);
static void vMaxCheckCB (GtkToggleButton* checkBox, struct dyGraph* graphInfo);
static void traceEnableToggleCB (GtkToggleButton* checkBox, struct handlerData* data);
static void globalEnableToggleCB (GtkToggleButton* checkBox, struct dyGraph* graphInfo);
static gint scrollWheelCB (GtkWidget *widget, GdkEventScroll *event, struct dyGraph* graphInfo);
void findZoomedLimits (float axisMin, float axisMax, int value, int minPix, int maxPix, float ZoomFactor, float* min, float* max);
static gint buttonPressCB (GtkWidget *widget, GdkEventButton *event, struct dyGraph* graphInfo);
static gint buttonReleaseCB (GtkWidget *widget, GdkEventButton *event, struct dyGraph* graphInfo);
static gint pointerMotionCB (GtkWidget *widget, GdkEventMotion *event, struct dyGraph* graphInfo);

void dyGraphRedrawAll (struct dyGraph * graphInfo);
void dyGraphRedrawTrace (struct dyGraph* graphInfo, struct dyTrace* trace);

struct dyGraph * dyGraphInit (char* title, char* subTitle, char* xLabel, char* yLabel, float xMax, float yMin, float yMax) {
	
	struct dyGraph * graphInfo = malloc(sizeof(struct dyGraph));
	
	graphInfo->xZoomFactor = 1.5;
	graphInfo->yZoomFactor = 1.5;
	
	//******************* Zoom Scales **********************
	
	float initialZoomMax = (abs(yMin)+abs(yMax))*300;
	GtkAdjustment* vZoomAdjust = (GtkAdjustment*)gtk_adjustment_new (initialZoomMax/3, 1., initialZoomMax, initialZoomMax/30, initialZoomMax/3, initialZoomMax/3);
	graphInfo->vZoom = abs(yMin)+abs(yMax);
	
	GtkWidget* vZoomScale = gtk_vscale_new(vZoomAdjust);
	// align container for vZoomScale
	GtkWidget* vZoomAlign = gtk_alignment_new (1,0,0,1); // align right, top   x - dont fill, y - fill full
	gtk_container_add(GTK_CONTAINER(vZoomAlign), vZoomScale); // add vZoomScale to the align container
	g_signal_connect (vZoomAdjust, "value-changed", G_CALLBACK (vZoomAdjustCB), graphInfo);
	
	float initialHZoomMax = abs(xMax)*300;
	GtkAdjustment* hZoomAdjust = (GtkAdjustment*)gtk_adjustment_new (initialHZoomMax/3, 0, initialHZoomMax, initialHZoomMax/30, initialHZoomMax/3, initialHZoomMax/3);
	graphInfo->hZoom = abs(xMax);
	
	GtkWidget* hZoomScale = gtk_hscale_new(hZoomAdjust);
	// align container for hZoomScale
	GtkWidget* hZoomAlign = gtk_alignment_new (0,1,1,0); // align left, bottom   y - dont fill, x - fill full
	gtk_container_add(GTK_CONTAINER(hZoomAlign), hZoomScale); // add hZoomScale to the align container
	g_signal_connect (hZoomAdjust, "value-changed", G_CALLBACK (hZoomAdjustCB), graphInfo);
	
	
	//******************* Max Check Boxes **********************
	
	GtkWidget* vMaxCheck = gtk_check_button_new ();
	GtkWidget* vMaxCheckAlign = gtk_alignment_new (1,0,0,0); // align right, top   y - dont fill, x - dont fill
	gtk_container_add(GTK_CONTAINER(vMaxCheckAlign), vMaxCheck); // add hZoomScale to the align container
	g_signal_connect (vMaxCheck, "toggled", G_CALLBACK (vMaxCheckCB), graphInfo);
	
	GtkWidget* hMaxCheck = gtk_check_button_new ();
	GtkWidget* hMaxCheckAlign = gtk_alignment_new (1,1,0,0); // align right, bottom   y - dont fill, x - dont fill
	gtk_container_add(GTK_CONTAINER(hMaxCheckAlign), hMaxCheck); // add hZoomScale to the align container
	g_signal_connect (hMaxCheck, "toggled", G_CALLBACK (hMaxCheckCB), graphInfo);
	
	//******************* Horizontal Scroll Bar **********************

	GtkAdjustment* hScrollAdjust = (GtkAdjustment*)gtk_adjustment_new (xMax/2, 0, xMax, xMax/10, xMax, xMax);
	GtkWidget* hScrollBar = gtk_hscale_new(hScrollAdjust);
	gtk_widget_set_sensitive (hScrollBar, FALSE);
	// align container for hScrollBar
	GtkWidget* hScrollAlign = gtk_alignment_new (0,1,1,0); // align left, bottom   y - dont fill, x - fill full
	gtk_container_add(GTK_CONTAINER(hScrollAlign), hScrollBar); // add hScrollBar to the align container
	g_signal_connect (hScrollAdjust, "value-changed", G_CALLBACK (hScrollAdjustCB), graphInfo);
	
	//******************* Vertical Scroll Bar **********************

	GtkAdjustment* vScrollAdjust = (GtkAdjustment*)gtk_adjustment_new (0, 0, 0, 1, 1, 1);
	GtkWidget* vScrollBar = gtk_vscale_new(vScrollAdjust);
	// align container for hScrollBar
	GtkWidget* vScrollAlign = gtk_alignment_new (1,0,0,1); // align right, top   x - dont fill, y - fill full
	gtk_container_add(GTK_CONTAINER(vScrollAlign), vScrollBar); // add hScrollBar to the align container
	g_signal_connect (vScrollAdjust, "value-changed", G_CALLBACK (vScrollAdjustCB), graphInfo);

	//******************* Enable Trace Checkboxes **********************
	
	// make a vbox to put enable trace checkboxes in.  individual trace checkboxes will be added after init function
	GtkWidget* enableBox = gtk_vbox_new (FALSE, 3);	
	
	
	// add enable toggle
	
	GtkWidget* globalEnableToggle = gtk_toggle_button_new_with_label ("Global Enable");
	gtk_toggle_button_set_active (globalEnableToggle, TRUE);
	GtkWidget* globalEnableToggleAlign = gtk_alignment_new (0,1,0,0); // align left, bottom   y - dont fill, x - dont fill
	gtk_container_add(GTK_CONTAINER(globalEnableToggleAlign), globalEnableToggle); // add checkbox to the align container
	g_signal_connect (globalEnableToggle, "toggled", G_CALLBACK (globalEnableToggleCB), graphInfo);
	
	
	gtk_box_pack_start ((GtkBox*)enableBox, globalEnableToggleAlign, FALSE, FALSE, 0);
	
	gtk_widget_show_all (globalEnableToggleAlign);
	
	//******************* The Graph *********************
	
	GtkGraph* graph = (GtkGraph*)gtk_graph_new (XY);
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
	
	GtkWidget* graphTable = gtk_table_new(4, 3, FALSE);
	
	// add all of the widgets to the table
	gtk_table_attach((GtkTable*)graphTable, vScrollAlign, 2, 3, 0, 1, GTK_SHRINK | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0); 
	gtk_table_attach((GtkTable*)graphTable, vZoomAlign, 3, 4, 0, 1, GTK_SHRINK | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0); 
	gtk_table_attach((GtkTable*)graphTable, hScrollAlign, 1, 2, 1, 2, GTK_EXPAND | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0); 
	gtk_table_attach((GtkTable*)graphTable, hZoomAlign, 1, 2, 2, 3, GTK_EXPAND | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0); 
	gtk_table_attach((GtkTable*)graphTable, (GtkWidget*)enableBox, 0, 1, 0, 3, GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 5, 0);
	gtk_table_attach((GtkTable*)graphTable, (GtkWidget*)graph, 1, 2, 0, 1, GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 5, 0);
	gtk_table_attach((GtkTable*)graphTable, (GtkWidget*)vMaxCheckAlign, 3, 4, 1, 2, GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 5, 0);
	gtk_table_attach((GtkTable*)graphTable, (GtkWidget*)hMaxCheckAlign, 2, 3, 2, 3, GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 5, 0);
	
	gtk_widget_show_all (graphTable); // show everything in table
	
	graphInfo->table = graphTable;
	graphInfo->graph = graph;
	graphInfo->enableBox = enableBox;
	graphInfo->vZoomAdjust = vZoomAdjust;
	graphInfo->vZoomAlign = vZoomAlign;
	graphInfo->hZoomAdjust = hZoomAdjust;
	graphInfo->hZoomAlign = hZoomAlign;
	graphInfo->hScrollAdjust = hScrollAdjust;
	graphInfo->hScrollBar = hScrollBar;
	graphInfo->vScrollBar = hScrollBar;
	graphInfo->vZoomScale = vZoomScale;
	graphInfo->hZoomScale = hZoomScale;
	
	graphInfo->globalEnable = 1;
	graphInfo->autoScaleX = 0;
	graphInfo->autoScaleY = 0;
	
	graphInfo->vScroll = yMin;

	graphInfo->traces = (struct dyTrace**)malloc(sizeof(struct dyTrace*)*256);
	graphInfo->traceCount = 0;
	
	return graphInfo;
	
}

struct dyTrace * dyGraphAddTrace (struct dyGraph * graphInfo, GtkGraphLineType type, gint width, GdkColor line_color, char * name) {

//******************* Stuff to do after initialization **********************
	
	// add enable checkbox
	
	GtkWidget* enableToggle = gtk_toggle_button_new_with_label (name);
	gtk_toggle_button_set_active (enableToggle, TRUE);

	gtk_widget_modify_bg(enableToggle, GTK_STATE_NORMAL, &line_color);
	gtk_widget_modify_bg(enableToggle, GTK_STATE_ACTIVE, &line_color);
	gtk_widget_modify_bg(enableToggle, GTK_STATE_PRELIGHT, &line_color);
	gtk_widget_modify_bg(enableToggle, GTK_STATE_SELECTED, &line_color);
	gtk_widget_modify_bg(enableToggle, GTK_STATE_INSENSITIVE, &line_color);

	// align container for enableACheck
	GtkWidget* enableToggleAlign = gtk_alignment_new (0,0,0,0); // align left, top   y - dont fill, x - dont fill
	gtk_container_add(GTK_CONTAINER(enableToggleAlign), enableToggle); // add hZoomScale to the align container
	
	gtk_box_pack_start ((GtkBox*)graphInfo->enableBox, enableToggleAlign, FALSE, FALSE, 0);

	gtk_widget_show_all (graphInfo->enableBox); // show everything we just added to enableBox
	
	// add trace
	
	gint trace = gtk_graph_trace_new(graphInfo->graph);
	
	gtk_graph_trace_format_line(graphInfo->graph, trace, type, width, &line_color, TRUE);
	gtk_graph_trace_format_title(graphInfo->graph, trace, name);	
	
	graphInfo->traces[graphInfo->traceCount] = (struct dyTrace*)malloc(sizeof(struct dyTrace));
	
	graphInfo->traces[graphInfo->traceCount]->trace = trace;
	graphInfo->traces[graphInfo->traceCount]->name = name;
	graphInfo->traces[graphInfo->traceCount]->enableToggle = enableToggle;
	graphInfo->traces[graphInfo->traceCount]->enableToggleAlign = enableToggleAlign;
	graphInfo->traces[graphInfo->traceCount]->xData = (float*)malloc(sizeof(float)*INITIAL_TRACE_DATA_LENGTH);
	graphInfo->traces[graphInfo->traceCount]->yData = (float*)malloc(sizeof(float)*INITIAL_TRACE_DATA_LENGTH);
	graphInfo->traces[graphInfo->traceCount]->dataLength = INITIAL_TRACE_DATA_LENGTH;
	graphInfo->traces[graphInfo->traceCount]->dataCurr = 0;
	
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
			graphInfo->xDataMax = x;
			if (graphInfo->globalEnable && trace->enabled) {
				if (graphInfo->autoScaleX)
					gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, x, graphInfo->xDataMin);
				else
					gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, x, x-graphInfo->hZoom);
			}
		}
	}
	
	if (x < trace->xDataMin) {
		trace->xDataMin = x;
		if (x < graphInfo->xDataMin) {
			graphInfo->xDataMin = x;
			if (graphInfo->globalEnable && graphInfo->autoScaleX && trace->enabled) {
				if (graphInfo->autoScaleX)
					gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, graphInfo->xDataMax, x);
				else
					gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, x, x-graphInfo->hZoom);
			}
		}
	}

	if (y > trace->yDataMax) {
		trace->yDataMax = y;
		if (y > graphInfo->yDataMax) {
			graphInfo->yDataMax = y;
			if (graphInfo->globalEnable && graphInfo->autoScaleY && trace->enabled)
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, y, graphInfo->yDataMin);
		}
	}
		
	if (y < trace->yDataMin) {
		trace->yDataMin = y;
		if (y < graphInfo->yDataMin) {
			graphInfo->yDataMin = y;
			if (graphInfo->globalEnable && graphInfo->autoScaleY && trace->enabled)
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, graphInfo->yDataMax, y);
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

static void hZoomAdjustCB (GtkAdjustment* adjust, struct dyGraph* graphInfo) {
	printf("\n\n**********hZoomAdjustCB**********\n\n");
	//~ graphInfo->hZoom = adjust->value/100;
	//~ gtk_graph_axis_set_limits(graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, graphInfo->hScroll+graphInfo->hZoom, graphInfo->hScroll);
	//~ gtk_adjustment_configure (adjust, adjust->value, 1., adjust->value*3., adjust->value/10., adjust->value, adjust->value);
	//~ dyGraphRedrawAll(graphInfo);
}

static void vZoomAdjustCB (GtkAdjustment* adjust, struct dyGraph* graphInfo) {
	printf("\n\n**********vZoomAdjustCB**********\n\n");
	//~ graphInfo->vZoom = adjust->value/100;
	//~ gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, graphInfo->vScroll+graphInfo->vZoom, graphInfo->vScroll);
	//~ gtk_adjustment_configure (adjust, adjust->value, 1., adjust->value*3., adjust->value/10., adjust->value, adjust->value);
	//~ dyGraphRedrawAll(graphInfo);
}

static void hScrollAdjustCB (GtkAdjustment* adjust, struct dyGraph* graphInfo) {
	printf("\n\n**********hScrollAdjustCB %f**********\n", adjust->value);
	//~ graphInfo->hScroll = adjust->value;
	//~ gtk_graph_axis_set_limits(graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, graphInfo->hScroll+graphInfo->hZoom/2, graphInfo->hScroll-graphInfo->hZoom/2);
	//~ dyGraphRedrawAll(graphInfo);
}

static void vScrollAdjustCB (GtkAdjustment* adjust, struct dyGraph* graphInfo) {
	printf("\n\n**********vScrollAdjustCB**********\n\n");
}

static void hMaxCheckCB (GtkToggleButton* checkBox, struct dyGraph* graphInfo) {
	printf("\n\n**********hMaxCheckCB**********\n\n");
	graphInfo->autoScaleX = gtk_toggle_button_get_active (checkBox);
	if (graphInfo->autoScaleX) {
		gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, graphInfo->xDataMax, graphInfo->xDataMin);
		gtk_widget_set_sensitive (graphInfo->hZoomScale, FALSE);
	} else {
		gtk_widget_set_sensitive (graphInfo->hZoomScale, TRUE);
	}
	dyGraphRedrawAll(graphInfo);
}

static void vMaxCheckCB (GtkToggleButton* checkBox, struct dyGraph* graphInfo) {
	printf("\n\n**********vMaxCheckCB**********\n\n");
	graphInfo->autoScaleY = gtk_toggle_button_get_active (checkBox);
	if (graphInfo->autoScaleY) {
		gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, graphInfo->yDataMax, graphInfo->yDataMin);
		gtk_widget_set_sensitive (graphInfo->vZoomScale, FALSE);
	} else {
		gtk_widget_set_sensitive (graphInfo->vZoomScale, TRUE);
	}
	dyGraphRedrawAll(graphInfo);
}

//this will have to serve for all trace enable checkboxes
static void traceEnableToggleCB (GtkToggleButton* toggleButton, struct handlerData* data) {
	printf("\n\n**********traceEnableCheckCB**********\n");
	data->trace->enabled = gtk_toggle_button_get_active (toggleButton);
	printf("%d\n\n", data->trace->enabled);
	dyGraphRedrawAll(data->graphInfo);
}

static void globalEnableToggleCB (GtkToggleButton* toggleButton, struct dyGraph* graphInfo) {
	printf("\n\n**********globalEnableCheckCB**********\n\n");
	graphInfo->globalEnable = gtk_toggle_button_get_active (toggleButton);
	
	if (graphInfo->globalEnable) {
		gtk_widget_set_sensitive (graphInfo->hScrollBar, FALSE);
	} else {
		gtk_widget_set_sensitive (graphInfo->hScrollBar, TRUE);
		//~ gtk_adjustment_configure (graphInfo->xDataMax-(, adjust->value, graphInfo->hScroll-graphInfo->hZoom/2, graphInfo->hScroll-graphInfo->hZoom/2, graphInfo->hZoom/10, graphInfo->hZoom, graphInfo->hZoom);
	}
	dyGraphRedrawAll(graphInfo);
}

static gint buttonPressCB (GtkWidget *widget, GdkEventButton *event, struct dyGraph* graphInfo) {
	if (event->button == 1) {
		graphInfo->translateOriginX = event->x;
		graphInfo->translateOriginY = event->y;
		
		printf ("translateOriginX=%d translateOriginY=%d\n", graphInfo->translateOriginX, graphInfo->translateOriginY);
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
	
	float xNumsPerPixel = (graphInfo->graph->independant->axis_max - graphInfo->graph->independant->axis_min) / (maxXPix - minXPix);
	float yNumsPerPixel = (graphInfo->graph->dependant->axis_max - graphInfo->graph->dependant->axis_min) / (maxYPix - minYPix);
	
	float newXMin = graphInfo->graph->independant->axis_min + (x - graphInfo->translateOriginX)*xNumsPerPixel;
	float newXMax = graphInfo->graph->independant->axis_max + (x - graphInfo->translateOriginX)*xNumsPerPixel;
	
	float newYMin = graphInfo->graph->dependant->axis_min + (y - graphInfo->translateOriginY)*yNumsPerPixel;
	float newYMax = graphInfo->graph->dependant->axis_max + (y - graphInfo->translateOriginY)*yNumsPerPixel;
	
	gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, newXMax, newXMin);
	//~ gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, newYMax, newYMin);
	
	dyGraphRedrawAll(graphInfo);
	
	printf ("xNumsPerPixel=%f\n", xNumsPerPixel);
	
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
			if (event->state & GDK_SHIFT_MASK) {
				// Zoom in x axis
				float min, max;
				findZoomedLimits (graphInfo->graph->independant->axis_min, graphInfo->graph->independant->axis_max, x, minXPix, maxXPix, graphInfo->xZoomFactor, &min, &max);				
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, max, min);
				dyGraphRedrawAll(graphInfo);
			} else if (event->state & GDK_CONTROL_MASK) {
				printf ("ZOOM IN CTRL @ %d %d\n", x, y);
			} else {
				// Zoom in y axis
				float min, max;
				findZoomedLimits (graphInfo->graph->dependant->axis_min, graphInfo->graph->dependant->axis_max, maxYPix-y+minYPix, minYPix, maxYPix, graphInfo->yZoomFactor, &min, &max);				
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, max, min);
				dyGraphRedrawAll(graphInfo);
			}
		} else if (event->direction == GDK_SCROLL_DOWN) {
			if (event->state & GDK_SHIFT_MASK) {
				// Zoom out x axis
				float min, max;
				findZoomedLimits (graphInfo->graph->independant->axis_min, graphInfo->graph->independant->axis_max, x, minXPix, maxXPix, 1/graphInfo->xZoomFactor, &min, &max);				
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_INDEPENDANT, max, min);
				dyGraphRedrawAll(graphInfo);
			} else if (event->state & GDK_CONTROL_MASK) {
				printf ("ZOOM OUT CTRL @ %d %d\n", x, y);
			} else {
				// Zoom out y axis
				float min, max;
				findZoomedLimits (graphInfo->graph->dependant->axis_min, graphInfo->graph->dependant->axis_max, maxYPix-y+minYPix, minYPix, maxYPix, 1/graphInfo->yZoomFactor, &min, &max);				
				gtk_graph_axis_set_limits (graphInfo->graph, GTK_GRAPH_AXIS_DEPENDANT, max, min);
				dyGraphRedrawAll(graphInfo);
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
