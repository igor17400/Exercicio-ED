#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO 10

/*------------------------- Lógica de Grafos ----------------------------- */
typedef struct grafo_t{
    int vertices[TAMANHO];
    int arestas[TAMANHO][TAMANHO];
    int ordem;
} grafo_t;


/*------------------------------------------------------------------------ */

int main(){

    grafo_t *grafo;

    printf("%d\n", grafo->vertices != NULL);
    printf("%d\n", grafo->arestas != NULL);

    return 0;
}
