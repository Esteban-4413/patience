#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ncurses.h>
#include "../include/display.h"
#include "../include/utils.h"
#include "../include/card.h"
#include "../include/gamedef.h"



// ------- ATUALIZA JANELAS -------
void update_pilha(EstadoJogo *e, POINTERS *janelas){
    int s = e->jog_atual.pilha; // índice da pilha de saida
    int rs = checkFlags_pilha(e, (e->pilhas[s].nome_tipo));

    if (e->jog_atual.flag == 0 && e->jog_atual.pilha != (-1)) {
        int lim = e->jog_atual.coluna; 
        wprint_pilha(janelas->end_pilhas[s], 2, 1, rs, e->pilhas[s].nome_tipo, e->pilhas[s].pilha, e->pilhas[s].tamanho_pilha, 1, lim); 
    }
    else if (e->jog_atual.flag == 1 && e->jog_atual.coluna != (-1)){  
        int c = e->jog_atual.chegada; // índice da pilha de chegada 
        
        int rc = checkFlags_pilha(e, (e->pilhas[c].nome_tipo));
        wprint_pilha(janelas->end_pilhas[s], 2, 1, rs, e->pilhas[s].nome_tipo, e->pilhas[s].pilha, e->pilhas[s].tamanho_pilha, 0, 0); // SAIDA
        wprint_pilha(janelas->end_pilhas[c], 2, 1, rc, e->pilhas[c].nome_tipo, e->pilhas[c].pilha, e->pilhas[c].tamanho_pilha, 0, 0); // CHEGADA
               
    } else {
        wprint_pilha(janelas->end_pilhas[s], 2, 1, rs, e->pilhas[s].nome_tipo, e->pilhas[s].pilha, e->pilhas[s].tamanho_pilha, 0, 0); // SAIDA // TIRA O QUE TAVA EM NEGRITO - jogada inválida
   
    } 
}


// ------- INICILIZA JANELAS -------
void setPointers(EstadoJogo *e, POINTERS *janelas){
    // Pilhas 
    int size = e->total_pilhas;
    WINDOW **end_pilhas = malloc(size * sizeof(WINDOW*)); // Cria o array de pointers de janelas 

    setPilhas(e, end_pilhas, size);

    janelas->total_pilhas = size; 
    janelas->end_pilhas = end_pilhas; 

    // UNDO 
    janelas->end_undo = defineButtonUndo(); 

    // SAVE 
    janelas->end_save = defineButtonSave();
    
    
}
// -------  BOTÃO UNDO -------
WINDOW* defineButtonUndo(){ 
        WINDOW *janela_undo;
        janela_undo = newwin(3, 10, 1, 30);
        box(janela_undo, 0, 0);
        wattron(janela_undo, COLOR_PAIR(3));
        mvwprintw(janela_undo, 1, 1, "  UNDO");
        wrefresh(janela_undo);
        wattroff(janela_undo, COLOR_PAIR(3));

        return janela_undo; 

}

// -------  BOTÃO SAVE -------
WINDOW* defineButtonSave(){ 
        WINDOW *janela_save;
        janela_save = newwin(3, 10, 1, 40);    
        box(janela_save, 0, 0);
        wattron(janela_save, COLOR_PAIR(3));
        mvwprintw(janela_save, 1, 1, "  SAVE");
        wrefresh(janela_save);
        wattroff(janela_save, COLOR_PAIR(3));

        return janela_save; 

}

// ------- POINTERS DE TODAS AS PILHAS -------
void setPilhas(EstadoJogo *e, WINDOW *end_pilhas[], size_t total_pilhas){

    int x = 4;
    int y = 4;
    for (int i = 0; i < total_pilhas; i++){
        end_pilhas[i] = newwin(40, 8, y, x);
        x+=9;
    }
    printPilhas(e, end_pilhas, total_pilhas);

}

// ------- PRINT DE TODAS AS PILHAS -------
void printPilhas(EstadoJogo *e, WINDOW *end_pilhas[], size_t total_pilhas){
    int r = 0; 
    //int rAnt = 0; 

    int y_local = 1; 
    int x_local = 2;
    for (int i = 0; i < total_pilhas; i++){           
        r = checkFlags_pilha(e, e->pilhas[i].nome_tipo);

        wprint_pilha(end_pilhas[i], x_local, y_local, r, e->pilhas[i].nome_tipo, e->pilhas[i].pilha, e->pilhas[i].tamanho_pilha, 0, 0);
    } 
    
}

