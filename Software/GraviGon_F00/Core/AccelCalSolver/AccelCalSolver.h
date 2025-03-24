/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: AccelCalSolver.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

#ifndef ACCELCALSOLVER_H
#define ACCELCALSOLVER_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void AccelCalSolver(const double accel[18], double gravityScalar,
                           double x[6], double fval[6]);

void AccelCalSolver_anonFcn1(const double accel[18], double gravityScalar,
                             const double x[6], double varargout_1[6]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for AccelCalSolver.h
 *
 * [EOF]
 */
