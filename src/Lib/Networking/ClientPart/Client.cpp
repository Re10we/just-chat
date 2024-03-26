#include "Client.h"

Client::Client(QObject *Parent, QHostAddress HostAddress, quint16 Port)
    : QObject(Parent) {

  this->Socket = std::make_unique<QTcpSocket>();

  this->Socket->connectToHost(HostAddress, Port);
}

Client::~Client() = default;

void Client::SendToServer(QString NameFunc, QList<QVariant> ListArguments) {
  this->Socket->write(JsonMess::ToSerialize(NameFunc, ListArguments));
}

void Client::SetName(QString NewNameClient) {
  this->SendToServer(__func__, QList<QVariant>({NewNameClient}));
}