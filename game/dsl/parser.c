#include <stdio.h>
#include <stdlib.h>
#include "../include/gamedef.h"
#include "../include/parser.h"
#include "../include/utils.h"



DefJogo* load_paciencia(char *ficheiro){
    DefJogo *estado = incializa_estado();
    FILE * paciencia = fopen(ficheiro, "r");
    char buffer[255];

    if(paciencia == NULL) {printf("nao existe"); return estado;}

    else 
    {
        while(fgets(buffer, 255, paciencia) != NULL) processa_linha(buffer, estado);
        fclose(paciencia);
        return estado;
    }

    return estado;
}

int processa_linha(char *buffer, DefJogo *est){
    char *comentario = aux_string(buffer, '#');
    if (comentario != NULL) *comentario = '\0';

    // vamo' identificar o comando 
    char comando[32];
 
    // sscanf devolve um int que é a quantidade de elementos que consiguio ler.
    // Neste caso só interessa se conseguio ler a primeira string ou não (nesse caso devolve 0).
    if (sscanf(buffer, "%s", comando) == 1) what_command(comando, buffer, est);
    return 1;// sscanf lê uma string e extrai as palavras, muito fixe.
}

DefJogo* incializa_estado(void){
    DefJogo *est = malloc(sizeof(DefJogo)); // Adicionei (Fernanda) isso para converter para um pointer.
    est->nome[0] = '\0';

    est->tipos = NULL;
    est->total_tipos = 0;

    est->total_wins = 0;

    est->movs = NULL;
    est->total_movs = 0;

    est->autos = NULL;
    est->total_autos = 0;

    est->total_inits = 0;
    est->inits = NULL;

    est->wins = NULL;
    return est;
}

void what_command(char * comando, char *buffer, DefJogo *est){
    if(comp_strings(comando, "JOGO") == 0) sscanf(buffer, "%s %s", comando, est->nome);

    else if(comp_strings(comando, "BARALHOS") == 0) sscanf(buffer, "%s %d", comando, &est->num_baralhos);
    
    else if(comp_strings(comando, "TIPO") == 0) cmd_tipo(buffer, est);

    else if(comp_strings(comando, "MOV") == 0) cmd_mov(buffer, est);

    else if(comp_strings(comando, "AUTO") == 0) cmd_auto(buffer, est);

    else if(comp_strings(comando, "INIT") == 0) cmd_init(buffer, est);

    else if(comp_strings(comando, "WIN") == 0) cmd_win(buffer, est);
}

void cmd_tipo(char *buffer, DefJogo *est){
    est->total_tipos++;
    est->tipos = realloc(est->tipos, est->total_tipos * sizeof(TipoPilha));
    char cmd[32];
    int idx = est->total_tipos - 1;
    sscanf(buffer, "%s %s %s", cmd, est->tipos[idx].nome_tipo, est->tipos[idx].flags);
}

void cmd_mov(char *buffer, DefJogo *est){
    est->total_movs++;
    est->movs = realloc(est->movs, est->total_movs * sizeof(Movimento));
    char cmd[32];
    int idx = est->total_movs-1;
    sscanf(buffer, "%s %s %s %s", cmd, est->movs[idx].pilha_origem, est->movs[idx].pilha_destino, est->movs[idx].flags);
}

void cmd_auto(char *buffer, DefJogo *est){
    est->total_autos++;
    est->autos = realloc(est->autos, est->total_autos * sizeof(Movimento));
    char cmd[32];
    int idx = est->total_autos-1;
    sscanf(buffer, "%s %s %s %s", cmd, est->autos[idx].pilha_origem, est->autos[idx].pilha_destino, est->autos[idx].flags);
}

void cmd_init(char *buffer, DefJogo *est){
    est->total_inits++;
    est->inits = realloc(est->inits, est->total_inits * sizeof(InitPilha));
    char cmd[32];
    int idx = est->total_inits-1;
    sscanf(buffer, "%s %s %d", cmd, est->inits[idx].nome_tipo, &est->inits[idx].num_cartas);
}

void cmd_win(char *buffer, DefJogo *est){
   est->total_wins++;
   est->wins = realloc(est->wins, est->total_wins * sizeof(VictoryCondition));
   char cmd[32];
   int idx = est->total_wins - 1;
   sscanf(buffer, "%s %s %d", cmd, est->wins[idx].nome_tipo, &est->wins[idx].num_cartas); 
}