
#ifndef PARSER_H
#define PARSER_H

DefJogo load_paciencia(char *ficheiro);
DefJogo incializa_estado(void);
void what_command(char * comando, char *buffer, DefJogo *est);

#endif 
