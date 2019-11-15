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

grafo_t* grafoInit( char ch) {
   grafo_t* grafo = (grafo_t*)malloc(sizeof(grafo_t));
   grafo->vertices[0] = ch;
   grafo->ordem = 1;
   initAresta(grafo);

   return grafo;
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

void grafoInsert(grafo_t* grafo, char ch) {
    grafo->vertices[grafo->ordem] = ch;
    aresta(grafo, grafo->vertices[grafo->ordem], ch);
    grafo->ordem++;
}


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int verticeInt(grafo_t* g, char vertice) {
   /* Insira seu código aqui. */
   int i;

   if(g == NULL){
       return -1;
   }

   if(!isalpha(vertice)){
       return -1;
   }

   for(i = 0; i < TAMANHO; i++){
       if(g->vertices[i] == vertice){
           return i;
       }
   }

   return -1;
}

/* Retorna a quantidade de arestas que incidem sobre um vértice. */
int grau_de_entrada(grafo_t* g, char vertice) {
    /* Insira seu código aqui. */
    int i, j;
    int pos_interesse;
    int qtd = 0;

    pos_interesse = verticeInt(g, vertice);

    for(i = 0; i < TAMANHO; i++){
        if(g->arestas[i][pos_interesse] == 1){
            qtd++;
        }
    }

    for(j = 0; j < TAMANHO; j++){
        if(g->arestas[pos_interesse][j] == 1){
            qtd++;
        }
    }

    return qtd;
}


/*------------------------------------------------------------------------ */

int main(){

    grafo_t *grafo;


    grafo = grafoInit('A');
    grafoInsert(grafo, 'B');
    grafoInsert(grafo, '0');


    printf("%d\n", grau_de_entrada(grafo, 'B'));
    printf("%d\n", grau_de_entrada(grafo, 'X'));

    return 0;
}
