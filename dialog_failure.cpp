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

void Dialog_failure::on_btn_ok_clicked()
{
    this->close();
}

