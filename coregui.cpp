#include "coregui.h"
#include <unistd.h>

CoreGUI::CoreGUI(QObject *parent)
    : QObject{parent}
{
    qInfo()<<"coreGUI criada";
    this->isRun=true;
}


void CoreGUI::start()
{
    uint8_t val_teste = 0;
    static st_ui_image img_gui;
    static st_ui_aut aut_gui;
    static st_ui_conexao con_gui;
    iniciar_UI_interface(&img_gui, &aut_gui, &con_gui, UI__GUI);
    pthread_detach(pthread_self());
    sleep(1);
    std::cout << "+[GUI] Rodando " << endl;
    while (this->isRun)
    {

        uint8_t val = verificarFilas(&img_gui, &aut_gui, &con_gui, UI__GUI);
        if (val == RP_fila_imagem) {
            std::cout << "+[GUI] Cmd Recebido " << unsigned(img_gui.byte_controle) << endl;
            std::cout << "+[GUI] Cmd Anterior " << unsigned(img_gui.byte_controle_anterior) << endl;
            if(img_gui.byte_controle_anterior == UI_Informacoes_Imagem)
            {
                emit imageFileUpdate(img_gui.img_info.tabela_de_img,img_gui.img_info.tam);
            }
            else if(img_gui.byte_controle_anterior == UI_Carregar_Imagem && img_gui.byte_controle == UI_Ok)
            {
                printf("\r\nEnviando Solicitação de Imagem \r\n");
                img_gui =*carregar_imagem_GUI(UI_Informacoes_Imagem,&img_gui);
            }

        }
        else if (val == RP_fila_transf_imagem) {
            std::cout << "+[GUI] Cmd Recebido " << unsigned(img_gui.byte_controle) << endl;
            std::cout << "+[GUI] Cmd Anterior " << unsigned(img_gui.byte_controle_anterior) << endl;

            if(img_gui.byte_controle == UI_Andamento_Transferencia){
                printf("\n Json: %s  ",(char*)img_gui.img_transf.prt_json);
                fflush(stdout);
            }
            else if(img_gui.byte_controle == UI_Fim_Transferencia){
                printf("\n Status : %d  ",img_gui.img_transf.status_transf);
                fflush(stdout);
            }
        }
        else if (val == RP_fila_autenticacao)
        {
            std::cout << "+[GUI] Cmd Recebido " << unsigned(aut_gui.byte_controle) << endl;
            std::cout << "+[GUI] Cmd Anterior " << unsigned(aut_gui.byte_controle_anterior) << endl;

            if(aut_gui.byte_controle_anterior == UI_EnviarLogin){
                std::cout << "+chegou até aqui no while " << endl;
                emit loginWindowsUpdate(aut_gui.byte_controle);
            }



        }
        else if ( val == RP_fila_conexao)
        {
            std::cout << "+[GUI] Cmd Recebido " << unsigned(con_gui.byte_controle) << endl;
            std::cout << "+[GUI] Cmd Anterior " << unsigned(con_gui.byte_controle_anterior) << endl;
        }

        sleep(1);
    }



}
