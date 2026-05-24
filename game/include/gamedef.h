/**
 * @file gamedef.h
 * @author your name (you@domain.com)
 * @brief Definição das estruturas de dados que armazenam as regras da DSL de cada paciência.
 * @version 0.1
 * @date 2026-05-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef GAMEDEF_H
#define GAMEDEF_H

#include <stddef.h> // Para usar o size_t

/**
 * @brief Estrutura que define um tipo de pilha no jogo (comando TIPO).
 * 
 * Guarda o nome identificador da pilha e as suas propriedades visuais ou de comportamento.
 * 
 */
typedef struct{
    char nome_tipo[16]; /**< Nome do tipo de pilha (ex: "TAB", "FND", "RST"). */
    char flags[16]; /**< Flags de visualização/comportamento (ex: "=" para visível, "_" para oculta, "^" para topo visível). */
} TipoPilha;

/**
 * @brief Estrutura que define uma regra de movimento manual ou automático (comandos MOV ou AUTO).
 * 
 * Determina de que tipo de pilha as cartas podem sair e para que tipo de pilha podem ir,
 * bem como as restrições desse movimento.
 * 
 */
typedef struct {
    char pilha_origem[16]; /**< Nome do tipo da pilha de onde a carta sai. */
    char pilha_destino[16]; /**< Nome do tipo da pilha para onde a carta vai. */
    char flags[32]; /**< Flags de restrição do movimento (ex: "*" qualquer, "~" alternada, "v" descrescente). */
} Movimento;

/**
 * @brief Estrutura que define uma condição de vitória do jogo (comando WIN).
 * 
 * Especifica quantas cartas têm de estar num determinado tipo de pilha para o jogador ganhar.
 * 
 */
typedef struct{
    char nome_tipo[16]; /**< Nome do tipo de pilha alvo da condição de vitória. */
    int num_cartas; /**< Número de cartas necessárias nessa pilha para cumprir a condição. */
} VictoryCondition;

/**
 * @brief Estrutura que define a inicialização de uma pilha individual no tabuleiro (comando INIT).
 * 
 * Diz ao motor de jogo que deve criar uma nova pilha de um determinado tipo e
 * quantas cartas deve distribuir para ela no início da partida.
 * 
 */
typedef struct {
    char nome_tipo[16]; /**< Nome do tipo da pilha a ser criada no tabuleiro. */
    int num_cartas; /**< Número de cartas a colocar inicialmente nesta pilha. */
} InitPilha;

/**
 * @brief Estrutura principal que armazena todas as regras e configurações de uma paciência.
 * 
 * Esta estrutura é construída pelo parser (parser.c) ao ler o ficheiro `.paciencia`
 * Contém o "ADN" completo do jogo, incluindo os arrays dinâmicos com todas as regras válidas.
 * 
 */
typedef struct {

    char nome[64]; /**< Nome de exibição do jogo (ex: "Golf"). */
    char nome_paciencia[64]; /**< Nome exato do ficheiro original lido (ex: "golf.paciencia"). */
    int num_baralhos; /**< Quantidade de baralhos (de 52 cartas) usados nesta paciência. */

    TipoPilha *tipos; /**< Array dinâmico com os tipos de pilhas definidos no jogo. */
    size_t total_tipos; /**< Número total de tipos de pilhas guardados no array. */

    Movimento *movs; /**< Array dinâmico com as regras de movimentos manuais permitidos. */
    size_t total_movs; /**< Número total de regras de movimento. */

    Movimento *autos; /**< Array dinâmico com as regras de movimentos automáticos. */
    size_t total_autos; /**< Número total de regras automáticas. */

    InitPilha *inits; /**< Array dinâmico com as instruções de inicialização de pilhas. */
    size_t total_inits; /**< Número total de pilhas a criar no tabuleiro inicial. */
    
    VictoryCondition *wins; /**< Array dinâmico com as condições necessárias para vencer. */
    size_t total_wins; /**< Número total de condições de vitória. */

} DefJogo;

#endif 
