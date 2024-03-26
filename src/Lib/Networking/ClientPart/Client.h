#ifndef CLIENT_H
#define CLIENT_H

#include "../../JSON/JsonConcept.h"
#include <QObject>
#include <QTcpSocket>
#include <memory>

class Client : public QObject {
  Q_OBJECT

public:
  Client(QObject *Parent = nullptr,
         QHostAddress HostAddress = QHostAddress::Any, quint16 Port = 8080);
  ~Client();

  void SetName(QString NewNameClient);

private:
  void SendToServer(QString NameFunc, QList<QVariant> ListArgument);

private:
  std::unique_ptr<QTcpSocket> Socket;
};

#endif // CLIENT_H
