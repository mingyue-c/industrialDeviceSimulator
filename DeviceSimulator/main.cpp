#include <QCoreApplication>
#include <QDebug>
#include "SimulatorServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    SimulatorServer server;

    if (!server.start(9000)) {
        qCritical() << "Device simulator start failed.";
        return -1;
    }

    qInfo() << "Device simulator started on port 9000.";

    return app.exec();
}