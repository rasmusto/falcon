/*
 * kalman01_initialize.c
 *
 * Embedded MATLAB Coder code generation for function 'kalman01_initialize'
 *
 * C source code generated on: Mon Feb 21 11:45:35 2011
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kalman01.h"
#include "kalman01_initialize.h"
#include "kalman01_data.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void kalman01_initialize(void)
{
  int32_T eml_i;
  rt_InitInfAndNaN(8U);
  for (eml_i = 0; eml_i < 6; eml_i++) {
    x_est[eml_i] = 0.0;
  }

  memset((void *)&p_est[0], 0, 36U * sizeof(real_T));
}

/* End of Embedded MATLAB Coder code generation (kalman01_initialize.c) */
