#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct elem {
    int info;
    char nome[20];
    struct elem *ligado_com;
} tipo_elem;

typedef struct{
    tipo_elem *inicio;
    tipo_elem *fim;
} fila;

// cria fila vazia com dois ponteiros
void create(fila *q) {
    q->inicio = NULL;
    q->fim = NULL;
}

// testa se q está vazia
boolean isEmpty (fila *q) {
    return (q->inicio == NULL);
}

// imprime q
void imprime(fila *q) {

    //usando um ponteiro auxiliar
    tipo_elem *x;
    x = q->inicio;

    //iterando na pilha
    while(x != NULL) {
        printf("%s\n", x->nome);
        x = x->ligado_com;
    }
}

// insere x no fim de q
boolean enqueue(fila *q_fila, char *nome) {

    tipo_elem *novo_elemento = malloc(sizeof(tipo_elem));
    if(novo_elemento == NULL)
        return FALSE;

    strcpy(novo_elemento->nome, nome);
    novo_elemento->ligado_com = NULL;

    if(isEmpty(q_fila)) {
        q_fila->inicio = novo_elemento;
    } else {
        q_fila->fim->ligado_com = novo_elemento;
    }

    q_fila->fim = novo_elemento;
    return TRUE;
}

// remove do topo de q
boolean dequeue(fila *q_fila) {

    tipo_elem *p_elem;
    if (isEmpty(q_fila)) {
        return FALSE;
    }

    p_elem = q_fila->inicio;
    q_fila->inicio = p_elem->ligado_com;

    if(q_fila->inicio == NULL) {
        q_fila->fim = NULL;
    }

    free(p_elem);
    return TRUE;
}

char* alocarChar(int size){
    char* aloc_char = (char*) malloc(size*sizeof(char));
    if(aloc_char == NULL){
        printf("erro\n");
        return 0;
    }
    return aloc_char;
}

void lerTopoFila(fila *q_fila, char *str_rtn){
    if(isEmpty(q_fila)) {
        printf("Fila vazia\n");
        return;
    } else {
        strcpy(str_rtn, q_fila->inicio->nome);
    }
}

void lerFinalFila(fila *q_fila, char *str_rtn){
    if(isEmpty(q_fila)) {
        printf("Fila vazia\n");
        return;
    } else {
        strcpy(str_rtn, q_fila->fim->nome);
    }
}


void liberaChar(char** lib_char){
    if(*lib_char != NULL){
        free(*lib_char);
        *lib_char = NULL;
    }
}

char* entraStringGrande(char* pStr, int len_max){
    unsigned int current_size = 0;

    /*Espera o usuario entrar com a string que vamos analisar*/
    if(pStr != NULL){
    	int c = EOF;
    	unsigned int i =0;

    	while (( c = getchar() ) != '\n' && c != EOF)
    	{
    		pStr[i++]=(char)c;

            /* caso tenhamos chegado no máximo precisamos utilizar o realloc*/
    		if(i == current_size){
                current_size = i+len_max;
    			pStr = realloc(pStr, current_size);
    		}
	    }

    	pStr[i] = '\0';
    }

    return pStr;
}

int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

int isPalindrome(char str[]){
    int l = 0;
    int h = strlen(str) - 1;

    while (h > l){
        if (str[l++] != str[h--]){
            return 0;
        }
    }
    return 1;
}

int containPalindrome(char *string){
    int n = strlen(string);
    int flag = 0;
    char *juncao = malloc(100*sizeof(char));
    char *teste = malloc(40*sizeof(char));
    strncat(juncao, "00", 2);
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            for(int k = i; k <= j; k++){
                strncat(teste, &string[k], 1);
            }
            if(isPalindrome(teste) && (strlen(teste) > 2) ){
                // printf("-->* %s\n", teste);
                // printf("--> %s\n", juncao);
                // printf("--> %s\n", strstr(juncao, teste));
                // printf("--> juncao = %lu\n", strlen(juncao));
                // printf("--> teste = %lu\n", strlen(teste));
                if(strlen(juncao) > strlen(teste)){
                    // printf("1\n");
                    if( strstr(juncao, teste) == NULL ){
                        // printf("**** 1\n");
                        flag++;
                    }
                } else if(strlen(juncao) < strlen(teste)){
                    // printf("2\n");
                    if( strstr(teste, juncao) == NULL ){
                        // printf("**** 2\n");
                        flag++;
                    }
                }
                // printf("\n");
                strncat(juncao, teste, strlen(teste));
                strncat(juncao, "0", 1);
            }
            strcpy(teste, "");
        }
    }
    free(teste);
    free(juncao);
    if(flag >= 2){
        return 1;
    } else {
        return 0;
    }
}

int main(){

    unsigned int len_max = 128;

    char *pStr = alocarChar(len_max);
    char *nomes;

    //cria fila
    fila q_fila;
    create(&q_fila);

    //recebo entrada
    pStr = entraStringGrande(pStr, len_max);
    //separo nomes
    nomes = strtok(pStr, " ");
    while (nomes != NULL) {
        //enfileira
        if(containPalindrome(nomes)){
            enqueue(&q_fila, nomes);
        }
        nomes = strtok(NULL, " ");
    }

    // printf("************\n");
    imprime(&q_fila);

    while(1){
        if(dequeue(&q_fila) == FALSE)
            break;
        dequeue(&q_fila);
    }
	liberaChar(&pStr);
    return 0;
}
