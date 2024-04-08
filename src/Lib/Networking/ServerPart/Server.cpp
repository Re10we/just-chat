#include "Server.h"

Server::Server(QObject *Parent) : QObject(Parent) {
  this->TcpServer = new QTcpServer();
  this->ClientReadyToConnect = nullptr;

  connect(this->TcpServer, &QTcpServer::newConnection, this, &Server::NewConnection);
}

Server::~Server() { qDebug() << "Server stop!"; }

bool Server::StartServer() const { return TcpServer->listen(QHostAddress::Any, 8080); }

void Server::NewConnection() {
  QTcpSocket *socket = TcpServer->nextPendingConnection();
  if (!socket) {
    qDebug() << "Socket undefined";
    return;
  }

  auto Client = new ClientConnection(socket);

  this->ClientsConnections.insert(Client);

  connect(Client, &ClientConnection::__SearchPartner, [Client, this]() {
    if (this->ClientReadyToConnect != nullptr) {
      if (Client->CheckConnectionWithPartner(this->ClientReadyToConnect->GetSocket()) == false) {
        this->ConnectPartners(Client, this->ClientReadyToConnect);
      } else {
        for (auto it : ClientsConnections) {
          if (Client->CheckConnectionWithPartner(it->GetSocket()) == false && it != Client) {
            this->ConnectPartners(Client, this->ClientReadyToConnect);
            return;
          }
        }

        connect(this, &Server::ChangeClientReadyToConnect, [Client, this]() {
          if (this->ClientReadyToConnect == nullptr) {
            this->ClientReadyToConnect = Client;
          }
        });
      }
    } else {
      this->ClientReadyToConnect = Client;
    }
  });
}

void Server::ConnectPartners(ClientConnection *FirstClient, ClientConnection *SecondClient) {
  FirstClient->SetSocketChatPartner(SecondClient->GetSocket());
  SecondClient->SetSocketChatPartner(FirstClient->GetSocket());

  auto SuccessfullyFoundPartner = [](QTcpSocket *Socket) {
    Socket->write(JsonMess::ToJson("SuccessfullyFoundPartner", QList<QVariant>()));
  };

  SuccessfullyFoundPartner(FirstClient->GetSocket());
  SuccessfullyFoundPartner(SecondClient->GetSocket());

  this->ClientReadyToConnect = nullptr;

  emit ChangeClientReadyToConnect();
}
