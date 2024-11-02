//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// vlogR.cpp
//
// Code generation for function 'vlogR'
//

// Include files
#include "vlogR.h"
#include "hybrid_data.h"
#include "rt_nonfinite.h"
#include "schur.h"
#include "xzggev.h"
#include <cmath>

// Function Definitions
void vlogR(const double R[9], double w[3])
{
  creal_T At[9];
  creal_T V[9];
  creal_T alpha1[3];
  creal_T beta1[3];
  double T[9];
  double b_w[9];
  double D[3];
  double fai;
  double tr;
  int sgn;
  // w is the rotation axis of a rotation matrix R
  tr = (((R[0] + R[4]) + R[8]) - 1.0) / 2.0;
  if (tr > 1.0) {
    tr = 1.0;
  } else if (tr < -1.0) {
    tr = -1.0;
  }
  fai = std::acos(tr);
  if (std::abs(fai) < 1.0E-12) {
    w[0] = 0.0;
    w[1] = 0.0;
    w[2] = 0.0;
  } else if (std::abs(fai - 3.1415926535897931) < 1.0E-12) {
    double absxk;
    int i;
    int k;
    boolean_T exitg2;
    boolean_T p;
    //  11.17 comment: warning('Logarithm of rotation matrix with angle PI.' );
    p = true;
    for (k = 0; k < 9; k++) {
      if ((!p) || (std::isinf(R[k]) || std::isnan(R[k]))) {
        p = false;
      }
    }
    if (!p) {
      for (i = 0; i < 9; i++) {
        V[i].re = rtNaN;
        V[i].im = 0.0;
      }
      alpha1[0].re = rtNaN;
      alpha1[1].re = rtNaN;
      alpha1[2].re = rtNaN;
    } else {
      int exitg1;
      p = true;
      k = 0;
      exitg2 = false;
      while ((!exitg2) && (k < 3)) {
        sgn = 0;
        do {
          exitg1 = 0;
          if (sgn <= k) {
            if (!(R[sgn + 3 * k] == R[k + 3 * sgn])) {
              p = false;
              exitg1 = 1;
            } else {
              sgn++;
            }
          } else {
            k++;
            exitg1 = 2;
          }
        } while (exitg1 == 0);
        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
      if (p) {
        coder::schur(R, b_w, T);
        for (i = 0; i < 9; i++) {
          V[i].re = b_w[i];
          V[i].im = 0.0;
        }
        alpha1[0].re = T[0];
        alpha1[1].re = T[4];
        alpha1[2].re = T[8];
      } else {
        p = true;
        k = 0;
        exitg2 = false;
        while ((!exitg2) && (k < 3)) {
          sgn = 0;
          do {
            exitg1 = 0;
            if (sgn <= k) {
              if (!(R[sgn + 3 * k] == -R[k + 3 * sgn])) {
                p = false;
                exitg1 = 1;
              } else {
                sgn++;
              }
            } else {
              k++;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
        if (p) {
          coder::schur(R, b_w, T);
          sgn = 1;
          do {
            exitg1 = 0;
            if (sgn <= 3) {
              boolean_T guard1{false};
              guard1 = false;
              if (sgn != 3) {
                absxk = T[sgn + 3 * (sgn - 1)];
                if (absxk != 0.0) {
                  tr = std::abs(absxk);
                  alpha1[sgn - 1].re = 0.0;
                  alpha1[sgn - 1].im = tr;
                  alpha1[sgn].re = 0.0;
                  alpha1[sgn].im = -tr;
                  sgn += 2;
                } else {
                  guard1 = true;
                }
              } else {
                guard1 = true;
              }
              if (guard1) {
                alpha1[sgn - 1].re = 0.0;
                alpha1[sgn - 1].im = 0.0;
                sgn++;
              }
            } else {
              exitg1 = 1;
            }
          } while (exitg1 == 0);
          for (i = 0; i < 9; i++) {
            V[i].re = b_w[i];
            V[i].im = 0.0;
          }
          k = 1;
          do {
            exitg1 = 0;
            if (k <= 3) {
              if (k != 3) {
                i = 3 * (k - 1);
                if (T[k + i] != 0.0) {
                  double t;
                  int kend_tmp;
                  if (T[k + 3 * (k - 1)] < 0.0) {
                    sgn = 1;
                  } else {
                    sgn = -1;
                  }
                  tr = V[i].re;
                  t = static_cast<double>(sgn) * V[3 * k].re;
                  if (t == 0.0) {
                    V[i].re = tr / 1.4142135623730951;
                    V[i].im = 0.0;
                  } else if (tr == 0.0) {
                    V[i].re = 0.0;
                    V[i].im = t / 1.4142135623730951;
                  } else {
                    V[i].re = tr / 1.4142135623730951;
                    V[i].im = t / 1.4142135623730951;
                  }
                  V[3 * k].re = V[i].re;
                  V[3 * k].im = -V[i].im;
                  tr = V[i + 1].re;
                  kend_tmp = 3 * k + 1;
                  t = static_cast<double>(sgn) * V[kend_tmp].re;
                  if (t == 0.0) {
                    V[i + 1].re = tr / 1.4142135623730951;
                    V[i + 1].im = 0.0;
                  } else if (tr == 0.0) {
                    V[i + 1].re = 0.0;
                    V[i + 1].im = t / 1.4142135623730951;
                  } else {
                    V[i + 1].re = tr / 1.4142135623730951;
                    V[i + 1].im = t / 1.4142135623730951;
                  }
                  V[kend_tmp].re = V[i + 1].re;
                  V[kend_tmp].im = -V[i + 1].im;
                  tr = V[i + 2].re;
                  kend_tmp = 3 * k + 2;
                  t = static_cast<double>(sgn) * V[kend_tmp].re;
                  if (t == 0.0) {
                    V[i + 2].re = tr / 1.4142135623730951;
                    V[i + 2].im = 0.0;
                  } else if (tr == 0.0) {
                    V[i + 2].re = 0.0;
                    V[i + 2].im = t / 1.4142135623730951;
                  } else {
                    V[i + 2].re = tr / 1.4142135623730951;
                    V[i + 2].im = t / 1.4142135623730951;
                  }
                  V[kend_tmp].re = V[i + 2].re;
                  V[kend_tmp].im = -V[i + 2].im;
                  k += 2;
                } else {
                  k++;
                }
              } else {
                k++;
              }
            } else {
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        } else {
          double colnorm;
          for (i = 0; i < 9; i++) {
            At[i].re = R[i];
            At[i].im = 0.0;
          }
          coder::internal::reflapack::xzggev(At, &sgn, alpha1, beta1, V);
          for (sgn = 0; sgn <= 6; sgn += 3) {
            double t;
            int kend_tmp;
            colnorm = 0.0;
            tr = 3.3121686421112381E-170;
            kend_tmp = sgn + 3;
            for (k = sgn + 1; k <= kend_tmp; k++) {
              absxk = std::abs(V[k - 1].re);
              if (absxk > tr) {
                t = tr / absxk;
                colnorm = colnorm * t * t + 1.0;
                tr = absxk;
              } else {
                t = absxk / tr;
                colnorm += t * t;
              }
              absxk = std::abs(V[k - 1].im);
              if (absxk > tr) {
                t = tr / absxk;
                colnorm = colnorm * t * t + 1.0;
                tr = absxk;
              } else {
                t = absxk / tr;
                colnorm += t * t;
              }
            }
            colnorm = tr * std::sqrt(colnorm);
            for (k = sgn + 1; k <= kend_tmp; k++) {
              tr = V[k - 1].re;
              t = V[k - 1].im;
              if (t == 0.0) {
                absxk = tr / colnorm;
                tr = 0.0;
              } else if (tr == 0.0) {
                absxk = 0.0;
                tr = t / colnorm;
              } else {
                absxk = tr / colnorm;
                tr = t / colnorm;
              }
              V[k - 1].re = absxk;
              V[k - 1].im = tr;
            }
          }
          if (beta1[0].im == 0.0) {
            if (alpha1[0].im == 0.0) {
              absxk = alpha1[0].re / beta1[0].re;
            } else if (alpha1[0].re == 0.0) {
              absxk = 0.0;
            } else {
              absxk = alpha1[0].re / beta1[0].re;
            }
          } else if (beta1[0].re == 0.0) {
            if (alpha1[0].re == 0.0) {
              absxk = alpha1[0].im / beta1[0].im;
            } else if (alpha1[0].im == 0.0) {
              absxk = 0.0;
            } else {
              absxk = alpha1[0].im / beta1[0].im;
            }
          } else {
            tr = std::abs(beta1[0].re);
            absxk = std::abs(beta1[0].im);
            if (tr > absxk) {
              tr = beta1[0].im / beta1[0].re;
              absxk = (alpha1[0].re + tr * alpha1[0].im) /
                      (beta1[0].re + tr * beta1[0].im);
            } else if (absxk == tr) {
              if (beta1[0].re > 0.0) {
                colnorm = 0.5;
              } else {
                colnorm = -0.5;
              }
              if (beta1[0].im > 0.0) {
                absxk = 0.5;
              } else {
                absxk = -0.5;
              }
              absxk = (alpha1[0].re * colnorm + alpha1[0].im * absxk) / tr;
            } else {
              tr = beta1[0].re / beta1[0].im;
              absxk = (tr * alpha1[0].re + alpha1[0].im) /
                      (beta1[0].im + tr * beta1[0].re);
            }
          }
          alpha1[0].re = absxk;
          if (beta1[1].im == 0.0) {
            if (alpha1[1].im == 0.0) {
              absxk = alpha1[1].re / beta1[1].re;
            } else if (alpha1[1].re == 0.0) {
              absxk = 0.0;
            } else {
              absxk = alpha1[1].re / beta1[1].re;
            }
          } else if (beta1[1].re == 0.0) {
            if (alpha1[1].re == 0.0) {
              absxk = alpha1[1].im / beta1[1].im;
            } else if (alpha1[1].im == 0.0) {
              absxk = 0.0;
            } else {
              absxk = alpha1[1].im / beta1[1].im;
            }
          } else {
            tr = std::abs(beta1[1].re);
            absxk = std::abs(beta1[1].im);
            if (tr > absxk) {
              tr = beta1[1].im / beta1[1].re;
              absxk = (alpha1[1].re + tr * alpha1[1].im) /
                      (beta1[1].re + tr * beta1[1].im);
            } else if (absxk == tr) {
              if (beta1[1].re > 0.0) {
                colnorm = 0.5;
              } else {
                colnorm = -0.5;
              }
              if (beta1[1].im > 0.0) {
                absxk = 0.5;
              } else {
                absxk = -0.5;
              }
              absxk = (alpha1[1].re * colnorm + alpha1[1].im * absxk) / tr;
            } else {
              tr = beta1[1].re / beta1[1].im;
              absxk = (tr * alpha1[1].re + alpha1[1].im) /
                      (beta1[1].im + tr * beta1[1].re);
            }
          }
          alpha1[1].re = absxk;
          if (beta1[2].im == 0.0) {
            if (alpha1[2].im == 0.0) {
              absxk = alpha1[2].re / beta1[2].re;
            } else if (alpha1[2].re == 0.0) {
              absxk = 0.0;
            } else {
              absxk = alpha1[2].re / beta1[2].re;
            }
          } else if (beta1[2].re == 0.0) {
            if (alpha1[2].re == 0.0) {
              absxk = alpha1[2].im / beta1[2].im;
            } else if (alpha1[2].im == 0.0) {
              absxk = 0.0;
            } else {
              absxk = alpha1[2].im / beta1[2].im;
            }
          } else {
            tr = std::abs(beta1[2].re);
            absxk = std::abs(beta1[2].im);
            if (tr > absxk) {
              tr = beta1[2].im / beta1[2].re;
              absxk = (alpha1[2].re + tr * alpha1[2].im) /
                      (beta1[2].re + tr * beta1[2].im);
            } else if (absxk == tr) {
              if (beta1[2].re > 0.0) {
                colnorm = 0.5;
              } else {
                colnorm = -0.5;
              }
              if (beta1[2].im > 0.0) {
                absxk = 0.5;
              } else {
                absxk = -0.5;
              }
              absxk = (alpha1[2].re * colnorm + alpha1[2].im * absxk) / tr;
            } else {
              tr = beta1[2].re / beta1[2].im;
              absxk = (tr * alpha1[2].re + alpha1[2].im) /
                      (beta1[2].im + tr * beta1[2].re);
            }
          }
          alpha1[2].re = absxk;
        }
      }
    }
    D[0] = alpha1[0].re;
    D[1] = alpha1[1].re;
    D[2] = alpha1[2].re;
    for (i = 0; i < 9; i++) {
      b_w[i] = V[i].re;
    }
    if (!std::isnan(alpha1[0].re)) {
      sgn = 1;
    } else {
      sgn = 0;
      k = 2;
      exitg2 = false;
      while ((!exitg2) && (k < 4)) {
        if (!std::isnan(D[k - 1])) {
          sgn = k;
          exitg2 = true;
        } else {
          k++;
        }
      }
    }
    if (sgn == 0) {
      tr = alpha1[0].re;
    } else {
      tr = D[sgn - 1];
      i = sgn + 1;
      for (k = i; k < 4; k++) {
        absxk = D[k - 1];
        if (tr < absxk) {
          tr = absxk;
        }
      }
    }
    if (tr == alpha1[0].re) {
      w[0] = b_w[0];
      w[1] = b_w[1];
      w[2] = b_w[2];
    } else if (tr == alpha1[1].re) {
      w[0] = b_w[3];
      w[1] = b_w[4];
      w[2] = b_w[5];
    } else {
      w[0] = b_w[6];
      w[1] = b_w[7];
      w[2] = b_w[8];
    }
    absxk = std::cos(fai);
    tr = std::sin(fai);
    // SKEW Create skew-symmetric matrix
    //
    //  S = SKEW(V) is a skew-symmetric matrix formed from V (3x1).
    //
    //            | 0   -vz  vy|
    //            | vz   0  -vx|
    //            |-vy   vx  0 |
    //
    //  See also VEX.
    //  Copyright (C) 1993-2011, by Peter I. Corke
    //
    //  This file is part of The Robotics Toolbox for Matlab (RTB).
    //
    //  RTB is free software: you can redistribute it and/or modify
    //  it under the terms of the GNU Lesser General Public License as published
    //  by the Free Software Foundation, either version 3 of the License, or (at
    //  your option) any later version.
    //
    //  RTB is distributed in the hope that it will be useful,
    //  but WITHOUT ANY WARRANTY; without even the implied warranty of
    //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    //  GNU Lesser General Public License for more details.
    //
    //  You should have received a copy of the GNU Leser General Public License
    //  along with RTB.  If not, see <http://www.gnu.org/licenses/>.
    //  SO(3) case
    for (i = 0; i < 3; i++) {
      b_w[3 * i] = w[0] * w[i];
      b_w[3 * i + 1] = w[1] * w[i];
      b_w[3 * i + 2] = w[2] * w[i];
    }
    T[0] = tr * 0.0;
    T[3] = tr * -w[2];
    T[6] = tr * w[1];
    T[1] = tr * w[2];
    T[4] = tr * 0.0;
    T[7] = tr * -w[0];
    T[2] = tr * -w[1];
    T[5] = tr * w[0];
    T[8] = tr * 0.0;
    for (i = 0; i < 9; i++) {
      b_w[i] = ((absxk * static_cast<double>(iv[i]) + (1.0 - absxk) * b_w[i]) +
                T[i]) -
               R[i];
    }
    for (k = 0; k < 3; k++) {
      absxk = b_w[3 * k];
      D[k] = absxk;
      tr = b_w[3 * k + 1];
      if (std::isnan(tr)) {
        p = false;
      } else if (std::isnan(absxk)) {
        p = true;
      } else {
        p = (absxk < tr);
      }
      if (p) {
        absxk = tr;
        D[k] = tr;
      }
      tr = b_w[3 * k + 2];
      if (std::isnan(tr)) {
        p = false;
      } else if (std::isnan(absxk)) {
        p = true;
      } else {
        p = (absxk < tr);
      }
      if (p) {
        D[k] = tr;
      }
    }
    if (!std::isnan(D[0])) {
      sgn = 1;
    } else {
      sgn = 0;
      k = 2;
      exitg2 = false;
      while ((!exitg2) && (k < 4)) {
        if (!std::isnan(D[k - 1])) {
          sgn = k;
          exitg2 = true;
        } else {
          k++;
        }
      }
    }
    if (sgn == 0) {
      tr = D[0];
    } else {
      tr = D[sgn - 1];
      i = sgn + 1;
      for (k = i; k < 4; k++) {
        absxk = D[k - 1];
        if (tr < absxk) {
          tr = absxk;
        }
      }
    }
    if (tr > 1.0E-12) {
      w[0] = -w[0];
      w[1] = -w[1];
      w[2] = -w[2];
    }
    w[0] *= fai;
    w[1] *= fai;
    w[2] *= fai;
  } else {
    tr = fai / (2.0 * std::sin(fai));
    w[0] = tr * (R[5] - R[7]);
    w[1] = tr * (R[6] - R[2]);
    w[2] = tr * (R[1] - R[3]);
  }
}

// End of code generation (vlogR.cpp)
