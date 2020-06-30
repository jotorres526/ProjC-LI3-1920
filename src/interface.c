#include "../include/interface.h"
#include "../include/MyString.h"
#include "../include/myTypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define BUFF_SIZE 256

void printListaProds(ListaProds lp){
    int i, j = 0;
    char buf[64];
    Produto prodAtual;
    ListaProds tmp = lp;
    while(tmp) {
        for(i = 0; i <= 10 && tmp; i++){
            prodAtual = getCabecaLProds(tmp);
            printf(" | %s ", getCodProd(prodAtual));
            tmp = getProxLProds(tmp);
        }
        printf("|\n");
        j++;
        if(j > 100){
            printf("Enter para ver o resto\n");
            fgets(buf, BUFF_SIZE, stdin);
            j = 0;
        }
    }
}

void printListaClientes(ListaClientes lc){
    int i, j = 0;
    char buf[64];
    Cliente clntAtual;
    ListaClientes tmp = lc;
    while(tmp){
        for(i = 0; i <= 10 && tmp; i++){
            clntAtual = getCabecaLClientes(tmp);
            printf(" | %s ", getCodCliente(clntAtual));
            tmp = getProxLClientes(tmp);
        }
        printf("|\n");
        j++;
        if(j > 100){
            printf("Enter para ver o resto.\n");
            fgets(buf, BUFF_SIZE, stdin);
            j = 0;
        }
    }
}

/*Query1*/
SGV printQuery1(SGV sgv){
    char dirSales[BUFF_SIZE], dirProds[BUFF_SIZE], dirClients[BUFF_SIZE];
    printf("A fechar o SGV antigo... Por favor aguarde.\n");
    destroySVG(sgv);

    printf("Diretoria do ficheiro dos clientes:\n");
    fgets(dirClients, BUFF_SIZE, stdin);
    printf("Diretoria do ficheiro dos produtos:\n");
    fgets(dirProds, BUFF_SIZE, stdin);
    printf("Diretoria do ficheiro das vendas:\n");
    fgets(dirSales, BUFF_SIZE, stdin);

    char *cli = strtok(dirClients, "\n");
    char *prod = strtok(dirProds, "\n");
    char *sale = strtok(dirProds, "\n");

    printf("A ler os novos ficheiros..\n");
    sgv = initSGV();
    sgv = loadSGVFromFiles(sgv, sale, prod, cli);
    return sgv;
}

/*Query3*/
void printQuery3(SGV sgv, char* productID, int month){
    int i;
    float** arr;
    if(month <= 12 && month >= 1){
        arr = getProductSalesAndProfit(sgv, productID, month); 
        if(arr){
            printf("-------------------------------------------------\n");
            printf("Faturaçao Total por metodo \"Normal\":\n\t>Filial 1: %0.2f\n\t>Filial 2: %0.2f\n\t>Filial 3: %0.2f\n", arr[0][0], arr[0][1], arr[0][2]);
            printf("\tTotal: %0.2f\n", arr[0][0] + arr[0][1] + arr[0][2]);
            printf("-------------------------------------------------\n");
            printf("Faturaçao Total por metodo \"Promocao\":\n\t>Filial 1: %0.2f\n\t>Filial 2: %0.2f\n\t>Filial 3: %0.2f\n",arr[1][0], arr[1][1], arr[1][2]);
            printf("\tTotal: %0.2f\n", arr[1][0] + arr[1][1] + arr[1][2]);
            printf("-------------------------------------------------\n");
            printf("Numero Total de Registos por metodo \"Normal\":\n\t>Filial 1: %0.f\n\t>Filial 2: %0.f\n\t>Filial 3: %0.f\n",arr[2][0], arr[2][1], arr[2][2]);
            printf("\tTotal: %0.f\n", arr[2][0] + arr[2][1] + arr[2][2]);
            printf("-------------------------------------------------\n");
            printf("Numero Total de Registos por metodo \"Promocao\":\n\t>Filial 1: %0.f\n\t>Filial 2: %0.f\n\t>Filial 3: %0.f\n",arr[3][0], arr[3][1], arr[3][2]);
            printf("\tTotal: %0.f\n", arr[3][0] + arr[3][1] + arr[3][2]);
            printf("-------------------------------------------------\n");
            for(i = 0; i < 4; i++) free(arr[i]);
            free(arr);
        }else {
            printf("Cliente Invalido!\n");
        }
    } else {
        printf("Mês invalido!\n");
    }
}

