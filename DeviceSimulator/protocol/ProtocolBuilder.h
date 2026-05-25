#pragma once

#include <QByteArray>
#include <QJsonObject>

class ProtocolBuilder
{
public:
    static QByteArray buildMessage(const QJsonObject& data);
};