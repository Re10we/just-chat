#ifndef JSONCONCEPT_H
#define JSONCONCEPT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QObject>
#include <QList>

class JsonMess : public QObject {
  Q_OBJECT

public:
  JsonMess();
  ~JsonMess();
  
  QByteArray static ToSerialize(QString FuncName, QList<QVariant> ArgV);
  QJsonObject static FromSerialize(QByteArray SerializeValue);
};

#endif // JSONCONCEPT_H