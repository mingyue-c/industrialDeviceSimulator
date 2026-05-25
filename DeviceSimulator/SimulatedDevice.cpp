#include "SimulatedDevice.h"

#include <QDateTime>
#include <QRandomGenerator>

SimulatedDevice::SimulatedDevice(const QString& deviceId)
    : m_deviceId(deviceId),
      m_temperature(50.0),
      m_pressure(0.7),
      m_speed(3000)
{
}

QJsonObject SimulatedDevice::generateData()
{
    m_temperature += QRandomGenerator::global()->bounded(400) / 100.0 - 2.0;
    m_pressure += QRandomGenerator::global()->bounded(100) / 1000.0 - 0.05;
    m_speed += QRandomGenerator::global()->bounded(200) - 100;

    QString status = "RUNNING";

    if (m_temperature > 80.0) {
        status = "ALARM";
    }

    QJsonObject obj;
    obj["deviceId"] = m_deviceId;
    obj["temperature"] = m_temperature;
    obj["pressure"] = m_pressure;
    obj["speed"] = m_speed;
    obj["status"] = status;
    obj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    return obj;
}