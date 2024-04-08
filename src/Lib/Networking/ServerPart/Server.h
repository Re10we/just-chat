#ifndef SERVER_H
#define SERVER_H

#include "../../JSON/JsonConcept.h"
#include "ClientConnection.h"
#include <QObject>
#include <QTcpServer>
#include <QThread>

class Server : public QObject {

  Q_OBJECT

public:
  explicit Server(QObject *Parent = nullptr);
  virtual ~Server();

  bool StartServer() const;

private slots:
  void NewConnection();
  void ConnectPartners(ClientConnection *FirstClient, ClientConnection *SecondClient);

private:
  Q_SIGNAL void ChangeClientReadyToConnect();

private:
  QTcpServer *TcpServer;
  ClientConnection *ClientReadyToConnect;
  QSet<ClientConnection *> ClientsConnections;
};

#endif // SERVER_H