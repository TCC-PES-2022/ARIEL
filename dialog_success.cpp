#include "dialog_success.h"
#include "ui_dialog_success.h"

Dialog_success::Dialog_success(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_success)
{
    ui->setupUi(this);
}

Dialog_success::~Dialog_success()
{
    delete ui;
}

void Dialog_success::showUp(QString title, QString mensage)
{
    ui->lb_msg->setText(mensage);
    this->setWindowTitle(title);
    ui->lb_msg->setAlignment(Qt::AlignCenter);
    this->show();
}

void Dialog_success::on_pushButton_clicked()
{
    this->close();
}

