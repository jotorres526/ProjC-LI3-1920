/**
@file AVLRegistos.h
Definicão do tipo AVLRegistas e das funcoes que a manipulam
É a base do catálogo das filiais e da faturacao
A diferenca para a AVL é que aqui guarda tambem um registo alem do nodo 
No caso de ser usado para faturacao o registo é um RegistoFaturacao
No caso de ser usado para filial o registo é uma ListaRegistosFilial
*/
#ifndef ___AVLREG_H___
#define ___AVLREG_H___
#include "RegistoFat.h"
#include "catProds.h"
#include "RegistoFilial.h"
#include "catClientes.h"

/**
\brief Definicão do tipo AVLRegistos
*/
typedef struct avlRegistos* AVLRegistos;

/**
\brief Inicializa uma AVLRegistos vazia
@returns AVLRegistos vazia 
*/
AVLRegistos initAVLRegistos();

/**
\brief Adiciona um nodo, que contém um registo, à AVLRegistos
@param a - AVLRegistos onde será inserido o nodo
@param node - Nodo que será inserido (serve como chave de procura)
@param rf - Registo que estará associado a um nodo
@returns AVLRegistos com o novo nodo inserido
*/
AVLRegistos insereAVLRegistos(AVLRegistos a, int key, void* rf);

/**
\brief Dada uma AVLRegistos, uma key e um RegistoFilial adiciona o registo à ListaRegistosFilial do nodo
@param a - AVLRegistos onde irá ser adicionado o registo
@param key - Chave do nodo onde será adicionado o registo
@param registo - Registo que será adicionado à lista de registos do nodo
*/
void adicionaRegistoFilialAVL(AVLRegistos a, int key, void* registo);

/**
\brief Dada uma AVLRegistos e uma key retorna o registo associado ao nodo
@param a - AVLRegistos onde irá ser procurado o registo
@param key - Chave do nodo onde se encontra o registo
*/
void* procuraRegisto(AVLRegistos a, int key);

/**
\brief Calcula o total faturado e o numero de vendas que houve entre dois meses
@returns Array de long double onde o primeiro elemento é o numero de vendas e o segundo é o total faturado
*/
long double* fatAndNumVendas(AVLRegistos a, int minMonth, int maxMonth);
ListaRegistosFilial getTopNProdutosAVLRegistos(AVLRegistos a, ListaRegistosFilial mainList);
ListaRegistosFilial aumentaOuSwapOrdLRegFilial(ListaRegistosFilial mainLista, RegistoFilial r);

/**
\brief Procura todos os Produto que não foram comprados em todo ano em nenhuma Filial
@param ar - AVLRegistos(Faturacao) onde será procurado os Produto não comprados
@param lp - ListaProds que será usada para construir o resultado final de todos os catálogos de Faturacao
@param branchID - Numero da Filial que queremos avaliar. Se for 0 é uma procura da Faturacao global
@param l1 - Primeira letra de um código de Produto para construir o produto que será adicionado à ListaProds
@param l2 - Segunda letra de um código de Produto para construir o produto que será adicionado à ListaProds
@returns ListaProds ordenada com os Produto que não foram comprados
*/
ListaProds produtosNaoComprados(AVLRegistos ar, ListaProds lp, int branchID, char l1, char l2);

/**
\brief ListaClientes que compraram algo em pelo menos uma Filial
@param ar - AVLRegistos(Filial) onde irá ser procurado os Cliente compradores
@param lc - ListaClientes onde será construido o resultado final após iteracões sobre o catálogo da Filial
@param l - Primeira letra do cliente que serve para construir o cliente antes de adicionar à lista
@returns ListaClientes ordenada com os Cliente compradores
*/
ListaClientes clientesCompradores(AVLRegistos ar, ListaClientes lc, char l);

/**
\brief ListaClientes que não compraram nada em nenhuma Filial
@param ar - AVLRegistos(Filial) onde irá ser procurado os Cliente que nada compraram
@param lc - ListaClientes onde será construido o resultado final após iteracões sobre o catálogo da Filial
@param l - Primeira letra do cliente que serve para construir o cliente antes de adicionar à lista
@returns ListaClientes ordenada com os Cliente não compradores
*/
ListaClientes clientesNaoCompradores(AVLRegistos ar, ListaClientes lc, char l);

/**
\brief Encontra todos os Cliente que compraram o Produto p
@param ar - AVLRegistos(Filial) onde irá ser procurado os Cliente que compraram o Produto p
@param lc - ListaClientes onde será construido o resultado final após iteracões sobre o catálogo da Filial
@param l - Primeira letra do Cliente que serve para construir o mesmo antes de adicionar à lista
@param p - Produto que se quer verificar por quem foi comprado
@param compN - Numero de compras do tipo N que é incrementado 
@param compP - Numero de compras do tipo P que é incrementado 
@returns ListaClientes ordenada com todos os Cliente que compraram o Produto p
*/
ListaClientes procuraCompradoresProduto(AVLRegistos ar, ListaClientes lc, char l, Produto p, int* compN, int* compP);

/**
\brief Limpa de memória uma AVLRegistos da Faturacao
@param a - AVLRegistos que será apagada
*/
void closeAVLFaturacao(AVLRegistos a);

/**
\brief Limpa de memória uma AVLRegistos de uma Filial
@param a - AVLRegistos que será apagada
*/
void closeAVLFilial(AVLRegistos a);


#endif