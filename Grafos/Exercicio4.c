#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO 3

/*------------------------- Lógica de Grafos ----------------------------- */
/* TAMANHO é um valor constante. */

/* Define a estrutura da informação relevante. */
typedef struct {
    int dia, mes, ano;
    char descricao[50];
} data_t;

/* Define a estrutura do vértice. */
typedef struct {
    char chave;
    data_t data;
} vertice_t;


typedef struct {
    vertice_t vertices[TAMANHO];
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
        if(g->vertices[i].chave == v){
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

grafo_t* grafoInit( char ch) {
   grafo_t* grafo = (grafo_t*)malloc(sizeof(grafo_t));
   grafo->vertices[0].chave = ch;
   grafo->ordem = 1;
   initAresta(grafo);

   return grafo;
}

void grafoInsert(grafo_t* grafo, char ch) {
    grafo->vertices[grafo->ordem].chave = ch;
    aresta(grafo, grafo->vertices[grafo->ordem].chave, ch);
    grafo->ordem++;
}


/* Retorna o ponteiro para o vértice identificado pela chave, caso exista, NULL caso contrário. */
vertice_t* vertice(grafo_t* g, char chave) {
   /* Insira seu código aqui. */
   int i;
   vertice_t *vPtr;

   if(g == NULL){
       return NULL;
   }

   if(!isalpha(chave)){
       return NULL;
   }

   for(i = 0; i < TAMANHO; i++){
       if(g->vertices[i].chave == chave){
           vPtr = &g->vertices[i];

           return vPtr;
       }
   }

   return NULL;
}



/*------------------------------------------------------------------------ */

int main(){

    grafo_t *grafo;
    grafo = grafoInit('0');
    grafoInsert(grafo, 'B');
    grafoInsert(grafo, 'A');
    grafoInsert(grafo, '0');

    vertice_t *vert1 = vertice(grafo, 'A');
    vertice_t *vert2 = vertice(grafo, 'B');
    vertice_t *vert4 = vertice(grafo, 0);
    vertice_t *vert3 = vertice(NULL, 'B');

    printf("%d %d %d\n", idx_vertice(grafo, 'A'), idx_vertice(grafo, 'B'), idx_vertice(grafo, 'Z'));
    if(vert1 != NULL)
        printf("%c\n", vert1->chave);
    if(vert2 != NULL)
        printf("%c\n", vert2->chave);
    if(vert3 != NULL)
        printf("%c\n", vert3->chave);
    if(vert4 != NULL)
        printf("%c\n", vert4->chave);

    return 0;
}
