#ifndef INPUT_H
#define INPUT_H

void cleanInputBuffer();
int obterInt(char *msg, int minimo, int maximo);
void lerString(char *string, unsigned int tamanho, char *msg);
int verificaData (int dia, int mes, int ano);

#endif
