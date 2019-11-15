#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO 3

/*------------------------- Lógica de Grafos ----------------------------- */
/* TAMANHO é um valor constante. */

typedef struct {
    char vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t;
/* Atenção, não  modifique o trecho acima! */

/* Retorna o índice do vértice no vetor, caso exista, -1 caso contrário. */
int idx_vertice(grafo_t* g, char v) {
    if(g == NULL){
        return -1;
    }

    int i = 0;
    int pos = -1;
    for(i = 0; i < TAMANHO; i++){
        if(g->vertices[i] == v){
            pos = i;
        }
    }

    return pos;
}


/*------------------------------------------------------------------------ */

int main(){

    grafo_t *grafo;
    grafo->vertices[0] = 'a';
    grafo->vertices[1] = 'b';
    grafo->vertices[2] = 'Z';

    printf("%d\n", idx_vertice(grafo, 'Z'));
    printf("%d\n", -1 == idx_vertice(grafo, 'A'));
    printf("%d\n", -1 == idx_vertice(NULL, 'Z'));
    printf("%d\n", -1 == idx_vertice(NULL, '1'));

    return 0;
}
