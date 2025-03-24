/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: linearLeastSquares.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 21-Apr-2024 17:12:30
 */

/* Include Files */
#include "linearLeastSquares.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double lhs[72]
 *                double rhs[12]
 *                double dx[6]
 * Return Type  : void
 */
void linearLeastSquares(double lhs[72], double rhs[12], double dx[6])
{
  double jpvt[6];
  double work[6];
  double d;
  double temp;
  int b_i;
  int i;
  int ii;
  int ix;
  int iy;
  int j;
  int k;
  int nfxd;
  int temp_tmp;
  for (i = 0; i < 6; i++) {
    jpvt[i] = 0.0;
  }
  nfxd = 0;
  for (j = 0; j < 6; j++) {
    if (jpvt[j] != 0.0) {
      nfxd++;
      if (j + 1 != nfxd) {
        ix = j * 12;
        iy = (nfxd - 1) * 12;
        for (k = 0; k < 12; k++) {
          temp_tmp = ix + k;
          temp = lhs[temp_tmp];
          b_i = iy + k;
          lhs[temp_tmp] = lhs[b_i];
          lhs[b_i] = temp;
        }
        jpvt[j] = jpvt[nfxd - 1];
        jpvt[nfxd - 1] = (double)j + 1.0;
      } else {
        jpvt[j] = (double)j + 1.0;
      }
    } else {
      jpvt[j] = (double)j + 1.0;
    }
    dx[j] = 0.0;
    work[j] = 0.0;
  }
  b_i = (unsigned char)nfxd;
  for (i = 0; i < b_i; i++) {
    ii = i * 12 + i;
    temp = lhs[ii];
    d = xzlarfg(12 - i, &temp, lhs, ii + 2);
    dx[i] = d;
    lhs[ii] = temp;
    if (i + 1 < 6) {
      lhs[ii] = 1.0;
      xzlarf(12 - i, 5 - i, ii + 1, d, lhs, ii + 13, work);
      lhs[ii] = temp;
    }
  }
  if (nfxd < 6) {
    double vn1[6];
    double vn2[6];
    for (i = 0; i < 6; i++) {
      work[i] = 0.0;
      vn1[i] = 0.0;
      vn2[i] = 0.0;
    }
    b_i = nfxd + 1;
    for (j = b_i; j < 7; j++) {
      d = xnrm2(12 - nfxd, lhs, (nfxd + (j - 1) * 12) + 1);
      vn1[j - 1] = d;
      vn2[j - 1] = d;
    }
    for (i = b_i; i < 7; i++) {
      double s;
      int ip1;
      ip1 = i + 1;
      j = (i - 1) * 12;
      ii = (j + i) - 1;
      iy = 7 - i;
      nfxd = -1;
      if (7 - i > 1) {
        temp = fabs(vn1[i - 1]);
        for (k = 2; k <= iy; k++) {
          s = fabs(vn1[(i + k) - 2]);
          if (s > temp) {
            nfxd = k - 2;
            temp = s;
          }
        }
      }
      iy = i + nfxd;
      if (iy + 1 != i) {
        ix = iy * 12;
        for (k = 0; k < 12; k++) {
          temp_tmp = ix + k;
          temp = lhs[temp_tmp];
          nfxd = j + k;
          lhs[temp_tmp] = lhs[nfxd];
          lhs[nfxd] = temp;
        }
        temp = jpvt[iy];
        jpvt[iy] = jpvt[i - 1];
        jpvt[i - 1] = temp;
        vn1[iy] = vn1[i - 1];
        vn2[iy] = vn2[i - 1];
      }
      temp = lhs[ii];
      d = xzlarfg(13 - i, &temp, lhs, ii + 2);
      dx[i - 1] = d;
      lhs[ii] = temp;
      if (i < 6) {
        lhs[ii] = 1.0;
        xzlarf(13 - i, 6 - i, ii + 1, d, lhs, ii + 13, work);
        lhs[ii] = temp;
      }
      for (j = ip1; j < 7; j++) {
        iy = i + (j - 1) * 12;
        d = vn1[j - 1];
        if (d != 0.0) {
          temp = fabs(lhs[iy - 1]) / d;
          temp = 1.0 - temp * temp;
          if (temp < 0.0) {
            temp = 0.0;
          }
          s = d / vn2[j - 1];
          s = temp * (s * s);
          if (s <= 1.4901161193847656E-8) {
            d = xnrm2(12 - i, lhs, iy + 1);
            vn1[j - 1] = d;
            vn2[j - 1] = d;
          } else {
            vn1[j - 1] = d * sqrt(temp);
          }
        }
      }
    }
  }
  for (j = 0; j < 6; j++) {
    if (dx[j] != 0.0) {
      temp = rhs[j];
      b_i = j + 2;
      for (i = b_i; i < 13; i++) {
        temp += lhs[(i + 12 * j) - 1] * rhs[i - 1];
      }
      temp *= dx[j];
      if (temp != 0.0) {
        rhs[j] -= temp;
        for (i = b_i; i < 13; i++) {
          rhs[i - 1] -= lhs[(i + 12 * j) - 1] * temp;
        }
      }
    }
  }
  nfxd = 0;
  temp = 2.6645352591003757E-14 * fabs(lhs[0]);
  while ((nfxd < 6) && (!(fabs(lhs[nfxd + 12 * nfxd]) <= temp))) {
    nfxd++;
  }
  for (b_i = 0; b_i < 6; b_i++) {
    dx[b_i] = rhs[b_i];
  }
  if (nfxd != 0) {
    for (j = nfxd; j >= 1; j--) {
      iy = (j + (j - 1) * 12) - 1;
      dx[j - 1] /= lhs[iy];
      for (i = 0; i <= j - 2; i++) {
        ix = (j - i) - 2;
        dx[ix] -= dx[j - 1] * lhs[(iy - i) - 1];
      }
    }
  }
  if (nfxd + 1 > 6) {
    nfxd = 0;
    b_i = 0;
  } else {
    b_i = 6;
  }
  iy = b_i - nfxd;
  if (iy - 1 >= 0) {
    memset(&dx[nfxd], 0, (unsigned int)((iy + nfxd) - nfxd) * sizeof(double));
  }
  for (b_i = 0; b_i < 6; b_i++) {
    work[b_i] = dx[b_i];
  }
  for (b_i = 0; b_i < 6; b_i++) {
    dx[(int)jpvt[b_i] - 1] = work[b_i];
  }
}

/*
 * File trailer for linearLeastSquares.c
 *
 * [EOF]
 */
