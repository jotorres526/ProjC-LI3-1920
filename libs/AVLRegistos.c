#include "../include/AVLRegistos.h"
#include "../include/RegistoFat.h"
#include "../include/catProds.h"
#include "../include/RegistoFilial.h"

#include <stdlib.h>
#include <stdio.h>

typedef enum balance {Left, Equal, Right} Balance;

struct avlRegistos{
    int key;
    void* registo;
    AVLRegistos left;
    AVLRegistos right;
    Balance bl;
    boolean cresceu;
};

AVLRegistos initAVLRegistos(){
    AVLRegistos af = NULL;
    return af;
}

/*Faz uma rotação de um nodo para a direita*/
AVLRegistos rodaDirRegistos(AVLRegistos a) {
    AVLRegistos aux = a->left;
    a->left = aux->right;
    aux->right = a;
    a = aux;
    return a;
}

/*Faz uma rotação de um nodo para a esquerda*/
AVLRegistos rodaEsqRegistos(AVLRegistos a) {
    AVLRegistos aux = a->right;
    a->right = aux->left;
    aux->left = a;
    a = aux;
    return a;
}

AVLRegistos balancaEsqRegistos(AVLRegistos a) {
    /*Verificar se precisa de uma rotaçao simples ou dupla
    Quando a sub-arvore da esquerda está "tilted" à esquerda necessita apenas de uma rotaçao simples*/
    if(a->left->bl == Left) {
        a = rodaDirRegistos(a);
        a->bl = Equal;
        a->right->bl = Equal;
    }
    /*Caso em que seja necessario fazer rotaçao dupla ou seja
    Quando a sub-arvore da esquerda está tilted a direita*/
    else { 
        a->left = rodaEsqRegistos(a->left);
        a = rodaDirRegistos(a);
        switch(a->bl) {
            case Equal:
                a->left->bl  = Equal;
                a->right->bl = Equal;
                break;
            case Left:
                a->left->bl  = Left;
                a->right->bl = Equal;
                break;
            case Right:
                a->left->bl  = Right;
                a->right->bl = Equal;
                
        }
        a->bl = Equal;
    }
    return a;
}

AVLRegistos balancaDirRegistos(AVLRegistos a) {
    /*Verificar se precisa de uma rotaçao simples ou dupla
    Quando a sub-arvore da direita está "tilted" à direita necessita apenas de uma rotaçao simples*/
    if(a->right->bl == Right) {
        a = rodaEsqRegistos(a);
        a->bl = Equal;
        a->left->bl = Equal;
    }
    /*Caso em que seja necessario fazer rotaçao dupla ou seja
    Quando a sub-arvore da direita está tilted a esquerda*/
    else { 
        a->right = rodaDirRegistos(a->right);
        a = rodaEsqRegistos(a);
        switch(a->bl) {
            case Equal:
                a->left->bl  = Equal;
                a->right->bl = Equal;
                break;
            case Left:
                a->left->bl = Equal;
                a->right->bl = Right;
                break;
            case Right:
                a->right->bl = Left;
                a->left->bl = Equal;
        }
        a->bl = Equal;
    }
    return a;
}

/*Insere um nodo na AVLFat*/
AVLRegistos insereAVLRegistos(AVLRegistos a, int key, void* rf){
    /*inserir nodo*/
    if(!a) { 
        a = malloc(sizeof(struct avlRegistos));
        a->key = key;
        a->registo = rf;
        a->right = a->left = NULL;
        a->bl = Equal;
        a->cresceu = True;
    } else if(key > a->key) {
        a->right = insereAVLRegistos(a->right, key, rf);
        if(a->cresceu) {
            switch (a->bl) {
                case Equal:
                    a->bl = Right;
                    a->cresceu = True;
                    break;
                case Right:
                    a = balancaDirRegistos(a);
                    a->cresceu = False;
                    break;
                case Left:
                    a->bl = Equal;
                    a->cresceu = False;
                    break;
            }
        }
    } else {
        a->left = insereAVLRegistos(a->left, key, rf);
        if(a->cresceu) {
            switch (a->bl) {
                case Equal:
                    a->bl = Left;
                    a->cresceu = True;
                    break;
                case Right:
                    a->bl = Equal;
                    a->cresceu = False;
                    break;
                case Left:
                    a = balancaEsqRegistos(a);
                    a->cresceu = False;
                    break;
            }
        }
    }
    return a;
}

void* procuraRegisto(AVLRegistos a, int key) {
    void* r = NULL;
    if (a) {
        if (key == a->key) r = a->registo;
        else if (key > a->key) r = procuraRegisto(a->right, key);
        else r = procuraRegisto(a->left, key);
    }
    return r;
}

void adicionaRegistoFilialAVL(AVLRegistos a, int key, void* registo) {
    if (a) {
        if (key == a->key) 
            a->registo = consListaRegistosFilial(registo, a->registo);
        else if (key > a->key) adicionaRegistoFilialAVL(a->right, key, registo);
        else adicionaRegistoFilialAVL(a->left, key, registo);
    }
}

