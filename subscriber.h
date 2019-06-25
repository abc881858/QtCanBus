#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include <QThread>
#include "vehiclecommand.h"
#include "vehiclereport.h"
#include <QDebug>

class Subscriber : public QThread
{
    Q_OBJECT

public:
    Subscriber(QObject* parent = nullptr);
    void run() override;

    void vehicle_command(const vehicle::VehicleCommand::ConstPtr &msg);
    void vehicle_report(const vehicle::VehicleReport::ConstPtr &msg);

signals:
    void vehicle_control(const QString &s);
    void vehicle_info(const QString &s);

};

#endif // SUBSCRIBE_H
