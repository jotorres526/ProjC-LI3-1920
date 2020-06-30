/**
@file RegistoFat.h
Definicão da entidade RegistoFaturacão e das funcões que o manipulam 
*/
#ifndef ___REGISTOFAT_H___
#define ___REGISTOFAT_H___
#include "myTypes.h"

/**
\brief Definicão do tipo RegistoFaturacao
*/
typedef struct registoFat* RegistoFaturacao;

/**
\brief Inicializa um registo de faturacão vazio
@returns RegistoFaturacao vazio
*/
RegistoFaturacao initRegistoFaturacao();

/**
\brief Dado um registo aumenta os valores do mesmo
@param rf - Registo a ser alterado
@param preco - Valor em que irá ser aumentado o preco
@param quant - Quantidade que irá ser aumentada
@param filial - Numero da filial onde o produto foi vendido 
@param m - Mes do registo da faturacao
@param np - Tipo de compra N ou P
*/
void aumentaRegisto(RegistoFaturacao rf, float preco, int quant, int filial, int m, char np);

/**
\brief Calcula todos os valores de um registo num dado mes
@param rf - Registo que será analizado
@param mes - Mês onde será calculado os valores
@returns Matriz com todos os valores de um dado registo
*/
float** getValoresRegistos(RegistoFaturacao rf, int mes);

/**
\brief Retorna o total faturado de um dado produto e o numero de vendas entre dois meses
@param rf - Registo que será analizado
@param minMonth - Limite inferior
@param maxMonth - Limite superior
@returns Array de long doubles com o total faturado de um produto e o total de vendas
*/
long double* vendasFaturadoRegisto(RegistoFaturacao rf, int minMonth, int maxMonth);


int getRegVendaProdFaturacaoAux(RegistoFaturacao r, int branch);

/**
\brief Verifica se um dado produto foi comprado numa dada filial
@param rf - Registo que será analizado
@param branchID - ID da branch que se quer verificar
@returns True se tiver sido comprado, False caso contrário
*/
boolean isComprado(RegistoFaturacao rf, int branchID);

/**
\brief Apaga de memória um RegistoFaturcao
@param f - RegistoFaturacao a apagar
*/
void closeRegistoFaturacao(RegistoFaturacao rf);

#endif