/*query 4*/
void printQuery4(SGV sgv, int branchID) {
    ListaProds lp = getProductsNeverBought(sgv, branchID);
    ListaProds tmp = lp;
    Produto prodAtual = NULL;
    int i = 0;
    while(tmp) {
        prodAtual = getCabecaLProds(tmp);
        printf("> %s\n", getCodProd(prodAtual));
        tmp = getProxLProds(tmp);
        i++;
    }
    printf("Numero de produtos nao comprados: %d\n", i);
    closeListaProds(lp);
}

/*Query 5*/
void printQuery5(SGV sgv) {
    ListaClientes lc = getClientsOfAllBranches(sgv);
    printListaClientes(lc);
    closeListaClientes(lc);
}

/*Query6*/
void printQuery6(SGV sgv) {
    int* nums = getClientsAndProductsNeverBoughtCount(sgv);
    printf("Num clientes que nao efetuaram nenhuma compra: %d\n", nums[0]);
    printf("Num de produtos nunca comprados: %d\n", nums[1]);
    free(nums);
}


/*Query7*/
void printQuery7(SGV sgv, char* clientID){
    int total = 0, t, i, j;
    int** mat = getProductsBoughtByClient(sgv, clientID);
    printf(" ----------------------------------------------------------------------------------------------------------\n");
    printf(" | Filial |  Jan  |  Fev  |  Mar  |  Abr  |  Mai  |  Jun  |  Jul  |  Ago  |  Set  |  Out  |  Nov  |  Dez  |\n");
    printf(" ----------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < 3; i++){
        printf(" |   %d    |", i+1);
        for (j = 0; j < 12; j++){
            t = mat[i][j];
            total += t;
            if(t/1000 > 0) printf(" %d  |", t);
            else if(t/100 > 0) printf("  %d  |", t);
            else if (t/10 > 0) printf("  %d   |", t);
            else printf("   %d   |", t);
        }
        printf("\n");
    }
    printf(" ----------------------------------------------------------------------------------------------------------\n");
    printf(" Quantidade de Produtos comprados: %d\n\n", total);
    
    for (i = 0; i < 3; i++){
        free(mat[i]);
    }
    free(mat);
}
/*Query8*/
void printQuery8(SGV sgv, int minMonth, int maxMonth){
    long double* arr = getSalesAndProfit(sgv, minMonth, maxMonth);
    printf("--------------------------------------------------------------------------------\n");
    printf("Total Faturado entre %s e %s: %0.2Lf €", mesToString(minMonth - 1), mesToString(maxMonth - 1), arr[1]);
    printf("\nTotal de vendas entre %s e %s:  %0.Lf\n", mesToString(minMonth - 1), mesToString(maxMonth - 1), arr[0]);
    printf("--------------------------------------------------------------------------------\n");
    free(arr);
}

/*Query9*/
void printQuery9(SGV sgv, char* productID, int branch) {
    Query9 q = getProductBuyers(sgv, productID, branch - 1);
    printListaClientes(getListaClientesQ9(q));
    int *np = getComprasQ9(q);
    printf("-----------------------------------------\n");
    printf("Numero de compras N: %d", np[0]);
    printf("\nNumero de compras P: %d", np[1]);
    printf("\nNumero total de compras: %d\n", np[0] + np[1]);
    printf("-----------------------------------------\n");
    free(np);
    closeQuery9(q);
}

/*Query10*/
void printQuery10(SGV sgv, char* clientID, int month) {
    ListaProds lp = getClientFavoriteProducts(sgv, clientID, month);
    printListaProds(lp);
}

/*Query11*/
void printQuery11(SGV sgv, int limit) {
    ListaProds lp = getTopSelledProducts(sgv, limit);
    printListaProds(lp);
}

/*Query12*/
void printQuery12(SGV sgv, char* clientID, int limit){
    ListaProds lc = getClienteTopProfitProducts(sgv, clientID, limit);
    printListaProds(lc);
}

/*Query13*/
void printQuery13(SGV sgv){
    char **files = getCurrentFilesInfo(sgv);
    int *arr = getValoresFilesInfo(sgv);
    printf("O ficheiro \"%s\" continha \n\t> %d clientes e %d foram validados\n", files[0], arr[1], arr[0]);
    printf("O ficheiro \"%s\" continha \n\t> %d produtos e %d foram validados\n", files[1], arr[3], arr[2]);
    printf("O ficheiro \"%s\" continha \n\t> %d vendas e %d foram validadas\n", files[2], arr[5], arr[4]);
    free(arr);
    free(files);
}

