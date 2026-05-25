#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QList>

#include "SimulatedDevice.h"

class SimulatorServer : public QObject
{
    Q_OBJECT

public:
    explicit SimulatorServer(QObject* parent = nullptr);
    bool start(quint16 port);

private slots:
    void onNewConnection();
    void sendData();

private:
    QTcpServer* m_server;
    QList<QTcpSocket*> m_clients;
    QList<SimulatedDevice*> m_devices;
    QTimer* m_timer;
};