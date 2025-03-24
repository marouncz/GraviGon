/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: AccelCalSolver.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

/* Include Files */
#include "AccelCalSolver.h"
#include "AccelCalSolver_internal_types.h"
#include "AccelCalSolver_rtwutil.h"
#include "computeFiniteDifferences.h"
#include "linearLeastSquares.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * The directive %#codegen indicates that the function
 *  is intended for code generation
 *
 * Arguments    : const double accel[18]
 *                double gravityScalar
 *                double x[6]
 *                double fval[6]
 * Return Type  : void
 */
void AccelCalSolver(const double accel[18], double gravityScalar, double x[6],
                    double fval[6])
{
  static const double varargin_1[6] = {1.0, 0.0, 1.0, 0.0, 1.0, 0.0};
  static const signed char b_x[6] = {1, 0, 1, 0, 1, 0};
  c_struct_T FiniteDifferences;
  double augJacobian[72];
  double JacCeqTrans[36];
  double rhs[12];
  double dx[6];
  double gradf[6];
  double b_gamma;
  double b_scale;
  double c;
  double funDiff;
  double normGradF;
  double relFactor;
  double resnorm;
  double scale;
  double t;
  int aIdx;
  int bIdx;
  int exitflag;
  int funcCount;
  int i;
  int iter;
  bool evalOK;
  bool exitg1;
  bool stepSuccessful;
  FiniteDifferences.nonlin.workspace.fun.workspace.gravityScalar =
      gravityScalar;
  memcpy(&FiniteDifferences.nonlin.workspace.fun.workspace.accel[0], &accel[0],
         18U * sizeof(double));
  funDiff = rtInf;
  iter = 0;
  AccelCalSolver_anonFcn1(accel, gravityScalar, varargin_1, gradf);
  resnorm = 0.0;
  FiniteDifferences.f_1 = 0.0;
  FiniteDifferences.f_2 = 0.0;
  FiniteDifferences.nVar = 6;
  FiniteDifferences.mIneq = 0;
  FiniteDifferences.mEq = 6;
  FiniteDifferences.numEvals = 0;
  FiniteDifferences.SpecifyObjectiveGradient = false;
  FiniteDifferences.SpecifyConstraintGradient = false;
  FiniteDifferences.isEmptyNonlcon = false;
  FiniteDifferences.FiniteDifferenceType = 0;
  FiniteDifferences.hasBounds = false;
  for (i = 0; i < 6; i++) {
    dx[i] = rtInf;
    bIdx = (int)varargin_1[i];
    x[i] = bIdx;
    c = gradf[i];
    fval[i] = c;
    resnorm += c * c;
    FiniteDifferences.hasLB[i] = false;
    FiniteDifferences.hasUB[i] = false;
    gradf[i] = bIdx;
  }
  computeFiniteDifferences(&FiniteDifferences, fval, gradf, JacCeqTrans);
  for (bIdx = 0; bIdx < 6; bIdx++) {
    for (exitflag = 0; exitflag < 6; exitflag++) {
      augJacobian[exitflag + 12 * bIdx] = JacCeqTrans[bIdx + 6 * exitflag];
    }
  }
  funcCount = FiniteDifferences.numEvals + 1;
  for (exitflag = 0; exitflag < 6; exitflag++) {
    aIdx = exitflag * 12;
    bIdx = exitflag * 6;
    for (i = 0; i < 6; i++) {
      JacCeqTrans[bIdx + i] = augJacobian[aIdx + i];
    }
  }
  b_gamma = 0.01;
  for (i = 0; i < 6; i++) {
    exitflag = 12 * (i + 1);
    for (aIdx = 0; aIdx < 6; aIdx++) {
      augJacobian[(exitflag + aIdx) - 6] = 0.0;
    }
    augJacobian[(i + 12 * i) + 6] = 0.1;
    gradf[i] = 0.0;
  }
  for (aIdx = 0; aIdx <= 30; aIdx += 6) {
    c = 0.0;
    bIdx = aIdx + 6;
    for (exitflag = aIdx + 1; exitflag <= bIdx; exitflag++) {
      c += JacCeqTrans[exitflag - 1] * fval[(exitflag - aIdx) - 1];
    }
    exitflag = div_nde_s32_floor(aIdx, 6);
    gradf[exitflag] += c;
  }
  c = 0.0;
  stepSuccessful = true;
  normGradF = 0.0;
  for (aIdx = 0; aIdx < 6; aIdx++) {
    scale = fabs(gradf[aIdx]);
    evalOK = rtIsNaN(scale);
    if (evalOK || (scale > c)) {
      c = scale;
    }
    if (evalOK || (scale > normGradF)) {
      normGradF = scale;
    }
  }
  relFactor = fmax(c, 1.0);
  if (normGradF <= 1.0E-10 * relFactor) {
    exitflag = 1;
  } else if (FiniteDifferences.numEvals + 1 >= 1200) {
    exitflag = 0;
  } else {
    c = 0.0;
    scale = 3.3121686421112381E-170;
    normGradF = 0.0;
    b_scale = 3.3121686421112381E-170;
    for (aIdx = 0; aIdx < 6; aIdx++) {
      if (scale < rtInf) {
        c = c * 0.0 * 0.0 + 1.0;
        scale = rtInf;
      } else {
        c = rtNaN;
      }
      bIdx = b_x[aIdx];
      if (bIdx > b_scale) {
        normGradF = normGradF * b_scale * b_scale + 1.0;
        b_scale = 1.0;
      } else {
        t = (double)bIdx / b_scale;
        normGradF += t * t;
      }
    }
    c = scale * sqrt(c);
    normGradF = b_scale * sqrt(normGradF);
    if (c < 1.0E-6 * (normGradF + 1.4901161193847656E-8)) {
      exitflag = 4;
    } else {
      exitflag = -5;
    }
  }
  exitg1 = false;
  while ((!exitg1) && (exitflag == -5)) {
    double fNew[6];
    double xp[6];
    bool guard1;
    for (aIdx = 0; aIdx < 6; aIdx++) {
      rhs[aIdx] = -fval[aIdx];
      rhs[aIdx + 6] = 0.0;
    }
    linearLeastSquares(augJacobian, rhs, dx);
    for (bIdx = 0; bIdx < 6; bIdx++) {
      xp[bIdx] = x[bIdx] + dx[bIdx];
    }
    AccelCalSolver_anonFcn1(accel, gravityScalar, xp, gradf);
    scale = 0.0;
    evalOK = true;
    for (i = 0; i < 6; i++) {
      c = gradf[i];
      fNew[i] = c;
      scale += c * c;
      if ((!evalOK) || (rtIsInf(c) || rtIsNaN(c))) {
        evalOK = false;
      }
    }
    funcCount++;
    guard1 = false;
    if ((scale < resnorm) && evalOK) {
      iter++;
      funDiff = fabs(scale - resnorm) / resnorm;
      resnorm = scale;
      for (bIdx = 0; bIdx < 6; bIdx++) {
        gradf[bIdx] = xp[bIdx];
      }
      evalOK = computeFiniteDifferences(&FiniteDifferences, fNew, gradf,
                                        JacCeqTrans);
      funcCount += FiniteDifferences.numEvals;
      for (i = 0; i < 6; i++) {
        for (bIdx = 0; bIdx < 6; bIdx++) {
          augJacobian[bIdx + 12 * i] = JacCeqTrans[i + 6 * bIdx];
        }
        fval[i] = fNew[i];
      }
      for (exitflag = 0; exitflag < 6; exitflag++) {
        aIdx = exitflag * 12;
        bIdx = exitflag * 6;
        for (i = 0; i < 6; i++) {
          JacCeqTrans[bIdx + i] = augJacobian[aIdx + i];
        }
      }
      if (evalOK) {
        for (bIdx = 0; bIdx < 6; bIdx++) {
          x[bIdx] = xp[bIdx];
        }
        if (stepSuccessful) {
          b_gamma *= 0.1;
        }
        stepSuccessful = true;
        guard1 = true;
      } else {
        exitg1 = true;
      }
    } else {
      b_gamma *= 10.0;
      stepSuccessful = false;
      for (exitflag = 0; exitflag < 6; exitflag++) {
        aIdx = exitflag * 6;
        bIdx = exitflag * 12;
        for (i = 0; i < 6; i++) {
          augJacobian[bIdx + i] = JacCeqTrans[aIdx + i];
        }
      }
      guard1 = true;
    }
    if (guard1) {
      c = sqrt(b_gamma);
      for (i = 0; i < 6; i++) {
        exitflag = 12 * (i + 1);
        for (aIdx = 0; aIdx < 6; aIdx++) {
          augJacobian[(exitflag + aIdx) - 6] = 0.0;
        }
        augJacobian[(i + 12 * i) + 6] = c;
        gradf[i] = 0.0;
      }
      for (aIdx = 0; aIdx <= 30; aIdx += 6) {
        c = 0.0;
        bIdx = aIdx + 6;
        for (exitflag = aIdx + 1; exitflag <= bIdx; exitflag++) {
          c += JacCeqTrans[exitflag - 1] * fval[(exitflag - aIdx) - 1];
        }
        exitflag = div_nde_s32_floor(aIdx, 6);
        gradf[exitflag] += c;
      }
      normGradF = 0.0;
      for (aIdx = 0; aIdx < 6; aIdx++) {
        c = fabs(gradf[aIdx]);
        if (rtIsNaN(c) || (c > normGradF)) {
          normGradF = c;
        }
      }
      if (normGradF <= 1.0E-10 * relFactor) {
        exitflag = 1;
      } else if (funcCount >= 1200) {
        exitflag = 0;
      } else if (iter >= 400) {
        exitflag = 0;
      } else {
        c = 0.0;
        scale = 3.3121686421112381E-170;
        normGradF = 0.0;
        b_scale = 3.3121686421112381E-170;
        for (aIdx = 0; aIdx < 6; aIdx++) {
          double absxk;
          absxk = fabs(dx[aIdx]);
          if (absxk > scale) {
            t = scale / absxk;
            c = c * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            c += t * t;
          }
          absxk = fabs(x[aIdx]);
          if (absxk > b_scale) {
            t = b_scale / absxk;
            normGradF = normGradF * t * t + 1.0;
            b_scale = absxk;
          } else {
            t = absxk / b_scale;
            normGradF += t * t;
          }
        }
        c = scale * sqrt(c);
        normGradF = b_scale * sqrt(normGradF);
        if (c < 1.0E-6 * (normGradF + 1.4901161193847656E-8)) {
          exitflag = 4;
          if (!stepSuccessful) {
            iter++;
          }
        } else if (funDiff <= 1.0E-6) {
          exitflag = 3;
        } else {
          exitflag = -5;
        }
      }
      if (exitflag != -5) {
        exitg1 = true;
      }
    }
  }
}

