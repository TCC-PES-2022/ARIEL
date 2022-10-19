#include "UI_API.h"

using namespace std;
queue<st_ui_image> fila_imagem_GUI;
queue<st_ui_image> fila_imagem_Controler;

queue<st_ui_image> fila_transf_imagem_GUI;
queue<st_ui_image> fila_transf_imagem_Controler;

queue<st_ui_aut> fila_autent_GUI;
queue<st_ui_aut> fila_autent_Controler;

queue<st_ui_conexao> fila_conexao_GUI;
queue<st_ui_conexao> fila_conexao_Controler;

pthread_mutex_t lock_print;

///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\



st_ui_image* carregar_imagem_GUI(uint8_t cmd_controle, st_ui_image* val)
{
    //Máquina de Estados referente ao comando de Carregar Imagem lado GUI
    // cmd_controle -> Estado MQ_Imagem de solicitação
    // *val			-> Ponteiro da estrutura da imagem
    // Return: Estrutura st_ui_image contendo todas as informações referentes a imagem e o estado da ultima alteração feita pela MQ.

    static st_ui_image tmp = { 0 };
    static uint8_t cmd_anterior = 0;
    //tmp.byte_controle_anterior = val->byte_controle_anterior;

    switch (cmd_controle)
    {
    case UI_Null: // Reseta MQ
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        ui_api_debug("+[GUI][MQ] : Comando UI_Null - MQ carregar_imagem_GUI Resetada");
        break;
    case UI_Ok: // CTRL -> GUI
        ui_api_debug("+[GUI][MQ] : Comando UI_Ok");
        tmp.byte_controle = cmd_controle;
        break;
    case UI_Timeout:
        break;
    case UI_Aguardar:
        break;
    case UI_Falha:
        ui_api_debug("+[GUI][MQ] : Comando UI_Falha");
        tmp.byte_controle = cmd_controle;
        break;
    case UI_Carregar_Imagem:
        ui_api_debug("+[GUI][MQ] : Comando UI_Carregar_Imagem");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Informacoes_Imagem:
        ui_api_debug("+[GUI][MQ] : Comando UI_Informacoes_Imagem");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Apagar_Aquivo:
        ui_api_debug("+[GUI][MQ] : Comando UI_Apagar_Aquivo");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Cancelar:
        ui_api_debug("+[GUI][MQ] : Comando UI_Cancelar");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
        break;
    default:
        //Caso cmd_controle nao contemplado
        tmp.byte_controle = UI_Null;
        tmp.byte_controle_anterior = UI_Null;
        break;
    }
    return &tmp;
}
///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\




st_ui_image* carregar_imagem_Controler(uint8_t cmd_controle, st_ui_image* val)
{
    // Máquina de Estados referente ao comando de Carregar Imagem lado Controler
    // cmd_controle -> Estado MQ_Imagem de solicitação
    // *val			-> Ponteiro da estrutura da imagem
    // Return: Estrutura st_ui_image contendo todas as informações referentes a imagem e o estado da ultima alteração feita pela MQ.

    static st_ui_image tmp;
    static uint8_t cmd_anterior = 0;

    switch (cmd_controle)
    {
    case UI_Falha:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Falha");
        fila_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Ok:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Ok");
        fila_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Timeout:
        break;
    case UI_Aguardar:
        break;
    case UI_Null: // Reseta MQ
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Null - MQ carregar_imagem_Controler Resetada");
        break;
    case UI_Carregar_Imagem:
        ui_api_debug("+[CTL][MQ] : Comando UI_Carregar_Imagem");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Informacoes_Imagem:
        ui_api_debug("+[CTL][MQ] : Comando UI_Informacoes_Imagem");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Apagar_Aquivo:
        ui_api_debug("+[CTL][MQ] : Comando UI_Apagar_Aquivo");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Cancelar:
        ui_api_debug("+[CTL][MQ] : Comando UI_Cancelar");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    default:
        //Caso cmd_controle nao contemplado
        tmp.byte_controle = UI_Null;
        tmp.byte_controle_anterior = UI_Null;
        break;
    }

    return &tmp;
}

///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\


