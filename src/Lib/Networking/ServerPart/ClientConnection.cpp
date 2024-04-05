#include "ClientConnection.h"

ClientConnection::ClientConnection(QTcpSocket *Socket, QObject *Parent)
    : QObject(Parent) {
  this->Socket = Socket;

  const short StartWithoutInheritedFunc = 5;

  for (int i = StartWithoutInheritedFunc;
       i < this->staticMetaObject.methodCount(); i++) {
    this->FnMap.insert(this->staticMetaObject.method(i).name(),
                       this->staticMetaObject.method(i));
  }

  connect(this->Socket, &QAbstractSocket::disconnected, this,
          &QObject::deleteLater);
  connect(this->Socket, &QIODevice::readyRead, this,
          &ClientConnection::readyRead);
}

ClientConnection::~ClientConnection() = default;

void ClientConnection::readyRead() {
  qDebug() << "ClientConnection is readyRead!";

  QByteArray MessFromClient = Socket->readAll();
  QJsonObject jsonObject = JsonMess::FromSerialize(MessFromClient);

  QMetaMethod InvokeFn = FnMap[jsonObject["name"].toVariant().toString()];
  InvokeFn.invoke(this, Qt::DirectConnection,
                  jsonObject["argv"].toVariant().toList());
}

void ClientConnection::SearchPartner(QList<QVariant> ArgV) {
  if (ArgV.size() == 0) {
    emit __SearchPartner();
  } else {
    // TODO Error
  }
}

QTcpSocket* ClientConnection::GetSocket() {
  return this->Socket;
}

void ClientConnection::SetSocketChatPartner(QTcpSocket *SocketChatPartner) {
  this->SocketChatPartner = SocketChatPartner;
}

void ClientConnection::SetName(QList<QVariant> Argv) {
  if (Argv.size() == 1) {
    __SetName(Argv[0].toString());
  } else {
    // TODO Error
  }
}
void ClientConnection::__SetName(QString NewName) { NameUser = NewName; }

void ClientConnection::SubmitMess(QList<QVariant> Argv) {
  if (Argv.size() == 1) {
    __SubmitMess(Argv[0].toString());
  } else {
    // TODO Error
  }
}
void ClientConnection::__SubmitMess(QString Mess) {
  this->SocketChatPartner->write("hello World");
}

