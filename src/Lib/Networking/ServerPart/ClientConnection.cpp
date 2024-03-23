#include "ClientConnection.h"
#include <QDebug>

ClientConnection::ClientConnection(QTcpSocket *Socket, QObject *Parent)
    : QObject(Parent) {
  this->Socket = std::unique_ptr<QTcpSocket>(Socket);

  connect(this->Socket.get(), &QAbstractSocket::disconnected, this,
          &QObject::deleteLater);
  connect(this->Socket.get(), &QIODevice::readyRead, this,
          &ClientConnection::readyRead);
}

void ClientConnection::readyRead() {
  qDebug() << "ClientConnection is readyRead!";
  qDebug() << Socket->readLine();
}

ClientConnection::~ClientConnection() = default;
