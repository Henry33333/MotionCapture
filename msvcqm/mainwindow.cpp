#include "mainwindow.h"
#include "ui_mainwindow.h"

//受回调函数影响，只能在文件中定义**************
int flag = 0;
int currentRow = 1;
QXlsx::Document *Tcexlsx = nullptr;
QString TcefilePath;
//****************************************

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , theClient(new SeekerSDKClient)
    , T07xlsx(nullptr)
    , worker(new Worker)
    , robotapi(nullptr)
{
    ui->setupUi(this);

    worker->moveToThread(&workThread);

    connect(ui->startRobButton, &QPushButton::clicked, this, &MainWindow::beforeStart);
    connect(this, &MainWindow::startWorking, worker, &Worker::on_doSomething);
    connect(&workThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &Worker::resultReady, this, [this]()
            {
                QMessageBox::information(this,"提示","运动命令已全部发送完毕");
                ui->infoTextEdit->append("运动命令已全部发送完毕\n");
            });

    workThread.start();

}

MainWindow::~MainWindow()
{

    workThread.quit();
    workThread.wait();
    delete worker;
    delete theClient;
    delete T07xlsx;
    delete Tcexlsx;
    delete robotapi;
    delete ui;
}

void MainWindow::on_seekIpButton_clicked()
{

    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        QMessageBox::warning(this,"Seeking IP","Wrong at init wsa");
        qDebug() << "Wrong at init wsa";
        return;
    }
    //2.Get host name
    char hostname[256];
    ret = gethostname(hostname, sizeof(hostname));
    if (ret == SOCKET_ERROR)
    {
        QMessageBox::warning(this,"Seeking IP","Wrong at get host name");
        qDebug() << "Wrong at get host name";
        return;
    }
    //3.Get host IP
    HOSTENT* host = gethostbyname(hostname);
    if (host == NULL)
    {
        QMessageBox::warning(this,"Seeking IP","Wrong at get host ip");
        qDebug() << "Wrong at get host ip";
        return;
    }

    ui->infoTextEdit->append("Found all IP addresses. Please ensure there is an IP address in the same network with the server\n");
    qDebug() << "Found all IP addresses. Please ensure there is an IP address in the same network with the server\n";

    for (int iCount = 0; host->h_addr_list[iCount] != NULL; ++iCount)
    {
        strcpy(szMyIPAddress, inet_ntoa(*(in_addr*)host->h_addr_list[iCount]));
        ui->infoTextEdit->append( QString("%1)[%2] .").arg(iCount + 1).arg(szMyIPAddress) );
        qDebug() << QString("%1)[%2] .").arg(iCount + 1).arg(szMyIPAddress);
    }

//************************************************************************************************************************

    ui->infoTextEdit->append("Please input the server IP\n");
    qDebug() << "Please input the server IP\n";


}


void MainWindow::on_testClientButton_clicked()
{
    if (ui->nokov_ip->text().isEmpty())
    {
        QMessageBox::warning(this,"提示","动捕IP为空");
        return;
    }

    char ipBuf[100] = {0};
    QByteArray nokovip = ui->nokov_ip->text().toUtf8();
    qstrcpy(ipBuf, nokovip.constData());


    //4.Create SeekerSDK Client
    int iResult = -1;
    iResult = CreateClient(ipBuf);
    if(iResult != ErrorCode_OK)
    {
        QMessageBox::warning(this,"Seeking IP","Error initializing client.\n");
        qDebug() << "Error initializing client.  Exiting\n";
    }
    else
    {
        QMessageBox::information(this,"Seeking IP","Client initialized and ready.\n");
        qDebug() << "Client initialized and ready.\n";
    }

    theClient->Uninitialize();
//    delete theClient;
//    theClient = nullptr;
}



