//
// Created by Esteban Yepez Orozco on 10/05/2026.
//

#ifndef UNDO_H
#define UNDO_H

#include <ncurses.h>
#include "../include/gamestate.h"

/**
 * @brief Regista uma jogada no histórico para permitir o "Desfazer" (Undo).
 * 
 * @param e Ponteiro para o estado atual do jogo.
 */
void registar_jogada(EstadoJogo *e);

/**
 * @brief Desfaz a última jogada realizada pelo jogador.
 * Verifica se é possível voltar atrás a jogada- se não retorna uma mensagem, 
 * e se for possível chama a aux_undo que faz toda a parte de devolver as cartas
 * de onde vieram.
 * 
 * @param e Ponteiro para o estado atual do jogo.
 */
void undo(EstadoJogo *e);

/**
 * @brief Auxiliar do undo
 * Onde está a lógica do undo, para o caso de ser possível retroceder uma jogada, 
 * Lê a última() entrada do histórico e reverte o movimento da(s) carta(s),
 * devolvendo-a à sua posição original.
 * 
 * @param e Ponteiro para o estado atual do jogo.
 */
void aux_undo(EstadoJogo *e);


#endif //PATIENCE_UNDO_H
