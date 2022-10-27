#include <stdlib.h>
#include <unistd.h>

#include "corecontroller.h"
#include "iauthentication.h"
#include "icommunicationmanager.h"
#include "ilogger.h"

CoreController::CoreController(QObject *parent)
    : QObject{parent}
{
    qInfo()<<"controlador criado";

}


void CoreController::start()
{
    int opt;
    unsigned char val;
    static st_ui_image img_controler = {0};
    static st_ui_aut aut_controler = {0};
    static st_ui_conexao con_controler = {0};
    CommunicationHandlerPtr handler;

    iniciar_UI_interface(&img_controler, &aut_controler, &con_controler, UI__CTL);

    this->isRun=true;
    uint8_t tmp = 0;
    while (this->isRun) {
        //Verifica se existe mensagem na fila de mensagens do controlador
        val = verificarFilas(&img_controler, &aut_controler, &con_controler, UI__CTL);

        switch (val) {
        case RP_fila_autenticacao: // a struct aut_controler foi atualizada pelo usuário
            if(aut_controler.byte_controle == UI_EnviarLogin) // Requisitado autenticação do login
            {

                tmp = login((char*)aut_controler.autenticao.login,
                            (char*) aut_controler.autenticao.senha);
                if (tmp == AU_AUTHENTICATION_OK){
                    aut_controler = *verificar_autenticacao_Controler(UI_Ok,
                                                                      &aut_controler);
                    logger(LG_AUTHENTICATION,"%s;%s;",(char*)aut_controler.autenticao.login,"Autenticação Valida");
                }
                else
                {
                    aut_controler = *verificar_autenticacao_Controler(UI_Falha,
                                                                      &aut_controler);
                    logger(LG_AUTHENTICATION,"%s;%s;",(char*)aut_controler.autenticao.login,"Autenticação Invalida");

                }
            }
            else if (aut_controler.byte_controle == UI_Cadastrar) // Requisitado cadastrar novo usuario
            {

            }
            else if (aut_controler.byte_controle == UI_RemoverUsuario) // Requisitado remover usuario
            {

            }
            else
            {
                //Comando inválido
                aut_controler = *verificar_autenticacao_Controler(UI_Falha,&aut_controler);
            }
            break;
        case RP_fila_conexao: // a struct con_controler foi atualizada pelo usuário
            if (con_controler.byte_controle == UI_EstabelecerConexao) {
                create_handler(&handler);

                //con_controler.info_conexao.dataloader_server_port <- Porta enviada pelo Usuario
                //con_controler.info_conexao.targethardware_server_port <- Target enviado pelo usuário

                set_tftp_dataloader_server_port(handler, 5959);
                set_tftp_targethardware_server_port(handler, 59595);
                upload_information_status_callback callback = [](CommunicationHandlerPtr handler,
                        const char *upload_information_status_json,
                        void *context) -> CommunicationOperationResult
                {
                    printf("%s\n", upload_information_status_json);
                    return COMMUNICATION_OPERATION_OK;
                };
                register_upload_information_status_callback(handler, callback, NULL);

                /* configurar target */
                // Estruturas enviadas para configurar o target
                //con_controler.info_conexao.hardware_id
                //con_controler.info_conexao.hardware_ip
                //con_controler.info_conexao.hardware_pos

                set_target_hardware_id(handler, "HNPFMS");
                set_target_hardware_pos(handler, "L");
                set_target_hardware_ip(handler, "127.0.0.1");

                /* carregar imagens */
                // TODO - Essa parte não deveria estar aqui, quem carrega a imagens não é esse comando.
                Load loads[4];
                strcpy(loads[0].loadName, "images/load1.bin");
                strcpy(loads[0].partNumber, "00000001");
                strcpy(loads[1].loadName, "images/load2.bin");
                strcpy(loads[1].partNumber, "00000002");
                strcpy(loads[2].loadName, "images/load3.bin");
                strcpy(loads[2].partNumber, "00000003");
                strcpy(loads[3].loadName, "images/ARQ_Compatibilidade.xml");
                strcpy(loads[3].partNumber, "00000000");
                set_load_list(handler, loads, 4);

                /* certificado */
                Certificate certificate;
                strcpy(certificate.certificatePath, "certificate/pescert.crt");
                set_certificate(handler, certificate);

                /* upload */
                CommunicationOperationResult result = upload(handler);

                // TODO: Falta enviar a resposta.
                // Resposta = UI_Ok ou Resposta = UI_Falha
                // con_controler = conexoes_Controler(Resposta,&con_controler);
                //
            }
            else if (con_controler.byte_controle == UI_ListarConexoes) {
                con_controler = *conexoes_Controler(UI_Falha,&con_controler);
            }
            else if(con_controler.byte_controle == UI_EncerrarConexao)
            {
                con_controler = *conexoes_Controler(UI_Falha,&con_controler);
            }
            else // Comando Invalido
            {
                con_controler = *conexoes_Controler(UI_Falha,&con_controler);
            }
            break;
        case RP_fila_imagem:
            if(img_controler.byte_controle == UI_Carregar_Imagem)
            {
                //TODO - Rotina para carregar imagem
                printf("Print Ptr imgPATH CTRL\r\n");
                printf("%s \r\n",(char*)img_controler.dir_img.diretorio_img);
                printf("Print Ptr cmpPATH CTRL\r\n");
                printf("%s \r\n",(char*)img_controler.dir_img.diretorio_cmp);
                // Qualquer outra informação extra tem que ser comunicada
                // TODO - Resposta no formato:
                // Resposta = UI_Ok ou Resposta = UI_Falha
                img_controler= *carregar_imagem_Controler(UI_Falha,&img_controler);
            }
            else if(img_controler.byte_controle == UI_Informacoes_Imagem)
            {
                //TODO - Rotina para listar as imagens
                // img_controler.img_info.tabela_de_img <- Maximo de 10 strings por envio
                // img_controler.img_info.quantidade_de_imagens_total <- quantidade de PNs existeentes
                // img_controler.img_info.offset_imagens <- Posição da lista de PNs a ser enviada
                // Qualquer outra informação extra tem que ser comunicada
                //TODO - Resposta no formato:
                // Resposta = UI_Ok ou Resposta = UI_Falha
                img_controler= *carregar_imagem_Controler(UI_Falha,&img_controler);
            }
            else if(img_controler.byte_controle == UI_Apagar_Aquivo)
            {
                //TODO - Rotina para carregar imagem
                // img_controler.apagar_pn  <- PN Informado para apagar
                // Qualquer outra informação extra tem que ser comunicada
                //TODO - Resposta no formato:
                // Resposta = UI_Ok ou Resposta = UI_Falha
                img_controler= *carregar_imagem_Controler(UI_Falha,&img_controler);
            }
            break;
        case RP_fila_transf_imagem:
            break;
        default:
            break;
        }
        sleep(1);
    }



}
