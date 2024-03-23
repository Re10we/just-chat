#include "Lib/Networking/ServerPart/Server.h"
#include "Widgets/MainWindow/Source/mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QTcpSocket>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  bool isServer = false;
  MainWindow w;

  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "--server" ||
        std::string(argv[i]) ==
            "-s") { // if app have a flag `server` - start server without client
      isServer = true;
    }
  }

  if (isServer) {
    const auto server = new Server();

    if (server->StartServer()) {
      qDebug() << "Start server is successfully ";
    } else {
      qCritical() << "Start server error";
    }
  } else {
    (new QTcpSocket())->connectToHost(QHostAddress::Any, 8080);
    w.show();
  }

  return a.exec();
}