int MainWindow::CreateClient(char* szServerIP)
{
    // release previous server
    if(theClient)
    {
        theClient->Uninitialize();
        delete theClient;
    }

    // create SeekerSDK client
    theClient = new SeekerSDKClient();

    // print version info
    unsigned char ver[4];
    theClient->SeekerSDKVersion(ver);
    ui->infoTextEdit->append( QString("SeekerSDK Sample Client 2.4.0.4177 (SeekerSDK ver. %1.%2.%3.%4)").arg(ver[0]).arg(ver[1]).arg(ver[2]).arg(ver[3]) );

    // Set callback handlers
    //theClient->SetMessageCallback(MessageHandler);
    //theClient->SetVerbosityLevel(Verbosity_Error);
    // Init Client and connect to SeekerSDK server
    int retCode = -1;
    retCode = theClient->Initialize(szServerIP);//szMyIPAddress��Client IP (local IP)��szServerIP��Server IP (computer IP running motion capture software)
    //Sleep(10);
    memcpy(szServerIPAddress, szServerIP, strlen(szServerIP));

    if (retCode != ErrorCode_OK)
    {

        QMessageBox::warning(this,"Initializing Client","Unable to connect to server\n");
        return ErrorCode_Internal;
    }
    else
    {
        // print server info
        sServerDescription ServerDescription;
        memset(&ServerDescription, 0, sizeof(ServerDescription));
        theClient->GetServerDescription(&ServerDescription);
        if(!ServerDescription.HostPresent)
        {

            QMessageBox::warning(this,"Getting Server","Unable to connect to server. Host not present\n");
            return 1;
        }

        ui->infoTextEdit->append("Successfully connected to server\n");
    }

    {
        sDataDescriptions* ps = nullptr;
        theClient->GetDataDescriptions(&ps);
        if (ps)
        {
            for (int dsIndex = 0; dsIndex < ps->nDataDescriptions; ++dsIndex)
            {
                const auto& dataDescription = ps->arrDataDescriptions[dsIndex];

                switch (dataDescription.type)
                {
//                case Descriptor_MarkerSetEx:
//                    printf("MarkerSetExName : %s\n", dataDescription.Data.MarkerSetData->szName);
//                    for (int markerIndex = 0; markerIndex < dataDescription.Data.MarkerSetData->nMarkers; ++markerIndex)
//                    {
//                        MarkerData& md = dataDescription.Data.MarkerSetData->Markers[markerIndex];
//                        printf("Marker[%d] : %f,%f,%f\n", markerIndex, md[0], md[1], md[2]);
//                    }
//                    break;
//                case Descriptor_MarkerSet:
//                    printf("MarkerSetName : %s\n", dataDescription.Data.MarkerSetDescription->szName);

//                    for (int markerIndex = 0; markerIndex < dataDescription.Data.MarkerSetDescription->nMarkers; ++markerIndex)
//                    {
//                        printf("Marker[%d] : %s\n", markerIndex, dataDescription.Data.MarkerSetDescription->szMarkerNames[markerIndex]);
//                    }
//                    break;
                case Descriptor_RigidBody:
                    printf("RigidBody:%s\n", dataDescription.Data.RigidBodyDescription->szName);

                    break;
//                case Descriptor_Skeleton:
//                    printf("Skeleton:%s\n", dataDescription.Data.SkeletonDescription->szName);
//                    for (int boneIndex = 0; boneIndex < dataDescription.Data.SkeletonDescription->nRigidBodies; ++boneIndex)
//                    {
//                        auto boneDescription = dataDescription.Data.SkeletonDescription->RigidBodies[boneIndex];
//                        printf("[%d] %s\n", boneDescription.ID, boneDescription.szName);
//                    }
//                    break;
//                case Descriptor_ForcePlate:
//                    for (int channelIdx = 0; channelIdx < dataDescription.Data.ForcePlateDescription->nChannels; ++channelIdx)
//                    {
//                        printf("Channel:%d %s\n", channelIdx,
//                               dataDescription.Data.ForcePlateDescription->szChannelNames[channelIdx]);
//                    }
                default:
                    break;
                }
            }

            theClient->FreeDataDescriptions(ps);
            ps = nullptr;
        }

    }

//    theClient->WaitForForcePlateInit();
    theClient->SetDataCallback(DataHandler, theClient);	// this function will receive data from the server


    return ErrorCode_OK;
}



// DataHandler receives data from the server //回调函数、全局函数
void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData)

{
    SeekerSDKClient* pClient = (SeekerSDKClient*) pUserData;

    // FrameOfMocapData params
    bool bIsRecording = data->params & 0x01;
    bool bTrackedModelsChanged = data->params & 0x02;
    if (bIsRecording)
        printf("RECORDING\n");
    if (bTrackedModelsChanged)
        printf("Models Changed.\n");

    // timecode - for systems with an eSync and SMPTE timecode generator - decode to values



    // decode to friendly string
    char szTimecode[128] = "";
    pClient->TimecodeStringify(data->Timecode, data->TimecodeSubframe, szTimecode, 128);
    printf("Timecode : %s\n", szTimecode);//print timecode stardard
    printf("FrameNO:%d\tTimeStamp:%lld\n", data->iFrame, data->iTimeStamp);

    printf("MarkerSet [Count=%d]\n", data->nMarkerSets);	//Number of Markerset




    //Print RigidBodies
    printf("Markerset.RigidBodies [Count=%d]\n", data->nRigidBodies);//Number of Markerset.Skeleton(skeleton)
    printf("{\n");
    for (int i = 0; i < data->nRigidBodies; i++)
    {
        printf("\tid\t\tx\ty\tz\tqx\tqy\tqz\tqw\n");
        printf("\tRigidBody%d\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",
               data->RigidBodies[i].ID,
               data->RigidBodies[i].x,
               data->RigidBodies[i].y,
               data->RigidBodies[i].z,
               data->RigidBodies[i].qx,
               data->RigidBodies[i].qy,
               data->RigidBodies[i].qz,
               data->RigidBodies[i].qw);

        if (flag == 1)
        {
            Tcexlsx->write(currentRow,1,data->RigidBodies[i].x);
            Tcexlsx->write(currentRow,2,data->RigidBodies[i].y);
            Tcexlsx->write(currentRow,3,data->RigidBodies[i].z);
            Tcexlsx->write(currentRow,4,data->RigidBodies[i].qx);
            Tcexlsx->write(currentRow,5,data->RigidBodies[i].qy);
            Tcexlsx->write(currentRow,6,data->RigidBodies[i].qz);
            Tcexlsx->write(currentRow,7,data->RigidBodies[i].qw);

            Tcexlsx->saveAs(TcefilePath);
            currentRow = currentRow + 1;
            flag = 0;
        }

    }

}



