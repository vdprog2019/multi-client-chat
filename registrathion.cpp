#include "registrathion.h"
#include "ui_registrathion.h"
#include "clientsocketadapter.h"
#include <QMessageBox>
registrathion::registrathion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registrathion)
{
    ui->setupUi(this);
}

registrathion::~registrathion()
{
    delete ui;
}

void registrathion::on_pushButton_clicked()
{
    QMessageBox m(this);
    if(ClientSocketAdapter::RegistUser(this->ui->LoginEdit->text(), this->ui->PasswordEdit->text()))
        m.setText("Successes!");
    else
        m.setText("Error!");
    m.exec();
    this->ui->LoginEdit->clear();
    this->ui->PasswordEdit->clear();
}

void registrathion::on_pushButton_2_clicked()
{
    this->close();
}
