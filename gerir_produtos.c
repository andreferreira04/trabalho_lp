#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "input.h"
#include "gerir_produtos.h"
#include "gerir_clientes.h"

extern int tam_struct_produtos;
extern int tam_struct_encomendas;
extern Clientes clientes;

/**
 * Esta função procura se um certo produto existe
 * 
 * @param idProduto ID do produto a procurar
 * @param produtos struct Produtos a procurar
 * @return 1 se o produto existe, 0 se nao existe
 */
int procurarProduto(char *idProduto, Produtos produtos) {
    for (int i = 0; i < produtos.numProdutos; i++) {
        if (strcmp(produtos.produto[i].idProduto, idProduto) == 0 && produtos.produto[i].estado == 1) { //encontrou um produto ativo
            return 1;
        }
    }
    return 0;
}

/**
 * Esta função retorna a posicao de um certo produto
 * 
 * @param idProduto o ID do produto a procurar
 * @param produtos struct Produtos a procurar
 * @return a posicao do produto, se nao existe retorna -1
 */
int obterPosicaoProduto(char *idProduto, Produtos produtos) {
    for (int i = 0; i < produtos.numProdutos; i++) {
        if (strcmp(produtos.produto[i].idProduto, idProduto) == 0 && produtos.produto[i].estado == 1) { //encontrou um produto ativo
            return i;
        }
    }
    return -1;
}

/**
 * Esta função procura se um certo produto tem encomendas associadas
 * 
 * @param idProduto ID do produto a procurar
 * @param encomendas struct Encomendas a procurar
 * @return 1 se o produto tem encomendas, 0 se nao tem
 */
int procurarEncomenda(char *idProduto, Encomendas encomendas) {
    for (int i = 0; i < encomendas.numEncomendas; i++) {
        if (strcmp(encomendas.encomenda[i].idProduto, idProduto) == 0) { //encontrou
            return 1;
        }
    }
    return 0;
}

int procurarMaterial(char *codMaterial, Materiais materiais) {
    for (int i = 0; i < materiais.numMateriais; i++) {
        if (strcmp(materiais.material[i].codMaterial, codMaterial) == 0) { //encontrou um material
            return 1;
        }
    }
    return 0;
}

int obterPosicaoMaterial(char *codMaterial, Materiais materiais) {
    for (int i = 0; i < materiais.numMateriais; i++) {
        if (strcmp(materiais.material[i].codMaterial, codMaterial) == 0) { //encontrou um material
            return i;
        }
    }
    return -1;
}


void reallocProdutos(Produtos *produtos) {
    tam_struct_produtos = produtos->numProdutos + NUM_PRODUTOS;
    produtos->produto = (Produto*) realloc(produtos->produto, tam_struct_produtos * sizeof(Produto));
}

void reallocEncomendas(Encomendas *encomendas) {
    tam_struct_encomendas = encomendas->numEncomendas + NUM_ENCOMENDAS;
    encomendas->encomenda = (Encomenda*) realloc(encomendas->encomenda, tam_struct_encomendas * sizeof(Encomenda));
}



/**
 * A função recebe um dado do tipo Produto e lista as suas informações
 * 
 * @param produto Produto a exibir
 */
