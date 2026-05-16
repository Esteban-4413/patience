#include <stdio.h>
#include <ncurses.h>
#include "../ui/input.h"



int verifica_click (EstadoJogo *e, POINTERS *janelas, int *num_carta) {
    MEVENT event;
    if (getmouse(&event) == OK) {
        int r = eclickValido(event.x, event.y, janelas);
        if(r >= 0 && r < 11) *num_carta = coords_para_carta(event.y, r, e);
        return r;
    }
    return -1;
}

int eclickValido(int x, int y, POINTERS *janelas) {
    if (eJanela(janelas->end_undo, x, y)) return (12); //total_pilhas -1 ;
    else return eclicknaPilha(x, y, janelas->end_pilhas); 
        // Verifica as pilhas 
        /* 
        Vai passar a dar de o índice da pilha no array de pilhas 
        */

    return -1; 

}

int eclicknaPilha(int x, int y, WINDOW *janela_pilha[]){
    for (int i = 0; i < 10; i++) {
        if (eJanela(janela_pilha[i], x, y)) {
            return i; 
            }
        }
    return -1;
}

int eJanela(WINDOW *win, int x, int y) {
    int xmin, xmax, ymin, ymax;
    tamanhojanela(win, &xmin, &xmax, &ymin, &ymax);
    
    // x tem de estar ENTRE o min e o max
    if ((x >= xmin) && (x <= xmax) && (y >= ymin) && (y <= ymax)) return 1;
    return 0;
}

void tamanhojanela(WINDOW *win, int *xmin, int *xmax, int *ymin, int *ymax) {
    int altura, largura;

    // guarda no x e no y as coordenadas onde se encontra o ponto superior esquerdo da janela
    getbegyx(win, *ymin, *xmin); 

    //guarda no x e no y as dimensões da janela
    getmaxyx(win, altura, largura); 

    *ymax = *ymin + altura - 1; // -1 porque as coordenadas são inclusivas
    *xmax = *xmin + largura - 1; 
}

// ------- DEFINE COLUNA DO CLIQUE ------- 
int coords_para_carta(int x, int pilha, EstadoJogo *e){
    const int offset = 5;
    const int comprimento_cabeca_carta = 1;
    const int comprimento_carta = 1;
    
    if (x < offset) {
        return -1; /*< Clique fora da pilha (em cima dela)*/
    }
    int idx = (x - offset);
    
    
    if (idx >= e->pilhas[pilha].tamanho_pilha - 1){
        return (e->pilhas[pilha].tamanho_pilha -1);
    }
    
    
    return idx;
}