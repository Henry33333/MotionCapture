#ifndef TRACK_H
#define TRACK_H

#include <QWidget>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <QAxObject>

#define IP_ADDRESS "192.168.1.10"
#define PORT 10000

// Maximum allowed waiting time during actions
constexpr auto TIMEOUT_DURATION = std::chrono::seconds(20);

QT_BEGIN_NAMESPACE
namespace Ui { class track; }
QT_END_NAMESPACE

class track : public QWidget
{
    Q_OBJECT

public:
    explicit track(QWidget *parent = nullptr);
    ~track();
    void readXlsx(QString &FilePath);            //read .xlsx

    void angular_Waypointlist();

private slots:
//    void on_ConnectButton_clicked();

//    void on_SendButton_clicked();

//    void on_DisconnectButton_clicked();

//    void on_TestButton_3_clicked();

//    void on_RunButton_2_clicked();

    void on_ImportButton_clicked();

//    void on_StopButton_clicked();

//    void on_InitialButton_clicked();

//    void on_pushButton_clicked();

private:
    Ui::track *ui;
//    robot *new_robot;
    std::vector<std::vector<float>> data;
    std::vector<float> Initial_Data;
    int row;
    int col;
    int robot_deg;
    float intervalTime;
};

#endif // TRACK_H
