/*
 * kalman01_api.c
 *
 * Embedded MATLAB Coder code generation for function 'kalman01_api'
 *
 * C source code generated on: Sun Feb 20 12:22:09 2011
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kalman01.h"
#include "kalman01_api.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void m_b_emlrt_marshallIn(const mxArray *eml_src, const char_T *eml_nam, real_T eml_ret[2]);
static void m_emlrt_marshallIn(const mxArray *eml_z, const char_T *eml_name, real_T eml_y[2]);
static const mxArray *m_emlrt_marshallOut(const real_T eml_u[2]);

/* Function Definitions */

static void m_b_emlrt_marshallIn(const mxArray *eml_src, const char_T *eml_nam, real_T eml_ret[2])
{
    int32_T eml_iv7[1];
    int32_T eml_i0;
    eml_iv7[0] = 2;
    emlrtCheckBuiltIn(eml_nam, eml_src, "double", FALSE, 1U, eml_iv7);
    for(eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        eml_ret[eml_i0] = (*((real_T (*)[2])mxGetData(eml_src)))[eml_i0];
    }
    emlrtDestroyArray(&eml_src);
}

static void m_emlrt_marshallIn(const mxArray *eml_z, const char_T *eml_name, real_T eml_y[2])
{
    m_b_emlrt_marshallIn(emlrtAlias(eml_z), eml_name, eml_y);
    emlrtDestroyArray(&eml_z);
}

static const mxArray *m_emlrt_marshallOut(const real_T eml_u[2])
{
    const mxArray *eml_y;
    static const int32_T eml_iv6[1] = { 2 };
    const mxArray *eml_m1;
    real_T (*eml_pData)[];
    int32_T eml_i;
    eml_y = NULL;
    eml_m1 = mxCreateNumericArray(1, (int32_T *)&eml_iv6, mxDOUBLE_CLASS, mxREAL);
    eml_pData = (real_T (*)[])mxGetPr(eml_m1);
    for(eml_i = 0; eml_i < 2; eml_i++) {
        (*eml_pData)[eml_i] = eml_u[eml_i];
    }
    emlrtAssign(&eml_y, eml_m1);
    return eml_y;
}

void kalman01_api(kalman01StackData *eml_SD, const mxArray *const eml_prhs[1], const mxArray *eml_plhs[1])
{
    real_T eml_z[2];
    int32_T eml_i;
    real_T eml_b_z[2];
    /* Marshall function inputs */
    m_emlrt_marshallIn(emlrtAliasP(eml_prhs[0]), "z", eml_z);
    /* Invoke the target function */
    for(eml_i = 0; eml_i < 2; eml_i++) {
        eml_b_z[eml_i] = eml_z[eml_i];
    }
    kalman01(eml_SD, eml_b_z, eml_z);
    /* Marshall function outputs */
    eml_plhs[0] = m_emlrt_marshallOut(eml_z);
}
/* End of Embedded MATLAB Coder code generation (kalman01_api.c) */
