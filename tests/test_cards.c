#include <CUnit/CUnit.h>
#include "../game/include/card.h"

// --- Figuras e Ás ---
void test_traduzvalor_especiais(void) {
    char buffer[10]; // Buffer para guardar o resultado do mapeamento

    // Testar o Ás (1)
    traduzvalor(buffer, 1);
    CU_ASSERT_STRING_EQUAL(buffer, "A");

    // Testar o Valete (11)
    traduzvalor(buffer, 11);
    CU_ASSERT_STRING_EQUAL(buffer, "J" );

    // Testar a Dama (12)
    traduzvalor(buffer, 12);
    CU_ASSERT_STRING_EQUAL(buffer, "Q" );

    // Testar o Rei (13)
    traduzvalor(buffer, 13);
    CU_ASSERT_STRING_EQUAL(buffer, "K" );
}

// --- Carta Oculta / Desconhecida ---
void test_traduzvalor_oculta(void) {
    char buffer[10];

    // Testar o valor 0 (costuma representar cartas viradas para baixo ou lixo)
    traduzvalor(buffer, 0);
    CU_ASSERT_STRING_EQUAL(buffer, "?" );
}

