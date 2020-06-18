#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Service/ServerSocket.h"
#include "Messages/ChatMessage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::messageRecieved, ui->textBrowser, &QTextBrowser::append);
    connect(this, &MainWindow::errorRecieved, ui->textBrowser, &QTextBrowser::append);
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

void MainWindow::on_pushButton_clicked()
{
    controller.sendButtonClicked(ui->sendEdit->text().toStdString());
}

void MainWindow::on_pushButton_2_clicked()
{
    controller.testConnect();
    setupCallback();
}

void MainWindow::on_pushButton_3_clicked()
{
    controller.testRegister(ui->regEdit->text().toStdString());
}
