#include <stdlib.h>
#include <unistd.h>
#include "corecontroller.h"
#include <pthread.h>
#include <cjson/cJSON.h>

#define FIND_STUB_FILE "/pes/findstub.json"

struct upload_thr
{
    CommunicationHandlerPtr comHandler;
    st_ui_image img_controler;
    st_ui_aut aut_controler;
};
void *ptrUploadthread(void *ptr);

CoreController::CoreController(QObject *parent)
    : QObject{parent}
{
    qInfo()<<"controlador criado";
    ImageOperationResult rs =  create_handler(&imageHandler);
    create_handler(&comHandler);
//    printf("%d",rs == IMAGE_OPERATION_OK);
    homePath = string(getenv("HOME"));
}

void CoreController::parseFindStub()
{
    string findStubPath = homePath + "/" + FIND_STUB_FILE;
    FILE *findStubFile = fopen(findStubPath.c_str(), "r");
    if (findStubFile != NULL)
    {
        fseek(findStubFile, 0, SEEK_END);
        size_t findStubFileSize = ftell(findStubFile);
        rewind(findStubFile);

        char *findStubFileContent = (char *)malloc(findStubFileSize + 1);
        if (findStubFileContent != NULL)
        {
            size_t result = fread(findStubFileContent, 1, findStubFileSize, findStubFile);
            if (result == findStubFileSize)
            {

                findStubFileContent[findStubFileSize] = '\0';

                cJSON *config = cJSON_Parse(findStubFileContent);
                if (config != NULL)
                {
                    cJSON *devices = cJSON_GetObjectItemCaseSensitive(config, "devices");
                    if (devices != NULL)
                    {
                        cJSON *device = cJSON_GetArrayItem(devices, 0);
                        if (device != NULL)
                        {
                            cJSON *ip = cJSON_GetObjectItemCaseSensitive(device, "ip");
                            if (ip != NULL)
                            {
                                targetIp = string(ip->valuestring);
                            }
                        }
                    }
                }
            }

            free(findStubFileContent);
        }
        fclose(findStubFile);
    }
}

