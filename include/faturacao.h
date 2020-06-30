/**
@file faturacao.h
Definicão da entidade faturacao e das funcões que a manipulam
*/
#ifndef ___FATURACAO_H___
#define ___FATURACAO_H___
#include "produto.h"
#include "filial.h"

/**
\brief Definicao do tipo Faturacao
*/
typedef struct faturacao* Faturacao;

/**
\brief Inicializa uma faturacao vazia
@returns Faturacao vazia
*/
Faturacao initFaturacao();

/**
\brief Insere um produto na estrutura da faturacão
@param f - Faturacao onde irá ser inserido o produto
@param p - Produto a inserir
@returns Faturacao com o produto inserido
*/
Faturacao insereRegistoFaturacao(Faturacao f, Produto p);

/**
\brief Aumenta os dados parametros de um produto da faturacao
@param f - Faturacao onde irá ser alterado um produto
@param p - Produto a ser aumentado
@param preco - Valor em que irá ser aumentado o preco
@param quant - Quantidade que irá ser aumentada
@param filial - Numero da filial onde o produto foi vendido 
@param m - Mes do registo da faturacao
@param np - Tipo de compra N ou P
@returns Faturacao atualizada
*/
Faturacao aumentaFaturacao(Faturacao f, Produto p, float preco, int quant, int filial, int m, char np);

/**
\brief Retorna o total faturado de um produto num certo mês
@param f - Faturacao onde irá ser procurado o produto
@param codProd - Código do produto a procurar
@param m - Mês a ter em consideracão
@returns Matriz que tem a faturacão total N e P juntamente com o total de vendas N e P
*/
float** fatPorProdutoMes(Faturacao fat, char* codProd, int m);

/**
\brief Retorna o total faturado de todos os produtos e o numero de vendas entre dois meses
@param f - Faturacao que irá ser "varrida"
@param minMonth - Limite inferior
@param maxMonth - Limite superior
@returns Array de long doubles com total faturado e o total de vendas
*/
long double* regAndFatEntreMeses(Faturacao f, int minMonth, int maxMonth);

/**
\brief Procura os produtos que nunca foram comprados numa faturacao ou por filial
@param f - Faturacao que irá ser "varrida"
@param r - Lista de produtos que irá ser construida com chamadas sucessivas desta funcão
@param branchID - ID da filial que queremos verificar
@returns Lista dos produtos que não foram comprados
*/
ListaProds prodsFaturNuncaComprados(Faturacao f, ListaProds r, int branchID);

/**
\brief Calcula o numero de registos de venda de um produto por filial
@param f - Faturacao que irá ser "varrida"
@param p - Código do produto
@param branch - ID da filial que queremos verificar
@returns Numero de registos de venda
*/
int getNumRegVendaFatFilial(Faturacao f, char* p, int branch);


/**
\brief Apaga de memória uma faturacao
@param f - Faturacao a apagar
*/
void closeFaturacao(Faturacao f);

#endif 