#ifndef INPUT_H
#define INPUT_H

#include "gerir_produtos.h"

void cleanInputBuffer();
int obterInt(char *msg, int minimo, int maximo);
void lerString(char *string, unsigned int tamanho, char *msg);
int verificaData (int dia, int mes, int ano);
int date_cmp(struct date d1, struct date d2);
int diaDaSemana(int d, int m, int y);

#endif
