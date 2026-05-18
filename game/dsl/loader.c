#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/parser.h"
#include "../include/loader.h"
#include "../include/utils.h"



DefJogo escolhe_paciencia(char *pasta){
   DefJogo r;
    DIR *d = opendir(pasta);

   if (d == NULL){
    printf("esquizofrenico, essa pasta '%s'? não existe lol\n ", pasta);
    DefJogo vazio;
    vazio.nome[0] = '\0';
    r = vazio;
    return r;
   }
   
   struct dirent *entrada;
   int conta = 0;

   char ficheiros[50][256]; //guarda ate 50 nome de ficheiros, ainda pode ser melhor usando malloc (fica para o futuro)
   while ((entrada = readdir(d)) != NULL){
    if(entrada->d_name[0] != '.'){
        copia_string(ficheiros[conta], entrada->d_name);
        printf("%d. %s\n", conta+1, entrada->d_name);
        conta++;
    }
   }
   closedir(d);

   int escolha = 0;
   printf("Qual é o jogo que você quer jogar?\n Digite o número\n");
   //scanf("%d", &escolha); isto era unsafe porque o user podia meter qualquer macacada então vou fazer um while que so aceite coisas logicas
   while(escolha < 1 || escolha > conta){
    scanf("%d", &escolha);
    if(escolha < 1 || escolha > conta) printf("Número invalido. Tenta outra vez (1 a %d)", conta);
   }

   char ruta[256];
   sprintf(ruta, "%s/%s", pasta, ficheiros[escolha-1]); 
   r = load_paciencia(ruta);
   printf("pessima escolha mas pronto vou carrega-la por você: %s..\n", ruta);
   return r;
}