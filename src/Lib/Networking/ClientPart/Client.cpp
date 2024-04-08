#include "Client.h"

Client::Client(QObject *Parent, QHostAddress HostAddress, quint16 Port) : QObject(Parent) {

  this->Socket = new QTcpSocket();

  this->Socket->connectToHost(HostAddress, Port);

  const int StartWithoutInheritedFunc = 5;

  for (int i = StartWithoutInheritedFunc; i < this->staticMetaObject.methodCount(); i++) {
    this->FnMap.insert(this->staticMetaObject.method(i).name(), this->staticMetaObject.method(i));
  }

  connect(this->Socket, &QAbstractSocket::disconnected, this, &QObject::deleteLater);
  connect(this->Socket, &QIODevice::readyRead, this, &Client::ReadyRead);
}

Client::~Client() = default;

void Client::ReadyRead() {
  QByteArray MessFromServer = Socket->readAll();
  QJsonObject JsonObject = JsonMess::FromJson(MessFromServer);

  QMetaMethod InvokeFn = FnMap[JsonObject["name"].toVariant().toString()];
  InvokeFn.invoke(this, Qt::DirectConnection, JsonObject["argv"].toVariant().toList());
}

void Client::SendToServer(QString NameFunc, QList<QVariant> ListArguments) {
  this->Socket->write(JsonMess::ToJson(NameFunc, ListArguments));
}

void Client::SetName(QString NewNameClient) {
  this->ClientName = NewNameClient;

  this->SendToServer(__func__, QList<QVariant>({NewNameClient}));
}

QString Client::GetName() const { return ClientName; }

void Client::SearchPartner() { this->SendToServer(__func__, QList<QVariant>()); }

void Client::SubmitMess(QString Mess) { this->SendToServer(__func__, QList<QVariant>({Mess})); }

void Client::SuccessfullyFoundPartner(QList<QVariant> ArgV) {
  if (ArgV.size() == 0) {
    __SuccessfullyFoundPartner();
  } else {
    // TODO error
  }
}

void Client::__SuccessfullyFoundPartner() { emit isFoundPatner(); }

void Client::SubmitMessFromClient(QList<QVariant> ArgV) {
  if (ArgV.size() == 1) {
    __SubmitMessFromClient(ArgV[0].toString());
  } else {
    // TODO Error
  }
}

void Client::__SubmitMessFromClient(QString Mess) { emit MessFromClient(Mess); }

void Client::StartExitFromChat() { ExitFromChat(QList<QVariant>({QVariant(true)})); }

void Client::ExitFromChat(QList<QVariant> ArgV) {
  if (ArgV.size() == 1) {
    this->SendToServer(__func__, ArgV);

    __ExitFromChat(ArgV[0].toBool());
  } else {
    // TODO Error
  }
}

void Client::__ExitFromChat(bool isIniciator) { emit SignalStartExitFromChat(); }
