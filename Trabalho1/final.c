#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// {2 ^ [3 - (4 / 8)]}
// {2 * [3 - (4 / 8)]}

int isNumeric (const char * s){
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

char* replaceChar(char* str, char ch, char Newch){
    int i;
    for(i = 0; i <= strlen(str); i++)
      {
          if(str[i] == ch)
        {
              str[i] = Newch;
         }
    }

    return str;
}

void remove_spaces(char* str) {
    const char* new_str = str;
    do {
        while (*new_str == ' ') {
            ++new_str;
        }
    } while ( (*str++ = *new_str++) );
}

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
/*-------------------------------------------------------------------*/


/*------------------------- Lógica da FILA -------------------------*/

typedef struct elem {
    int info;
    char nome;
    struct elem *ligado_com;
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

    tipo_elem *novo_elemento = malloc(sizeof(tipo_elem));
    if(novo_elemento == NULL)
        return false;

    // strcpy(novo_elemento->nome, nome);
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

_Bool ehBalanceada(char *expressao){
    /* cria pilha para verificar chave e colchete */
    Pilha* stack = NULL;
    char coringa;
    int i;
    for (i = 0; expressao[i] != '\0'; i++){
        if(expressao[i] == '{'){
            push(&stack, expressao[i]);
        }

        if(expressao[i] == '}'){
            coringa = pop(&stack);
            if(coringa != '{'){
                return false;
            }
        }

        if(expressao[i] == '('){
            push(&stack, expressao[i]);
        }

        if(expressao[i] == ')'){
            coringa = pop(&stack);
            if(coringa != '('){
                return false;
            }
        }

        if(expressao[i] == '['){
            push(&stack, expressao[i]);
        }

        if(expressao[i] == ']'){
            coringa = pop(&stack);
            if(coringa != '['){
                return false;
            }
        }
    }

    if(!isEmptyPilha(stack)){
        return false;
    }

    return true;
}


_Bool operadoresSemNumeros(char *expressao){

    /* cria fila */
    fila q_fila;
    create(&q_fila);
    fila saida;
    create(&saida);

    char coringa;
    int i;
    int flag = 0;

    for (i = 0; expressao[i] != '\0'; i++){
        if(expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*'
        || expressao[i] == '/' || expressao[i] == '^' )
        {
            enqueue(&q_fila, expressao[i]);
        } else {
            enqueue(&saida, expressao[i]);
        }
    }

    while(!isEmpty(&saida)){
        coringa = dequeue(&saida);
        // printf("%c\n", coringa);

        if(flag){
            if(flag == 2){
                if(coringa == '0' || coringa == '1' || coringa == '2'
                || coringa == '3' || coringa == '4' || coringa == '5'
                || coringa == '6' || coringa == '7' || coringa == '8'
                || coringa == '9' || coringa == '(' || coringa == ')')
                {
                    return false;
                }
                flag = 0;
            } else {
                if(coringa == '.' || coringa == ')'){
                    flag = 0;
                } else{
                    flag++;
                }
            }
        }

        if(coringa == '0' || coringa == '1' || coringa == '2'
        || coringa == '3' || coringa == '4' || coringa == '5'
        || coringa == '6' || coringa == '7' || coringa == '8'
        || coringa == '9')
        {
            // printf("## %c\n", coringa);
            flag = 1;
        }
    }

    /* esvaziar q_fila */
    while(!isEmpty(&q_fila)){
        coringa = dequeue(&q_fila);
    }

    return true;
}

_Bool numerosSemOperadores(char *expressao_entrada){

    char expressao[101];
    strcpy(expressao, replaceChar(expressao_entrada, '[', '('));
    strcpy(expressao, replaceChar(expressao_entrada, ']', ')'));
    strcpy(expressao, replaceChar(expressao_entrada, '{', '('));
    strcpy(expressao, replaceChar(expressao_entrada, '}', ')'));

    Pilha* stack = NULL;
    char coringa;

    int flag = 0;
    int i;

    /* operadores sem numeros na frente */
    for (i = 0; expressao[i] != '\0'; i++){
        if(expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*'
        || expressao[i] == '/' || expressao[i] == '^' )
        {
            flag = 1;
        }

        if(flag){
            if(!(expressao[i+2] == '0' || expressao[i+2] == '1' || expressao[i+2] == '2'
            || expressao[i+2] == '3' || expressao[i+2] == '4' || expressao[i+2] == '5'
            || expressao[i+2] == '6' || expressao[i+2] == '7' || expressao[i+2] == '8'
            || expressao[i+2] == '9' || expressao[i+2] == '('))
            {
                return false;
            }
            flag = 0;
        }
    }

    /* operadores sem numeros atras */
    for (i = 0; expressao[i] != '\0'; i++){
        push(&stack, expressao[i]);

        if(expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*'
        || expressao[i] == '/' || expressao[i] == '^' )
        {
            flag = 1;
        }

        if(flag){
            /* faz o pop tres vezes */
            coringa = pop(&stack);
            coringa = pop(&stack);
            coringa = pop(&stack);

            if(!(coringa == '0' || coringa == '1' || coringa == '2'
            || coringa == '3' || coringa == '4' || coringa == '5'
            || coringa == '6' || coringa == '7' || coringa == '8'
            || coringa == '9' || coringa == ')'))
            {
                return false;
            }
            flag = 0;
        }
    }

    while(!isEmptyPilha(stack)){
        coringa = pop(&stack);
    }

    return true;
}

_Bool parentesesSemOperadores(char *expressao_entrada){
    char expressao[101];
    strcpy(expressao, replaceChar(expressao_entrada, '[', '('));
    strcpy(expressao, replaceChar(expressao_entrada, ']', ')'));
    strcpy(expressao, replaceChar(expressao_entrada, '{', '('));
    strcpy(expressao, replaceChar(expressao_entrada, '}', ')'));

    int flag = 0;
    int i;


    for (i = 0; expressao[i] != '\0'; i++){

        if(flag){
            if(!(expressao[i] == ')' || expressao[i] == ' ')){
                return false;
            }
            flag = 0;
        }

        if(expressao[i] == ')'){
            flag = 1;
        }
    }


    return true;
}

_Bool parentesesVazios(char *expressao_entrada){
    char expressao[101];
    strcpy(expressao, replaceChar(expressao_entrada, '[', '('));
    strcpy(expressao, replaceChar(expressao_entrada, ']', ')'));
    strcpy(expressao, replaceChar(expressao_entrada, '{', '('));
    strcpy(expressao, replaceChar(expressao_entrada, '}', ')'));

    int flag = 0;
    int i;

    for (i = 0; expressao[i] != '\0'; i++){

        if(flag){
            if((expressao[i] == ')' || expressao[i] == ' ')){
                return false;
            }
            flag = 0;
        }

        if(expressao[i] == '('){
            flag = 1;
        }
    }


    return true;

}

int sizeArray(char* expressao){
    int k = 0;
    while(expressao[k] != '\0'){
        k++;
    }

    return k;
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

char *colocaSpaces(char *expressao_dois){

    expressao_dois = removeChavesColchetes(expressao_dois);

    int i;
    int flag = 0;
    int size = 0;
    int size_plus = 0;
    char coringa;

    /* cria pilha */
    Pilha* stack = NULL;

    for (i = 0; expressao_dois[i] != '\0'; i++){

        if(flag){
            if(expressao_dois[i] != ' '){
                push(&stack, ' ');
                size_plus++;
            }

            flag = 0;
        }

        if(expressao_dois[i] == '+' || expressao_dois[i] == '-' || expressao_dois[i] == '*'
        || expressao_dois[i] == '/' || expressao_dois[i] == '^' )
        {

            coringa = pop(&stack);

            if(coringa != ' '){
                push(&stack, coringa);
                push(&stack, ' ');
                size_plus++;
            } else {
                push(&stack, coringa);
            }

            push(&stack, expressao_dois[i]);
            flag = 1;

        } else {
            push(&stack, expressao_dois[i]);
        }

        size++;
    }
    size += size_plus;

    expressao_dois[size--] = '\0';
    while(!isEmptyPilha(stack)){
        expressao_dois[size--] = pop(&stack);
    }

    return expressao_dois;
}


/*----------------------------------------------------------------*/

_Bool valida(const char* expressao) {
    /* Insira seu código aqui. */

    char expressao_tres[101];
    strcpy(expressao_tres, expressao);
    char expressao_dois[101];
    strcpy(expressao_dois, expressao);


    /* ###------------ checar (){}[] ------------------### */
    if(!ehBalanceada(expressao_tres)){
       // printf("1 - aqui\n");
       return false;
    }

    strcpy(expressao_dois, colocaSpaces(expressao_tres));

    /* ###------------ checar operadores-----------------### */
    if(!operadoresSemNumeros(expressao_tres)){
        // printf("2 - aqui\n");
        return false;
    }

    /* ###------------ checar operadores sem numeros-----------------### */
    if(!numerosSemOperadores(expressao_tres)){
        // printf("3 - aqui\n");
        return false;
    }

    /* ###------------ parenteses juntos -> (2)(2) -----------------### */
    if(!parentesesSemOperadores(expressao_tres)){
        // printf("4 - aqui\n");
        return false;
    }

    /* ###------------ parenteses vazios -> () -----------------### */
    if(!parentesesVazios(expressao_tres)){
        // printf("5 - aqui\n");
        return false;
    }

    /* ###------------ limitar o tamanho -----------------### */
    if(sizeArray(expressao_tres) < 4){
        return false;
    }


//    free(expressao_dois);
//    free(expressao_tres);
    return true;
}

int main() {
    char expressao[101];

    scanf("%100[^\n]", expressao);

    if (valida(expressao))
        printf("VALIDA\n");
    else
        printf("INVALIDA\n");

    return 0;
}
