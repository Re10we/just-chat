#include "Server.h"

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

  const QTcpSocket *socket = TcpServer->nextPendingConnection();
  if (!socket) {
    return;
  }

  // TODO create instance if Client
}