#include "Client.h"
#include <QDebug>

Client::Client(QTcpSocket *Socket, QObject *Parent) : QObject(Parent) {
  this->Socket = std::make_unique<QTcpSocket>(Socket);

  connect(this->Socket.get(), SIGNAL(QAbstractSocket::disconnected), this,
          SLOT(QObject::deleteLater));
  connect(this->Socket.get(), SIGNAL(QIDevice::readyRead), this,
          SLOT(Client::readyRead));
}

Client::~Client() = default;

void Client::readyRead() {
  while (this->Socket->canReadLine()) {
    qDebug() << this->Socket->readLine();
  }
}