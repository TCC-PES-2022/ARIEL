/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *txt_userName;
    QLineEdit *txt_password;
    QPushButton *btn_login;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/Ariel/img/Ariel2.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoginWindow->setWindowIcon(icon);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(250, 30, 241, 161));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/Ariel/img/Ariel1.png")));
        label->setScaledContents(true);
        txt_userName = new QLineEdit(centralwidget);
        txt_userName->setObjectName("txt_userName");
        txt_userName->setGeometry(QRect(150, 240, 461, 28));
        txt_password = new QLineEdit(centralwidget);
        txt_password->setObjectName("txt_password");
        txt_password->setGeometry(QRect(150, 280, 461, 28));
        btn_login = new QPushButton(centralwidget);
        btn_login->setObjectName("btn_login");
        btn_login->setGeometry(QRect(160, 340, 441, 30));
        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName("statusbar");
        LoginWindow->setStatusBar(statusbar);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "ARIEL", nullptr));
        label->setText(QString());
        btn_login->setText(QCoreApplication::translate("LoginWindow", "Entrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
