
#ifndef PARSER_H
#define PARSER_H
#include "gamedef.h"

DefJogo* load_paciencia(char *ficheiro);
DefJogo* incializa_estado(void);
void what_command(char * comando, char *buffer, DefJogo *est);

void cmd_tipo(char *buffer, DefJogo *est);
void cmd_init(char *buffer, DefJogo *est);
void cmd_auto(char *buffer, DefJogo *est);
void cmd_win(char *buffer, DefJogo *est);
void cmd_mov(char *buffer, DefJogo *est);
int processa_linha(char *buffer, DefJogo *est);



#endif 