void MainWindow::on_saveTceButton_clicked()
{

    if (ui->nokov_ip->text().isEmpty())
    {
        QMessageBox::information(this,"提示","动捕IP为空");
        return;
    }

    if(!Tcexlsx)
    {
        TcefilePath = QFileDialog::getSaveFileName(nullptr, "Save Excel File", "", "Excel Files (*.xlsx)");
        if (TcefilePath.isEmpty())
        {
            QMessageBox::warning(nullptr,"Saving Tce","No TcefilePath");
            return;
        }
        currentRow = 1;
        Tcexlsx = new QXlsx::Document;
    }

    flag = 1;

    char ipBuf[100] = {0};
    QByteArray nokovip = ui->nokov_ip->text().toUtf8();
    qstrcpy(ipBuf, nokovip.constData());


    //4.Create SeekerSDK Client
    int iResult = -1;
    iResult = CreateClient(ipBuf);
    if(iResult != ErrorCode_OK)
    {
        QMessageBox::warning(this,"Seeking IP","Error initializing client\n");

    }
    else
    {
        QMessageBox::warning(this,"保存Tce中","请点击确认\n");
        ui->infoTextEdit->append("已将Tce保存至第" + QString::number(currentRow-1) + "行\n");
    }

    theClient->Uninitialize();
//    delete theClient;
//    theClient = nullptr;
}



void MainWindow::on_rebuildTceButton_clicked()
{
    delete Tcexlsx;
    Tcexlsx = nullptr;
    ui->infoTextEdit->append("已重建Tce\n");
}



void MainWindow::on_readT07Button_clicked()
{

    // 清空每一行
    for (auto& row : T07) {
        row.clear();
    }
    // 清空主向量
    T07.clear();

    QString fileName = QFileDialog::getOpenFileName(this,"Open Excel File","","Exel file(*.xls *.xlsx)");

    if (fileName.isEmpty())
    {
        //        QMessageBox::warning(this,"警告","请选择一个文件");
    }
    else
    {
        QXlsx::Document xlsx(fileName);
        QXlsx::CellRange range = xlsx.dimension();
        //起始行列号，row是行，col是列
        //使用数组来存储
        for (int row = range.firstRow(); row < range.lastRow()+1; row++)
        {
            std::vector<QVariant> data_tmp;

            for (int col = range.firstColumn(); col < range.lastColumn()+1; col++)
            {
                data_tmp.push_back(xlsx.read(row, col));
            }
            T07.push_back(data_tmp);
        }
        ui->infoTextEdit->append("已读取T07\n");
    }

}


void MainWindow::on_readTceButton_clicked()
{

    // 清空每一行
    for (auto& row : Tce) {
        row.clear();
    }
    // 清空主向量
    Tce.clear();

    QString fileName = QFileDialog::getOpenFileName(this,"Open Excel File","","Exel file(*.xls *.xlsx)");

    if (fileName.isEmpty())
    {
        //        QMessageBox::warning(this,"警告","请选择一个文件");
    }
    else
    {
        QXlsx::Document xlsx(fileName);
        QXlsx::CellRange range = xlsx.dimension();
        for (int row = range.firstRow(); row < range.lastRow()+1; row++)
        {
            std::vector<QVariant> data_tmp;
            for (int col = range.firstColumn(); col < range.lastColumn()+1; col++)
            {
                data_tmp.push_back(xlsx.read(row, col));
            }
            Tce.push_back(data_tmp);
        }
        ui->infoTextEdit->append("已读取Tce\n");
    }
}


void MainWindow::on_computeButton_clicked()
{
    if (T07.empty())
    {
        QMessageBox::information(this,"提示","缺少T07");
        return;
    }
    if (Tce.empty())
    {
        QMessageBox::information(this,"提示","缺少Tce");
        return;
    }
    if (demonstrations.empty())
    {
        QMessageBox::information(this,"提示","缺少示教轨迹");
        return;
    }

    Eigen::MatrixXd result = calibration(Tce,T07,demonstrations);

    // 清空每一行
    for (auto& row : res) {
        row.clear();
    }
    // 清空主向量
    res.clear();


    for (int i = 0; i < result.rows(); ++i)
    {
        std::vector<QVariant> row;
        for (int j = 0; j < result.cols(); ++j)
        {
            row.push_back(QVariant(result(i, j)));
        }
        res.push_back(row);
    }

    ui->infoTextEdit->append("已成功计算得到复现轨迹\n");
}



void MainWindow::on_readDemoButton_clicked()
{
    // 清空每一行
    for (auto& row : demonstrations) {
        row.clear();
    }
    // 清空主向量
    demonstrations.clear();

    QString fileName = QFileDialog::getOpenFileName(this,"Open Excel File","","Exel file(*.xls *.xlsx)");

    if (fileName.isEmpty())
    {
        //        QMessageBox::warning(this,"警告","请选择一个文件");
    }
    else
    {
        QXlsx::Document xlsx(fileName);
        QXlsx::CellRange range = xlsx.dimension();
        for (int row = range.firstRow(); row < range.lastRow()+1; row++)
        {
            std::vector<QVariant> data_tmp;
            for (int col = range.firstColumn(); col < range.lastColumn()+1; col++)
            {
                data_tmp.push_back(xlsx.read(row, col));
            }
            demonstrations.push_back(data_tmp);
        }
        ui->infoTextEdit->append("已读取示教轨迹\n");
    }
}




