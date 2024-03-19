#include "Lib/Networking/Server.h"
#include "Widgets/MainWindow/Source/mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Server server;
  server.StartServer();

  //MainWindow w;
  //w.show();
  return a.exec();
}
