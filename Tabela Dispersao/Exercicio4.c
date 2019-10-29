#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MAX 10

/* A constante global TAM_MAX já foi definida. */
typedef struct {
    unsigned int num_elementos;
    char dados[TAM_MAX];
} tab_disp_char;

int hash(int matricula) {
    /*  hash para mapear a matrícula (chave numérica) */
    return matricula%10;
}


/* Returna "true", se conseguiu inserir o dado na tabela, "false" se houve colisão. */
_Bool insere(tab_disp_char* td, int chave, char dado) {
    /* Insira seu código aqui. */
    if(chave < 0){
        return false;
    }

    if(td == NULL){
        return false;
    }

    /* hash, que mapeia qualquer chave dada para índices válidos */
    int hash_index = hash(chave);

    if(hash_index > TAM_MAX)
        return false;

    if(td->dados[hash_index] == '\0'){
        td->dados[hash_index] = dado;
        td->num_elementos++;
        return true;
    } else {
        /* não é possível inserir o dado em caso de colisão */
        return false;
    }
}


int main()
{
    char dados[3] = {'A', 'B', '\0'};

    if(dados[2] == '\0'){
        printf("true\n");
        dados[2] = 'C';
        printf("%c\n", dados[2]);
    } else {
        /* não é possível inserir o dado em caso de colisão */
        printf("false\n");
    }

    return 0;
}
