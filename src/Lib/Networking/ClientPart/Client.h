#ifndef CLIENT_H
#define CLIENT_H

#include "../../JSON/JsonConcept.h"
#include <QMetaMethod>
#include <QObject>
#include <QTcpSocket>

class Client : public QObject {
  Q_OBJECT

public:
  Client(QObject *Parent = nullptr,
         QHostAddress HostAddress = QHostAddress::Any, quint16 Port = 8080);
  ~Client();

  void SetName(QString NewNameClient);
  void SubmitMess(QString Mess);
  void SearchPartner();

  Q_SIGNAL void isFoundPatner();

private:
  void SendToServer(QString NameFunc, QList<QVariant> ListArgument);

  Q_INVOKABLE void SuccessfullyFoundPartner(QList<QVariant> ArgV);
  void __SuccessfullyFoundPartner(bool isFound);

private slots:
  void ReadyRead();

private:
  QTcpSocket *Socket;
  QMap<QString, QMetaMethod> FnMap;
};

#endif // CLIENT_H
