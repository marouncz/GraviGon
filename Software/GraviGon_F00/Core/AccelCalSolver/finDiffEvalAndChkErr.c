/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: finDiffEvalAndChkErr.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

/* Include Files */
#include "finDiffEvalAndChkErr.h"
#include "AccelCalSolver.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const double c_obj_nonlin_workspace_fun_work[18]
 *                double d_obj_nonlin_workspace_fun_work
 *                int dim
 *                double delta
 *                double xk[6]
 *                double *fplus
 *                double cEqPlus[6]
 * Return Type  : bool
 */
bool finDiffEvalAndChkErr(const double c_obj_nonlin_workspace_fun_work[18],
                          double d_obj_nonlin_workspace_fun_work, int dim,
                          double delta, double xk[6], double *fplus,
                          double cEqPlus[6])
{
  double temp_tmp;
  int idx;
  bool evalOK;
  *fplus = 0.0;
  evalOK = true;
  temp_tmp = xk[dim - 1];
  xk[dim - 1] = temp_tmp + delta;
  AccelCalSolver_anonFcn1(c_obj_nonlin_workspace_fun_work,
                          d_obj_nonlin_workspace_fun_work, xk, cEqPlus);
  idx = 0;
  while (evalOK && (idx + 1 <= 6)) {
    evalOK = ((!rtIsInf(cEqPlus[idx])) && (!rtIsNaN(cEqPlus[idx])));
    idx++;
  }
  xk[dim - 1] = temp_tmp;
  return evalOK;
}

/*
 * File trailer for finDiffEvalAndChkErr.c
 *
 * [EOF]
 */
