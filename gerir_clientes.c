#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "input.h"
#include "gerir_clientes.h"
#include "gerir_produtos.h"

/**
 * Esta função procura se um certo cliente existe
 * 
 * @param idCliente ID do cliente a procurar
 * @param clientes struct Clientes a procurar
 * @return 1 se o cliente existe, 0 se nao existe
 */
int procurarCliente(char *idCliente, Clientes clientes) {
    for (int i = 0; i < clientes.numClientes; i++) {
        if (strcmp(clientes.cliente[i].idCliente, idCliente) == 0 && clientes.cliente[i].estado == 1) {
            return 1;
        }
    }
    return 0;
}

/**
 * Esta função retorna a posicao de um certo cliente
 * 
 * @param idCliente ID do cliente a procurar
 * @param clientes struct Clientes a procurar
 * @return a posicao do cliente, se nao existe retorna -1
 */
int obterPosicaoCliente(char *idCliente, Clientes clientes) {
    for (int i = 0; i < clientes.numClientes; i++) {
        if (strcmp(clientes.cliente[i].idCliente, idCliente) == 0 && clientes.cliente[i].estado == 1) {
            return i;
        }
    }
    return -1;
}



/**
 * A função recebe um dado do tipo Cliente e lista as suas informações
 * 
 * @param cliente Cliente a exibir
 */
void listarCliente(DadosPessoais cliente) {
  if(cliente.estado ==1)
    printf("\n\tID:%s \n\tNIF:%d \n\tNome:%s \n\tTelemovel:%d\n\tMorada:%s\n\tPais:%s\n", cliente.idCliente, cliente.nif, cliente.nome, cliente.telemovel, cliente.morada, cliente.pais);
  }
}

/**
 * A função lista todos os elementos de uma estrutura de dados do tipo Clientes
 * 
 * @param clientes clientes a exibir
 */
void listarClientes(Clientes clientes) {
    if (clientes.numClientes > 0) {
        for (int i = 0; i < clientes.numClientes; i++) {
            listarCliente(clientes.cliente[i]);
        }
    } else {
        puts("Nao existem clientes");
    }
}

/**
 * 
 * @param produtos apontador da estrtura de dados Clientes
 * @param encomendas estrutura do tipo Encomendas
 */
void removerCliente(Clientes *clientes, Encomendas encomendas) {
    char idCliente[MAX_ID_CLIENTE];

    listarClientes(*clientes);
    printf(PRINTF_REM_CLIENTE);

    lerString(idCliente, MAX_ID_CLIENTE, "");

    if (idCliente[0] != '0') {
        //converter para maiusculas
        for (int i = 0; idCliente[i] != '\0'; i++)
            idCliente[i] = toupper(idCliente[i]);

        if (procurarCliente(idCliente, *clientes) == 1) { // se o cliente existir
            int pos = obterPosicaoCliente(idCliente, *clientes);
            if (procurarEncomenda(idCliente, encomendas) == 0) { // se nao tiver encomendas, remover
            for (int i = pos; i < clientes->numClientes - 1; i++) {
                clientes->cliente[i] = clientes->cliente[i + 1];
            }
            clientes->numClientes--;
        }
            else { //se tiver encomendas, mudar para inativo
                clientes->cliente[pos].estado = 0;
            }
        }
        else {
            printf("Nao e possivel remover");
        }
    }
}

/**
 * Esta função permite ao utilizador editar informações de um cliente
 * 
 * @param clientes apontador do tipo Clientes
 */
void editarCliente(Clientes *clientes) {

    char idCliente[MAX_ID_CLIENTE], nome[MAX_NOME_CLIENTE], morada[MAX_MORADA], pais[MAX_PAIS];

    listarClientes(*clientes);
    printf(PRINTF_EDIT_CLIENTE);

    lerString(idCliente, MAX_ID_CLIENTE, "");

    if (procurarCliente(idCliente, *clientes) == 1) { // se o cliente existir
        int pos = obterPosicaoCliente(idCliente, *clientes);

        clientes->cliente[pos].nif = obterInt(MSG_OBTER_NIF, MIN_NIF, MAX_NIF);
        lerString(nome, MAX_NOME_CLIENTE, MSG_OBTER_NOME);
        clientes->cliente[pos].telemovel = obterInt(MSG_OBTER_TELEMOVEL, MIN_TELEMOVEL, MAX_TELEMOVEL);
        lerString(morada, MAX_MORADA, MSG_OBTER_MORADA);
        lerString(pais, MAX_PAIS, MSG_OBTER_PAIS);

        strcpy(clientes->cliente[pos].nome, nome);
        strcpy(clientes->cliente[pos].morada, morada);
        strcpy(clientes->cliente[pos].pais, pais);

    } else {
        printf("Nao e possivel editar");
    }
}

/**
 * Esta função permite carregar dados do ficheiro "clientes.txt" para uma struct do tipo Clientes
 * 
 * @param clientes apontador do tipo Clientes
 */
void loadClientes(Clientes *clientes) {
    int i = 0, count = 0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("clientes.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        char *delim = ";";
        char *token = strtok(line, delim);
        i = 0;

        while (token != NULL) {
            switch (i) {
                case 0: strncpy(clientes->cliente[count].idCliente, token, 7);
                case 1: clientes->cliente[count].nif = atoi(token);
                case 2: strncpy(clientes->cliente[count].nome, token, 60);
                case 3: clientes->cliente[count].telemovel = atoi(token);
                case 4: strncpy(clientes->cliente[count].morada, token, 100);
                case 5: strncpy(clientes->cliente[count].pais, token, 20);
                case 6: clientes->cliente[count].estado = atoi(token);
            }
            token = strtok(NULL, delim);
            i++;
        }
        count++;
    }
    clientes->numClientes = count;

    fclose(fp);
}

/**
 * A função permite ao utilizador fazer upload dos dados da struct do tipo Clientes para o ficheiro "clientes.txt"
 * 
 * @param clientes apontador do tipo Clientes
 */
void uploadClientes(Clientes *clientes) {
    FILE *clientes_file = fopen("clientes.txt", "w");

    if (clientes_file == NULL) {
        printf("Erro a abrir o ficheiro.\n");
        return;
    }

    for (int i = 0; i < clientes->numClientes; i++) {
        fprintf(clientes_file, "%s;%d;%s;%d;%s;%s;%d\n", clientes->cliente[i].idCliente, clientes->cliente[i].nif, clientes->cliente[i].nome, clientes->cliente[i].telemovel, clientes->cliente[i].morada, clientes->cliente[i].pais, clientes->cliente[i].estado);
    }
    fclose(clientes_file);
}

