#include "scatterdatamodifier.h"
#include <QObject>

//using namespace QtDataVisualization;

const int numberOfItems = 3600;
const float curveDivider = 3.0f;
const int lowerNumberOfItems = 900;
const float lowerCurveDivider = 0.75f;

ScatterDataModifier::ScatterDataModifier(Q3DScatter *scatter, std::vector<std::vector<QVariant>> data, QWidget *parent)
    : QObject(parent)
    , m_graph(scatter)
    , m_fontSize(4.0f)
    , m_style(QAbstract3DSeries::MeshSphere)
    , m_smooth(true)
    , m_itemCount(lowerNumberOfItems)
    , m_indexRecord1(0)
    , m_indexRecord2(0)
    , m_curveDivider(lowerCurveDivider)
    , parentWidget(parent)
{
    flag = 0;
//    m_selectedSeries = nullptr;
    m_graph->activeTheme()->setType(Q3DTheme::ThemeEbony);
    QFont font = m_graph->activeTheme()->font();
    font.setPointSize(m_fontSize);
    m_graph->activeTheme()->setFont(font);
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    QScatterDataProxy *proxy = new QScatterDataProxy;
    series = new QScatter3DSeries(proxy);
    series->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series->setMeshSmooth(m_smooth);
    series->setItemSize(0.08f);
    m_graph->addSeries(series);
    data_2 = data;
    addData(data_2);
//    connect(m_graph, &Q3DScatter::selectedSeriesChanged, this, &ScatterDataModifier::on3Dscatter_selected);
    connect(series, &QScatter3DSeries::selectedItemChanged, this, &ScatterDataModifier::on3Dseries_selected);
    changeTheme(1);
    changeShadowQuality(3);
    changeStyle(3);
}

ScatterDataModifier::~ScatterDataModifier()
{

}

void ScatterDataModifier::addData(std::vector<std::vector<QVariant>> data)
{
    m_graph->axisX()->setTitle("X");
    m_graph->axisY()->setTitle("Y");
    m_graph->axisZ()->setTitle("Z");
    int n = data.size();

    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(n);
    QScatterDataItem *ptrToDataArray = &dataArray->first();
    for (int i = 0; i < n; ++i) {
        ptrToDataArray->setPosition(QVector3D(data[i][0].toFloat(),data[i][1].toFloat(),data[i][2].toFloat()));
        ptrToDataArray++;
    }
//    for(int i = 0; i < n; ++i) {
//        for(int j = 0; j < n; ++j) {
//            qDebug().noquote()<<data[i][0].toFloat(),data[i][1].toFloat(),data[i][2].toFloat(),"\n";
//        }
//    }
    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
}

void ScatterDataModifier::changeStyle(int style)
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(sender());
    if (comboBox) {
        m_style = QAbstract3DSeries::Mesh(comboBox->itemData(style).toInt());
        if (m_graph->seriesList().size())
            m_graph->seriesList().at(0)->setMesh(m_style);
    }
}

void ScatterDataModifier::setSmoothDots(int smooth)
{
    m_smooth = bool(smooth);
    QScatter3DSeries *series = m_graph->seriesList().at(0);
    series->setMeshSmooth(m_smooth);
}

void ScatterDataModifier::changeTheme(int theme)
{
    Q3DTheme *currentTheme = m_graph->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(theme));
    emit backgroundEnabledChanged(currentTheme->isBackgroundEnabled());
    emit gridEnabledChanged(currentTheme->isGridEnabled());
    emit fontChanged(currentTheme->font());
}

void ScatterDataModifier::changePresetCamera()
{
    static int preset = Q3DCamera::CameraPresetFrontLow;

    m_graph->scene()->activeCamera()->setCameraPreset((Q3DCamera::CameraPreset)preset);

    if (++preset > Q3DCamera::CameraPresetDirectlyBelow)
        preset = Q3DCamera::CameraPresetFrontLow;
}

void ScatterDataModifier::changeLabelStyle()
{
    m_graph->activeTheme()->setLabelBackgroundEnabled(!m_graph->activeTheme()->isLabelBackgroundEnabled());
}

