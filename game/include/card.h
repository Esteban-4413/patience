//
// Created by Esteban Yepez Orozco on 10/05/2026.
//

#ifndef PATIENCE_CARD_H
#define PATIENCE_CARD_H

/**
 * @brief Estrutura que representa uma única carta do baralho.
 * 
 */
typedef struct {
    int valor; /**< Valor numérico da carta (ex: 1 para Ás, 11 para Valete, 12 para Dama, 13 para Rei). */
    char naipe; /**< Carácter que representa o naipe da carta (ex: 'P' paus, 'O' ouros, 'C' copas, 'E' espadas). */
} CARTAS;

#endif //PATIENCE_CARD_H
