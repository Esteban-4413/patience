#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ncurses.h>
#include "../include/display.h"
#include "../include/utils.h"
#include "../include/gamedef.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NÃO TESTADO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ------- ATUALIZA JANELAS -------
void update_pilha(EstadoJogo *e, POINTERS *janelas){
    int s = e->jog_atual.pilha; // índice da pilha de saida
    int rs = checkFlags_pilha(e, (e->pilhas[s].nome_tipo));

    if (e->jog_atual.flag == 0 && e->jog_atual.pilha != (-1)) {
        int lim = e->jog_atual.coluna; 
        pilha_negrito(janelas->end_pilhas[s], 2, 1, e->pilhas[s].nome_tipo, e->pilhas[s].pilha, e->pilhas[s].tamanho_pilha, lim);
    }
    else if (e->jog_atual.flag == 1 && e->jog_atual.coluna != (-1)){  
        int c = e->jog_atual.chegada; // índice da pilha de chegada 
        
        int rc = checkFlags_pilha(e, (e->pilhas[c].nome_tipo));
        wprint_pilha(janelas->end_pilhas[s], 2, 1, rs, e->pilhas[s].nome_tipo, e->pilhas[s].pilha, e->pilhas[s].tamanho_pilha ); // SAIDA
        wprint_pilha(janelas->end_pilhas[c], 2, 1, rc, e->pilhas[c].nome_tipo, e->pilhas[c].pilha, e->pilhas[c].tamanho_pilha ); // CHEGADA
               
    } else {
        wprint_pilha(janelas->end_pilhas[s], 2, 1, rs, e->pilhas[s].nome_tipo, e->pilhas[s].pilha, e->pilhas[s].tamanho_pilha ); // SAIDA // TIRA O QUE TAVA EM NEGRITO - jogada inválida
   
    } 
}

void pilha_negrito(WINDOW *win, int x, int y, char nome[], CARTAS *pilha, int tamanho_pilha, int lim){
    int ultCarta = tamanho_pilha - 1;

    for(int j = 0; j <= ultCarta; j++) {
        // Se a carta atual (j) for igual ou maior que o limite clicado, ativa o destaque
        if (j >= lim) { 
            wattron(win, A_BOLD | A_BLINK);
        }
        wprint_carta(win, x, y, pilha[j]);

        // Desliga IMEDIATAMENTE após imprimir a carta para não pintar o fundo da janela
        wattroff(win, A_BOLD | A_BLINK);
        
        x += 2; // EMPILHAMENTO VERTICAL 
    }

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TESTADO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

        wprint_pilha(end_pilhas[i], x_local, y_local, r, e->pilhas[i].nome_tipo, e->pilhas[i].pilha, e->pilhas[i].tamanho_pilha);
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
void wprint_pilha(WINDOW *win, int x, int y, int r, char nome[], CARTAS *pilha, int tamanho_pilha){

    werase(win);

    if(r == 1){  
        print_todas(win, x, y, pilha, tamanho_pilha);
        // Borda da janela 
        box(win, 0, 0);
    }
    else if (r == 2 || r == 3) {
        print_pilhaTopInv(win, x, y, r, pilha, tamanho_pilha); 
    }
    // Fraz print do nome/tipo da pilha
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 0, 0,"%s", nome);
    wattroff(win, COLOR_PAIR(3));  

    wrefresh(win);

}

// TODAS as cartas visíveis
void print_todas(WINDOW *win, int x, int y, CARTAS *pilha, int tamanho_pilha){
    for(int i = 0; i<tamanho_pilha; i++){
        wprint_carta(win, x, y, pilha[i]);
        x+= 2;
    }

}

// Apenas a do TOPO visível ou NENHUMA VISÍVEL
void print_pilhaTopInv(WINDOW *win, int x, int y, int r, CARTAS *pilha, int tamanho_pilha){
    int i;
    int j = 0; 
    if (r==3) j = 1; 
    // Print de cada uma das "invisíveis"
    for(i = 0; i<tamanho_pilha - j ; i++){
        mvwprintw(win, x, y, "[%-2s%s]", "?", "?");
        x+= 2;
    }

    // Faz print da carta do topo 
    if (r == 3 && tamanho_pilha>1) wprint_carta(win, x, y, pilha[i]);


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

        case 'H': return "\xE2\x99\xA5"; // Copas (Retorna o endereco na memoria)
        case 'S': return "\xE2\x99\xA6"; // Ouros
        case 'D': return "\xE2\x99\xA3"; // Paus
        case 'C': return "\xE2\x99\xA0"; // Espadas
        default:  return "?";
        /*
        case 'C': return ""; // Retorna o endereço da string na memória
        case 'O': return "";
        case 'P': return "";
        case 'E': return "";
        default:  return "";
      */
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
