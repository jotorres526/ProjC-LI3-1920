#include "../include/produto.h"
#include "../include/myTypes.h"
#include "../include/MyString.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct prod {
    char* codProd;
};

Produto criaProd(char* codProd) {
    Produto prod = malloc(sizeof(struct prod));
    prod->codProd = dupString(strtok(codProd, " \r\n"));
    return prod;
}

char* getCodProd(Produto p) {
    return p->codProd;
}

boolean isValidProd(Produto p) {
    int i;
    char* cod = getCodProd(p);
    boolean r = True;
    for(i = 0; i < 6; i++) {
        if (((i == 0 || i == 1) && !isupper(cod[i]))  || (i > 1 && !isdigit(cod[i]))) {
            r = False;
            break;
        }
    }
    return r;
}

/*Devolve 0 se forem iguais
menor que 0 se p2 > p1
maior que o se p1 > p2*/
int compareProduto(Produto p1, Produto p2){
    char *cod1 = p1->codProd;
    char *cod2 = p2->codProd;
    return strcmp(cod1,cod2);
}

void closeProduto(Produto p) {
    if(p) {
        free(p->codProd);
        free(p);
        p = NULL;
    }
}