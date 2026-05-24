/**
 * @file card.h
 * @brief 
 * @version 0.1
 * @date 2026-05-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef CARD_H
#define CARD_H

/**
 * @brief Estrutura que representa uma única carta do baralho.
 * 
 */
typedef struct {
    int valor; /**< Valor numérico da carta (ex: 1 para Ás, 11 para Valete, 12 para Dama, 13 para Rei). */
    char naipe; /**< Carácter que representa o naipe da carta (ex: 'P' paus, 'O' ouros, 'C' copas, 'E' espadas). */
} CARTAS;

/**
 * @brief Converte o valor numérico de uma carta para a sua representação em texto.
 * * Transforma os valores especiais (1, 11, 12, 13) nas respetivas letras ("A", "J", "Q", "K").
 * * Os valores de 2 a 10 são mantidos como números, mas convertidos para formato string.
 * @param valor Ponteiro para a string (buffer) onde o resultado será guardado.
 * @param v Valor numérico da carta que pretendemos traduzir.
 * 
 * @see escreve_carta()
 */
void traduzvalor(char *valor, char v);

/**
 * @brief Converte uma string (ex: "10S", "AC") numa estrutura CARTAS.
 * * Lê a string, identifica o naipe (o último carácter) e o valor (os restantes).
 * * Faz o processo inverso da função traduzvalor.
 * 
 * @param str String que contém a representação textual da carta.
 * @return CARTAS A estrutura da carta preenchida com o valor e o naipe correspondentes.
 * 
 * @see parsel_linha_pilha
 */
CARTAS le_carta(char *str);


/**
 * @brief Função auxiliar para extrair o valor numérico de uma string de carta.
 * * Lê os caracteres numéricos (ignorando o naipe no final) e converte-os para um inteiro.
 * 
 * @param str String que contém a representação textual da carta (ex: "10S").
 * @param len Tamanho total da string.
 * @return int O valor numérico extraído (ex: 10).
 * 
 * @see le_carta()
 */
int traduz_valor_numerico(char *str, int len);

#endif