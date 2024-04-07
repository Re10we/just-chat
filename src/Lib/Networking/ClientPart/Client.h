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
  QString GetName() const;

  void StartExitFromChat();

  void SubmitMess(QString Mess);
  void SearchPartner();

  Q_SIGNAL void isFoundPatner();
  Q_SIGNAL void MessFromClient(QString Mess);
  Q_SIGNAL void SignalStartExitFromChat();

private:
  void SendToServer(QString NameFunc, QList<QVariant> ListArgument);

  Q_INVOKABLE void SuccessfullyFoundPartner(QList<QVariant> ArgV);
  void __SuccessfullyFoundPartner(bool isFound);

  Q_INVOKABLE void SubmitMessFromClient(QList<QVariant> ArgV);
  void __SubmitMessFromClient(QString Mess);

  Q_INVOKABLE void ExitFromChat(QList<QVariant> ArgV);
  void __ExitFromChat(bool isIniciator);

private slots:
  void ReadyRead();

private:
  QTcpSocket *Socket;
  QMap<QString, QMetaMethod> FnMap;
  QString ClientName;
};

#endif // CLIENT_H
