/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeFiniteDifferences.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

/* Include Files */
#include "computeFiniteDifferences.h"
#include "AccelCalSolver_internal_types.h"
#include "finDiffEvalAndChkErr.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : c_struct_T *obj
 *                const double cEqCurrent[6]
 *                double xk[6]
 *                double JacCeqTrans[36]
 * Return Type  : bool
 */
bool computeFiniteDifferences(c_struct_T *obj, const double cEqCurrent[6],
                              double xk[6], double JacCeqTrans[36])
{
  double d;
  int idx;
  int idx_row;
  bool evalOK;
  bool exitg1;
  evalOK = true;
  obj->numEvals = 0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx < 6)) {
    double deltaX;
    bool guard1;
    deltaX = 1.4901161193847656E-8 * (1.0 - 2.0 * (double)(xk[idx] < 0.0)) *
             fmax(fabs(xk[idx]), 1.0);
    evalOK =
        finDiffEvalAndChkErr(obj->nonlin.workspace.fun.workspace.accel,
                             obj->nonlin.workspace.fun.workspace.gravityScalar,
                             idx + 1, deltaX, xk, &d, obj->cEq_1);
    obj->f_1 = 0.0;
    obj->numEvals++;
    guard1 = false;
    if (!evalOK) {
      deltaX = -deltaX;
      evalOK = finDiffEvalAndChkErr(
          obj->nonlin.workspace.fun.workspace.accel,
          obj->nonlin.workspace.fun.workspace.gravityScalar, idx + 1, deltaX,
          xk, &d, obj->cEq_1);
      obj->f_1 = 0.0;
      obj->numEvals++;
      if (!evalOK) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      for (idx_row = 0; idx_row < 6; idx_row++) {
        JacCeqTrans[idx + 6 * idx_row] =
            (obj->cEq_1[idx_row] - cEqCurrent[idx_row]) / deltaX;
      }
      idx++;
    }
  }
  return evalOK;
}

/*
 * File trailer for computeFiniteDifferences.c
 *
 * [EOF]
 */
