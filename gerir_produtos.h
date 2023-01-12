/*
 * @file gerir_produtos.h
 * @author André Ferreira, Paulo Coelho, Tiago Coelho
 * @date 12 Janeiro 2023
 * 
*/

#ifndef GERIR_PRODUTOS_H
#define GERIR_PRODUTOS_H

#define MAX_PRODUTOS 30
#define MAX_ENCOMENDAS 30
#define NUM_MATERIAIS 20

#define ERRO_PRODUTO_NAO_EXISTE "O produto nao existe!"
#define PRINTF_REG_ENCOMENDA "Escreva os ID´s dos produtos. Digite '0' para terminar.\n"
#define PRINTF_REM_PRODUTO "Escreva o ID do produto que deseja remover. Escreva '0' para sair.\n"
#define TAM_IDPRODUTO 7
#define TAM_MATERIAL 7
#define DELIMITADOR ";"


typedef struct {
    char codMaterial[7];
    char descricao[30];
    int quantidade;
    char unidade[5];
} Material;

typedef struct {
    char idProduto[7];
    char nomeProduto[30];
    char dimensoesProduto[20];
    int precoProduto;
    int estado; // 0 - inativo, 1 - ativo
    char materiais[NUM_MATERIAIS][TAM_MATERIAL];
    int numMateriais;
} Produto;

typedef struct {
    int numProdutos;
    Produto produto[MAX_PRODUTOS];
} Produtos;

typedef struct {
    int idCliente;
    char idProduto[7];
    char data[10];
} Encomenda;

typedef struct {
    int numEncomendas;
    Encomenda encomenda[MAX_ENCOMENDAS];
} Encomendas;


int procurarProduto(char *idProduto, Produtos produtos);
int obterPosicaoProduto(char *idProduto, Produtos produtos);
int procurarEncomenda(char *idProduto, Encomendas encomendas);

void listarProduto(Produto produto);
void listarProdutos(Produtos produtos);

void removerProduto(Produtos *produtos, Encomendas encomendas);
void editarProduto(Produtos *produtos);

void loadProdutos(Produtos *produtos);
void loadEncomendas(Encomendas *encomendas);

void uploadProdutos(Produtos *produtos);
void uploadEncomendas(Encomendas *encomendas);

void registarEncomenda(Produtos produtos, Encomendas encomendas);

void importExcel(Produtos *produtos, Material *material);

#endif /* GERIR_PRODUTOS_H */