
#include "../include/card.h"
#include "string.h"


void traduzvalor(char *valor, char v){
        switch(v){
                case 1:  copia_string(valor, "A"); return;
                case 11: copia_string(valor, "J"); return;
                case 12: copia_string(valor, "Q"); return;
                case 13: copia_string(valor, "K"); return;
                case 0 : copia_string(valor, "?"); return;
                default:
                sprintf(valor, "%d", v); return;
        }
        
}

CARTAS le_carta(char *str) {
    CARTAS c;
    int len = strlen(str);
    
    c.naipe = str[len - 1]; 
    
    if (str[0] == 'A') c.valor = 1;
    else if (str[0] == 'J') c.valor = 11;
    else if (str[0] == 'Q') c.valor = 12;
    else if (str[0] == 'K') c.valor = 13;
    else {
        char num_str[3];
        int i;
        for (i = 0; i < len - 1; i++) num_str[i] = str[i];
        num_str[i] = '\0';
        // strncpy(num_str, str, len - 1); 
        c.valor = atoi(num_str); //atoi, atoi_l – convert ASCII string to integer
    }
    return c;
}