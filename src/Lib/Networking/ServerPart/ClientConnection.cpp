#include "ClientConnection.h"

ClientConnection::ClientConnection(QTcpSocket *Socket, QObject *Parent) : QObject(Parent) {
  this->Socket = Socket;

  const short StartWithoutInheritedFunc = 5;

  for (int i = StartWithoutInheritedFunc; i < this->staticMetaObject.methodCount(); i++) {
    this->FnMap.insert(this->staticMetaObject.method(i).name(), this->staticMetaObject.method(i));
  }

  connect(this->Socket, &QAbstractSocket::disconnected, this, &QObject::deleteLater);
  connect(this->Socket, &QIODevice::readyRead, this, &ClientConnection::readyRead);
}

ClientConnection::~ClientConnection() = default;

void ClientConnection::readyRead() {
  QByteArray MessFromClient = Socket->readAll();
  QJsonObject jsonObject = JsonMess::FromSerialize(MessFromClient);

  QMetaMethod InvokeFn = FnMap[jsonObject["name"].toVariant().toString()];
  InvokeFn.invoke(this, Qt::DirectConnection, jsonObject["argv"].toVariant().toList());
}

QTcpSocket *ClientConnection::GetSocket() { return this->Socket; }

QString ClientConnection::GetName() const { return this->ClientName; }

void ClientConnection::SetSocketChatPartner(QTcpSocket *SocketChatPartner) {
  if (SocketChatPartner != nullptr) {
    this->HistoryOfConections.insert(SocketChatPartner);
  }
  this->SocketChatPartner = SocketChatPartner;
}

QTcpSocket *ClientConnection::GetSocketChatPartner() const { return this->SocketChatPartner; }

bool ClientConnection::CheckConnectionWithPartner(QTcpSocket *CheckedSocket) const {
  return HistoryOfConections.contains(CheckedSocket);
}

void ClientConnection::SendToClient(QString NameFunc, QList<QVariant> ArgV) {
  if (this->SocketChatPartner && this->SocketChatPartner->isValid()) {
    this->SocketChatPartner->write(JsonMess::ToSerialize(NameFunc, ArgV));
  } else {
    // TODO Error
  }
}

void ClientConnection::SearchPartner(QList<QVariant> ArgV) {
  if (ArgV.size() == 0) {
    emit __SearchPartner();
  } else {
    // TODO Error
  }
}

void ClientConnection::SetName(QList<QVariant> Argv) {
  if (Argv.size() == 1) {
    __SetName(Argv[0].toString());
  } else {
    // TODO Error
  }
}
void ClientConnection::__SetName(QString NewName) { ClientName = NewName; }

void ClientConnection::SubmitMess(QList<QVariant> ArgV) {
  if (ArgV.size() == 1) {
    SubmitMessFromClient(ArgV[0].toString());
  } else {
    // TODO Error
  }
}

void ClientConnection::SubmitMessFromClient(QString Mess) {
  this->SendToClient(__func__, QList<QVariant>({QString(ClientName + ": " + Mess)}));
}

void ClientConnection::ExitFromChat(QList<QVariant> ArgV) {
  if (ArgV.size() == 1) {
    if (ArgV[0].toBool() == true) {
      this->SendToClient(__func__, QList<QVariant>({QVariant(false)}));
    }
    __ExitFromChat(ArgV[0].toBool());
  } else {
    // TODO Error
  }
}

void ClientConnection::__ExitFromChat(bool isIniciator) { this->SetSocketChatPartner(nullptr); }
