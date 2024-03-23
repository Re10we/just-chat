#include "Client.h"

Client::Client(QObject *Parent, QHostAddress HostAddress, quint16 Port)
    : QObject(Parent) {

  this->Socket = std::make_unique<QTcpSocket>();

  this->Socket->connectToHost(HostAddress, Port);
}

Client::~Client() = default;

void Client::SubmitMess(QString Mess) {
  this->Socket->write(Mess.toUtf8());
}
