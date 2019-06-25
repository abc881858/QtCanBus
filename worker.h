#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "subscriber.h"
#include <QtSerialBus>
#include <QDebug>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(QObject *parent = nullptr);
    Subscriber *sub;
    void init(int argc, char *argv[]);

    QCanBusDevice *m_canDevice;

public slots:
    void vehicle_control(const QString &s);
    void vehicle_info(const QString &s);

};

#endif // WORKER_H
