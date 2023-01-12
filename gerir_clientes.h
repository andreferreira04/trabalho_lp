#ifndef GERIR_CLIENTES_H
#define GERIR_CLIENTES_H

#define MAX_NOME_CLIENTE 30
#define MAX_PAIS 20
#define MAX_MORADA 100
#define SEPARADOR "-----------------------------------\n"
#define VALOR_INVALIDO "Valor invalido"
#define MAX_NIF 1000000000
#define MIN_NIF 99999999
#define MAX_TELEMOVEL 1000000000
#define MIN_TELEMOVEL 99999999

typedef struct cliente {
    int nif, codigoCliente, telemovel;
    char nome [MAX_NOME_CLIENTE];
    char pais [MAX_PAIS];
    char morada [MAX_MORADA];
}dadosPessoais;

//dadosPessoais cliente[100];
    
    
void apagarDadosCliente();
int procurarCliente();
int criarCliente();
void editarCliente();
void removerCliente();

#endif
