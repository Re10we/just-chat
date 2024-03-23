#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->ConnectChatBtn, &QAbstractButton::clicked, this,
          &MainWindow::ConnectionBtn_Clicked);

  ui->ErrorUserNameLabel->setVisible(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ConnectionBtn_Clicked() {
  if (ui->UserNameLine->text().size() > 2) {
    qDebug() << "Good username!";
  } else {
    ui->ErrorUserNameLabel->setText("Field 'Username' is void");
    ui->ErrorUserNameLabel->setVisible(true);
  }
}
