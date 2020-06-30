/**
@file cliente.h
Definicão da entidade cliente e das funcões que a manipulam
*/
#ifndef ___CLIENTE_H___
#define ___CLIENTE_H___
#include "myTypes.h"

/**
\brief Definicao do tipo Cliente
*/
typedef struct cliente* Cliente;

/**
\brief Cria um cliente com um dado código
@param codCliente - Código que será atribuido ao cliente
@returns Cliente criado
*/
Cliente criaCliente(char* codCliente);

/**
\brief Compara dois clientes por ordem alfabética
@param c1 - Primeiro cliente da comparacão
@param c2 - Segundo cliente da comparacão
@returns 0 se forem iguais; maior do que 0 se c2 for maior que c1; menor do que 0 caso contrário
*/
int compareCliente(Cliente c1, Cliente c2);

/**
\brief Verifica se um cliente é válido
@param c - Cliente a validar
@returns True caso o cliente seja válido, False caso contrário
*/
boolean validateClient(Cliente c);

/**
\brief Retorna o código de um cliente
@param c - Cliente que será extraido o código
@returns Código de cliente
*/
char* getCodCliente(Cliente c);

/**
\brief Apaga de memória um cliente e o seu código
@param c - Cliente a apagar
*/
void closeCliente(Cliente c);

#endif