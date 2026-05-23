#ifndef SAVELOAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/loader.h"
#include "../include/gamestate.h"
#include "../include/gamedef.h"
#define SAVELOAD_H

void save_game(EstadoJogo *e, char *ficheiro);

#endif 
