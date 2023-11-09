/********************************************************************************
** Form generated from reading UI file 'track.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACK_H
#define UI_TRACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_track
{
public:
    QPushButton *ImportButton;
    QPushButton *ConnectButton;
    QPushButton *SendButton;
    QTextEdit *textEdit;
    QPushButton *DisconnectButton;
    QPushButton *StopButton;
    QPushButton *RunButton_2;
    QPushButton *TestButton_3;
    QPushButton *InitialButton;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *track)
    {
        if (track->objectName().isEmpty())
            track->setObjectName("track");
        track->resize(851, 446);
        ImportButton = new QPushButton(track);
        ImportButton->setObjectName("ImportButton");
        ImportButton->setGeometry(QRect(70, 20, 111, 31));
        ConnectButton = new QPushButton(track);
        ConnectButton->setObjectName("ConnectButton");
        ConnectButton->setGeometry(QRect(70, 70, 111, 31));
        SendButton = new QPushButton(track);
        SendButton->setObjectName("SendButton");
        SendButton->setGeometry(QRect(70, 160, 111, 31));
        textEdit = new QTextEdit(track);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(270, 40, 521, 161));
        DisconnectButton = new QPushButton(track);
        DisconnectButton->setObjectName("DisconnectButton");
        DisconnectButton->setGeometry(QRect(70, 210, 111, 31));
        StopButton = new QPushButton(track);
        StopButton->setObjectName("StopButton");
        StopButton->setGeometry(QRect(70, 260, 111, 41));
        RunButton_2 = new QPushButton(track);
        RunButton_2->setObjectName("RunButton_2");
        RunButton_2->setGeometry(QRect(70, 320, 111, 41));
        TestButton_3 = new QPushButton(track);
        TestButton_3->setObjectName("TestButton_3");
        TestButton_3->setGeometry(QRect(220, 320, 111, 41));
        InitialButton = new QPushButton(track);
        InitialButton->setObjectName("InitialButton");
        InitialButton->setGeometry(QRect(70, 110, 111, 31));
        lineEdit = new QLineEdit(track);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(460, 220, 113, 25));
        pushButton = new QPushButton(track);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(590, 220, 89, 25));
        label = new QLabel(track);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 220, 101, 21));

        retranslateUi(track);

        QMetaObject::connectSlotsByName(track);
    } // setupUi

    void retranslateUi(QWidget *track)
    {
        track->setWindowTitle(QCoreApplication::translate("track", "Form", nullptr));
        ImportButton->setText(QCoreApplication::translate("track", "Import Data", nullptr));
        ConnectButton->setText(QCoreApplication::translate("track", "Connect Robot", nullptr));
        SendButton->setText(QCoreApplication::translate("track", "Send Message", nullptr));
        DisconnectButton->setText(QCoreApplication::translate("track", "Disconnect", nullptr));
        StopButton->setText(QCoreApplication::translate("track", "StopRobot", nullptr));
        RunButton_2->setText(QCoreApplication::translate("track", "RunButton", nullptr));
        TestButton_3->setText(QCoreApplication::translate("track", "TestButton", nullptr));
        InitialButton->setText(QCoreApplication::translate("track", "InitialButton", nullptr));
        pushButton->setText(QCoreApplication::translate("track", "\347\241\256\350\256\244", nullptr));
        label->setText(QCoreApplication::translate("track", "\350\277\220\350\241\214\346\227\266\351\227\264\351\227\264\351\232\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class track: public Ui_track {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACK_H
