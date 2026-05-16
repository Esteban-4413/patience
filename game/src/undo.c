
#include "../include/undo.h"

/*                              Falta a função joga para terminar o teste do undo                                  */
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NÃO TESTADO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void registar_jogada(EstadoJogo *e){
   
    //para meter as jogadas mais recentes então empurramos as mais velhas fora do array (Se o histórico estiver cheio, apaga a jogada mais antiga)
    if (e->tamanho_historial == MAX_UNDO){
        for (int i = 0; i < MAX_UNDO - 1; i ++)
            e->historial[i] = e->historial[i + 1];
        (e->tamanho_historial)--;
    }
    
    // Guarda os dados da nova jogada
    int tamanho_historial = e->tamanho_historial;
    e->historial[tamanho_historial].pilha = e->jog_atual.pilha;
    e->historial[tamanho_historial].coluna = e->jog_atual.coluna;
    e->historial[tamanho_historial].chegada = e->jog_atual.chegada;
    e->historial[tamanho_historial].n = e->jog_atual.n;
    

    (e->tamanho_historial)++;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PARCIALMENTE TESTADO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void undo(EstadoJogo *e){

    // Verifica se há jogadas para desfazer
    if (e->tamanho_historial == 0){ 
        mvprintw(0, 2, "oh men para retroceder tanto no tempo é mais fácil comprar uma máquina do tempo.\n");
        return;
    }
    
    // Faz o undo 
    aux_undo(e);
    
}

void aux_undo(EstadoJogo *e){
    // Acede à última jogada
    (e->tamanho_historial)--;
    struct JOGADA ultimo_mov = e->historial[e->tamanho_historial];

    int origem = ultimo_mov.pilha;
    int chegada = ultimo_mov.chegada;
    int n = ultimo_mov.n; 
    int pos_original = ultimo_mov.coluna; // Onde elas estavam na origem

    // Localiza as cartas na chegada
    int pos_atual_chegada = e->pilhas[chegada].tamanho_pilha - n;

    //O Loop de Devolução
    for (int i = 0; i < n; i++) {
        e->pilhas[origem].pilha[pos_original + 1] = e->pilhas[chegada].pilha[pos_atual_chegada + i];
        //matriz[origem][pos_original + i] = e->matriz[chegada][pos_atual_chegada + i];
    }

    // Ajustar os contadores de tamanho
    e->pilhas[origem].tamanho_pilha += n;
    e->pilhas[chegada].tamanho_pilha -= n;
}