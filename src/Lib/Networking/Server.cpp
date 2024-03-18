#include "Server.h"
#include "Client.h"

Server::Server(QObject *Parent) : QObject(Parent) {
  TcpServer = std::make_unique<QTcpServer>();

  connect(TcpServer.get(), SIGNAL(&QTcpServer::newConnection), this,
          SLOT(&Server::newConnection));
}

Server::~Server() = default;

bool Server::StartServer() const {
  return TcpServer->listen(QHostAddress::Any, 8080);
}

void Server::newConnection() {

  QTcpSocket *socket = TcpServer->nextPendingConnection();
  if (!socket) {
    return;
  }

  new Client(socket);
}