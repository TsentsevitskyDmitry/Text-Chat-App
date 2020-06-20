#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "Controllers/ConnectDialogController.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT
private:
    ConnectDialogController controller;
    Ui::ConnectDialog *ui;

public:
    explicit ConnectDialog(ChatClient* _chat, QWidget *parent = nullptr);
    ~ConnectDialog();

private slots:
    void on_connectButton_clicked();
};

#endif // CONNECTDIALOG_H
