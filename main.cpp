#include <QCoreApplication>
#include <QLoggingCategory>
#include "worker.h"

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules(QStringLiteral("qt.canbus* = true"));
    QCoreApplication a(argc, argv);

    Worker *worker = new Worker();
    worker->init(argc, argv);

    return a.exec();
}
