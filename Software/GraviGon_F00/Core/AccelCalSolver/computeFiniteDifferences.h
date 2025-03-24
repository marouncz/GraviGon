/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeFiniteDifferences.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

#ifndef COMPUTEFINITEDIFFERENCES_H
#define COMPUTEFINITEDIFFERENCES_H

/* Include Files */
#include "AccelCalSolver_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
bool computeFiniteDifferences(c_struct_T *obj, const double cEqCurrent[6],
                              double xk[6], double JacCeqTrans[36]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeFiniteDifferences.h
 *
 * [EOF]
 */
