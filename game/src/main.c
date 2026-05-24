
#include <stdio.h>
#include <locale.h>
#include "../include/gamedef.h"
#include "../include/parser.h"
#include "../include/gamestate.h"
#include "../include/card.h"
#include "../include/display.h"
#include "../include/game.h"
#include "../include/loader.h"
#include "../include/saveload.h"


int main(){

    EstadoJogo e = menu("paciencias", "save.txt");

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

