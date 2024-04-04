#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->ConnectChatBtn, &QAbstractButton::clicked, this,
          &MainWindow::ConnectionBtn_Clicked);
  connect(ui->SubmitLine, &QLineEdit::returnPressed, this,
          &MainWindow::SubmitLine_ReturnPressed);

  ui->ErrorUserNameLabel->setVisible(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ConnectionBtn_Clicked() {
  if (ui->UserNameLine->text().size() > 2) {
    ClientSender->SearchPartner();
    //ClientSender->SetName(ui->UserNameLine->text());

    ui->PagesStacked->setCurrentIndex(ui->PagesStacked->currentIndex() + 1);
  } else {
    ui->ErrorUserNameLabel->setText("Field 'Username' is void");
    ui->ErrorUserNameLabel->setVisible(true);
  }
}

void MainWindow::SubmitLine_ReturnPressed() {
  if (ui->SubmitLine->displayText().size() > 0) {
    ClientSender->SubmitMess(ui->SubmitLine->displayText());
  }
}

void MainWindow::SetClient(Client *NewClient) {
  this->ClientSender = NewClient;
}