void CoreController::start()
{
    int opt;
    unsigned char val;
    static st_ui_image img_controler = {0};
    static st_ui_aut aut_controler = {0};
    static st_ui_conexao con_controler = {0};
    img_controler.img_transf.prt_json = NULL;
    iniciar_UI_interface(&img_controler, &aut_controler, &con_controler, UI__CTL);

    this->isRun=true;
    unsigned char tmp = 0;
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

                con_controler = *conexoes_Controler(UI_Falha,&con_controler);

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
//                printf("Print Ptr imgPATH CTRL\r\n");
//                printf("%s \r\n",(char*)img_controler.dir_img.diretorio_img);
//                printf("Print Ptr cmpPATH CTRL\r\n");
//                printf("%s \r\n",(char*)img_controler.dir_img.diretorio_cmp);

                char *pn; // TODO - ADICIONAR PN NA RESPOSTA
                ImageOperationResult result = import_image(imageHandler,(char*)img_controler.dir_img.diretorio_img,&pn);
                result = import_image(imageHandler,(char*)img_controler.dir_img.diretorio_cmp,NULL);

//                printf("Print PARTNUMBER CTRL\r\n");
//                printf("%s \r\n",(char*)pn);


                if(result == IMAGE_OPERATION_OK)
                {

                    img_controler= *carregar_imagem_Controler(UI_Ok,&img_controler);
                    logger(LG_IMAGE,"%s;%s;",(char*)aut_controler.autenticao.login,"Imagem Carregada");

                }
                else
                {
                    img_controler= *carregar_imagem_Controler(UI_Falha,&img_controler);
                    logger(LG_IMAGE,"%s;%s;",(char*)aut_controler.autenticao.login,"Falha na Imagem");

                }
                // TODO - Resposta no formato:
                // Resposta = UI_Ok ou Resposta = UI_Falha

            }
            else if(img_controler.byte_controle == UI_Informacoes_Imagem)
            {
                //TODO - Rotina para listar as imagens

                ImageOperationResult result = get_images(imageHandler,&img_controler.img_info.tabela_de_img,&img_controler.img_info.tam);
//                printf("/r/n %d /r/n",img_controler.img_info.tam);
//                for (int i = 0; i< img_controler.img_info.tam;i++)
//                {
//                    printf("/r/n BIN: %s /r/n",(char*)img_controler.img_info.tabela_de_img[i]);
//                }
                // img_controler.img_info.tabela_de_img <- Maximo de 10 strings por envio
                // img_controler.img_info.quantidade_de_imagens_total <- quantidade de PNs existeentes
                // img_controler.img_info.offset_imagens <- Posição da lista de PNs a ser enviada
                // Qualquer outra informação extra tem que ser comunicada
                //TODO - Resposta no formato:
                // Resposta = UI_Ok ou Resposta = UI_Falha
                if(result == IMAGE_OPERATION_OK)
                {
                    img_controler= *carregar_imagem_Controler(UI_Ok,&img_controler);}

                else{
                    img_controler= *carregar_imagem_Controler(UI_Falha,&img_controler);
                }
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
            if (img_controler.byte_controle == UI_Iniciar_Transferencia)
            {
               logger(LG_IMAGE,"%s;%s;",(char*)aut_controler.autenticao.login,"Transferencia iniciada");

               // if(img_controler.img_info.tam == 0)
               // {
               //     img_controler =*transferir_imagem_Controler(UI_Falha,&img_controler);
               //     break;
               // }
                // Conexao TFTP
                set_tftp_dataloader_server_port(comHandler, 5959);
                set_tftp_targethardware_server_port(comHandler, 59595);
                // Callback TFTP
                upload_information_status_callback callback = [](CommunicationHandlerPtr handler,
                        const char *upload_information_status_json,
                        void *context) -> CommunicationOperationResult
                {

                    st_ui_image *tmp =(st_ui_image*)context;
                    if (tmp->img_transf.prt_json != NULL)
                    {
                        free(tmp->img_transf.prt_json);
                    }
                    tmp->img_transf.prt_json = strdup(upload_information_status_json);
                    tmp =transferir_imagem_Controler(UI_Andamento_Transferencia,tmp);
                    return COMMUNICATION_OPERATION_OK;
                };
                register_upload_information_status_callback(comHandler, callback, &img_controler);
                // Set Target
                set_target_hardware_id(comHandler, "HNPFMS");
                set_target_hardware_pos(comHandler, "L");

                targetIp = string("127.0.0.1"); // Default to localhost
                parseFindStub();
                qDebug() << "Target IP: " << targetIp.c_str();
                set_target_hardware_ip(comHandler, targetIp.c_str());
                printf("Num of Images: %d\r\n",img_controler.img_info.tam);
                fflush(stdout);
                Load *loads = (Load *)malloc((img_controler.img_info.tam+1)*sizeof(Load));
                for (int i = 0;i<img_controler.img_info.tam;i++){
                    strcpy(loads[i].partNumber, img_controler.img_info.tabela_de_img[i]);
                    char *ln = NULL;
                    get_image_path(imageHandler,loads[i].partNumber,&ln);
                    strcpy(loads[i].loadName, ln);
                }

                char *cn = NULL;
                get_compatibility_path(imageHandler,img_controler.img_info.tabela_de_img,img_controler.img_info.tam,&cn);
                strcpy(loads[img_controler.img_info.tam].partNumber, "00000000");
                strcpy(loads[img_controler.img_info.tam].loadName, cn);

                set_load_list(comHandler, loads, img_controler.img_info.tam + 1);
                // Content is copied in set_load_list, it is safe to free it
                free(loads);
                //                /* certificado */
                Certificate certificate;
                string str = homePath + string("/pes/certificate/pescert.crt");
                strcpy(certificate.certificatePath, str.c_str());
                set_certificate(comHandler, certificate);

                /* upload */

                upload_thr *tmp = (upload_thr*)malloc(sizeof(upload_thr));

                tmp->comHandler = comHandler;
                tmp->img_controler = img_controler;
                tmp->aut_controler = aut_controler;
                pthread_t tmp2;
                pthread_create(&tmp2, NULL, ptrUploadthread, tmp);
                pthread_detach(tmp2);

            }
            else if (img_controler.byte_controle == UI_Cancelar)
            {
                abort_upload(comHandler,OPERATION_ABORTED_BY_THE_OPERATOR);
                logger(LG_IMAGE,"%s;%s;",(char*)aut_controler.autenticao.login,"Transferencia cancelada");

               //img_controler =*transferir_imagem_Controler(UI_Ok,&img_controler);
            }
            break;
        default:
            break;
        }
        sleep(1);
    }



}

void *ptrUploadthread(void *ptr)
{
    upload_thr *tmp = (upload_thr*)ptr;
    CommunicationOperationResult result = upload(tmp->comHandler);
    tmp->img_controler.img_transf.status_transf = (result == COMMUNICATION_OPERATION_OK);
    tmp->img_controler =*transferir_imagem_Controler(UI_Fim_Transferencia,&tmp->img_controler);
    if(result == COMMUNICATION_OPERATION_OK){
        logger(LG_IMAGE,"%s;%s;",(char*)tmp->aut_controler.autenticao.login,"Transferencia Finalizada");
    }
    else
    {
      logger(LG_IMAGE,"%s;%s;",(char*)tmp->aut_controler.autenticao.login,"Transferencia Não Finalizada");
    }
    free(tmp);
}
