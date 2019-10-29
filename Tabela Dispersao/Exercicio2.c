#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MAX 10

int hash(char chave) {
    /* Insira seu código aqui. */
    int size = 20;
    return chave % size;
}

int main(){

    printf("%d\n", hash('A'));
    return 0;
}
