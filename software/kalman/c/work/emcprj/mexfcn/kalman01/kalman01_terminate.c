/*
 * kalman01_terminate.c
 *
 * Embedded MATLAB Coder code generation for function 'kalman01_terminate'
 *
 * C source code generated on: Sun Feb 20 12:22:09 2011
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kalman01.h"
#include "kalman01_terminate.h"
#include "kalman01_data.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */

void kalman01_atexit(void)
{
    mxFree(kalman01PersistentDataGlobal);
}

void kalman01_terminate(void)
{
    emlrtLeaveRtStack(&emlrtContextGlobal);
}
/* End of Embedded MATLAB Coder code generation (kalman01_terminate.c) */
