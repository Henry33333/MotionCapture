#include "track.h"
#include "ui_track.h"


track::track(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::track),
    robot_deg(7),
    intervalTime(0.2f)
{
    ui->setupUi(this);
}

track::~track()
{
    delete ui;
}

void track::readXlsx(QString &FilePath)
{
    QAxObject *excel = NULL;
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;

    excel = new QAxObject("Excel.Application");
    excel->dynamicCall("SetVisible(bool)",true);
    workbooks = excel->querySubObject("WorkBooks");

    workbook = workbooks->querySubObject("Open(QString&)",FilePath);

    QAxObject *worksheets = workbook->querySubObject("WorkSheets");


 // 获取sheet的数量
    int iWorkSheet = worksheets->property("Count").toInt();
    if (iWorkSheet < 0)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("工作簿小于0个"));
        return;
    }

    QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);
    QAxObject *usedrange = worksheet->querySubObject("UsedRange");

 // 行数与列数
    row = usedrange->querySubObject("Rows")->property("Count").toInt();
    col = usedrange->querySubObject("Columns")->property("Count").toInt();
    qDebug() << row;
    qDebug() << col;

    if (row <= 0 || col <= 0)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("工作sheet的行列为空"));
        return;
    }

 // 获取第6行第6列的内容
    QAxObject *range1 = worksheet->querySubObject("Range(QString)","F6:F6");
    QString str = "";
    str = range1->property("Value").toString();
    qDebug() << str;

 // 保存关闭退出
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    if (excel)
    {
        delete excel;
        excel = NULL;
    }
}

// 导入按钮
void track::on_ImportButton_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName(this,QStringLiteral("选择Excel文件"),"",tr("Exel file(*.xls *.xlsx)"));
    readXlsx(FilePath);
    ui->lineEdit->setText("111");
}



//void track::on_ConnectButton_clicked()
//{

//    new_robot = new robot();
//}


//void track::on_SendButton_clicked()
//{
////    new_robot->SendJointSpeed();
////    my_timer->start();
//    angular_Waypointlist();
//}


//void track::on_DisconnectButton_clicked()
//{
//    new_robot->Disconnect();
//    delete new_robot;
//}

//void track::on_TestButton_3_clicked()
//{
//    vector<vector<int>> a = new_robot->test();
//}


//void track::on_RunButton_2_clicked()
//{
//    vector<vector<int>> data = new_robot->test();
//    float interval = 0.1;
//    new_robot->run(data,interval);
//}


//void track::on_StopButton_clicked()
//{
//    new_robot->base->Stop();
//}


//void track::on_pushButton_clicked()
//{
//    intervalTime = ui->lineEdit->text().toFloat();
//}

