#include "ConnectDialog.h"
#include "ui_connectdialog.h"
#include <QMessageBox>
#include <QIntValidator>

ConnectDialog::ConnectDialog(ChatClient* _chat, QWidget *parent) :
    QDialog(parent),
    controller(_chat),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    ui->ipEdit->setText(controller.getPrevSettings().getIp());
    ui->portEdit->setText(controller.getPrevSettings().getPort());
    ui->nameEdit->setText(QString::fromStdString(controller.getPrevSettings().getName()));
    ui->portEdit->setValidator(new QIntValidator(0, 99999, this));
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_connectButton_clicked()
{
    bool success = controller.connectButtonClicked(this->ui->ipEdit->text().toStdString(),
                                    this->ui->portEdit->text().toStdString(),
                                    this->ui->nameEdit->text().toStdString()
                                    );
    if(!success){
        QMessageBox mBox(QMessageBox::Icon::Warning, "Wrong input", "Some fields are empty", QMessageBox::Button::NoButton, this);
        mBox.exec();
        return;
    }
    this->accept();
}
