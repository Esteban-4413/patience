//
// Created by Esteban Yepez Orozco on 10/05/2026.
//

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
 * @brief 
 * 
 * @param valor 
 * @param v 
 */
void traduzvalor(char *valor, char v);

/**
 * @brief 
 * 
 * @param str 
 * @return CARTAS 
 */
CARTAS le_carta(char *str);

int traduz_valor_numerico(char *str, int len);

#endif