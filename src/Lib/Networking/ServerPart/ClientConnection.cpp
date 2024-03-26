#include "ClientConnection.h"

ClientConnection::ClientConnection(QTcpSocket *Socket, QObject *Parent)
    : QObject(Parent) {
  this->Socket = std::unique_ptr<QTcpSocket>(Socket);

  const short StartWithoutInheritedFunc = 5;

  for (int i = StartWithoutInheritedFunc;
       i < this->staticMetaObject.methodCount(); i++) {
    this->FnMap.insert(this->staticMetaObject.method(i).name(),
                       this->staticMetaObject.method(i));
  }

  connect(this->Socket.get(), &QAbstractSocket::disconnected, this,
          &QObject::deleteLater);
  connect(this->Socket.get(), &QIODevice::readyRead, this,
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

void ClientConnection::SetName(QList<QVariant> Argv) {
  if (Argv.size() == 1) {
    __SetName(Argv[0].toString());
  } else {
    // TODO Error
  }
}
void ClientConnection::__SetName(QString NewName) {
  // TODO Seting name for user
  qDebug() << "Name user is: " << NewName;
}
