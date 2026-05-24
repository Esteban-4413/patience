//
// Created by Esteban Yepez Orozco on 10/05/2026.
//

#ifndef LOADER_H
#define LOADER_H
#include "gamedef.h"
#include <dirent.h>

DefJogo* escolhe_paciencia(char *pasta);
int input_escolha(int conta);
int lista_ficheiros(DIR *d, char ficheiros[][256]);
DefJogo* carrega_escolha(char *pasta, char ficheiros[][256], int escolha);


#endif //PATIENCE_LOADER_H
