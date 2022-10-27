#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>



LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setUpInterface();

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
                dialog_falilure = new Dialog_failure();
                dialog_falilure->show();
                ui->txt_userName->setEnabled(true);
                ui->txt_password->setEnabled(true);
                ui->btn_login->setEnabled(true);
                ui->txt_password->clear();
                ui->txt_userName->clear();
            }
}

void LoginWindow::setUpInterface()
{
   ui->txt_password->clear();
   ui->txt_userName->clear();
   ui->btn_login->setEnabled(false);
   ui->txt_userName->setAlignment(Qt::AlignHCenter);
   ui->txt_password->setAlignment(Qt::AlignHCenter);
   ui->txt_userName->setPlaceholderText("Nome de usuário");
   ui->txt_password->setPlaceholderText("Senha");
}




void LoginWindow::on_txt_userName_textChanged(const QString &arg1)
{
    if(arg1!="" && ui->txt_password->text()!=""){
        ui->btn_login->setEnabled(true);
    }else{
        ui->btn_login->setEnabled(false);
    }
}


void LoginWindow::on_txt_password_textChanged(const QString &arg1)
{
    if(arg1!="" && ui->txt_userName->text()!=""){
        ui->btn_login->setEnabled(true);
    }else{
        ui->btn_login->setEnabled(false);
    }
}


void LoginWindow::on_btn_login_clicked()
{

    //UserManager_stub userManager;
    QString userName=ui->txt_userName->text();
    QString password=ui->txt_password->text();
    //dialog_falilure = new Dialog_failure();
    //mainScreen = new MainWindow();
    usermanger.authenticarUser(userName,password);
    //bool isAuthernticate=userManager.authenticarUser(userName,password);

    }

