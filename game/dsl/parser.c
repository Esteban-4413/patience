#include <stdio.h>
#include <stdlib.h>
#include "../include/gamedef.h"
#include "../include/parser.h"
#include "../include/utils.h"



DefJogo load_paciencia(char *ficheiro){
    DefJogo estado;
    FILE * paciencia = fopen(ficheiro, "r");
    char buffer[255];
    estado.tipos = NULL;
    estado.total_tipos = 0;
    estado.total_wins = 0;
    estado.movs = NULL;
    estado.total_movs = 0;
    estado.autos = NULL;
    estado.total_autos = 0;
    estado.total_inits = 0;

    estado.inits = NULL;
    estado.wins = NULL;

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
            if (sscanf(buffer, "%s", comando) == 1){ // sscanf lê uma string e extrai as palavras, muito fixe.

                if(comp_strings(comando, "JOGO") == 0) sscanf(buffer, "%s %s", comando, estado.nome);

                else if(comp_strings(comando, "BARALHOS") == 0) sscanf(buffer, "%s %d", comando, &estado.num_baralhos);
                else if(comp_strings(comando, "TIPO") == 0){                
                    estado.total_tipos++;
                    estado.tipos = realloc(estado.tipos, estado.total_tipos * sizeof(TipoPilha));
                    sscanf(buffer, "%s %s %s", comando, estado.tipos[estado.total_tipos-1].nome_tipo, estado.tipos[estado.total_tipos-1].flags);
                }
                else if(comp_strings(comando, "MOV") == 0){                
                    estado.total_movs++;
                    estado.movs = realloc(estado.movs, estado.total_movs * sizeof(Movimento));
                    sscanf(buffer, "%s %s %s %s", comando, estado.movs[estado.total_movs-1].pilha_origem, estado.movs[estado.total_movs-1].pilha_destino, estado.movs[estado.total_movs-1].flags);
                }
                else if(comp_strings(comando, "AUTO") == 0){                
                    estado.total_autos++;
                    estado.autos = realloc(estado.autos, estado.total_autos * sizeof(Movimento));
                    sscanf(buffer, "%s %s %s %s", comando, estado.autos[estado.total_autos-1].pilha_origem, estado.autos[estado.total_autos-1].pilha_destino, estado.autos[estado.total_autos-1].flags);
                }
                else if(comp_strings(comando, "INIT") == 0){                
                    estado.total_inits++;
                    estado.inits = realloc(estado.inits, estado.total_inits * sizeof(InitPilha));
                    sscanf(buffer, "%s %s %d", comando, estado.inits[estado.total_inits-1].nome_tipo, &estado.inits[estado.total_inits-1].num_cartas); // "estado.total_inits-1" podia ser uma variavel!
                }
                else if(comp_strings(comando, "WIN") == 0){
                    estado.total_wins++;
                    estado.wins = realloc(estado.wins, estado.total_wins * sizeof(VictoryCondition));
                    sscanf(buffer, "%s %s %d", comando, estado.wins[estado.total_wins - 1].nome_tipo, &estado.wins[estado.total_wins - 1].num_cartas); // "estado.total_wins - 1" podia ser uma variavel
                }
            }
        }
        fclose(paciencia);
        return estado;
    }
    return estado;
}