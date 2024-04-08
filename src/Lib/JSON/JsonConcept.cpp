#include "JsonConcept.h"

QByteArray JsonMess::ToJson(QString FuncName, QList<QVariant> ArgV) {
  QJsonObject JsonObject;
  QJsonArray JsonArr;

  JsonObject.insert("name", FuncName);

  for (auto Value : ArgV) {
    JsonArr.push_back(Value.toJsonValue());
  }
  JsonObject.insert("argv", JsonArr);

  return (new QJsonDocument(JsonObject))->toJson();
}

QJsonObject JsonMess::FromJson(QByteArray SerializeValue) {
  return QJsonDocument::fromJson(SerializeValue).object();
}
