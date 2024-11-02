//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xhseqr.cpp
//
// Code generation for function 'xhseqr'
//

// Include files
#include "xhseqr.h"
#include "hybrid_rtwutil.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xnrm2.h"
#include "xrot.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace internal {
namespace lapack {
int xhseqr(double h[9], double z[9])
{
  double v[3];
  double aa;
  double ab;
  double ba;
  double bb;
  double d;
  double h22;
  double rt1r;
  double s;
  double tst;
  int i;
  int info;
  int kdefl;
  boolean_T exitg1;
  info = 0;
  v[0] = 0.0;
  v[1] = 0.0;
  v[2] = 0.0;
  h[2] = 0.0;
  kdefl = 0;
  i = 2;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    int b_i;
    int b_k;
    int hoffset;
    int its;
    int k;
    int knt;
    int nr;
    boolean_T exitg2;
    boolean_T goto150;
    k = -1;
    goto150 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      boolean_T exitg3;
      k = i - 1;
      exitg3 = false;
      while ((!exitg3) && (k + 2 > 1)) {
        b_i = k + 3 * k;
        ba = std::abs(h[b_i + 1]);
        if (ba <= 3.0062525400134592E-292) {
          exitg3 = true;
        } else {
          knt = 3 * (k + 1);
          nr = k + knt;
          bb = std::abs(h[nr + 1]);
          tst = std::abs(h[b_i]) + bb;
          if (tst == 0.0) {
            if (k >= 1) {
              tst = std::abs(h[k]);
            }
            if (k + 3 <= 3) {
              tst += std::abs(h[knt + 2]);
            }
          }
          if (ba <= 2.2204460492503131E-16 * tst) {
            tst = std::abs(h[nr]);
            if (ba > tst) {
              ab = ba;
              ba = tst;
            } else {
              ab = tst;
            }
            tst = std::abs(h[b_i] - h[nr + 1]);
            if (bb > tst) {
              aa = bb;
              bb = tst;
            } else {
              aa = tst;
            }
            s = aa + ab;
            if (ba * (ab / s) <=
                std::fmax(3.0062525400134592E-292,
                          2.2204460492503131E-16 * (bb * (aa / s)))) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }
      if (k + 2 > 1) {
        h[(k + 3 * k) + 1] = 0.0;
      }
      if (k + 2 >= i) {
        goto150 = true;
        exitg2 = true;
      } else {
        int m;
        kdefl++;
        if (kdefl - kdefl / 20 * 20 == 0) {
          s = std::abs(h[i + 3 * (i - 1)]) + std::abs(h[i - 1]);
          tst = 0.75 * s + h[i + 3 * i];
          aa = -0.4375 * s;
          ab = s;
          h22 = tst;
        } else if (kdefl - kdefl / 10 * 10 == 0) {
          s = std::abs(h[1]) + std::abs(h[5]);
          tst = 0.75 * s + h[0];
          aa = -0.4375 * s;
          ab = s;
          h22 = tst;
        } else {
          knt = i + 3 * (i - 1);
          tst = h[knt - 1];
          ab = h[knt];
          aa = h[(i + 3 * i) - 1];
          h22 = h[i + 3 * i];
        }
        s = ((std::abs(tst) + std::abs(aa)) + std::abs(ab)) + std::abs(h22);
        if (s == 0.0) {
          rt1r = 0.0;
          tst = 0.0;
          bb = 0.0;
          ab = 0.0;
        } else {
          tst /= s;
          ab /= s;
          aa /= s;
          h22 /= s;
          ba = (tst + h22) / 2.0;
          tst = (tst - ba) * (h22 - ba) - aa * ab;
          ab = std::sqrt(std::abs(tst));
          if (tst >= 0.0) {
            rt1r = ba * s;
            bb = rt1r;
            tst = ab * s;
            ab = -tst;
          } else {
            rt1r = ba + ab;
            bb = ba - ab;
            if (std::abs(rt1r - h22) <= std::abs(bb - h22)) {
              rt1r *= s;
              bb = rt1r;
            } else {
              bb *= s;
              rt1r = bb;
            }
            tst = 0.0;
            ab = 0.0;
          }
        }
        m = i - 1;
        if (i - 1 >= 1) {
          aa = h[0] - bb;
          s = (std::abs(aa) + std::abs(ab)) + std::abs(h[1]);
          ba = h[1] / s;
          v[0] = (ba * h[3] + (h[0] - rt1r) * (aa / s)) - tst * (ab / s);
          v[1] = ba * (((h[0] + h[4]) - rt1r) - bb);
          v[2] = ba * h[5];
          s = (std::abs(v[0]) + std::abs(v[1])) + std::abs(v[2]);
          v[0] /= s;
          v[1] /= s;
          v[2] /= s;
        }
        for (b_k = m; b_k <= i; b_k++) {
          nr = (i - b_k) + 2;
          if (3 <= nr) {
            nr = 3;
          }
          if (b_k > i - 1) {
            hoffset = (b_k + 3 * (b_k - 2)) - 1;
            for (knt = 0; knt < nr; knt++) {
              v[knt] = h[knt + hoffset];
            }
          }
          ab = v[0];
          bb = 0.0;
          if (nr > 0) {
            tst = blas::xnrm2(nr - 1, v);
            if (tst != 0.0) {
              aa = rt_hypotd_snf(v[0], tst);
              if (v[0] >= 0.0) {
                aa = -aa;
              }
              if (std::abs(aa) < 1.0020841800044864E-292) {
                knt = 0;
                do {
                  knt++;
                  for (hoffset = 2; hoffset <= nr; hoffset++) {
                    v[hoffset - 1] *= 9.9792015476736E+291;
                  }
                  aa *= 9.9792015476736E+291;
                  ab *= 9.9792015476736E+291;
                } while ((std::abs(aa) < 1.0020841800044864E-292) &&
                         (knt < 20));
                aa = rt_hypotd_snf(ab, blas::xnrm2(nr - 1, v));
                if (ab >= 0.0) {
                  aa = -aa;
                }
                bb = (aa - ab) / aa;
                tst = 1.0 / (ab - aa);
                for (hoffset = 2; hoffset <= nr; hoffset++) {
                  v[hoffset - 1] *= tst;
                }
                for (hoffset = 0; hoffset < knt; hoffset++) {
                  aa *= 1.0020841800044864E-292;
                }
                ab = aa;
              } else {
                bb = (aa - v[0]) / aa;
                tst = 1.0 / (v[0] - aa);
                for (hoffset = 2; hoffset <= nr; hoffset++) {
                  v[hoffset - 1] *= tst;
                }
                ab = aa;
              }
            }
          }
          v[0] = ab;
          if (b_k > i - 1) {
            h[b_k - 1] = ab;
            h[b_k] = 0.0;
            if (b_k < i) {
              h[2] = 0.0;
            }
          }
          s = v[1];
          tst = bb * v[1];
          if (nr == 3) {
            d = v[2];
            ba = bb * v[2];
            for (knt = b_k; knt < 4; knt++) {
              nr = 3 * (knt - 1);
              hoffset = b_k + nr;
              aa = (h[hoffset - 1] + s * h[hoffset]) + d * h[nr + 2];
              h[hoffset - 1] -= aa * bb;
              h[hoffset] -= aa * tst;
              h[nr + 2] -= aa * ba;
            }
            if (b_k + 3 <= i + 1) {
              b_i = b_k + 2;
            } else {
              b_i = i;
            }
            for (knt = 0; knt <= b_i; knt++) {
              hoffset = knt + 3 * (b_k - 1);
              nr = knt + 3 * b_k;
              aa = (h[hoffset] + s * h[nr]) + d * h[knt + 6];
              h[hoffset] -= aa * bb;
              h[nr] -= aa * tst;
              h[knt + 6] -= aa * ba;
            }
            for (knt = 0; knt < 3; knt++) {
              hoffset = knt + 3 * (b_k - 1);
              ab = z[hoffset];
              nr = knt + 3 * b_k;
              aa = (ab + s * z[nr]) + d * z[knt + 6];
              z[hoffset] = ab - aa * bb;
              z[nr] -= aa * tst;
              z[knt + 6] -= aa * ba;
            }
          } else if (nr == 2) {
            for (knt = b_k; knt < 4; knt++) {
              hoffset = b_k + 3 * (knt - 1);
              ab = h[hoffset - 1];
              aa = ab + s * h[hoffset];
              h[hoffset - 1] = ab - aa * bb;
              h[hoffset] -= aa * tst;
            }
            for (knt = 0; knt <= i; knt++) {
              hoffset = knt + 3 * (b_k - 1);
              nr = knt + 3 * b_k;
              aa = h[hoffset] + s * h[nr];
              h[hoffset] -= aa * bb;
              h[nr] -= aa * tst;
            }
            for (knt = 0; knt < 3; knt++) {
              hoffset = knt + 3 * (b_k - 1);
              ab = z[hoffset];
              nr = knt + 3 * b_k;
              aa = ab + s * z[nr];
              z[hoffset] = ab - aa * bb;
              z[nr] -= aa * tst;
            }
          }
        }
        its++;
      }
    }
    if (!goto150) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((k + 2 != i + 1) && (k + 2 == i)) {
        b_i = i + 3 * i;
        s = h[b_i - 1];
        knt = i + 3 * (i - 1);
        d = h[knt];
        tst = h[b_i];
        reflapack::xdlanv2(&h[(i + 3 * (i - 1)) - 1], &s, &d, &tst, &ab, &aa,
                           &ba, &bb, &h22, &rt1r);
        h[b_i - 1] = s;
        h[knt] = d;
        h[b_i] = tst;
        if (3 > i + 1) {
          knt = 1 - i;
          nr = i + (i + 1) * 3;
          for (b_k = 0; b_k <= knt; b_k++) {
            hoffset = nr + b_k * 3;
            tst = h[hoffset];
            ab = h[hoffset - 1];
            h[hoffset] = h22 * tst - rt1r * ab;
            h[hoffset - 1] = h22 * ab + rt1r * tst;
          }
        }
        blas::xrot(i - 1, h, (i - 1) * 3 + 1, i * 3 + 1, h22, rt1r);
        blas::xrot(z, (i - 1) * 3 + 1, i * 3 + 1, h22, rt1r);
      }
      kdefl = 0;
      i = k;
    }
  }
  return info;
}

} // namespace lapack
} // namespace internal
} // namespace coder

// End of code generation (xhseqr.cpp)
