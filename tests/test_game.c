#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "../game/include/display.h"
#include "../game/include/gamestate.h"
#include "../game/include/game.h"
#include "../game/include/utils.h"




void test_verifica_vitoria_sucesso(void) {
    EstadoJogo *e = malloc(sizeof(EstadoJogo));
    e->def_jogo = malloc(sizeof(DefJogo));
    
    // 1. Configurar a condição de vitória do jogo (ex: 1 pilha do tipo "Fim" com 13 cartas)
    e->def_jogo->total_wins = 1;
    e->def_jogo->wins = malloc(sizeof(VictoryCondition));
    copia_string( e->def_jogo->wins[0].nome_tipo, "Fim");
    e->def_jogo->wins[0].num_cartas = 13;

    // 2. Configurar o estado atual das pilhas do jogo (Simular que o jogador já arrumou as 13 cartas)
    e->total_pilhas = 1;
    e->pilhas = malloc(sizeof(PILHA));
    // Alocar espaço para a string (ex: 10 bytes chegam perfeitamente para "Fim")
    e->pilhas[0].nome_tipo = malloc(10 * sizeof(char));
    // Copiar o texto usando a tua própria função utilitária
    copia_string(e->pilhas[0].nome_tipo, "Fim");

    e->pilhas[0].tamanho_pilha = 13; // Está cheia!

    // 3. Executar e Validar
    int resultado = verifica_vitoria(e);
    CU_ASSERT_EQUAL(resultado, 1); // Tem de retornar 1 (Vitória!)

    // Limpeza
    free(e->pilhas); free(e->def_jogo->wins); free(e->def_jogo); free(e);
}

// --- 1. Teste do Primeiro Clique (Flag == -2) ---
void test_define_jogAtual_primeiro_clique(void) {
    EstadoJogo *e = malloc(sizeof(EstadoJogo));
    e->total_pilhas = 3;
    e->pilhas = malloc(3 * sizeof(PILHA));
    
    // Simular que a pilha 0 tem 5 cartas
    e->pilhas[0].pilha = malloc(10 * sizeof(CARTAS));
    e->pilhas[0].tamanho_pilha = 5;

    // Estado inicial: sem nenhuma carta selecionada
    e->jog_atual.flag = -2;

    // Cenário: Utilizador clica na pilha 0, na carta do índice 2
    // Isso significa que ele quer mover as cartas do índice 2 até ao topo (5 - 2 = 3 cartas)
    define_jogAtual(0, 2, e);

    // Validações
    CU_ASSERT_EQUAL(e->jog_atual.pilha, 0);       // Origem guardada
    CU_ASSERT_EQUAL(e->jog_atual.coluna, 2);      // Índice da carta guardado
    CU_ASSERT_EQUAL(e->jog_atual.n, 3);           // Calculou que vai mover 3 cartas (5 - 2)
    CU_ASSERT_EQUAL(e->jog_atual.flag, 0);        // Transição de estado: flag passou de -2 para 0

    // Limpeza de memória
    free(e->pilhas[0].pilha);
    free(e->pilhas);
    free(e);
}

// --- 2. Teste do Segundo Clique: Clicar na mesma pilha ---
void test_jogAtual_segClick_mesma_pilha(void) {
    EstadoJogo *e = malloc(sizeof(EstadoJogo));
    if (e == NULL) return;

    // Alocar pilhas simuladas para a função valida_jogada não dar crash
    e->total_pilhas = 2;
    e->pilhas = malloc(2 * sizeof(PILHA));
    if (e->pilhas != NULL) {
        e->pilhas[0].pilha = malloc(5 * sizeof(CARTAS));
        e->pilhas[1].pilha = malloc(5 * sizeof(CARTAS));
        e->pilhas[0].tamanho_pilha = 0;
        e->pilhas[1].tamanho_pilha = 0;
    }
    
    // Configurar a jogada atual simulando que o 1º clique foi na pilha 1
    e->jog_atual.flag = 0;
    e->jog_atual.pilha = 1;
    e->jog_atual.coluna = 0;
    e->jog_atual.n = 1;

    // Cenário: Clica outra vez na mesma pilha (1)
    jogAtual_segClick(1, e);

    // Validação
    CU_ASSERT_EQUAL(e->jog_atual.chegada, 1);
    CU_ASSERT_EQUAL(e->jog_atual.flag, 1); 

    // Limpeza
    if (e->pilhas) {
        free(e->pilhas[0].pilha);
        free(e->pilhas[1].pilha);
        free(e->pilhas);
    }
    free(e);
}

// --- 3. Teste do Segundo Clique: Validação Geral ---
void test_jogAtual_segClick_validacao(void) {
    EstadoJogo *e = malloc(sizeof(EstadoJogo));
    if (e == NULL) return;

    e->total_pilhas = 3;
    e->pilhas = malloc(3 * sizeof(PILHA));
    if (e->pilhas != NULL) {
        e->pilhas[0].pilha = malloc(5 * sizeof(CARTAS));
        e->pilhas[2].pilha = malloc(5 * sizeof(CARTAS));
        e->pilhas[0].tamanho_pilha = 0;
        e->pilhas[2].tamanho_pilha = 0;
    }
    
    e->jog_atual.flag = 0;
    e->jog_atual.pilha = 0;
    e->jog_atual.coluna = 0;
    e->jog_atual.n = 1;
    
    // Cenário: Clica na pilha 2 (Pilha diferente da de origem)
    jogAtual_segClick(2, e);
    
    // Valida se o estado mudou para um dos valores esperados (-1 ou 1)
    // prevenindo que tenha ficado parado em 0
    CU_ASSERT_TRUE(e->jog_atual.flag == 1 || e->jog_atual.flag == -1);

    if (e->pilhas) {
        free(e->pilhas[0].pilha);
        free(e->pilhas[2].pilha);
        free(e->pilhas);
    }
    free(e);
}