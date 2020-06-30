#include "../include/faturacao.h"
#include "../include/catProds.h"
#include "../include/cliente.h"
#include "../include/AVLRegistos.h"
#include "../include/RegistoFat.h"
#include <stdlib.h>
#include <stdio.h>

struct faturacao{
    AVLRegistos cat[676];
};

Faturacao initFaturacao() {
    int i;
    Faturacao f = malloc(sizeof(struct faturacao));
    for(i = 0; i < 676; i++) 
        f->cat[i] = initAVLRegistos(); 
    return f;
}

Faturacao insereRegistoFaturacao(Faturacao f, Produto p) {
    RegistoFaturacao rf = initRegistoFaturacao();
    char *codProd = getCodProd(p);
    int posCat = 26 * (codProd[0] - 'A') + (codProd[1] - 'A');
    int key = atoi(codProd + 2);
    f->cat[posCat] = insereAVLRegistos(f->cat[posCat], key, rf);
    return f;
}


Faturacao aumentaFaturacao(Faturacao f, Produto p, float preco, int quant, int filial, int m, char np) {
    char *codProd = getCodProd(p);
    int posCat = 26 * (codProd[0] - 'A') + (codProd[1] - 'A');
    int key = atoi(codProd + 2);
    AVLRegistos a = f->cat[posCat];
    RegistoFaturacao rf = procuraRegisto(a, key);
    aumentaRegisto(rf, preco, quant, filial, m, np);
    return f;
}

/*Query 3 - funcao que retorna o total faturado de um produto num certo mes*/
float** fatPorProdutoMes(Faturacao fat, char* codProd, int m) {
   float** arr;
   int pos = 26 * (codProd[0] - 'A') + (codProd[1] - 'A');
   AVLRegistos a = fat->cat[pos];
   RegistoFaturacao rf = procuraRegisto(a, atoi(codProd + 2));
   arr = getValoresRegistos(rf, m);
   return arr;
}

/*retorna uma lista ordenada de produtos que nunca foram compraods em nenhuma filial*/
ListaProds prodsFaturNuncaComprados(Faturacao f, ListaProds r, int branchID) {
    int i;
    char l1, l2;
    l1 = l2 = 'Z';
    for(i = 675; i >= 0; i--) {
        r = produtosNaoComprados(f->cat[i], r, branchID, l1, l2);
        if(l2 == 'A') {
            l2 = 'Z';
            l1--;
        } else l2--;
    }
    return r;
}

/*Query8
Inicializa-se um array[2] de long logn ints pois para alguns casos pode obter valores gigantes, inicializa-se os a 0.
Percorremos a lista da Faturação e verificamos se o mes do registo da compra é entre o minMonth e o maxMonth.
Caso esteja neste intervalo, adiciona-se a arr[0] a quantidade nesse registo, ou seja, em arr[0] vamos ter o numero total de compras,
depois adiciona-se a arr[1] a multiplicaçao da quantidade nessa registo com o preço, em arr[1] vai estar o total faturado.
No fim retorna se o arr.*/
long double* regAndFatEntreMeses(Faturacao f, int minMonth, int maxMonth){
    int i;
    long double* arr = malloc(sizeof(long double) * 2);
    arr[0] = 0;
    arr[1] = 0;
    for(i = 0; i < 26*26; i++){
        long double *temp = fatAndNumVendas(f->cat[i], minMonth,maxMonth);
        arr[0] += temp[0];
        arr[1] += temp[1];
        free(temp);
    }
    return arr;
}

/*Query11*/
int getNumRegVendaFatFilial(Faturacao f, char* p, int branch) {
    int r = 0,key;
    int posCat = 26 * (p[0] - 'A') + (p[1] - 'A');
    key = atoi(p + 2);
    RegistoFaturacao rf = procuraRegisto(f->cat[posCat], key);
    r = getRegVendaProdFaturacaoAux(rf, branch);
    return r;
}

void closeFaturacao(Faturacao f) {
    int i;
    for (i = 0; i < 676; i++) 
        closeAVLFaturacao(f->cat[i]);
    free(f);
    f = NULL;
}