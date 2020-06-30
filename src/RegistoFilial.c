#include "../include/RegistoFilial.h"
#include "../include/produto.h"
#include "../include/catProds.h"
#include "../include/myTypes.h"
#include <stdlib.h>
#include <stdio.h>


struct registoFilial {
    Produto p;
    int quant;
    char np;
    Mes m; 
};

/*Assim, para cada cliente, associamos uma lista de registos*/
struct listaRegistosFilial {
    RegistoFilial registo;
    ListaRegistosFilial prox;
};

RegistoFilial initRegistoFilial() {
    RegistoFilial rf = malloc(sizeof(struct registoFilial));
    return rf;
}

ListaRegistosFilial initListaRegistosFilial() {
    ListaRegistosFilial lrf = NULL;
    return lrf;
}

RegistoFilial criaRegistoFilial(Produto prod, int q, char modo, int mes) {
    RegistoFilial rf = malloc(sizeof(struct registoFilial));
    rf->p = prod;
    rf->quant = q;
    rf->np = modo;
    rf->m = mes;
    return rf;
}

ListaRegistosFilial consListaRegistosFilial(RegistoFilial r, ListaRegistosFilial lrf) {
    ListaRegistosFilial aux = malloc(sizeof(struct listaRegistosFilial));
    aux->registo = r;
    aux->prox = lrf;
    lrf = aux;
    return lrf;
}

ListaRegistosFilial insereOrdInvQuantListaRegistosFilial(ListaRegistosFilial lrf, RegistoFilial rf) {
	ListaRegistosFilial nova = lrf, aux = NULL;
    int q = rf->quant;
	if (lrf) {
		while (nova && nova->registo->quant > q) { 
			aux = nova;
			nova = nova->prox;
		}
	    if (aux) aux->prox = consListaRegistosFilial(rf, nova);
		else lrf = consListaRegistosFilial(rf, lrf);		
	}
	else lrf = consListaRegistosFilial(rf, lrf);
	return lrf;
}


ListaRegistosFilial insereOrdQuantListaRegistosFilial(ListaRegistosFilial lrf, RegistoFilial rf) {
	ListaRegistosFilial nova = lrf, aux = NULL;
    int q = rf->quant;
	if (lrf) {
		while (nova && nova->registo->quant < q) { 
			aux = nova;
			nova = nova->prox;
		}
	    if (aux) aux->prox = consListaRegistosFilial(rf, nova);
		else lrf = consListaRegistosFilial(rf, lrf);		
	}
	else lrf = consListaRegistosFilial(rf, lrf);
	return lrf;
}

ListaRegistosFilial concatListaRegistosFilial(ListaRegistosFilial l1, ListaRegistosFilial l2) {
    ListaRegistosFilial tmp = l1;
    if(l1){
        while(tmp->prox)
            tmp = tmp->prox;
        tmp->prox = l2;
    } else l1 = l2;
    return l1;
}

ListaRegistosFilial filtraRegistosMes(ListaRegistosFilial lrf, Mes m) {
    ListaRegistosFilial tmp = lrf, nova = NULL;
    while(tmp) {
        if (tmp->registo->m == m) 
            nova = consListaRegistosFilial(tmp->registo, nova);
        tmp = tmp->prox;
    }
    lrf = nova;
    return lrf;
}

int sizeListaRegistos(ListaRegistosFilial lrf) {
    ListaRegistosFilial aux = lrf;
    int size = 0;
    while(aux) {
        size++;
        aux = aux->prox;
    }
    return size;
}

/*A partir da lista dos N produtos mais vendidos, a cada registo vê se já existe aquele na lista. 
Se existir, aumenta a quantidade do que já está na lista. Se não, se houver espaço insere na lista. Se já estiver
cheio, vê se pode trocar com o primeiro (que é o menos comprado da lista). Se trocar, volta a ordenar a lista. 
Se não, não faz nada*/
ListaRegistosFilial aumentaOuInsereRegistoListaRegistosFilial(RegistoFilial registo, ListaRegistosFilial lfinal, int size, int *n_clientes) {
    ListaRegistosFilial tmp = lfinal, nova = NULL;
    boolean r = False;
    while (tmp && !r) {
        if (!compareProduto(registo->p, tmp->registo->p)) {
                (*n_clientes)++;
                r = True;
                tmp->registo->quant += registo->quant;
        }
        tmp = tmp->prox;           
    }
    
    if (r) { /*significa que existe um registo já*/
        tmp = lfinal;
        while(tmp) {
            nova = insereOrdQuantListaRegistosFilial(nova, tmp->registo);
            tmp = tmp->prox;
        }
        lfinal = nova;
    }
    else if (sizeListaRegistos(lfinal) < size) 
        lfinal = insereOrdQuantListaRegistosFilial(lfinal, registo);
    else {
        tmp = lfinal;
        if (registo->quant > tmp->registo->quant) {
            tmp->registo->p = registo->p;
            tmp->registo->quant = registo->quant;
            lfinal = insereOrdQuantListaRegistosFilial(lfinal->prox, tmp->registo);
        }
    }
    return lfinal;
}

