#include <string.h>
#include <stdlib.h>

#include "../include/gamestate.h"
#include "../include/move.h"

int valida_jogada(EstadoJogo *estado, JOGADA jogada){
    PILHA origem = estado->pilhas[jogada.pilha];
    PILHA destino = estado->pilhas[jogada.chegada];

    for (int i = 0; i < estado->def_jogo->total_movs; i++){
        Movimento mov = estado->def_jogo->movs[i];

        if (strcmp(mov.pilha_origem, origem.nome_tipo) == 0
            &&  strcmp(mov.pilha_destino, destino.nome_tipo) == 0){
                if (ativa_flags(mov.flags, estado, jogada)) return 1;
        }
    }
    return 0;
}

int cor(CARTAS carta){
    if (carta.naipe == 'C' || carta.naipe == 'O') return 1;
    return 0;
}


int verifica_pilha_origem_aux2(int flag[20], PILHA *origem, JOGADA jogada, int inicio, int fim, CARTAS topo_origem, CARTAS fundo_origem){
    for(int i = inicio; i < fim; i++){
        if ((flag[9] && origem->pilha[i].naipe == origem->pilha[i+1].naipe) // x: naipes alternados
         || (flag[11] && cor(origem->pilha[i]) != cor(origem->pilha[i+1])) // c: mesma cor
         || (flag[13] && cor(origem->pilha[i]) == cor(origem->pilha[i+1]))) return 0; // d: cores alternadas
    }
    return 1;
}
int verifica_pilha_origem_aux(int flag[20],
                            PILHA *origem,
                            JOGADA jogada,
                            int inicio,
                            int fim,
                            CARTAS topo_origem,
                            CARTAS fundo_origem){
    if (flag[19] && fundo_origem.valor != 13) return 0; // K: fundo deve ser Rei
    for(int i = inicio; i < fim; i++){
        if((flag[2] && origem->pilha[i].valor != origem->pilha[i+1].valor + 1) // [: decrescente
        || (flag[3] && origem->pilha[i].valor != origem->pilha[i+1].valor - 1) // ]: crescente
        || (flag[7] && origem->pilha[i].naipe != origem->pilha[i+1].naipe)) // m: mesmo naipe
        return 0;
    }
    return verifica_pilha_origem_aux2(flag, origem, jogada, inicio, fim, topo_origem, fundo_origem);
}

int verifica_pilha_origem(int flag[20],
                         PILHA *origem,
                         JOGADA jogada,
                         int inicio,
                         int fim,
                         CARTAS topo_origem,
                         CARTAS fundo_origem){

    // Se mover mais que 1 carta, a flag '+' (flag[1]) TEM de estar ativa
    if (!flag[1] && jogada.n > 1) return 0;

    if (flag[16] && topo_origem.valor != 1) return 0; // a: topo deve ser Ás

    if (flag[17] && fundo_origem.valor != 1) return 0; // A: fundo deve ser Ás

    if (flag[18] && topo_origem.valor != 13) return 0; // k: topo deve ser Rei

    return verifica_pilha_origem_aux(flag, origem, jogada, inicio, fim, topo_origem, fundo_origem);
}

int verifica_pilha_destino_aux2(int flag[20], PILHA *destino, CARTAS topo_origem){
    CARTAS topo_destino = destino->pilha[destino->tamanho_pilha - 1];

    return !((flag[4]  && topo_origem.valor != topo_destino.valor - 1) || // <: valor inferior ao destino
            (flag[5]  && topo_origem.valor != topo_destino.valor + 1) || // >: valor superior ao destino
            (flag[14] && cor(topo_origem) == cor(topo_destino))); // D: cor diferente do destino
}

int verifica_pilha_destino_aux(int flag[20], PILHA *destino, CARTAS topo_origem){
    CARTAS topo_destino = destino->pilha[destino->tamanho_pilha - 1];    
    
    return  !((flag[6]  && abs(topo_origem.valor - topo_destino.valor) != 1) || // ~: valor superior ou inferior
              (flag[8]  && topo_origem.naipe != topo_destino.naipe) || // M: mesmo naipe que o destino
              (flag[10] && topo_origem.naipe == topo_destino.naipe) || // X: naipe diferente do destino
              (flag[12] && cor(topo_origem) != cor(topo_destino)) || // C: mesma cor que o destino
              !verifica_pilha_destino_aux2(flag, destino, topo_origem));
}

