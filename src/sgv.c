#include "../include/myTypes.h"
#include "../include/produto.h"
#include "../include/cliente.h"
#include "../include/filial.h"
#include "../include/faturacao.h"
#include "../include/sgv.h"
#include "../include/myTypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sgv {
    CatProds cp;
    CatClientes cc;
    Filial fil[3];
    Faturacao fact;
    int prodsLidos[2];
    int clntLidos[2];
    int salesLidas[2];
    char** files;
};
/*prod, preco, quant, np, cliente, mes, filial*/
boolean validaVenda(SGV sgv, char* prod, float preco, int quant, char np, char* cliente, int mes, int filial) {
    boolean r = False;
    Cliente c = criaCliente(cliente);
    Produto p = criaProd(prod);
    /*Temos de procurar os clientes e oos produtos dos catalogos... e nao apenas validar los*/
    if (existeCliente(sgv -> cc, c) && existeProd(sgv -> cp, p) &&
        (np == 'N' || np == 'P') && 
        preco >= 0.0 && preco <= 999.99 && 
        quant >= 1 && quant <= 200 &&
        mes >= 1 && mes <= 12 &&
        filial >= 1 && filial <= 3) {
            r = True;
        }
    closeCliente(c);
    closeProduto(p);
    return r;
}

void loadFileClientes(SGV sgv, FILE *fp) {
	char buffer[64];
    int i;
	if(fp){
		while(fgets(buffer, 64, fp)){
			Cliente c = criaCliente(buffer);
			if (validateClient(c)) {
                sgv->clntLidos[0]++;
                sgv->cc = insereCliente(sgv->cc, c);
                for(i = 0; i < 3; i++)
                    sgv->fil[i] = insereClienteFilial(c, sgv->fil[i]);
            }
            sgv->clntLidos[1]++;
			closeCliente(c);
		}
	}
}

void loadFileProdutos(SGV sgv, FILE *fp) {
    char buffer[64];
    if (fp) {
        while (fgets(buffer, 64, fp)) {
            Produto p = criaProd(buffer);
            if (isValidProd(p)){ 
                sgv->prodsLidos[0]++;
                sgv->cp = insereProd(sgv->cp, p);
                sgv->fact = insereRegistoFaturacao(sgv->fact, p);
            }
            sgv->prodsLidos[1]++;
            closeProduto(p);
        }
    }
}

void loadFileVenda(SGV sgv, FILE *fp) {
    int quant, mes, filial;
    float preco;
    char prod[32], cliente[32], buffer[64], np;
    if(fp) {
        while(fgets(buffer, 64, fp)) {
            int var = sscanf(buffer, "%s %f %d %c %s %d %d", prod, &preco, &quant, &np, cliente, &mes, &filial);
            if(var == 7 && validaVenda(sgv, prod, preco, quant, np, cliente, mes, filial)) {
                sgv->salesLidas[0]++;
                Cliente c = criaCliente(cliente);
                Produto p = criaProd(prod);
                Mes m = mes - 1; 
                sgv->fil[filial - 1] = insereRegistoFilial(sgv->fil[filial-1], c, p, quant, np, m);
                sgv->fact = aumentaFaturacao(sgv->fact, p, preco, quant, filial - 1, m, np);
                closeCliente(c);
            }
            sgv->salesLidas[1]++;
        }
    }
}

SGV loadSGVFromFiles(SGV sgv, char* dirSales, char* dirProds, char* dirClnts) {
    /*Abrir os 3 ficheiros*/
    FILE *fc, *fp, *fv; /*file clientes, produtos e vendas respectively*/
    fc = fopen(dirClnts, "r");
    sgv->files[0] = dirClnts;
    fp = fopen(dirProds, "r");
    sgv->files[1] = dirProds;
    fv = fopen(dirSales, "r");
    sgv->files[2] = dirSales;
    /*Carregar os dados para a estrutura*/
    if(fc && fp && fv){
        loadFileClientes(sgv, fc);
        loadFileProdutos(sgv, fp);
        loadFileVenda(sgv, fv);
        /*Fechar streams*/
        fclose(fp); fclose(fc); fclose(fv);
    }
    
    return sgv;
}

