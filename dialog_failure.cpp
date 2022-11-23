#include "dialog_failure.h"
#include "ui_dialog_failure.h"

Dialog_failure::Dialog_failure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_failure)
{
    ui->setupUi(this);
}

Dialog_failure::~Dialog_failure()
{
    delete ui;
}

void Dialog_failure::showUp(QString title, QString mensage)
{
    ui->lb_msg->setText(mensage);
    this->setWindowTitle(title);
    ui->lb_msg->setAlignment(Qt::AlignCenter);
    this->show();
}

void Dialog_failure::on_btn_ok_clicked()
{
    this->close();
}

