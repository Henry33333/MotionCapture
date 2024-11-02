#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QVariant>
#include <cmath>



#include "StructDef.h"
#include "x1motlibface.h"

#include "EstunRemoteApiLib/EstunRemoteApiLib.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);
    void setRob(EstunRemoteApiLib *a);
    void setRes(std::vector<std::vector<QVariant>> r);


signals:
    void resultReady();

public slots:
    void on_doSomething();

private:

    EstunRemoteApiLib *api;
    std::vector<std::vector<QVariant>> res;
};



#endif // WORKER_H
