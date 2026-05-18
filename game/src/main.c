
#include <stdio.h>
#include <locale.h>
#include "../include/gamedef.h"
#include "../include/parser.h"
#include "../include/gamestate.h"
#include "../include/card.h"
#include "../include/display.h"
#include "../include/game.h"
#include "../include/loader.h"


int main(){
    DefJogo jogo = escolhe_paciencia("paciencias");
    /*
    printf("Jogo: %s\n", jogo.nome);
    printf("Baralhos: %d\n", jogo.num_baralhos);
    printf("Total tipos: %zu\n", jogo.total_tipos);
    printf("Total movs: %zu\n", jogo.total_movs);
    printf("Total inits: %zu\n", jogo.total_inits);
    printf("Total wins: %zu\n", jogo.total_wins); 

    ----------------------
    print_pilhas(&e); 

    */

    EstadoJogo e = setGameState(jogo);
    print_pilhas(&e);
    printf("Total pilhas: %d\n", e.total_pilhas);
    printf("Total inits: %zu\n", jogo.total_inits);
    POINTERS janelas;
    // codificação de caracteres
    setlocale(LC_ALL, ""); 

    // Função do aux_main - ativa as configurações gerais do Ncurses 
    ativaNcurses(); 
    setPointers(&e, &janelas);
    int jogando = 1;
    loop_principal(&e, &janelas, jogando);
    
    endwin();
    
    return 0;

}