/*=================================================================MAIN PROMPT==================================================================================*/

void prompt(SGV sgv) {
    char command[BUFF_SIZE], letter, clientID[32], productID[32];
    int minMonth, maxMonth, branch, month, limit;
    clock_t start, end;
    double cpu_time_used;
    printf("Inicializando SGV... Por favor aguarde\n\n");
    char *saleDir = "src/Dados Iniciais/Vendas_1M.txt";
    char *prodDir = "src/Dados Iniciais/Produtos.txt";
    char *clntDir =  "src/Dados Iniciais/Clientes.txt";
    start = clock();
    sgv = loadSGVFromFiles(sgv, saleDir, prodDir, clntDir);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f\n", cpu_time_used);
    boolean isOver = False;
    printf("SGV inicializado com sucesso\nBem vindo!\n(Use h para abrir a janela de ajuda)\n\n");
    while(!isOver) {
        printf("SGV > ");
        if(fgets(command, BUFF_SIZE, stdin)) {
            strToUpper(command);
            if(!strcmp("Q1\n", command)){
                sgv = printQuery1(sgv);
            }
            else if(sscanf(command, "Q2 %c", &letter) == 1) {
                start = clock();
                ListaProds lp = getProductsStartedByLetter(sgv, letter);
                printListaProds(lp);
                closeListaProds(lp);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Tempo de execução: %f\n", cpu_time_used);
            }
            else if(sscanf(command, "Q3 %s %d", productID, &month) == 2){
                start = clock();
                printQuery3(sgv, productID, month);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Tempo de execução: %f\n", cpu_time_used);
            }
            else if(sscanf(command, "Q4 %d", &branch) == 1){
                if (branch >= 1 && branch <= 3){
                    start = clock();
                    printQuery4(sgv, branch);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Tempo de execução: %f\n", cpu_time_used);
                } 
            }    
            else if(!strcmp("Q5\n", command)){
                start = clock();
                printQuery5(sgv);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Tempo de execução: %f\n", cpu_time_used);

            }
            else if(!strcmp("Q6\n", command)){
                start = clock();
                printQuery6(sgv);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Tempo de execução: %f\n", cpu_time_used);
            }
            else if(sscanf(command, "Q7 %s", clientID) == 1){
                start = clock();
                printQuery7(sgv, clientID);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Tempo de execução: %f\n", cpu_time_used);
            }
            else if(sscanf(command, "Q8 %d %d", &minMonth, &maxMonth) == 2){
                if(minMonth > 0 && minMonth < 13 && maxMonth > 0 && maxMonth < 13){
                    start = clock();
                    printQuery8(sgv, minMonth, maxMonth);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Tempo de execução: %f\n", cpu_time_used);
                }
            }
            else if(sscanf(command, "Q9 %s %d", productID, &branch) == 2){
                if(branch > 0 && branch < 4){
                    start = clock();
                    printQuery9(sgv, productID, branch);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Tempo de execução: %f\n", cpu_time_used);
                }
            }
            else if(sscanf(command, "Q10 %s %d", clientID, &month) == 2) {
                if(month > 0 && month < 13) {
                    start = clock();
                    printQuery10(sgv, clientID, month);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Tempo de execução: %f\n", cpu_time_used);
                }
            }
            else if(sscanf(command, "Q11 %d", &limit) == 1) {
                if(limit > 0){
                    printf("Não implementada :(\n");
                }
            }
            else if(sscanf(command, "Q12 %s %d", clientID, &limit) == 2) {
                if(limit > 0){
                    printf("Não implementada :(\n");
                }
            }
            else if(!strcmp("Q13\n", command)) {
                start = clock();
                printQuery13(sgv);
                end = clock(); 
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Tempo de execução: %f\n", cpu_time_used);
            }
            else if(!strcmp("H\n", command)) {
                printf("Lista de comandos:\n");
                printf(" - Q\n\tEncerra o programa\n");
                printf(" - Q1\n\tAltera os ficheiros utilizados\n");
                printf(" - Q2 <letter>\n\tMostra a listagem de produtos ordenada, começada pela letra <letter>\n");
                printf(" - Q3 <productID> <month> \n\tTotal faturado e de vendas do ProductID\n");
                printf(" - Q4 <branch>\n\tDetermina a lista dos codigos que ninguem comprou\n\tO -> Produtos que ninguem comprou em todas as branchs\n\t1 a 3 -> Produtos que ninguem comprou numa das branchs\n");
                printf(" - Q5 \n\tLista de clientes que compraram em todas as filiais\n");
                printf(" - Q6 \n\tDetermina o numero de clientes que nao realizaram compras, bem como os produtos que nao foram comprados\n");
                printf(" - Q7 <clientID>\n\tMostra uma tabela com o numero total de produtos comprados pelo clientID\n");
                printf(" - Q8 <minMonth> <maxMonth> \n\tDetermina o totla de vendas registadas entre minMonth e maxMonth\n");
                printf(" - Q9 <productID> <branch>\n\tLista os clientes que compraram o productID na filial<branch> e difere se foram por compra Normal ou Promoção\n");
                printf(" - Q10 <clientID> <month>\n\tDetermina a lista de codigos mais comprados por esse cliente nesse mês\n");
                printf(" - Q11 <limit>\n\tCria uma lista dos N produtos mais vendidos\n");
                printf(" - Q12 <clientID> <limit>\n\tDado um codigo de cliente determina os N produtos em que gastou mais dinheiro\n");
                printf(" - Q13 \n\tApresenta resultados da leitura do ficheiro\n");
                printf(" - h\n\tAbre esta listagemzinha :)\n\n");
            }
            else if(!strcmp("Q\n", command)) {
                isOver = True;
                printf("A fechar o SGV... Por favor aguarde\n");
                start = clock();
                destroySVG(sgv);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Tempo de execução: %f\n", cpu_time_used);
            }
            else {
                printf("⢐⢕⢕⢕⢕⢕⣕⢕⢕⠕⠁⢕⢕⢕⢕⢕⢕⢕⢕⠅⡄⢕⢕⢕⢕⢕⢕⢕⢕⢕\n");
                printf("⢕⢕⢕⢕⢕⠅⢗⢕⠕⣠⠄⣗⢕⢕⠕⢕⢕⢕⠕⢠⣿⠐⢕⢕⢕⠑⢕⢕⠵⢕\n");
                printf("⢕⢕⢕⢕⠁⢜⠕⢁⣴⣿⡇⢓⢕⢵⢐⢕⢕⠕⢁⣾⢿⣧⠑⢕⢕⠄⢑⢕⠅⢕\n");
                printf("⢕⢕⠵⢁⠔⢁⣤⣤⣶⣶⣶⡐⣕⢽⠐⢕⠕⣡⣾⣶⣶⣶⣤⡁⢓⢕⠄⢑⢅⢑\n");
                printf("⠍⣧⠄⣶⣾⣿⣿⣿⣿⣿⣿⣷⣔⢕⢄⢡⣾⣿⣿⣿⣿⣿⣿⣿⣦⡑⢕⢤⠱⢐\n");    
                printf("⢠⢕⠅⣾⣿⠋⢿⣿⣿⣿⠉⣿⣿⣷⣦⣶⣽⣿⣿⠈⣿⣿⣿⣿⠏⢹⣷⣷⡅⢐\n");
                printf("⣔⢕⢥⢻⣿⡀⠈⠛⠛⠁⢠⣿⣿⣿⣿⣿⣿⣿⣿⡀⠈⠛⠛⠁⠄⣼⣿⣿⡇⢔\n");
                printf("⢕⢕⢽⢸⢟⢟⢖⢖⢤⣶⡟⢻⣿⡿⠻⣿⣿⡟⢀⣿⣦⢤⢤⢔⢞⢿⢿⣿⠁⢕\n");
                printf("⢕⢕⠅⣐⢕⢕⢕⢕⢕⣿⣿⡄⠛⢀⣦⠈⠛⢁⣼⣿⢗⢕⢕⢕⢕⢕⢕⡏⣘⢕\n");
                printf("⢕⢕⠅⢓⣕⣕⣕⣕⣵⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣷⣕⢕⢕⢕⢕⡵⢀⢕⢕\n");
                printf("⢑⢕⠃⡈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃⢕⢕⢕\n");
                printf("⣆⢕⠄⢱⣄⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢁⢕⢕⠕⢁\n");
                printf("⣿⣦⡀⣿⣿⣷⣶⣬⣍⣛⣛⣛⡛⠿⠿⠿⠛⠛⢛⣛⣉⣭⣤⣂⢜⠕⢑⣡⣴⣿\n");
                printf("     NAO PODE FAZER ISSO\n");
            }
        }
    } 
}