/*Dado uma lista de registos de um certo cliente e uma lista (que será a lista final para os N produtos mais
vendidos), percorre a lista e vê se algum registo lhe interessa para inserir*/
ListaRegistosFilial insereRegistoListaNComp(ListaRegistosFilial lrf, ListaRegistosFilial lfinal, int size, int *n_clientes) {
    ListaRegistosFilial tmp = lrf;
    int i = 0;
    if (!lfinal) {
        while (i < size && tmp) {
            lfinal = consListaRegistosFilial(tmp->registo, lfinal);
            (*n_clientes)++;
            tmp = tmp->prox;
            i++;
        }
    } 
    else {
        while(tmp) {
            lfinal = aumentaOuInsereRegistoListaRegistosFilial(tmp->registo, lfinal, size, n_clientes);
            tmp = tmp->prox;
        }
    }
    return lfinal;
}

ListaProds getListaProdsConsListaRegF(ListaRegistosFilial lrf) {
    ListaRegistosFilial tmp = lrf;
    ListaProds lp = NULL;
    while(tmp) {
        lp = consListaProd(lp, tmp->registo->p);
        tmp = tmp->prox;
    }
    return lp;
}

ListaProds getListaProdsOrdInvQuantDesc (ListaRegistosFilial lrf, int limit) {
    ListaRegistosFilial aux = NULL, tmp = lrf;
    ListaProds lp = NULL;
    int i = 0;
    while(tmp) {
        aux = insereOrdInvQuantListaRegistosFilial(aux, tmp->registo);
        tmp = tmp->prox;
    }
    while(aux && i < limit) {
        lp = consListaProd(lp, aux->registo->p);
        i++;
        aux = aux->prox;
    } 
    return lp;
}

ListaProds getConsListaProds(ListaRegistosFilial lrf) {
    ListaRegistosFilial aux = lrf;
    ListaProds lp = NULL;
    while(aux) {
        lp = consListaProd(lp, aux->registo->p);
        aux = aux->prox;
    }
    return lp;
}

ListaProds getListaProdsOrdQuantDesc (ListaRegistosFilial lrf) {
    ListaRegistosFilial aux = NULL, tmp = lrf;
    ListaProds lp = NULL;
    while(tmp) {
        aux = insereOrdQuantListaRegistosFilial(aux, tmp->registo);
        tmp = tmp->prox;
    }
    while(aux) {
        lp = consListaProd(lp, aux->registo->p);
        aux = aux->prox;
    } 
    return lp;
}
/*Query7*/
int* getRegistosFilialCliente(ListaRegistosFilial lrf){
    int* ret = malloc(sizeof(int) * 12);
    int i;
    for(i = 0; i < 12; i++) ret[i] = 0;
    while(lrf){
        RegistoFilial rf = lrf->registo;
        int m = rf->m;
        int q = rf->quant;

        ret[m] += q;

        lrf = lrf->prox;
    }
    return ret;
}

/*-----------------------------------------------Query12---------------------------------------------------------*/
ListaRegistosFilial insereOrdProdListaRegistosFilial(ListaRegistosFilial lrf, RegistoFilial rf) {
	ListaRegistosFilial nova = lrf, aux = NULL;
	if (lrf) {
		while (nova && compareProduto(lrf->registo->p, rf->p) < 0) { 
			aux = nova;
			nova = nova->prox;
		}
	    if (aux) aux->prox = consListaRegistosFilial(rf, nova);
		else lrf = consListaRegistosFilial(rf, lrf);		
	} /*Tenho que ver melhor esta*/
	else lrf = consListaRegistosFilial(rf, lrf);
	return lrf;
}

ListaRegistosFilial ordenaPorProd(ListaRegistosFilial lrf) {
    ListaRegistosFilial ret = NULL;
    ListaRegistosFilial aux = lrf;
    while(aux) {
        ret = insereOrdProdListaRegistosFilial(ret, aux->registo);
        aux = aux->prox;
    }
    lrf = ret;
    return lrf;
}

ListaRegistosFilial insereOrdQuantListaRegistosFilialI(ListaRegistosFilial lrf, RegistoFilial rf) {
	ListaRegistosFilial nova = lrf, aux = NULL;
    int q = rf->quant;
	if (lrf) {
		while (nova && nova->registo->quant > q) { 
			aux = nova;
			nova = nova->prox;
		}
	    if (aux) aux->prox = consListaRegistosFilial(rf, nova);
		else lrf = consListaRegistosFilial(rf, lrf);		
	}
	else lrf = consListaRegistosFilial(rf, lrf);
	return lrf;
}

