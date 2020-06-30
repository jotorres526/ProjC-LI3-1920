#include "../include/MyString.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
void strToUpper(char *str) {
    int i;
    for(i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}

char* dupString(char* str) {
    char* newStr = malloc(strlen(str)+1);
    strcpy(newStr, str);
    return newStr;
}

/*ToString de Mes*/
char* mesToString(Mes mes) {
    char* c;
    if(mes == 0) c = "Jan";
    else if(mes == 1) c = "Fev";
    else if(mes == 2) c = "Mar";
    else if(mes == 3) c = "Abr";
    else if(mes == 4) c = "Mai";
    else if(mes == 5) c = "Jun";
    else if(mes == 6) c = "Jul";
    else if(mes == 7) c = "Ago";
    else if(mes == 8) c = "Set";
    else if(mes == 9) c = "Out";
    else if(mes == 10) c = "Nov";
    else c = "Dez";
    return c;
}