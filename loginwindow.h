#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "UI_API.h"
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
     void on_btn_login_clicked();

private:
    Ui::LoginWindow *ui;
    userManager usermanger;
};

#endif // LOGINWINDOW_H
