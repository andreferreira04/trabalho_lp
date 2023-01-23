#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "input.h"
#include "gerir_produtos.h"

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
 * Esta função lista o número de encomendas de todos os produtos, ordenadamente
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
    
    printf("%d\n", produtos->numProdutos);
    
    for (int i = 0; i < encomendas->numEncomendas; i++) {
        char tmpstr[7];
        strcpy(tmpstr, encomendas->encomenda[i].idProduto);
        memmove(tmpstr, tmpstr+1, strlen(tmpstr));
        
        array_produtos[obterPosicaoProduto(encomendas->encomenda[i].idProduto, *produtos)] = atoi(tmpstr);
        count_produtos[obterPosicaoProduto(encomendas->encomenda[i].idProduto, *produtos)]++;
    }
    
    int temp;
    for (int i = 0; i < produtos->numProdutos; i++) {
        for (int j = i+1; j < produtos->numProdutos; j++) {
            if(count_produtos[i] < count_produtos[j]) {
                temp = count_produtos[i];
                count_produtos[i] = count_produtos[j];
                count_produtos[j] = temp;
                
                temp = array_produtos[i];    
                array_produtos[i] = array_produtos[j];    
                array_produtos[j] = temp;  
            }
        }
    }
    
    for (int i = 0; i < produtos->numProdutos; i++) {
        printf("P%05d: %d encomendas totais\n", array_produtos[i],count_produtos[i]);
    }
}