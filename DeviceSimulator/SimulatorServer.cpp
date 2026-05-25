#include "SimulatorServer.h"
#include "protocol/ProtocolBuilder.h"

#include <QHostAddress>
#include <QDebug>

SimulatorServer::SimulatorServer(QObject* parent)
    : QObject(parent),
      m_server(new QTcpServer(this)),
      m_timer(new QTimer(this))
{
    m_devices.append(new SimulatedDevice("DEV_001"));
    m_devices.append(new SimulatedDevice("DEV_002"));
    m_devices.append(new SimulatedDevice("DEV_003"));

    connect(m_server, &QTcpServer::newConnection,
            this, &SimulatorServer::onNewConnection);

    connect(m_timer, &QTimer::timeout,
            this, &SimulatorServer::sendData);
}

bool SimulatorServer::start(quint16 port)
{
    const bool ok = m_server->listen(QHostAddress::Any, port);

    if (ok) {
        m_timer->start(1000);
    }

    return ok;
}

void SimulatorServer::onNewConnection()
{
    while (m_server->hasPendingConnections()) {
        QTcpSocket* client = m_server->nextPendingConnection();
        m_clients.append(client);

        qInfo() << "Client connected:"
                << client->peerAddress().toString()
                << client->peerPort();

        connect(client, &QTcpSocket::disconnected, this, [this, client]() {
            qInfo() << "Client disconnected.";
            m_clients.removeAll(client);
            client->deleteLater();
        });
    }
}

void SimulatorServer::sendData()
{
    for (SimulatedDevice* device : m_devices) {
        const QByteArray message = ProtocolBuilder::buildMessage(device->generateData());

        for (QTcpSocket* client : m_clients) {
            if (client->state() == QAbstractSocket::ConnectedState) {
                client->write(message);
                client->flush();
            }
        }

        qInfo().noquote() << message.trimmed();
    }
}