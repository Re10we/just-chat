#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../../Lib/Networking/ClientPart/Client.h"
#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void SetClient(Client* NewClient);

private slots:
  void ConnectionBtn_Clicked();
  void SubmitLine_ReturnPressed();
  void HandleFoundPartner();

private:
  Ui::MainWindow *ui;
  Client* ClientSender;
};
#endif // MAINWINDOW_H
