#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include "../../JSON/JsonConcept.h"
#include <QMap>
#include <QMetaMethod>
#include <QObject>
#include <QTcpSocket>

class ClientConnection : public QObject {

  Q_OBJECT

public:
  explicit ClientConnection(QTcpSocket *Socket, QObject *Parent = nullptr);
  virtual ~ClientConnection();

private:
  Q_INVOKABLE void SetName(QList<QVariant> ArgV);
  void __SetName(QString NewName);

  Q_INVOKABLE void SubmitMess(QList<QVariant> ArgV);
  void __SubmitMess(QString Mess);

public:
  void SetSocketChatPartner(QTcpSocket *SocketChatPartner);
  QTcpSocket* GetSocket();

  Q_INVOKABLE void SearchPartner(QList<QVariant> ArgV);
  Q_SIGNAL void __SearchPartner();

  void SendToPartner() const;

private slots:
  void readyRead();

private:
  QTcpSocket* Socket;
  QTcpSocket* SocketChatPartner;
  QMap<QString, QMetaMethod> FnMap;
  QString NameUser;
};

#endif // CLIENTCONNECTION_H
