/*
 * @file gerir_produtos.h
 * @author André Ferreira, Paulo Coelho, Tiago Coelho
 * @date 23 Janeiro 2023
 * 
*/

#ifndef GERIR_PRODUCAO_H
#define GERIR_PRODUCAO_H

#include "gerir_clientes.h"

void obterLista(Encomendas *encomendas, Produtos *produtos, Materiais *materiais);
void obterListaProdutos(Encomendas *encomendas, Produtos *produtos);
void obterListaClientes(Encomendas *encomendas, Clientes *clientes);
void retornoMeses(Encomendas *encomendas, Produtos *produtos);
void vendasPorMes(Encomendas *encomendas, Produtos *produtos);
void paisesEncomenda(Encomendas *encomendas, Clientes *clientes);
#endif


