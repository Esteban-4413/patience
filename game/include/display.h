#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "gamestate.h"
#include "card.h"
#include "utils.h"


/**
 * @brief Struct construida para guardar os endereços de todas as janelas 
 * e tornar mais fácil o seu manuseio ao ultilizar o bloco como argumento 
 *  das funções, no lugar de cada um dos pointers individualmente. 
 */
typedef struct {
    WINDOW **end_pilhas;     /**< Ponteiro para o array com os endereços das janelas das pilhas da mesa. */
    size_t total_pilhas;    /**Tamanho do array de endereços de pilhas */
    WINDOW *end_undo;       /**< Endereço da janela do botão Undo. */
    WINDOW *end_ngame;      /**< Endereço da janela do botão New Game. */

} POINTERS ; 


/**
 * @brief Função chamada após ser definida uma nova jogada
 * reponsável por chamar as funções, que vai por a piscar a selecionada a piscar 
 * ou fazer com que a mesma deixe de piscar. 
 * 
 * @param e Ponteiro para o estado atual do jogo.
 * @param janelas Pointer onde estão guadados os endereços das janelas.
 */
void update_pilha(EstadoJogo *e, POINTERS *janelas);

/**
 * @brief Função auxiliar da update_pilha.
 * Determina o lim que é o índice até onde as cartas vão ser mostradas
 * sem piscar, para depois na função print_pilha, ser usado esse valor.
 * 
 * @param win Endereço da janela da pilha.
 * @param x Posição relativa dentro da janela para a coluna do print. 
 * @param y Posição relativa dentro da janela para a linha do print.
 * @param nome Array com o nome do tipo da pilha. 
 * @param pilha Array de cartas da correspondente pilha.
 * @param tamanho_pilha Quantas cartas há na pilha,i.e., quantos elementos há no array.
 * @param lim Coluna onde foi feito o click, i.e., a partir de onde as cartas ficam em destaque. 
 */
void pilha_negrito(WINDOW *win, int x, int y, char nome[], CARTAS *pilha, int tamanho_pilha, int lim);


/**
 * @brief Chama as funções que vão criar as janelas 
 * a guardar os seus endereços nos seus devidos lugares da struct.
 * 
 * @param e Ponteiro para o estado atual do jogo.
 * @param janelas Ponteiro para o struct POINTERS criado no main.
 */
void setPointers(EstadoJogo *e, POINTERS *janelas);

/**
 * @brief Define a janela do botão undo 
 * É criada a janela,e depois feito print do nome do botão. 
 * 
 * @return WINDOW* Endereço da janela do botão
 */
WINDOW* defineButtonUndo();

/**
 * @brief Preenche o array de do struct Pointers, com os endereços de cada uma 
 * das janelas nas posições que as mesmas correspondem no array de PILHA do EstadoJogo. 
 * E chama a função que faz print das pilhas. 
 * 
 * @param e Ponteiro para o estado atual do jogo.
 * @param end_pilhas Array onde estão guardados os endereços das janelas das pilhas.
 * @param total_pilhas Quantas cartas há na pilha,i.e., quantos elementos há no array.
 */
void setPilhas(EstadoJogo *e, WINDOW *end_pilhas[], size_t total_pilhas);

/**
 * @brief Função que vai fazer o print de TODAS as PILHAS. 
 * 
 * @param e Ponteiro para o estado atual do jogo.
 * @param end_pilhas Array onde estão guardados os endereços das janelas das pilhas.
 * @param total_pilhas Quantas cartas há na pilha,i.e., quantos elementos há no array.
 */
void printPilhas(EstadoJogo *e, WINDOW *end_pilhas[], size_t total_pilhas);

int checkFlags_pilha(EstadoJogo *e, char nome_tipo[]);

/**
 * @brief Função que vai fazer o print de TODAS as CARTAS da pilha.
 * Explicação do parâmetro "r": 
 * Se r = 1 -> Todas as cartas da pilha são visíveis.
 * Ser r = 2 -> Nenhuma carta da pilha é visível. 
 * Se r = 3 -> Apenas a carta do topo é visível.
 * 
 * @param win Endereço da janela da pilha.
 * @param x Posição relativa dentro da janela para a coluna do print. 
 * @param y Posição relativa dentro da janela para a linha do print.
 * @param r Índice recebido da printPilhas, indica qual o tipo de print será feito. 
 * @param nome Array com o nome do tipo da pilha. 
 * @param pilha Array de cartas da correspondente pilha.
 * @param tamanho_pilha Quantas cartas há na pilha,i.e., quantos elementos há no array.
 */
void wprint_pilha(WINDOW *win, int x, int y, int r, char nome[], CARTAS *pilha, int tamanho_pilha);

/**
 * @brief Loop que faz o print de todas as cartas da pilha vísiveis. 
 * 
 * @param win Endereço da janela da pilha.
 * @param x Posição relativa dentro da janela para a coluna do print. 
 * @param y  Posição relativa dentro da janela para a linha do print.
 * @param pilha Array de cartas da correspondente pilha.
 * @param tamanho_pilha Quantas cartas há na pilha,i.e., quantos elementos há no array.
 */
void print_todas(WINDOW *win, int x, int y, CARTAS *pilha, int tamanho_pilha);

/**
 * @brief Loop que ou faz o print de todas as cartas, como invisíveis, 
 * ou todas invisíveis e a do topo virada para cima(visível). 
 * 
 * @param win Endereço da janela da pilha.
 * @param x Posição relativa dentro da janela para a coluna do print. 
 * @param y Posição relativa dentro da janela para a linha do print.
 * @param r Índice recebido da printPilhas, indica qual o tipo de print será feito. 
 * @param pilha Array de cartas da correspondente pilha.
 * @param tamanho_pilha Quantas cartas há na pilha,i.e., quantos elementos há no array.
 */
void print_pilhaTopInv(WINDOW *win, int x, int y, int r, CARTAS *pilha, int tamanho_pilha);

/**
 * @brief Função geral que faz print de uma carta numa janela 
 * Dada a carta, chama as funções traduz_valor e traduz_simbolo, e com as informações
 * fornecidas por essas e as coordenadas fornecidas como argumento faz o print da carta. 
 * 
 * @param win Endereço da janela onde o print será feito o print.
 * @param x Coluna de onde se iniciam os prints.
 * @param y Linha de onde se iniam os print.
 * @param c Carta a ser mostrada no ecrã.
 */
void wprint_carta(WINDOW *win, int x, int y, CARTAS c);


/**
 * @brief Recebe da definição da carta, o seu naipe, ou seja um char 
 * e atribui o devido simbólo a esse char. 
 *  
 * 
 * @param naipe 
 * @return const char* endereço da memória onde fica guadado , apenas para leitura, o símbolo
 */
const char* traduzsimbolo(char naipe);

/**
 * @brief "Traduz" o valor da carta 
 * Para os casos mais éspecíficos, onde as cartas acima de 10 passam para J, Q e K 
 * e as cartas de valor 1, passam para A. 
 * 
 * @param valor endereço onde fica guardado o novo valor - um char
 * @param v valor int que vem da definição das cartas 
 */
void traduzvalor(char *valor, char v); 

/**
 * @brief Inicializa e configura a biblioteca ncurses.
 * Prepara o terminal para o jogo: ativa a leitura do rato, TO-DO
 * desativa o eco das teclas (noecho) e inicializa as cores (start_color).
 */
void ativaNcurses();

#endif //DISPLAY_H