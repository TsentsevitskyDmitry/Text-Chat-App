#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Service/ClientSocket.h"

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
    ClientSocket s;
    s.try_connect();

}
