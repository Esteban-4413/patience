
#ifndef INPUT_H
#define INPUT_H

#include "../include/gamestate.h"
#include "../include/card.h"
#include "../include/utils.h"
#include "../ui/display.h"

/**
 * @brief Identifica o evento do rato e o classifica
 *
 * Depois de identificar o evento do rato, chama a função eclickValido,
 * para classificar se o click foi em algum lugar válido para o jogo.
 * @param e Ponteiro para a estrutura principal do jogo.
 * @param janelas Ponteiro para a estrutura que guarda todas as janelas (POINTERS).
 * @param num_carta Ponteiro de onde, caso preciso, deve guarda o número da carta na pilha que foi clicada.
 * @return int 
 */
int verifica_click (EstadoJogo *e, POINTERS *janelas, int *num_carta);

/**
 * @brief Atribui um int para cada tipo específico de click
 *
 * A lógica é:
 * Para as pilhas, se o click for na pilha vai retornar o próprio número da pilha 
 *  ( Ou seja, um número de 0 a total_pilhas -1 )
 *  Se for:
 *  Botão Undo -> total_pilhas (número total de pilhas que existe no jogo) 
 *  
 * Definindo se o click se enquadra, ou não, em alguma destas janelas 
 * com o auxilio da função eclicknaPilha.
 * 
 * @param x Coluna onde ocorreu o click
 * @param y Linha onde ocorreu o click
 * @param janelas Ponteiro para a estrutura que guarda todas as janelas (POINTERS).
 * @return int Indentifica onde foi feito o click
 */
int eclickValido(int x, int y, POINTERS *janelas); 

/**
 * @brief Função específica para verificar se o click foi em alguma das pilhas 
 *
 * Verifica pilha a pilha se o click pertence a aquela pilha, 
 * chamando a função eJanela com o endereço de cada uma das pilhas. 
 *  Se estiver em alguma das pilhas, vai retornar exatamente o int que corresponde ao índice dessa pilha 
 *  no array "pilhas".
 * 
 * @param x Coluna onde ocorreu o click
 * @param y Linha onde ocorreu o click
 * @param janela_pilha Array onde estão guardados os endereços das janelas das pilhas
 * @return int Retorna o indice da pilha, ou -1 caso o click não se enquandre em nenhuma das pilhas
 */
int eclicknaPilha(int x, int y, WINDOW *janela_pilha[]);

/**
 * @brief Verifica se coordenadas estão dentro de uma janela
 * 
 * Recebe o endereço da janela, que queremos testar para com ele usar a função tamanho_janela. 
 * E com essa função obtemos nas variáveis "xmin, xmax, ymin, ymax" , os limites para enquadra 
 * as coordenadas do click, e verificar se está contido no intervalo. 
 * 
 * @param win Endereço da janela que queremos testar 
 * @param x Coluna onde ocorreu o click
 * @param y Linha onde ocorreu o click
 * @return int Bool 
 */
int eJanela(WINDOW *win, int x, int y);

/**
 * @brief Calcula limites das coordenadas de uma janela específica
 * 
 * Recebe da eJanela os endereços das variáveis, e nelas guarda, com o auxilio das funções do ncurses 
 * -> getbegyx, que gaurada em ymin, e xmin, respectivamente, a linha e a coluna onde se encontra o ponto 
 * superior esquerdo da janela
 * -> getmaxyx, que dá a altura e largura da janela 
 *  E com os valores da altura e largura, calculamos o ymax (linha máxima) e o xmax (coluna máxima);
 * 
 * @param win 
 * @param xmin Endereço recebido da eJanela para guardar o valor mínimo da coluna 
 * @param xmax Endereço recebido da eJanela para guardar o valor máximo da coluna
 * @param ymin Endereço recebido da eJanela para guardar o valor mínimo da linha 
 * @param ymax Endereço recebido da eJanela para guardar o valor máximo da linha
 */
void tamanhojanela(WINDOW *win, int *xmin, int *xmax, int *ymin, int *ymax);



/**
 * @brief A partir da linha e da pilha onde foi feito o click, é
 * calculado qual o índice da carta, na matriz, que foi clicada. 
 * 
 * @param y_click Linha na qual foi detectado o click.
 * @param pilha Pilha na qual foi detectado o click.
 * @param e Ponteiro para a estrutura principal do jogo.
 * @return int Índice da carta que foi clicada, ou -1 em caso do click não ser em nenhuma carta da pilha. 
 */
int coords_para_carta(int y_click, int pilha, EstadoJogo *e); 

#endif //INPUT_H