#include "ConnectDialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(ChatClient* _chat, QWidget *parent) :
    QDialog(parent),
    controller(_chat),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    ui->ipEdit->setText(controller.getPrevSettings().getIp());
    ui->portEdit->setText(controller.getPrevSettings().getPort());
    ui->nameEdit->setText(QString::fromStdString(controller.getPrevSettings().getName()));
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_connectButton_clicked()
{
    controller.connectButtonClicked(this->ui->ipEdit->text().toStdString(),
                                    this->ui->portEdit->text().toStdString(),
                                    this->ui->nameEdit->text().toStdString()
                                    );
    this->close();
}
