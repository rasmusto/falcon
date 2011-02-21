/*
 * kalman01_mex.c
 *
 * Embedded MATLAB Coder code generation for function 'kalman01'
 *
 * C source code generated on: Sun Feb 20 12:22:09 2011
 *
 */

/* Include files */
#include "mex.h"
#include "kalman01_api.h"
#include "kalman01_data.h"
#include "kalman01_initialize.h"
#include "kalman01_terminate.h"

/* Type Definitions */

/* Function Declarations */
static void kalman01_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

/* Variable Definitions */
emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "kalman01", NULL, false };

/* Function Definitions */
static void kalman01_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Temporary copy for mex outputs. */
  mxArray *outputs[1];
  int n = 0;
  int nOutputs = (nlhs < 1 ? 1 : nlhs);
  kalman01StackData* eml_kalman01StackDataLocal = (kalman01StackData*)mxCalloc(1,sizeof(kalman01StackData));
  eml_kalman01StackDataLocal->pd = kalman01PersistentDataGlobal;
  /* Check for proper number of arguments. */
  if(nrhs != 1) {
    mexErrMsgIdAndTxt("emlcoder:emlmex:WrongNumberOfInputs","1 input required for entry-point 'kalman01'.");
  } else if(nlhs > 1) {
    mexErrMsgIdAndTxt("emlcoder:emlmex:TooManyOutputArguments","Too many output arguments for entry-point 'kalman01'.");
  }
  /* Module initialization. */
  kalman01_initialize(eml_kalman01StackDataLocal, &emlrtContextGlobal);
  /* Call the function. */
  kalman01_api(eml_kalman01StackDataLocal, prhs,(const mxArray**)outputs);
  /* Copy over outputs to the caller. */
  for (n = 0; n < nOutputs; ++n) {
    plhs[n] = emlrtReturnArrayR2009a(outputs[n]);
  }
  /* Module finalization. */
  kalman01_terminate();
  mxFree(eml_kalman01StackDataLocal);
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Initialize the memory manager. */
  if (kalman01PersistentDataGlobal == NULL) {
      kalman01PersistentDataGlobal = (kalman01PersistentData*)mxCalloc(1,sizeof(kalman01PersistentData));
      mexMakeMemoryPersistent(kalman01PersistentDataGlobal);
  }
  mexAtExit(kalman01_atexit);
  emlrtClearAllocCount(&emlrtContextGlobal, 0, 0, NULL);
  /* Dispatch the entry-point. */
  kalman01_mexFunction(nlhs, plhs, nrhs, prhs);
}
/* End of Embedded MATLAB Coder code generation (kalman01_mex.c) */