int verifica_pilha_destino(int flag[20],
                         PILHA *destino,
                         CARTAS topo_origem){
    if(destino->tamanho_pilha == 0){
        if (flag[4]||flag[5]||flag[6]||flag[8]||flag[10]||flag[12]||flag[14]) return 0;
        return 1;
    }

    if(flag[15]) return 0; // V: destino vazio aceita o movimento

    return verifica_pilha_destino_aux(flag, destino, topo_origem);
}

int ativa_flags(char flags[32], EstadoJogo *estado, JOGADA jogada){
    int flag[20] = {0};
    char *caracteres = "*+[]<>~mMxXcCdDVaAkK";
    for (int i = 0; flags[i]; i++){
        for(int j = 0; caracteres[j]; j++){
            if(flags[i] == caracteres[j]) flag[j] = 1;
        }
    }

    PILHA *origem = &(estado->pilhas[jogada.pilha]), *destino = &(estado->pilhas[jogada.chegada]);

    int inicio = jogada.coluna, fim = origem->tamanho_pilha-1;

    CARTAS topo_destino, topo_origem = origem->pilha[fim], fundo_origem = origem->pilha[inicio];

    

    return(verifica_pilha_origem(flag, origem, jogada, inicio, fim, topo_origem, fundo_origem)
            && verifica_pilha_destino(flag, destino, topo_origem));
}

void joga(EstadoJogo *estado, JOGADA jogada){
    PILHA *origem = &(estado->pilhas[jogada.pilha]);

    PILHA *destino = &(estado->pilhas[jogada.chegada]);

    int fim = origem->tamanho_pilha;
    int inicio = fim - jogada.n;

    
    for(int i = inicio; i < fim; i++){
        destino->pilha[destino->tamanho_pilha] = origem->pilha[i];
        destino->tamanho_pilha++;
        origem->tamanho_pilha--;
    }

}


void movAutos(EstadoJogo *e) {
    int total_autos = e->def_jogo->total_autos; 
    Movimento *mov = e->def_jogo->autos;

    JOGADA jog;
    int moved = 1;

    while (moved) {
        moved = 0;

        for (int i = 0; i < total_autos && !moved; i++) {
            if (search_auto_valido(e, &jog, mov[i])) {
                joga(e, jog);        // Executa a jogada automática
                moved = 1; // Força o 'while' a rodar mais uma cadeia
                // O loop 'for' termina na próxima iteração porque !moved será falso
            }
        }
    }
}


int search_auto_valido(EstadoJogo *e, JOGADA *jog, Movimento mov) {
    char *nome_tipoO = mov.pilha_origem;
    int found = 0;

    for (int i = 0; i < e->total_pilhas && !found; i++) {
        // Só avança se a pilha 'i' coincidir com o tipo de origem
        if (comp_strings(e->pilhas[i].nome_tipo, nome_tipoO) == 0) {
            jog->pilha = i;

            for (int j = 0; j < e->pilhas[i].tamanho_pilha && !found; j++) {
                jog->coluna = j;
                jog->n = e->pilhas[i].tamanho_pilha - j;
                aux_search_auto(e, jog, mov, &found);
                
            }
        }
    }
    return found;
}

void aux_search_auto(EstadoJogo *e, JOGADA *jog, Movimento mov, int *found){
    char *nome_tipoD = mov.pilha_destino; 
    for (int k = 0; k < e->total_pilhas && !(*found); k++) {
                    // Só avança se a pilha 'k' coincidir com o tipo de destino
                    if (comp_strings(e->pilhas[k].nome_tipo, nome_tipoD) == 0) {
                        jog->chegada = k; 

                        if (ativa_flags(mov.flags, e, *jog)) {
                            *found = 1; 
                        }
                    }
                }

}