long double* fatAndNumVendas(AVLRegistos a, int minMonth, int maxMonth){
    long double* arr = malloc(sizeof(long double) * 2);
    arr[0] = 0;
    arr[1] = 0;
    if(a){
        long double* temp = vendasFaturadoRegisto(a->registo, minMonth, maxMonth);
        arr[0] += temp[0]; arr[1] += temp[1];
        /*------------------------------------------------------------*/
        long double *aux = fatAndNumVendas(a->right, minMonth, maxMonth);
        arr[0] += aux[0]; arr[1] += aux[1];
        long double* aux1 = fatAndNumVendas(a->left, minMonth, maxMonth);
        arr[0] += aux1[0]; arr[1] += aux1[1];
        free(temp);
        free(aux);
        free(aux1);
    }
    return arr;
}

ListaProds produtosNaoComprados(AVLRegistos ar, ListaProds lp, int branchID, char l1, char l2) {
    if(ar) {
        /*buscar maior elem*/
        lp = produtosNaoComprados(ar->right, lp, branchID, l1, l2);
        RegistoFaturacao rf = ar->registo;
        if(!isComprado(rf, branchID)) {
            char cod[32];
            sprintf(cod, "%c%c%d ", l1,l2, ar->key);
            lp = consListaProd(lp, criaProd(cod));
        }
        lp = produtosNaoComprados(ar->left, lp, branchID, l1, l2);
    }
    return lp;
}

ListaRegistosFilial percorreAVLProdsMaisComprados(AVLRegistos a, ListaRegistosFilial lfinal, int size, int* n_clientes) {
    AVLRegistos tmp = a;
    if (tmp) {
        ListaRegistosFilial lrf = tmp->registo;
        if (lrf) lfinal = insereRegistoListaNComp(lrf, lfinal, size, n_clientes);
        if (tmp->right) lfinal = percorreAVLProdsMaisComprados(tmp->right, lfinal, size, n_clientes);
        if (tmp->left) lfinal = percorreAVLProdsMaisComprados(tmp->left, lfinal, size, n_clientes);
    }
    return lfinal;
}

/*query 5*/
ListaClientes clientesCompradores(AVLRegistos ar, ListaClientes lc, char l) {
    if(ar) {
        lc = clientesCompradores(ar->left, lc, l);
        /*se o registo for nulo nao comprou nada*/
        if(ar->registo) {
            char cod[32];
            sprintf(cod, "%c%d ", l, ar->key);
            lc = consListaClientes(lc, criaCliente(cod));
        }
        lc = clientesCompradores(ar->right, lc, l);
    }
    return lc;
}


/*Q6*/
ListaClientes clientesNaoCompradores(AVLRegistos ar, ListaClientes lc, char l) {
    if(ar) {
        lc = clientesNaoCompradores(ar->left, lc, l);
        /*se o registo for nulo nao comprou nada*/
        if(ar->registo == NULL) {
            char cod[32];
            sprintf(cod, "%c%d ", l, ar->key);
            lc = consListaClientes(lc, criaCliente(cod));
        }
        lc = clientesNaoCompradores(ar->right, lc, l);
    }
    return lc;
}

/*Query11*/
ListaRegistosFilial getTopNProdutosAVLRegistos(AVLRegistos a, ListaRegistosFilial mainList) {
    if (a) {
        ListaRegistosFilial registo = a->registo;
        if (registo) mainList = getRegistosListaNProds(mainList,registo);
        if (a->right) mainList = getTopNProdutosAVLRegistos(a->right, mainList);
        if (a->left) mainList = getTopNProdutosAVLRegistos(a->left, mainList);
    }
    return mainList;
}

ListaClientes procuraCompradoresProduto(AVLRegistos ar, ListaClientes lc, char l, Produto p, int* compN, int* compP) {
    if(ar) {
        lc = procuraCompradoresProduto(ar->right, lc, l, p, compN, compP);
        if(regCompraProd(ar->registo, p, compN, compP)) {
            char cod[32];
            sprintf(cod, "%c%d ", l, ar->key);
            lc = consListaClientes(lc, criaCliente(cod));
        }
        lc = procuraCompradoresProduto(ar->left, lc, l, p, compN, compP);
    }
    return lc;
}

void closeAVLFaturacao(AVLRegistos a) {
    if(a) {
        free(a->registo);
        closeAVLFaturacao(a->left);
        closeAVLFaturacao(a->right);
        free(a);
        a = NULL;
    } 
}

void closeAVLFilial(AVLRegistos a) {
    if(a) {
        ListaRegistosFilial rf = a->registo;
        closeListaRegistosFilial(rf);
        closeAVLFilial(a->left);
        closeAVLFilial(a->right);
        free(a);
        a = NULL;
    } 
}