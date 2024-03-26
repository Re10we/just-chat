#include "JsonConcept.h"

JsonMess::JsonMess() {}

JsonMess::~JsonMess() = default;

QByteArray JsonMess::ToSerialize(QString FuncName, QList<QVariant> ArgV) {
  QJsonObject JsonObject;
  QJsonArray JsonArr;

  JsonObject.insert("name", FuncName);

  for (auto Value : ArgV) {
    JsonArr.push_back(Value.toJsonValue());
  }
  JsonObject.insert("argv", JsonArr);

  return (new QJsonDocument(JsonObject))->toJson();
}

QJsonObject JsonMess::FromSerialize(QByteArray SerializeValue) {
  return QJsonDocument::fromJson(SerializeValue).object();
}
