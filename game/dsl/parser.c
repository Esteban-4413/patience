#include <stdio.h>
#include <stdlib.h>
#include "../include/gamedef.h"
#include "../include/parser.h"
#include "../include/utils.h"



DefJogo load_paciencia(char *ficheiro){
    DefJogo estado = incializa_estado();
    FILE * paciencia = fopen(ficheiro, "r");
    char buffer[255];


    if(paciencia == NULL) {printf("nao existe"); return estado;}

    else{
        while(fgets(buffer, 255, paciencia) != NULL){
        
            // digo eu que começamos por tirar tudo o que não vamos ler, i.e, os comentarios (#)
            char * comentario = aux_string(buffer, '#');
            if (comentario != NULL) *comentario = '\0';

            // vamo' identificar o comando 
            char comando[32];
 
            // sscanf devolve um int que é a quantidade de elementos que consiguio ler.
            // Neste caso só interessa se conseguio ler a primeira string ou não (nesse caso devolve 0).
            if (sscanf(buffer, "%s", comando) == 1) what_command(comando, buffer, &estado);// sscanf lê uma string e extrai as palavras, muito fixe.
        }
        fclose(paciencia);
        return estado;
    }
    return estado;
}

DefJogo incializa_estado(void){
    DefJogo est;
    est.nome[0] = '\0';

    est.tipos = NULL;
    est.total_tipos = 0;

    est.total_wins = 0;

    est.movs = NULL;
    est.total_movs = 0;

    est.autos = NULL;
    est.total_autos = 0;

    est.total_inits = 0;
    est.inits = NULL;

    est.wins = NULL;
    return est;
}

void what_command(char * comando, char *buffer, DefJogo *est){
    if(comp_strings(comando, "JOGO") == 0) sscanf(buffer, "%s %s", comando, est->nome);

    else if(comp_strings(comando, "BARALHOS") == 0) sscanf(buffer, "%s %d", comando, &est->num_baralhos);
    else if(comp_strings(comando, "TIPO") == 0){                
    est->total_tipos++;
    est->tipos = realloc(est->tipos, est->total_tipos * sizeof(TipoPilha));
    sscanf(buffer, "%s %s %s", comando, est->tipos[est->total_tipos-1].nome_tipo, est->tipos[est->total_tipos-1].flags);
    }

    else if(comp_strings(comando, "MOV") == 0){                
    est->total_movs++;
    est->movs = realloc(est->movs, est->total_movs * sizeof(Movimento));
    sscanf(buffer, "%s %s %s %s", comando, est->movs[est->total_movs-1].pilha_origem, est->movs[est->total_movs-1].pilha_destino, est->movs[est->total_movs-1].flags);
    }

    else if(comp_strings(comando, "AUTO") == 0){                
    est->total_autos++;
    est->autos = realloc(est->autos, est->total_autos * sizeof(Movimento));
    sscanf(buffer, "%s %s %s %s", comando, est->autos[est->total_autos-1].pilha_origem, est->autos[est->total_autos-1].pilha_destino, est->autos[est->total_autos-1].flags);
    }

    else if(comp_strings(comando, "INIT") == 0){                
    est->total_inits++;
    est->inits = realloc(est->inits, est->total_inits * sizeof(InitPilha));
    sscanf(buffer, "%s %s %d", comando, est->inits[est->total_inits-1].nome_tipo, &est->inits[est->total_inits-1].num_cartas); // "estado.total_inits-1" podia ser uma variavel!
    }

    else if(comp_strings(comando, "WIN") == 0){
    est->total_wins++;
    est->wins = realloc(est->wins, est->total_wins * sizeof(VictoryCondition));
    sscanf(buffer, "%s %s %d", comando, est->wins[est->total_wins - 1].nome_tipo, &est->wins[est->total_wins - 1].num_cartas); // "estado.total_wins - 1" podia ser uma variavel
    }   
}