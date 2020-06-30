#include "../include/AVL.h"
#include "../include/catProds.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum balance {Left, Equal, Right} Balance;

struct avl {
    int key;
    AVL left;
    AVL right;
    Balance bl;
    boolean cresceu;
};

/*Inicializa uma arvore com 1 nodo e ambos os filhos vazios;*/
AVL inicializaAVL() {
	AVL a = NULL;
	return a;
}

/*Faz uma rotação de um nodo para a direita*/
AVL rodaDir(AVL a) {
    AVL aux = a->left;
    a->left = aux->right;
    aux->right = a;
    a = aux;
    return a;
}

/*Faz uma rotação de um nodo para a esquerda*/
AVL rodaEsq(AVL a) {
    AVL aux = a->right;
    a->right = aux->left;
    aux->left = a;
    a = aux;
    return a;
}

AVL balancaEsq(AVL a) {
    /*Verificar se precisa de uma rotaçao simples ou dupla
    Quando a sub-arvore da esquerda está "tilted" à esquerda necessita apenas de uma rotaçao simples*/
    if(a->left->bl == Left) {
        a = rodaDir(a);
        a->bl = Equal;
        a->right->bl = Equal;
    }
    /*Caso em que seja necessario fazer rotaçao dupla ou seja
    Quando a sub-arvore da esquerda está tilted a direita*/
    else { 
        a->left = rodaEsq(a->left);
        a = rodaDir(a);
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

AVL balancaDir(AVL a) {
    /*Verificar se precisa de uma rotaçao simples ou dupla
    Quando a sub-arvore da direita está "tilted" à direita necessita apenas de uma rotaçao simples*/
    if(a->right->bl == Right) {
        a = rodaEsq(a);
        a->bl = Equal;
        a->left->bl = Equal;
    }
    /*Caso em que seja necessario fazer rotaçao dupla ou seja
    Quando a sub-arvore da direita está tilted a esquerda*/
    else { 
        a->right = rodaDir(a->right);
        a = rodaEsq(a);
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

/*Insere um nodo na AVL*/
AVL insereAVL(AVL a, int node) {
    /*inserir nodo*/
    if(!a) { 
        a = malloc(sizeof(struct avl));
        a->key = node;
        a->right = a->left = NULL;
        a->bl = Equal;
        a->cresceu = True;
    } else if(node > a->key) {
        a->right = insereAVL(a->right, node);
        if(a->cresceu) {
            switch (a->bl) {
                case Equal:
                    a->bl = Right;
                    a->cresceu = True;
                    break;
                case Right:
                    a = balancaDir(a);
                    a->cresceu = False;
                    break;
                case Left:
                    a->bl = Equal;
                    a->cresceu = False;
                    break;
            }
        }
    } else {
        a->left = insereAVL(a->left, node);
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
                    a = balancaEsq(a);
                    a->cresceu = False;
                    break;
            }
        }
    }
    return a;
}

/*Procura de um node na AVL*/
boolean procuraAVL(AVL a, int node){
    int r = False;
    if (a) {
        if (node == a->key) r = True;
        else if (node > a->key) r = procuraAVL(a->right, node);
        else r = procuraAVL(a->left, node);
    }
    return r;
}

AVL getRight(AVL a){
    return a->right;
}

AVL getLeft(AVL a){
    return a->left;
}

int getNode(AVL a){
    return a->key;
}

void closeAVL(AVL a) {
    if(a != NULL) {
        closeAVL(a->left);
        closeAVL(a->right);
        free(a);
        a = NULL;
    } 
}