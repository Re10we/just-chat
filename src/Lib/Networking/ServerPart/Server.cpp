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

  auto Client = new ClientConnection(socket);

  ClientsConnections.insert(Client);

  connect(Client, &ClientConnection::__SearchPartner, [Client, this]() {
    if (this->ClientReadyToConnect != nullptr) {

      if (Client->CheckConnectionWithPartner(
              this->ClientReadyToConnect->GetSocket()) == false) {

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
        for (auto it : ClientsConnections) {
          if (Client->CheckConnectionWithPartner(it->GetSocket()) == false) {

            Client->SetSocketChatPartner(
                this->ClientReadyToConnect->GetSocket());
            this->ClientReadyToConnect->SetSocketChatPartner(
                Client->GetSocket());

            auto SuccessfullyFoundPartner = [](QTcpSocket *Socket) {
              Socket->write(JsonMess::ToSerialize("SuccessfullyFoundPartner",
                                                  QList<QVariant>(true)));
            };

            SuccessfullyFoundPartner(Client->GetSocket());
            SuccessfullyFoundPartner(Client->GetSocketChatPartner());

            this->ClientReadyToConnect = nullptr;

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

      emit ChangeClientReadyToConnect();
    }
  });
}
