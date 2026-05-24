/**
 * @file gamestate.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../include/card.h"
#include "../include/gamedef.h"
#include <stddef.h> // para usar o size_t

/** @brief Número máximo de jogadas que ficam guardadas no histórico para o Undo. */
#define MAX_UNDO 5



typedef struct{
    char *nome_tipo;
    //TipoPilha *tipo_pilha; -- Acho que será desnecessário 

    CARTAS *pilha;
    size_t tamanho_pilha;   
    /* Existe o caso da flag 1- só pode ter no máximo 1 elemento
     Para esse caso, valia a pena criar um array com tamanho 1 apenas; 
    */  
     
} PILHA; 


typedef struct JOGADA {
    int pilha;    /**< Indice da pilha de onde a carta saiu. */
    int coluna;   /**< O índice da posição da carta dentro da pilha de saida. */
    int n;        /**< Número de cartas na sequência que vão ser movidas. */
    int chegada;  /**< O índice da pilha de onde a carta vai passar. */
    int flag;     /**< Inicializada a 0; -1 se a jogada não for possível */
    CARTAS carta; /**< A carta exata que foi movida durante esta jogada. */
}JOGADA;

typedef struct{
    char naipes[4]; // Isso pode está definido fora do estado de jogo - é fixo !!

    PILHA *pilhas;
    size_t total_pilhas;     

    CARTAS *baralho; 
    size_t tamanho_baralho;
    /* A ideia:
        tamnho_baralho sempre vai ser igual a 52*x - onde x é o num_baralhos; 
        (aproveitando do SimpleSimon - a ideia seria de inicilizar_baralho x vezes seguidas 
        e ir preenchendo o array do baralho com essas cartas) 
    
    */

    JOGADA jog_atual;

    JOGADA historial[MAX_UNDO];
    size_t tamanho_historial;

    DefJogo *def_jogo; //Ponteiro para a definição do jogo

} EstadoJogo;



/**
 * @brief Set the Game State object
 * Função que define o estado de jogo
 * @param d 
 * @return EstadoJogo 
 */
EstadoJogo setGameState(DefJogo *d); 

/**
 * @brief 
 * Função que inicializa os 4 naipes
 * @param e 
 */
void inicializa_naipes(EstadoJogo *e);

/**
 * @brief 
 * Função que inicializa o jogo atual com todas as suas propriedades
 * @param e 
 */
void inicializa_jogAtual(EstadoJogo *e); 

/**
 * @brief Set the pilhas object
 * Função que prepara as pilhas do jogo
 * @param d 
 * @param total_inits 
 * @param pilhas 
 */
void set_pilhas (InitPilha d[], int total_inits, PILHA *pilhas); 

/**
 * @brief 
 * Função que inicializa os baralhos do jogo
 * @param baralho 
 * @param num_baralhos 
 * @param naipes 
 */
void inicializa_baralhos(CARTAS *baralho, int num_baralhos, char naipes[4]);

/**
 * @brief 
 * Função que inicializa as pilhas com as cartas certas
 * @param e 
 */
void inicializa_pilhas(EstadoJogo *e); 



#endif //PATIENCE_GAMESTATE_H
