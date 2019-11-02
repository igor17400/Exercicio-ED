/** Matricula: 160124981
*       Nome: IGOR LIMA ROCHA AZEVEDO
*      Turma: E*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/*------------------------- Lógica da PILHA -------------------------*/

typedef struct Pilha {
    double num;
    struct Pilha* prox;
} Pilha;

void push(struct Pilha** pilha_ref, double num){
    Pilha *novo_node = (Pilha*) malloc(sizeof(Pilha));
    if(!novo_node){
        printf("Error.");
    } else{
        novo_node->num = num;
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

double pop(Pilha** pilha_ref){
    double saida = 0.0;
    struct Pilha *prox_pilha = NULL;

    if(*pilha_ref == NULL) {
        return saida;
    }

    prox_pilha = (*pilha_ref)->prox;
    saida = (*pilha_ref)->num;
    printf("--> %f\n", saida);
    free(*pilha_ref);
    *pilha_ref = prox_pilha;

    return saida;
}

double topo(Pilha** pilha_ref){
    double saida = 0.0;
    saida = pop(pilha_ref);
    push(pilha_ref, saida);

    return saida;
}

/*-------------------------------------------------------------------*/

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

double calcula(const char* posfixa) {
    /* Insira seu código aqui. */

    int i;
    int flag_float = 0;
    int flag_num_duas_casas = 0;

    double num1 = 0.0;
    double num2 = 0.0;

    char coringa = '\0';
    char num[101] = "";
    double num_double = 0.0;

    /* cria pilha */
    Pilha* stack = NULL;

    for(i = 0; posfixa[i] != '\0'; i++){

        if(posfixa[i] == '.')
            continue;

        if(isNumeric(posfixa[i])){

            if(posfixa[i+1] == '.'){
                strcat(num, &posfixa[i]);
                flag_float = 1;
                continue;
            }

            if(flag_float){
                strcat(num, &posfixa[i]);
            }

            if(isNumeric(posfixa[i+1])){
                strcat(num, &posfixa[i]);
                flag_num_duas_casas = 1;
                continue;
            }

            num_double = atof(&posfixa[i]);
            printf("%f\n", num_double);
            push(&stack, num_double);
        } else {
            num1 = pop(&stack);
            num2 = pop(&stack);
            switch (posfixa[i])
            {
                case '+':
                        push(&stack, num2 + num1);
                        break;
                case '-':
                        push(&stack, num2 - num1);
                        break;
                case '*':
                        printf("2) %f 1) %f\n", num2, num1);
                        push(&stack, num2 * num1);
                        break;
                case '/':
                        push(&stack, num2 / num1);
                        break;
                case '^':
                        push(&stack, pow(num2, num1));
                        break;
            }
        }

        if(posfixa[i+1] == ' '){

             if(flag_float){
                 num_double = atof(num);
                 push(&stack, num_double);
                 strcpy(num, "");
                 flag_float = 0;
            }

            if(flag_num_duas_casas){
                num_double = atof(num);
                push(&stack, num_double);
                strcpy(num, "");
                flag_num_duas_casas = 0;
            }
        }

    }
    return pop(&stack);
}


int main() {
    char posfixa[201];

    scanf("%200[^\n]", posfixa);
    printf("%.5lf\n", calcula(posfixa));

    return 0;
}


/*

Input                                          Result
-------------------------------------------------------------------------------
1 2 3 * +                                      7.00000
1 2 + 3 *                                      9.00000
3.14 2.5 * 7 + 0.25 1 / 42 + -                 -27.40000
1 3 ^ 5 * 4 2 / +                              7.00000

*/
