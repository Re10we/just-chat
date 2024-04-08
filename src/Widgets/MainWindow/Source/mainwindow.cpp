#include "./ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->ConnectChatBtn, &QAbstractButton::clicked, this, &MainWindow::ConnectionBtn_Clicked);

  connect(ui->SubmitLine, &QLineEdit::returnPressed, this, &MainWindow::SubmitLine_ReturnPressed);

  connect(ui->ExitChat, &QAbstractButton::clicked, this, &MainWindow::ExitChatBtn_Clicked);

  ui->ErrorUserNameLabel->setVisible(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ConnectionBtn_Clicked() {
  if (ui->UserNameLine->text().size() > 2) {
    ClientSender->SearchPartner();
  } else {
    ui->ErrorUserNameLabel->setText("Field 'Username' is void");
    ui->ErrorUserNameLabel->setVisible(true);
  }
}

void MainWindow::ExitChatBtn_Clicked() { ClientSender->StartExitFromChat(); }

void MainWindow::SubmitLine_ReturnPressed() {
  if (ui->SubmitLine->displayText().size() > 0) {
    ClientSender->SubmitMess(ui->SubmitLine->displayText());

    ui->ChatBrowser->append(
        QString(ClientSender->GetName() + ": " + ui->SubmitLine->displayText()));

    ui->SubmitLine->clear();
  }
}

void MainWindow::HandleFoundPartner() {
  ClientSender->SetName(ui->UserNameLine->text());

  ui->PagesStacked->setCurrentIndex(ui->PagesStacked->currentIndex() + 1);
}

void MainWindow::HandleMessFromClient(QString Mess) { ui->ChatBrowser->append(Mess); }

void MainWindow::HandleExitFromChat() {
  ui->PagesStacked->setCurrentIndex(ui->PagesStacked->currentIndex() - 1);
}

void MainWindow::SetClient(Client *NewClient) {
  this->ClientSender = NewClient;

  connect(this->ClientSender, &Client::isFoundPatner, this, &MainWindow::HandleFoundPartner);

  connect(this->ClientSender, &Client::MessFromClient, this, &MainWindow::HandleMessFromClient);

  connect(this->ClientSender, &Client::SignalStartExitFromChat, this,
          &MainWindow::HandleExitFromChat);
}
