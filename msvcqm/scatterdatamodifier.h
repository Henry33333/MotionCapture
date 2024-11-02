
#ifndef SCATTERDATAMODIFIER_H
#define SCATTERDATAMODIFIER_H
#include <QtDataVisualization>
#include <QSurface>
#include <QBoxLayout>
#include <QVector3D>
#include <QComboBox>
#include <QCheckBox>
#include <QFontComboBox>
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dseries.h>
#include <QtGui/QFont>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>

class ScatterDataModifier : public QObject
{
    Q_OBJECT
public:
    ScatterDataModifier(Q3DScatter *scatter, std::vector<std::vector<QVariant>> data, QWidget *parent = nullptr);
    ~ScatterDataModifier();
    void addData(std::vector<std::vector<QVariant>> data);

    void changeData();
    void changePresetCamera();
    void changeLabelStyle();
    void changeFont(const QFont &font);
    void changeFontSize(int fontsize);
    void setBackgroundEnabled(int enabled);
    void setGridEnabled(int enabled);
    void setSmoothDots(int smooth);
    void toggleItemCount();
    void on3Dseries_selected(int index);
    void on3Dscatter_selected(QScatter3DSeries *series);



public Q_SLOTS:
    void changeStyle(int style);
    void changeTheme(int theme);
    void changeShadowQuality(int quality);
    void shadowQualityUpdatedByVisual(QAbstract3DGraph::ShadowQuality shadowQuality);

Q_SIGNALS:
    void backgroundEnabledChanged(bool enabled);
    void gridEnabledChanged(bool enabled);
    void shadowQualityChanged(int quality);
    void fontChanged(QFont font);
    void sendData(std::vector<int>);

private:

    Q3DScatter *m_graph;
    QScatter3DSeries *series;
    int m_fontSize;
    QAbstract3DSeries::Mesh m_style;
    bool m_smooth;
    int m_itemCount;
    int m_indexRecord1;
    int m_indexRecord2;
    int flag;
    float m_curveDivider;
    std::vector<std::vector<QVariant>> data_2;
//    QScatter3DSeries *m_selectedSeries;
    QWidget *parentWidget;
};

#endif // SCATTERDATAMODIFIER_H