ListaRegistosFilial ordenaPorQuant(ListaRegistosFilial lrf){
    ListaRegistosFilial ret = NULL;
    ListaRegistosFilial aux = lrf;
    while(aux){
        ret = insereOrdQuantListaRegistosFilialI(ret, aux->registo);
        aux = aux->prox;
    }
    return ret;
}

ListaRegistosFilial removeRepetidos(ListaRegistosFilial lrf) {
    ListaRegistosFilial aux = lrf, ret = NULL;
    while(aux) {
        RegistoFilial r = aux->registo;
        aux = aux->prox;
        if(aux) {
            while(aux && (compareProduto(r->p, aux->registo->p) == 0)) {
                r->quant += aux->registo->quant;
                aux = aux->prox;
            }
        }
        ret = consListaRegistosFilial(r, ret);
    }
    lrf = ret;
    return lrf;
}

ListaProds pegaProdutos(ListaRegistosFilial lr, int limit){
    ListaRegistosFilial aux = lr;
    ListaProds lp = NULL;
    int i = 0;
    while (aux && i < limit){
        lp = consListaProd(lp, aux->registo->p);
        aux = aux->prox;
        i++;
    }
    return lp;
}
/*---------------------------------------------------------------------------------------------------------------*/
/*q9*/
boolean regCompraProd(ListaRegistosFilial lrf, Produto p, int* compN, int* compP) {
    ListaRegistosFilial tmp = lrf;
    boolean r = False;
    while(tmp) {
        RegistoFilial reg = tmp->registo;
        if(compareProduto(p, reg->p) == 0) {
            r = True;
            if(reg->np == 'N') (*compN)++;
            else (*compP)++;
        }
        tmp = tmp->prox;
    }
    return r;
}

/*Query11 - auxiliar*/
ListaRegistosFilial swapListaRegistos(ListaRegistosFilial l) {
    ListaRegistosFilial ant = NULL, tmp = l, next = NULL;
    while (tmp) {
        next = tmp->prox; 
        tmp->prox = ant;
        ant = tmp;
        tmp = next;
    }
    l = ant;
    return l;
}

/*Query11 - auxiliar*/
ListaProds delimitaLista(ListaRegistosFilial l, int limit) {
    ListaProds lp = NULL;
    ListaRegistosFilial tmp = l;
    int i;
    for (i = 0; i < limit && tmp->prox; i++) 
        tmp = tmp->prox;
    closeListaRegistosFilial(tmp->prox);
    tmp->prox = NULL;
    lp = getConsListaProds(l);
    return lp;
}

/*Query11 - auxiliar*/
ListaRegistosFilial reordenaListaRegistosFilial(ListaRegistosFilial lrf) {
    ListaRegistosFilial tmp = lrf, next = NULL, ant = NULL, firstElem = NULL;
    while(tmp->prox && tmp->registo->quant < tmp->prox->registo->quant) {
        if (!ant) firstElem = tmp->prox;
        ant = tmp->prox;
        next = tmp->prox;
        tmp->prox = next->prox;
        next->prox = tmp;
        if (ant) ant->prox = tmp->prox;
    }
    lrf = firstElem;
    return lrf;
}

/*Query11 - auxiliar*/
ListaRegistosFilial aumentaOuSwapOrdLRegFilial(ListaRegistosFilial mainLista, RegistoFilial rg) {
    if (mainLista) {
        ListaRegistosFilial mainAux = mainLista;
        int r = -1;
        while(mainAux && r) {
            r = compareProduto(mainAux->registo->p, rg->p);
            if (r == 0) {
                mainAux->registo->quant += rg->quant;
                mainAux = reordenaListaRegistosFilial(mainAux);
            }
            mainAux = mainAux->prox;
        }
        if (r) {
            mainLista = consListaRegistosFilial(rg, mainLista);
            /*mainLista = reordenaListaRegistosFilial(mainLista);*/
        }
    } else mainLista = consListaRegistosFilial(rg, mainLista);
    return mainLista;
}

/*Query 11*/
ListaRegistosFilial getRegistosListaNProds(ListaRegistosFilial mainLista, ListaRegistosFilial l) {
    ListaRegistosFilial lAux = l;
    while(lAux) {
        mainLista = aumentaOuSwapOrdLRegFilial(mainLista, lAux->registo);
        lAux = lAux->prox;
    }
    return mainLista;
}

void closeRegistoFilial(RegistoFilial rf) {
    closeProduto(rf->p);
    free(rf);
}

void closeListaRegistosFilial(ListaRegistosFilial l) {
    ListaRegistosFilial tmp = NULL;
    while(l) {
		closeRegistoFilial(l->registo);
        tmp = l;
        l = l->prox;
        free(tmp);
    }
    l = NULL;
}