#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Service/ClientSocket.h"
#include "Messages/DataTypeMessage.h"
#include "Messages/ChatMessage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    controller.sendButtonClicked(ui->sendEdit->text().toStdString());
}

void MainWindow::on_pushButton_2_clicked()
{
    controller.testConnect();
}

void MainWindow::on_pushButton_3_clicked()
{
    controller.testRegister(ui->regEdit->text().toStdString());
}
