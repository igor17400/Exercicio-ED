/** Matricula: 160124981
*       Nome: IGOR LIMA ROCHA AZEVEDO
*      Turma: E*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*------------------------- Lógica da FILA -------------------------*/

typedef struct tipo_elem{
    int info;
    char nome;
    struct tipo_elem *ligado_com;
} tipo_elem;

typedef struct{
    tipo_elem *inicio;
    tipo_elem *fim;
} fila;

void create(fila *q) {
    q->inicio = NULL;
    q->fim = NULL;
}

_Bool isEmpty (fila *q) {
    return (q->inicio == NULL);
}

void imprime(fila *q) {

    tipo_elem *x;
    x = q->inicio;

    while(x != NULL) {
        printf("%c\n", x->nome);
        x = x->ligado_com;
    }
}

_Bool enqueue(fila *q_fila, char nome) {

    tipo_elem *novo_elemento = (tipo_elem*) malloc(sizeof(tipo_elem));
    if(novo_elemento == NULL)
        return false;

    novo_elemento->nome = nome;
    novo_elemento->ligado_com = NULL;

    if(isEmpty(q_fila)) {
        q_fila->inicio = novo_elemento;
    } else {
        q_fila->fim->ligado_com = novo_elemento;
    }

    q_fila->fim = novo_elemento;
    return true;
}

char dequeue(fila *q_fila) {

    char simbolo_return = '\0';
    tipo_elem *p_elem;
    if (isEmpty(q_fila)) {
        return simbolo_return;
    }

    p_elem = q_fila->inicio;
    q_fila->inicio = p_elem->ligado_com;

    if(q_fila->inicio == NULL) {
        q_fila->fim = NULL;
    }
    simbolo_return = p_elem->nome;

    free(p_elem);
    return simbolo_return;
}

/*-------------------------------------------------------------------*/



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
    char* new_str = str;
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
    int i, j = 0;

    int size = sizeFunction(str);

    char old_str[101] = "";
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

char* alocarChar(int size){
    char* aloc_char = (char*) malloc(size*sizeof(char));
    if(aloc_char == NULL){
        printf("erro\n");
        return 0;
    }
    return aloc_char;
}

void liberaChar(char** lib_char){
    if(*lib_char != NULL){
        free(*lib_char);
        *lib_char = NULL;
    }
}

char* removeChavesColchetes(char *str){
    char ch = '[';
    char Newch = '(';
    int i;
    for(i = 0; i <= strlen(str); i++)
      {
          if(str[i] == ch)
        {
              str[i] = Newch;
         }
    }

    ch = ']';
    Newch = ')';
    for(i = 0; i <= strlen(str); i++)
      {
          if(str[i] == ch)
        {
              str[i] = Newch;
         }
    }

    ch = '{';
    Newch = '(';
    for(i = 0; i <= strlen(str); i++)
      {
          if(str[i] == ch)
        {
              str[i] = Newch;
         }
    }

    ch = '}';
    Newch = ')';
    for(i = 0; i <= strlen(str); i++)
      {
          if(str[i] == ch)
        {
              str[i] = Newch;
         }
    }

    return str;
}

void transforma(const char* infixa, char* posfixa) {
    /* Insira seu código aqui. */
    int i = 0;
    int k = 0;
    char coringa = '\0', coringa_dois = '\0';
    int flag = 0;

    /* cria pilha */
    Pilha* stack = NULL;

    /* cria fila */
    fila q_fila;
    create(&q_fila);

    i = 0;
    while(infixa[i] != '\0'){
        if(infixa[i] == ' '){
            i++;
            continue;
        }


        if(isNumeric(infixa[i]) || infixa[i] == '.' || isalpha(infixa[i]) != 0){
            if(flag && infixa[i] != '.'){
                enqueue(&q_fila, ' ');
                enqueue(&q_fila, infixa[i]);
                flag = 0;
            } else {
                enqueue(&q_fila, infixa[i]);
            }

        } else if(infixa[i] == '('){
            push(&stack, infixa[i]);
        } else if(infixa[i] == ')'){
            coringa = pop(&stack);
            while(coringa != '('){
                enqueue(&q_fila, ' ');
                enqueue(&q_fila, coringa);
                coringa = pop(&stack);
            }
        } else {
            flag = 1;
            if(!isEmptyPilha(stack))
                while(priority(topo(&stack)) >= priority(infixa[i])){
                    coringa_dois = pop(&stack);
                    enqueue(&q_fila, ' ');
                    enqueue(&q_fila, coringa_dois);
                }
            push(&stack, infixa[i]);
        }
        i++;
    }

    while(!isEmptyPilha(stack)){
        coringa_dois = pop(&stack);
        enqueue(&q_fila, ' ');
        enqueue(&q_fila, coringa_dois);
    }

    /* esvaziar q_fila */
    k = 0;
    while(!isEmpty(&q_fila)){
        posfixa[k] = dequeue(&q_fila);
        k++;
    }
}

int main() {
    char infixa[101] = "", posfixa[201] = "";

    scanf("%100[^\n]", infixa);

    removeChavesColchetes(infixa);

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
(A * B) + C - (D / E + F)                      A B * C + D E / F + -
1+2*3
(1+2)*3
(3.14*2.5)+7-(0.25/1+42)
1^3*5+4/2
(A*B)+C-(D/E+F)
(A * B) +C - (D/ E +F)
[1 + 2 * 3]

*/