st_ui_image* transferir_imagem_GUI(uint8_t cmd_controle, st_ui_image* val) {

    //Máquina de Estados referente ao comando de Transferir Imagem
    // cmd_controle -> Estado MQ_Imagem de solicitação
    // *val			-> Ponteiro da estrutura da imagem
    // Return: Estrutura st_ui_image contendo todas as informações referentes a imagem e o estado da ultima alteração feita pela MQ.

    static st_ui_image& tmp = *val;
    static uint8_t cmd_anterior = 0;
    switch (cmd_controle)
    {
    case UI_Falha:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[GUI][MQ] : Comando UI_Falha");
        fila_transf_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Ok:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[GUI][MQ] : Comando UI_Ok");
        fila_transf_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Timeout:
        break;
    case UI_Aguardar:
        break;
    case UI_Null: // Reseta MQ
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        ui_api_debug("+[GUI][MQ] : Comando UI_Null - MQ transferir_imagem_GUI Resetada");
        break;
    case UI_Cancelar:
        ui_api_debug("+[GUI][MQ] : Comando UI_Cancelar");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_transf_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Iniciar_Transferencia:
        ui_api_debug("+[GUI][MQ] : Comando UI_Iniciar_Transferencia");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_transf_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Andamento_Transferencia:
        ui_api_debug("+[GUI][MQ] : Comando UI_Andamento_Transferencia");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_transf_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Fim_Transferencia:
        ui_api_debug("+[GUI][MQ] : Comando UI_Fim_Transferencia");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_transf_imagem_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    default:
        //Caso cmd_controle nao contemplado
        tmp.byte_controle = UI_Null;
        tmp.byte_controle_anterior = UI_Null;
        break;
    }
    return &tmp;
}
///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\

st_ui_image* transferir_imagem_Controler(uint8_t cmd_controle, st_ui_image* val) {

    //Máquina de Estados referente ao comando de Transferir Imagem
    // cmd_controle -> Estado MQ_Imagem de solicitação
    // *val			-> Ponteiro da estrutura da imagem
    // Return: Estrutura st_ui_image contendo todas as informações referentes a imagem e o estado da ultima alteração feita pela MQ.

    static st_ui_image tmp;
    static uint8_t cmd_anterior = 0;
    tmp.byte_controle_anterior = val->byte_controle_anterior;
    if (tmp.byte_controle_anterior != UI_Aguardar)
        tmp.byte_controle_anterior = cmd_controle;

    switch (cmd_controle)
    {
    case UI_Falha:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Falha");
        fila_transf_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Ok:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Ok");
        fila_transf_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Timeout:
        break;
    case UI_Aguardar:
        break;
    case UI_Null: // Reseta MQ
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Null - MQ transferir_imagem_Controler Resetada");
        break;
    case UI_Iniciar_Transferencia:
        ui_api_debug("+[CTL][MQ] : Comando UI_Iniciar_Transferencia");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_transf_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Andamento_Transferencia:
        ui_api_debug("+[CTL][MQ] : Comando UI_Andamento_Transferencia");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_transf_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Fim_Transferencia:
        ui_api_debug("+[CTL][MQ] : Comando UI_Fim_Transferencia");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_transf_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Cancelar:
        ui_api_debug("+[CTL][MQ] : Comando UI_Cancelar");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        fila_transf_imagem_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    default:
        //Caso cmd_controle nao contemplado
        tmp.byte_controle = UI_Null;
        tmp.byte_controle_anterior = UI_Null;
        break;
    }

    return &tmp;
}

///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\

int iniciar_UI_interface(st_ui_image* val, st_ui_aut* val2, st_ui_conexao *val3, uint8_t thread)
{
    //Função de inicialização da UI_Interface
    // stats		-> Se inicialização ocorreu com sucesso, retorna 1
    int stats = 0;

    if(thread == UI__GUI){
        memset(val, 0x0, sizeof(st_ui_image));
        memset(val2, 0x0, sizeof(st_ui_aut));
        memset(val3, 0x0, sizeof(st_ui_conexao));
        carregar_imagem_GUI(UI_Null, val);
        transferir_imagem_GUI(UI_Null, val);
        verificar_autenticacao_GUI(UI_Null, val2);
        conexoes_GUI(UI_Null,val3);
    }
    else{
        memset(val, 0x0, sizeof(st_ui_image));
        memset(val2, 0x0, sizeof(st_ui_aut));
        memset(val3, 0x0, sizeof(st_ui_conexao));
        verificar_autenticacao_Controler(UI_Null, val2);
        carregar_imagem_Controler(UI_Null, val);
        transferir_imagem_Controler(UI_Null, val);
        conexoes_GUI(UI_Null,val3);
    }
    stats = 1;

    return stats;
}

