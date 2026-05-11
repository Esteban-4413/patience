#include <stdio.h>
#include "../include/gamedef.h"
#include "../include/parser.h"
#include "../include/utils.h"


EstadoJogo load_paciencia(char *ficheiro){
    EstadoJogo estado;
    FILE * paciencia = fopen(ficheiro, "r");
    char buffer[255];

    if(paciencia == NULL) printf("nao existe");

    else{
        while(fgets(buffer, 255, paciencia) != NULL){
        
            // digo eu que começamos por tirar tudo o que não vamos ler, i.e, os comentarios (#)
            char * comentario = aux_string(buffer, '#');
            if (comentario != NULL) *comentario = '\0';

            // vamo' identificar o comando 
            char comando[32];

            // sscanf devolve um int que é a quantidade de elementos que consiguio ler.
            // Neste caso só interessa se conseguio ler a primeira string ou não (nesse caso devolve 0).
            if (sscanf(buffer, "%s", comando) == 1){ // sscanf lê uma string e extrai as palavras, muito fixe.
                // [...] if/else para cada comando. TODO!!. Aqui usamos com_string 
                printf("comando: %s\n", comando);
            }
        printf("%s", buffer); 
        }
        fclose(paciencia);
    }
    return estado;

    
}