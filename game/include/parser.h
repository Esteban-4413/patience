/**
 * @file parser.h
 * @brief 
 * @version 0.1
 * @date 2026-05-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef PARSER_H
#define PARSER_H
#include "gamedef.h"


/**
 * @brief Abre e lê um ficheiro de texto (.paciencia) para carregar as regras do jogo.
 * 
 * Lê o ficheiro linha a linha, ignora os comentários (tudo o que estiver à direita de '#')
 * e utiliza a função what_command para interpretar e guardar cada instrução lida.
 * 
 * @param ficheiro Caminho para o ficheiro de texto que contém a DSL da paciência (ex: "paciencias/golf.paciencia").
 * @return DefJogo* Ponteiro para a estrutura que contém todas as definições estruturais e regras do jogo.
 * 
 * @see inicializa_estado()
 * @see what_command()
 */
DefJogo* load_paciencia(char *ficheiro);


/**
 * @brief Aloca memória e inicializa a estrutura principal de regras do jogo.
 * Prepara uma nova estrutura DefJogo, colocando todos os contadores a zero (total_tipos,
 * total_movs, etc.) e os respetivos ponteiros a NULL para garantir que a memória
 * não tem "lixo" antes de o ficheiro começar a ser lido.
 * 
 * @return DefJogo* Ponteiro para a nova estrutura inicializada.
 * @see load_paciencia()
 */
DefJogo* incializa_estado(void);


/**
 * @brief Identifica o comando lido do ficheiro e guarda a informação na estrutura DefJogo.
 * Compara a string do comando ("JOGO", "BARALHOS", "TIPO", "MOV", "AUTO", "INIT", "WIN")
 * e utiliza o sscanf para extrair os argumentos do resto do buffer. Realoca a memória dos
 * arrays correspondentes (ex: est->movs, est->inits) consoante for necessário.
 * 
 * @param comando String que contém a primeira palavra (o comando) da linha atual.
 * @param buffer String com a linha completa lida do ficheiro de texto.
 * @param est Ponteiro para a definição do jogo que está a ser preenchida.
 */
void what_command(char * comando, char *buffer, DefJogo *est);

/**
 * @brief Processa o comando "TIPO" e adiciona a informação ao estado do jogo.
 * 
 * Aumenta o contador de tipos, realoca a memória do array de tipos e guarda o nome e as flags.
 * 
 * @param buffer String com a linha completa do comando.
 * @param est Ponteiro para o estado do jogo (DefJogo).
 * 
 * @see what_command()
 */
void cmd_tipo(char *buffer, DefJogo *est);

/**
 * @brief Processa o comando "INIT" e adiciona a configuração inicial ao estado.
 * 
 * Aumenta o contador de inits, realoca a memória do array e guarda o tipo da pilha e o número de cartas.
 * 
 * @param buffer String com a linha completa do comando.
 * @param est Ponteiro para o estado do jogo (DefJogo).
 * 
 * @see what_command() 
 */
void cmd_init(char *buffer, DefJogo *est);

/**
 * @brief Processa o comando "AUTO" e adiciona um movimento automático às regras.
 * 
 * Realoca a memória do array de movimentos automáticos e guarda a origem, o destino e as flags.
 * 
 * @param buffer String com a linha completa do comando.
 * @param est Ponteiro para o estado do jogo (DefJogo).
 * 
 * @see what_command()
 */
void cmd_auto(char *buffer, DefJogo *est);

/**
 * @brief Processa o comando "WIN" e define uma condição de vitória.
 * 
 * Realoca o array de condições de vitória e guarda a pilha alvo e a quantidade de cartas necessária.
 * 
 * @param buffer String com a linha completa do comando.
 * @param est Ponteiro para o estado do jogo (DefJogo).
 * 
 * @see what_command()
 */
void cmd_win(char *buffer, DefJogo *est);

/**
 * @brief Processa o comando "MOV" e adiciona uma regra de movimento válida.
 * 
 * Realoca o array de movimentos válidos e regista a pilha de origem, a pilha de destino e as restrições (flags).
 * 
 * @param buffer String com a linha completa do comando.
 * @param est Ponteiro para o estado do jogo (DefJogo).
 * 
 * @see what_command()
 */
void cmd_mov(char *buffer, DefJogo *est);

/**
 * @brief Analisa uma linha lida do ficheiro, remove os comentários e extrai o comando principal.
 * 
 * Procura o carácter '#' para ignorar comentários. De seguida, extrai a primeira
 * palavra da linha (se existir) e envia-a para a função what_command.
 * 
 * @param buffer String com a linha completa acabada de ler do ficheiro.
 * @param est Ponteiro para o estado do jogo a ser configurado.
 * @return int Retorna 1 após o processamento da linha.
 * 
 * @see load_paciencia()
 */
int processa_linha(char *buffer, DefJogo *est);



#endif 
