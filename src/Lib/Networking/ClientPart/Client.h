#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <memory>

class Client : public QObject {
  Q_OBJECT

public:
  Client(QObject *Parent = nullptr,
         QHostAddress HostAddress = QHostAddress::Any, quint16 Port = 8080);
  ~Client();

  void SubmitMess(QString Massage);

private:
  std::unique_ptr<QTcpSocket> Socket;
};

#endif // CLIENT_H
