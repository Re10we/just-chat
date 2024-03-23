#include "ClientConnection.h"
#include <QDebug>

ClientConnection::ClientConnection(QTcpSocket *Socket, QObject *Parent)
    : QObject(Parent) {
  this->Socket = std::make_unique<QTcpSocket>(Socket);

  connect(this->Socket.get(), &QAbstractSocket::disconnected, this,
          &QObject::deleteLater);
  connect(this->Socket.get(), &QIODevice::readyRead, this,
          &ClientConnection::readyRead);
}

void ClientConnection::readyRead() {
  qDebug() << "Client!";
  while (Socket->canReadLine()) {
    qDebug() << Socket->readLine();
  }
}

ClientConnection::~ClientConnection() = default;
