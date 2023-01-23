#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "input.h"
#include "gerir_produtos.h"
#include "gerir_clientes.h"

/**
 * Esta função lista as encomendas para entregar numa dada semana
 * 
 * @param encomendas struct do tipo Encomendas, onde encontra as encomendas dentro dessa semana
 * @param produtos struct do tipo Produtos, para buscar informação sobre os produtos encomendados
 * @param materiais struct do tipo Materiais, para contar a quantidade demateriais
 */
void obterLista(Encomendas *encomendas, Produtos *produtos, Materiais *materiais) {
    int d, m, y;
    char data[30];
    int count_materiais[materiais->numMateriais];
    char codMaterial[TAM_MATERIAL];
    for (int i = 0; i < materiais->numMateriais; i++) {
        count_materiais[i] = 0;
    }

    do {
        printf("Escreva um dia da semana que quer analisar (DD/MM/AAAA):");
        scanf("%d/%d/%d", &d, &m, &y);
    } while (!verificaData(d, m, y));
    
    struct tm t = {};
    
    for (int i = 0; i < 7; i++) {
        t.tm_mday = d - diaDaSemana(d, m, y);
        t.tm_mon = m - 1;
        t.tm_year = y - 1900;
        t.tm_mday += i;
        mktime(&t);
        strftime(data, 30, "%d/%m/%Y", &t);
        
        struct date d1 = {t.tm_mday, t.tm_mon + 1, t.tm_year + 1900};
        struct date d2 = {};
        int count;
        
        for (int j = 0; j < encomendas->numEncomendas; j++) {
            char tmpdate[11];
            for (int k = 0; k < strlen(encomendas->encomenda[j].data); k++) {
                tmpdate[k] = encomendas->encomenda[j].data[k];
            }
            
            char *token = strtok(tmpdate, "/");
            count = 0;
                        
            while (token != NULL) {
                switch (count) {
                    case 0: d2.dd = atoi(token);break;
                    case 1: d2.mm = atoi(token);break;
                    case 2: d2.yy = atoi(token);break;
                }
                count++;
                token = strtok(NULL, "/");
            }
            if (date_cmp(d1, d2) == 1) { //se uma encomenda está dentro da semana escolhida
                int posProduto = obterPosicaoProduto(encomendas->encomenda[j].idProduto, *produtos); //2,   3
                
                for (int k = 0; k < produtos->produto[posProduto].numMateriais; k++) {                    
                    strcpy(codMaterial, produtos->produto[posProduto].materiais[k]);
                    int posMaterial = obterPosicaoMaterial(codMaterial, *materiais);
                    
                    if (posMaterial != -1) {
                        if (produtos->produto[posProduto].unidades[k] == 'P') {
                            count_materiais[posMaterial] += produtos->produto[posProduto].quantidades[k] * 2;
                        }
                        else {
                            count_materiais[posMaterial] += produtos->produto[posProduto].quantidades[k];
                        }
                    }
                }
            }
        }
    }
    
    printf("Lista de materiais necessarios para satisfazer as encomendas da semana %d/%d/%d:\n", d, m, y);
    for (int i = 0; i < materiais->numMateriais; i++) {
        printf("\t%s (%s): %d\n", materiais->material[i].codMaterial, materiais->material[i].descricao, count_materiais[i]);
    }
}


/**
 * Esta função lista o número de encomendas de todos os produtos
 * 
 * @param encomendas apontador para struct do tipo Encomendas para ir buscar as encomendas
 * @param produtos apontador para struct do tipo Produtos para obter informações sobre os produtos
 */
void obterListaProdutos(Encomendas *encomendas, Produtos *produtos) {
    int count_produtos[produtos->numProdutos];
    int array_produtos[produtos->numProdutos];
    
    for (int i = 0; i < produtos->numProdutos; i++) {
        count_produtos[i] = 0;
        array_produtos[i] = 0;
    }
        
    for (int i = 0; i < encomendas->numEncomendas; i++) {
        char tmpstr[7];
        strcpy(tmpstr, encomendas->encomenda[i].idProduto);
        memmove(tmpstr, tmpstr+1, strlen(tmpstr));
        
        array_produtos[obterPosicaoProduto(encomendas->encomenda[i].idProduto, *produtos)] = atoi(tmpstr);
        count_produtos[obterPosicaoProduto(encomendas->encomenda[i].idProduto, *produtos)]++;
    }
    
    for (int i = 0; i < produtos->numProdutos; i++) {
        printf("P%05d: %d encomendas totais\n", array_produtos[i],count_produtos[i]);
    }
}

