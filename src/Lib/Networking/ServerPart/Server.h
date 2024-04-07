#ifndef SERVER_H
#define SERVER_H

#include "ClientConnection.h"
#include <QObject>
#include <QTcpServer>
#include <QThread>

#define MAX_WAIT 10

class Server : public QObject {

  Q_OBJECT

public:
  explicit Server(QObject *Parent = nullptr);
  virtual ~Server();

  bool StartServer() const;

private slots:
  void NewConnection();

private:
  Q_SIGNAL void ChangeClientReadyToConnect();

private:
  QTcpServer *TcpServer;
  ClientConnection *ClientReadyToConnect;
  QSet<ClientConnection *> ClientsConnections;
};

#endif // SERVER_H