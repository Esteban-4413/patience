#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../include/gamestate.h"
#include "../include/card.h"
#include "../include/utils.h"


EstadoJogo setGameState(DefJogo *d){
    EstadoJogo e; 
    
    inicializa_naipes(&e); 
    inicializa_jogAtual(&e);
    e.tamanho_historial = 0; 
    e.def_jogo = d; 

    // ----- Inicilizando os baralhos -----
    int tamanho_baralho = 52 * (d->num_baralhos);
    CARTAS *baralho = malloc(tamanho_baralho * sizeof(CARTAS)); // Aloca a memória do array do baralho 

    inicializa_baralhos(baralho, d->num_baralhos, e.naipes); 
    e.tamanho_baralho = tamanho_baralho;
    e.baralho = baralho; 
    print_baralho_grid(&e); 

    // ----- Inicilizando as pilhas -----

    PILHA *pilhas = malloc(d->total_inits * sizeof(PILHA)); // Aloca a memória do array das pilhas 
    e.total_pilhas = d->total_inits; 

    set_pilhas(d->inits, d->total_inits,pilhas);
    e.pilhas = pilhas; 
    inicializa_pilhas(&e);

    print_baralho_grid(&e);
    

    return e; 
}


void set_pilhas (InitPilha d[], int total_inits, PILHA *pilhas){
     
    for(int i=0; i < total_inits; i++){
        CARTAS *nova_pilha = malloc(32 * sizeof(CARTAS)); // Número arbitrário para ser o máximo de cartas por pilha 
        pilhas[i].nome_tipo = d[i].nome_tipo; 
        pilhas[i].tamanho_pilha = 0; 
        pilhas[i].pilha = nova_pilha; 
    }
}

void inicializa_pilhas(EstadoJogo *e){
    srand(time(NULL));
    int indice_carta;
    int max_pilha;
    for(int i = 0; i < e->total_pilhas; i++){
        max_pilha = e->def_jogo->inits[i].num_cartas; 
        for(int j = 0; j < max_pilha; j++){

            // Seleciona uma carta aleatória 
            indice_carta = rand() % (e->tamanho_baralho); 

            // Atribui a carta à pilha 
            e->pilhas[i].pilha[j] = e->baralho[indice_carta]; 

            // Acrescenta 1 ao tamanho da pilha 
            e->pilhas[i].tamanho_pilha ++; 

            // Remove a carta do baralho, trocando-a com a última e diminuindo o tamanho
            e->baralho[indice_carta] = e->baralho[e->tamanho_baralho - 1];
            (e->tamanho_baralho)--;
        }
    }
}







void inicializa_naipes(EstadoJogo *e){
     /*
     Inicialização dos naipes
    
     H - Copas  
     S - Espadas  
     D - Ouros  
     C - Paus
     */
    e->naipes[0] = 'H';
    e->naipes[1] = 'S';
    e->naipes[2] = 'D';
    e->naipes[3] = 'C';

}

void inicializa_jogAtual(EstadoJogo *e){
    e->jog_atual.pilha = (-1);
    e->jog_atual.chegada = (-1);
    e->jog_atual.flag = -2; //número que não corresponde a nenhuma das condições definidas 
    e->jog_atual.n = -1;
}

void inicializa_baralhos(CARTAS *baralho, int num_baralhos, char naipes[4]){
    int indice = 0;
    while (num_baralhos != 0){
        //Para cada naipe, percorre as cartas com valores de 1 a 13.
        for(int i = 0; i < 4; i++){
            for(int j = 1; j <= 13; j++){
                baralho[indice].valor = j;
                baralho[indice].naipe = naipes[i];
                indice++;
            }
        }


        num_baralhos--;
    }
    
}




// ---------------------- AUXILIAR ----------------------
void print_baralho_grid(EstadoJogo *e) {
    if (e == NULL || e->baralho == NULL) {
        printf("Erro: Baralho não inicializado.\n");
        return;
    }

    printf("--- Exibição do Baralho (Total: %zu cartas) ---\n", e->tamanho_baralho);

    for (size_t i = 0; i < e->tamanho_baralho; i++) {
        // Imprime a carta (ex: [10C] para 10 de Copas)
        // Se o valor for 1, imprime 'A', se for 11 'J', etc. (opcional)
        printf("[%2d%c] ", e->baralho[i].valor, e->baralho[i].naipe);

        // Se o próximo índice for múltiplo de 10, salta uma linha
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    // Garante que termina com uma linha nova se o total não for múltiplo de 10
    if (e->tamanho_baralho % 10 != 0) {
        printf("\n");
    }
    
    printf("----------------------------------------------\n");
}


void print_pilhas(EstadoJogo *e) {
    if (e == NULL || e->pilhas == NULL) {
        printf("Erro: Pilhas não inicializadas.\n");
        return;
    }

    printf("\n--- ESTADO DAS PILHAS ---\n");

    for (int i = 0; i < e->total_pilhas; i++) {
        // Imprime o índice e o nome do tipo (ex: Pilha 0 [TAB]:)
        printf("Pilha %d [%s]: ", i, e->pilhas[i].nome_tipo);

        if (e->pilhas[i].tamanho_pilha == 0) {
            printf("[Vazia]");
        } else {
            for (size_t j = 0; j < e->pilhas[i].tamanho_pilha; j++) {
                CARTAS c = e->pilhas[i].pilha[j];
                
                // Formatação simples: [ValorNaipe]
                // Se preferires o 'A' em vez de 1, podes usar uma função auxiliar
                printf("[%d%c] ", c.valor, c.naipe);
                
                // Adiciona um separador visual entre as cartas, menos na última
                if (j < e->pilhas[i].tamanho_pilha - 1) {
                    printf("| ");
                }
            }
        }
        printf("\n");
    }
    printf("-------------------------\n");
}