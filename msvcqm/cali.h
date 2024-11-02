#ifndef CALI_H
#define CALI_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QStackedWidget>


#include <eigen-3.4.0/Eigen/Core>
#include <eigen-3.4.0/Eigen/Geometry>
#include <eigen-3.4.0/Eigen/Dense>


#include "hybrid/rtwtypes.h"
#include "hybrid/hybrid.h"
#include "hybrid/rt_nonfinite.h"


Eigen::Matrix4d T_tran_xrs(const Eigen::Vector3d& pos, const Eigen::Vector4d& xrs);

Eigen::Matrix4d T_inverse(const Eigen::Matrix4d& T);

Eigen::Vector3d rotationMatrixToRPY(const Eigen::Matrix4d& T);

Eigen::MatrixXd calibration(const std::vector<std::vector<QVariant>>& T1, const std::vector<std::vector<QVariant>>& T2, const std::vector<std::vector<QVariant>>& T3);



#endif // CALI_H
