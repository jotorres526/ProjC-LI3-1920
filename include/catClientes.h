/**
@file catClientes.h
Definicão do catalogo de clientes e as funcões que o manipulam/acedem
*/
#ifndef ___CATCLIENTES_H___
#define ___CATCLIENTES_H___
#include "cliente.h"
#include "AVL.h"
/**
\brief Definicao do tipo catalogos de clientes
*/
typedef struct catClientes* CatClientes;
/**
\brief Definicao do tipo lista de clientes
*/
typedef struct listaClientes* ListaClientes;

/**
\brief Inicializa um catalogo de clientes vazio
@returns Catalogo de clientes vazio
*/
CatClientes initCatClientes();
/**
\brief Inicializa uma lista de clientes vazia
@returns Lista de clientes vazia
*/
ListaClientes initListaClientes();

/**
\brief Insere um cliente à cabeca lista
@param lc - Lista onde se irá inserir o cliente
@param c - Cliente a inserir
@returns Lista de clientes com o novo cliente
*/
ListaClientes consListaClientes(ListaClientes lc, Cliente c);

/**
\brief Insere um cliente no catálogo de clientes
@param catc - Catálogo onde será inserido o cliente
@param c - Cliente a inserir no catálogo 
@returns Catálogo com o cliente inserido
*/
CatClientes insereCliente(CatClientes catc, Cliente c);

/**
\brief Constrói uma lista de clientes onde os elementos se encontram em todas as listas passadas como paramêtro
@param lc[] - Array de listas de clientes
@returns ListaClientes com clientes presentes em todas as listas
*/
ListaClientes getClientesDupTodasListas(ListaClientes lc[]);

/**
\brief Verifica no catálogo de clientes se existe um dado cliente
@param cc - Catálogo onde se irá procurar
@param c - Cliente a procurar
@returns True se for encontrado o cliente e False caso contrário
*/
boolean existeCliente(CatClientes cc, Cliente c);

/**
\brief Devolve a cabeca de uma lista de clientes para mostrar na interface
@param lc - Lista que retorna a cabeca
@returns Cliente da cabeça da lista
*/
Cliente getCabecaLClientes(ListaClientes lc);
/**
\brief Devolve a cauda de uma lista de clientes para mostrar na interface
@param lc - Lista que retorna a cauda
@returns Cauda da lista
*/
ListaClientes getProxLClientes(ListaClientes lc);

/**
\brief Liberta de memória uma lista de clientes e os respetivos nodos
@param lc - Lista a libertar
*/
void closeListaClientes(ListaClientes lc);
/**
\brief Liberta de memória o catálogo de clientes e os respetivos nodos
@param cc - Catálogo a libertar
*/
void closeCatClientes(CatClientes cc);

#endif