void MainWindow::on_connectRobButton_clicked()
{
    if (ui->robot_ip->text().isEmpty())
    {
        QMessageBox::information(this,"提示","机械臂IP为空");
        return;
    }
    char *robotip = ui->robot_ip->text().toUtf8().data();
//    QString robotport = ui->robot_port->text();

//    XEnableDebugOutput(0);
//    int res = XCreateRobHalConfig(&RobHandle, robotip, 2, 2);
//    XWaitCmdSendDone(RobHandle);
//    tcpSocket->connectToHost(QHostAddress(robotip), robotport.toInt());
//    if (!res)
//    {
//        QMessageBox::information(this,"连接提示","连接机械臂成功");
//        ui->infoTextEdit->append("连接机械臂成功\n");
//    }
//    else
//    {
//        QMessageBox::information(this,"连接提示","连接机械臂失败");
//        ui->infoTextEdit->append("连接机械臂失败\n");
//    }
// ***************************************************************************************

    if (robotapi != nullptr)
    {
        QMessageBox::information(this,"提示","已连接机械臂");
        return;
    }

    ESString ip(robotip);
    robotapi = new EstunRemoteApiLib;
    bool ret = false;
    ret = robotapi->connectToServer(ip);

    if (!ret)
    {
        QMessageBox::information(this,"连接提示","连接机械臂失败");
        ui->infoTextEdit->append("连接机械臂失败\n");

    }
    else
    {
        QMessageBox::information(this,"连接提示","连接机械臂成功");
        ui->infoTextEdit->append("连接机械臂成功\n");
    }
}


void MainWindow::on_dconnectRobButton_clicked()
{
//    commandTimer->stop();

//    if (RobHandle == -1)
//    {
//        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
//        return;
//    }

//    int res = XDeleteRobHal(RobHandle);
//    RobHandle = -1;
//    if (!res)
//    {
//        QMessageBox::information(this,"连接提示","已断开连接");
//        ui->infoTextEdit->append("已断开连接机械臂\n");
//    }
//    tcpSocket->disconnectFromHost();

    if (robotapi == nullptr)
    {
        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
        return;
    }
    bool ret = robotapi->disConnect();
    delete robotapi;
    robotapi = nullptr;
    if (ret)
    {
        QMessageBox::information(this,"连接提示","已断开连接");
        ui->infoTextEdit->append("已断开连接机械臂\n");
    }
}


void MainWindow::on_initRobButton_clicked()
{
//    if (RobHandle == -1)
//    {
//        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
//        return;
//    }

//    XServoOn(RobHandle);
//    XWaitCmdSendDone(RobHandle);

//    // 建立定时器，50毫秒后设置机械臂模式
//    QTimer::singleShot(50, this, [=]() {
//        XSetSysMode(RobHandle, 3);
//        XWaitCmdSendDone(RobHandle);
//        XSetSpeed(RobHandle, 100);
//    });
//    ui->infoTextEdit->append("机械臂已上使能并设为手动模式\n");

    if (robotapi == nullptr)
    {
        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
        return;
    }

    if (robotapi->E_GetErrorId() != 0)
    {
        robotapi->E_ClearError();
    }

    E_ROB_PERMIT permit = robotapi->E_AcquirePermit();
    if (permit.m_mainctrlcode <= 1)
    {
        QMessageBox::information(this,"提示","机械臂未能获取运动权限");
        return;
    }

    bool ret = robotapi->E_SetServoOn(true);
    if (!ret)
    {
        QMessageBox::information(this,"提示","机械臂未成功上使能");
        return;
    }

    ret = robotapi->E_SetSysMode(E_SysModeType::API);
    if (!ret)
    {
        QMessageBox::information(this,"提示","机械臂未成功设置为api模式");
        return;
    }

    ui->infoTextEdit->append("机械臂已初始化成功并设为API模式\n");


}


void MainWindow::on_initPointButton_clicked()
{

    if (robotapi == nullptr)
    {
        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
        return;
    }

    if (robotapi->E_GetErrorId() != 0)
    {
        robotapi->E_ClearError();
    }

    E_ROB_PERMIT permit = robotapi->E_AcquirePermit();
    if (permit.m_mainctrlcode <= 1)
    {
        QMessageBox::information(this,"提示","机械臂未能获取运动权限");
        return;
    }

    bool ret = robotapi->E_SetServoOn(true);
    if (!ret)
    {
        QMessageBox::information(this,"提示","机械臂未成功上使能");
        return;
    }

    ret = robotapi->E_SetSysMode(E_SysModeType::API);
    if (!ret)
    {
        QMessageBox::information(this,"提示","机械臂未成功设置为api模式");
        return;
    }


    robotapi->E_MotionStop();

    if (!res.empty())
    {
        ui->infoTextEdit->append("机械臂已初始化成功并往起始点运动\n");
        E_ROB_POSCFG cfg1;
        robotapi->E_GetCurWPos().GetCfgValue(cfg1);
        E_ROB_SPEED vel1;
        vel1.set_Tcp(200);
        E_ROB_POS pos1 = E_ROB_POS(cfg1, res[0][0].toDouble(), res[0][1].toDouble(),res[0][2].toDouble(), res[0][5].toDouble(), res[0][4].toDouble(), res[0][3].toDouble());
        robotapi->E_MovL2(pos1, vel1);
        ui->infoTextEdit->append("机械臂已运动到起始点\n");
    }
    else
    {
        QMessageBox::information(this,"提示","缺少起始点");
    }
}



void MainWindow::on_stopRobButton_clicked()
{
//    if (RobHandle == -1)
//    {
//        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
//        return;
//    }

//    XAbort(RobHandle);
//    XWaitCmdSendDone(RobHandle);
//    ui->infoTextEdit->append("已中止机械臂操作，请重新下达运动指令\n");

    if (robotapi == nullptr)
    {
        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
        return;
    }

    bool ret = robotapi->E_MotionStop();
    if (ret)
    {
        ui->infoTextEdit->append("已停止机械臂运动，请重新下达运动指令\n");
    }
}


