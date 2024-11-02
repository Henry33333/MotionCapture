//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// mldivide.cpp
//
// Code generation for function 'mldivide'
//

// Include files
#include "mldivide.h"
#include "hybrid_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
namespace coder {
void b_mldivide(const double A[1080], const double B[120], double Y[9])
{
  double b_A[1080];
  double b_B[120];
  double tau[9];
  double vn1[9];
  double vn2[9];
  double work[9];
  double absxk;
  double scale;
  double smax;
  double t;
  int b_i;
  int i;
  int ix0;
  int iy;
  int j;
  int kend;
  int lastc;
  int rankA;
  signed char jpvt[9];
  std::copy(&A[0], &A[1080], &b_A[0]);
  for (lastc = 0; lastc < 9; lastc++) {
    jpvt[lastc] = static_cast<signed char>(lastc + 1);
    tau[lastc] = 0.0;
    work[lastc] = 0.0;
    ix0 = lastc * 120;
    smax = 0.0;
    scale = 3.3121686421112381E-170;
    kend = ix0 + 120;
    for (iy = ix0 + 1; iy <= kend; iy++) {
      absxk = std::abs(A[iy - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        smax = smax * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        smax += t * t;
      }
    }
    absxk = scale * std::sqrt(smax);
    vn1[lastc] = absxk;
    vn2[lastc] = absxk;
  }
  for (i = 0; i < 9; i++) {
    int ii;
    int ip1;
    int pvt;
    ip1 = i + 2;
    ii = i * 120 + i;
    kend = 9 - i;
    iy = 0;
    if (9 - i > 1) {
      smax = std::abs(vn1[i]);
      for (lastc = 2; lastc <= kend; lastc++) {
        scale = std::abs(vn1[(i + lastc) - 1]);
        if (scale > smax) {
          iy = lastc - 1;
          smax = scale;
        }
      }
    }
    pvt = i + iy;
    if (pvt != i) {
      kend = pvt * 120;
      iy = i * 120;
      for (lastc = 0; lastc < 120; lastc++) {
        rankA = kend + lastc;
        smax = b_A[rankA];
        ix0 = iy + lastc;
        b_A[rankA] = b_A[ix0];
        b_A[ix0] = smax;
      }
      kend = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = static_cast<signed char>(kend);
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }
    t = b_A[ii];
    ix0 = ii + 2;
    tau[i] = 0.0;
    smax = internal::blas::c_xnrm2(119 - i, b_A, ii + 2);
    if (smax != 0.0) {
      absxk = b_A[ii];
      scale = rt_hypotd_snf(absxk, smax);
      if (absxk >= 0.0) {
        scale = -scale;
      }
      if (std::abs(scale) < 1.0020841800044864E-292) {
        kend = 0;
        b_i = (ii - i) + 120;
        do {
          kend++;
          for (lastc = ix0; lastc <= b_i; lastc++) {
            b_A[lastc - 1] *= 9.9792015476736E+291;
          }
          scale *= 9.9792015476736E+291;
          t *= 9.9792015476736E+291;
        } while ((std::abs(scale) < 1.0020841800044864E-292) && (kend < 20));
        scale = rt_hypotd_snf(t, internal::blas::c_xnrm2(119 - i, b_A, ii + 2));
        if (t >= 0.0) {
          scale = -scale;
        }
        tau[i] = (scale - t) / scale;
        smax = 1.0 / (t - scale);
        for (lastc = ix0; lastc <= b_i; lastc++) {
          b_A[lastc - 1] *= smax;
        }
        for (lastc = 0; lastc < kend; lastc++) {
          scale *= 1.0020841800044864E-292;
        }
        t = scale;
      } else {
        tau[i] = (scale - absxk) / scale;
        smax = 1.0 / (absxk - scale);
        b_i = (ii - i) + 120;
        for (lastc = ix0; lastc <= b_i; lastc++) {
          b_A[lastc - 1] *= smax;
        }
        t = scale;
      }
    }
    b_A[ii] = t;
    if (i + 1 < 9) {
      int lastv;
      b_A[ii] = 1.0;
      iy = ii + 121;
      if (tau[i] != 0.0) {
        boolean_T exitg2;
        lastv = 120 - i;
        kend = (ii - i) + 119;
        while ((lastv > 0) && (b_A[kend] == 0.0)) {
          lastv--;
          kend--;
        }
        lastc = 7 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc + 1 > 0)) {
          int exitg1;
          kend = (ii + lastc * 120) + 120;
          rankA = kend;
          do {
            exitg1 = 0;
            if (rankA + 1 <= kend + lastv) {
              if (b_A[rankA] != 0.0) {
                exitg1 = 1;
              } else {
                rankA++;
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
        lastc = -1;
      }
      if (lastv > 0) {
        if (lastc + 1 != 0) {
          if (0 <= lastc) {
            std::memset(&work[0], 0, (lastc + 1) * sizeof(double));
          }
          b_i = (ii + 120 * lastc) + 121;
          for (ix0 = iy; ix0 <= b_i; ix0 += 120) {
            smax = 0.0;
            pvt = (ix0 + lastv) - 1;
            for (rankA = ix0; rankA <= pvt; rankA++) {
              smax += b_A[rankA - 1] * b_A[(ii + rankA) - ix0];
            }
            kend = div_nde_s32_floor((ix0 - ii) - 121, 120);
            work[kend] += smax;
          }
        }
        if (!(-tau[i] == 0.0)) {
          kend = ii;
          for (j = 0; j <= lastc; j++) {
            absxk = work[j];
            if (absxk != 0.0) {
              smax = absxk * -tau[i];
              b_i = kend + 121;
              pvt = lastv + kend;
              for (rankA = b_i; rankA <= pvt + 120; rankA++) {
                b_A[rankA - 1] += b_A[((ii + rankA) - kend) - 121] * smax;
              }
            }
            kend += 120;
          }
        }
      }
      b_A[ii] = t;
    }
    for (j = ip1; j < 10; j++) {
      kend = i + (j - 1) * 120;
      absxk = vn1[j - 1];
      if (absxk != 0.0) {
        smax = std::abs(b_A[kend]) / absxk;
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }
        scale = absxk / vn2[j - 1];
        scale = smax * (scale * scale);
        if (scale <= 1.4901161193847656E-8) {
          absxk = internal::blas::c_xnrm2(119 - i, b_A, kend + 2);
          vn1[j - 1] = absxk;
          vn2[j - 1] = absxk;
        } else {
          vn1[j - 1] = absxk * std::sqrt(smax);
        }
      }
    }
  }
  rankA = 0;
  smax = 2.6645352591003757E-13 * std::abs(b_A[0]);
  while ((rankA < 9) && (!(std::abs(b_A[rankA + 120 * rankA]) <= smax))) {
    rankA++;
  }
  std::copy(&B[0], &B[120], &b_B[0]);
  for (j = 0; j < 9; j++) {
    Y[j] = 0.0;
    if (tau[j] != 0.0) {
      smax = b_B[j];
      b_i = j + 2;
      for (i = b_i; i < 121; i++) {
        smax += b_A[(i + 120 * j) - 1] * b_B[i - 1];
      }
      smax *= tau[j];
      if (smax != 0.0) {
        b_B[j] -= smax;
        for (i = b_i; i < 121; i++) {
          b_B[i - 1] -= b_A[(i + 120 * j) - 1] * smax;
        }
      }
    }
  }
  for (i = 0; i < rankA; i++) {
    Y[jpvt[i] - 1] = b_B[i];
  }
  for (j = rankA; j >= 1; j--) {
    kend = jpvt[j - 1] - 1;
    iy = 120 * (j - 1);
    Y[kend] /= b_A[(j + iy) - 1];
    for (i = 0; i <= j - 2; i++) {
      ix0 = jpvt[i] - 1;
      Y[ix0] -= Y[kend] * b_A[i + iy];
    }
  }
}

void mldivide(const double A[1800], const double B[120], double Y[15])
{
  double b_A[1800];
  double b_B[120];
  double tau[15];
  double vn1[15];
  double vn2[15];
  double work[15];
  double absxk;
  double scale;
  double smax;
  double t;
  int b_i;
  int i;
  int ix0;
  int iy;
  int j;
  int kend;
  int lastc;
  int rankA;
  signed char jpvt[15];
  std::copy(&A[0], &A[1800], &b_A[0]);
  for (lastc = 0; lastc < 15; lastc++) {
    jpvt[lastc] = static_cast<signed char>(lastc + 1);
    tau[lastc] = 0.0;
    work[lastc] = 0.0;
    ix0 = lastc * 120;
    smax = 0.0;
    scale = 3.3121686421112381E-170;
    kend = ix0 + 120;
    for (iy = ix0 + 1; iy <= kend; iy++) {
      absxk = std::abs(A[iy - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        smax = smax * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        smax += t * t;
      }
    }
    absxk = scale * std::sqrt(smax);
    vn1[lastc] = absxk;
    vn2[lastc] = absxk;
  }
  for (i = 0; i < 15; i++) {
    int ii;
    int ip1;
    int pvt;
    ip1 = i + 2;
    ii = i * 120 + i;
    kend = 15 - i;
    iy = 0;
    if (15 - i > 1) {
      smax = std::abs(vn1[i]);
      for (lastc = 2; lastc <= kend; lastc++) {
        scale = std::abs(vn1[(i + lastc) - 1]);
        if (scale > smax) {
          iy = lastc - 1;
          smax = scale;
        }
      }
    }
    pvt = i + iy;
    if (pvt != i) {
      kend = pvt * 120;
      iy = i * 120;
      for (lastc = 0; lastc < 120; lastc++) {
        rankA = kend + lastc;
        smax = b_A[rankA];
        ix0 = iy + lastc;
        b_A[rankA] = b_A[ix0];
        b_A[ix0] = smax;
      }
      kend = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = static_cast<signed char>(kend);
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }
    t = b_A[ii];
    ix0 = ii + 2;
    tau[i] = 0.0;
    smax = internal::blas::xnrm2(119 - i, b_A, ii + 2);
    if (smax != 0.0) {
      absxk = b_A[ii];
      scale = rt_hypotd_snf(absxk, smax);
      if (absxk >= 0.0) {
        scale = -scale;
      }
      if (std::abs(scale) < 1.0020841800044864E-292) {
        kend = 0;
        b_i = (ii - i) + 120;
        do {
          kend++;
          for (lastc = ix0; lastc <= b_i; lastc++) {
            b_A[lastc - 1] *= 9.9792015476736E+291;
          }
          scale *= 9.9792015476736E+291;
          t *= 9.9792015476736E+291;
        } while ((std::abs(scale) < 1.0020841800044864E-292) && (kend < 20));
        scale = rt_hypotd_snf(t, internal::blas::xnrm2(119 - i, b_A, ii + 2));
        if (t >= 0.0) {
          scale = -scale;
        }
        tau[i] = (scale - t) / scale;
        smax = 1.0 / (t - scale);
        for (lastc = ix0; lastc <= b_i; lastc++) {
          b_A[lastc - 1] *= smax;
        }
        for (lastc = 0; lastc < kend; lastc++) {
          scale *= 1.0020841800044864E-292;
        }
        t = scale;
      } else {
        tau[i] = (scale - absxk) / scale;
        smax = 1.0 / (absxk - scale);
        b_i = (ii - i) + 120;
        for (lastc = ix0; lastc <= b_i; lastc++) {
          b_A[lastc - 1] *= smax;
        }
        t = scale;
      }
    }
    b_A[ii] = t;
    if (i + 1 < 15) {
      int lastv;
      b_A[ii] = 1.0;
      iy = ii + 121;
      if (tau[i] != 0.0) {
        boolean_T exitg2;
        lastv = 120 - i;
        kend = (ii - i) + 119;
        while ((lastv > 0) && (b_A[kend] == 0.0)) {
          lastv--;
          kend--;
        }
        lastc = 13 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc + 1 > 0)) {
          int exitg1;
          kend = (ii + lastc * 120) + 120;
          rankA = kend;
          do {
            exitg1 = 0;
            if (rankA + 1 <= kend + lastv) {
              if (b_A[rankA] != 0.0) {
                exitg1 = 1;
              } else {
                rankA++;
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
        lastc = -1;
      }
      if (lastv > 0) {
        if (lastc + 1 != 0) {
          if (0 <= lastc) {
            std::memset(&work[0], 0, (lastc + 1) * sizeof(double));
          }
          b_i = (ii + 120 * lastc) + 121;
          for (ix0 = iy; ix0 <= b_i; ix0 += 120) {
            smax = 0.0;
            pvt = (ix0 + lastv) - 1;
            for (rankA = ix0; rankA <= pvt; rankA++) {
              smax += b_A[rankA - 1] * b_A[(ii + rankA) - ix0];
            }
            kend = div_nde_s32_floor((ix0 - ii) - 121, 120);
            work[kend] += smax;
          }
        }
        if (!(-tau[i] == 0.0)) {
          kend = ii;
          for (j = 0; j <= lastc; j++) {
            absxk = work[j];
            if (absxk != 0.0) {
              smax = absxk * -tau[i];
              b_i = kend + 121;
              pvt = lastv + kend;
              for (rankA = b_i; rankA <= pvt + 120; rankA++) {
                b_A[rankA - 1] += b_A[((ii + rankA) - kend) - 121] * smax;
              }
            }
            kend += 120;
          }
        }
      }
      b_A[ii] = t;
    }
    for (j = ip1; j < 16; j++) {
      kend = i + (j - 1) * 120;
      absxk = vn1[j - 1];
      if (absxk != 0.0) {
        smax = std::abs(b_A[kend]) / absxk;
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }
        scale = absxk / vn2[j - 1];
        scale = smax * (scale * scale);
        if (scale <= 1.4901161193847656E-8) {
          absxk = internal::blas::xnrm2(119 - i, b_A, kend + 2);
          vn1[j - 1] = absxk;
          vn2[j - 1] = absxk;
        } else {
          vn1[j - 1] = absxk * std::sqrt(smax);
        }
      }
    }
  }
  rankA = 0;
  smax = 2.6645352591003757E-13 * std::abs(b_A[0]);
  while ((rankA < 15) && (!(std::abs(b_A[rankA + 120 * rankA]) <= smax))) {
    rankA++;
  }
  std::copy(&B[0], &B[120], &b_B[0]);
  for (j = 0; j < 15; j++) {
    Y[j] = 0.0;
    if (tau[j] != 0.0) {
      smax = b_B[j];
      b_i = j + 2;
      for (i = b_i; i < 121; i++) {
        smax += b_A[(i + 120 * j) - 1] * b_B[i - 1];
      }
      smax *= tau[j];
      if (smax != 0.0) {
        b_B[j] -= smax;
        for (i = b_i; i < 121; i++) {
          b_B[i - 1] -= b_A[(i + 120 * j) - 1] * smax;
        }
      }
    }
  }
  for (i = 0; i < rankA; i++) {
    Y[jpvt[i] - 1] = b_B[i];
  }
  for (j = rankA; j >= 1; j--) {
    kend = jpvt[j - 1] - 1;
    iy = 120 * (j - 1);
    Y[kend] /= b_A[(j + iy) - 1];
    for (i = 0; i <= j - 2; i++) {
      ix0 = jpvt[i] - 1;
      Y[ix0] -= Y[kend] * b_A[i + iy];
    }
  }
}

} // namespace coder

// End of code generation (mldivide.cpp)
