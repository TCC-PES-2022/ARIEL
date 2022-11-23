#include "dialog_warning.h"
#include "ui_dialog_warning.h"

Dialog_warning::Dialog_warning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_warning)
{
    ui->setupUi(this);
}

Dialog_warning::~Dialog_warning()
{
    delete ui;
}

void Dialog_warning::showUp(QString title, QString mensage)
{
  ui->lb_msg->setText(mensage);
  this->setWindowTitle(title);
  ui->lb_msg->setAlignment(Qt::AlignCenter);
  this->show();
}

void Dialog_warning::on_pushButton_clicked()
{
    this->close();
}

