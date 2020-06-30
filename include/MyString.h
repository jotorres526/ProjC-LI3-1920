/**
@file MyString.h
Definicão de funcões gerais de manipulacão de strings
*/
#ifndef ___MYSTRING_H___
#define ___MYSTRING_H___
#include "myTypes.h"

/**
\brief Passa todos os chars de uma string para maiusculas
@param str - String a alterar
*/
void strToUpper(char* str);
/**
\brief Clona uma string
@param str - String a clonar
@returns String clonada
*/
char* dupString(char* str);
/**
\brief Passa um mês para uma string
@param mes - Mes que será transformado numa string
@returns String indicativa do mês
*/
char* mesToString(Mes mes);
#endif