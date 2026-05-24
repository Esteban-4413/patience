/**
 * @file utils.h
 * @brief 
 * @version 0.1
 * @date 2026-05-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Encontra a primeira ocorrência de um carácter numa string.
 * 
 * Percorre a string até encontrar o carácter especificado ou atingir o final da string ('\0').
 * É particularmente útil para detetar o início de comentários (como o '#') durante o parsing.
 * 
 * @param str A string onde a procura será realizada.
 * @param c O carácter a procurar.
 * @return char* Ponteiro para a primeira ocorrência do carácter, ou NULL se não existir.
 * 
 * @see processa_linha()
 */
char * aux_string(char *str, char c);

/**
 * @brief Compara duas strings de forma lexicográfica (semelhante ao strcmp).
 * 
 * Compara os caracteres de ambas as strings sequencialmente até encontrar uma diferença
 * ou chegar ao final. Utilizada para identificar os comandos lidos da DSL.
 * 
 * @param a Primeira string a comparar.
 * @param b Segunda string a comparar.
 * @return int Retorna 0 se as strings forem exatamentes iguais.
 * Um valor < 0 se a < b, ou um valor > 0 se a > b.
 * 
 * @see what_command()
 * 
 */
int comp_strings(char a[], char b[]);

/**
 * @brief Copia o conteúdo de uma string para outra (semelhante ao strcpy).
 * 
 * Copia os caracteres da string de origem para o buffer de destino, garantindo
 * que o carácter nulo de terminação ('\0') é devidamente incluído no final.
 * 
 * @param dest O buffer de destino onde a cópia será guardada.
 * @param source A string original que será copiada.
 * @return char* Ponteiro para a string de destino (dest).
 * 
 * @see lista_ficheiros()
 */
char *copia_string (char *dest, char source[]); 

#endif 
