/**
@file RegistoFilial.h
Definição da entidade RegistoFilial e das funções que o manipulam
*/

#ifndef ___REGISTOFILIAL_H___
#define ___REGISTOFILIAL_H___
#include "produto.h"
#include "catProds.h"
#include "myTypes.h"

/**
\brief Definição do tipo RegistoFilial
*/
typedef struct registoFilial* RegistoFilial;
/**
\brief Definição do tipo ListaRegistoFilial
*/
typedef struct listaRegistosFilial* ListaRegistosFilial;

/**
\brief Cria um registo filial dado os parametros
@param prod - Produto para o registo
@param q - Quantidade para o registo
@param modo - Tipo de compra para o registo
@param mes - Mes de compra para o registo
@returns RegistoFilial
*/
RegistoFilial criaRegistoFilial(Produto prod, int q, char modo, int mes);

/**
\brief Insere um registo filial na cabeça duma lista de registos de filial
@param r - Registo que se vai inserir à cabeça da lista
@param lrf - Lista onde vai se inserir à cabeça
@returns ListaRegistosFilial com o registo inserido à cabeça
*/
ListaRegistosFilial consListaRegistosFilial(RegistoFilial r, ListaRegistosFilial lrf);
/**
\brief Concatena duas listas de Registos Filial
@param l1 - Uma das listas que se vai concatenar
@param l2 - A outra lista que se vai concatenar
@returns ListaRegistosFilial que resultou da concatenação das duas
*/
ListaRegistosFilial concatListaRegistosFilial(ListaRegistosFilial l1, ListaRegistosFilial l2);
/**
\brief Utilizada na query 1, mas a query 11 não funciona
*/
ListaRegistosFilial insereRegistoListaNComp(ListaRegistosFilial lrf, ListaRegistosFilial lfinal, int size, int *n_clientes);
/**
\brief Por implementar (Query 11)
*/
ListaRegistosFilial swapListaRegistos(ListaRegistosFilial l);
/**
\brief Filtra duma lista de registos filial os registos que foram feitos no mês me
@param lrf - Lista que se vai filtrar
@param m - mes que se vai usar para filtrar os registos
@returns ListaRegistoFilial com os registos feitos no mês 'm'
*/
ListaRegistosFilial filtraRegistosMes(ListaRegistosFilial lrf, Mes m);

/**
\brief Filtra os produtos duma lista de registos filial e ordena a alfabeticamente
@param lrf - lista de registos que se vai filtrar
@return ListaProds com os produtos que estavam nos registos por ordem decrescente
*/
ListaProds getListaProdsOrdQuantDesc (ListaRegistosFilial lrf);
/**
\brief Por implementar (Query 11)
*/
ListaProds getConsListaProds(ListaRegistosFilial lrf);
/**
 * brief Por implementar (Query 11)
*/
ListaProds getListaProdsOrdInvQuantDesc (ListaRegistosFilial lrf, int limit);
/**
\brief Ordena uma lista de registos filial por ordem alfabetica dos produtos no registo
@param lrf - lista que se vai ordenar
@return ListaRegistosFilial ordenada
*/
ListaRegistosFilial ordenaPorProd(ListaRegistosFilial lrf);
/**
\brief Retira os registos duma lista de registos que têm o mesmo produto
@param lrf - lista que se vai remover os repetidos
@returns ListaRegistosFilial sem produtos repetidos, nos registos
*/
ListaRegistosFilial removeRepetidos(ListaRegistosFilial lrf);

/**
\brief Guarda os gastos mensais do cliente num array
@param lrf - Lista de registos do cliente
@returns aray com tamanho 12 uma posiçao para a quantidade de gastos mensais
*/
int* getRegistosFilialCliente(ListaRegistosFilial lrf);

/**
\brief Verifica se esta compra ocorreu
@returns True se a compra com aqueles parametros ocorreu no registo
*/
boolean regCompraProd(ListaRegistosFilial lrf, Produto p, int* compN, int* compP);
/**
\brief Por implementar (Query 12)
*/
ListaRegistosFilial getRegistosListaNProds(ListaRegistosFilial mainLista, ListaRegistosFilial l);

/**
\brief Apaga da memoria um Registo Filial
@param l - Lista de Registos Filial que se vai apagar
*/
void closeListaRegistosFilial(ListaRegistosFilial l);

#endif