/**
@file sgv.h
Definicão do SGV e das queries
*/
#ifndef ___SGV_H___
#define ___SGV_H___
#include "catClientes.h"
#include "catProds.h"

/**
\brief Declaracão do tipo SGV
Contém o catálogo de produtos, de clientes, das filiais e da faturacão
*/
typedef struct sgv* SGV;
/**
\brief Inicializacão de um SGV
@returns SGV vazio com todos os catálogos inicializados (também vazios)
*/
SGV initSGV();
/**
\brief Carrega os ficheiros de vendas, produtos e clientes para o SGV
@param sgv - SGV que irá ser carregado com a informacão dos 3 ficheiros
@param dirSales - Diretorio onde se encontra o ficheiro de vendas a carregar
@param dirProds - Diretorio onde se encontra o ficheiro de produtos a carregar
@param dirClnts - Diretorio onde se encontra o ficheiro de clientes a carregar
@returns SGV com a informacão carregada e validada
*/
SGV loadSGVFromFiles(SGV sgv, char* dirSales, char* dirProds, char* dirClnts);
/**
\brief Elimina um SGV e os seus catalogos de memória
@param sgv - SGV que irá ser eliminado
*/
void destroySVG(SGV sgv);

/**
\brief Define o tipo que irá ser usado para mostrar o resultado da Query9 na interface
*/
typedef struct query9* Query9;
/**
\brief Retorna a ListaClientes que será mostrada
param q - Resultado da query 9
@returns ListaClientes a mostrar
*/ 
ListaClientes getListaClientesQ9(Query9 q);
/**
\brief Lê o numero de compras por tipo resultantes da query 9
param q - Resultado da query 9
@returns Array de ints com o valor de compras N e P
*/ 
int* getComprasQ9(Query9 q);
/**
\brief Elimina os resultados da Query 9
@param q - Resultados a ser eliminados
*/
void closeQuery9(Query9 q);

/*
typedef struct query11* Query11;
ListaProds* getListaProdsQuery11(Query11 q);
int getNClientsQuery11(Query11 q, int i);
int getNUnidadesQuery11(Query11 q, int i);*/

/**
\brief Retorna informacão sobre os ficheiros abertos anteriormente
@param sgv - SGV com a informacão dos ficheiros
@returns Array de inteiros com a informacão contida
*/
int* getValoresFilesInfo(SGV sgv);

/*=============================QUERY ZONE=============================*/

/**
\brief Listagem com todos os produtos comecados por uma dada letra
@param sgv - SGV com as estruturas de dados inicializadas
@param letter - Letra fornecida pelo utilizador
@returns Lista de produtos com os produtos comecados pela letra fornecida
*/
ListaProds getProductsStartedByLetter(SGV sgv, char letter);

/**
\brief Calcula o numero total de vendas e o total faturado p
@param sgv - SGV com as estruturas de dados inicializadas 
@param productID - ID do produto
@param month - Mes
@returns Matriz de floats onde se encontra o Faturado(N e P) e o numero de registos(N e P)
*/
float** getProductSalesAndProfit(SGV sgv, char* productID, int month);

/**
\brief Calcula os produtos que nunca foram comprados (Total ou numa Filial especifica)
@param sgv - SGV com as estruturas de dados inicializadas 
@param productID - ID da Filial
@returns Lista de produtos que nunca foram comprados
*/
ListaProds getProductsNeverBought(SGV sgv, int branchID);
/**
\brief Calcula os clientes que fizeram compras em todas as Filiais 
@param sgv - SGV com as estruturas de dados inicializadas 
@returns Lista de clientes que compraram em todas as filiais
*/
ListaClientes getClientsOfAllBranches(SGV sgv);
/**
\brief Calcula o numero de clientes que nunca compraram nada e o numero de produtos nunca comprados 
@param sgv - SGV com as estruturas de dados inicializadas 
@returns Array de ints com duas posicões com os resultados da query
*/
int* getClientsAndProductsNeverBoughtCount(SGV sgv);
/**
\brief Calcula o numero total de compras por mes em cada filial feito por um cliente
@param sgv - SGV com as estruturas de dados inicializadas 
@param clientID - ID do cliente a pesquisar
@returns Array de ints com os totais ordenados por mes e filial
*/
int** getProductsBoughtByClient(SGV sgv, char* clientID);
/**
\brief Calcular o total de vendas e o total faturado entre dois meses 
@param sgv - SGV com as estruturas de dados inicializadas 
@param minMonth - Limite inferior
@param maxMonth - Limite superior
@returns Array de long doubles o total faturado e o total de vendas 
*/
long double* getSalesAndProfit(SGV sgv, int minMonth, int maxMonth);
/**
\brief Calcular a lista de clientes que compraram um dado produto numa filial e quantas dessas compras eram Normais ou em Promocao
@param sgv - SGV com as estruturas de dados inicializadas 
@param productID - ID do produto que irá ser verificado
@param branch - Filial que se irá analizar
@returns Estrutura com a lista de clientes e os totais de compras (N ou P) 
*/
Query9 getProductBuyers(SGV sgv, char* productID, int branch);
/**
\brief Calcular a lista de produtos que um dado cliente mais comprou durante um mes
@param sgv - SGV com as estruturas de dados inicializadas 
@param clientID - ID do cliente a analizar
@param month - Mês da compra
@returns Lista dos produtos mais comprados por um cliente
*/
ListaProds getClientFavoriteProducts(SGV sgv, char* clientID, int month);
/**
\brief Criar uma lista com os N produtos mais vendidos durante um ano, indicando também o número de clientes e de unidades vendidas
@param sgv - SGV com as estruturas de dados inicializadas 
@param limit - Número de produtos que devem ser apresentados
@returns Lista dos produtos mais comprados
*/
ListaProds getTopSelledProducts(SGV sgv, int limit);
/**
\brief Calcular a lista de produtos em que um cliente mais gastou dinheiro durante um ano
@param sgv - SGV com as estruturas de dados inicializadas 
@param clientID - ID do cliente a analizar
@param limit - Número de produtos que devem ser apresentados
@returns Lista dos produtos em que um cliente mais gastou dinheiro
*/
ListaProds getClienteTopProfitProducts(SGV sgv, char* clientID, int limit);
/**
\brief Apresentar os resultados da leitura dos ficheiros que inicializaram o SGV
@param sgv - SGV com as estruturas de dados inicializadas 
@returns Array de strings com a informacão relativa a cada ficheiro
*/
char** getCurrentFilesInfo(SGV sgv);

#endif