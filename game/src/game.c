#include "../include/gamestate.h"
#include "../include/display.h"
#include "../include/input.h"
#include "../include/game.h"
#include "../include/undo.h"
#include "../include/move.h"


void loop_principal(EstadoJogo *e, POINTERS *p, int jogando){
    while (jogando) {
        int ch = getch(); 
        // if (ganhou_EstadoJogo(e)){ mvprintw(0,60,"Vitória!"); jogando = 0;}
        if (ch == 'q') jogando = 0; // Condição de saida do EstadoJogo, clicar no "q"
        else if (ch == KEY_MOUSE) {
            processa_rato(e, p);
        }
    }
}


void processa_rato(EstadoJogo *e, POINTERS *p){
    int num_carta;
    // Verifica a existencia de um click
    int r = verifica_click(e, p, &num_carta);
    next_step(r, num_carta, e, p);
}



void next_step (int r, int num_carta, EstadoJogo *e, POINTERS *p){  
    // Click em alguma das pilhas 
    if (r >= 0 && r <= e->total_pilhas -1){
        print_jogAtual(e);

        naPilha(r, num_carta, e, p);  
        
    }

    // Click nos botões 
    if (r == e->total_pilhas){
        mvprintw(10,110, "CLICK NO UNDO");
        undo(e);
        // Atualiza o print de todas as pilhas 
        printPilhas(e, p->end_pilhas, p->total_pilhas);

    }
    
    
}

void naPilha(int r, int num_carta, EstadoJogo *e, POINTERS *p){
    if(e->jog_atual.flag == 1 || e->jog_atual.flag == -1){
            inicializa_jogAtual(e);
        }
    define_jogAtual(r, num_carta, e);
                print_jogAtual(e);

    int pilha = e->jog_atual.pilha;
    int chegada = e->jog_atual.chegada; 
    if (e->jog_atual.flag  == 1 && pilha != chegada) {
        joga(e, e->jog_atual); 
        registar_jogada(e);
            // MOVIMENTOS AUTOMATICOS 
                
        } 
            
    update_pilha(e,p);
  
    
    refresh();  
}

void print_jogAtual(EstadoJogo *e){
    mvprintw(2,110, "PILHA: %d || COLUNA: %d    ", e->jog_atual.pilha, e->jog_atual.coluna);
    mvprintw(3,110, "N: %d || CHEGADA: %d     ", e->jog_atual.n, e->jog_atual.chegada);
    mvprintw(4,110, "FLAG: %d    ", e->jog_atual.flag);
}

void define_jogAtual(int r, int num_carta, EstadoJogo *e){
    if(e->jog_atual.flag == -2){
        e->jog_atual.pilha = r;
        e->jog_atual.coluna = num_carta; 
        //mvprintw(2, 60 , "COLUNA :  %d      .                                  ", num_carta);
        if (num_carta >= 0 ) { // && Valida tamanho da sequencia é válido 
            e->jog_atual.flag = 0;
        } 
        else e->jog_atual.flag = 0;
        
    }
    else if (e->jog_atual.flag == 0) jogAtual_segClick(r, e);
    
}

void jogAtual_segClick(int r, EstadoJogo *e){
    e->jog_atual.chegada = r;
    int v = valida_jogada(e, e->jog_atual); 

    if (r == e->jog_atual.pilha) e->jog_atual.flag = 1;
    else if (v) e->jog_atual.flag = 1; 
    else e->jog_atual.flag = -1; 
    
}