SGV initSGV(){
    int i;
    SGV sgv = malloc(sizeof(struct sgv));
    sgv->cp = initCatProds();
    sgv->cc = initCatClientes();
    for(i = 0; i < 3; i++) sgv->fil[i] = initFilial();
    sgv->fact = initFaturacao();
    sgv->files = malloc(sizeof(char*) * 3);
    for(i = 0; i < 2; i++){
        sgv->clntLidos[i] = 0;
        sgv->prodsLidos[i] = 0;
        sgv->salesLidas[i] = 0;
    }
    return sgv;
}

void destroySVG(SGV sgv) {
    int i;
    closeCatProds(sgv->cp);
    closeCatClientes(sgv->cc);
    for(i = 0; i < 3; i++) closeFilial(sgv->fil[i]);
    closeFaturacao(sgv->fact);
    free(sgv->files);
    free(sgv);
    sgv = NULL;
}


struct query9 {
    int comprasN;
    int comprasP;
    ListaClientes lista;
};

ListaClientes getListaClientesQ9(Query9 q) {
    return q->lista;
}

/*Retorna um array em que o inteiro na primeira posiçao corresponde às compras N
e o segundo às compras P*/
int* getComprasQ9(Query9 q) {
    int* arr = malloc(sizeof(int) * 2);
    arr[0] = q->comprasN;
    arr[1] = q->comprasP;
    return arr;
} 

void closeQuery9(Query9 q) {
    closeListaClientes(q->lista);
    free(q);
}

/*
struct query11 {
    ListaProds* l;
    int n_clients[3];
    int n_unidades[3];
};

ListaProds* getListaProdsQuery11(Query11 q) {
    return q->l;
}

int getNClientsQuery11(Query11 q, int i) {
    return q->n_clients[i];
}

int getNUnidadesQuery11(Query11 q, int i) {
    return q->n_unidades[i];
}
*/

/*Query13*/
int* getValoresFilesInfo(SGV sgv){
    int* arr = malloc(sizeof(int) * 6);
    arr[0] = sgv->clntLidos[0];
    arr[1] = sgv->clntLidos[1];
    arr[2] = sgv->prodsLidos[0];
    arr[3] = sgv->prodsLidos[1];
    arr[4] = sgv->salesLidas[0];
    arr[5] = sgv->salesLidas[1];
    return arr;
}

/*=============================QUERY ZONE=============================*/
/*Query2*/
ListaProds getProductsStartedByLetter(SGV sgv, char letter) {
    ListaProds lp;
    lp = prodsToListaPorLetra(sgv->cp, letter);
    return lp;
}
/*Query3*/
float** getProductSalesAndProfit(SGV sgv, char* productID, int month){
    float** arr;
    Produto p = criaProd(productID);
    if(existeProd(sgv->cp, p)){
        Faturacao f = sgv->fact;
        arr = fatPorProdutoMes(f, productID, month - 1);
    } else {
        arr = NULL;
    }
    closeProduto(p);
    return arr;
}
/*se o branchID for 0 é total*/
ListaProds getProductsNeverBought(SGV sgv, int branchID) {
    ListaProds r = NULL;
    r = prodsFaturNuncaComprados(sgv->fact, r, branchID);
    return r;
}
/*Query 5
Retornar a lista ordenada de clientes que fizeram compras nas 3 filiais*/
ListaClientes getClientsOfAllBranches(SGV sgv){
    ListaClientes r = NULL, lcfil[3];
    int i;
    for(i = 0; i < 3; i++) lcfil[i] = getCompradoresFilial(sgv->fil[i]);
    r = getClientesDupTodasListas(lcfil);
    for(i = 0; i < 3; i++) closeListaClientes(lcfil[i]);
    return r;
}
/*Query 6*/
int* getClientsAndProductsNeverBoughtCount(SGV sgv) {
    int *arr = malloc(sizeof(int) * 2), i;
    ListaProds lp = getProductsNeverBought(sgv, 0), tmplp = lp;
    ListaClientes allFil[3], dups, tmplc;
    for(i = 0; i < 3; i++) allFil[i] = getNaoCompradoresFilial(sgv->fil[i]);
    dups = getClientesDupTodasListas(allFil);
    tmplc = dups;
    arr[0] = arr[1] = 0;
    while(tmplc) {
        arr[0]++;
        tmplc = getProxLClientes(tmplc);
    }
    while(tmplp) {
        arr[1]++;
        tmplp = getProxLProds(tmplp);
    }
    for(i = 0; i < 3; i++) closeListaClientes(allFil[i]);
    closeListaClientes(dups);
    closeListaProds(lp);
    return arr;
}
/*Query7
Dado um codigo de cliente,
percorre-se as 3 filiais à procura dos registos deste cliente
Retorn um array onde as linhas corespondem à filial e as colunas ao mes*/
int** getProductsBoughtByClient(SGV sgv, char* clientID){
    Filial f1, f2, f3;
    int** matriz = malloc(sizeof(int*) * 3);
    f1 = sgv->fil[0];
    f2 = sgv->fil[1];
    f3 = sgv->fil[2];
    matriz[0] = getRegistosCliente(f1, clientID);
    matriz[1] = getRegistosCliente(f2, clientID);
    matriz[2] = getRegistosCliente(f3, clientID);
    return matriz;
}

