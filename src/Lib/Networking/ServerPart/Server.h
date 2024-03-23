#ifndef SERVER_H
#define SERVER_H

#include "ClientConnection.h"
#include <QObject>
#include <QTcpServer>
#include <memory>

class Server : public QObject {

  Q_OBJECT
public:
  explicit Server(QObject *Parent = nullptr);
  virtual ~Server();

  bool StartServer() const;

private slots:
  void newConnection();

private:
  std::unique_ptr<QTcpServer> TcpServer;
};

#endif // SERVER_H