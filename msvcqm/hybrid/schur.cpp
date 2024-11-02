//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// schur.cpp
//
// Code generation for function 'schur'
//

// Include files
#include "schur.h"
#include "hybrid_rtwutil.h"
#include "rt_nonfinite.h"
#include "xgerc.h"
#include "xhseqr.h"
#include "xnrm2.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
namespace coder {
void schur(const double A[9], double V[9], double T[9])
{
  double work[3];
  double tau[2];
  int k;
  boolean_T p;
  p = true;
  for (k = 0; k < 9; k++) {
    if ((!p) || (std::isinf(A[k]) || std::isnan(A[k]))) {
      p = false;
    }
  }
  if (!p) {
    int b_i;
    int i;
    for (i = 0; i < 9; i++) {
      V[i] = rtNaN;
    }
    b_i = 2;
    for (k = 0; k < 2; k++) {
      if (b_i <= 3) {
        std::memset(&V[(k * 3 + b_i) + -1], 0, (-b_i + 4) * sizeof(double));
      }
      b_i++;
    }
    for (i = 0; i < 9; i++) {
      T[i] = rtNaN;
    }
  } else {
    double temp;
    int b_i;
    int c_i;
    int exitg1;
    int i;
    int ia;
    int knt;
    int lastc;
    int lastv;
    std::copy(&A[0], &A[9], &T[0]);
    work[0] = 0.0;
    work[1] = 0.0;
    work[2] = 0.0;
    for (c_i = 0; c_i < 2; c_i++) {
      double b_alpha1_tmp;
      int alpha1_tmp;
      int i1;
      int ic0;
      int in;
      int iv0_tmp;
      boolean_T exitg2;
      b_i = c_i * 3 + 3;
      in = (c_i + 1) * 3;
      alpha1_tmp = (c_i + 3 * c_i) + 1;
      b_alpha1_tmp = T[alpha1_tmp];
      tau[c_i] = 0.0;
      temp = internal::blas::b_xnrm2(1 - c_i, T, b_i);
      if (temp != 0.0) {
        double beta1;
        beta1 = rt_hypotd_snf(b_alpha1_tmp, temp);
        if (b_alpha1_tmp >= 0.0) {
          beta1 = -beta1;
        }
        if (std::abs(beta1) < 1.0020841800044864E-292) {
          knt = 0;
          i = b_i - c_i;
          do {
            knt++;
            for (k = b_i; k <= i; k++) {
              T[k - 1] *= 9.9792015476736E+291;
            }
            beta1 *= 9.9792015476736E+291;
            b_alpha1_tmp *= 9.9792015476736E+291;
          } while ((std::abs(beta1) < 1.0020841800044864E-292) && (knt < 20));
          beta1 = rt_hypotd_snf(b_alpha1_tmp,
                                internal::blas::b_xnrm2(1 - c_i, T, b_i));
          if (b_alpha1_tmp >= 0.0) {
            beta1 = -beta1;
          }
          tau[c_i] = (beta1 - b_alpha1_tmp) / beta1;
          temp = 1.0 / (b_alpha1_tmp - beta1);
          for (k = b_i; k <= i; k++) {
            T[k - 1] *= temp;
          }
          for (k = 0; k < knt; k++) {
            beta1 *= 1.0020841800044864E-292;
          }
          b_alpha1_tmp = beta1;
        } else {
          tau[c_i] = (beta1 - b_alpha1_tmp) / beta1;
          temp = 1.0 / (b_alpha1_tmp - beta1);
          i = b_i - c_i;
          for (k = b_i; k <= i; k++) {
            T[k - 1] *= temp;
          }
          b_alpha1_tmp = beta1;
        }
      }
      T[alpha1_tmp] = 1.0;
      iv0_tmp = c_i + b_i;
      ic0 = in + 1;
      if (tau[c_i] != 0.0) {
        lastv = 1 - c_i;
        b_i = (iv0_tmp - c_i) - 2;
        while ((lastv + 1 > 0) && (T[b_i + 1] == 0.0)) {
          lastv--;
          b_i--;
        }
        lastc = 3;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          knt = in + lastc;
          ia = knt;
          do {
            exitg1 = 0;
            if (ia <= knt + lastv * 3) {
              if (T[ia - 1] != 0.0) {
                exitg1 = 1;
              } else {
                ia += 3;
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
        lastv = -1;
        lastc = 0;
      }
      if (lastv + 1 > 0) {
        if (lastc != 0) {
          if (0 <= lastc - 1) {
            std::memset(&work[0], 0, lastc * sizeof(double));
          }
          knt = iv0_tmp - 2;
          i = (in + 3 * lastv) + 1;
          for (b_i = ic0; b_i <= i; b_i += 3) {
            i1 = (b_i + lastc) - 1;
            for (ia = b_i; ia <= i1; ia++) {
              k = ia - b_i;
              work[k] += T[ia - 1] * T[knt];
            }
            knt++;
          }
        }
        if (!(-tau[c_i] == 0.0)) {
          knt = in;
          for (k = 0; k <= lastv; k++) {
            temp = T[(iv0_tmp + k) - 2];
            if (temp != 0.0) {
              temp *= -tau[c_i];
              i = knt + 1;
              i1 = lastc + knt;
              for (b_i = i; b_i <= i1; b_i++) {
                T[b_i - 1] += work[(b_i - knt) - 1] * temp;
              }
            }
            knt += 3;
          }
        }
      }
      ic0 = (c_i + in) + 2;
      if (tau[c_i] != 0.0) {
        lastv = 2 - c_i;
        b_i = (iv0_tmp - c_i) - 1;
        while ((lastv > 0) && (T[b_i] == 0.0)) {
          lastv--;
          b_i--;
        }
        lastc = 2 - c_i;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          knt = ic0 + (lastc - 1) * 3;
          ia = knt;
          do {
            exitg1 = 0;
            if (ia <= (knt + lastv) - 1) {
              if (T[ia - 1] != 0.0) {
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
        if (lastc != 0) {
          if (0 <= lastc - 1) {
            std::memset(&work[0], 0, lastc * sizeof(double));
          }
          i = ic0 + 3 * (lastc - 1);
          for (b_i = ic0; b_i <= i; b_i += 3) {
            temp = 0.0;
            i1 = (b_i + lastv) - 1;
            for (ia = b_i; ia <= i1; ia++) {
              temp += T[ia - 1] * T[((iv0_tmp + ia) - b_i) - 2];
            }
            k = div_nde_s32_floor(b_i - ic0, 3);
            work[k] += temp;
          }
        }
        internal::blas::xgerc(lastv, lastc, -tau[c_i], iv0_tmp - 1, work, T,
                              ic0);
      }
      T[alpha1_tmp] = b_alpha1_tmp;
    }
    std::copy(&T[0], &T[9], &V[0]);
    for (k = 1; k >= 0; k--) {
      ia = (k + 1) * 3;
      for (c_i = 0; c_i <= k; c_i++) {
        V[ia + c_i] = 0.0;
      }
      i = k + 3;
      for (c_i = i; c_i < 4; c_i++) {
        V[ia + 2] = V[ia - 1];
      }
    }
    V[1] = 0.0;
    V[2] = 0.0;
    V[0] = 1.0;
    work[0] = 0.0;
    work[1] = 0.0;
    work[2] = 0.0;
    for (c_i = 1; c_i >= 0; c_i--) {
      knt = (c_i + c_i * 3) + 8;
      if (c_i + 1 < 2) {
        V[knt - 4] = 1.0;
        if (tau[c_i] != 0.0) {
          lastv = 2;
          b_i = knt;
          while ((lastv > 0) && (V[b_i - 3] == 0.0)) {
            lastv--;
            b_i--;
          }
          lastc = 1;
          ia = knt;
          do {
            exitg1 = 0;
            if (ia <= (knt + lastv) - 1) {
              if (V[ia - 1] != 0.0) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc = 0;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        } else {
          lastv = 0;
          lastc = 0;
        }
        if (lastv > 0) {
          if (lastc != 0) {
            work[0] = 0.0;
            for (b_i = knt; b_i <= knt; b_i += 3) {
              temp = 0.0;
              i = (b_i + lastv) - 1;
              for (ia = b_i; ia <= i; ia++) {
                temp += V[ia - 1] * V[((knt + ia) - b_i) - 4];
              }
              k = div_nde_s32_floor(b_i - knt, 3);
              work[k] += temp;
            }
          }
          internal::blas::xgerc(lastv, lastc, -tau[c_i], knt - 3, work, V, knt);
        }
        b_i = knt - 2;
        for (k = b_i; k <= b_i; k++) {
          V[k - 1] *= -tau[c_i];
        }
      }
      V[knt - 4] = 1.0 - tau[c_i];
      if (0 <= c_i - 1) {
        V[knt - 5] = 0.0;
      }
    }
    internal::lapack::xhseqr(T, V);
  }
}

} // namespace coder

// End of code generation (schur.cpp)
