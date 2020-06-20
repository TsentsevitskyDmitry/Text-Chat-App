#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controllers/ChatViewController.h"
#include "Views/ConnectDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    ChatViewController controller;
    ConnectDialog dialog;
    void setupCallback();
    void setTitle(QString text);

private slots:
    void on_sendButton_clicked();
    void on_connectionButton_clicked();

signals:
    void messageRecieved(QString message);
    void errorRecieved(QString message);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
