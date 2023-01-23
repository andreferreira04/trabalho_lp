/*
 * @file gerir_produtos.h
 * @author André Ferreira, Paulo Coelho, Tiago Coelho
 * @date 23 Janeiro 2023
 * 
*/

#ifndef GERIR_PRODUTOS_H
#define GERIR_PRODUTOS_H

#define NUM_PRODUTOS 2
#define NUM_ENCOMENDAS 2
#define NUM_MATERIAIS 30

#define ERRO_PRODUTO_NAO_EXISTE "O produto nao existe!"
#define PRINTF_REG_ENCOMENDA "Escreva os ID´s dos produtos. Digite '0' para terminar.\n"
#define PRINTF_REM_PRODUTO "Escreva o ID do produto que deseja remover. Escreva '0' para sair.\n"
#define TAM_IDPRODUTO 7
#define TAM_IDCLIENTE 8
#define TAM_MATERIAL 7
#define DELIMITADOR ";"

struct date {
    int dd, mm, yy;
};

typedef struct {
    char codMaterial[TAM_MATERIAL];
    char descricao[255];
} Material;

typedef struct {
    int numMateriais;
    Material material[NUM_MATERIAIS];
} Materiais;

typedef struct {
    char idProduto[TAM_IDPRODUTO];
    char nomeProduto[255];
    char dimensoesProduto[255];
    int precoProduto;
    int estado; // 0 - inativo, 1 - ativo
    char materiais[NUM_MATERIAIS][TAM_MATERIAL];
    int quantidades[NUM_MATERIAIS];
    char unidades[NUM_MATERIAIS];
    int numMateriais;
} Produto;

typedef struct {
    int numProdutos;
    Produto *produto;
} Produtos;

typedef struct {
    char idCliente[TAM_IDCLIENTE];
    char idProduto[TAM_IDPRODUTO];
    char data[10];
} Encomenda;

typedef struct {
    int numEncomendas;
    Encomenda *encomenda;
} Encomendas;


int procurarProduto(char *idProduto, Produtos produtos);
int obterPosicaoProduto(char *idProduto, Produtos produtos);
int procurarEncomenda(char *idProduto, Encomendas encomendas);
int procurarMaterial(char *codMaterial, Materiais materiais);
int obterPosicaoMaterial(char *codMaterial, Materiais materiais);

void reallocProdutos(Produtos *produtos);
void reallocEncomendas(Encomendas *encomendas);

void listarProduto(Produto produto);
void listarProdutos(Produtos produtos);

void removerProduto(Produtos *produtos, Encomendas encomendas);
void editarProduto(Produtos *produtos);

void loadProdutos(Produtos *produtos);
void loadEncomendas(Encomendas *encomendas);

void uploadProdutos(Produtos *produtos);
void uploadEncomendas(Encomendas *encomendas);

void registarEncomenda(Produtos produtos, Encomendas *encomendas);

void importExcel(Produtos *produtos, Materiais *materiais);

#endif /* GERIR_PRODUTOS_H */
