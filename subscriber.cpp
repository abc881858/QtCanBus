#include "subscriber.h"
#include "ros/ros.h"

void Subscriber::vehicle_command(const vehicle::VehicleCommand::ConstPtr &msg)
{
    if(msg->autonomy_mode.autonomy_level == 1)
    {
    qDebug() << "command:" << msg->header.stamp.toNSec() << msg->autonomy_mode.autonomy_level;
    QString result("command!!!");
    emit vehicle_control(result);
    }
}

void Subscriber::vehicle_report(const vehicle::VehicleReport::ConstPtr &msg)
{
    if(msg->autonomy_mode.autonomy_level == 1)
    {
    qDebug() << "report:" << msg->header.stamp.toNSec() << msg->autonomy_mode.autonomy_level;
    QString result("report!!!");
    emit vehicle_info(result);
    }
}

Subscriber::Subscriber(QObject *parent) : QThread(parent)
{
}

void Subscriber::run()
{
    ros::NodeHandle n1;
    ros::Subscriber sub1 = n1.subscribe("vehicle_control", 1000, &Subscriber::vehicle_command, this);

    ros::NodeHandle n2;
    ros::Subscriber sub2 = n2.subscribe("vehicle_info", 1000, &Subscriber::vehicle_report, this);

    ros::spin();
}
