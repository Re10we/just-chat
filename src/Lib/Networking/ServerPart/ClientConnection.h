#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include "../../JSON/JsonConcept.h"
#include <QMap>
#include <QMetaMethod>
#include <QObject>
#include <QSet>
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
  void SubmitMessFromClient(QString Mess);

  Q_INVOKABLE void ExitFromChat(QList<QVariant> ArgV);
  void __ExitFromChat(bool isIniciator);

  void SendToClient(QString NameFunc, QList<QVariant> ArgV);

public:
  void SetSocketChatPartner(QTcpSocket *SocketChatPartner);
  QTcpSocket *GetSocketChatPartner() const;

  QTcpSocket *GetSocket();
  QString GetName() const; 

  Q_INVOKABLE void SearchPartner(QList<QVariant> ArgV);
  Q_SIGNAL void __SearchPartner();

  void SendToPartner() const;

  bool CheckConnectionWithPartner(QTcpSocket *CheckedSocket) const;

private slots:
  void readyRead();

private:
  QTcpSocket *Socket;
  QTcpSocket *SocketChatPartner;
  QMap<QString, QMetaMethod> FnMap;
  QString ClientName;
  QSet<QTcpSocket *> HistoryOfConections;
};

#endif // CLIENTCONNECTION_H
