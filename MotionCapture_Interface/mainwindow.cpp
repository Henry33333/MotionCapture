#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_readData_triggered()
{
    QString fileName= QFileDialog::getOpenFileName
        (this,"选择一个文件",QCoreApplication::applicationFilePath(),tr("Xlsx files(*.xlsx);;All files (*.*)"));
    if (fileName.isEmpty())
    {
        //        QMessageBox::warning(this,"警告","请选择一个文件");
    }
    else
    {
        QXlsx::Document xlsx(fileName);
        QXlsx::CellRange range = xlsx.dimension();
        qDebug() << range.firstRow() << range.lastRow()<<range.firstColumn()<<range.lastColumn();       //起始行列号，row是行，col是列

        //使用数组来存储
        Motion_Data_length = range.lastRow()-range.firstRow()+1;
        Motion_Data = new int *[range.lastRow()-range.firstRow()+1];
        for (int i = 0; i < range.lastRow()-range.firstRow()+1; i++)
        {
            Motion_Data[i] = new int [range.lastRow()-range.firstRow()+1] {};//或者()代替{},每个元素都初始化为0
        }
        for (int row = range.firstRow(); row < range.lastRow()+1; row++)
        {
            for (int col = range.firstColumn(); col < range.lastColumn()+1; col++)
            {
                Motion_Data[row-range.firstRow()][col-range.firstColumn()] = xlsx.read(row, col).toInt();
            }
        }
}

