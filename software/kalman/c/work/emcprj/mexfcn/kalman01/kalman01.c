/*
 * kalman01.c
 *
 * Embedded MATLAB Coder code generation for function 'kalman01'
 *
 * C source code generated on: Sun Feb 20 12:22:09 2011
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kalman01.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static emlrtRSInfo eml_emlrtRSI = { 32, "kalman01", "/Users/cooleys/Desktop/work/kalman01.m" };
static emlrtRSInfo eml_b_emlrtRSI = { 37, "kalman01", "/Users/cooleys/Desktop/work/kalman01.m" };
static emlrtRSInfo eml_c_emlrtRSI = { 41, "kalman01", "/Users/cooleys/Desktop/work/kalman01.m" };
static emlrtRSInfo eml_d_emlrtRSI = { 17, "eye", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/elmat/eye.m" };
static emlrtRSInfo eml_f_emlrtRSI = { 83, "mtimes", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/ops/mtimes.m" };
static emlrtRSInfo eml_g_emlrtRSI = { 53, "eml_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m" };
static emlrtRSInfo eml_h_emlrtRSI = { 26, "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m" };
static emlrtRSInfo eml_i_emlrtRSI = { 76, "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m" };
static emlrtRSInfo eml_j_emlrtRSI = { 83, "mtimes", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/ops/mtimes.m" };
static emlrtRSInfo eml_k_emlrtRSI = { 1, "mldivide", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/ops/mldivide.p" };
static emlrtRSInfo eml_l_emlrtRSI = { 30, "eml_lusolve", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/eml_lusolve.m" };
static emlrtRSInfo eml_m_emlrtRSI = { 108, "eml_lusolve", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/eml_lusolve.m" };
static emlrtRSInfo eml_n_emlrtRSI = { 48, "eml_lusolve", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/eml_lusolve.m" };
static emlrtRSInfo eml_o_emlrtRSI = { 11, "eml_warning", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/eml_warning.m" };
static emlrtRSInfo eml_p_emlrtRSI = { 83, "mtimes", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/ops/mtimes.m" };
static emlrtRSInfo eml_q_emlrtRSI = { 53, "eml_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m" };
static emlrtRSInfo eml_r_emlrtRSI = { 26, "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m" };
static emlrtRSInfo eml_s_emlrtRSI = { 76, "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m" };
static emlrtRSInfo eml_t_emlrtRSI = { 83, "mtimes", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/ops/mtimes.m" };
static emlrtMCInfo eml_emlrtMCI = { 11, 9, "eml_warning", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/eml_warning.m" };
static emlrtBCInfo eml_emlrtBCI = { 1, 36, 78, 22, "", "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m", 0 };
static emlrtBCInfo eml_b_emlrtBCI = { 1, 36, 79, 5, "", "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m", 0 };
static emlrtBCInfo eml_c_emlrtBCI = { 1, 36, 80, 21, "", "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m", 0 };
static emlrtBCInfo eml_d_emlrtBCI = { 1, 12, 78, 22, "", "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m", 0 };
static emlrtBCInfo eml_e_emlrtBCI = { 1, 12, 79, 5, "", "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m", 0 };
static emlrtBCInfo eml_f_emlrtBCI = { 1, 36, 80, 21, "", "eml_blas_xgemm", "/Applications/MATLAB_R2010b.app/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m", 0 };

/* Function Declarations */
static void m_b_refp12_ceval_xgemm(int32_T eml_m, int32_T eml_n, int32_T eml_k, real_T eml_alpha1, const real_T eml_A[12], int32_T eml_ia0, int32_T eml_lda, const real_T eml_B[12], int32_T eml_ib0, int32_T eml_ldb, real_T eml_beta1, real_T eml_C[36], int32_T eml_ic0, int32_T eml_ldc);
static void m_eml_warning(void);
static void m_refp12_ceval_xgemm(int32_T eml_m, int32_T eml_n, int32_T eml_k, real_T eml_alpha1, const real_T eml_A[36], int32_T eml_ia0, int32_T eml_lda, const real_T eml_B[36], int32_T eml_ib0, int32_T eml_ldb, real_T eml_beta1, real_T eml_C[36], int32_T eml_ic0, int32_T eml_ldc);
static void m_warning(const mxArray *eml_b, const mxArray *eml_c, emlrtMCInfo *eml_location);

/* Function Definitions */

