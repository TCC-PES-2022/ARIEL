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

        pthread_detach(pthread_self());
        sleep(1);
        std::cout << "+[GUI] Rodando " << endl;
        while (this->isRun)
        {

            uint8_t val = verificarFilas(&img_gui, &aut_gui, &con_gui, UI__GUI);
            if (val == RP_fila_imagem) {
                std::cout << "+[GUI] Cmd Recebido " << unsigned(img_gui.byte_controle) << endl;
                std::cout << "+[GUI] Cmd Anterior " << unsigned(img_gui.byte_controle_anterior) << endl;
                usleep(2000);

            }
            else if (val == 2) {
                std::cout << "+[GUI] Cmd Recebido " << unsigned(img_gui.byte_controle) << endl;
                std::cout << "+[GUI] Cmd Anterior " << unsigned(img_gui.byte_controle_anterior) << endl;
                usleep(2000);

            }
            else if (val == 3)
            {
                std::cout << "+[GUI] Cmd Recebido " << unsigned(aut_gui.byte_controle) << endl;
                std::cout << "+[GUI] Cmd Anterior " << unsigned(aut_gui.byte_controle_anterior) << endl;

                if(aut_gui.byte_controle_anterior==UI_EnviarLogin){
                    std::cout << "+chegou até aqui no while " << endl;
                     emit loginWindowsUpdate(aut_gui.byte_controle);
                }


            }

            sleep(1);
        }



}
