/**
 * @file saveload.h
 * @brief 
 * @version 0.1
 * @date 2026-05-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
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
 * @brief Escreve uma única carta num ficheiro, no formato requerido (ex: "AC", "10S").
 * 
 * @param f Ponteiro para o ficheiro aberto onde a carta será escrita.
 * @param c Estrutura da carta a ser escrita.
 * 
 * @see escreve_pilha()
 * 
 * @see traduzvalor()
 */
void escreve_carta(FILE *f, CARTAS c);

/**
 * @brief Guarda o estado atual do jogo num ficheiro de texto (.txt).
 * 
 * O ficheiro gerado segue as regras da DSL: a primeira linha é o
 * nome do ficheiro da paciência, e as seguintes representam o estado de cada pilha.
 * 
 * @param e Ponteiro para o estado atual do jogo
 * @param ficheiro_save Caminho/Nome do ficheiro onde o jogo será guardado.
 * @param nome_paciencia_original Nome do ficheiro da paciência (ex: "golf.paciencia").
 * 
 * @see load_game()
 * 
 * @see escreve_pilha()
 */
void save_game(EstadoJogo *e, char *ficheiro_save, char *nome_paciencia_original);


/**
 * @brief Carrega um jogo previamente guardado e reconstrói o EstadoJogo.
 * 
 * Lê a primeira linha para identificar o jogo original e carrega as suas regras.
 * Em seguida, reconstrói o tabuleiro lendo as cartas guardadas linha a linha.
 * 
 * @param ficheiro_save Caminho para o ficheiro de save que pretendemos ler.
 * @param pasta_paciencias Pasta onde se encontram os ficheiros originais das regras (.paciencia).
 * @return EstadoJogo O estado do jogo totalmente carregado e pronto a jogar.
 * 
 * @see save_game()
 * 
 * @see carrega_estado_inicial()
 * @see carrega_pilhas()
 * 
 */
EstadoJogo load_game(char *ficheiro_save, char *pasta_paciencias);

/**
 * @brief Analisa uma linha de texto do ficheiro de save e preenche uma pilha.
 * 
 * Corta a string recebida (buffer) nos espaços, traduz cada parte numa carta
 * e adiciona-a ao array da pilha correspondente.
 * 
 * @param buffer String com a linha de texto lida do ficheiro (ex: "AC 10S 2H").
 * @param pilha Ponteiro para a pilha onde as cartas serão guardadas.
 * 
 * @see carrega_pilhas()
 */
void parse_linha_pilha(char *buffer, PILHA *pilha);


/**
 * @brief Escreve todas as cartas de uma pilha numa linha do ficheiro.
 *  
 * Separa as cartas por um espaço, não deixando espaço no final da linha.
 * 
 * @param f 
 * @param pilha 
 * 
 * @see save_game()
 * 
 * @see escreve_carta()
 */
void escreve_pilha(FILE *f, PILHA *pilha);


/**
 * @brief Função auxiliar que inicializa o estado base a partir da leitura do ficheiro de save.
 * 
 * @param f Ponteiro para o ficheiro de save aberto.
 * @param pasta_paciencias Caminho para a pasta das regras
 * @return EstadoJogo Estado do jogo alocado e configurado com as regras bases.
 * 
 * @see load_game()
 * @see escreve_carta()
 * 
 * @see load_paciencia()
 * @see setGameState()
 * 
 */
EstadoJogo carrega_estado_inicial(FILE *f, char *pasta_paciencias);


/**
 * @brief Função auxiliar que percorre as linhas restantes do ficheiro para preencher as pilhas.
 * 
 * @param f Ponteiro para o ficheiro de save aberto.
 * @param e Ponteiro para o EstadoJogo recém-criado que receberá as cartas.
 * 
 * @see load_game()
 * 
 * @see parse_linha_pilha()
 * 
 */
void carrega_pilhas(FILE *f, EstadoJogo *e);


#endif 