static void m_b_refp12_ceval_xgemm(int32_T eml_m, int32_T eml_n, int32_T eml_k, real_T eml_alpha1, const real_T eml_A[12], int32_T 
    eml_ia0, int32_T eml_lda, const real_T eml_B[12], int32_T eml_ib0, int32_T eml_ldb, real_T eml_beta1, real_T eml_C[36], int32_T 
    eml_ic0, int32_T eml_ldc)
{
    char_T eml_TRANSA;
    char_T eml_TRANSB;
    eml_TRANSA = 'N';
    eml_TRANSB = 'N';
    EMLRTPUSHRTSTACK(&eml_s_emlrtRSI);
    dgemm32(&eml_TRANSA, &eml_TRANSB, &eml_m, &eml_n, &eml_k, &eml_alpha1, &eml_A[emlrtBoundsCheck(eml_ia0, &eml_d_emlrtBCI) - 1], &
        eml_lda, &eml_B[emlrtBoundsCheck(eml_ib0, &eml_e_emlrtBCI) - 1], &eml_ldb, &eml_beta1, &eml_C[emlrtBoundsCheck(eml_ic0, &
        eml_f_emlrtBCI) - 1], &eml_ldc);
    EMLRTPOPRTSTACK(&eml_s_emlrtRSI);
}

static void m_eml_warning(void)
{
    const mxArray *eml_y;
    static const int32_T eml_iv4[2] = { 1, 21 };
    const mxArray *eml_m0;
    static char_T eml_cv0[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a', 't', 'r', 'i'
                                          , 'x' };
    const mxArray *eml_b_y;
    static const int32_T eml_iv5[2] = { 1, 40 };
    static char_T eml_cv1[40] = { 'M', 'a', 't', 'r', 'i', 'x', ' ', 'i', 's', ' ', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', ' ', 't'
                                          , 'o', ' ', 'w', 'o', 'r', 'k', 'i', 'n', 'g', ' ', 'p', 'r', 'e', 'c', 'i', 's', 'i', 'o'
                                          , 'n', '.' };
    EMLRTPUSHRTSTACK(&eml_o_emlrtRSI);
    eml_y = NULL;
    eml_m0 = mxCreateCharArray(2, eml_iv4);
    emlrtInitCharArray(21, eml_m0, eml_cv0);
    emlrtAssign(&eml_y, eml_m0);
    eml_b_y = NULL;
    eml_m0 = mxCreateCharArray(2, eml_iv5);
    emlrtInitCharArray(40, eml_m0, eml_cv1);
    emlrtAssign(&eml_b_y, eml_m0);
    m_warning(eml_y, eml_b_y, &eml_emlrtMCI);
    EMLRTPOPRTSTACK(&eml_o_emlrtRSI);
}

static void m_refp12_ceval_xgemm(int32_T eml_m, int32_T eml_n, int32_T eml_k, real_T eml_alpha1, const real_T eml_A[36], int32_T 
    eml_ia0, int32_T eml_lda, const real_T eml_B[36], int32_T eml_ib0, int32_T eml_ldb, real_T eml_beta1, real_T eml_C[36], int32_T 
    eml_ic0, int32_T eml_ldc)
{
    char_T eml_TRANSA;
    char_T eml_TRANSB;
    eml_TRANSA = 'N';
    eml_TRANSB = 'N';
    EMLRTPUSHRTSTACK(&eml_i_emlrtRSI);
    dgemm32(&eml_TRANSA, &eml_TRANSB, &eml_m, &eml_n, &eml_k, &eml_alpha1, &eml_A[emlrtBoundsCheck(eml_ia0, &eml_emlrtBCI) - 1], &
        eml_lda, &eml_B[emlrtBoundsCheck(eml_ib0, &eml_b_emlrtBCI) - 1], &eml_ldb, &eml_beta1, &eml_C[emlrtBoundsCheck(eml_ic0, &
        eml_c_emlrtBCI) - 1], &eml_ldc);
    EMLRTPOPRTSTACK(&eml_i_emlrtRSI);
}

static void m_warning(const mxArray *eml_b, const mxArray *eml_c, emlrtMCInfo *eml_location)
{
    const mxArray *eml_pArrays[2];
    eml_pArrays[0] = eml_b;
    eml_pArrays[1] = eml_c;
    emlrtCallMATLAB(0, NULL, 2, eml_pArrays, "warning", TRUE, eml_location);
}

