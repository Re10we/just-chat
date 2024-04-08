#ifndef JSONCONCEPT_H
#define JSONCONCEPT_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QObject>

namespace JsonMess {
QByteArray ToJson(QString FuncName, QList<QVariant> ArgV);
QJsonObject FromJson(QByteArray SerializeValue);
} // namespace JsonMess

#endif // JSONCONCEPT_H