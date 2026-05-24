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
                if (verifica_flags(mov.flags, estado, jogada)) return 1;
        }
    }
    return 0;
}

// Função que retorna a cor de uma carta (0 para Preto, 1 para Vermelho)
int cor(CARTAS carta){
    if (carta.naipe == 'C' || carta.naipe == 'O') return 1;
    return 0;
}

int verifica_pilha_origem_aux2(int flag[20], PILHA *origem, JOGADA jogada, int inicio, int fim, CARTAS topo_origem, CARTAS fundo_origem){
    for(int i = inicio; i < fim; i++){
        if ((flag[9] && origem->pilha[i].naipe == origem->pilha[i+1].naipe)
         || (flag[11] && cor(origem->pilha[i]) != cor(origem->pilha[i+1]))
         || (flag[13] && cor(origem->pilha[i]) == cor(origem->pilha[i+1]))) return 0;
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
    if (flag[19] && fundo_origem.valor != 13) return 0;
    for(int i = inicio; i < fim; i++){
        if((flag[2] && origem->pilha[i].valor != origem->pilha[i+1].valor + 1)
        || (flag[3] && origem->pilha[i].valor != origem->pilha[i+1].valor - 1)
        || (flag[7] && origem->pilha[i].naipe != origem->pilha[i+1].naipe))
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

    if (!flag[1] && jogada.n > 1) return 0;

    if (flag[16] && topo_origem.valor != 1) return 0;

    if (flag[17] && fundo_origem.valor != 1) return 0;

    if (flag[18] && topo_origem.valor != 13) return 0;

    return verifica_pilha_origem_aux(flag, origem, jogada, inicio, fim, topo_origem, fundo_origem);
}

int verifica_pilha_destino_aux2(int flag[20], PILHA *destino, CARTAS topo_origem){
    CARTAS topo_destino = destino->pilha[destino->tamanho_pilha - 1];

    return !((flag[4]  && topo_origem.valor != topo_destino.valor - 1) ||
            (flag[5]  && topo_origem.valor != topo_destino.valor + 1) ||
            (flag[14] && cor(topo_origem) == cor(topo_destino)));
}
int verifica_pilha_destino_aux(int flag[20], PILHA *destino, CARTAS topo_origem){
    CARTAS topo_destino = destino->pilha[destino->tamanho_pilha - 1];    
    
    return !((flag[6]  && abs(topo_origem.valor - topo_destino.valor) != 1) ||
             (flag[8]  && topo_origem.naipe != topo_destino.naipe) ||
             (flag[10] && topo_origem.naipe == topo_destino.naipe) ||
             (flag[12] && cor(topo_origem) != cor(topo_destino)) ||
             verifica_pilha_destino_aux2(flag, destino, topo_origem));
}
int verifica_pilha_destino(int flag[20],
                         PILHA *destino,
                         CARTAS topo_origem){
    
    
    if(flag[15]){
        if (destino->tamanho_pilha != 0) return 0;
    }
    return !(flag[4] || flag[5] || flag[6] || flag[8]
        || flag[10] || flag[12] || flag[14] || verifica_pilha_destino_aux(flag, destino, topo_origem));
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

    CARTAS topo_destino, topo_origem = origem->pilha[fim], fundo_origem = origem->pilha[inicio];;

    return(verifica_pilha_origem(flag, origem, jogada, inicio, fim, topo_origem, fundo_origem)
            && verifica_pilha_destino(flag, destino, topo_origem));
}


void joga(EstadoJogo *estado, JOGADA jogada){
    PILHA *origem = &(estado->pilhas[jogada.pilha]);
    int tamanho_origem = origem->tamanho_pilha;

    PILHA *destino = &(estado->pilhas[jogada.chegada]);
    int tamanho_destino = destino->tamanho_pilha;

    int inicio = jogada.coluna;
    
    for(int i = 0; i < tamanho_origem - jogada.coluna; i++){
        destino->pilha[tamanho_destino] = origem->pilha[tamanho_origem -1];
        origem->tamanho_pilha --;
        destino->tamanho_pilha ++;
    }

}

//tratar do caso em que destino->tamanho_pilha = 0 AFINAL JA ESTAVA FEITO
//int fim pode ser escrito de maneira mais simples (é sempre o topo da pilha) FEITO
//memmove não é preciso FEITO

//condicao de vitoria
//movimentos automaticos