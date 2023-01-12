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
                                "2.Editar cliente\n3.Remover cliente\n4.Retroceder\n0.Sair\n"\
                                "Selecione uma opcao (0-4):"
#define MENU_GERIR_PRODUTOS_MSG "----------\nGestao de produtos\n----------\n1.Editar produto\n"\
                                "2.Remover produto\n3.Retroceder\n0.Sair\nSelecione uma opcao (0-3):"
#define MENU_GERIR_PRODUCAO_MSG "----------\nGestao da producao\n----------\n1.Obter lista de componentes"\
                                " de encomendas(por semana)\n2.Retroceder\n0.Sair\nSelecione uma opcao (0-2):"
#define MENU_MSG_INVALIDA "Insira uma opcao valida!"

//Produtos produtos = {};
Produtos *produtos = (Produtos*) malloc(MAX_PRODUTOS * sizeof(Produtos));
Encomendas encomendas = {};
Material materiais = {};

void menuCliente() {
    switch (obterInt(MENU_CLIENTE_MSG, 0, 1)) {
        case 1:
            registarEncomenda(produtos, encomendas);
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
            criarCliente();
            break;
        case 2:
            editarCliente();
            break;
        case 3:
            removerCliente();
            break;
        case 4:
            //menuAdmin();
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
            //menuAdmin();
            break;
        case 0:
            return;
        default:
            break;
    }
}

void menuGerirProducao(){
    switch (obterInt(MENU_GERIR_PRODUCAO_MSG, 0, 2)){
        case 1:
            obterLista();
            break;
        case 2:
            //menuAdmin();
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
    importExcel(&produtos, &materiais);
    printf("aaa");
    
    //loadProdutos(&produtos);
    loadEncomendas(&encomendas);
    
    menuPrincipal();

    
    uploadProdutos(&produtos);
    uploadEncomendas(&encomendas);
    
    return 0;
}

