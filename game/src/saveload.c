#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/loader.h"
#include "../include/gamestate.h"
#include "../include/gamedef.h"
#include "../include/saveload.h"
#include "../include/display.h"

void save_game(EstadoJogo *e, char *ficheiro){
    FILE *f = fopen(ficheiro, "wb"); // wb = write binary
    fprintf(f, "%s\n", e->def_jogo->nome);
    
}