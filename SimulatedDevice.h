#pragma once

#include <QString>
#include <QJsonObject>

class SimulatedDevice
{
public:
    explicit SimulatedDevice(const QString& deviceId);

    QJsonObject generateData();

private:
    QString m_deviceId;
    double m_temperature;
    double m_pressure;
    int m_speed;
};