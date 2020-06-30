#include "../include/RegistoFat.h"
#include "../include/myTypes.h"

#include <stdlib.h>

struct registoFat {
    /*Faturaçao obtida dividida por mes, filial e se foi N ou P*/
    float fatMensalN[3][12];
    float fatMensalP[3][12];
    /*Registos feitos divididos por mes, filial e se foi N ou P*/
    int compraP[3][12];
    int compraN[3][12];
};

RegistoFaturacao initRegistoFaturacao(){
    RegistoFaturacao rf = malloc(sizeof(struct registoFat));
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 12; j++){
            rf->compraN[i][j] = 0;
            rf->compraP[i][j] = 0;
            rf->fatMensalN[i][j] = 0;
            rf->fatMensalP[i][j] = 0; 
        }
    return rf;
}

void aumentaRegisto(RegistoFaturacao rf, float preco, int quant, int filial, int m, char np){
    if(np == 'N') {
        rf->compraN[filial][m] ++;
        rf->fatMensalN[filial][m] += quant * preco;
    }
    else {
        rf->compraP[filial][m] ++;
        rf->fatMensalP[filial][m] += preco * quant;
    }
}

/*Query3*/
float** getValoresRegistos(RegistoFaturacao rf, int mes){
    int i;
    float** arr = malloc(sizeof(float*) * 4);
    for(i = 0; i < 4; i++) arr[i] = malloc(sizeof(float) * 3);
    for(i = 0; i < 3; i++){
        arr[0][i] = rf->fatMensalN[i][mes];
        arr[1][i] = rf->fatMensalP[i][mes];
        arr[2][i] = rf->compraN[i][mes];
        arr[3][i] = rf->compraP[i][mes];
    }
    return arr;
}

/*Query8*/
long double* vendasFaturadoRegisto(RegistoFaturacao rf, int minMonth, int maxMonth){
    int i, j;
    long double* arr = malloc(sizeof(long double) * 2);
    arr[0] = 0; arr[1] = 0;
    for(j = 0; j < 3; j++){
        for(i = minMonth; i < maxMonth + 1; i++){
            arr[0] += rf->compraP[j][i] + rf->compraN[j][i];
            arr[1] += rf->fatMensalP[j][i] + rf->fatMensalN[j][i];
        }
    }
    return arr;
}

/*Query11*/
int getRegVendaProdFaturacaoAux(RegistoFaturacao r, int branch) {
    int res = 0, i;
    for (i = 0; i < 12; i++) 
        res += r->compraN[branch][i] + r->compraP[branch][i];
    return res;
}

boolean isComprado(RegistoFaturacao rf, int branchID) {
    boolean r = False;
    int i, currFil = 0, max = 3;
    if(branchID != 0) { 
        max = 1;
        currFil = branchID - 1;
    } 
    while (max > 0 && !r) {
        for(i = 0; i < 12 && !r; i++) {
            if(rf->compraN[currFil][i] > 0 || rf->compraP[currFil][i] > 0) 
                r = True;
        }
        currFil++;
        max--;
    }        
    return r;
}

void closeResgistoFaturacao(RegistoFaturacao rf){
    free(rf);
}

