/*Query8*/
long double* getSalesAndProfit(SGV sgv, int minMonth, int maxMonth){
    long double* arr = regAndFatEntreMeses(sgv->fact, minMonth - 1, maxMonth - 1);
    return arr;
}

/*Query9
Inicializa-se uma estrutura de dados para guardas os dado necessarios.
Depois chama-se uma função da filial que percorre a filial procurando
os registos do produto recebido como parametro.*/
Query9 getProductBuyers(SGV sgv, char* productID, int branch) {
    Query9 q = malloc(sizeof(struct query9));
    int i = 0, j = 0;
    Produto p = criaProd(productID);
    q->lista = clientesProduto(sgv->fil[branch], p, &i, &j);
    q->comprasN = i;
    q->comprasP = j;
    closeProduto(p);
    return q;
}

/*Query 10*/
ListaProds getClientFavoriteProducts(SGV sgv, char* clientID, int month) {
    ListaProds lp = NULL;
    ListaRegistosFilial listaRegistos = NULL, lrf[3];
    Cliente c = criaCliente(clientID);
    int i;
    for(i = 0; i < 3; i++) {
        lrf[i] = NULL;
        lrf[i] = getListaRegistosFilialClienteMes(sgv->fil[i], c, month);
    }
    listaRegistos = lrf[0];
    listaRegistos = concatListaRegistosFilial(listaRegistos, lrf[1]);
    listaRegistos = concatListaRegistosFilial(listaRegistos, lrf[2]);
    lp = getListaProdsOrdQuantDesc(listaRegistos);
    closeCliente(c);
    return lp;
}

/*Query 11*/
ListaProds getTopSelledProducts(SGV sgv, int limit) {
    ListaProds lp = NULL;
    ListaRegistosFilial mainList = NULL;
    int i;
    for (i = 0; i < 3; i++) 
       mainList = getTopNProdsFilial(sgv->fil[i], mainList);
    mainList = swapListaRegistos(mainList);
    lp = getConsListaProds(mainList);
    return lp;
}

/*Query12*/
ListaProds getClienteTopProfitProducts(SGV sgv, char* clientID, int limit) {
    ListaProds lp = NULL;
    ListaRegistosFilial lr = NULL, aux = NULL;

    lr = getClienteTopProfitProductsFilial(sgv->fil[0], clientID);
    aux = getClienteTopProfitProductsFilial(sgv->fil[1], clientID);
    /*concateno as*/
    lr = concatListaRegistosFilial(lr, aux);
    aux = getClienteTopProfitProductsFilial(sgv->fil[2], clientID);
    /*concateno outra vez*/
    lr = concatListaRegistosFilial(lr, aux);
    /*ordeno por produto*/
    lr = ordenaPorProd(lr);
    /*removo os repetidos*/
    lr = removeRepetidos(lr);
    /*ordeno por faturado*/
    lp = getListaProdsOrdInvQuantDesc(lr, limit);
    return lp;
}

/*Query13*/
char** getCurrentFilesInfo(SGV sgv){
    int i;
    char **ret = malloc(sizeof(char *) * 3);
    for(i = 0; i < 3; i++) ret[i] = sgv->files[i];
    return ret;
}