void kalman01(kalman01StackData *eml_SD, const real_T eml_z[2], real_T eml_y[2])
{
    int32_T eml_r1;
    int8_T eml_Q[36];
    real_T eml_x_prd[6];
    int32_T eml_r2;
    static int8_T eml_iv0[36] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0
                                          , 1, 0, 1 };
    real_T eml_b_y[36];
    real_T eml_dv0[36];
    static real_T eml_dv1[36] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0
                                          , 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0 };
    static real_T eml_dv2[36] = { 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0
                                          , 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
    real_T eml_klm_gain[12];
    int32_T eml_k;
    static int8_T eml_iv1[12] = { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
    real_T eml_a21;
    static int8_T eml_iv2[12] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
    static int16_T eml_iv3[4] = { 1000, 0, 0, 1000 };
    real_T eml_S[4];
    real_T eml_B[12];
    real_T eml_a22;
    real_T eml_Y[12];
    real_T eml_b_z[2];
    static real_T eml_dv3[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    real_T eml_c_y[36];
    real_T eml_dv4[36];
    /*  */
    /*    --------------------------------------------------------------------- */
    /*  */
    /*    Copyright 2010 The MathWorks, Inc. */
    /*  */
    /*    --------------------------------------------------------------------- */
    /*  */
    /*  Initialize state transition matrix */
    /*  Measurement matrix */
    EMLRTPUSHRTSTACK(&eml_d_emlrtRSI);
    for(eml_r1 = 0; eml_r1 < 36; eml_r1++) {
        eml_Q[eml_r1] = 0;
    }
    for(eml_r1 = 0; eml_r1 < 6; eml_r1++) {
        eml_Q[eml_r1 + 6 * eml_r1] = 1;
    }
    EMLRTPOPRTSTACK(&eml_d_emlrtRSI);
    /*  Initial conditions */
    /*  Predicted state and covariance */
    for(eml_r1 = 0; eml_r1 < 6; eml_r1++) {
        eml_x_prd[eml_r1] = 0.0;
        for(eml_r2 = 0; eml_r2 < 6; eml_r2++) {
            eml_x_prd[eml_r1] += (real_T)eml_iv0[eml_r1 + 6 * eml_r2] * eml_SD->pd->x_est[eml_r2];
        }
    }
    EMLRTPUSHRTSTACK(&eml_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_f_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_g_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_h_emlrtRSI);
    memset((void *)&eml_b_y[0], 0, 36U * sizeof(real_T));
    memcpy((void *)&eml_dv0[0], (void *)&eml_SD->pd->p_est[0], 36U * sizeof(real_T));
    m_refp12_ceval_xgemm(6, 6, 6, 1.0, eml_dv1, 1, 6, eml_dv0, 1, 6, 0.0, eml_b_y, 1, 6);
    EMLRTPOPRTSTACK(&eml_h_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_g_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_f_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_j_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_g_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_h_emlrtRSI);
    memset((void *)&eml_SD->pd->p_est[0], 0, 36U * sizeof(real_T));
    m_refp12_ceval_xgemm(6, 6, 6, 1.0, eml_b_y, 1, 6, eml_dv2, 1, 6, 0.0, eml_SD->pd->p_est, 1, 6);
    EMLRTPOPRTSTACK(&eml_h_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_g_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_j_emlrtRSI);
    for(eml_r1 = 0; eml_r1 < 36; eml_r1++) {
        eml_SD->pd->p_est[eml_r1] += (real_T)eml_Q[eml_r1];
    }
    EMLRTPOPRTSTACK(&eml_emlrtRSI);
    /*  Estimation */
    for(eml_r1 = 0; eml_r1 < 2; eml_r1++) {
        for(eml_r2 = 0; eml_r2 < 6; eml_r2++) {
            eml_klm_gain[eml_r1 + (eml_r2 << 1)] = 0.0;
            for(eml_k = 0; eml_k < 6; eml_k++) {
                eml_klm_gain[eml_r1 + (eml_r2 << 1)] += (real_T)eml_iv1[eml_r1 + (eml_k << 1)] * eml_SD->pd->p_est[eml_r2 + 6 * 
                    eml_k];
            }
        }
    }
    for(eml_r1 = 0; eml_r1 < 2; eml_r1++) {
        for(eml_r2 = 0; eml_r2 < 2; eml_r2++) {
            eml_a21 = 0.0;
            for(eml_k = 0; eml_k < 6; eml_k++) {
                eml_a21 += eml_klm_gain[eml_r1 + (eml_k << 1)] * (real_T)eml_iv2[eml_k + 6 * eml_r2];
            }
            eml_S[eml_r1 + (eml_r2 << 1)] = eml_a21 + (real_T)eml_iv3[eml_r1 + (eml_r2 << 1)];
        }
    }
    for(eml_r1 = 0; eml_r1 < 2; eml_r1++) {
        for(eml_r2 = 0; eml_r2 < 6; eml_r2++) {
            eml_B[eml_r1 + (eml_r2 << 1)] = 0.0;
            for(eml_k = 0; eml_k < 6; eml_k++) {
                eml_B[eml_r1 + (eml_r2 << 1)] += (real_T)eml_iv1[eml_r1 + (eml_k << 1)] * eml_SD->pd->p_est[eml_r2 + 6 * eml_k];
            }
        }
    }
    EMLRTPUSHRTSTACK(&eml_b_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_k_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_l_emlrtRSI);
    if(muDoubleScalarAbs(eml_S[1]) > muDoubleScalarAbs(eml_S[0])) {
        eml_r1 = 2;
        eml_r2 = 1;
    } else {
        eml_r1 = 1;
        eml_r2 = 2;
    }
    eml_a21 = eml_S[eml_r2 - 1] / eml_S[eml_r1 - 1];
    eml_a22 = eml_S[eml_r2 + 1] - eml_a21 * eml_S[eml_r1 + 1];
    if((eml_a22 == 0.0) || (eml_S[eml_r1 - 1] == 0.0)) {
        EMLRTPUSHRTSTACK(&eml_m_emlrtRSI);
        EMLRTPUSHRTSTACK(&eml_n_emlrtRSI);
        m_eml_warning();
        EMLRTPOPRTSTACK(&eml_n_emlrtRSI);
        EMLRTPOPRTSTACK(&eml_m_emlrtRSI);
    }
    for(eml_k = 0; eml_k < 6; eml_k++) {
        eml_Y[1 + (eml_k << 1)] = (eml_B[(eml_r2 - 1) + (eml_k << 1)] - eml_B[(eml_r1 - 1) + (eml_k << 1)] * eml_a21) / eml_a22;
        eml_Y[eml_k << 1] = (eml_B[(eml_r1 - 1) + (eml_k << 1)] - eml_Y[1 + (eml_k << 1)] * eml_S[eml_r1 + 1]) / eml_S[eml_r1 - 1];
    }
    EMLRTPOPRTSTACK(&eml_l_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_k_emlrtRSI);
    for(eml_r1 = 0; eml_r1 < 2; eml_r1++) {
        for(eml_r2 = 0; eml_r2 < 6; eml_r2++) {
            eml_klm_gain[eml_r2 + 6 * eml_r1] = eml_Y[eml_r1 + (eml_r2 << 1)];
        }
    }
    EMLRTPOPRTSTACK(&eml_b_emlrtRSI);
    /*  Estimated state and covariance */
    for(eml_r1 = 0; eml_r1 < 2; eml_r1++) {
        eml_a21 = 0.0;
        for(eml_r2 = 0; eml_r2 < 6; eml_r2++) {
            eml_a21 += (real_T)eml_iv1[eml_r1 + (eml_r2 << 1)] * eml_x_prd[eml_r2];
        }
        eml_b_z[eml_r1] = eml_z[eml_r1] - eml_a21;
    }
    for(eml_r1 = 0; eml_r1 < 6; eml_r1++) {
        eml_a21 = 0.0;
        for(eml_r2 = 0; eml_r2 < 2; eml_r2++) {
            eml_a21 += eml_klm_gain[eml_r1 + 6 * eml_r2] * eml_b_z[eml_r2];
        }
        eml_SD->pd->x_est[eml_r1] = eml_x_prd[eml_r1] + eml_a21;
    }
    EMLRTPUSHRTSTACK(&eml_c_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_p_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_q_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_r_emlrtRSI);
    memset((void *)&eml_b_y[0], 0, 36U * sizeof(real_T));
    m_b_refp12_ceval_xgemm(6, 6, 2, 1.0, eml_klm_gain, 1, 6, eml_dv3, 1, 2, 0.0, eml_b_y, 1, 6);
    EMLRTPOPRTSTACK(&eml_r_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_q_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_p_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_t_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_g_emlrtRSI);
    EMLRTPUSHRTSTACK(&eml_h_emlrtRSI);
    memset((void *)&eml_c_y[0], 0, 36U * sizeof(real_T));
    memcpy((void *)&eml_dv4[0], (void *)&eml_SD->pd->p_est[0], 36U * sizeof(real_T));
    m_refp12_ceval_xgemm(6, 6, 6, 1.0, eml_b_y, 1, 6, eml_dv4, 1, 6, 0.0, eml_c_y, 1, 6);
    EMLRTPOPRTSTACK(&eml_h_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_g_emlrtRSI);
    EMLRTPOPRTSTACK(&eml_t_emlrtRSI);
    for(eml_r1 = 0; eml_r1 < 36; eml_r1++) {
        eml_SD->pd->p_est[eml_r1] -= eml_c_y[eml_r1];
    }
    EMLRTPOPRTSTACK(&eml_c_emlrtRSI);
    /*  Compute the estimated measurements */
    for(eml_r1 = 0; eml_r1 < 2; eml_r1++) {
        eml_y[eml_r1] = 0.0;
        for(eml_r2 = 0; eml_r2 < 6; eml_r2++) {
            eml_y[eml_r1] += (real_T)eml_iv1[eml_r1 + (eml_r2 << 1)] * eml_SD->pd->x_est[eml_r2];
        }
    }
}
/* End of Embedded MATLAB Coder code generation (kalman01.c) */
