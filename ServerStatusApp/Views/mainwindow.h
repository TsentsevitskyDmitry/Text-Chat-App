#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controllers/StatusViewController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    StatusViewController controller;
    void alert(QString title);

private slots:
    void on_updateButton_clicked();
    void on_installButton_clicked();
    void on_removeButton_clicked();
    void on_startButton_clicked();

    void on_stopButton_clicked();

signals:
    void usersUpdate(QString message);
    void stateUpdate(QString message);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};

#endif // MAINWINDOW_H
