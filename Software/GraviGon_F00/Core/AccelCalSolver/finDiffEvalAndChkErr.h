/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: finDiffEvalAndChkErr.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

#ifndef FINDIFFEVALANDCHKERR_H
#define FINDIFFEVALANDCHKERR_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
bool finDiffEvalAndChkErr(const double c_obj_nonlin_workspace_fun_work[18],
                          double d_obj_nonlin_workspace_fun_work, int dim,
                          double delta, double xk[6], double *fplus,
                          double cEqPlus[6]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for finDiffEvalAndChkErr.h
 *
 * [EOF]
 */
