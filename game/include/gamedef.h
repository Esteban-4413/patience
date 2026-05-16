

#ifndef GAMEDEF_H
#define GAMEDEF_H

#include <stddef.h>

typedef struct{
    char nome_tipo[16]; // TAB e whatnot
    char flags[16]; // ex: "=", "_", "^"
} TipoPilha;

typedef struct {
    char pilha_origem[16];
    char pilha_destino[16];
    char flags[32]; // ex: "*", "~", etc.
} Movimento;

typedef struct{
    char nome_tipo[16];
    int num_cartas;
} VictoryCondition;

typedef struct {
    char nome_tipo[16];
    int num_cartas;
} InitPilha;

typedef struct {

    char nome[64]; // nome do jogo
    int num_baralhos;

    TipoPilha *tipos;
    size_t total_tipos;

    Movimento *movs;
    size_t total_movs;

    Movimento *autos;
    size_t total_autos;

    InitPilha *inits;
    size_t total_inits;
    
    VictoryCondition *wins;
    size_t total_wins;

} DefJogo;

#endif 
