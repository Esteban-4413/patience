/**
 * @file move.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef MOVE_H
#define MOVE_H
#include <stdio.h>
#include <locale.h>
#include "../include/gamedef.h"
#include "../include/parser.h"
#include "../include/gamestate.h"
#include "../include/card.h"
#include "../include/display.h"
#include "../include/game.h"
#include "../include/loader.h"
#include "../include/saveload.h"

/*Função que verifica se a jogada é válida, consoante as flags que existem*/
int valida_jogada(EstadoJogo *estado, JOGADA jogada);
/* Função que retorna a cor de uma carta (0 para Preto, 1 para Vermelho) */
int cor(CARTAS carta);
/* Função que identifica as flags presentes e ativam os elementos certos no array flag*/
int ativa_flags(char flags[32], EstadoJogo *estado, JOGADA jogada);
int verifica_pilha_origem_aux2(int flag[20], PILHA *origem, JOGADA jogada, int inicio, int fim, CARTAS topo_origem, CARTAS fundo_origem);
int verifica_pilha_origem_aux(int flag[20],
                            PILHA *origem,
                            JOGADA jogada,
                            int inicio,
                            int fim,
                            CARTAS topo_origem,
                            CARTAS fundo_origem);
/* Função que verifica se as condições das flags que se relacionam à pilha
    de origem estão a ser cumpridas*/
int verifica_pilha_origem(int flag[20],
                        PILHA *origem,
                        JOGADA jogada,
                        int inicio,
                        int fim,
                        CARTAS topo_origem,
                        CARTAS fundo_origem);
int verifica_pilha_destino_aux2(int flag[20], PILHA *destino, CARTAS topo_origem, int inicio);
int verifica_pilha_destino_aux(int flag[20], PILHA *destino, CARTAS topo_origem, int inicio);
/* Função que verifica se as condições das flags que se relacionam à pilha
    de destino estão a ser cumpridas*/
int verifica_pilha_destino(int flag[20], PILHA *destino, CARTAS topo_origem, int inicio);
/* Função que executa a jogada*/
void joga(EstadoJogo *estado, JOGADA jogada); 


/**
 * @brief Auxiliar da movAutos que vai buscar movimentos automáticos 
 * válidos existentes; 
 
 * 
 * @param e  Pointer para o estado do jogo.
 * @param jog Pointer da jogada do movAutos.
 * @param mov Movimento que queremos tratar. 
 * @return int (Bool) 
 */
int search_auto_valido(EstadoJogo *e, JOGADA *jog, Movimento mov);
/**
 * @brief Auxiliar da search_auto_valido, que coniste no loop de procura 
 * de um destino válido para a jogada. 
 * 
 * @param e Pointer para o estado do jogo.
 * @param jog Pointer da jogada do movAutos.
 * @param mov Movimento que queremos tratar. 
 * @param found Pointer da flag da movAutos.
 */
void aux_search_auto(EstadoJogo *e, JOGADA *jog, Movimento mov, int *found);

/**
 * @brief Função que vai verificar os movimentos automáticos 
 * 
 * @param e Pointer para o estado do jogo.
 */
void movAutos (EstadoJogo *e); 


#endif

