#include <stdio.h>
#include <stdlib.h>

#include "gerir_clientes.h"
#include "gerir_produtos.h"
#include "gerir_producao.h"
#include "menus.h"
#include "input.h"
#include "tools.h"

#define EMPRESA_MSG "----- MOVEIS PARA TODOS -----"
#define MENU_PRINCIPAL_MSG "\nSelecione o seu tipo de  perfil\n----------\n1.Administrador\n2.Cliente\n"\
                           "0.Sair\n"
#define MENU_ADMIN_MSG "----------\nMenu do Administrador\n----------\n1.Gestao de clientes\n"\
                       "2.Gestao de produtos\n3.Gestao de producao\n0.Sair\nSelecione uma opcao (0-3):"
#define MENU_CLIENTE_MSG "----------\nMenu do cliente\n----------\n1.Registar encomenda\n0.Sair\n"\
                         "Selecione uma opcao (0-1):"
#define MENU_GERIR_CLIENTES_MSG "----------\nGestao de clientes\n----------\n1.Criar cliente\n"\
                                "2.Editar cliente\n3.Remover cliente\n4.Guardar alteracoes\n0.Sair\n"\
                                "Selecione uma opcao (0-4):"
#define MENU_GERIR_PRODUTOS_MSG "----------\nGestao de produtos\n----------\n1.Editar produto\n"\
                                "2.Remover produto\n3.Guardar alteracoes\n0.Sair\nSelecione uma opcao (0-3):"
#define MENU_GERIR_PRODUCAO_MSG "----------\nGestao da producao\n----------\n1.Obter lista de componentes"\
                                " de encomendas (por semana)\n2.Obter lista dos produtos mais vendidos\n3.Obter lista de clientes mais ativos"\
                                "4.Obter lista do retorno financeiro(mes a mes)\n5.Obter lista de vendas conseguidas (por mes)\n0.Sair\nSelecione uma opcao (0-2):"
#define MENU_MSG_INVALIDA "Insira uma opcao valida!"


int tam_struct_produtos = NUM_PRODUTOS;
int tam_struct_encomendas = NUM_ENCOMENDAS;
int tam_struct_materiais = NUM_MATERIAIS;
int tam_struct_clientes = MAX_CLIENTES;

Produtos produtos = {};
Encomendas encomendas = {};
Materiais materiais = {};
Clientes clientes = {};

void menuCliente() {
    switch (obterInt(MENU_CLIENTE_MSG, 0, 1)) {
        case 1:
            registarEncomenda(produtos, &encomendas);
            break;
        case 0:
            return;
        default:
            break;
    }
}

void menuGerirClientes() {
    switch (obterInt(MENU_GERIR_CLIENTES_MSG, 0, 4)) {
        case 1:
            criarCliente(&clientes);
            break;
        case 2:
            editarCliente(&clientes);
            break;
        case 3:
            removerCliente(&clientes, encomendas);
            break;
        case 4:
            uploadClientes(&clientes);
        case 0:
            return;
        default:
            break;
    }
}

void menuGerirProdutos() {
    switch (obterInt(MENU_GERIR_PRODUTOS_MSG, 0, 3)) {
        case 1:
            editarProduto(&produtos);
            break;
        case 2:
            removerProduto(&produtos, encomendas);
            break;
        case 3:
            uploadProdutos(&produtos);
            break;
        case 0:
            return;
        default:
            break;
    }
}

void menuGerirProducao(){
    switch (obterInt(MENU_GERIR_PRODUCAO_MSG, 0, 5)){
        case 1:
            obterLista(&encomendas, &produtos, &materiais);
            break;
        case 2:
            obterListaProdutos(&encomendas, &produtos);
            break;
        case 3:
            obterListaClientes(&encomendas, &clientes);
            break;
        case 4:
            retornoMeses(&encomendas, &produtos);
            break;
        case 5:
            vendasPorMes(&encomendas, &produtos);
            break;
        case 0:
            return;
        default:
            break;
    }
}
void menuAdmin() {
    switch (obterInt(MENU_ADMIN_MSG, 0, 3)) {
        case 1:
            menuGerirClientes();
            break;
        case 2:
            menuGerirProdutos();
            break;
        case 3:
            menuGerirProducao();
            break;
        case 0:
            return;
        default:
            puts(MENU_MSG_INVALIDA);
            break;
    }
}

void menuPrincipal() {
    int opcao;
    puts(EMPRESA_MSG);
    do {
        opcao = obterInt(MENU_PRINCIPAL_MSG, 0, 2);
        switch (opcao) {
            case 1:
                menuAdmin();
                break;
            case 2:
                menuCliente();
                break;
            case 0:
                return;
            default:
                puts(MENU_MSG_INVALIDA);
                break;
        }
    } while (opcao);
}

int main() {
    produtos.produto = (Produto *) malloc(NUM_PRODUTOS * sizeof(Produto));
    encomendas.encomenda = (Encomenda *) malloc(NUM_ENCOMENDAS * sizeof(Encomenda));
    clientes.cliente = (DadosPessoais *) malloc(MAX_CLIENTES * sizeof(DadosPessoais));
    //materiais.material = (Material *) malloc(NUM_MATERIAIS * sizeof(Material));

    importExcel(&produtos, &materiais);
    loadClientes(&clientes);
    loadEncomendas(&encomendas);
    
    menuPrincipal();
    
    uploadEncomendas(&encomendas);
    
    free(produtos.produto);
    free(encomendas.encomenda);
    free(clientes.cliente);
    //free(materiais.material);
    
    return 0;
}

