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


#endif 
