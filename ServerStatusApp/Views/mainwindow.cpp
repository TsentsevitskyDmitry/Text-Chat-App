#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::usersUpdate, ui->usersCount, static_cast<void (QLCDNumber::*)(const QString&)>(&QLCDNumber::display));
    connect(this, &MainWindow::stateUpdate, ui->statusLabel, &QLabel::setText);

    auto dataArrived = [this] (ServerInfo& info) {
        emit usersUpdate(QString::number(info.getUsersCount()));
        QString state = info.getRunningPort() ? "Running on " + QString::number(info.getRunningPort()) : "Not Running";
        emit stateUpdate(state);
    };

    controller.setDataArrivedCallback(dataArrived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_updateButton_clicked()
{
    controller.updateButtonPressed();
}
