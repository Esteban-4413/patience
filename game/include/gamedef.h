

#ifndef GAMEDEF_H
#define GAMEDEF_H

enum caracteristicas_tipo_pilha{
  CARTAS_TODAS_VISIVEIS, // =
  CARTAS_TODAS_INVISIVEIS, // _
  SO_MOSTRA_A_CARTA_TOPO // ^
};

typedef struct{
    char nome_tipo[16];
    enum caracteristicas_tipo_pilha caracteristicas;
    int max_cartas; // -1 = sem limite, 1 = max uma carta 
} TipoPilha;

typedef struct {
    int isAuto; // 0 = mov, 1 = auto
    char pilha_origem[16];
    char pilha_destino[16];
    int total_cartas;
    char flags[16];
} Movimento;

typedef struct {
    TipoPilha *tipos;
    size_t total_tipos;

    Movimento *autos;
    size_t total_autos; 
    Movimento *movs;
    size_t total_movs;
    
    char nome[64];
    
    int num_baralhos;
    
    // Este comando pode ser utilizado múltiplas vezes ao longo do ficheiro, sendo a regra aplicável a conjunção dos vários comandos WIN.
    char tipos_win[8][32]; // numeros arbitrarios 
    int num_cartas_win[8];
    size_t total_wins;

} EstadoJogo;

#endif 