void MainWindow::beforeStart()
{
//    if (RobHandle == -1)
//    {
//        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
//        return;
//    }

//    XSYSTEMSTATE sys;
//    memset(&sys,0,sizeof(XSYSTEMSTATE));
//    XGetSystemState(RobHandle, &sys);

//    if (sys.Enable == 0)
//    {
//        QMessageBox::information(this,"提示","机械臂未上使能，请初始化机械臂");
//        return;
//    }

//    if (res.empty())
//    {
//        QMessageBox::information(this,"提示","缺少复现轨迹");
//        return;
//    }

//    worker->setRob(RobHandle);
//    worker->setRes(res);
//    emit startWorking();

    if (res.empty())
    {
        QMessageBox::information(this,"提示","缺少复现轨迹");
        return;
    }


    if (robotapi == nullptr)
    {
        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
        return;
    }

    if (!robotapi->isConnected())
    {
        QMessageBox::information(this,"提示","机械臂未连接服务，请断开并重新连接");
        return;
    }

    if (robotapi->E_GetServoOn() != E_ServoStatusType::ServoOn)
    {
        QMessageBox::information(this,"提示","机械臂未上使能，请初始化机械臂");
        return;
    }

    if (robotapi->E_GetSysMode() != E_SysModeType::API)
    {
        QMessageBox::information(this,"提示","机械臂未设置为api模式，请初始化机械臂");
        return;
    }

    robotapi->E_MotionStop();
//    robotapi->E_SetGlobalSpeed(100);
    worker->setRob(robotapi);
    worker->setRes(res);
    emit startWorking();
}




//void MainWindow::on_startRobButton_clicked()
//{

////    for (const auto& row : res) {
////        commandList << "MovL;P," + row[0].toString() + "," + row[1].toString() + "," + row[2].toString() + "," + row[3].toString() + "," + row[4].toString() + "," + row[5].toString() + ",cnt=A\r";
////    }

////    currentCommandIndex = 0;
////    commandTimer->stop();
////    commandTimer->start(5000);
//    if (RobHandle == -1)
//    {
//        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
//        return;
//    }

//    XSYSTEMSTATE sys;
//    memset(&sys,0,sizeof(XSYSTEMSTATE));
//    XGetSystemState(RobHandle, &sys);

//    if (sys.Enable == 0)
//    {
//        QMessageBox::information(this,"提示","机械臂未上使能，请初始化机械臂");
//        return;
//    }

//    if (res.empty())
//    {
//        QMessageBox::information(this,"提示","缺少复现轨迹");
//        return;
//    }




//    XPOINT MPos;
//    memset(&MPos,0,sizeof(XPOINT));
//    XGetWPoint(RobHandle, &MPos); // 初始化


//    XMOVPOINTADD Data;
//    Data.DataInit();
//    Data.Cnt = -1;

//    for (size_t i = 0; i < res.size(); i++)
//    {
//        XGetSystemState(RobHandle, &sys);
//        XWaitCmdSendDone(RobHandle);
//        if (sys.CmdQueFull != 2)
//        {
//            MPos.PosData.X = res[i][0].toDouble();
//            MPos.PosData.Y = res[i][1].toDouble();
//            MPos.PosData.Z = res[i][2].toDouble();

//            MPos.PosData.A = res[i][3].toDouble();
//            MPos.PosData.B = res[i][4].toDouble();
//            MPos.PosData.C = res[i][5].toDouble();

////            Data.Vel = ; // 速度待设置
//            ui->infoTextEdit->append("正在发送第" + QString::number(i+1) + "组数据，请注意！\n");
//            XMovLAdd(RobHandle, MPos, Data);
//        }
//        else
//        {
//            i--;
//        }
//    }
//    ui->infoTextEdit->append("运动命令已全部发送完毕\n");
//}

//void MainWindow::sendNextCommand()
//{

//    if (currentCommandIndex < commandList.size()) {
//        tcpSocket->write(commandList.at(currentCommandIndex).toUtf8());
//        currentCommandIndex++;
//    } else {
//        // 所有命令发送完毕，停止定时器
//        commandTimer->stop();
//        QMessageBox::information(this,"发送提示","数据已全部发送");
//    }
//}


void MainWindow::on_pauseRobButton_clicked()
{
//    commandTimer->stop();
    if (robotapi == nullptr)
    {
        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
        return;
    }

    bool ret = robotapi->E_MotionPause();
    if (ret)
    {
        QMessageBox::warning(this,"提示","已暂停机械臂运动，点击继续可恢复");
    }
    else
    {
        QMessageBox::warning(this,"提示","暂停机械臂运动失败！");
    }
}

void MainWindow::on_resumeRobButton_clicked()
{
//    commandTimer->start(5000);
    if (robotapi == nullptr)
    {
        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
        return;
    }

    bool ret = robotapi->E_MotionContinue();
    if (ret)
    {
        QMessageBox::warning(this,"提示","已恢复机械臂运动");
    }
    else
    {
        QMessageBox::warning(this,"提示","恢复机械臂运动失败！");
    }
}


void MainWindow::on_clearInfoButton_clicked()
{
    ui->infoTextEdit->clear();
    ui->infoTextEdit->setText("消息打印：");
}



