#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QTcpSocket>

class ClientConnection : public QObject {

  Q_OBJECT

public:
  explicit ClientConnection(QTcpSocket *Socket, QObject *Parent = nullptr);
  virtual ~ClientConnection();

private slots:
  void readyRead();

private:
  std::unique_ptr<QTcpSocket> Socket;
};

#endif // CLIENTCONNECTION_H
