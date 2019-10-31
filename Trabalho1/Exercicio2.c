/** Matricula: 160124981
*       Nome: IGOR LIMA ROCHA AZEVEDO
*      Turma: E*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*------------------------- Lógica da PILHA -------------------------*/

typedef struct Pilha {
    char nome;
    struct Pilha* prox;
} Pilha;

void push(struct Pilha** pilha_ref, char nome){
    Pilha *novo_node = (Pilha*) malloc(sizeof(Pilha));
    if(!novo_node){
        printf("Error.");
    } else{
        novo_node->nome = nome;
        novo_node->prox = *pilha_ref;

        *pilha_ref = novo_node;
    }
}

_Bool isEmptyPilha(Pilha* pilha){
    /*
     está vazia -> true
     não está vazia -> false
     */
    bool saida = false;
    if(pilha == NULL){
        saida = true;
    }
    return saida;
}

char pop(Pilha** pilha_ref){
    char saida = '\0';
    struct Pilha *prox_pilha = NULL;

    if(*pilha_ref == NULL) {
        return saida;
    }

    prox_pilha = (*pilha_ref)->prox;
    saida = (*pilha_ref)->nome;
    free(*pilha_ref);
    *pilha_ref = prox_pilha;

    return saida;
}

char topo(Pilha** pilha_ref){
    char saida = '\0';
    saida = pop(pilha_ref);
    push(pilha_ref, saida);

    return saida;
}

/*-------------------------------------------------------------------*/

int priority(char ch) {
    if(ch == '(')
        return 0;
    if(ch == '+' || ch == '-')
        return 1;
    if(ch == '*' || ch == '/')
        return 2;
    if(ch == '^')
        return 3;
    return 0;
}

_Bool isNumeric(char coringa){
    if(coringa == '0' || coringa == '1' || coringa == '2'
    || coringa == '3' || coringa == '4' || coringa == '5'
    || coringa == '6' || coringa == '7' || coringa == '8'
    || coringa == '9')
    {
        return true;
    }
    return false;
}

void remove_spaces(char* str) {
    const char* new_str = str;
    do {
        while (*new_str == ' ') {
            ++new_str;
        }
    } while ( (*str++ = *new_str++) );
}

int sizeFunction(char* str){
    int i;
    int size = 0;

    for(i = 0; str[i] != '\0'; i++){
        size++;
    }
    size++;

    return size;
}

void insert_spaces(char *str){
    //Insert Space between each character
    int i, j = 0;

    int size = sizeFunction(str);

    char old_str[101];
    strcpy(old_str, str);

    for(i = 0; i < size; i++){
        str[j] = old_str[i];
        j++;

        if(old_str[i] == '.')
            continue;

        if(old_str[i+1] == '.')
            continue;

        if(isNumeric(old_str[i+1]))
            continue;

        if(old_str[i] == ' ')
            continue;

        if(old_str[i+1] == ' ')
            continue;

        str[j] = ' ';
        j++;
    }
}

void transforma(const char* infixa, char* posfixa) {
    /* Insira seu código aqui. */
    int i;
    char coringa, coringa_dois;
    int flag = 0;
    char temp[101];
    /* cria pilha */
    Pilha* stack = NULL;

    strcpy(temp, infixa);
    strcpy(posfixa, "");
    remove_spaces(temp);


    for(i = 0; temp[i] != '\0'; i++){
        if(isNumeric(temp[i]) || temp[i] == '.'){
            if(flag && temp[i] != '.'){
                char ch = ' ';
                strncat(posfixa, &ch, 1);
                strncat(posfixa, &temp[i], 1);
                flag = 0;
            } else {
                strncat(posfixa, &temp[i], 1);
            }
//            printf("%c\n", temp[i]);
        } else if(temp[i] == '('){
            push(&stack, temp[i]);
        } else if(temp[i] == ')'){
            coringa = pop(&stack);
            while(coringa != '('){
                strncat(posfixa, &coringa, 1);
//                printf("%c\n", coringa);
                coringa = pop(&stack);
            }
        } else {
            flag = 1;
            if(!isEmptyPilha(stack))
                while(priority(topo(&stack)) >= priority(temp[i])){
                    coringa_dois = pop(&stack);
                    strncat(posfixa, &coringa_dois, 1);
//                    printf("%c\n",pop(&stack));
                }
            push(&stack, temp[i]);
        }
    }

    push(&stack, '\0');

    while(!isEmptyPilha(stack)){
        coringa_dois = pop(&stack);
        strncat(posfixa, &coringa_dois, 1);
//        printf("%c\n",pop(&stack));
    }
//    printf("\n");

    insert_spaces(posfixa);

}

int main() {
    char infixa[101], posfixa[201];

    scanf("%100[^\n]", infixa);

    transforma(infixa, posfixa);
    printf("%s\n", posfixa);

    return 0;
}

/*

Input                                          Result
-------------------------------------------------------------------------------
1 + 2 * 3                                      1 2 3 * +
(1 + 2) * 3                                    1 2 + 3 *
(3.14 * 2.5) + 7 - (0.25 / 1 + 42)             3.14 2.5 * 7 + 0.25 1 / 42 + -
1 ^ 3 * 5 + 4 / 2                              1 3 ^ 5 * 4 2 / +

*/
