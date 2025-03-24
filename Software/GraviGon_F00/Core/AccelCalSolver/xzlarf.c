/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzlarf.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

/* Include Files */
#include "xzlarf.h"
#include "AccelCalSolver_rtwutil.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                double tau
 *                double C[72]
 *                int ic0
 *                double work[6]
 * Return Type  : void
 */
void xzlarf(int m, int n, int iv0, double tau, double C[72], int ic0,
            double work[6])
{
  int i;
  int ia;
  int lastc;
  int lastv;
  if (tau != 0.0) {
    bool exitg2;
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && (C[i - 2] == 0.0)) {
      lastv--;
      i--;
    }
    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      int exitg1;
      i = ic0 + (lastc - 1) * 12;
      ia = i;
      do {
        exitg1 = 0;
        if (ia <= (i + lastv) - 1) {
          if (C[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);
      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }
  if (lastv > 0) {
    double c;
    int b_i;
    int i1;
    if (lastc != 0) {
      b_i = (unsigned char)lastc;
      memset(&work[0], 0, (unsigned int)b_i * sizeof(double));
      b_i = ic0 + 12 * (lastc - 1);
      for (i = ic0; i <= b_i; i += 12) {
        c = 0.0;
        i1 = (i + lastv) - 1;
        for (ia = i; ia <= i1; ia++) {
          c += C[ia - 1] * C[((iv0 + ia) - i) - 1];
        }
        i1 = div_nde_s32_floor(i - ic0, 12);
        work[i1] += c;
      }
    }
    if (!(-tau == 0.0)) {
      i = ic0;
      b_i = (unsigned char)lastc;
      for (lastc = 0; lastc < b_i; lastc++) {
        c = work[lastc];
        if (c != 0.0) {
          c *= -tau;
          i1 = lastv + i;
          for (ia = i; ia < i1; ia++) {
            C[ia - 1] += C[((iv0 + ia) - i) - 1] * c;
          }
        }
        i += 12;
      }
    }
  }
}

/*
 * File trailer for xzlarf.c
 *
 * [EOF]
 */
