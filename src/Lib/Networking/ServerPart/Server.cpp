#include "Server.h"
#include "src/Lib/Networking/ServerPart/ClientConnection.h"

Server::Server(QObject *Parent) : QObject(Parent) {
  TcpServer = new QTcpServer();

  connect(TcpServer, &QTcpServer::newConnection, this, &Server::NewConnection);
}

Server::~Server() { qDebug() << "Server stop!"; }

bool Server::StartServer() const {
  return TcpServer->listen(QHostAddress::Any, 8080);
}

void Server::NewConnection() {

  QTcpSocket *socket = TcpServer->nextPendingConnection();
  if (!socket) {
    qDebug() << "Socket undefined";
    return;
  }

  auto Client = new ClientConnection(socket);

  ClientConnections.insert(ValueMapType(Client, nullptr));

  connect(Client, &ClientConnection::__SearchPartner,
          [this]() { qDebug() << "I`m lambda"; });
}
