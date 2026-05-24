/**
 * @file loader.h
 * @brief 
 * @version 0.1
 * @date 2026-05-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef LOADER_H
#define LOADER_H
#include "gamedef.h"
#include <dirent.h>

/**
 * @brief Função principal que orquestra a listagem, seleção e carregamento de uma paciência.
 * 
 * Abre a diretoria especificada, mostra os ficheiros disponíveis e solicita ao utilizador
 * que escolha um. Em caso de erro na abertura da diretoria, devolve uma estrutura DefJogo
 * alocada mas vazia, para evitar crashar o programa.
 * 
 * @param pasta String com o caminho para a diretoria onde os ficheiros .paciencia estão guardados
 * @return DefJogo* Ponteiro para a estrutura com as regras do jogo escolhido, ou estado vazio em caso de erro.
 * 
 * @see lista_ficheiros()
 * @see input_escolha()
 * @see carrega_escolha()
 */
DefJogo* escolhe_paciencia(char *pasta);

/**
 * @brief Pede e valida a escolha numérica do utilizador de forma segura.
 * 
 * Utiliza um ciclo blindado com fgets e sscanf (com boolean flag) para garantir que o
 * utilizador insere um número inteiro válido que esteja entre 1 e o número total de opções.
 * Rejeita letras, símbolos ou números fora dos limites sem bloquear o terminal.
 * 
 * @param conta O número total de opções disponíveis (o limite máximo aceite).
 * @return int O número inteiro correspondente à escolha válida do utilizador.
 * 
 * @see escolhe_paciencia()
 * 
 */
int input_escolha(int conta);

/**
 * @brief Lê e lista todos os ficheiros válidos dentro de uma diretoria.
 * 
 * Percorre a diretoria, ignorando ficheiros ocultos ou de sistema (que começam por '.').
 * Imprime os nomes no ecrã acompanhados de um índice numérico e guarda as strings na matriz.
 * 
 * @param d Ponteiro para a diretoria aberta através de opendir().
 * @param ficheiros Matriz bidimensional de caracteres onde os nomes dos ficheiros serão guardados.
 * @return int O número total de ficheiros de paciências encontrados e listados.
 * 
 * @see escolhe_paciencia()
 * @see copia_string()
 * 
 */
int lista_ficheiros(DIR *d, char ficheiros[][256]);

/**
 * @brief Constrói o caminho completo do ficheiro escolhido e delega o seu carregamento.
 * 
 * Junta a string da pasta com o nome do ficheiro selecionado (baseado no índice escolhido)
 * utilizando sprintf, e passa a string final para o parser (load_paciencia) processar as regras.
 * 
 * @param pasta String com o nome/caminho da diretoria (ex: "paciencias").
 * @param ficheiros Matriz que contém todos os nomes dos ficheiros encontrados.
 * @param escolha O número da opção selecionada pelo utilizador.
 * @return DefJogo* Ponteiro para a definição do jogo carregado a partir do ficheiro escolhido.
 * 
 * @see escolhe_paciencia()
 * @see load_paciencia()
 */
DefJogo* carrega_escolha(char *pasta, char ficheiros[][256], int escolha);


#endif 