int checkFlags_pilha(EstadoJogo *e, char nome_tipo[]){
    char *f;

    int lim = e->def_jogo->total_tipos ; // Total de tipos de pilhas existentes 
    int i = 0;

    while ( i < lim && (comp_strings(nome_tipo, e->def_jogo->tipos[i].nome_tipo))){
        i++;
    }

    if (i < lim) {
    f = e->def_jogo->tipos[i].flags;

    for(int j = 0; j < 2; j++){ 
        if ( f[j] == '=') return 1; 
        else if (f[j] == '_') return 2;
        else if ( f[j] == '^') return 3;
        } 
    }
    

    return (-1);
    
}

// ------- PRINT DE UMA PILHA -------
void wprint_pilha(WINDOW *win, int x, int y, int r, char nome[], CARTAS *pilha, int tamanho_pilha, int flag, int lim){
     int f = 0; 
     if (flag) f = 1;
    werase(win);

    if(r == 1){  
        print_todas(win, x, y, pilha, tamanho_pilha, f, lim);
        // Borda da janela 
        box(win, 0, 0);
    }
    else if (r == 2 || r == 3) {
        print_pilhaTopInv(win, x, y, r, pilha, tamanho_pilha, f, lim); 
    }
    // Fraz print do nome/tipo da pilha
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 0, 0,"%s", nome);
    wattroff(win, COLOR_PAIR(3));  

    wrefresh(win);

}

// TODAS as cartas visíveis
void print_todas(WINDOW *win, int x, int y, CARTAS *pilha, int tamanho_pilha, int flag, int lim){

    for(int i = 0; i<tamanho_pilha; i++){
        if (flag && i >= lim) { 
                wattron(win, A_BOLD | A_BLINK);
            }
        wprint_carta(win, x, y, pilha[i]);

        // Desliga IMEDIATAMENTE após imprimir a carta para não pintar o fundo da janela
        wattroff(win, A_BOLD | A_BLINK);

        x+= 2;
    }

}

// Apenas a do TOPO visível ou NENHUMA vísivel
void print_pilhaTopInv(WINDOW *win, int x, int y, int r, CARTAS *pilha, int tamanho_pilha, int flag, int lim){
    int i;
    int j = 0; 
    if (r==3) j = 1; 
    // Print de cada uma das "invisíveis"
    for(i = 0; i<tamanho_pilha - j ; i++){
        if (flag && i >= lim) { 
                wattron(win, A_BOLD | A_BLINK);
            }
        mvwprintw(win, x, y, "[%-2s%s]", "?", "?");

        // Desliga IMEDIATAMENTE após imprimir a carta para não pintar o fundo da janela
        wattroff(win, A_BOLD | A_BLINK);
        x+= 2;
    }

    // Faz print da carta do topo 
    if (r == 3 && tamanho_pilha>1) {
        if (flag){
            wattron(win, A_BOLD | A_BLINK);
        }

        wprint_carta(win, x, y, pilha[i]);
        wattroff(win, A_BOLD | A_BLINK);
    }
}

// ------- PRINT DA CARTA -------

// Carta vísivel 
void wprint_carta(WINDOW *win, int x, int y,  CARTAS c){

        char valor[3]; // guarda o valor da carta 
        traduzvalor(valor, c.valor);

        const char *s = traduzsimbolo(c.naipe);

    // Define as cores de acordo com o naipe
        if (c.naipe == 'H' || c.naipe == 'S')
                wattron(win, COLOR_PAIR(1));
        else
                wattron(win, COLOR_PAIR(2));
        


        mvwprintw(win, x, y, "[%-2s%s]", valor, s);

        refresh();

        // Desativa o atributo das cores
        wattroff(win, COLOR_PAIR(1));
        wattroff(win, COLOR_PAIR(2));



}

// ------- AUXILIARES (print_carta) -------
const char* traduzsimbolo(char naipe) {
    switch(naipe) {

        case 'H': return "\xE2\x99\xA5"; // Copas 
        case 'S': return "\xE2\x99\xA6"; // Ouros
        case 'D': return "\xE2\x99\xA3"; // Paus
        case 'C': return "\xE2\x99\xA0"; // Espadas
        default:  return "?";
    }
}


// ------- ATIVA NCURSES -------
void ativaNcurses(){

    // Inicia ncurses
    initscr(); 

    // o que o ultilizador digita não aparece no ecrã
    noecho();  

    // Ativa a leitura de teclas especiais
    keypad(stdscr, TRUE);


    // Ativa as cores 
    start_color(); 

    // Definindo os pares de cores 
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    //Alterei a cor do Cyan predefinida
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);

    init_pair(5, COLOR_GREEN, COLOR_WHITE);
    init_pair(4, COLOR_YELLOW, COLOR_WHITE);

    // Ativa o leitor de eventos do Mouse 
    mousemask(ALL_MOUSE_EVENTS, NULL);

    cbreak();
}
