#include "usermanager.h"

userManager::userManager(QObject *parent)
    : QObject{parent}
{

}

void userManager::authenticarUser(QString userName, QString password)
{


    QByteArray ba_password = password.toLocal8Bit();
    char *c_password = ba_password.data();
    memcpy(auteticationGUI.autenticao.senha,&c_password,32*sizeof(char));

    QByteArray ba_userName = userName.toLocal8Bit();
    char *c_userName = ba_userName.data();
    memcpy(auteticationGUI.autenticao.login,&c_userName,32*sizeof(char));

    auteticationGUI.byte_controle=UI_EnviarLogin;

    auteticationGUI = *verificar_autenticacao_GUI(UI_EnviarLogin, &auteticationGUI);

}

void userManager::confirmeReceivedAuthenticationResponse()
{
    auteticationGUI = *verificar_autenticacao_GUI(UI_Null, &auteticationGUI);          // comando null enviado para reiniciar a máquina de estado.
}