void listarProduto (Produto produto) {
    if (produto.estado == 1) {
        printf("%s: \n\tNome: %s \n\tDimensoes: %s \n\tPreco: %d\n", produto.idProduto, produto.nomeProduto, produto.dimensoesProduto, produto.precoProduto);
        printf("\tMateriais: ");
        for (int i = 0; i < produto.numMateriais; i++) {
            printf("%s ) ", produto.materiais[i];
        }
        printf("\n\n");
    }
}

/**
 * A função lista todos os elementos de uma estrutura de dados do tipo Produtos
 * 
 * @param produtos produtos a exibir
 */
void listarProdutos (Produtos produtos) {
    if (produtos.numProdutos > 0) {
        for (int i = 0; i < produtos.numProdutos; i++) {
            listarProduto(produtos.produto[i]);
        }
    } else {
        puts("Nao existem produtos");
    }
}

/**
 * 
 * @param produtos apontador da estrtura de dados Produtos
 * @param encomendas estrutura do tipo Encomendas
 */
void removerProduto(Produtos *produtos, Encomendas encomendas) {
    char idProduto[TAM_IDPRODUTO];
    
    listarProdutos(*produtos);
    printf(PRINTF_REM_PRODUTO);
    
    lerString(idProduto, TAM_IDPRODUTO, "");
    
    if (idProduto[0] != '0') {
        //converter para maiusculas
        for (int i = 0; idProduto[i] != '\0'; i++)
            idProduto[i] = toupper(idProduto[i]);
        
        if (procurarProduto(idProduto, *produtos) == 1) { // se o produto existir
            int pos = obterPosicaoProduto(idProduto, *produtos);
            if (procurarEncomenda(idProduto, encomendas) == 0) { // se nao tiver encomendas, remover
                for (int i = pos; i < produtos->numProdutos - 1; i++) {
                    produtos->produto[i] = produtos->produto[i + 1];
                }
                produtos->numProdutos--;
            }
            else { //se tiver encomendas, mudar para inativo
                produtos->produto[pos].estado = 0;
            }
        }
        else {
            printf("Nao e possivel remover");
        }
    }
}
/**
 * Esta função permite ao utilizador editar informações de um produto
 * 
 * @param produtos apontador do tipo Produtos
 */
void editarProduto(Produtos *produtos) {
    char tmpstr[4], print_opcao[] = "Escolha uma opcao (1 - ", nomeProduto[30], dimensoesProduto[30];
    listarProdutos(*produtos);
    
    sprintf(tmpstr, "%d", produtos->numProdutos);
    strlcat(print_opcao, tmpstr, 30);
    strlcat(print_opcao, ") (Escreva '0' para sair): ", 60);
        
    int opcao = obterInt(print_opcao, 0, produtos->numProdutos) - 1;
    
    if (opcao == -1) return;
    
    lerString(nomeProduto, 30, "Nome do produto: ");
    lerString(dimensoesProduto, 30, "Dimensoes do produto: ");
    produtos->produto[opcao].precoProduto = obterInt("Preco do produto: ", 0, 999999);
    
    strcpy(produtos->produto[opcao].nomeProduto, nomeProduto);
    strcpy(produtos->produto[opcao].dimensoesProduto, dimensoesProduto);
}

/**
 * Esta função permite carregar dados do ficheiro "produtos.txt" para uma struct do tipo Produtos
 * 
 * @param produtos apontador do tipo Produtos
 */
void loadProdutos (Produtos *produtos) {
    int i = 0, count = 0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("produtos.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        char *delim = DELIMITADOR;
        char *token = strtok(line, delim);
        i = 0;
        
        while(token != NULL) {
            switch (i) {
                case 0: strncpy(produtos->produto[count].idProduto, token, 20);
                case 1: strncpy(produtos->produto[count].nomeProduto, token, 20);
                case 2: strncpy(produtos->produto[count].dimensoesProduto, token, 20);
                case 3: produtos->produto[count].precoProduto = atoi(token);
                case 4: produtos->produto[count].estado = atoi(token);
            }
            token = strtok(NULL, delim);
            i++;
        }
        count++;
        
        if (count == tam_struct_produtos) {
            reallocProdutos(produtos);
        }
    }
    produtos->numProdutos = count;

    fclose(fp);
}

/**
 * Esta função permite carregar dados do ficheiro "encomendas.txt" para uma struct do tipo Encomendas
 * 
 * @param encomendas apontador do tipo Encomendas
 */
void loadEncomendas (Encomendas *encomendas) {
    int param = 0, count = 0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("encomendas.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        param = 0;
        char *delim = DELIMITADOR;
        char *token = strtok(line,delim);
        while (token != NULL) {
            switch (param) {
                case 0: 
                    strlcpy(encomendas->encomenda[count].idCliente, token, TAM_IDCLIENTE);
                    break;
                case 1:
                    strlcpy(encomendas->encomenda[count].idProduto, token, TAM_IDPRODUTO);
                    break;
                case 2:
                    strlcpy(encomendas->encomenda[count].data, token, 10);
                    break;
            }
            param++;
            token = strtok(NULL, delim);
        }
        count++;
        encomendas->numEncomendas = count;
            
        if (count == tam_struct_encomendas) {
            reallocEncomendas(encomendas);
        }
    }
    encomendas->numEncomendas = count;

    fclose(fp);
}

/**
 * A função permite ao utilizador fazer upload dos dados da struct do tipo Produtos para o ficheiro "produtos.txt"
 * 
 * @param produtos apontador do tipo Produtos
 */
void uploadProdutos (Produtos *produtos) {
    FILE *produtos_file = fopen("produtos.txt", "w");

    if (produtos_file == NULL) {
        printf("Erro a abrir o ficheiro.\n");
        return;
    }

    for (int i = 0; i < produtos->numProdutos; i++) {
        fprintf(produtos_file, "%s;%s;%s;%d;%d\n", produtos->produto[i].idProduto, produtos->produto[i].nomeProduto, produtos->produto[i].dimensoesProduto, produtos->produto[i].precoProduto, produtos->produto[i].estado);
    }
    fclose(produtos_file);
}

/**
 * A função permite ao utilizador fazer upload dos dados da struct do tipo Encomendas para o ficheiro "encomendas.txt"
 * 
 * @param produtos apontador do tipo Encomendas
 */
void uploadEncomendas (Encomendas *encomendas) {
    FILE *encomendas_file = fopen("encomendas.txt", "w");

    if (encomendas_file == NULL) {
        printf("Erro a abrir o ficheiro.\n");
        return;
    }
    for (int i = 0; i < encomendas->numEncomendas; i++) {
        fprintf(encomendas_file, "%s;%s;%s\n", encomendas->encomenda[i].idCliente, encomendas->encomenda[i].idProduto, encomendas->encomenda[i].data);
    }
    fclose(encomendas_file);
}

/**
 * A função permite registar uma encomenda
 * 
 * @param produtos struct do tipo de dados Produtos para listar os produtos disponiveis
 * @param encomendas struct do tipo de dados Encomendas para registar a encomenda
 */
void registarEncomenda (Produtos produtos, Encomendas *encomendas) {    
    int dd, mm, yy;
    char idProduto[TAM_IDPRODUTO], idCliente[TAM_IDCLIENTE];
    
    
    do {
        lerString(idCliente, TAM_IDCLIENTE, "Escreva o ID do cliente: ");
    } while (procurarCliente(idCliente, clientes) != 1);
    

    do {
        printf("Escreva a data da encomenda (DD/MM/AAAA):");
        scanf("%d/%d/%d", &dd, &mm, &yy);
    } while (!verificaData(dd, mm, yy));
    

    listarProdutos(produtos);
    
    //ler os produtos
    printf(PRINTF_REG_ENCOMENDA);
    do {
        lerString(idProduto, TAM_IDPRODUTO, "");
        
        if (idProduto[0] != '0') {
            //converter para maiusculas
            for (int i = 0; idProduto[i] != '\0'; i++)
                idProduto[i] = toupper(idProduto[i]);
            
            //se o produto existir
            if (procurarProduto(idProduto, produtos) == 1) {                
                char data[10];
                
                sprintf(data, "%d/%d/%d", dd,mm,yy);
                
                
                if (encomendas->numEncomendas == tam_struct_encomendas) {
                    reallocEncomendas(encomendas);
                }
                
                strlcpy(encomendas->encomenda[encomendas->numEncomendas].idCliente, idCliente, TAM_IDCLIENTE);
                strlcpy(encomendas->encomenda[encomendas->numEncomendas].idProduto, idProduto, TAM_IDPRODUTO);
                strlcpy(encomendas->encomenda[encomendas->numEncomendas].data, data, 10);
                
                encomendas->numEncomendas++;
            }
        }
    } while (idProduto[0] != '0');
}

/**
 * Função que permite importar dados de um ficheiro do tipo .csv
 * 
 * @param produtos apontador para a struct do tipo Produtos
 * @param materiais apontador para a struct do tipo Materiais
 */
void importExcel(Produtos *produtos, Materiais *materiais) {
    FILE *fp;
    int i, count_materiais = 0, count_produtos = 0, num_materiais = 0;
    char * line = NULL, procurarCod[TAM_MATERIAL];
    size_t len = 0;
    ssize_t read;
    
    fp = fopen( "tabela.csv", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        char *delim = DELIMITADOR;
        char *token = strtok(line,delim);
        i = 0;
        
        if (line[0] == 'P') {
            count_materiais = 0;
            
            produtos->produto[count_produtos].estado = 1;
            while(token != NULL) {
                switch (i) {
                    case 0: 
                        strncpy(produtos->produto[count_produtos].idProduto, token, 20);
                        break;
                    case 1: 
                        strncpy(produtos->produto[count_produtos].nomeProduto, token, 20);
                        break;
                    case 2: 
                        strncpy(produtos->produto[count_produtos].dimensoesProduto, token, 20);
                        break;
                    case 3: 
                        produtos->produto[count_produtos].precoProduto = atoi(token);
                        break;
                    case 4:
                        strcpy(procurarCod, token);
                        strncpy(produtos->produto[count_produtos].materiais[count_materiais], token, 20);
                        if (procurarMaterial(procurarCod, *materiais) == 0) { // se noa encontrar, adicionar
                            strncpy(materiais->material[num_materiais].codMaterial, token, 20);
                            num_materiais++;
                        }
                        break;
                    case 5:
                        if (procurarMaterial(procurarCod, *materiais) == 0)
                            strncpy(materiais->material[num_materiais-1].descricao, token, 20);
                        break;
                    case 6:
                        produtos->produto[count_produtos].quantidades[count_materiais] = atoi(token);
                        break;
                    case 7:
                        produtos->produto[count_produtos].unidades[count_materiais] = token[0];
                        break;
                }
                token = strtok(NULL, delim);
                i++;
            }
            count_produtos++;
            count_materiais++;
            produtos->numProdutos = count_produtos;
            produtos->produto[count_produtos-1].numMateriais = count_materiais;
            materiais->numMateriais = num_materiais;
                 
            if (count_produtos == tam_struct_produtos) {
                reallocProdutos(produtos);
            }
        }
        
        else if (line[4] == 'M') {
            while(token != NULL) {
                switch (i) {
                    case 0:
                        strcpy(procurarCod, token);
                        strncpy(produtos->produto[count_produtos-1].materiais[count_materiais], token, 20);
                        if (procurarMaterial(procurarCod, *materiais) == 0) {
                            strncpy(materiais->material[num_materiais].codMaterial, token, 20);
                            num_materiais++;
                        }
                        break;
                    case 1:
                        if (procurarMaterial(procurarCod, *materiais) == 0)
                            strncpy(materiais->material[num_materiais-1].descricao, token, 20);
                        break;
                    case 2:
                        produtos->produto[count_produtos-1].quantidades[count_materiais] = atoi(token);
                        break;
                    case 3:
                        produtos->produto[count_produtos-1].unidades[count_materiais] = token[0];
                        break;
                }
                token = strtok(NULL, delim);
                i++;
            }
            count_materiais++;
            produtos->produto[count_produtos-1].numMateriais = count_materiais;
        }
    }
    produtos->numProdutos = count_produtos;
    materiais->numMateriais = num_materiais;
    fclose(fp);
}
