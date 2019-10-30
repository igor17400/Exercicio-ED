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

/*----------------------------------------------------------------*/



/*------------------------- Lógica do VALIDA --------------------------*/

_Bool valida(const char* expressao) {
   /* Insira seu código aqui. */
   char expressao_um[101];
   char expressao_dois[101];
   int i;
   char coringa;
   char char_ant;
   // char char_ant_ant;
   // int flag_ant_ant = 0;
   int pos = 0;
   int flag = 0;
   int flag_abre = 0;
   int flag_op = 0;
   int flag_espaco = 0;

   /* ###--------------------------------### */

   /* cria pilha para verificar chave e colchete */
   Pilha* stack = NULL;

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

   /* ###--------------------------------### */
   char expressao_quatro[101];
   strcpy(expressao_um, expressao);
   strcpy(expressao_quatro, replaceChar(expressao_um, '[', '('));
   strcpy(expressao_quatro, replaceChar(expressao_um, ']', ')'));
   strcpy(expressao_quatro, replaceChar(expressao_um, '{', '('));
   strcpy(expressao_quatro, replaceChar(expressao_um, '}', ')'));

   int size_again = 0;
   for(i = 0; expressao[i] != '\0'; i++){
       size_again++;
   }
   if(size_again < 2){
       return false;
   }


   int flag_y;
   for(i = 0; expressao[i] != '\0'; i++){
       if(flag_y){
           if(expressao[i] == '('){
               return false;
           }
           flag_y = 0;
       }

       if(expressao[i] == ')'){
           flag_y = 1;
       }
   }


   /* ###--------------------------------### */

   char expressao_tres[101];
   strcpy(expressao_um, expressao);
   strcpy(expressao_tres, replaceChar(expressao_um, '[', '('));
   strcpy(expressao_tres, replaceChar(expressao_um, ']', ')'));
   strcpy(expressao_tres, replaceChar(expressao_um, '{', '('));
   strcpy(expressao_tres, replaceChar(expressao_um, '}', ')'));
   // printf("%s\n", expressao_tres);

   /* cria pilha para verificar chave e colchete */
   Pilha* stack_operador = NULL;

    /* logica do numero antes do operador */
    for (i = 0; expressao_tres[i] != '\0'; i++){
        if(expressao_tres[i] == '+' || expressao_tres[i] == '-' || expressao_tres[i] == '*'
        || expressao_tres[i] == '/' || expressao_tres[i] == '^' )
        {
            coringa = pop(&stack_operador);
            if(coringa == '0' || coringa == '1' || coringa == '2' ||
                 coringa == '3' || coringa == '4' || coringa == '5' ||
                 coringa == '6' || coringa == '7' || coringa == '8' ||
                 coringa == '9' || coringa == ')')
            {} else {
                return false;
            }
        }
        if(expressao_tres[i] != ' ')
            push(&stack_operador, expressao_tres[i]);
    }

   /* apaga a lista inteira */
   while(isEmptyPilha(stack_operador)){
       coringa = pop(&stack_operador);
   }

   remove_spaces(expressao_tres);
   /* logica do numero depois do operador */
   int flag_x = 0;
  for (i = 0; expressao_tres[i] != '\0'; i++){
      if(flag_x){
          if(expressao_tres[i]  == '0' || expressao_tres[i]  == '1' || expressao_tres[i]  == '2' ||
               expressao_tres[i]  == '3' || expressao_tres[i]  == '4' || expressao_tres[i]  == '5' ||
               expressao_tres[i]  == '6' || expressao_tres[i]  == '7' || expressao_tres[i]  == '8' ||
               expressao_tres[i]  == '9' || expressao_tres[i]  == '(')
          {
              flag_x = 0;
          } else {
              return false;
          }
      }
      if(expressao_tres[i]  == '+' || expressao_tres[i]  == '-' || expressao_tres[i]  == '*'
      || expressao_tres[i]  == '/' || expressao_tres[i]  == '^' )
      {
          flag_x = 1;
      }
  }

   /* ###--------------------------------### */

   /* cria fila */
   fila q_fila;
   create(&q_fila);

   /* cria pilha para verificar chave e colchete */
   Pilha* stack_numero = NULL;

   strcpy(expressao_um, expressao);
   strcpy(expressao_dois, replaceChar(expressao_um, '[', '('));
   strcpy(expressao_dois, replaceChar(expressao_um, ']', ')'));
   strcpy(expressao_dois, replaceChar(expressao_um, '{', '('));
   strcpy(expressao_dois, replaceChar(expressao_um, '}', ')'));

   for (i = 0; expressao_dois[i] != '\0'; i++){
       enqueue(&q_fila, expressao_dois[i]);
   }

   int size = 0;
   while(expressao_dois[size] != '\0'){
       size++;
   }

   if(expressao_dois[size-1] == '+' || expressao_dois[size-1] == '-' || expressao_dois[size-1] == '*'
        || expressao_dois[size-1] == '/' || expressao_dois[size-1] == '^' || expressao_dois[size-1] == '('){
            // printf("1 ---->\n");
            return false;
        }

   /* logica da primeira posicao */
   while(!isEmpty(&q_fila)){
       coringa = dequeue(&q_fila);
       if(pos == 0){
           if(coringa == '+' || coringa == '-' || coringa == '*'
           || coringa == '/' || coringa == '^' || coringa == ')'  ){
               // printf("2 ---->\n");
               return false;
           }
       }
       pos++;

       if(flag_op){
           if(coringa == ')' ){
               return false;
           }
           flag_op = 0;
       }

       if(coringa == '+' || coringa == '-' || coringa == '*'
            || coringa == '/' || coringa == '^' ){
                flag_op = 1;
        }

       if(flag_abre == 1){
           if(coringa == '+' || coringa == '-' || coringa == '*'
                || coringa == '/' || coringa == '^' || coringa == ')' ){
                    // printf("4 ---->\n");
                    return false;
                }
            flag_abre = 0;
       }

       if(coringa == '('){
           flag++;
           flag_abre = 1;
       }

       if(coringa == ')'){
           flag--;
       }


        if(flag_espaco){
            flag_espaco = 0;
            char_ant = pop(&stack_numero);
            if(coringa == '0' || coringa == '1' || coringa == '2' ||
                 coringa == '3' || coringa == '4' || coringa == '5' ||
                 coringa == '6' || coringa == '7' || coringa == '8' || coringa == '9'){

                    if(char_ant == '0' || char_ant == '1' || char_ant == '2' ||
                         char_ant == '3' || char_ant == '4' || char_ant == '5' ||
                         char_ant == '6' || char_ant == '7' || char_ant == '8' || char_ant == '9'){
                             return false;
                    }
            }

        }

        if(coringa == ' '){
            flag_espaco = 1;
        }

        if(coringa == '0' || coringa == '1' || coringa == '2' ||
             coringa == '3' || coringa == '4' || coringa == '5' ||
             coringa == '6' || coringa == '7' || coringa == '8' || coringa == '9'){
                 char_ant = pop(&stack_numero);
                 push(&stack_numero, coringa);
        }
   }

   if(flag != 0){
       // printf("6 ---->\n");
       return false;
   }


   /* ###--------------------------------### */



   return true;
}
/*----------------------------------------------------------------*/


int main() {
   char expressao[101];

   scanf("%100[^\n]", expressao);

   if (valida(expressao))
       printf("VALIDA\n");
   else
       printf("INVALIDA\n");

   return 0;
}
