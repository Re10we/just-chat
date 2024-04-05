#include "Client.h"

Client::Client(QObject *Parent, QHostAddress HostAddress, quint16 Port)
    : QObject(Parent) {

  this->Socket = new QTcpSocket();
  
  this->Socket->connectToHost(HostAddress, Port);

  const short StartWithoutInheritedFunc = 5;

  for (int i = StartWithoutInheritedFunc;
       i < this->staticMetaObject.methodCount(); i++) {
    this->FnMap.insert(this->staticMetaObject.method(i).name(),
                       this->staticMetaObject.method(i));
  }

  connect(this->Socket, &QAbstractSocket::disconnected, this,
          &QObject::deleteLater);
  connect(this->Socket, &QIODevice::readyRead, this, &Client::ReadyRead);
}

Client::~Client() = default;

void Client::SendToServer(QString NameFunc, QList<QVariant> ListArguments) {
  this->Socket->write(JsonMess::ToSerialize(NameFunc, ListArguments));
}

void Client::SetName(QString NewNameClient) {
  this->SendToServer(__func__, QList<QVariant>({NewNameClient}));
}

void Client::SearchPartner() {
  this->SendToServer(__func__, QList<QVariant>());
}

void Client::SubmitMess(QString Mess) {
  this->SendToServer(__func__, QList<QVariant>({Mess}));
}

void Client::ReadyRead() {
  QByteArray MessFromServer = Socket->readAll();
  QJsonObject jsonObject = JsonMess::FromSerialize(MessFromServer);
  qDebug() << MessFromServer;
  QMetaMethod InvokeFn = FnMap[jsonObject["name"].toVariant().toString()];
  InvokeFn.invoke(this, Qt::DirectConnection,
                  jsonObject["argv"].toVariant().toList());
  qDebug() << "Client is readyRead!";
}

void Client::SuccessfullyFoundPartner(QList<QVariant> ArgV) {
  if (ArgV.size() == 1) {
    __SuccessfullyFoundPartner(ArgV[0].toBool());
  } else {
    // TODO error
  }
}

void Client::__SuccessfullyFoundPartner(bool isFound) {
  emit isFoundPatner();
}