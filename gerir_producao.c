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