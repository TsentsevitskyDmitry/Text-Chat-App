#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

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
    auto alertArrived = [this] (std::string& text) {
        alert(QString::fromStdString(text));
    };

    controller.setDataArrivedCallback(dataArrived);
    controller.setAlertCallback(alertArrived);
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
        controller.installButtonPressed(fileName.toStdWString());
    }
}

void MainWindow::on_removeButton_clicked()
{
    controller.removeButtonPressed();
}

void MainWindow::on_stopButton_clicked()
{
    controller.stopButtonPressed();
}

void MainWindow::on_startButton_clicked()
{
    controller.startButtonPressed();
}

void MainWindow::alert(QString text)
{
    QMessageBox box(QMessageBox::Icon::Information, "Information", text, QMessageBox::Button::NoButton, this);
    box.exec();
}
