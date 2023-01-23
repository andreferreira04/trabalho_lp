/*
 * @file gerir_clientes.h
 * @author André Ferreira, Paulo Coelho, Tiago Coelho
 * @date 23 Janeiro 2023
 * 
*/

#ifndef GERIR_CLIENTES_H
#define GERIR_CLIENTES_H

#include "gerir_produtos.h"

#define ERRO_CLIENTE_NAO_EXISTE   "O cliente não existe na lista."
#define ERRO_CLIENTE_JA_EXISTE "O clinte já existe na lista."
#define PRINTF_EDIT_CLIENTE "Escreva o ID do cliente que deseja editar. Escreva '0' para sair.\n"
#define PRINTF_REM_CLIENTE "Escreva o ID do cliente que deseja remover. Escreva '0' para sair.\n"

#define MAX_CLIENTES 100

#define MAX_NOME_CLIENTE 60
#define MSG_OBTER_NOME "Insira o nome do cliente: "

#define MAX_PAIS 20
#define MSG_OBTER_PAIS "Insira o pais: "

#define MAX_MORADA 100
#define MSG_OBTER_MORADA "Insira a morada: "

#define MSG_OBTER_NIF "Insira o nif: "
#define MAX_NIF 1000000000
#define MIN_NIF 99999999

#define MSG_OBTER_TELEMOVEL "Insira o numero de telemovel"
#define MAX_TELEMOVEL 1000000000
#define MIN_TELEMOVEL 99999999

#define MSG_OBTER_ID "Insira o codigo de cliente: "
#define MAX_ID_CLIENTE 7


#define SEPARADOR "-----------------------------------\n"
#define VALOR_INVALIDO "Valor invalido"

typedef struct cliente {
    char idCliente[MAX_ID_CLIENTE]; 
    int nif;
    char nome[MAX_NOME_CLIENTE];
    int telemovel;
    char pais[MAX_PAIS];
    char morada[MAX_MORADA];
    int estado;
} DadosPessoais;

typedef struct {
    int numClientes;
    DadosPessoais cliente[MAX_CLIENTES];
} Clientes;

int procurarCliente(char *idCliente, Clientes clientes);
int obterPosicaoCliente(char *idCliente, Clientes clientes);

void reallocClientes(Clientes *clientes);

void listarCliente(DadosPessoais cliente);
void listarClientes(Clientes clientes);

void criarCliente(Clientes *clientes);
void apagarDadosCliente(DadosPessoais *cliente);

void removerCliente(Clientes *clientes, Encomendas encomendas);
void editarCliente(Clientes *clientes);

void loadClientes(Clientes *clientes);

void uploadClientes(Clientes *clientes);

#endif /* GERIR_CLIENTES_H */
