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

void initAresta(grafo_t* grafo){
    int i, j;
    for(i = 0; i < TAMANHO; i++){
        for(j = 0; j < TAMANHO; j++){
            grafo->arestas[i][j] = 0;
        }
    }

}

/* Cria uma aresta ligando o vértice origem ao vértice destino, se existirem no grafo. */
_Bool aresta(grafo_t* grafo, char origem, char destino) {
    /* Insira seu código aqui. */
    /*  Considere que o grafo é não direcionado */
    if(grafo == NULL){
        return false;
    }

    int pos_origem = idx_vertice(grafo, origem);
    if(pos_origem == -1){
        return false;
    }

    int pos_destino = idx_vertice(grafo, destino);
    if(pos_destino == -1){
        return false;
    }

    grafo->arestas[pos_origem][pos_destino] = 1;
    grafo->arestas[pos_destino][pos_origem] = 1;
    return true;
}


/*------------------------------------------------------------------------ */

int main(){

    grafo_t *grafo;
    grafo->vertices[0] = '0';
    grafo->vertices[1] = 'B';
    grafo->vertices[2] = 'A';

    initAresta(grafo);

    printf("%d %d %d\n", idx_vertice(grafo, 'A'), idx_vertice(grafo, 'B'), idx_vertice(grafo, 'Z'));
    printf("%d\n", aresta(grafo, 'A', 'B'));
    printf("%d\n", aresta(grafo, 'A', 'Z'));

    return 0;
}
