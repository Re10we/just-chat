#include "Client.h"
#include <QDebug>

Client::Client(QTcpSocket *Socket, QObject *Parent) : QObject(Parent) {
  this->Socket = std::make_unique<QTcpSocket>(Socket);

  connect(this->Socket.get(), &QAbstractSocket::disconnected, this,
          &QObject::deleteLater);
  connect(this->Socket.get(), &QIODevice::readyRead, this, &Client::readyRead);

  
}

void Client::readyRead() {
  qDebug() << "Client!";
  while (Socket->canReadLine()) {
    qDebug() << Socket->readLine();
  }
}

Client::~Client() = default;
