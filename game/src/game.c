#include "../include/gamestate.h"
#include "../include/display.h"
#include "../include/input.h"
#include "../include/game.h"
#include "../include/undo.h"
#include "../include/move.h"
#include "../include/saveload.h"


void loop_principal(EstadoJogo *e, POINTERS *p, int jogando){
    while (jogando) {
        int ch = getch(); 
        if (verifica_vitoria(e)){ mvprintw(0,60,"Vitória!"); jogando = 0;}
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
    else if (r == e->total_pilhas){
        undo(e);
        // Atualiza o print de todas as pilhas 
        printPilhas(e, p->end_pilhas, p->total_pilhas);

    }

    else if (r == e->total_pilhas + 1){
        save_game(e, "save.txt", e->def_jogo->nome_paciencia);
        mvprintw(0, 60, " Jogo guardado em 'save.txt'");
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
        movAutos(e);  // MOVIMENTOS AUTOMATICOS 
                
    } 
            
    update_pilha(e,p);
  
    
    refresh();  
}


void define_jogAtual(int r, int num_carta, EstadoJogo *e){
    if(e->jog_atual.flag == -2){
        e->jog_atual.pilha = r;
        e->jog_atual.coluna = num_carta; 
        e->jog_atual.n = e->pilhas[r].tamanho_pilha - num_carta;
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

int verifica_vitoria(EstadoJogo *estado){
    for(int i = 0; i < estado->def_jogo->total_wins; i++){
        VictoryCondition vict = estado->def_jogo->wins[i];
        
        for(int j = 0; j < estado->total_pilhas; j++){
            PILHA pilha = estado->pilhas[j];
            if(strcmp(pilha.nome_tipo, vict.nome_tipo) == 0){
                if(pilha.tamanho_pilha != vict.num_cartas) return 0;
            }
        }
    }
    return 1;
}


int existe_save(char *ficheiro){
    FILE *f = fopen(ficheiro, "r");
    if(f == NULL) return 0;
    fclose(f);
    return 1;
}

EstadoJogo menu(char *pasta, char *save){
    EstadoJogo e;
    (existe_save(save) && input_menu() == 1) ? (e = load_game(save, pasta)) : (e = setGameState(escolhe_paciencia(pasta)));
    return e;
}

int input_menu(void){
    printf("Encontrei um jogo guardado\n1 - Continuar\n2 - Novo Jogo\n");
    int op = 0;
    char buf[64];
    int buul = 0;
    while (!buul){
        if(fgets(buf, sizeof(buf), stdin) != NULL){
            if(sscanf(buf, "%d", &op) == 1 && (op == 1 || op == 2)) buul = 1;
            else printf("Número invalido. Tenta outra vez man");
        }
    }
    return op;
}