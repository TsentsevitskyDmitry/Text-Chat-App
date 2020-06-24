#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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

void MainWindow::on_installButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "./", tr("Executable (*.exe)"));
    if(fileName.length()){
        controller.installButtonPressed(fileName.toStdString());
    }
}

void MainWindow::on_removeButton_clicked()
{

}

void MainWindow::on_startButton_clicked()
{

}
