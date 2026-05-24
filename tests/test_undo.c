#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "../game/include/gamestate.h"
#include "../game/include/undo.h"
#include "../game/include/card.h"


void test_registar_jogada_vazio(void){
    EstadoJogo e; 
    e.tamanho_historial = 0;

    // Jogada fictícia 
    e.jog_atual.pilha = 2;
    e.jog_atual.coluna = 4;
    e.jog_atual.chegada = 5;
    e.jog_atual.n = 1;

    registar_jogada(&e);

    // Verifica se na posição do historial foi passada a jogada corretamente
    CU_ASSERT_EQUAL(e.tamanho_historial, 1);
    CU_ASSERT_EQUAL(e.historial[0].pilha, 2);
    CU_ASSERT_EQUAL(e.historial[0].coluna, 4);
    CU_ASSERT_EQUAL(e.historial[0].chegada, 5);
    CU_ASSERT_EQUAL(e.historial[0].n, 1);
}

void test_registrar_jogada_cheio(void){
    EstadoJogo e;
    e.tamanho_historial = MAX_UNDO; 

    // Opcional: Vamos criar uma jogada antiga no índice 1 para testar o "empurrão"
    e.historial[1].pilha = 1;
    e.historial[1].coluna = 1;
    e.historial[1].chegada = 1;
    e.historial[1].n = 1;

    // Nova jogada fictícia que vai entrar
    e.jog_atual.pilha = 5;
    e.jog_atual.coluna = 10;
    e.jog_atual.chegada = 8;
    e.jog_atual.n = 5;

    registar_jogada(&e);
    
    // O tamanho final tem de continuar a ser MAX_UNDO
    CU_ASSERT_EQUAL(e.tamanho_historial, MAX_UNDO);

    // CORREÇÃO: A nova jogada tem de estar no FIM do historial (índice MAX_UNDO - 1)
    int ultimo_indice = MAX_UNDO - 1;
    CU_ASSERT_EQUAL(e.historial[ultimo_indice].pilha, 5);
    CU_ASSERT_EQUAL(e.historial[ultimo_indice].coluna, 10);
    CU_ASSERT_EQUAL(e.historial[ultimo_indice].chegada, 8);
    CU_ASSERT_EQUAL(e.historial[ultimo_indice].n, 5);

    // Extra de Segurança: Verificar se a antiga jogada do índice 1 foi parar ao índice 0
    CU_ASSERT_EQUAL(e.historial[0].pilha, 1);
}


void test_undo_histVazio(void){
    EstadoJogo e;
    e.tamanho_historial = 0;

    undo(&e);

    CU_ASSERT_EQUAL(e.tamanho_historial, 0); 
}

void test_undo_Carta(void) {
    // 1. Alocar o Estado do Jogo
    EstadoJogo *e = malloc(sizeof(EstadoJogo));
    if (e == NULL) return;

    // 2. Alocar o array de pilhas (vamos simular que o jogo tem pelo menos 2 pilhas: origem 0 e chegada 1)
    e->total_pilhas = 2;
    e->pilhas = malloc(2 * sizeof(PILHA));
    if (e->pilhas == NULL) { free(e); return; }

    // 3. Alocar espaço para as cartas dentro de cada pilha (ex: máximo de 10 cartas para o teste)
    e->pilhas[0].pilha = malloc(10 * sizeof(CARTAS));
    e->pilhas[1].pilha = malloc(10 * sizeof(CARTAS));
    if (e->pilhas[0].pilha == NULL || e->pilhas[1].pilha == NULL) {
        free(e->pilhas[0].pilha); free(e->pilhas[1].pilha);
        free(e->pilhas); free(e);
        return;
    }

    // 4. Configurar os tamanhos falsos pós-jogada
    e->pilhas[0].tamanho_pilha = 4; // Origem (tinha 5, agora tem 4)
    e->pilhas[1].tamanho_pilha = 2; // Chegada (tinha 1, agora tem 2)
    
    // Colocar a carta a ser devolvida no topo da chegada (índice 1)
    CARTAS c; 
    c.valor = 5; 
    c.naipe = 'C'; 
    e->pilhas[1].pilha[1] = c; 

    // 5. Configurar o Historial simulando a jogada
    e->tamanho_historial = 1;
    e->historial[0].pilha = 0;       // Origem
    e->historial[0].chegada = 1;     // Chegada
    e->historial[0].coluna = 4;      // Ia voltar para a posição 4 da origem
    e->historial[0].n = 1;           // 1 carta movida

    // Executar a função
    undo(e);

    // 6. Asserções (Validações)
    CU_ASSERT_EQUAL(e->tamanho_historial, 0);
    CU_ASSERT_EQUAL(e->pilhas[0].tamanho_pilha, 5); 
    CU_ASSERT_EQUAL(e->pilhas[1].tamanho_pilha, 1); 
    CU_ASSERT_EQUAL(e->pilhas[0].pilha[4].naipe, c.naipe); 
    CU_ASSERT_EQUAL(e->pilhas[0].pilha[4].valor, c.valor); 

    // 7. Libertar toda a memória alocada
    free(e->pilhas[0].pilha);
    free(e->pilhas[1].pilha);
    free(e->pilhas);
    free(e);
}