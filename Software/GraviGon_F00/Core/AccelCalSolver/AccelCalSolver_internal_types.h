/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: AccelCalSolver_internal_types.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

#ifndef ACCELCALSOLVER_INTERNAL_TYPES_H
#define ACCELCALSOLVER_INTERNAL_TYPES_H

/* Include Files */
#include "AccelCalSolver_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  double accel[18];
  double gravityScalar;
} struct_T;
#endif /* typedef_struct_T */

#ifndef typedef_anonymous_function
#define typedef_anonymous_function
typedef struct {
  struct_T workspace;
} anonymous_function;
#endif /* typedef_anonymous_function */

#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct {
  anonymous_function fun;
} b_struct_T;
#endif /* typedef_b_struct_T */

#ifndef typedef_b_anonymous_function
#define typedef_b_anonymous_function
typedef struct {
  b_struct_T workspace;
} b_anonymous_function;
#endif /* typedef_b_anonymous_function */

#ifndef typedef_c_struct_T
#define typedef_c_struct_T
typedef struct {
  b_anonymous_function nonlin;
  double f_1;
  double cEq_1[6];
  double f_2;
  double cEq_2[6];
  int nVar;
  int mIneq;
  int mEq;
  int numEvals;
  bool SpecifyObjectiveGradient;
  bool SpecifyConstraintGradient;
  bool isEmptyNonlcon;
  bool hasLB[6];
  bool hasUB[6];
  bool hasBounds;
  int FiniteDifferenceType;
} c_struct_T;
#endif /* typedef_c_struct_T */

#endif
/*
 * File trailer for AccelCalSolver_internal_types.h
 *
 * [EOF]
 */
