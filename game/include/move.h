#ifndef MOVE_H
#define MOVE_H

int valida_jogada(EstadoJogo *estado, JOGADA jogada);
int cor(CARTAS carta);
int verifica_flags(char flags[32], EstadoJogo *estado, JOGADA jogada);
void joga(EstadoJogo *estado, JOGADA jogada); 

#endif //PATIENCE_MOVE_H
