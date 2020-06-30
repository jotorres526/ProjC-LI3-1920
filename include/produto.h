/**
@file produto.h
Definicão da entidade produto e das funcões que a manipulam
*/
#ifndef ___PRODUTO_H___
#define ___PRODUTO_H___
#include "myTypes.h"

/**
\brief Definicão do tipo Produto
*/
typedef struct prod* Produto;

/**
\brief Cria um produto com um dado código
@param codProd - Código do produto
@returns Produto registado
*/
Produto criaProd(char* codProd);

/**
\brief Verifica se um Produto é válido
@param sp - Produto a verificar
@returns True se for válido, False caso contrário
*/
boolean isValidProd(Produto sp);

/**
\brief Compara dois produtos alfabéticamente
@param p1 - Primeiro produto
@param p2 - Segundo produto
@returns 0 se forem iguais; maior do que 0 se p2 for maior que p1; menor do que 0 caso contrário
*/
int compareProduto(Produto p1, Produto p2);

/**
\brief Retorna o código de um produto
@param p - Produto que será extraido o código
@returns Código de produto
*/
char* getCodProd(Produto p);

/**
\brief Apaga de memória um produto e o seu código
@param p - Produto a apagar
*/
void closeProduto(Produto p);

#endif