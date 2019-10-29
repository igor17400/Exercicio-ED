#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MAX 10
#define TAM_NOME 20

typedef struct {
    unsigned int num_elementos;
    char dados[TAM_MAX][TAM_NOME];
} tab_disp_str;

typedef struct {
    unsigned int num_elementos;
    char dados[TAM_MAX][TAM_NOME];
} tabela_teste;

int hash(int matricula) {
    /*  hash para mapear a matrícula (chave numérica) */
    return matricula%4;
}


/* Retorna o endereço do dado, se existir, NULL caso contrário. */
char *busca(tab_disp_str* tabela, int chave) {
    /* Insira seu código aqui. */
    char *nome = NULL;
    int hash_index = hash(chave);

    if(tabela == NULL){
        return nome = NULL;
    }

    if(hash_index < 0 || chave < 0){
        return nome = NULL;
    }

    nome = tabela->dados[hash_index];
    if(strcmp(nome, "") == 0){
        nome = NULL;
    }else if(strcmp(nome, " ") == 0){
        nome = NULL;
    } else {
        if(tabela->dados[hash_index] != NULL)
            nome = tabela->dados[hash_index];
    }

    return nome;
}

// /* Retorna o endereço do dado, se existir, NULL caso contrário. */
// char *busca(tab_disp_str* tabela, int chave) {
//     /* Insira seu código aqui. */
//     char *nome = NULL;
//     int hash_index = hash(chave);
//     int i;
//     for(i = 0; i < hash_index; i++){
//         nome = tabela->dados[i];
//     }
//
//     if(hash_index > tabela->num_elementos)
//         nome = NULL;
//
//     return nome;
// }

/* Retorna o endereço do dado, se existir, NULL caso contrário. */
char *buscaTeste(tabela_teste* tabela, int chave) {
    /* Insira seu código aqui. */
    char *nome = NULL;
    int hash_index = hash(chave);

    if(hash_index > tabela->num_elementos){
        nome = NULL;
    } else{
        nome = tabela->dados[hash_index];
        if(strcmp(nome, "") == 0){
            nome = NULL;
        } else {
            nome = tabela->dados[hash_index];
        }
    }
    return nome;
}

int main(){

    tabela_teste tabela;
    strcpy(tabela.dados[0], "Igor");
    strcpy(tabela.dados[1], "Ola");
    strcpy(tabela.dados[2], " ");

    printf("------------------\n");
    char nome[1] = "";
    printf("%d", strcmp(nome, ""));
    printf("------------------\n");

    char* teste = "";
    teste = buscaTeste(&tabela, 10);
    printf("%s\n", teste);
    printf("%d\n", teste==NULL);

    printf("------------------\n");

    char* teste2 = "";
    teste2 = buscaTeste(&tabela, 1);
    printf("%s\n", teste2);
    printf("%d\n", teste2==NULL);

    printf("------------------\n");

    char* teste3 = "";
    teste3 = buscaTeste(&tabela, 3);
    printf("%s\n", teste3);
    printf("%d\n", teste3==NULL);

    return 0;
}


// /* A constante global TAM_MAX já foi definida. */
// /* A constante global TAM_NOME já foi definida. */
// typedef struct {
//     unsigned int num_elementos;
//     char dados[TAM_MAX][TAM_NOME];
// } tab_disp_str;
//
// /* Retorna o endereço do dado, se existir, NULL caso contrário. */
// char *busca(tab_disp_str* tabela, int chave) {
//     /* Insira seu código aqui. */
//     char *nome = NULL;
//     int hash_index = hash(chave);
//     int i = 0;
//
//     if(hash_index > TAM_MAX)
//         return nome = NULL;
//
//     for(i = 0; i < hash_index; i++){
//         nome = tabela->dados[i];
//     }
//
//     return nome;
// }
