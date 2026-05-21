#include <string.h>
#include <stdlib.h>
#include "../include/move.h"
#include "../include/gamestate.h"

int valida_jogada(EstadoJogo estado, JOGADA jogada){
    PILHA origem = estado.pilhas[jogada.pilha];
    PILHA destino = estado.pilhas[jogada.chegada];

    for (int i = 0; i < estado.def_jogo->total_movs; i++){
        Movimento mov = estado.def_jogo->movs[i];

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


int verifica_flags(char flags[32], EstadoJogo estado, JOGADA jogada){

    int flag[20] = {0};

    for (int i = 0; flags[i]; i++){

        switch (flags[i]){

            case '*':
                flag[0] = 1;
                break;

            case '+':
                flag[1] = 1;
                break;

            case '[':
                flag[2] = 1;
                break;

            case ']':
                flag[3] = 1;
                break;

            case '<':
                flag[4] = 1;
                break;

            case '>':
                flag[5] = 1;
                break;

            case '~':
                flag[6] = 1;
                break;

            case 'm':
                flag[7] = 1;
                break;

            case 'M':
                flag[8] = 1;
                break;

            case 'x':
                flag[9] = 1;
                break;

            case 'X':
                flag[10] = 1;
                break;

            case 'c':
                flag[11] = 1;
                break;

            case 'C':
                flag[12] = 1;
                break;

            case 'd':
                flag[13] = 1;
                break;

            case 'D':
                flag[14] = 1;
                break;

            case 'V':
                flag[15] = 1;
                break;

            case 'a':
                flag[16] = 1;
                break;

            case 'A':
                flag[17] = 1;
                break;

            case 'k':
                flag[18] = 1;
                break;

            case 'K':
                flag[19] = 1;
                break;
        }
    }

    PILHA *origem = &estado.pilhas[jogada.pilha];
    PILHA *destino = &estado.pilhas[jogada.chegada];

    int inicio = jogada.coluna;
    int fim = jogada.coluna + jogada.n - 1;

    CARTAS topo_origem = origem->pilha[fim];
    CARTAS fundo_origem = origem->pilha[inicio];

    CARTAS topo_destino;
    if (destino->tamanho_pilha > 0) topo_destino = destino->pilha[destino->tamanho_pilha - 1];

    if (flag[0]) return 1;

    //Estas flags precisam de uma pilha existente. Se o tamanho for 0,
    //então imediatamente não é válido
    if (destino->tamanho_pilha == 0){
        if (flag[4] || flag[5] || flag[6] || flag[8]
         || flag[10] || flag[12] || flag[14]) return 0;
}

    if (!flag[1] && jogada.n > 1) return 0;

    if (flag[16] && topo_origem.valor != 1) return 0;

    if (flag[17] && fundo_origem.valor != 1) return 0;

    if (flag[18] && topo_origem.valor != 13) return 0;

    if (flag[19] && fundo_origem.valor != 13) return 0;

    if (flag[15] && destino->tamanho_pilha != 0) return 0;

    if (flag[4] && topo_origem.valor != topo_destino.valor - 1) return 0;

    if (flag[5] && topo_origem.valor != topo_destino.valor + 1) return 0;

    if (flag[6] && abs(topo_origem.valor - topo_destino.valor) != 1) return 0;

    if (flag[8] && topo_origem.naipe != topo_destino.naipe) return 0;

    if (flag[10] && topo_origem.naipe == topo_destino.naipe) return 0;

    if (flag[12] && cor(topo_origem) != cor(topo_destino)) return 0;

    if (flag[14] && cor(topo_origem) == cor(topo_destino)) return 0;

    if (flag[2]){
        for (int i = inicio; i < fim; i++){
            if (origem->pilha[i].valor != origem->pilha[i+1].valor + 1) return 0;
        }
    }

    if (flag[3]){
        for (int i = inicio; i < fim; i++){
            if (origem->pilha[i].valor != origem->pilha[i+1].valor - 1) return 0;
        }
    }

    if (flag[7]){
        for (int i = inicio; i < fim; i++){
            if (origem->pilha[i].naipe != origem->pilha[i+1].naipe) return 0;
        }
    }

    if (flag[9]){
        for (int i = inicio; i < fim; i++){
            if (origem->pilha[i].naipe == origem->pilha[i+1].naipe) return 0;
        }
    }

    if (flag[11]){
        for (int i = inicio; i < fim; i++){
            if (cor(origem->pilha[i]) != cor(origem->pilha[i+1])) return 0;
        }
    }

    if (flag[13]){
        for (int i = inicio; i < fim; i++){
            if (cor(origem->pilha[i]) == cor(origem->pilha[i+1])) return 0;
        }
    }

    return 1;
}


void joga(EstadoJogo *estado, JOGADA jogada){
    if (!valida_jogada(*estado, jogada)) return;

    PILHA *origem = &estado->pilhas[jogada.pilha];
    PILHA *destino = &estado->pilhas[jogada.chegada];

    int inicio = jogada.coluna;

    memmove(&destino->pilha[destino->tamanho_pilha],
            &origem->pilha[inicio],
            jogada.n*sizeof(CARTAS));

    destino->tamanho_pilha += jogada.n;
    origem->tamanho_pilha -= jogada.n;

    estado->jog_atual = jogada;

    if(estado->tamanho_historial < MAX_UNDO){
        estado->historial[estado->tamanho_historial++] = jogada;
    }
}