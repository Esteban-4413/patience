#ifndef SAVELOAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/loader.h"
#include "../include/gamestate.h"
#include "../include/gamedef.h"
#define SAVELOAD_H

/**
 * @brief 
 * 
 * @param f 
 * @param c 
 */
void escreve_carta(FILE *f, CARTAS c);

/**
 * @brief 
 * 
 * @param e 
 * @param ficheiro_save 
 * @param nome_paciencia_original 
 */
void save_game(EstadoJogo *e, char *ficheiro_save, char *nome_paciencia_original);


/**
 * @brief 
 * 
 * @param ficheiro_save 
 * @param pasta_paciencias 
 * @return EstadoJogo 
 */
EstadoJogo load_game(char *ficheiro_save, char *pasta_paciencias);

/**
 * @brief 
 * 
 * @param buffer 
 * @param pilha 
 */
void parse_linha_pilha(char *buffer, PILHA *pilha);

void escreve_pilha(FILE *f, PILHA *pilha);

EstadoJogo carrega_estado_inicial(FILE *f, char *pasta_paciencias);

void carrega_pilhas(FILE *f, EstadoJogo *e);


#endif 
