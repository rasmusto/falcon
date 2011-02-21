/*
 * kalman01_types.h
 *
 * Embedded MATLAB Coder code generation for function 'kalman01'
 *
 * C source code generated on: Sun Feb 20 12:22:09 2011
 *
 */

#ifndef __KALMAN01_TYPES_H__
#define __KALMAN01_TYPES_H__

/* Type Definitions */
typedef struct {
    real_T x_est[6];
    real_T p_est[36];
} kalman01PersistentData;
typedef struct {
    kalman01PersistentData *pd;
} kalman01StackData;

#endif
/* End of Embedded MATLAB Coder code generation (kalman01_types.h) */
