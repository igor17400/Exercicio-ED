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

// reverses a string 'str' of length 'len'
void reverse(char *str, int len){
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d){
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint){
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

double calcula(const char* posfixa) {
    /* Insira seu código aqui. */

    int i;
    int flag_float = 0;
    int flag_num_duas_casas = 0;

    double num1 = 0.0;
    double num2 = 0.0;

    char num[101] = "";
    double num_double = 0.0;

    /* cria pilha */
    Pilha* stack = NULL;

    for(i = 0; posfixa[i] != '\0'; i++){
        if(posfixa[i] == '.'){
            continue;
        }

        if(isNumeric(posfixa[i])){

            if(posfixa[i+1] == '.'){
                strcat(num, &posfixa[i]);
                flag_float = 1;
                continue;
            }

            if(flag_float){
                strcat(num, &posfixa[i]);
                continue;
            }

            if(isNumeric(posfixa[i+1])){
                strncat(num, &posfixa[i], 1);
                flag_num_duas_casas = 1;
                continue;
            }

            if(flag_num_duas_casas){
                strncat(num, &posfixa[i], 1);
                continue;
            }

            num_double = atof(&posfixa[i]);
            push(&stack, num_double);
        } else if(posfixa[i] != ' '){
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

        if(posfixa[i] == ' '){

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