///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\

st_ui_conexao* conexoes_GUI(uint8_t cmd_controle, st_ui_conexao* val) {
    // Função que deve requisitar a lista de conexões.
    // cmd_controle -> Estado MQ de solicitação
    // *val			-> Ponteiro da estrutura da conexao
    // Return: Estrutura st_info_conexao contendo todas as informações referentes a imagem e o estado da ultima alteração feita pela MQ.
    static st_ui_conexao& tmp = *val;
    static uint8_t cmd_anterior = 0;
    switch (cmd_controle)
    {
    case UI_Null: // Reseta MQ
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        ui_api_debug("+[GUI][MQ] : Comando UI_Null - MQ listar_conexoes_GUI Resetada");
        break;
    case UI_Ok: // CTRL -> GUI
        ui_api_debug("+[GUI][MQ] : Comando UI_Ok");
        tmp.byte_controle = cmd_controle;
        break;
    case UI_Timeout:
        break;
    case UI_Aguardar:
        break;
    case UI_Falha:
        ui_api_debug("+[GUI][MQ] : Comando UI_Falha");
        tmp.byte_controle = cmd_controle;
        break;
    case UI_ListarConexoes:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_conexao_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        ui_api_debug("+[GUI][MQ] : Comando UI_ListarConexoes");
        break;
    case UI_EstabelecerConexao:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_conexao_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        ui_api_debug("+[GUI][MQ] : Comando UI_EstabelecerConexao");
        break;
    case UI_EncerrarConexao:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_conexao_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        ui_api_debug("+[GUI][MQ] : Comando UI_EncerrarConexao");
        break;
    default:
        break;
    }
    return &tmp;
}
///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\

st_ui_conexao* conexoes_Controler(uint8_t cmd_controle, st_ui_conexao* val){

    // Função que deve requisitar o estabelecimento da conexão.
    // cmd_controle -> Estado MQ de solicitação
    // *val			-> Ponteiro da estrutura da conexao
    // Return: Estrutura st_info_conexao contendo todas as informações referentes a imagem e o estado da ultima alteração feita pela MQ.

    st_ui_conexao& tmp = *val;
    static uint8_t cmd_anterior = 0;
    switch (cmd_controle)
    {
    case UI_Falha:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Falha");
        fila_conexao_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Ok:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Ok");
        fila_conexao_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Timeout:
        break;
    case UI_Aguardar:
        break;
    case UI_Null: // Reseta MQ
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Null - MQ conexoes_Controler Resetada");
        break;
    default:
        break;
    }
    return &tmp;
}


///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\


st_ui_aut* verificar_autenticacao_GUI(uint8_t cmd_controle, st_ui_aut* val)
{
    // Função que deve verificar a autenticação fornecida pelo usuário.
    // cmd_controle -> Estado MQ de solicitação
    // *val			-> Ponteiro da estrutura da autenticação
    // Return: Estrutura st_ui_aut contendo todas as informações referentes a imagem e o estado da ultima alteração feita pela MQ.

    static st_ui_aut & tmp = *val;
    static uint8_t cmd_anterior;
    switch (cmd_controle)
    {
    case UI_EnviarLogin:
        ui_api_debug("+[GUI][MQ] : Comando UI_EnviarLogin");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_autent_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Falha:
        ui_api_debug("+[GUI][MQ] : Comando UI_Falha");
        tmp.byte_controle = cmd_controle;
        break;
    case UI_Ok:
        ui_api_debug("+[GUI][MQ] : Comando UI_Ok");
        tmp.byte_controle = cmd_controle;
        break;
    case UI_Null:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        ui_api_debug("+[GUI][MQ] : Comando UI_Null - MQ verificar_autenticacao_GUI Resetada");
        break;
    case UI_Cadastrar:
        ui_api_debug("+[GUI][MQ] : Comando UI_Cadastrar");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_autent_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_RemoverUsuario:
        ui_api_debug("+[GUI][MQ] : Comando UI_RemoverUsuario");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_autent_Controler.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    default:
        break;
    }
    // memcpy(val,tmp,sizeof(st_ui_aut));
    return &tmp;
}
///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\


