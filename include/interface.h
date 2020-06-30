/**
@file interface.h
Definicão da entidade interface que só exporta para o main a funcão prompt
*/
#ifndef ___PROMPT_H___
#define ___PROMPT_H___
#include "sgv.h"

/**
\brief Cria um interpretador de comandos para interagir com o utilizador
@param sgv - SGV com os catálogos que o user vai questionar
*/
void prompt(SGV sgv);

#endif