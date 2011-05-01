#ifndef __DY_GRAPH_H__
#define __DY_GRAPH_H__

#include <stdint.h>
#include <gtk/gtk.h>
#include "gtkgraph.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct dyTrace {
	gint trace;
	char* name;
	GtkWidget* enableToggle;
	GtkWidget* enableToggleAlign;

	float* xData;
	float* yData;
	uint32_t dataLength;
	uint32_t dataCurr;
	float xDataMax;
	float xDataMin;
	float yDataMax;
	float yDataMin;

	uint8_t enabled; // boolean - trace enabled
};

struct dyGraph {
	GtkWidget * table;
	GtkGraph* graph;
	GtkWidget* enableBox;
	
	GtkWidget* vZoomScale;
	GtkWidget* hZoomScale;

	struct dyTrace** traces;
	volatile uint8_t traceCount;

	float xDataMax;
	float yDataMax;
	float xDataMin;
	float yDataMin;

	uint8_t globalEnable; // boolean - enable for all traces

	uint8_t autoScaleX;
	uint8_t autoPanX;
	uint8_t autoScaleY;
	
	float xZoomFactor;
	float yZoomFactor;
	
	int translateOriginX;
	int translateOriginY;
	
	float translateOrigionalMinX;
	float translateOrigionalMaxX;
	float translateOrigionalMinY;
	float translateOrigionalMaxY;
};

struct handlerData {
	struct dyGraph* graphInfo;
	struct dyTrace* trace;
};

typedef enum 
{
DYGRAPH_FULL     = 1 << 0,
DYGRAPH_SIMPLE   = 1 << 1,
}dyGraphType;

typedef enum 
{
DYGRAPH_AUTO_SCALE_X = 1 << 0,
DYGRAPH_AUTO_SCALE_Y = 1 << 1,
DYGRAPH_AUTO_PAN_X   = 1 << 2,
}dyGraphSettings;

struct dyGraph * dyGraphInit (char* title, char* subTitle, char* xLabel, char* yLabel, float xMax, float yMin, float yMax, dyGraphType type, dyGraphSettings settings);
struct dyTrace * dyGraphAddTrace (struct dyGraph * graphInfo, GtkGraphLineType type, gint width, GdkColor line_color, char * name);
void dyGraphAddData (struct dyGraph * graphInfo, struct dyTrace * trace, float x, float y);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DY_GRAPH_H__ */
