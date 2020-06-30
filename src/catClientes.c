#include "../include/catClientes.h"
#include "../include/AVL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>


/*Um array de 26 AVLs em que cada uma corresponde a uma letra do alfabeto*/
struct catClientes{
	AVL cat[26];
};

struct listaClientes{
	Cliente cliente;
	ListaClientes next;
};

/*Inicializa a estutura de dados onde iremos guardas os clientes, 
lê dum ficheiro esses clientes e guarda os na estrutura caso sejam validos*/
CatClientes initCatClientes(){
	int i;
	CatClientes cc = malloc(sizeof(struct catClientes));
	for(i = 0; i < 26; i++) cc->cat[i] = inicializaAVL();
	return cc;
}

/*Inicializa uma lista de clientes*/
ListaClientes initListaClientes(){
	ListaClientes lc = malloc(sizeof(struct listaClientes));
	return lc;
}

/*Recebe uma lista de clientes e um cliente
O cliente vai ser a cabeça da lista e asegunda lista vai ser a "prox" lista*/
ListaClientes consListaClientes(ListaClientes lc, Cliente c){
	ListaClientes temp = initListaClientes();
	temp->cliente = c;
	temp->next = lc;
	lc = temp;
	return lc;
}

/*Insere um cliente numa arvore AVL,
mas antes disso escolhe qual das AVL da estrutura de dados o guarda
neste caso basta fazer cod[0] - 'A'*/
CatClientes insereCliente(CatClientes cc, Cliente c) {
	char *cod = getCodCliente(c);
	int posCat = cod[0] - 'A';
	int clientNumber = atoi(cod + 1);
	cc->cat[posCat] = insereAVL(cc->cat[posCat], clientNumber);
	return cc;
}

/*Vê se um certo cliente está na estrutura de dados*/
boolean existeCliente(CatClientes cc, Cliente c) {
	char *cod = getCodCliente(c);
	int posCat = cod[0] - 'A';
	int clientNumber = atoi(cod + 1);
	if(procuraAVL(cc->cat[posCat], clientNumber)) return True;
	return False;
}

/*Query 5 - funcao que retorna a lista de clientes que participaram nas 3 filiais*/
ListaClientes getClientesDupTodasListas(ListaClientes lc[]) {
    ListaClientes r = NULL, tmp0 = lc[0], tmp1 = lc[1], tmp2 = lc[2];
	int comp01, comp02;
	while(tmp0 && tmp1 && tmp2) {
		comp01 = compareCliente(tmp0->cliente, tmp1->cliente);
		comp02 = compareCliente(tmp0->cliente, tmp2->cliente);
		if(comp01 == 0 && comp02 == 0) {
			Cliente clone = criaCliente(getCodCliente(tmp0->cliente)); 
			r = consListaClientes(r, clone);
			tmp0 = tmp0->next; tmp1 = tmp1->next; tmp2 = tmp2->next;
		}
		if(comp01 > 0) tmp1 = tmp1->next;
		if(comp02 > 0) tmp2 = tmp2->next;
		if(comp01 < 0 || comp02 < 0) tmp0 = tmp0->next; 
	}
    return r;
}


Cliente getCabecaLClientes(ListaClientes lc){
	return lc->cliente;
}

ListaClientes getProxLClientes(ListaClientes lc){
	return lc->next;
}

/*Fecha todos os nodos da lista de clientes*/
void closeListaClientes(ListaClientes lc) {
    ListaClientes tmp = NULL;
    while(lc) {
		closeCliente(lc->cliente);
        tmp = lc;
        lc = lc->next;
        free(tmp);
    }
	lc = NULL;
}

/*Fecha o catalogo dos clientes*/
void closeCatClientes(CatClientes cc) {
	int i;
	if(cc) {
    	for(i = 0; i < 26; i++) closeAVL(cc->cat[i]);
    	free(cc);
		cc = NULL;
	}
}