#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>


//*********************************************************
#include <string.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <winsock2.h>

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>

#pragma warning( disable : 4996 )

#include "SeekerSDKTypes.h"
#include "SeekerSDKClient.h"
#include "Utility.h"


//*********************************************************

#include <xlsxdocument.h>
#include <xlsxchartsheet.h>
#include <xlsxcellrange.h>
#include <xlsxchart.h>
#include <xlsxrichstring.h>
#include <xlsxworkbook.h>

//*********************************************************
#include "cali.h"

//*********************************************************
#include "StructDef.h"
#include "x1motlibface.h"
#include "Worker.h"
//*********************************************************
#include "scatterdatamodifier.h"
#include "dif.h"
//*********************************************************
#include "EstunRemoteApiLib/EstunRemoteApiLib.h"

//*********************************************************
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData); //回调函数、全局函数

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    static void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData);		// receives data from the server 回调函数、一开始作为类的静态函数，后改成全局函数
    int CreateClient(char* serverIp);
    void ConnectSeeker();
    void sendNextCommand();

signals:
    void startWorking();

private slots:
    void on_readT07Button_clicked();

    void on_readTceButton_clicked();

    void on_computeButton_clicked();

    void on_readDemoButton_clicked();

    void on_connectRobButton_clicked();

    void on_dconnectRobButton_clicked();

    void on_initRobButton_clicked();

//    void on_startRobButton_clicked();
    void beforeStart();

    void on_pauseRobButton_clicked();

    void on_resumeRobButton_clicked();

    void on_clearInfoButton_clicked();

    void on_seekIpButton_clicked();

    void on_testClientButton_clicked();

    void on_saveT07Button_clicked();

    void on_stopRobButton_clicked();

    void on_rebuildT07Button_clicked();

    void on_saveTceButton_clicked();

    void on_rebuildTceButton_clicked();

    void on_showDataButton_clicked();

    void changeData(std::vector<int> startAndgoal);


    void on_initPointButton_clicked();

    void on_onlyshowButton_clicked();

    void on_compareButton_clicked();

private:
    Ui::MainWindow *ui;
    SeekerSDKClient *theClient;
    char szMyIPAddress[128] = "";
    char szServerIPAddress[128] = "";


    std::vector<std::vector<QVariant>> Tce;
    std::vector<std::vector<QVariant>> T07;
    std::vector<std::vector<QVariant>> demonstrations;
    std::vector<std::vector<QVariant>> res;

//    QTcpSocket *tcpSocket;
//    QTimer *commandTimer;
//    QStringList commandList;
//    int currentCommandIndex = 0;
//    int RobHandle = -1;


    QXlsx::Document *T07xlsx;
    int currentColumn;
    QString T07filePath;


    QThread workThread;
    Worker *worker;

    EstunRemoteApiLib *robotapi;

};
#endif // MAINWINDOW_H
