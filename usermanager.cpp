#include "usermanager.h"

userManager::userManager(QObject *parent)
    : QObject{parent}
{

}

void userManager::authenticarUser(QString userName, QString password)
{


    /*QByteArray ba_password = password.toLocal8Bit();
    char *c_password = ba_password.data();
    memcpy(auteticationGUI.autenticao.senha,&c_password,32*sizeof(char));

    QByteArray ba_userName = userName.toLocal8Bit();
    char *c_userName = ba_userName.data();
    memcpy(auteticationGUI.autenticao.login,&c_userName,32*sizeof(char));
    */

    //Senha
       QByteArray ba_password = password.toLocal8Bit();
       char *c_password = ba_password.data();
       int tam = strlen(c_password);
       memcpy(&auteticationGUI.autenticao.senha,c_password,tam);
       auteticationGUI.autenticao.senha[tam] = '\0';
       //Usuario -

       // TODO - Verificar o tamanho usuario e senha e o '\0' no final
       QByteArray ba_userName = userName.toLocal8Bit();
       char *c_userName = ba_userName.data();
       tam = strlen(c_userName);
       memcpy(&auteticationGUI.autenticao.login,c_userName,tam);
       auteticationGUI.autenticao.login[tam] = '\0';
       //set coontrole



    auteticationGUI.byte_controle=UI_EnviarLogin;

    //auteticationGUI = *verificar_autenticacao_GUI(UI_EnviarLogin, &auteticationGUI);
    // Envio da requisição
       //JUAN: VERIFICA SEMPRE O QUE VOCE VAI ENVIAR PARA A FILA
       auteticationGUI = *verificar_autenticacao_GUI(UI_EnviarLogin, &auteticationGUI);

}

void userManager::confirmeReceivedAuthenticationResponse()
{
    auteticationGUI = *verificar_autenticacao_GUI(UI_Null, &auteticationGUI);          // comando null enviado para reiniciar a máquina de estado.
}
