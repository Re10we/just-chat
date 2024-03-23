#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject {
  Q_OBJECT

public:
  Client(QObject *Parent);
  ~Client();
};

#endif // CLIENT_H
