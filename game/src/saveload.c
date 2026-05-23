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
    if(f == NULL) printf("erro a criar o ficheiro save");

    fprintf(f, "%s\n", nome_paciencia_original);

    size_t i, j;
    for(i = 0; i < e->total_pilhas; i ++){
        if(e->pilhas[i].tamanho_pilha == 0) {fprintf(f, "\n"); return;}
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
    FILE *f = fopen(ficheiro_save, "r");
    if(f == NULL) printf("erro ao carregar o ficherio save");

}