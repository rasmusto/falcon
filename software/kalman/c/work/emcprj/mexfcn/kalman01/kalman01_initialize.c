/*
 * kalman01_initialize.c
 *
 * Embedded MATLAB Coder code generation for function 'kalman01_initialize'
 *
 * C source code generated on: Sun Feb 20 12:22:09 2011
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kalman01.h"
#include "kalman01_initialize.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void m_kalman01_once(kalman01StackData *eml_SD);

/* Function Definitions */

static void m_kalman01_once(kalman01StackData *eml_SD)
{
    int32_T eml_i;
    for(eml_i = 0; eml_i < 6; eml_i++) {
        eml_SD->pd->x_est[eml_i] = 0.0;
    }
    memset((void *)&eml_SD->pd->p_est[0], 0, 36U * sizeof(real_T));
}

void kalman01_initialize(kalman01StackData *eml_SD, emlrtContext *eml_context)
{
    emlrtEnterRtStack(&emlrtContextGlobal);
    if(emlrtFirstTime(eml_context)) {
        m_kalman01_once(eml_SD);
    }
}
/* End of Embedded MATLAB Coder code generation (kalman01_initialize.c) */
