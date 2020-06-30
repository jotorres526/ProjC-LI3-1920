#include "../include/filial.h"
#include "../include/produto.h"
#include "../include/catProds.h"
#include "../include/cliente.h"
#include "../include/AVLRegistos.h"
#include "../include/RegistoFilial.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct filial {
    AVLRegistos cat[26];
};

Filial initFilial() {
    int i;
    Filial f = malloc(sizeof(struct filial));
    for(i = 0; i < 26; i++) 
        f->cat[i] = initAVLRegistos();
    return f;
}

Filial insereClienteFilial(Cliente c, Filial f) {
    char *codCliente = getCodCliente(c);
    int posCat = codCliente[0] - 'A';
    int key = atoi(codCliente + 1);
    f->cat[posCat] = insereAVLRegistos(f->cat[posCat], key, NULL);
    return f;
}

Filial insereRegistoFilial(Filial f, Cliente c, Produto prod, int q, char modo, int mes) {
    RegistoFilial rf = criaRegistoFilial(prod, q, modo, mes);
    char* codCliente = getCodCliente(c);
    int posCat = codCliente[0] - 'A';
    int key = atoi(codCliente + 1);
    adicionaRegistoFilialAVL(f->cat[posCat], key, rf);
    return f;
}

ListaRegistosFilial getListaRegistosFilialClienteMes(Filial f, Cliente c, Mes m) {
    char* codCliente = getCodCliente(c);
    int posCat = codCliente[0] - 'A';
    int key = atoi(codCliente + 1);
    ListaRegistosFilial lrf = procuraRegisto(f->cat[posCat], key);
    lrf = filtraRegistosMes(lrf, m-1);
    return lrf;
}

/*Q5*/
ListaClientes getCompradoresFilial(Filial f) {
    ListaClientes r = NULL;
    int i;
    for(i = 0; i < 26; i++)
        r = clientesCompradores(f->cat[i], r, 'A' + i);
    return r;
}

/*q6*/
ListaClientes getNaoCompradoresFilial(Filial f) {
    ListaClientes r = NULL;
    int i;
    for(i = 0; i < 26; i++)
        r = clientesNaoCompradores(f->cat[i], r, 'A' + i);
    return r;
}

/*Query7*/
int* getRegistosCliente(Filial f, char* codCliente) {
    int posCat = codCliente[0] - 'A';
    int key = atoi(codCliente + 1);
    void* lrf = procuraRegisto(f->cat[posCat], key);
    int* arr = getRegistosFilialCliente(lrf); 
    return arr;
}

/*Query11*/
ListaRegistosFilial getTopNProdsFilial(Filial f, ListaRegistosFilial mainList) {
    int i;
    for(i = 0; i < 26; i++)
        mainList = getTopNProdutosAVLRegistos(f->cat[i], mainList);
    return mainList;
} 


/*---------------------------------------------------Query12-------------------------------------------------------------*/
ListaRegistosFilial getClienteTopProfitProductsFilial(Filial f, char* clientID){
    int pos = clientID[0] - 'A';
    int key = atoi(clientID + 1);
    ListaRegistosFilial lr = procuraRegisto(f->cat[pos], key);
    return lr;
}

/*q9*/
ListaClientes clientesProduto(Filial f, Produto p, int* compN, int* compP) {
    ListaClientes r = NULL;
    int i;
    for(i = 25; i >= 0; i--)
        r = procuraCompradoresProduto(f->cat[i], r, 'A' + i, p, compN, compP);
    return r;
}

void closeFilial(Filial f) {
    int i;
    for (i = 0; i < 26; i++) 
        closeAVLFilial(f->cat[i]);
    free(f);
    f = NULL;
}