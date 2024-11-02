//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xzhgeqz.cpp
//
// Code generation for function 'xzhgeqz'
//

// Include files
#include "xzhgeqz.h"
#include "hybrid_data.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xzlartg.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace internal {
namespace reflapack {
void xzhgeqz(creal_T A[9], int ilo, int ihi, creal_T Z[9], int *info,
             creal_T alpha1[3], creal_T beta1[3])
{
  creal_T ctemp;
  creal_T stemp;
  creal_T y;
  double anorm;
  double ascale;
  double b_atol;
  double colscale;
  double colssq;
  double eshift_im;
  double eshift_re;
  double scale;
  double ssq;
  double t;
  int col;
  int i;
  int ilast;
  int j;
  int jp1;
  int nm1;
  int row;
  boolean_T failed;
  boolean_T guard1{false};
  boolean_T guard2{false};
  *info = 0;
  alpha1[0].re = 0.0;
  alpha1[0].im = 0.0;
  beta1[0].re = 1.0;
  beta1[0].im = 0.0;
  alpha1[1].re = 0.0;
  alpha1[1].im = 0.0;
  beta1[1].re = 1.0;
  beta1[1].im = 0.0;
  alpha1[2].re = 0.0;
  alpha1[2].im = 0.0;
  beta1[2].re = 1.0;
  beta1[2].im = 0.0;
  eshift_re = 0.0;
  eshift_im = 0.0;
  ctemp.re = 0.0;
  ctemp.im = 0.0;
  anorm = 0.0;
  if (ilo <= ihi) {
    scale = 3.3121686421112381E-170;
    ssq = 0.0;
    nm1 = ihi - ilo;
    for (j = 0; j <= nm1; j++) {
      colscale = 3.3121686421112381E-170;
      colssq = 0.0;
      col = (ilo + j) - 1;
      jp1 = j + 1;
      if (jp1 > nm1) {
        jp1 = nm1;
      }
      i = ilo + jp1;
      for (row = ilo; row <= i; row++) {
        jp1 = (row + 3 * col) - 1;
        anorm = std::abs(A[jp1].re);
        if (anorm > colscale) {
          t = colscale / anorm;
          colssq = colssq * t * t + 1.0;
          colscale = anorm;
        } else {
          t = anorm / colscale;
          colssq += t * t;
        }
        anorm = std::abs(A[jp1].im);
        if (anorm > colscale) {
          t = colscale / anorm;
          colssq = colssq * t * t + 1.0;
          colscale = anorm;
        } else {
          t = anorm / colscale;
          colssq += t * t;
        }
      }
      if (scale >= colscale) {
        t = colscale / scale;
        ssq += t * t * colssq;
      } else {
        t = scale / colscale;
        ssq = colssq + t * t * ssq;
        scale = colscale;
      }
    }
    anorm = scale * std::sqrt(ssq);
  }
  t = 2.2204460492503131E-16 * anorm;
  b_atol = 2.2250738585072014E-308;
  if (t > 2.2250738585072014E-308) {
    b_atol = t;
  }
  t = 2.2250738585072014E-308;
  if (anorm > 2.2250738585072014E-308) {
    t = anorm;
  }
  ascale = 1.0 / t;
  failed = true;
  i = ihi + 1;
  for (j = i; j < 4; j++) {
    alpha1[j - 1] = A[(j + 3 * (j - 1)) - 1];
  }
  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    int ifirst;
    int iiter;
    int ilastm1;
    int istart;
    int jiter;
    boolean_T goto60;
    boolean_T goto70;
    boolean_T goto90;
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1) - 1) {
        boolean_T b_guard1{false};
        boolean_T exitg2;
        b_guard1 = false;
        if (ilast + 1 == ilo) {
          goto60 = true;
          b_guard1 = true;
        } else {
          i = ilast + 3 * ilastm1;
          nm1 = ilast + 3 * ilast;
          jp1 = ilastm1 + 3 * ilastm1;
          if (std::abs(A[i].re) + std::abs(A[i].im) <=
              std::fmax(2.2250738585072014E-308,
                        2.2204460492503131E-16 *
                            ((std::abs(A[nm1].re) + std::abs(A[nm1].im)) +
                             (std::abs(A[jp1].re) + std::abs(A[jp1].im))))) {
            A[i].re = 0.0;
            A[i].im = 0.0;
            goto60 = true;
            b_guard1 = true;
          } else {
            boolean_T guard3{false};
            j = ilastm1;
            guard3 = false;
            exitg2 = false;
            while ((!exitg2) && (j + 1 >= ilo)) {
              if (j + 1 == ilo) {
                guard3 = true;
                exitg2 = true;
              } else {
                i = j + 3 * (j - 1);
                nm1 = j + 3 * j;
                if (std::abs(A[i].re) + std::abs(A[i].im) <=
                    std::fmax(2.2250738585072014E-308,
                              2.2204460492503131E-16 *
                                  ((std::abs(A[nm1].re) + std::abs(A[nm1].im)) +
                                   (std::abs(A[i - 1].re) +
                                    std::abs(A[i - 1].im))))) {
                  A[i].re = 0.0;
                  A[i].im = 0.0;
                  guard3 = true;
                  exitg2 = true;
                } else {
                  j--;
                  guard3 = false;
                }
              }
            }
            if (guard3) {
              ifirst = j + 1;
              goto70 = true;
            }
            if (goto70) {
              b_guard1 = true;
            } else {
              alpha1[0].re = rtNaN;
              alpha1[0].im = 0.0;
              beta1[0].re = rtNaN;
              beta1[0].im = 0.0;
              alpha1[1].re = rtNaN;
              alpha1[1].im = 0.0;
              beta1[1].re = rtNaN;
              beta1[1].im = 0.0;
              alpha1[2].re = rtNaN;
              alpha1[2].im = 0.0;
              beta1[2].re = rtNaN;
              beta1[2].im = 0.0;
              for (i = 0; i < 9; i++) {
                Z[i].re = rtNaN;
                Z[i].im = 0.0;
              }
              *info = 1;
              exitg1 = 1;
            }
          }
        }
        if (b_guard1) {
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = A[ilast + 3 * ilast];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              failed = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              eshift_re = 0.0;
              eshift_im = 0.0;
              jiter++;
            }
          } else {
            if (goto70) {
              double ad22_im;
              double ad22_re;
              goto70 = false;
              iiter++;
              if (iiter - iiter / 10 * 10 != 0) {
                jp1 = ilast + 3 * ilast;
                anorm = ascale * A[jp1].re;
                t = ascale * A[jp1].im;
                if (t == 0.0) {
                  ad22_re = anorm / 0.57735026918962584;
                  ad22_im = 0.0;
                } else if (anorm == 0.0) {
                  ad22_re = 0.0;
                  ad22_im = t / 0.57735026918962584;
                } else {
                  ad22_re = anorm / 0.57735026918962584;
                  ad22_im = t / 0.57735026918962584;
                }
                jp1 = ilastm1 + 3 * ilast;
                anorm = ascale * A[jp1].re;
                t = ascale * A[jp1].im;
                if (t == 0.0) {
                  stemp.re = anorm / 0.57735026918962584;
                  stemp.im = 0.0;
                } else if (anorm == 0.0) {
                  stemp.re = 0.0;
                  stemp.im = t / 0.57735026918962584;
                } else {
                  stemp.re = anorm / 0.57735026918962584;
                  stemp.im = t / 0.57735026918962584;
                }
                b_sqrt(&stemp);
                jp1 = ilast + 3 * ilastm1;
                anorm = ascale * A[jp1].re;
                t = ascale * A[jp1].im;
                if (t == 0.0) {
                  y.re = anorm / 0.57735026918962584;
                  y.im = 0.0;
                } else if (anorm == 0.0) {
                  y.re = 0.0;
                  y.im = t / 0.57735026918962584;
                } else {
                  y.re = anorm / 0.57735026918962584;
                  y.im = t / 0.57735026918962584;
                }
                b_sqrt(&y);
                ctemp.re = stemp.re * y.re - stemp.im * y.im;
                ctemp.im = stemp.re * y.im + stemp.im * y.re;
                if ((ctemp.re != 0.0) || (ctemp.im != 0.0)) {
                  double x_im;
                  jp1 = ilastm1 + 3 * ilastm1;
                  anorm = ascale * A[jp1].re;
                  t = ascale * A[jp1].im;
                  if (t == 0.0) {
                    anorm /= 0.57735026918962584;
                    t = 0.0;
                  } else if (anorm == 0.0) {
                    anorm = 0.0;
                    t /= 0.57735026918962584;
                  } else {
                    anorm /= 0.57735026918962584;
                    t /= 0.57735026918962584;
                  }
                  colssq = 0.5 * (anorm - ad22_re);
                  x_im = 0.5 * (t - ad22_im);
                  colscale = std::abs(colssq) + std::abs(x_im);
                  ssq = std::fmax(std::abs(ctemp.re) + std::abs(ctemp.im),
                                  colscale);
                  if (x_im == 0.0) {
                    stemp.re = colssq / ssq;
                    stemp.im = 0.0;
                  } else if (colssq == 0.0) {
                    stemp.re = 0.0;
                    stemp.im = x_im / ssq;
                  } else {
                    stemp.re = colssq / ssq;
                    stemp.im = x_im / ssq;
                  }
                  if (ctemp.im == 0.0) {
                    y.re = ctemp.re / ssq;
                    y.im = 0.0;
                  } else if (ctemp.re == 0.0) {
                    y.re = 0.0;
                    y.im = ctemp.im / ssq;
                  } else {
                    y.re = ctemp.re / ssq;
                    y.im = ctemp.im / ssq;
                  }
                  anorm = stemp.re * stemp.re - stemp.im * stemp.im;
                  t = stemp.re * stemp.im;
                  scale = y.re * y.im;
                  stemp.re = anorm + (y.re * y.re - y.im * y.im);
                  stemp.im = (t + t) + (scale + scale);
                  b_sqrt(&stemp);
                  y.re = ssq * stemp.re;
                  y.im = ssq * stemp.im;
                  if (colscale > 0.0) {
                    if (x_im == 0.0) {
                      t = colssq / colscale;
                      anorm = 0.0;
                    } else {
                      if (colssq == 0.0) {
                        t = 0.0;
                      } else {
                        t = colssq / colscale;
                      }
                      anorm = x_im / colscale;
                    }
                    if (t * y.re + anorm * y.im < 0.0) {
                      y.re = -y.re;
                      y.im = -y.im;
                    }
                  }
                  scale = colssq + y.re;
                  ssq = x_im + y.im;
                  if (ssq == 0.0) {
                    if (ctemp.im == 0.0) {
                      colssq = ctemp.re / scale;
                      anorm = 0.0;
                    } else if (ctemp.re == 0.0) {
                      colssq = 0.0;
                      anorm = ctemp.im / scale;
                    } else {
                      colssq = ctemp.re / scale;
                      anorm = ctemp.im / scale;
                    }
                  } else if (scale == 0.0) {
                    if (ctemp.re == 0.0) {
                      colssq = ctemp.im / ssq;
                      anorm = 0.0;
                    } else if (ctemp.im == 0.0) {
                      colssq = 0.0;
                      anorm = -(ctemp.re / ssq);
                    } else {
                      colssq = ctemp.im / ssq;
                      anorm = -(ctemp.re / ssq);
                    }
                  } else {
                    colscale = std::abs(scale);
                    anorm = std::abs(ssq);
                    if (colscale > anorm) {
                      t = ssq / scale;
                      anorm = scale + t * ssq;
                      colssq = (ctemp.re + t * ctemp.im) / anorm;
                      anorm = (ctemp.im - t * ctemp.re) / anorm;
                    } else if (anorm == colscale) {
                      if (scale > 0.0) {
                        t = 0.5;
                      } else {
                        t = -0.5;
                      }
                      if (ssq > 0.0) {
                        anorm = 0.5;
                      } else {
                        anorm = -0.5;
                      }
                      colssq = (ctemp.re * t + ctemp.im * anorm) / colscale;
                      anorm = (ctemp.im * t - ctemp.re * anorm) / colscale;
                    } else {
                      t = scale / ssq;
                      anorm = ssq + t * scale;
                      colssq = (t * ctemp.re + ctemp.im) / anorm;
                      anorm = (t * ctemp.im - ctemp.re) / anorm;
                    }
                  }
                  ad22_re -= ctemp.re * colssq - ctemp.im * anorm;
                  ad22_im -= ctemp.re * anorm + ctemp.im * colssq;
                }
              } else {
                if (iiter - iiter / 20 * 20 == 0) {
                  jp1 = ilast + 3 * ilast;
                  anorm = ascale * A[jp1].re;
                  t = ascale * A[jp1].im;
                  if (t == 0.0) {
                    anorm /= 0.57735026918962584;
                    t = 0.0;
                  } else if (anorm == 0.0) {
                    anorm = 0.0;
                    t /= 0.57735026918962584;
                  } else {
                    anorm /= 0.57735026918962584;
                    t /= 0.57735026918962584;
                  }
                  eshift_re += anorm;
                  eshift_im += t;
                } else {
                  jp1 = ilast + 3 * ilastm1;
                  anorm = ascale * A[jp1].re;
                  t = ascale * A[jp1].im;
                  if (t == 0.0) {
                    anorm /= 0.57735026918962584;
                    t = 0.0;
                  } else if (anorm == 0.0) {
                    anorm = 0.0;
                    t /= 0.57735026918962584;
                  } else {
                    anorm /= 0.57735026918962584;
                    t /= 0.57735026918962584;
                  }
                  eshift_re += anorm;
                  eshift_im += t;
                }
                ad22_re = eshift_re;
                ad22_im = eshift_im;
              }
              j = ilastm1;
              jp1 = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = j + 1;
                nm1 = j + 3 * j;
                ctemp.re = ascale * A[nm1].re - ad22_re * 0.57735026918962584;
                ctemp.im = ascale * A[nm1].im - ad22_im * 0.57735026918962584;
                ssq = std::abs(ctemp.re) + std::abs(ctemp.im);
                jp1 += 3 * j;
                colscale = ascale * (std::abs(A[jp1].re) + std::abs(A[jp1].im));
                anorm = ssq;
                if (colscale > ssq) {
                  anorm = colscale;
                }
                if ((anorm < 1.0) && (anorm != 0.0)) {
                  ssq /= anorm;
                  colscale /= anorm;
                }
                i = j + 3 * (j - 1);
                if ((std::abs(A[i].re) + std::abs(A[i].im)) * colscale <=
                    ssq * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  jp1 = j;
                  j--;
                }
              }
              if (!goto90) {
                istart = ifirst;
                nm1 = (ifirst + 3 * (ifirst - 1)) - 1;
                ctemp.re = ascale * A[nm1].re - ad22_re * 0.57735026918962584;
                ctemp.im = ascale * A[nm1].im - ad22_im * 0.57735026918962584;
              }
              goto90 = false;
              jp1 = istart + 3 * (istart - 1);
              stemp.re = ascale * A[jp1].re;
              stemp.im = ascale * A[jp1].im;
              xzlartg(ctemp, stemp, &scale, &y);
              j = istart;
              nm1 = istart - 2;
              while (j < ilast + 1) {
                if (j > istart) {
                  col = j + 3 * nm1;
                  xzlartg(A[3 * nm1 + 1], A[col], &scale, &y, &A[3 * nm1 + 1]);
                  A[col].re = 0.0;
                  A[col].im = 0.0;
                }
                for (nm1 = j; nm1 < 4; nm1++) {
                  row = j + 3 * (nm1 - 1);
                  anorm = A[row].im;
                  ssq = A[row].re;
                  colscale = A[row - 1].re;
                  stemp.re = scale * colscale + (y.re * ssq - y.im * anorm);
                  t = A[row - 1].im;
                  stemp.im = scale * t + (y.re * anorm + y.im * ssq);
                  A[row].re = scale * ssq - (y.re * colscale + y.im * t);
                  A[row].im = scale * A[row].im - (y.re * t - y.im * colscale);
                  A[row - 1] = stemp;
                }
                y.re = -y.re;
                y.im = -y.im;
                nm1 = j;
                if (ilast + 1 < j + 2) {
                  nm1 = ilast - 1;
                }
                for (jp1 = 1; jp1 <= nm1 + 2; jp1++) {
                  row = (jp1 + 3 * (j - 1)) - 1;
                  ssq = A[row].im;
                  anorm = A[row].re;
                  col = (jp1 + 3 * j) - 1;
                  t = A[col].re;
                  stemp.re = scale * t + (y.re * anorm - y.im * ssq);
                  colscale = A[col].im;
                  stemp.im = scale * colscale + (y.re * ssq + y.im * anorm);
                  A[row].re = scale * A[row].re - (y.re * t + y.im * colscale);
                  A[row].im = scale * A[row].im - (y.re * colscale - y.im * t);
                  A[col] = stemp;
                }
                row = 3 * (j - 1);
                anorm = Z[row].im;
                ssq = Z[row].re;
                colscale = Z[3 * j].re;
                stemp.re = scale * colscale + (y.re * ssq - y.im * anorm);
                t = Z[3 * j].im;
                stemp.im = scale * t + (y.re * anorm + y.im * ssq);
                Z[row].re = scale * ssq - (y.re * colscale + y.im * t);
                Z[row].im = scale * Z[row].im - (y.re * t - y.im * colscale);
                Z[3 * j] = stemp;
                anorm = Z[row + 1].im;
                ssq = Z[row + 1].re;
                col = 3 * j + 1;
                colscale = Z[col].re;
                stemp.re = scale * colscale + (y.re * ssq - y.im * anorm);
                t = Z[col].im;
                stemp.im = scale * t + (y.re * anorm + y.im * ssq);
                Z[row + 1].re = scale * ssq - (y.re * colscale + y.im * t);
                Z[row + 1].im =
                    scale * Z[row + 1].im - (y.re * t - y.im * colscale);
                Z[col] = stemp;
                anorm = Z[row + 2].im;
                ssq = Z[row + 2].re;
                col = 3 * j + 2;
                colscale = Z[col].re;
                stemp.re = scale * colscale + (y.re * ssq - y.im * anorm);
                t = Z[col].im;
                stemp.im = scale * t + (y.re * anorm + y.im * ssq);
                Z[row + 2].re = scale * ssq - (y.re * colscale + y.im * t);
                Z[row + 2].im =
                    scale * Z[row + 2].im - (y.re * t - y.im * colscale);
                Z[col] = stemp;
                nm1 = j - 1;
                j++;
              }
            }
            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }
  if (guard2) {
    if (failed) {
      *info = ilast + 1;
      for (jp1 = 0; jp1 <= ilast; jp1++) {
        alpha1[jp1].re = rtNaN;
        alpha1[jp1].im = 0.0;
        beta1[jp1].re = rtNaN;
        beta1[jp1].im = 0.0;
      }
      for (i = 0; i < 9; i++) {
        Z[i].re = rtNaN;
        Z[i].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }
  if (guard1) {
    for (j = 0; j <= ilo - 2; j++) {
      alpha1[j] = A[j + 3 * j];
    }
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

// End of code generation (xzhgeqz.cpp)
