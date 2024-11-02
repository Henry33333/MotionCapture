//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// hybrid.cpp
//
// Code generation for function 'hybrid'
//

// Include files
#include "hybrid.h"
#include "hybrid_data.h"
#include "mldivide.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include "vlogR.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (std::isinf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

void hybrid(const double R_BH[360], const double t_BH[120],
            const double P_W[120], double R_BW[9], double t_BW[3],
            double P_H[3])
{
  static const signed char b_iv[360]{
      1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
      1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
      1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
      1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
      1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
      0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
      0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
      0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
      0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
      0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
      0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
      0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
      0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
      0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
      0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
  double A[1800];
  double crossRP_W[1080];
  double e_crossRP_W[360];
  double b[120];
  double b_R_BH[120];
  double b_crossRP_W[120];
  double c_R_BH[120];
  double c_crossRP_W[120];
  double d_R_BH[120];
  double d_crossRP_W[120];
  double K[27];
  double b_x[15];
  double Q_BW[9];
  double c_x[9];
  double tempR_BW[9];
  double x[9];
  double w[3];
  double d;
  double scale;
  double theta;
  int b_i;
  int b_j1;
  int i;
  int kidx;
  signed char b_I[9];
  boolean_T p;
  // iterative Iterative solution for finding the kinematic base frame by
  // hand-eye calibration using 3D position data
  //
  //    [ R_BW, t_BW, P_H ] = closedForm( R_BH, t_BH, P_W )
  //    R_BH:       rotation matrix from base to hand, 3x3xM
  //    t_BH:       translation vector from base to hand, 3xM
  //    P_W:        position of marker in world frame, 3xM
  //    R_BW_init:  initial rotation matrix from base to world, 3x3
  //    t_BW_init:  initial translantion vector from base to world, 3x1
  //    P_H_init:   initial position of marker in hand frame, 3x1
  //    R_BW:       rotation matrix from base to world, 3x3
  //    t_BW:       translantion vector from base to world, 3x1
  //    P_H:        position of marker in hand frame, 3x1
  for (i = 0; i < 9; i++) {
    x[i] = 1.0;
  }
  // closedForm Closed form solution for finding the kinematic base frame by
  // hand-eye calibration using 3D position data
  //
  //    [ R_BW, t_BW, P_H ] = closedForm( R_BH, t_BH, P_W )
  //    R_BH:   rotation matrix from base to hand, 3x3xM
  //    t_BH:   translation vector from base to hand, 3xM
  //    P_W:    position of marker in world frame, 3xM
  //    R_BW:   rotation matrix from base to world, 3x3
  //    t_BW:   translantion vector from base to world, 3x1
  //    P_H:    position of marker in hand frame, 3x1
  // number of measurements
  std::memset(&A[0], 0, 1800U * sizeof(double));
  for (i = 0; i < 40; i++) {
    int j2;
    kidx = -1;
    for (b_j1 = 0; b_j1 < 3; b_j1++) {
      theta = P_W[b_j1 + 3 * i];
      for (j2 = 0; j2 < 3; j2++) {
        K[kidx + 1] = theta * static_cast<double>(iv[3 * j2]);
        K[kidx + 2] = theta * static_cast<double>(iv[3 * j2 + 1]);
        K[kidx + 3] = theta * static_cast<double>(iv[3 * j2 + 2]);
        kidx += 3;
      }
    }
    kidx = (i + 1) * 3 - 3;
    for (b_i = 0; b_i < 9; b_i++) {
      b_I[b_i] = 0;
      b_j1 = kidx + 120 * b_i;
      A[b_j1] = K[3 * b_i];
      A[b_j1 + 1] = K[3 * b_i + 1];
      A[b_j1 + 2] = K[3 * b_i + 2];
    }
    b_I[0] = 1;
    b_I[4] = 1;
    b_I[8] = 1;
    for (b_i = 0; b_i < 3; b_i++) {
      int A_tmp;
      b_j1 = kidx + 120 * (b_i + 9);
      A[b_j1] = b_I[3 * b_i];
      j2 = 3 * b_i + 9 * i;
      A_tmp = kidx + 120 * (b_i + 12);
      A[A_tmp] = -R_BH[j2];
      A[b_j1 + 1] = b_I[3 * b_i + 1];
      A[A_tmp + 1] = -R_BH[j2 + 1];
      A[b_j1 + 2] = b_I[3 * b_i + 2];
      A[A_tmp + 2] = -R_BH[j2 + 2];
      b[b_i + kidx] = t_BH[b_i + 3 * i];
    }
  }
  coder::mldivide(A, b, b_x);
  t_BW[0] = b_x[9];
  P_H[0] = b_x[12];
  t_BW[1] = b_x[10];
  P_H[1] = b_x[13];
  t_BW[2] = b_x[11];
  P_H[2] = b_x[14];
  p = true;
  for (kidx = 0; kidx < 9; kidx++) {
    d = b_x[kidx];
    if ((!p) || (std::isinf(d) || std::isnan(d))) {
      p = false;
    }
  }
  if (p) {
    std::copy(&b_x[0], &b_x[9], &c_x[0]);
    coder::internal::svd(c_x, tempR_BW, w, Q_BW);
  } else {
    for (b_i = 0; b_i < 9; b_i++) {
      tempR_BW[b_i] = rtNaN;
      Q_BW[b_i] = rtNaN;
    }
  }
  for (b_i = 0; b_i < 3; b_i++) {
    d = tempR_BW[b_i];
    theta = tempR_BW[b_i + 3];
    scale = tempR_BW[b_i + 6];
    for (b_j1 = 0; b_j1 < 3; b_j1++) {
      R_BW[b_i + 3 * b_j1] =
          (d * Q_BW[b_j1] + theta * Q_BW[b_j1 + 3]) + scale * Q_BW[b_j1 + 6];
    }
  }
  int exitg1;
  do {
    double absxk;
    double t;
    exitg1 = 0;
    theta = 0.0;
    scale = 3.3121686421112381E-170;
    for (kidx = 0; kidx < 9; kidx++) {
      absxk = std::abs(x[kidx]);
      if (absxk > scale) {
        t = scale / absxk;
        theta = theta * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        theta += t * t;
      }
    }
    theta = scale * std::sqrt(theta);
    if (theta > 1.0E-6) {
      //  there are two ways to generate the Jacobian matrix
      // J_maker Jacobian matrix for the iterative algorithm
      //
      //    J = J_maker(R_BW,P_W,R_BH)
      //    R_BW:       rotation matrix from base to world, 3x3
      //    P_W:        position of marker in world frame, 3xM
      //    R_BH:       rotation matrix from base to hand, 3x3xM
      // number of measurements
      vlogR(R_BW, w);
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
      //  it under the terms of the GNU Lesser General Public License as
      //  published by the Free Software Foundation, either version 3 of the
      //  License, or (at your option) any later version.
      //
      //  RTB is distributed in the hope that it will be useful,
      //  but WITHOUT ANY WARRANTY; without even the implied warranty of
      //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      //  GNU Lesser General Public License for more details.
      //
      //  You should have received a copy of the GNU Leser General Public
      //  License along with RTB.  If not, see <http://www.gnu.org/licenses/>.
      //  SO(3) case
      tempR_BW[0] = 0.0;
      tempR_BW[3] = -w[2];
      tempR_BW[6] = w[1];
      tempR_BW[1] = w[2];
      tempR_BW[4] = 0.0;
      tempR_BW[7] = -w[0];
      tempR_BW[2] = -w[1];
      tempR_BW[5] = w[0];
      tempR_BW[8] = 0.0;
      scale = 3.3121686421112381E-170;
      absxk = std::abs(w[0]);
      if (absxk > 3.3121686421112381E-170) {
        theta = 1.0;
        scale = absxk;
      } else {
        t = absxk / 3.3121686421112381E-170;
        theta = t * t;
      }
      absxk = std::abs(w[1]);
      if (absxk > scale) {
        t = scale / absxk;
        theta = theta * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        theta += t * t;
      }
      absxk = std::abs(w[2]);
      if (absxk > scale) {
        t = scale / absxk;
        theta = theta * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        theta += t * t;
      }
      theta = scale * std::sqrt(theta);
      scale = 1.0 / (theta * theta) * (1.0 - std::cos(theta));
      theta = 1.0 / rt_powd_snf(theta, 3.0) * (theta - std::sin(theta));
      for (b_i = 0; b_i < 9; b_i++) {
        b_I[b_i] = 0;
      }
      b_I[0] = 1;
      b_I[4] = 1;
      b_I[8] = 1;
      for (b_i = 0; b_i < 3; b_i++) {
        for (b_j1 = 0; b_j1 < 3; b_j1++) {
          kidx = b_i + 3 * b_j1;
          c_x[kidx] =
              (static_cast<double>(b_I[kidx]) + scale * tempR_BW[kidx]) +
              ((theta * tempR_BW[b_i] * tempR_BW[3 * b_j1] +
                theta * tempR_BW[b_i + 3] * tempR_BW[3 * b_j1 + 1]) +
               theta * tempR_BW[b_i + 6] * tempR_BW[3 * b_j1 + 2]);
        }
      }
      for (b_i = 0; b_i < 3; b_i++) {
        d = R_BW[3 * b_i];
        theta = R_BW[3 * b_i + 1];
        scale = R_BW[3 * b_i + 2];
        for (b_j1 = 0; b_j1 < 3; b_j1++) {
          Q_BW[b_i + 3 * b_j1] =
              (d * c_x[3 * b_j1] + theta * c_x[3 * b_j1 + 1]) +
              scale * c_x[3 * b_j1 + 2];
        }
      }
      c_x[0] = 0.0;
      c_x[4] = 0.0;
      c_x[8] = 0.0;
      for (b_i = 0; b_i < 9; b_i++) {
        tempR_BW[b_i] = -R_BW[b_i];
      }
      for (i = 0; i < 40; i++) {
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
        //  it under the terms of the GNU Lesser General Public License as
        //  published by the Free Software Foundation, either version 3 of the
        //  License, or (at your option) any later version.
        //
        //  RTB is distributed in the hope that it will be useful,
        //  but WITHOUT ANY WARRANTY; without even the implied warranty of
        //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        //  GNU Lesser General Public License for more details.
        //
        //  You should have received a copy of the GNU Leser General Public
        //  License along with RTB.  If not, see <http://www.gnu.org/licenses/>.
        //  SO(3) case
        d = P_W[3 * i + 2];
        c_x[3] = -d;
        theta = P_W[3 * i + 1];
        c_x[6] = theta;
        c_x[1] = d;
        d = P_W[3 * i];
        c_x[7] = -d;
        c_x[2] = -theta;
        c_x[5] = d;
        for (b_i = 0; b_i < 3; b_i++) {
          d = tempR_BW[b_i];
          theta = tempR_BW[b_i + 3];
          scale = tempR_BW[b_i + 6];
          for (b_j1 = 0; b_j1 < 3; b_j1++) {
            x[b_i + 3 * b_j1] =
                (d * c_x[3 * b_j1] + theta * c_x[3 * b_j1 + 1]) +
                scale * c_x[3 * b_j1 + 2];
          }
          d = x[b_i];
          theta = x[b_i + 3];
          scale = x[b_i + 6];
          for (b_j1 = 0; b_j1 < 3; b_j1++) {
            e_crossRP_W[(b_i + 3 * b_j1) + 9 * i] =
                (d * Q_BW[3 * b_j1] + theta * Q_BW[3 * b_j1 + 1]) +
                scale * Q_BW[3 * b_j1 + 2];
          }
        }
      }
      //    J=J2_maker(R_BW,P_W,R_BH);
      // f_maker generate f_0 for the iterative algorithm
      //
      //    f = f_maker (R_BW, t_BW, P_W, R_BH, t_BH, P_H)
      //    R_BW:       rotation matrix from base to world, 3x3
      //    t_BW:       translantion vector from base to world, 3x1
      //    P_W:        position of marker in world frame, 3xM
      //    R_BH:       rotation matrix from base to hand, 3x3xM
      //    t_BH:       translation vector from base to hand, 3xM
      //    P_H:        position of marker in hand frame, 3x1
      // number of measurements
      for (b_i = 0; b_i < 9; b_i++) {
        tempR_BW[b_i] = -R_BW[b_i];
      }
      d = P_H[0];
      theta = P_H[1];
      scale = P_H[2];
      for (i = 0; i < 40; i++) {
        double d1;
        absxk = P_W[3 * i];
        t = P_W[3 * i + 1];
        d1 = P_W[3 * i + 2];
        for (b_i = 0; b_i < 3; b_i++) {
          double d2;
          double d3;
          double d4;
          b_j1 = b_i + 9 * i;
          d2 = R_BH[b_j1];
          d3 = R_BH[b_j1 + 3];
          d4 = R_BH[b_j1 + 6];
          kidx = b_i + 3 * i;
          b[kidx] = ((((tempR_BW[b_i] * absxk + tempR_BW[b_i + 3] * t) +
                       tempR_BW[b_i + 6] * d1) -
                      t_BW[b_i]) +
                     ((d2 * d + d3 * theta) + d4 * scale)) +
                    t_BH[kidx];
          b_crossRP_W[kidx] = e_crossRP_W[b_j1];
          c_crossRP_W[kidx] = e_crossRP_W[b_j1 + 3];
          d_crossRP_W[kidx] = e_crossRP_W[b_j1 + 6];
          b_R_BH[kidx] = d2;
          c_R_BH[kidx] = d3;
          d_R_BH[kidx] = d4;
        }
      }
      for (b_i = 0; b_i < 120; b_i++) {
        crossRP_W[b_i] = b_crossRP_W[b_i];
        crossRP_W[b_i + 120] = c_crossRP_W[b_i];
        crossRP_W[b_i + 240] = d_crossRP_W[b_i];
      }
      for (b_i = 0; b_i < 3; b_i++) {
        for (b_j1 = 0; b_j1 < 120; b_j1++) {
          crossRP_W[b_j1 + 120 * (b_i + 3)] = b_iv[b_j1 + 120 * b_i];
        }
      }
      for (b_i = 0; b_i < 120; b_i++) {
        crossRP_W[b_i + 720] = -b_R_BH[b_i];
        crossRP_W[b_i + 840] = -c_R_BH[b_i];
        crossRP_W[b_i + 960] = -d_R_BH[b_i];
      }
      coder::b_mldivide(crossRP_W, b, x);
      // if J2_maker used, comment the first three lines and uncomment the
      // second three lines
      scale = 3.3121686421112381E-170;
      d = w[0] + x[0];
      w[0] = d;
      absxk = std::abs(d);
      if (absxk > 3.3121686421112381E-170) {
        theta = 1.0;
        scale = absxk;
      } else {
        t = absxk / 3.3121686421112381E-170;
        theta = t * t;
      }
      d = w[1] + x[1];
      w[1] = d;
      absxk = std::abs(d);
      if (absxk > scale) {
        t = scale / absxk;
        theta = theta * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        theta += t * t;
      }
      d = w[2] + x[2];
      absxk = std::abs(d);
      if (absxk > scale) {
        t = scale / absxk;
        theta = theta * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        theta += t * t;
      }
      theta = scale * std::sqrt(theta);
      w[0] /= theta;
      w[1] /= theta;
      w[2] = d / theta;
      // rotationMatrix Rotation from axis and angle
      //
      //    R = rotationMatrix(w,theta) gives the rotation matrix about a unit
      //    axis w for an angle of theta. w:      Unit rotation axis, 3 x 1
      //    theta:  rotation algle
      //    R:      Rotation matrix, 3 x 3
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
      //  it under the terms of the GNU Lesser General Public License as
      //  published by the Free Software Foundation, either version 3 of the
      //  License, or (at your option) any later version.
      //
      //  RTB is distributed in the hope that it will be useful,
      //  but WITHOUT ANY WARRANTY; without even the implied warranty of
      //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      //  GNU Lesser General Public License for more details.
      //
      //  You should have received a copy of the GNU Leser General Public
      //  License along with RTB.  If not, see <http://www.gnu.org/licenses/>.
      //  SO(3) case
      tempR_BW[0] = 0.0;
      tempR_BW[3] = -w[2];
      tempR_BW[6] = w[1];
      tempR_BW[1] = w[2];
      tempR_BW[4] = 0.0;
      tempR_BW[7] = -w[0];
      tempR_BW[2] = -w[1];
      tempR_BW[5] = w[0];
      tempR_BW[8] = 0.0;
      scale = std::sin(theta);
      theta = 1.0 - std::cos(theta);
      for (b_i = 0; b_i < 9; b_i++) {
        b_I[b_i] = 0;
      }
      for (kidx = 0; kidx < 3; kidx++) {
        b_I[kidx + 3 * kidx] = 1;
        for (b_i = 0; b_i < 3; b_i++) {
          R_BW[kidx + 3 * b_i] = (tempR_BW[kidx] * tempR_BW[3 * b_i] +
                                  tempR_BW[kidx + 3] * tempR_BW[3 * b_i + 1]) +
                                 tempR_BW[kidx + 6] * tempR_BW[3 * b_i + 2];
        }
      }
      for (b_i = 0; b_i < 9; b_i++) {
        R_BW[b_i] = (static_cast<double>(b_I[b_i]) + tempR_BW[b_i] * scale) +
                    R_BW[b_i] * theta;
      }
      //    delta_theta=x(1:3);
      //    delta_R=rotationMatrix(delta_theta/norm(delta_theta),norm(delta_theta));
      //    R_BW = R_BW*delta_R; % update rotation
      t_BW[0] += x[3];
      P_H[0] += x[6];
      t_BW[1] += x[4];
      P_H[1] += x[7];
      t_BW[2] += x[5];
      P_H[2] += x[8];
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

// End of code generation (hybrid.cpp)
