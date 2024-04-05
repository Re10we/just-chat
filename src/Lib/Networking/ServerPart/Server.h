#ifndef SERVER_H
#define SERVER_H

#include "ClientConnection.h"
#include <QObject>
#include <QTcpServer>
#include <boost/bimap.hpp>
#include <QThread>

#define MAX_WAIT 10

class Server : public QObject {

  Q_OBJECT

private:
  typedef boost::bimap<ClientConnection*, ClientConnection *>
      ClientConnectionsMapType;

  typedef ClientConnectionsMapType::value_type ValueMapType;

public:
  explicit Server(QObject *Parent = nullptr);
  virtual ~Server();

  bool StartServer() const;

private slots:
  void NewConnection();

private:
  QTcpServer* TcpServer;
  ClientConnection* ClientReadyToConnect;
  ClientConnectionsMapType ClientConnections;
};

#endif // SERVER_H