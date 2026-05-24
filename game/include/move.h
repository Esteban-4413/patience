#ifndef MOVE_H
#define MOVE_H

int valida_jogada(EstadoJogo *estado, JOGADA jogada);
int cor(CARTAS carta);
int ativa_flags(char flags[32], EstadoJogo *estado, JOGADA jogada);
int verifica_pilha_origem_aux2(int flag[20], PILHA *origem, JOGADA jogada, int inicio, int fim, CARTAS topo_origem, CARTAS fundo_origem);
int verifica_pilha_origem_aux(int flag[20],
                            PILHA *origem,
                            JOGADA jogada,
                            int inicio,
                            int fim,
                            CARTAS topo_origem,
                            CARTAS fundo_origem);
int verifica_pilha_origem(int flag[20],
                        PILHA *origem,
                        JOGADA jogada,
                        int inicio,
                        int fim,
                        CARTAS topo_origem,
                        CARTAS fundo_origem);
int verifica_pilha_destino_aux2(int flag[20], PILHA *destino, CARTAS topo_origem);
int verifica_pilha_destino_aux(int flag[20], PILHA *destino, CARTAS topo_origem);
int verifica_pilha_destino(int flag[20], PILHA *destino, CARTAS topo_origem);
void joga(EstadoJogo *estado, JOGADA jogada); 

#endif //PATIENCE_MOVE_H
