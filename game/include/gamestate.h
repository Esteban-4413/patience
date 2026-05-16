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




EstadoJogo setGameState(DefJogo d); 

void inicializa_naipes(EstadoJogo *e);
void inicializa_jogAtual(EstadoJogo *e); 
void set_pilhas (InitPilha d[], int total_inits, PILHA *pilhas); 
void inicializa_baralhos(CARTAS *baralho, int num_baralhos, char naipes[4]);
void inicializa_pilhas(EstadoJogo *e); 


// ---------------------- AUXILIAR ----------------------
void print_baralho_grid(EstadoJogo *e); 
void print_pilhas(EstadoJogo *e);


#endif //PATIENCE_GAMESTATE_H
