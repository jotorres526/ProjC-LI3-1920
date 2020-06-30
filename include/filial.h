/**
@file filial.h
Definicão da entidade filial e das funcões que a manipulam
*/
#ifndef ___FILIAL_H___
#define ___FILIAL_H___
#include "cliente.h"
#include "catClientes.h"
#include "produto.h"
#include "RegistoFilial.h"

/**
\brief definição do tipo Filial
*/
typedef struct filial* Filial;

/**
\brief Inicializa uma filial vazia
@returns Filial vazia
*/
Filial initFilial();

/**
\brief Insere um cliente na estrutura da filial
@param c - Cliente a inserir na filial
@param f - Filial onde se irá inserir o cliente
@returns Filial com o cliente inserido
*/
Filial insereClienteFilial(Cliente c, Filial f);
/**
\brief Insere um registo na lista de registos filial, dados os parametros, num cliente da filial
@param f - Filial onde está o cliente onde se vai inserir o registo
@param c - Cliente onde se vai inserir o registo
@param q - Valor de quantidade do registo filial
@param modo - Tipo de compra do registo filial
@param mes - Mes do registo da filial
@return Filial atualizada
*/
Filial insereRegistoFilial(Filial f, Cliente c, Produto prod, int q, char modo, int mes);

/**
\brief Procura todos os clientes que compraram pelo menos um produto na filial
@param f - Filial onde se vai procurar
@return ListaCLientes com os clientes que compraram pelo menos um produto
*/
ListaClientes getCompradoresFilial(Filial f);
/**
\brief Procura os clientes que nao compraram na filial
@param f - Filial onde se vai procurar
@return ListaClientes com os clientes que nao compraram nesta filial
*/
ListaClientes getNaoCompradoresFilial(Filial f);
/**
\brief Percorre a filial à procura dos registos do cliente 
@param f - Filial onde se vai procurar os registos do cliente
@param codCliente - String com o codigo do cliente
@return int* array de tamanho 12 em que cada posiçao corresponde às compras do cliente num certo mês
*/
int* getRegistosCliente(Filial f, char* codCliente);
/**
\brief Procura os clientes que compraram o produto p na filial f
@param f - Filial onde se procura
@param p - Produto que se procura
@param compN - apontador para as compras que se fez pelo método N
@param compP - apontador para as compras que se fez pelo método P
@returns ListaClientes que compraram o produto p
*/
ListaClientes clientesProduto(Filial f, Produto p, int* compN, int* compP);

/**
\brief Procura os registos feitos pelo cliente neste mes
@param f - Filial onde se procura os registos
@param c - Cliente que se procura na filial
@param mes - Mês que se vai registar as compras feitas pelo cliente
@returns ListaRegistosFilial dos registos feitos no mes recebido como parametro pelo cliente
*/
ListaRegistosFilial getListaRegistosFilialClienteMes (Filial f, Cliente c, Mes m);
/**
\brief Utilizada para a query 11, mas nao funciona. Deveria retornar os registos dos N produtos mais comprados
*/
ListaRegistosFilial getTopNProdsFilial(Filial f, ListaRegistosFilial mainList);
/**
\brief Utilizada para a query 12, mas nao funciona. Deveria retornar os regitos do cliente
*/
ListaRegistosFilial getClienteTopProfitProductsFilial(Filial f, char* clientID);

void closeFilial(Filial f);

#endif 