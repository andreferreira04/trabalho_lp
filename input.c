#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "input.h"

#define VALOR_INVALIDO_MSG "Valor invalido!\n"

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int obterInt(char *msg, int minimo, int maximo) {
    int opcao;
    
    printf(msg);
    while (scanf("%d", &opcao) != 1 || opcao < minimo || opcao > maximo) {
        puts(VALOR_INVALIDO_MSG);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return opcao;
}

void lerString(char *string, unsigned int tamanho, char *msg) {
    printf(msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}

/** @param dia = recebe o dia inserido
* @param mes = recebe o mes inserido
* @param ano = recebe o ano inserido
* @param anoAtual = recebe o ano atual para verificar se a data é válida
* @return 
*/

int verificaData (int dia, int mes, int ano) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    cleanInputBuffer();
    
    if (ano >= (tm.tm_year + 1900) && ano <= 9999) {
        if(mes >= 1 && mes <= 12) {
            if ((dia >= 1 && dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)) {
                return 1;
            }
            else if ((dia >= 1 && dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) {
                return 1;
            }
            else if ((dia >= 1 && dia <= 28) && (mes == 2)) {
                return 1;
            }
            else if (dia == 29 && mes == 2 && (ano%400 == 0 ||(ano%4 == 0 && ano%100 != 0))) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}