void MainWindow::on_saveT07Button_clicked()
{


    if (robotapi == nullptr)
    {
        QMessageBox::information(this,"提示","机械臂未连接，请连接机械臂");
        return;
    }

    if(!T07xlsx){
        QString filePath = QFileDialog::getSaveFileName(this, "Save Excel File", "", "Excel Files (*.xlsx)");
        if (filePath.isEmpty()) return;
        T07filePath = filePath;


        T07xlsx = new QXlsx::Document;
        currentColumn = 1;
    }

    E_ROB_POS cpos = robotapi->E_GetCurWPos();
    double c = cpos.getA() * M_PI / 180 ; // c 对应 z
    double b = cpos.getB() * M_PI / 180 ; // b 对应 y
    double a = cpos.getC() * M_PI / 180 ; // a 对应 x

    T07xlsx->write(4,currentColumn,0);
    T07xlsx->write(4,currentColumn+1,0);
    T07xlsx->write(4,currentColumn+2,0);
    T07xlsx->write(4,currentColumn+3,1);

    T07xlsx->write(1,currentColumn+3,cpos.getX()/1000);
    T07xlsx->write(2,currentColumn+3,cpos.getY()/1000);
    T07xlsx->write(3,currentColumn+3,cpos.getZ()/1000);

    T07xlsx->write(1,currentColumn, std::cos(b)*std::cos(c));
    T07xlsx->write(1,currentColumn+1, std::cos(c)*std::sin(a)*std::sin(b)-std::cos(a)*std::sin(c));
    T07xlsx->write(1,currentColumn+2, std::sin(a)*std::sin(c)+std::cos(a)*std::cos(c)*std::sin(b));
    T07xlsx->write(2,currentColumn, std::cos(b)*std::sin(c));
    T07xlsx->write(2,currentColumn+1, std::cos(a)*std::cos(c)+std::sin(a)*std::sin(b)*std::sin(c));
    T07xlsx->write(2,currentColumn+2, std::cos(a)*std::sin(b)*std::sin(c)-std::cos(c)*std::sin(a));
    T07xlsx->write(3,currentColumn, -std::sin(b));
    T07xlsx->write(3,currentColumn+1, std::cos(b)*std::sin(a));
    T07xlsx->write(3,currentColumn+2, std::cos(a)*std::cos(b));

    T07xlsx->saveAs(T07filePath);
    ui->infoTextEdit->append("已将T07保存至" + QString::number(currentColumn) + "-" + QString::number(currentColumn+3) + "列\n");
                                 currentColumn = currentColumn + 4;

}


void MainWindow::on_rebuildT07Button_clicked()
{
    delete T07xlsx;
    T07xlsx = nullptr;
    ui->infoTextEdit->append("已重建T07\n");
}







