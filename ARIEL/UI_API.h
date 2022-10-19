#pragma once
#include <stdio.h>
//#include <cstdint>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <string>		// Necessário para usar strings
#include "regex"
#define PORT 8080

#define TAM_DIR 100 // Tamanho máximo do diretório
#define TIMER_THREAD 500 // 500 ms
#define TAM_LOG 20

#define DEBUG_UI_API
#define UI__GUI 1
#define UI__CTL 0
using namespace std;
enum UI_RESP {
	RP_fila_imagem = 1,
	RP_fila_transf_imagem = 2,
	RP_fila_autenticacao = 3,
    RP_fila_conexao = 4,
};
enum  UI_INTERFACE {

	UI_Falha = 4,
	UI_Ok = 1,
	UI_Timeout = 2,
	UI_Aguardar = 3,
	UI_Null = 0,
    //Imagem
    UI_Iniciar_Transferencia = 5,    // INICIAR A TRANSFERENCIA DO ARQUIVO SELECIONADO
	UI_Andamento_Transferencia = 6,
	UI_Cancelar = 7,
	UI_Fim_Transferencia = 8,
    UI_Carregar_Imagem = 9,         // ENVIAR DO PEN-DRIVE PARA A PASTA DE IMAGENS
    UI_Informacoes_Imagem = 10,     // LISTAR IMAGENS DENTRO DO PROJETO
    UI_Apagar_Aquivo,               // APAGAR A IMAGEM DENTRO DO PROJETO
    //Autenticacao
	UI_EnviarLogin = 11,
    UI_Cadastrar = 12,
    UI_RemoverUsuario = 13,
    //Conexao
    UI_ListarConexoes = 14,
    UI_EstabelecerConexao = 15,
    UI_EncerrarConexao = 16,
	//
	UI_TOT_ESTADOS,
};
///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\

// Estrutura destinada à informações sobre o Diretório
typedef struct st_dir_img {
    char *diretorio_img;
    uint16_t tam_dir;
}st_dir_img;

// Estrutura destinada ao campo de informações da imagem
typedef struct st_info_img {


}st_info_img;

// Estrutura Das informações sobre a Imagem
typedef struct st_ui_image {

	uint8_t byte_controle;
	uint8_t byte_controle_anterior;
	st_dir_img dir_img;
	uint16_t status_transferencia;
	st_info_img img_info;

}st_ui_image;

///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\

// Estrutura Das informações sobre a conexao
typedef struct st_info_conexao {
	

}st_info_conexao_ty;
// Estrutura Geral da Conexao
typedef struct st_ui_conexao {

    uint8_t byte_controle;
    uint8_t byte_controle_anterior;
	st_info_conexao info_conexao;
}st_ui_conexao;

///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\

// Estrutura Das informações sobre a autenticação
typedef struct st_info_aut {
	//hash, senha, etc
	uint8_t login[32];
	uint8_t senha[32];
}st_info_aut;
// Estrutura Geral da Autenticação
typedef struct st_ui_aut {
	uint8_t byte_controle;
	uint8_t byte_controle_anterior;
	st_info_aut autenticao;
}st_ui_aut;

///\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\  //\\ 
///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\///\\\


//Funções referentes a Imagem
st_ui_image* carregar_imagem_GUI(uint8_t cmd_controle, st_ui_image* val);
st_ui_image* carregar_imagem_Controler(uint8_t cmd_controle, st_ui_image* val);

st_ui_image* transferir_imagem_GUI(uint8_t cmd_controle, st_ui_image* val);
st_ui_image* transferir_imagem_Controler(uint8_t cmd_controle, st_ui_image* val);

//Funções referentes a Conexão
st_ui_conexao* conexoes_GUI(uint8_t cmd_controle, st_ui_conexao* val);
st_ui_conexao* conexoes_Controler(uint8_t cmd_controle, st_ui_conexao* val);
//Funções referentes a Autenticação
st_ui_aut* verificar_autenticacao_GUI(uint8_t cmd_controle, st_ui_aut* val);
st_ui_aut* verificar_autenticacao_Controler(uint8_t cmd_controle, st_ui_aut* val);

//
int iniciar_UI_interface(st_ui_image* val, st_ui_aut* val2,st_ui_conexao *val3, uint8_t thread);
uint8_t verificarFilas(st_ui_image* val, st_ui_aut* val2,st_ui_conexao *val3, uint8_t thread);
//DEBUG

int ui_api_debug(string txt);
