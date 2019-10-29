#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

/*------------------------- Lógica da FILA -------------------------*/

typedef struct elem {
    int info;
    char nome[20];
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
        printf("%s\n", x->nome);
        x = x->ligado_com;
    }
}

_Bool enqueue(fila *q_fila, char *nome) {

    tipo_elem *novo_elemento = malloc(sizeof(tipo_elem));
    if(novo_elemento == NULL)
        return false;

    strcpy(novo_elemento->nome, nome);
    novo_elemento->ligado_com = NULL;

    if(isEmpty(q_fila)) {
        q_fila->inicio = novo_elemento;
    } else {
        q_fila->fim->ligado_com = novo_elemento;
    }

    q_fila->fim = novo_elemento;
    return true;
}

char* dequeue(fila *q_fila) {

    char* simbolo_return = NULL;
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


/*------------------------- Shunting Yard --------------------------------*/

/*
 * Tokens that string is parsed down to.
 */
enum tokens {
    TOKEN_NONE,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_LEFTP,
    TOKEN_RIGHTP,
    TOKEN_POT,
};


/*
 * Conversion strings from tokens.
 */
const static char token2ascii[] = "  +-*/()";
const static char token2prec[]  = "  223311";

/*
 * Stack and stack operations.
 */
#define STACK_SIZE 16
static enum tokens stack[STACK_SIZE];
static int stack_ptr = 0;

int push(enum tokens token){
    if (stack_ptr > STACK_SIZE) {
	       return -1;
    }

    stack[stack_ptr++] = token;

    return 0;
} /* push */

enum tokens pop(void){
    if (stack_ptr == 0) {
	return TOKEN_NONE;
    }

    return stack[--stack_ptr];
} /* pop */

enum tokens top_of_stack(void){
    if (stack_ptr == 0) {
	return TOKEN_NONE;
    }

    return stack[stack_ptr];
} /* top_of_stack */

/*
 * Determine precedence of token and decide wheter to print it
 * or push it onto the stack.
 */
void push_or_print(enum tokens token)
{
    if (token2prec[top_of_stack()] > token2prec[token]) {
	printf("%c ", pop());
    } else {
	push(token);
    }
} /* push_or_print */


void shutingYard(char* expressao){

    /*{2 ^ [3 - (4 / 8)]}*/
    /*{2 * [3 - (4 / 8)]}*/

    int i = 0;
    int number = 0;
    enum tokens token = TOKEN_NONE;

    for(i = 0; i < strlen(expressao); i++){
        switch(expressao[i]){
            case '+':
        	    if (token == TOKEN_NUMBER) {
        		printf("%d ", number);
        		number = 0;
        	    }
        	    push_or_print(TOKEN_PLUS);
        	    break;
            case '-':
        	    if (token == TOKEN_NUMBER) {
        		printf("%d ", number);
        		number = 0;
        	    }
        	    push_or_print(TOKEN_MINUS);
        	    break;
            case '*':
        	    if (token == TOKEN_NUMBER) {
        		printf("%d ", number);
        		number = 0;
        	    }
        	    push_or_print(TOKEN_MULT);
        	    break;
            case '/':
        	    if (token == TOKEN_NUMBER) {
        		printf("%d ", number);
        		number = 0;
        	    }
        	    push_or_print(TOKEN_DIV);
        	    break;
            case '(': /* Parenthesis requires special attention */
        	    if (token == TOKEN_NUMBER) {
        		printf("%d ", number);
        		number = 0;
        	    }
        	    token = TOKEN_LEFTP;
        	    push(token);
        	    break;
            case ')':
        	    if (token == TOKEN_NUMBER) {
        		printf("%d ", number);
        		number = 0;
        	    }
        	    while ((token = pop()) != TOKEN_LEFTP) {
        		if (token == TOKEN_NONE) {
        		    fflush(stdout);
        		    fprintf(stderr, "Parenthesis error\n");
        		    exit(0);
        		}
        		printf("%c ", token2ascii[token]);
        	    }
        	    break;
            case '0':
        	case '1':
        	case '2':
        	case '3':
        	case '4':
        	case '5':
        	case '6':
        	case '7':
        	case '8':
        	case '9':
        	    token = TOKEN_NUMBER;
        	    number = number * 10 + (expressao[i] - '0');
        	    break;
        	default:
        	    fprintf(stderr, "Unknown character detected:%c[%d]\n",
        		    number, number);
        	    number = 0;
        }
    }

    if (token == TOKEN_NUMBER) {
	printf("%d ", number);
	number = 0;
    }

    while ((token = pop()) != TOKEN_NONE) {
	printf("%c ", token2ascii[token]);
    }

    printf("\n");
}

/*----------------------------------------------------------------*/


/*------------------------- Lógica do VALIDA --------------------------*/

_Bool numeroSimboloNumero(fila *q_fila){
    int flag = 0;

    tipo_elem *x;
    x = q_fila->inicio;

    while(x != NULL) {
        if(isNumeric(x->nome) ){
            if(flag == 1){ /* dois numeros seguidos */
                return false;
            }
            flag++;
        } else {
            flag = 0;
        }
        x = x->ligado_com;
    }

    return true;
}

_Bool valida(const char* expressao) {
    /* Insira seu código aqui. */
    int resultado_final = -1;

    char* str = malloc(sizeof(expressao)*sizeof(char));
    strcpy(str, expressao);
    char *simbolos;
    int numero;
    /* cria fila */
    fila q_fila;
    create(&q_fila);

    // printf("------------\n");
    // imprime(&q_fila);
    // printf("------------\n");
    free(str);

    resultado_final = numeroSimboloNumero(&q_fila);

    return resultado_final;
}

/*----------------------------------------------------------------*/


int main() {
    char expressao[101];
    char expressao_dois[101];

    scanf("%100[^\n]", expressao);
    strcpy(expressao_dois, replaceChar(expressao, '[', '('));
    strcpy(expressao_dois, replaceChar(expressao, ']', ')'));
    strcpy(expressao_dois, replaceChar(expressao, '{', '('));
    strcpy(expressao_dois, replaceChar(expressao, '}', ')'));
    remove_spaces(expressao_dois);
    printf("%s\n", expressao_dois);

    shutingYard(expressao_dois);

    // if (valida(expressao))
    //     printf("VALIDA\n");
    // else
    //     printf("INVALIDA\n");

    return 0;
}
