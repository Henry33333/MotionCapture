#include "cali.h"


// Function Definitions

Eigen::Matrix4d T_tran_xrs(const Eigen::Vector3d& pos, const Eigen::Vector4d& xrs) {
    Eigen::Matrix4d T = Eigen::Matrix4d::Identity();

    // Convert quaternion to rotation matrix and transpose
    Eigen::Matrix3d rotation_matrix = Eigen::Quaterniond(xrs(3), xrs(0), xrs(1), xrs(2)).toRotationMatrix();
    T.block(0, 0, 3, 3) = rotation_matrix;

    // Set the translation vector 起始行为0，取3行，起始列为3，取1列
    T.block(0, 3, 3, 1) = pos;

    return T;
}

Eigen::Matrix4d T_inverse(const Eigen::Matrix4d& T) {
    Eigen::Matrix4d T_new = T;

    // Transpose the rotation submatrix (1:3, 1:3) of T 取<3,3>大小的矩阵，起始行为0，起始列为0
    T_new.block<3, 3>(0, 0) = T.block<3, 3>(0, 0).transpose();

    // Calculate the new translation vector based on the transposed rotation
    T_new.block<3, 1>(0, 3) = -T_new.block<3, 3>(0, 0) * T.block<3, 1>(0, 3);

    // Set the bottom right element of T_new to 1 (homogeneous coordinates)
    T_new(3, 3) = 1.0;

    return T_new;
}

Eigen::Vector3d rotationMatrixToRPY(const Eigen::Matrix4d& T) {
    Eigen::Matrix3d rotationMatrix = T.block<3, 3>(0, 0);
    Eigen::Vector3d RPYMatrix;

    // Convert rotation matrix to roll, pitch, and yaw (RPY) angles
    RPYMatrix(0) = atan2(rotationMatrix(2, 1), rotationMatrix(2, 2));  // roll
    RPYMatrix(1) = atan2(-rotationMatrix(2, 0), sqrt(rotationMatrix(2, 1) * rotationMatrix(2, 1) + rotationMatrix(2, 2) * rotationMatrix(2, 2)));  // pitch
    RPYMatrix(2) = atan2(rotationMatrix(1, 0), rotationMatrix(0, 0));  // yaw

    return RPYMatrix;
}



Eigen::MatrixXd calibration(const std::vector<std::vector<QVariant>>& T1, const std::vector<std::vector<QVariant>>& T2, const std::vector<std::vector<QVariant>>& T3) {

    //T1=Tce,T2=T07,T3=demo

    // Example usage
    Eigen::MatrixXd Tce; // Assuming Tce is a matrix, replace with your actual data type
    Eigen::MatrixXd T07; // Assuming T07 is a matrix, replace with your actual data type
    Eigen::MatrixXd demonstrations;


    // Initialize Tce and T07 with your data
    Tce.resize(40, 7);
    for (int a = 0; a < 40; a++)
    {
        for (int b = 0; b < 7; b++)
        {
            Tce(a,b) = T1[a][b].toFloat();
        }
    }


    T07.resize(4, 160);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 160; j++)
        {
            T07(i,j) = T2[i][j].toFloat();
        }
    }

    size_t T3Rows = T3.size(); // 获取行数
    size_t T3Cols = (T3Rows > 0) ? T3[0].size() : 0;
    demonstrations.resize(T3Rows, T3Cols);
    for (int i = 0; i < T3Rows; i++)
    {
        for (int j = 0; j < T3Cols; j++)
        {
            demonstrations(i,j) = T3[i][j].toFloat();
        }
    }

 //********************************************************************************************************


    // 毫米转米制，角度转弧度
    Tce.block(0, 0, Tce.rows(), 3) /= 1000.0 ;

    Eigen::MatrixXd BB;
    int traing_number = Tce.rows();

    for (int i = 0; i < traing_number; ++i) {
        Eigen::Matrix4d transformation = T_tran_xrs(Tce(i, Eigen::seq(0, 2)), Tce(i, Eigen::seq(3, 6)));
        BB.conservativeResize(4, (i + 1) * 4);
        BB.block(0, i * 4, 4, 4) = transformation;
    }

    Eigen::MatrixXd AA = T07; // Assuming T07 is already defined

    std::vector<Eigen::Matrix3d> R_07_ByWu(traing_number);
    std::vector<Eigen::Vector3d> t_07_ByWu(traing_number);
    std::vector<Eigen::Vector3d> t_ce_ByWu(traing_number);


    for (int i = 0; i < traing_number; ++i) {
        R_07_ByWu[i] = AA.block(0, i * 4, 3, 3);
        t_07_ByWu[i] = AA.block(0, i * 4 + 3, 3, 1);
        t_ce_ByWu[i] = BB.block(0, i * 4 + 3, 3, 1);
    }

    double rbh[360];
    double tbh[120];
    double pw[120];

    double res1[9];
    double res2[3];
    double res3[3];

    int idx1 = 0;  // Index to keep track of the position in rbh array
    for (const auto& matrix : R_07_ByWu) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rbh[idx1++] = matrix(j, i);
            }
        }
    }




    int idx2 = 0;  // Index to keep track of the position in tbh array
    for (const auto& vector : t_07_ByWu) {
        for (int i = 0; i < 3; ++i) {
            tbh[idx2++] = vector(i);
        }
    }




    int idx3 = 0;  // Index to keep track of the position in tbh array
    for (const auto& vector : t_ce_ByWu) {
        for (int i = 0; i < 3; ++i) {
            pw[idx3++] = vector(i);
        }
    }


    hybrid(rbh, tbh, pw, res1, res2, res3);

    Eigen::Matrix3d R_0c_ByWu;
    R_0c_ByWu << res1[0], res1[3], res1[6],
        res1[1], res1[4], res1[7],
        res1[2], res1[5], res1[8];

    Eigen::Vector3d t_0c_ByWu(res2);
    Eigen::Vector3d t_7e_ByWu(res3);


    Eigen::Matrix3d R_7e_ByWu = R_07_ByWu[0].transpose() * R_0c_ByWu * BB.block(0, 0, 3, 3);

    Eigen::Matrix4d T7e = Eigen::Matrix4d::Identity();
    T7e.block(0, 0, 3, 3) = R_7e_ByWu;
    T7e.block(0, 3, 3, 1) = t_7e_ByWu;

    Eigen::Matrix4d T0c = Eigen::Matrix4d::Identity();
    T0c.block(0, 0, 3, 3) = R_0c_ByWu;
    T0c.block(0, 3, 3, 1) = t_0c_ByWu;

//    std::cout << T7e << std::endl;
//    std::cout << std::endl;
//    std::cout << T0c << std::endl;

//********************************************************************************************************

    demonstrations.col(0).array() /= 1000.0;
    demonstrations.col(1).array() /= 1000.0;
    demonstrations.col(2).array() /= 1000.0;

    int trainingNumber = demonstrations.rows();
    Eigen::MatrixXd reproduction(trainingNumber, 6);;


    for (int i = 0; i < trainingNumber; ++i) {
        Eigen::Matrix4d tmp = T0c * T_tran_xrs(demonstrations.row(i).head<3>(), demonstrations.row(i).tail<4>()) * T_inverse(T7e);
        Eigen::Vector3d tmpTranslation = tmp.block<3, 1>(0, 3) * 1000.0;
        Eigen::Vector3d rpy = rotationMatrixToRPY(tmp);
        Eigen::VectorXd tmp2(6);
        tmp2.head<3>() = tmpTranslation;
        tmp2.tail<3>() = rpy*180/M_PI;
        reproduction.row(i) = tmp2;
    }

    return reproduction;
}




