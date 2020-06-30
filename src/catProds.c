#include "../include/catProds.h"
#include "../include/AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
O catalogo de produtos sera no fundo um array de arvores onde será guardado apenas o NUMERO do produto
Irá ser colocado na posicao equivalente à "chave" dos caracteres
    ie: AA -> i = 0
        AB -> i = 1
        AZ -> i = 25
        BA -> i = 26
*/

struct catProds {
    AVL catalogo[676];
};

struct lstProds {
    Produto prod;
    ListaProds nxtProd;
};

CatProds initCatProds() {
    int i;
    CatProds cp = malloc(sizeof(struct catProds));
    for(i = 0; i < 676; i++) cp->catalogo[i] = inicializaAVL();
    return cp;
}

ListaProds initNodeLProds() {
    ListaProds lp = malloc(sizeof(struct lstProds));
    return lp;
}

CatProds insereProd(CatProds cp, Produto p) {
    char *codProd = getCodProd(p);
    int posCat = 26 * (codProd[0] - 'A') + (codProd[1] - 'A');
    int prodNumber = atoi(codProd + 2);
    cp->catalogo[posCat] = insereAVL(cp->catalogo[posCat], prodNumber);
    return cp;
}

boolean existeProd(CatProds cp, Produto p) {
    char *cod = getCodProd(p);
	int posCat = 26 * (cod[0] - 'A') + (cod[1] - 'A');
	int prodNumber = atoi(cod + 2);
	if(procuraAVL(cp->catalogo[posCat], prodNumber)) return True;
	return False;
}

ListaProds consListaProd(ListaProds lp, Produto p) {
    ListaProds novoNodo = initNodeLProds();
    novoNodo->prod = p;
    novoNodo->nxtProd = lp;
    lp = novoNodo;
    return lp;
}

/*Funcao auxiliar e recursiva
Percorre uma AVL que contem produtos e retorna uma ListaProds ordenada de forma crescente*/
ListaProds lpLetraAux(AVL a, ListaProds lp, char letra1, char letra2) {
    if(a) {
        /*Começamos por obter o elemento mais a direita possivel*/
        lp = lpLetraAux(getRight(a), lp, letra1, letra2);
        /*Agora tem de ser criada uma nova entrada que vai ser colocado a cabeça da lista*/
        ListaProds newNode = initNodeLProds();
        char codigo[32]; 
        sprintf(codigo, "%c%c%d ", letra1, letra2, getNode(a));
        newNode->prod = criaProd(codigo);
        newNode->nxtProd = lp;
        lp = newNode;
        /*Aqui vai se ao elemento anterior para descer até ao proximo elemento maior*/
        lp = lpLetraAux(getLeft(a), lp, letra1, letra2);
    }
    return lp;
}

ListaProds prodsToListaPorLetra(CatProds cp, char letter) {
    ListaProds lp = NULL;
    int i, cod = 26 * (letter - 'A');
    for(i = 25; i >= 0; i--) {
        AVL a = cp->catalogo[cod + i];
        lp = lpLetraAux(a, lp, letter, 'A' + i);
    } 
    return lp;
}
boolean existeProdLista(ListaProds lp, Produto p) {
    boolean r = False;
    ListaProds tmp = lp;
    while(tmp && !r)
        if(compareProduto(tmp->prod, p) == 0) 
            r = True;
    return r;
}

Produto getCabecaLProds(ListaProds lp) {
    return lp->prod;
}

ListaProds getProxLProds(ListaProds lp) {
    return lp->nxtProd;
}

/*Funcoes que fecham as listas e os catalogos
Fecha o catalogo de produtos incluindo as arvores AVL e os seus nodos*/
void closeCatProds(CatProds cp) {
    int i;
    if(cp) {
        for(i = 0; i < 676; i++) closeAVL(cp->catalogo[i]);
        free(cp);
        cp = NULL;
    }
}

/*Fecha todos os nodos da lista de produtos */
void closeListaProds(ListaProds lp) {
    ListaProds tmp;
    while(lp != NULL) {
        tmp = lp;
        closeProduto(lp->prod);
        lp = lp->nxtProd;
        free(tmp);
    }
    lp = NULL;
}