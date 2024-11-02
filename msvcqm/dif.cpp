#include "dif.h"
#include "ui_dif.h"

dif::dif(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dif)
{
    ui->setupUi(this);

}

dif::~dif()
{
    delete ui;
    delete chart;
    delete chart2;
    delete chart3;
}

void dif::showdata(std::vector<std::vector<QVariant>> data,std::vector<std::vector<QVariant>> data2)
{

    chart = new QChart();
    QLineSeries *series = new QLineSeries();
    int n = data[0].size();
    int n2 = data2[0].size();
    for ( counter = 0; counter < n; ++counter) {
        series->append(data[0][counter].toInt(),data[1][counter].toInt());
    }
    series->setName("X-axis");
    chart->addSeries(series);

    QLineSeries *series2 = new QLineSeries();
    for ( counter = 0; counter < n2; ++counter) {
        series2->append(data2[0][counter].toInt(),data2[1][counter].toInt());
    }
    chart->addSeries(series2);
    ui->my_chart->setChart(chart);
    chart->createDefaultAxes();
    chart->setTitle("my chart");
    

    chart2 = new QChart();
    QLineSeries *series3 = new QLineSeries();
    for ( counter = 0; counter < n; ++counter) {
        series3->append(data[0][counter].toInt(),data[2][counter].toInt());
    }
    series3->setName("Y-axis");
    chart2->addSeries(series3);

    QLineSeries *series4 = new QLineSeries();
    for ( counter = 0; counter < n2; ++counter) {
        series4->append(data2[0][counter].toInt(),data2[2][counter].toInt());
    }
    chart2->addSeries(series4);
    ui->my_chart_2->setChart(chart2);
    chart2->createDefaultAxes();
    chart2->setTitle("my chart");

    chart3 = new QChart();
    QLineSeries *series5 = new QLineSeries();
    for ( counter = 0; counter < n; ++counter) {
        series5->append(data[0][counter].toInt(),data[3][counter].toInt());
    }
    series5->setName("Z-axis");
    chart3->addSeries(series5);

    QLineSeries *series6 = new QLineSeries();
    counter = 0;
    for ( counter = 0; counter < n2; ++counter) {
        series6->append(data[0][counter].toInt(),data2[3][counter].toInt());
    }
    chart3->addSeries(series6);
    ui->my_chart_3->setChart(chart3);
    chart3->createDefaultAxes();
    chart3->setTitle("my chart");
}

