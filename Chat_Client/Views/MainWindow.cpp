#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Service/ServerSocket.h"
#include "Messages/ChatMessage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connectDialog(controller.getChat(), this)
{
    ui->setupUi(this);
    connect(this, &MainWindow::messageRecieved, ui->textBrowser, &QTextEdit::append);
    connect(this, &MainWindow::errorRecieved, ui->textBrowser, &QTextEdit::append);
    setupCallback();
}

MainWindow::~MainWindow()
{
    controller.disconnect();
    delete ui;
}

void MainWindow::setupCallback()
{
    auto message = [this] (string text) {
        emit messageRecieved(QString::fromStdString(text));
    };
    auto error = [this] (string text) {
        emit errorRecieved(QString::fromStdString(text));
    };

    controller.setTextMessageCallback(message);
    controller.setErrorMessageCallback(error);
}

void MainWindow::setTitle(QString text)
{
    this->setWindowTitle(text);
}

void MainWindow::on_connectionButton_clicked()
{
    if (connectDialog.exec() ==  QDialog::DialogCode::Rejected){
        return;
    }
    setTitle("Connecting...");
    controller.tryConnect();
    QString result = controller.tryRegister() ? "Connected" : "Error";
    setTitle(result);
}

void MainWindow::on_sendButton_clicked()
{
    controller.sendButtonClicked(ui->sendEdit->toPlainText().toStdString());
    ui->sendEdit->clear();
}
