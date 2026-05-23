#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/loader.h"
#include "../include/gamestate.h"
#include "../include/gamedef.h"
#include "../include/saveload.h"
#include "../include/card.h"


void escreve_carta(FILE *f, CARTAS c){
    char var_str[4]; // arr para guardar "A", "10" etc
    
    traduzvalor(var_str, c.valor);

    fprintf(f, "%s%c", var_str, c.naipe);
}


void save_game(EstadoJogo *e, char *ficheiro_save, char *nome_paciencia_original){
    FILE *f = fopen(ficheiro_save, "w"); 
    if(f == NULL) {printf("erro a criar o ficheiro save"); return;}

    fprintf(f, "%s\n", nome_paciencia_original);

    size_t i, j;
    for(i = 0; i < e->total_pilhas; i ++){
        if(e->pilhas[i].tamanho_pilha == 0) fprintf(f, "\n");
        else
        {
            for(j = 0; j < e->pilhas[i].tamanho_pilha; j++){
                escreve_carta(f, e->pilhas[i].pilha[j]);
                if(j < e->pilhas[i].tamanho_pilha - 1) fprintf(f, " ");
            }
            fprintf(f, "\n");
        }
    }
    fclose(f);
}

EstadoJogo load_game(char *ficheiro_save, char *pasta_paciencias){
    EstadoJogo e;
    e.total_pilhas = 0;
    e.def_jogo = NULL;
    
    FILE *f = fopen(ficheiro_save, "r");
    if(f == NULL) {printf("erro ao carregar o ficherio save"); return e;}

    char buffer[128];
    char ruta[256];
    fgets(buffer, sizeof(buffer), f);
    int len = strlen(buffer);
    if(len > 0 && buffer[len - 1] == '\n') buffer[len-1] = '\0';

    sprintf(ruta, "%s/%s", pasta_paciencias, buffer);
    DefJogo *regras = load_paciencia(ruta);
    e = setGameState(regras);
    
    size_t i = 0;
    int eof = 0; //end of file. Mesmo trque que usei noutra qualuqer função: a boolean flag haha
    while (i < e.total_pilhas && !eof){
        if(fgets(buffer, sizeof(buffer), f) == NULL) eof = 1;
        else{
            int len = strlen(buffer);
            if(len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
            e.pilhas[i].tamanho_pilha = 0;
            if(buffer[0] != '\0') parse_linha_pilha(buffer, &e.pilhas[i]);
        }
        i++;    
    }
    fclose(f);
    return e;
}

void parse_linha_pilha(char *buffer, PILHA *pilha){
    char token[4];
    int pos = 0;
    int leidos;
    pilha->tamanho_pilha = 0;
    while (sscanf(buffer + pos, "%s%n", token, &leidos) == 1){
        CARTAS c = le_carta(token);
        pilha->pilha[pilha->tamanho_pilha] = c;
        pilha->tamanho_pilha++;
        pos += leidos;
    }
}