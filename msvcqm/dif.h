#ifndef DIF_H
#define DIF_H

#include <QWidget>
#include <QtCharts>
#include <QDebug>
#include <QLegend>

namespace Ui {
class dif;
}

class dif : public QWidget
{
    Q_OBJECT

public:
    explicit dif(QWidget *parent = nullptr);
    ~dif();
    QChart* chart;
    QChart* chart2;
    QChart* chart3;
//    QLineSeries *series;
    qint32 counter;
    void showdata(std::vector<std::vector<QVariant>> data,std::vector<std::vector<QVariant>> data2);

private:
    Ui::dif *ui;
};

#endif // DIF_H
