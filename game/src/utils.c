#include <stdio.h>
#include "../include/utils.h"

char * aux_string(char *str, char c){
    char *r;
    int i;
    for(i = 0;  str[i] != c && str[i] != '\0'; i ++);
    (str[i] == '\0') ? (r = NULL) : (r = str + i);
    return r; 
}

// < 0 sse a < b, = 0 sse a = b, > sse a > b
int comp_strings(char a[], char b[]){
    while( *a == *b && *a){
        a ++;
        b ++;
    } 
    return (*a - *b);
}

char *copia_string (char *dest, char source[]){
    int i;
    for (i = 0; source[i] != '\0'; i ++){
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return dest;
}