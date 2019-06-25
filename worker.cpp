#include "worker.h"
#include <QtSerialBus>
#include <QDebug>
#include "ros/ros.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    QStringList canPluginList = QCanBus::instance()->plugins();
    QString pluginName = canPluginList.last(); //"virtualcan"
    qDebug() << "canPlugins:";
    for (QString name : canPluginList)
    {
        qDebug() << name;
    }
    QList<QCanBusDeviceInfo> interfaces = QCanBus::instance()->availableDevices(pluginName);
    qDebug() << "interfaces:";
    for (QCanBusDeviceInfo info : interfaces)
    {
        qDebug() << "name" << info.name()
                 << "description" << info.description()
                 << "serialNumber" << info.serialNumber()
                 << "channel" << info.channel()
                 << "hasFlexibleDataRate" << info.hasFlexibleDataRate()
                 << "isVirtual" << info.isVirtual();
    }
    QString deviceInterfaceName = interfaces.first().name();

    QString errorString;
    m_canDevice = QCanBus::instance()->createDevice(pluginName, deviceInterfaceName, &errorString);
    if (!m_canDevice)
    {
        qDebug() << QString("Error creating device '%1', reason: '%2'").arg(pluginName).arg(errorString);
    }

    if (!m_canDevice->connectDevice())
    {
        qDebug() << QString("Connection error: %1").arg(m_canDevice->errorString());

        delete m_canDevice;
        m_canDevice = nullptr;
    }

//    const uint frameId = QString("123").toUInt(nullptr, 16);
//    QString data = QString("7f7f");
//    const QByteArray payload = QByteArray::fromHex(data.remove(QLatin1Char(' ')).toLatin1());
//    QCanBusFrame frame = QCanBusFrame(frameId, payload);
//    frame.setExtendedFrameFormat(false);
//    frame.setFlexibleDataRateFormat(false);
//    frame.setBitrateSwitch(false);
//    m_canDevice->writeFrame(frame);
}

void Worker::vehicle_control(const QString &s)
{
    qDebug() << s;
}

void Worker::vehicle_info(const QString &s)
{
    qDebug() << s;
}

void Worker::init(int argc, char *argv[])
{
    ros::init(argc, argv, "listener");

    sub = new Subscriber(this);
    connect(sub, &Subscriber::vehicle_control, this, &Worker::vehicle_control);
    connect(sub, &Subscriber::vehicle_info, this, &Worker::vehicle_info);
    sub->start();
}