/**
 * Esta função lista o número de encomendas pro cliente
 * 
 * @param encomendas apontador para struct do tipo Encomendas para ir buscar as encomendas
 * @param clientes apontador para struct do tipo Clientes para obter informações sobre os clientes
 */
void obterListaClientes(Encomendas *encomendas, Clientes *clientes) {
    int count_clientes[clientes->numClientes];
    int array_clientes[clientes->numClientes];
    
    for (int i = 0; i < clientes->numClientes; i++) {
        count_clientes[i] = 0;
        array_clientes[i] = 0;
    }
        
    for (int i = 0; i < encomendas->numEncomendas; i++) {
        char tmpstr[7];
        strcpy(tmpstr, encomendas->encomenda[i].idCliente);
        memmove(tmpstr, tmpstr+1, strlen(tmpstr));
                
        count_clientes[obterPosicaoCliente(encomendas->encomenda[i].idCliente, *clientes)]++;
        array_clientes[obterPosicaoCliente(encomendas->encomenda[i].idCliente, *clientes)] = atoi(tmpstr);
    }
    
    for (int i = 0; i < clientes->numClientes; i++) {
        printf("C%05d: %d encomendas totais\n", array_clientes[i],count_clientes[i]);
    }
}

/**
 * Esta função lista o retorno financeiro conseguido ao longo dos meses do ano atual
 * 
 * @param encomendas apontador para struct do tipo Encomendas para ir buscar as encomendas
 * @param produtos apontador para struct do tipo Produtos para obter informações sobre os produtos
 */
void retornoMeses(Encomendas *encomendas, Produtos *produtos) {
    int mes, ano, count;
    int contagens_mes[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    for (int i = 0; i < 13; i++) {
        contagens_mes[i] = 0;
    }

    for (int j = 0; j < encomendas->numEncomendas; j++) {
        char tmpdate[11];
        count = 0;
        for (int k = 0; k < strlen(encomendas->encomenda[j].data); k++) {
            tmpdate[k] = encomendas->encomenda[j].data[k];
        }
        char *token = strtok(tmpdate, "/");

        while (token != NULL) {
            switch (count) {
                case 1: mes = atoi(token);
                    break;
                case 2:
                    ano = atoi(token);
                    break;
            }
            count++;
            token = strtok(NULL, "/");
        }
        if (ano == (tm.tm_year + 1900)) {
            contagens_mes[mes - 1] += produtos->produto[obterPosicaoProduto(encomendas->encomenda[j].idProduto, *produtos)].precoProduto;
        }
    }
    for (int i = 0; i < 12; i++) {
        printf("Retorno do mes %d: %d€\n", i + 1, contagens_mes[i]);
    }
}

/**
 * Esta função lista as vendas conseguidas ao longo dos meses do ano atual
 * 
 * @param encomendas apontador para struct do tipo Encomendas para ir buscar as encomendas
 * @param produtos apontador para struct do tipo Produtos para obter informações sobre os produtos
 */
void vendasPorMes(Encomendas *encomendas, Produtos *produtos) {
    int mes, ano, count;
    int contagens_mes[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    for (int i = 0; i < 13; i++) {
        contagens_mes[i] = 0;
    }

    for (int j = 0; j < encomendas->numEncomendas; j++) {
        char tmpdate[11];
        count = 0;
        for (int k = 0; k < strlen(encomendas->encomenda[j].data); k++) {
            tmpdate[k] = encomendas->encomenda[j].data[k];
        }
        char *token = strtok(tmpdate, "/");

        while (token != NULL) {
            switch (count) {
                case 1: mes = atoi(token);
                    break;
                case 2:
                    ano = atoi(token);
                    break;
            }
            count++;
            token = strtok(NULL, "/");
        }
        if (ano == (tm.tm_year + 1900)) {
            contagens_mes[mes - 1] ++;
        }
    }
    for (int i = 0; i < 12; i++) {
        printf("Vendas do mes %d: %d\n", i + 1, contagens_mes[i]);
    }
}
