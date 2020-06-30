/**
@file catProds.h
Definição de catalogo de produtos e as funções  que o manipulam/acedem
*/
#ifndef ___CATPRODS_H___
#define ___CATPRODS_H___

#include "produto.h"
#include "myTypes.h"
#include "AVL.h"
/**
\brief Definição do tipo Catalogos de Produtos 
 */
typedef struct catProds* CatProds;
/** 
\brief Definição do tipo Lista de Produtos
*/
typedef struct lstProds* ListaProds;

/** 
\brief Inicializa um catálogo de produtos vazio
@returns Catalogo de produtos vazio
*/
CatProds initCatProds();
/** 
\brief Inicializa um nodo vazia duma lista de produtos
@returns Nodo vazio duma lista de produtos
*/
ListaProds initNodeLProds();

/** 
\brief Insere um produto no catálogo de produtos
@param cp - Catálogo onde será inserido o produto
@param p - Produto a inserir no catálogo
@returns Catálogo com o produto inserido
*/
CatProds insereProd(CatProds cp, Produto p);
/** 
\brief Insere um produto à cabeça da lista
@param lp - Lista onde se irá inserir o produto
@param p - Produto a inserir
@returns Lista com o novo produto
*/
ListaProds consListaProd(ListaProds lp, Produto p);
/**
\brief Percorre uma AVL que contem os produtos começados pela letra recebida como parametro
@param cp - Catálogo dos produtos
@param letter - Letra pelo qual os produtos retornados começam
@returns ListaProds onde todos os elementos começam pela "letter" e estão ordenados crescentemente
*/
ListaProds prodsToListaPorLetra(CatProds cp, char letter);

/**
\brief Verifica se um certo produto existe no catálogo de produtos
@param cp - Catálogo onde se vai procurar o produto
@param p - produto que se está à procura
@returns boolean Verdadeiro se o produto estiver no catálogo
*/
boolean existeProd(CatProds cp, Produto p);
/** 
\brief Verifica se um certo produto existe numa lista de produtos
@param lp - Lista onde se vai procurar o produto
@param p - Produto que se está à procura
@return boolean Verdadeiro se o produto estiver na lista
*/
boolean existeProdLista(ListaProds lp, Produto p);

/**
\brief Devolve a cabeca de uma lista de produtos para mostrar na interface
@param lp - Lista que retorna a cabeça
@returns Produto da cabeça da lista
*/
Produto getCabecaLProds(ListaProds lp);
/**
\brief Devolve a cauda de uma lista de produtos para mostrar na interface
@param lp - Lista que retorna a cauda
@returns Cauda da lista
*/
ListaProds getProxLProds(ListaProds lp);

/**
\brief Liberta de memória o catálogo de produtos e os respetivos nodos
@param cp - Catálogo a libertar
*/
void closeCatProds(CatProds cp);
/**
\brief Liberta de memória uma lista de produtos e os respetivos nodos
@param lp - Lista a libertar
*/
void closeListaProds(ListaProds lp);

#endif