#include "ProtocolBuilder.h"

#include <QJsonDocument>

QByteArray ProtocolBuilder::buildMessage(const QJsonObject& data)
{
    return QJsonDocument(data).toJson(QJsonDocument::Compact) + "\n";
}