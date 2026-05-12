
#include <stdio.h>
#include "../include/gamedef.h"
#include "../include/parser.h"
#include "../include/gamestate.h"
#include "../include/card.h"

int main(){
    DefJogo jogo = load_paciencia("paciencias/golf.paciencia");
    printf("Jogo: %s\n", jogo.nome);
    printf("Baralhos: %d\n", jogo.num_baralhos);
    printf("Total tipos: %zu\n", jogo.total_tipos);
    printf("Total movs: %zu\n", jogo.total_movs);
    printf("Total inits: %zu\n", jogo.total_inits);
    printf("Total wins: %zu\n", jogo.total_wins);   

    EstadoJogo e = setGameState(jogo);
    print_pilhas(&e); 
    return 0;

}

