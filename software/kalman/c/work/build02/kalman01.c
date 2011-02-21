/*
 * kalman01.c
 *
 * Embedded MATLAB Coder code generation for function 'kalman01'
 *
 * C source code generated on: Mon Feb 21 11:45:35 2011
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kalman01.h"
#include "kalman01_data.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void kalman01(const real_T eml_z[2], real_T eml_y[2])
{
  int32_T eml_r2;
  int8_T eml_Q[36];
  int32_T eml_r1;
  real_T eml_x_prd[6];
  static int8_T eml_iv0[36] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0
    , 1, 0, 1 };

  real_T eml_klm_gain[36];
  int32_T eml_k;
  real_T eml_a21;
  static int8_T eml_iv1[36] = { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0,
    1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0
    , 0, 0, 1 };

  real_T eml_p_prd[36];
  real_T eml_b_klm_gain[12];
  static int8_T eml_iv2[12] = { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

  static int8_T eml_iv3[12] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };

  static int16_T eml_iv4[4] = { 1000, 0, 0, 1000 };

  real_T eml_S[4];
  real_T eml_B[12];
  real_T eml_a22;
  real_T eml_Y[12];
  real_T eml_b_z[2];

  /*  */
  /*    --------------------------------------------------------------------- */
  /*  */
  /*    Copyright 2010 The MathWorks, Inc. */
  /*  */
  /*    --------------------------------------------------------------------- */
  /*  */
  /*  Initialize state transition matrix */
  /*  Measurement matrix */
  for (eml_r2 = 0; eml_r2 < 36; eml_r2++) {
    eml_Q[eml_r2] = 0;
  }

  for (eml_r1 = 0; eml_r1 < 6; eml_r1++) {
    eml_Q[eml_r1 + 6 * eml_r1] = 1;

    /*  Initial conditions */
    /*  Predicted state and covariance */
    eml_x_prd[eml_r1] = 0.0;
    for (eml_r2 = 0; eml_r2 < 6; eml_r2++) {
      eml_x_prd[eml_r1] += (real_T)eml_iv0[eml_r1 + 6 * eml_r2] * x_est[eml_r2];
    }

    for (eml_r2 = 0; eml_r2 < 6; eml_r2++) {
      eml_klm_gain[eml_r1 + 6 * eml_r2] = 0.0;
      for (eml_k = 0; eml_k < 6; eml_k++) {
        eml_klm_gain[eml_r1 + 6 * eml_r2] += (real_T)eml_iv0[eml_r1 + 6 * eml_k]
          * p_est[eml_k + 6 * eml_r2];
      }
    }
  }

  for (eml_r2 = 0; eml_r2 < 6; eml_r2++) {
    for (eml_k = 0; eml_k < 6; eml_k++) {
      eml_a21 = 0.0;
      for (eml_r1 = 0; eml_r1 < 6; eml_r1++) {
        eml_a21 += eml_klm_gain[eml_r2 + 6 * eml_r1] * (real_T)eml_iv1[eml_r1 +
          6 * eml_k];
      }

      eml_p_prd[eml_r2 + 6 * eml_k] = eml_a21 + (real_T)eml_Q[eml_r2 + 6 * eml_k];
    }
  }

  /*  Estimation */
  for (eml_r2 = 0; eml_r2 < 2; eml_r2++) {
    for (eml_k = 0; eml_k < 6; eml_k++) {
      eml_b_klm_gain[eml_r2 + (eml_k << 1)] = 0.0;
      for (eml_r1 = 0; eml_r1 < 6; eml_r1++) {
        eml_b_klm_gain[eml_r2 + (eml_k << 1)] += (real_T)eml_iv2[eml_r2 +
          (eml_r1 << 1)] * eml_p_prd[eml_k + 6 * eml_r1];
      }
    }
  }

  for (eml_r2 = 0; eml_r2 < 2; eml_r2++) {
    for (eml_k = 0; eml_k < 2; eml_k++) {
      eml_a21 = 0.0;
      for (eml_r1 = 0; eml_r1 < 6; eml_r1++) {
        eml_a21 += eml_b_klm_gain[eml_r2 + (eml_r1 << 1)] * (real_T)
          eml_iv3[eml_r1 + 6 * eml_k];
      }

      eml_S[eml_r2 + (eml_k << 1)] = eml_a21 + (real_T)eml_iv4[eml_r2 + (eml_k <<
        1)];
    }
  }

  for (eml_r2 = 0; eml_r2 < 2; eml_r2++) {
    for (eml_k = 0; eml_k < 6; eml_k++) {
      eml_B[eml_r2 + (eml_k << 1)] = 0.0;
      for (eml_r1 = 0; eml_r1 < 6; eml_r1++) {
        eml_B[eml_r2 + (eml_k << 1)] += (real_T)eml_iv2[eml_r2 + (eml_r1 << 1)] *
          eml_p_prd[eml_k + 6 * eml_r1];
      }
    }
  }

  if (fabs(eml_S[1]) > fabs(eml_S[0])) {
    eml_r1 = 2;
    eml_r2 = 1;
  } else {
    eml_r1 = 1;
    eml_r2 = 2;
  }

  eml_a21 = eml_S[eml_r2 - 1] / eml_S[eml_r1 - 1];
  eml_a22 = eml_S[eml_r2 + 1] - eml_a21 * eml_S[eml_r1 + 1];
  for (eml_k = 0; eml_k < 6; eml_k++) {
    eml_Y[1 + (eml_k << 1)] = (eml_B[(eml_r2 - 1) + (eml_k << 1)] - eml_B
      [(eml_r1 - 1) + (eml_k << 1)] * eml_a21) / eml_a22;
    eml_Y[eml_k << 1] = (eml_B[(eml_r1 - 1) + (eml_k << 1)] - eml_Y[1 + (eml_k <<
      1)] * eml_S[eml_r1 + 1]) / eml_S[eml_r1 - 1];
  }

  for (eml_r2 = 0; eml_r2 < 2; eml_r2++) {
    for (eml_k = 0; eml_k < 6; eml_k++) {
      eml_b_klm_gain[eml_k + 6 * eml_r2] = eml_Y[eml_r2 + (eml_k << 1)];
    }
  }

  /*  Estimated state and covariance */
  for (eml_r2 = 0; eml_r2 < 2; eml_r2++) {
    eml_a21 = 0.0;
    for (eml_k = 0; eml_k < 6; eml_k++) {
      eml_a21 += (real_T)eml_iv2[eml_r2 + (eml_k << 1)] * eml_x_prd[eml_k];
    }

    eml_b_z[eml_r2] = eml_z[eml_r2] - eml_a21;
  }

  for (eml_r2 = 0; eml_r2 < 6; eml_r2++) {
    eml_a21 = 0.0;
    for (eml_k = 0; eml_k < 2; eml_k++) {
      eml_a21 += eml_b_klm_gain[eml_r2 + 6 * eml_k] * eml_b_z[eml_k];
    }

    x_est[eml_r2] = eml_x_prd[eml_r2] + eml_a21;
  }

  for (eml_r2 = 0; eml_r2 < 6; eml_r2++) {
    for (eml_k = 0; eml_k < 6; eml_k++) {
      eml_klm_gain[eml_r2 + 6 * eml_k] = 0.0;
      for (eml_r1 = 0; eml_r1 < 2; eml_r1++) {
        eml_klm_gain[eml_r2 + 6 * eml_k] += eml_b_klm_gain[eml_r2 + 6 * eml_r1] *
          (real_T)eml_iv2[eml_r1 + (eml_k << 1)];
      }
    }
  }

  for (eml_r2 = 0; eml_r2 < 6; eml_r2++) {
    for (eml_k = 0; eml_k < 6; eml_k++) {
      eml_a21 = 0.0;
      for (eml_r1 = 0; eml_r1 < 6; eml_r1++) {
        eml_a21 += eml_klm_gain[eml_r2 + 6 * eml_r1] * eml_p_prd[eml_r1 + 6 *
          eml_k];
      }

      p_est[eml_r2 + 6 * eml_k] = eml_p_prd[eml_r2 + 6 * eml_k] - eml_a21;
    }
  }

  /*  Compute the estimated measurements */
  for (eml_r2 = 0; eml_r2 < 2; eml_r2++) {
    eml_y[eml_r2] = 0.0;
    for (eml_k = 0; eml_k < 6; eml_k++) {
      eml_y[eml_r2] += (real_T)eml_iv2[eml_r2 + (eml_k << 1)] * x_est[eml_k];
    }
  }
}

/* End of Embedded MATLAB Coder code generation (kalman01.c) */