void ScatterDataModifier::changeFont(const QFont &font)
{
    QFont newFont = font;
    newFont.setPointSizeF(m_fontSize);
    m_graph->activeTheme()->setFont(newFont);
}

void ScatterDataModifier::shadowQualityUpdatedByVisual(QAbstract3DGraph::ShadowQuality sq)
{
    int quality = int(sq);
    emit shadowQualityChanged(quality); // connected to a checkbox in main.cpp
}

void ScatterDataModifier::changeShadowQuality(int quality)
{
    QAbstract3DGraph::ShadowQuality sq = QAbstract3DGraph::ShadowQuality(quality);
    m_graph->setShadowQuality(sq);
}

void ScatterDataModifier::setBackgroundEnabled(int enabled)
{
    m_graph->activeTheme()->setBackgroundEnabled((bool)enabled);
}

void ScatterDataModifier::setGridEnabled(int enabled)
{
    m_graph->activeTheme()->setGridEnabled((bool)enabled);
}

void ScatterDataModifier::toggleItemCount()
{
    if (m_itemCount == numberOfItems) {
        m_itemCount = lowerNumberOfItems;
        m_curveDivider = lowerCurveDivider;
    } else {
        m_itemCount = numberOfItems;
        m_curveDivider = curveDivider;
    }
    m_graph->seriesList().at(0)->dataProxy()->resetArray(0);
}

//void ScatterDataModifier::on3Dscatter_selected(QScatter3DSeries *series_2)
//{
//    if (series_2 == nullptr) {
//        return;
//    }
//    m_selectedSeries = series_2;
//}

void ScatterDataModifier::changeData()
{
//    int a;
//    int b;
//    if(m_indexRecord1>m_indexRecord2){
//        a = m_indexRecord2;
//        b = m_indexRecord1;
//    }
//    else{
//        b = m_indexRecord2;
//        a = m_indexRecord1;
//    }
//    std::vector<std::vector<QVariant>> data_3;

//    for (int row = a; row < b+1; row++)
//    {
//        std::vector<QVariant> data_tmp;
//        for (int col = 0; col < 2; col++)
//        {
//            data_tmp.push_back(data_2[row][col]);
//        }
//        data_3.push_back(data_tmp);
//    }
//    qDebug()<<"到这里了4";
//    int n = data_3.size();
//    QScatterDataArray *dataArray2 = new QScatterDataArray;
//    dataArray2->resize(n);
//    QScatterDataItem *ptrToDataArray2 = &dataArray2->first();
//    qDebug()<<n;
//    for (int i = 0; i < n; ++i) {
//        ptrToDataArray2->setPosition(QVector3D(data_3[i][0].toFloat(),data_3[i][1].toFloat(),data_3[i][2].toFloat()));
//        ptrToDataArray2++;
//        qDebug()<<"到这里了5";
//    }
//    qDebug()<<"到这里了6";
//    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray2);
//    qDebug()<<"到这里了7";
    std::vector<int> startAndgoal(2);
    startAndgoal.push_back(0);
    startAndgoal.push_back(0);

    if(m_indexRecord1 > m_indexRecord2){
        startAndgoal[0] = m_indexRecord2;
        startAndgoal[1] = m_indexRecord1;
    }
    else if(m_indexRecord1 < m_indexRecord2){
        startAndgoal[1] = m_indexRecord2;
        startAndgoal[0] = m_indexRecord1;
    }
    else{
        QMessageBox::warning(parentWidget, "截断轨迹", "请选择截断轨迹的起点和终点！");
        return;
    }
    parentWidget->close();
    emit sendData(startAndgoal);
}

void ScatterDataModifier::on3Dseries_selected(int index)
{
//    if (m_selectedSeries == nullptr) {
//        return;
//    }
    if(flag==0){
        m_indexRecord1 = index;
        flag = 1 - flag;
    }
    else{
        m_indexRecord2 = index;
        flag = 1 - flag;
    }
    qDebug()<<index;
}

