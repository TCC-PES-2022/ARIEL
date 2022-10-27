#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "dialog_failure.h"
#include "mainwindow.h"
#include "usermanager.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
     void loginSucessAuthentication();

public slots:
     void updateAuthenticationRequest(int authenticationResponse);


private slots:

    //void updateAuthenticationRequest(int authenticationResponse);
    void on_txt_userName_textChanged(const QString &arg1);

    void on_txt_password_textChanged(const QString &arg1);

    void on_btn_login_clicked();

private:
    Ui::LoginWindow *ui;
    userManager usermanger;
    Dialog_failure *dialog_falilure;
    QMainWindow *mainScreen;
    void setUpInterface();
};

#endif // LOGINWINDOW_H
