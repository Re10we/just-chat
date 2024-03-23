#include "Server.h"
#include <QDebug>

Server::Server(QObject *Parent) : QObject(Parent) {
  TcpServer = std::make_unique<QTcpServer>();

  connect(TcpServer.get(), &QTcpServer::newConnection, this,
          &Server::newConnection);
}

Server::~Server() { qDebug() << "Server stop!"; }

bool Server::StartServer() const {
  return TcpServer->listen(QHostAddress::Any, 8080);
}

void Server::newConnection() {

  QTcpSocket *socket = TcpServer->nextPendingConnection();
  if (!socket) {
    qDebug() << "Socket undefined";
    return;
  }

  qDebug() << "Socket creating...";
  new ClientConnection(socket);
}