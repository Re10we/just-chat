#include "Server.h"
#include "src/Lib/JSON/JsonConcept.h"
#include "src/Lib/Networking/ServerPart/ClientConnection.h"

Server::Server(QObject *Parent) : QObject(Parent) {
  TcpServer = new QTcpServer();
  ClientReadyToConnect = nullptr;

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

  auto Client = new ClientConnection(socket, this);

  ClientConnections.insert(ValueMapType(Client, nullptr));

  connect(Client, &ClientConnection::__SearchPartner, [Client, this]() {
    if (this->ClientReadyToConnect != nullptr) {
      auto ClientConnectionObject =
          ClientConnections.left.find(this->ClientReadyToConnect);

      Client->SetSocketChatPartner(this->ClientReadyToConnect->GetSocket());
      this->ClientReadyToConnect->SetSocketChatPartner(Client->GetSocket());

      auto SuccessfullyFoundPartner = [](QTcpSocket *Socket) {
        Socket->write(JsonMess::ToSerialize("SuccessfullyFoundPartner",
                                            QList<QVariant>(true)));
      };

      SuccessfullyFoundPartner(Client->GetSocket());
      SuccessfullyFoundPartner(Client->GetSocketChatPartner());

      this->ClientReadyToConnect = nullptr;
    } else {
      this->ClientReadyToConnect = Client;
    }
  });
}
