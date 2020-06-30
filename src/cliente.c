#include "../include/cliente.h"
#include "../include/myTypes.h"
#include "../include/MyString.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/*Dentro de um cliente a única coisa que vamos ter é o seu codigo de cliente que é uma String (ex:"A8798")*/
struct cliente{
    char* codCliente;
};

/*Recebe um codigo cliente e cria um cliente com este codigo*/
Cliente criaCliente(char* codCliente){
    Cliente cl = malloc(sizeof(struct cliente));
    cl->codCliente = dupString(strtok(codCliente, " \r\n"));
    return cl;
}

/*Se o c1 for menor que o c2, retorna negativo. Se for maior, retorna positivo.*/
int compareCliente(Cliente c1, Cliente c2) {
    char* aux1 = c1 -> codCliente;
    char* aux2 = c2 -> codCliente;

    return strcmp(aux1,aux2); 
}

/*Retorna o codigo do cliente*/
char* getCodCliente(Cliente c){
    return c->codCliente;
}

/*Verifica se um codigo de cliente é valido
Para ser valido o codigo tem de ter tamanho 5,
    o primeiro elemento tem de ser uma letra e
    os outros 4 têm de ser um numero.*/
boolean validateClient(Cliente c) {
    int i;
    boolean r = True;
    char *cod = getCodCliente(c);
    for(i = 0; i < 5; i++) {
        if((i == 0 && !isupper(cod[i])) || (i > 0 && !isdigit(cod[i]))) { 
            r = False;
            break;
        } 
    }
    return r;
}

void closeCliente(Cliente c){
    if(c) {
        free(c->codCliente);
        free(c);
        c = NULL;
    }
}