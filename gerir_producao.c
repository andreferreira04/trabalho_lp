#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "input.h"
#include "gerir_produtos.h"

int procurarEncomenda2(char *data, Encomendas encomendas) {
    for (int i = 0; i < encomendas.numEncomendas; i++) {
        if (strcmp(encomendas.encomenda[i].data, data) == 0) { //encontrou
            return 1;
        }
    }
    return 0;
}

int obterPosicaoEncomenda(char *data, Encomendas encomendas) {
    for (int i = 0; i < encomendas.numEncomendas; i++) {
        if (strcmp(encomendas.encomenda[i].data, data) == 0) { //encontrou um produto ativo
            return i;
        }
    }
    return -1;
}

void obterLista(Encomendas *encomendas) {
    int j, i, d, m, y;
    char data[30];

    do {
        printf("Escreva o primeiro dia da semana que quer analisar (DD/MM/AAAA):");
        scanf("%d/%d/%d", &d, &m, &y);
    } while (!verificaData(d, m, y));

    for (i = 0; i < 8; i++) {
        struct tm t = {0};
        t.tm_mday = d;
        t.tm_mon = m - 1;
        t.tm_year = y - 1900;
        t.tm_mday += i;
        mktime(&t);
        strftime(data, 30, "%d/%m/%Y", &t);
        puts(data);
        /*if (procurarEncomenda2(data, *encomendas) == 1) { // se o produto existir
            int pos = obterPosicaoEncomenda(data, *encomendas);
                for (int i = pos; i < encomendas->numEncomendas - 1; i++) {
                    
                }
            }*/
        }
    }
