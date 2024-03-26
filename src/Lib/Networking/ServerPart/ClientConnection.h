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

private slots:
  void readyRead();

private:
  std::unique_ptr<QTcpSocket> Socket;
  QMap<QString, QMetaMethod> FnMap;
};

#endif // CLIENTCONNECTION_H