st_ui_aut* verificar_autenticacao_Controler(uint8_t cmd_controle, st_ui_aut* val)
{
    // Função que deve verificar a autenticação fornecida pelo usuário.
    // cmd_controle -> Estado MQ de solicitação
    // *val			-> Ponteiro da estrutura da autenticação
    // Return: Estrutura st_ui_aut contendo todas as informações referentes a imagem e o estado da ultima alteração feita pela MQ.

    static st_ui_aut& tmp = *val;
    static uint8_t cmd_anterior;
    switch (cmd_controle)
    {
    case UI_EnviarLogin:
        ui_api_debug("+[CTL][MQ] : Comando UI_EnviarLogin");
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        fila_autent_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Falha:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Falha");
        fila_autent_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Ok:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Ok");
        fila_autent_GUI.push(tmp);
        tmp.byte_controle = UI_Aguardar;
        break;
    case UI_Null:
        tmp = *val;
        tmp.byte_controle = cmd_controle;
        tmp.byte_controle_anterior = cmd_controle;
        ui_api_debug("+[CTL][MQ] : Comando UI_Null - MQ verificar_autenticacao_Controler Resetada");
        break;
    default:
        break;
    }
    return &tmp;
}
///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\


uint8_t verificarFilas(st_ui_image* val, st_ui_aut *val2,st_ui_conexao *val3,  uint8_t thread)
{
    st_ui_image tmp,tmpg;
    st_ui_aut tmp2,tmp2g;
    st_ui_conexao tmp3,tmp3g;
    if (thread == UI__CTL) {
        if (!fila_imagem_Controler.empty())
        {
            tmp = fila_imagem_Controler.front();
            memcpy(val, &tmp, sizeof(st_ui_image));
            fila_imagem_Controler.pop();
            return RP_fila_imagem;
        }
        if (!fila_transf_imagem_Controler.empty())
        {
            tmp = fila_transf_imagem_Controler.front();
            memcpy(val, &tmp, sizeof(st_ui_image));
            fila_transf_imagem_Controler.pop();
            return RP_fila_transf_imagem;
        }
        if (!fila_autent_Controler.empty())
        {
            tmp2 = fila_autent_Controler.front();
            memcpy(val2, &tmp2, sizeof(st_ui_aut));
            fila_autent_Controler.pop();
            return RP_fila_autenticacao;
        }
        if(!fila_conexao_Controler.empty())
        {
            tmp3 = fila_conexao_Controler.front();
            memcpy(val3, &tmp3, sizeof(st_ui_conexao));
            fila_conexao_Controler.pop();
            return RP_fila_conexao;
        }
    }
    else
    {
        if (!fila_imagem_GUI.empty())
        {
            tmpg = fila_imagem_GUI.front();
            memcpy(val, &tmpg, sizeof(st_ui_image));
            fila_imagem_GUI.pop();
            return RP_fila_imagem;
        }
        if (!fila_transf_imagem_GUI.empty())
        {
            tmpg = fila_transf_imagem_GUI.front();
            memcpy(val, &tmpg, sizeof(st_ui_image));
            fila_transf_imagem_GUI.pop();
            return RP_fila_transf_imagem;
        }
        if (!fila_autent_GUI.empty())
        {
            tmp2g = fila_autent_GUI.front();
            memcpy(val2, &tmp2g, sizeof(st_ui_aut));
            fila_autent_GUI.pop();
            return RP_fila_autenticacao;
        }
        if(!fila_conexao_GUI.empty())
        {
            tmp3g = fila_conexao_GUI.front();
            memcpy(val3, &tmp3g, sizeof(st_ui_conexao));
            fila_conexao_GUI.pop();
            return RP_fila_conexao;
        }
    }

    return 0;
}

///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\


int ui_api_debug(string txt)
{
#ifdef DEBUG_UI_API
    pthread_mutex_lock(&lock_print);
    std::cout  << txt << endl;
    pthread_mutex_unlock(&lock_print);
#else

#endif
    return 1;

}
