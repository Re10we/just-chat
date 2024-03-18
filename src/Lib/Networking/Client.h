#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject {

  Q_OBJECT

public:
  explicit Client(QTcpSocket *Socket, QObject *Parent = nullptr);
  virtual ~Client();

private slots:
  void readyRead();

private:
  std::unique_ptr<QTcpSocket> Socket;
};

#endif // CLIENT_H