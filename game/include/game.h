#ifndef e_H
#define e_H


void print_jogAtual(EstadoJogo *e);


/**
 * @brief O ciclo principal (loop) de execução do jogo.
 * 
 * Mantém o jogo a correr de forma contínua, à espera de input do utilizador
 * (cliques ou teclas), atualizando o ecrã sempre que uma ação é validada.
 * 
 * @param e Ponteiro para a estrutura principal do jogo.
 * @param janelas Ponteiro para a estrutura que contém as janelas ncurses.
 * @param jogando Variável de controlo (flag) que mantém o loop ativo (ex: 1 para jogar, 0 para sair).
 */
void loop_principal(EstadoJogo *e, POINTERS *janelas, int jogando);

/**
 * @brief Processa os cliques do rato feitos pelo utilizador.
 * 
 * Analisa as coordenadas de onde o utilizador clicou, determina se foi numa 
 * pilha, no baralho ou num botão, e invoca a ação correspondente.
 * 
 * @param e Ponteiro para a estrutura principal do jogo.
 * @param p Ponteiro para a estrutura que guarda todas as janelas (POINTERS).
 */
void processa_rato(EstadoJogo *e, POINTERS *p);

/**
 * @brief Lógica intermédia para processar o próximo passo do jogador.
 * 
 * Avalia o contexto da jogada após um clique numa pilha e decide o que
 * deve acontecer a seguir (ex: se o movimento avança para validação).
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas, 11 - Hint, 12 - Undo e 13 - New e).
 * @param num_carta Linha onde foi feito o click (posição, no caso de ser uma carta, da carta na matriz).
 * @param e Ponteiro para a estrutura principal do jogo.
 * @param p Ponteiro para as janelas da interface gráfica.
 */
void next_step (int r, int num_carta, EstadoJogo *e, POINTERS *p);


/**
 * @brief Função Auxiliar da next_step
 * A partir da informação que o click foi em uma das pilhas, inicia o 
 * processo de construir e preencher a Jogada Atual com as informações 
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas, 11 - Hint, 12 - Undo e 13 - New e).
 * @param num_carta Linha onde foi feito o click (posição, no caso de ser uma carta, da carta na matriz).
 * @param e Ponteiro para a estrutura principal do jogo.
 * @param p Ponteiro para as janelas da interface gráfica.
 */
void naPilha(int r, int num_carta, EstadoJogo *e, POINTERS *p);


/**
 * @brief Preenche a Jogada Atual.
 * Onde a flag da jog_Atual indica em que estado está a jogada.
 * (Se a flag for -2, a jogada acabou de ser inicializada,
 *  se for 0, já recebeu o primeiro click e está a espera do segundo,
 *  se for 1, já recebeu o segundo click e a jogada é válida
 *  e, por fim, se for -1, a jogada é inválida). 
 * + Primeiro click  corresponde ao click de onde queremos remover a(s) carta(s) 
 *  enquanto o segundo click corresponde a pilha para onde queremos mover essa(s) carta(s).
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas, 11 - Hint, 12 - Undo e 13 - New e).
 * @param num_carta Linha onde foi feito o click (posição, no caso de ser uma carta, da carta na matriz).
 * @param e Ponteiro para a estrutura principal do jogo.
 */
void define_jogAtual(int r, int num_carta,  EstadoJogo *e);

/**
 * @brief Função Auxiliar da define_jogAtual.
 * Define no caso da jog_atual está com a flag= 0, ou seja acabou de receber o 2º click
 * Preenche o parâmetro da jog_atual chamado chegada, com a pilha que foi detetado o click
 * e depois busca verificar se a jogada é possível, passando a atribuir a devida flag a jogada. 
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas, 11 - Hint, 12 - Undo e 13 - New e).
 * @param e Ponteiro para a estrutura principal do jogo.
 */
void jogAtual_segClick(int r, EstadoJogo *e);


#endif // e_H