void MainWindow::on_showDataButton_clicked()
{


    if (res.empty())
    {
        QMessageBox::information(this,"提示","缺少复现轨迹");
        return;
    }

    Q3DScatter *graph = new Q3DScatter();
    QWidget *container = QWidget::createWindowContainer(graph, this);


    if (!graph->hasContext()) {
        QMessageBox::critical(this, "Error", "Couldn't initialize the OpenGL context.");
        delete container;
        return;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    widget->setWindowTitle(QStringLiteral("Show result"));

    QComboBox *themeList = new QComboBox(widget);
    themeList->addItem(QStringLiteral("Qt"));
    themeList->addItem(QStringLiteral("Primary Colors"));
    themeList->addItem(QStringLiteral("Digia"));
    themeList->addItem(QStringLiteral("Stone Moss"));
    themeList->addItem(QStringLiteral("Army Blue"));
    themeList->addItem(QStringLiteral("Retro"));
    themeList->addItem(QStringLiteral("Ebony"));
    themeList->addItem(QStringLiteral("Isabelle"));
    themeList->setCurrentIndex(1);

    QPushButton *labelButton = new QPushButton(widget);
    labelButton->setText(QStringLiteral("Change label style"));

    QPushButton *dataButton = new QPushButton(widget);
    dataButton->setText(QStringLiteral("Change data"));

    QCheckBox *smoothCheckBox = new QCheckBox(widget);
    smoothCheckBox->setText(QStringLiteral("Smooth dots"));
    smoothCheckBox->setChecked(true);

    QComboBox *itemStyleList = new QComboBox(widget);
    itemStyleList->addItem(QStringLiteral("Sphere"), int(QAbstract3DSeries::MeshSphere));
    itemStyleList->addItem(QStringLiteral("Cube"), int(QAbstract3DSeries::MeshCube));
    itemStyleList->addItem(QStringLiteral("Minimal"), int(QAbstract3DSeries::MeshMinimal));
    itemStyleList->addItem(QStringLiteral("Point"), int(QAbstract3DSeries::MeshPoint));
    itemStyleList->setCurrentIndex(3);

    QPushButton *cameraButton = new QPushButton(widget);
    cameraButton->setText(QStringLiteral("Change camera preset"));

    QPushButton *itemCountButton = new QPushButton(widget);
    itemCountButton->setText(QStringLiteral("Toggle item count"));

    QCheckBox *backgroundCheckBox = new QCheckBox(widget);
    backgroundCheckBox->setText(QStringLiteral("Show background"));
    backgroundCheckBox->setChecked(true);

    QCheckBox *gridCheckBox = new QCheckBox(widget);
    gridCheckBox->setText(QStringLiteral("Show grid"));
    gridCheckBox->setChecked(true);

    QComboBox *shadowQuality = new QComboBox(widget);
    shadowQuality->addItem(QStringLiteral("None"));
    shadowQuality->addItem(QStringLiteral("Low"));
    shadowQuality->addItem(QStringLiteral("Medium"));
    shadowQuality->addItem(QStringLiteral("High"));
    shadowQuality->addItem(QStringLiteral("Low Soft"));
    shadowQuality->addItem(QStringLiteral("Medium Soft"));
    shadowQuality->addItem(QStringLiteral("High Soft"));
    shadowQuality->setCurrentIndex(3);

    QFontComboBox *fontList = new QFontComboBox(widget);
    fontList->setCurrentFont(QFont("Arial"));

    vLayout->addWidget(labelButton, 0, Qt::AlignTop);
    vLayout->addWidget(dataButton, 0, Qt::AlignTop);
    vLayout->addWidget(cameraButton, 0, Qt::AlignTop);
    vLayout->addWidget(itemCountButton, 0, Qt::AlignTop);
    vLayout->addWidget(backgroundCheckBox);
    vLayout->addWidget(gridCheckBox);
    vLayout->addWidget(smoothCheckBox, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(QStringLiteral("Change dot style")));
    vLayout->addWidget(itemStyleList);
    vLayout->addWidget(new QLabel(QStringLiteral("Change theme")));
    vLayout->addWidget(themeList);
    vLayout->addWidget(new QLabel(QStringLiteral("Adjust shadow quality")));
    vLayout->addWidget(shadowQuality);
    vLayout->addWidget(new QLabel(QStringLiteral("Change font")));
    vLayout->addWidget(fontList, 1, Qt::AlignTop);



    ScatterDataModifier *modifier = new ScatterDataModifier(graph, res, widget);

    QObject::connect(cameraButton, &QPushButton::clicked, modifier,
                     &ScatterDataModifier::changePresetCamera);
    QObject::connect(labelButton, &QPushButton::clicked, modifier,
                     &ScatterDataModifier::changeLabelStyle);
    QObject::connect(dataButton, &QPushButton::clicked, modifier,
                     &ScatterDataModifier::changeData);
    QObject::connect(itemCountButton, &QPushButton::clicked, modifier,
                     &ScatterDataModifier::toggleItemCount);

    QObject::connect(backgroundCheckBox, &QCheckBox::stateChanged, modifier,
                     &ScatterDataModifier::setBackgroundEnabled);
    QObject::connect(gridCheckBox, &QCheckBox::stateChanged, modifier,
                     &ScatterDataModifier::setGridEnabled);
    QObject::connect(smoothCheckBox, &QCheckBox::stateChanged, modifier,
                     &ScatterDataModifier::setSmoothDots);

    QObject::connect(modifier, &ScatterDataModifier::backgroundEnabledChanged,
                     backgroundCheckBox, &QCheckBox::setChecked);
    QObject::connect(modifier, &ScatterDataModifier::gridEnabledChanged,
                     gridCheckBox, &QCheckBox::setChecked);

    QObject::connect(itemStyleList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeStyle(int)));
    QObject::connect(themeList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeTheme(int)));

    QObject::connect(shadowQuality, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeShadowQuality(int)));

    QObject::connect(modifier, &ScatterDataModifier::shadowQualityChanged, shadowQuality,
                     &QComboBox::setCurrentIndex);

    QObject::connect(graph, &Q3DScatter::shadowQualityChanged, modifier,
                     &ScatterDataModifier::shadowQualityUpdatedByVisual);

    QObject::connect(fontList, &QFontComboBox::currentFontChanged, modifier,
                     &ScatterDataModifier::changeFont);

    QObject::connect(modifier, &ScatterDataModifier::fontChanged, fontList,
                     &QFontComboBox::setCurrentFont);

    connect(modifier, SIGNAL(sendData(std::vector<int>)), this, SLOT(changeData(std::vector<int>)));

    widget->show();

}

void MainWindow::changeData(std::vector<int> startAndgoal)
{
    qDebug()<<startAndgoal[0]<<startAndgoal[1];
    std::vector<std::vector<QVariant>>  new_motion_data;
    int start = startAndgoal[0];
    int goal = startAndgoal[1];
    for (int row = start; row <= goal; row++)
    {
        std::vector<QVariant> data_tmp;
        for (int col = 0; col < 6; col++)
        {
            data_tmp.push_back(res[row][col]);
        }
        new_motion_data.push_back(data_tmp);
    }
    res = new_motion_data;
    ui->infoTextEdit->append("复现轨迹已修改，请注意！\n");
    on_showDataButton_clicked();
}





