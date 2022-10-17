#include <stdlib.h>
#include <unistd.h>

#include "corecontroller.h"
#include "iauthentication.h"
#include "communication_api.h"

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

    while (this->isRun) {
        val = verificarFilas(&img_controler, &aut_controler, &con_controler, UI__CTL);
        switch (val) {
		case RP_fila_autenticacao:
		    aut_controler.byte_controle = UI_Aguardar;

		    printf("RETURN: %d\n", login((char*)aut_controler.autenticao.login,
		    (char*) aut_controler.autenticao.senha));

		    aut_controler = *verificar_autenticacao_Controler(UI_Ok,
		    &aut_controler);

		    break;
		case RP_fila_conexao:
			if (con_controler.byte_controle == UI_EstabelecerConexao) {
				create_handler(&handler);		
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
				set_target_hardware_id(handler, "HNPFMS");
				set_target_hardware_pos(handler, "L");
				set_target_hardware_ip(handler, "127.0.0.1");

				/* carregar imagens */
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
			}

			break;
        }
        sleep(1);
    }



}
