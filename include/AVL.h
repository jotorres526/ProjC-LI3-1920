/**
@file AVL.h
Definicão do tipo AVL e das funcoes que a manipulam
É a base do catálogo de produtos e de clientes
*/
#ifndef ___AVL_H___
#define ___AVL_H___
#include "myTypes.h"

/**
\brief Tipo de dados AVL
> Aceita um int como chave
*/
typedef struct avl* AVL;

/**
\brief Inicializa uma AVL
@returns AVL vazia 
*/
AVL inicializaAVL();

/**
\brief Insere um nodo numa AVL
@param a - AVL onde irá ser inserido o novo elemento
@param node - Elemento a inserir na AVL
@returns AVL com o novo elemento inserido corretamente 
*/
AVL insereAVL(AVL a, int node);

/**
\brief Procura um nodo numa AVL
@param a - AVL onde irá ser efetuada a procura
@param node - Elemento a procurar
@returns False se o nodo não existir ou True caso contrário
*/
boolean procuraAVL(AVL a, int node);

/**
\brief Avanca a AVL para a sub-árvore da direita
@param a - AVL que se vai avancar 
@returns AVL da direita
*/
AVL getRight(AVL a);

/**
\brief Avanca a AVL para a sub-árvore da esquerda
@param a - AVL que se vai avancar 
@returns AVL da esquerda
*/
AVL getLeft(AVL a);

/**
\brief Retorna o nodo da AVL
@param a - AVL que com o nodo a retornar 
@returns Nodo raiz
*/
int getNode(AVL a);

/**
\brief Encerra uma AVL apagando-a de memória
@param a - AVL a fechar 
*/
void closeAVL(AVL a);

#endif