void MainWindow::on_onlyshowButton_clicked()
{
    if (demonstrations.empty())
    {
        QMessageBox::information(this,"提示","缺少示教轨迹");
        return;
    }

    if (res.empty())
    {
        QMessageBox::information(this,"提示","缺少复现轨迹");
        return;
    }

    Q3DScatter *graph = new Q3DScatter();
    QWidget *container = QWidget::createWindowContainer(graph, this);


    if (!graph->hasContext()) {
        QMessageBox::critical(this, "Error", "Couldn't initialize the OpenGL context.");
        delete container;
        return;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    widget->setWindowTitle(QStringLiteral("Show result"));

    QComboBox *themeList = new QComboBox(widget);
    themeList->addItem(QStringLiteral("Qt"));
    themeList->addItem(QStringLiteral("Primary Colors"));
    themeList->addItem(QStringLiteral("Digia"));
    themeList->addItem(QStringLiteral("Stone Moss"));
    themeList->addItem(QStringLiteral("Army Blue"));
    themeList->addItem(QStringLiteral("Retro"));
    themeList->addItem(QStringLiteral("Ebony"));
    themeList->addItem(QStringLiteral("Isabelle"));
    themeList->setCurrentIndex(1);

    QPushButton *labelButton = new QPushButton(widget);
    labelButton->setText(QStringLiteral("Change label style"));



    QCheckBox *smoothCheckBox = new QCheckBox(widget);
    smoothCheckBox->setText(QStringLiteral("Smooth dots"));
    smoothCheckBox->setChecked(true);

    QComboBox *itemStyleList = new QComboBox(widget);
    itemStyleList->addItem(QStringLiteral("Sphere"), int(QAbstract3DSeries::MeshSphere));
    itemStyleList->addItem(QStringLiteral("Cube"), int(QAbstract3DSeries::MeshCube));
    itemStyleList->addItem(QStringLiteral("Minimal"), int(QAbstract3DSeries::MeshMinimal));
    itemStyleList->addItem(QStringLiteral("Point"), int(QAbstract3DSeries::MeshPoint));
    itemStyleList->setCurrentIndex(3);

    QPushButton *cameraButton = new QPushButton(widget);
    cameraButton->setText(QStringLiteral("Change camera preset"));

    QPushButton *itemCountButton = new QPushButton(widget);
    itemCountButton->setText(QStringLiteral("Toggle item count"));

    QCheckBox *backgroundCheckBox = new QCheckBox(widget);
    backgroundCheckBox->setText(QStringLiteral("Show background"));
    backgroundCheckBox->setChecked(true);

    QCheckBox *gridCheckBox = new QCheckBox(widget);
    gridCheckBox->setText(QStringLiteral("Show grid"));
    gridCheckBox->setChecked(true);

    QComboBox *shadowQuality = new QComboBox(widget);
    shadowQuality->addItem(QStringLiteral("None"));
    shadowQuality->addItem(QStringLiteral("Low"));
    shadowQuality->addItem(QStringLiteral("Medium"));
    shadowQuality->addItem(QStringLiteral("High"));
    shadowQuality->addItem(QStringLiteral("Low Soft"));
    shadowQuality->addItem(QStringLiteral("Medium Soft"));
    shadowQuality->addItem(QStringLiteral("High Soft"));
    shadowQuality->setCurrentIndex(3);

    QFontComboBox *fontList = new QFontComboBox(widget);
    fontList->setCurrentFont(QFont("Arial"));

    vLayout->addWidget(labelButton, 0, Qt::AlignTop);

    vLayout->addWidget(cameraButton, 0, Qt::AlignTop);
    vLayout->addWidget(itemCountButton, 0, Qt::AlignTop);
    vLayout->addWidget(backgroundCheckBox);
    vLayout->addWidget(gridCheckBox);
    vLayout->addWidget(smoothCheckBox, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(QStringLiteral("Change dot style")));
    vLayout->addWidget(itemStyleList);
    vLayout->addWidget(new QLabel(QStringLiteral("Change theme")));
    vLayout->addWidget(themeList);
    vLayout->addWidget(new QLabel(QStringLiteral("Adjust shadow quality")));
    vLayout->addWidget(shadowQuality);
    vLayout->addWidget(new QLabel(QStringLiteral("Change font")));
    vLayout->addWidget(fontList, 1, Qt::AlignTop);


    std::vector<std::vector<QVariant>> toshow;

    toshow.insert(toshow.end(),res.begin(),res.end());
    toshow.insert(toshow.end(),demonstrations.begin(),demonstrations.end());
    ScatterDataModifier *modifier = new ScatterDataModifier(graph, toshow, widget);

    QObject::connect(cameraButton, &QPushButton::clicked, modifier,
                     &ScatterDataModifier::changePresetCamera);
    QObject::connect(labelButton, &QPushButton::clicked, modifier,
                     &ScatterDataModifier::changeLabelStyle);

    QObject::connect(itemCountButton, &QPushButton::clicked, modifier,
                     &ScatterDataModifier::toggleItemCount);

    QObject::connect(backgroundCheckBox, &QCheckBox::stateChanged, modifier,
                     &ScatterDataModifier::setBackgroundEnabled);
    QObject::connect(gridCheckBox, &QCheckBox::stateChanged, modifier,
                     &ScatterDataModifier::setGridEnabled);
    QObject::connect(smoothCheckBox, &QCheckBox::stateChanged, modifier,
                     &ScatterDataModifier::setSmoothDots);

    QObject::connect(modifier, &ScatterDataModifier::backgroundEnabledChanged,
                     backgroundCheckBox, &QCheckBox::setChecked);
    QObject::connect(modifier, &ScatterDataModifier::gridEnabledChanged,
                     gridCheckBox, &QCheckBox::setChecked);

    QObject::connect(itemStyleList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeStyle(int)));
    QObject::connect(themeList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeTheme(int)));

    QObject::connect(shadowQuality, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeShadowQuality(int)));

    QObject::connect(modifier, &ScatterDataModifier::shadowQualityChanged, shadowQuality,
                     &QComboBox::setCurrentIndex);

    QObject::connect(graph, &Q3DScatter::shadowQualityChanged, modifier,
                     &ScatterDataModifier::shadowQualityUpdatedByVisual);

    QObject::connect(fontList, &QFontComboBox::currentFontChanged, modifier,
                     &ScatterDataModifier::changeFont);

    QObject::connect(modifier, &ScatterDataModifier::fontChanged, fontList,
                     &QFontComboBox::setCurrentFont);



    widget->show();
}


void MainWindow::on_compareButton_clicked()
{
    if (demonstrations.empty())
    {
        QMessageBox::information(this,"提示","缺少示教轨迹");
        return;
    }

    if (res.empty())
    {
        QMessageBox::information(this,"提示","缺少复现轨迹");
        return;
    }

    dif *widget = new dif();
    widget->showdata(demonstrations, res);

    widget->setWindowTitle("I am widget"); // 设置窗口标题
    widget->show(); // 显示窗口
}

