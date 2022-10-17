#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::updateAuthenticationRequest(int authenticationResponse)
{
        if(authenticationResponse==UI_Ok){
            emit loginSucessAuthentication();
            this->close();
        }else if(authenticationResponse==UI_Falha){

            QMessageBox::warning(this,"Autenticação Login","NOme do usuário ou senha inválidos");
            ui->txt_userName->setEnabled(true);
            ui->txt_password->setEnabled(true);
            ui->btn_login->setEnabled(true);
            ui->txt_password->clear();
            ui->txt_userName->clear();
        }
}

void LoginWindow::on_btn_login_clicked()
{
        QString userName=ui->txt_userName->text();
        QString password=ui->txt_password->text();

        ui->txt_password->setEnabled(false);
        ui->txt_userName->setEnabled(false);
        ui->btn_login->setEnabled(false);

        usermanger.authenticarUser(userName,password);
}

