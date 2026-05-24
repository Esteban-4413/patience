#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Dizemos ao compilador que estas funções existem nos outros ficheiros
extern void test_traduzvalor_especiais(void);
extern void test_traduzvalor_oculta(void); 

extern void test_registar_jogada_vazio(void);
extern void test_registrar_jogada_cheio(void);
extern void test_undo_histVazio(void); 
extern void test_undo_Carta(void); 

extern void test_verifica_vitoria_sucesso(void);
extern void test_define_jogAtual_primeiro_clique(void);
extern void test_jogAtual_segClick_mesma_pilha(void); 
extern void test_jogAtual_segClick_validacao(void); 

int main(){
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
    CU_basic_set_mode(CU_BRM_VERBOSE);

    // 1. Suite Cards
    CU_pSuite pSuiteCards = CU_add_suite("Suite_Card", NULL, NULL);
    if (pSuiteCards != NULL) {
        CU_add_test(pSuiteCards, "Traduz Especiais", test_traduzvalor_especiais);
        CU_add_test(pSuiteCards, "Traduz Desconhecido", test_traduzvalor_oculta);
    }

    // 2. Suite Undo
    CU_pSuite pSuiteUndo = CU_add_suite("Suite_Undo", NULL, NULL);
    if (pSuiteUndo != NULL) {
        CU_add_test(pSuiteUndo, "Historial Vazio", test_registar_jogada_vazio);
        CU_add_test(pSuiteUndo, "Historial Cheio", test_registrar_jogada_cheio);
        CU_add_test(pSuiteUndo, "Undo Historial Vazio", test_undo_histVazio);
        CU_add_test(pSuiteUndo, "Undo uma carta", test_undo_Carta);

    }

    // 3. Suite Game
    CU_pSuite pSuiteGame = CU_add_suite("Suite_Game", NULL, NULL);
    if (pSuiteGame != NULL) {
        CU_add_test(pSuiteGame, "Condição de Vitória", test_verifica_vitoria_sucesso);
        CU_add_test(pSuiteGame, "Test Define Jog Atual - Primeiro Clique", test_define_jogAtual_primeiro_clique);
        CU_add_test(pSuiteGame, "Test Segundo Clique - Mesma Pilha", test_jogAtual_segClick_mesma_pilha);
        CU_add_test(pSuiteGame, "Test Segundo Clique - Validacao", test_jogAtual_segClick_validacao);
    }
}