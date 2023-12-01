#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QFile>
#include <QCoreApplication>
#include <QAxObject>
#include "header/xlsxdocument.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_readData_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
