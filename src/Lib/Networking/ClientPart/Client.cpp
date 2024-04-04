#include "Client.h"

Client::Client(QObject *Parent, QHostAddress HostAddress, quint16 Port)
    : QObject(Parent) {

  this->Socket = new QTcpSocket();

  this->Socket->connectToHost(HostAddress, Port);
}

Client::~Client() = default;

void Client::SendToServer(QString NameFunc, QList<QVariant> ListArguments) {

  auto temp = JsonMess::ToSerialize(NameFunc, ListArguments);

  qDebug() << "Ser: " << temp;
  this->Socket->write(JsonMess::ToSerialize(NameFunc, ListArguments));
}

void Client::SetName(QString NewNameClient) {
  this->SendToServer(__func__, QList<QVariant>({NewNameClient}));
}

void Client::SearchPartner() {
  this->SendToServer(__func__, QList<QVariant>());
}

void Client::SubmitMess(QString Mess) {
  this->SendToServer(__func__, QList<QVariant>({Mess}));
}