/*
 * Arguments    : const double accel[18]
 *                double gravityScalar
 *                const double x[6]
 *                double varargout_1[6]
 * Return Type  : void
 */
void AccelCalSolver_anonFcn1(const double accel[18], double gravityScalar,
                             const double x[6], double varargout_1[6])
{
  double a;
  double b_a;
  double c_a;
  double varargout_1_tmp;
  /*  Allocate return array */
  a = accel[0] * x[0] + x[1];
  b_a = x[2] * accel[6] + x[3];
  c_a = x[4] * accel[12] + x[5];
  varargout_1_tmp = gravityScalar * gravityScalar;
  varargout_1[0] = ((a * a + b_a * b_a) + c_a * c_a) - varargout_1_tmp;
  a = x[0] * accel[1] + x[1];
  b_a = x[2] * accel[7] + x[3];
  c_a = x[4] * accel[13] + x[5];
  varargout_1[1] = ((a * a + b_a * b_a) + c_a * c_a) - varargout_1_tmp;
  a = x[0] * accel[2] + x[1];
  b_a = x[2] * accel[8] + x[3];
  c_a = x[4] * accel[14] + x[5];
  varargout_1[2] = ((a * a + b_a * b_a) + c_a * c_a) - varargout_1_tmp;
  a = x[0] * accel[3] + x[1];
  b_a = x[2] * accel[9] + x[3];
  c_a = x[4] * accel[15] + x[5];
  varargout_1[3] = ((a * a + b_a * b_a) + c_a * c_a) - varargout_1_tmp;
  a = x[0] * accel[4] + x[1];
  b_a = x[2] * accel[10] + x[3];
  c_a = x[4] * accel[16] + x[5];
  varargout_1[4] = ((a * a + b_a * b_a) + c_a * c_a) - varargout_1_tmp;
  a = x[0] * accel[5] + x[1];
  b_a = x[2] * accel[11] + x[3];
  c_a = x[4] * accel[17] + x[5];
  varargout_1[5] = ((a * a + b_a * b_a) + c_a * c_a) - varargout_1_tmp;
}

/*
 * File trailer for AccelCalSolver.c
 *
 * [EOF]
 */
