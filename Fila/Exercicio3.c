#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct elem {
    int pos_priority;
    char nome[20];
    struct elem *next;
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

// imprime q reversamente
void printReverse(tipo_elem* head)
{
    // Base case
    if (head == NULL)
       return;

    // print the list after head node
    printReverse(head->next);

    // After everything else is printed, print head
    printf("Atividade: %s Prioridade: #%d\n", head->nome, head->pos_priority);
}


// imprime q
void imprime(fila *q) {
    //usando um ponteiro auxiliar
    tipo_elem *x;
    x = q->inicio;

    //iterando na pilha
    while(x != NULL) {
        printf("Atividade: %s Prioridade: #%d\n", x->nome, x->pos_priority);
        x = x->next;
    }
    printf("\n");
}


// Function to push according to priority
void enqueuePriority(tipo_elem** head, char *nome, int p){
    tipo_elem* start = (*head);

    tipo_elem* temp = malloc(sizeof(tipo_elem));

    strcpy(temp->nome, nome);
    temp->pos_priority = p;

    if ((*head)->pos_priority > p) {
        temp->next = *head;
        (*head) = temp;
    } else {
        while (start->next != NULL &&
               start->next->pos_priority < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

boolean enqueue(fila *q_fila, char *nome, int p) {

    tipo_elem *novo_elemento = malloc(sizeof(tipo_elem));
    if(novo_elemento == NULL)
        return FALSE;

    strcpy(novo_elemento->nome, nome);
    novo_elemento->pos_priority = p;
    novo_elemento->next = NULL;

    if(isEmpty(q_fila)) {
        q_fila->inicio = novo_elemento;
    } else {
        q_fila->fim->next = novo_elemento;
    }

    q_fila->fim = novo_elemento;
    return TRUE;
}

// print x na posicao desejada de q
void printPos(fila *q_fila, int pos) {

    //usando um ponteiro auxiliar
    tipo_elem *temp;
    temp = q_fila->inicio;

    //iterando na pilha
    for(int i = 0; i < pos && temp->next != NULL; i++) {
        temp = temp->next;
    }

    printf("%s %d\n", temp->nome, temp->pos_priority);
}

// remove do topo de q
boolean dequeue(fila *q_fila) {

    tipo_elem *p_elem;
    if (isEmpty(q_fila)) {
        return FALSE;
    }

    p_elem = q_fila->inicio;
    q_fila->inicio = p_elem->next;

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

int isNumeric (const char * s){
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

int main(){

    unsigned int len_max = 250;

    char *pStr = alocarChar(len_max);
    char *pStr_palavra = "";
    char *palavras = "";
    int numero = 0;
    int i;
    int qtd = 0;
    int flag = 0;

    //cria fila
    fila q_fila;
    create(&q_fila);

    while (1) {
        //recebo entrada
        pStr = entraStringGrande(pStr, len_max);
        //separo palavras
        palavras = strtok(pStr, " ");

        if (isNumeric(palavras)){
            numero = atoi(palavras);
            break;
        }

        while(palavras != NULL){

            //enfileira
            if (!isNumeric(palavras) && palavras != NULL){
                pStr_palavra = palavras;
                qtd++;
            } else {
                if(flag == 0){
                    enqueue(&q_fila, pStr_palavra, atoi(palavras));
                    flag++;
                }else{
                    enqueuePriority(&(q_fila.inicio), pStr_palavra, atoi(palavras));
                }
            }
            palavras = strtok(NULL, " ");
        }
    }

    for(i = 0; i < numero; i++){
        dequeue(&q_fila);
        qtd--;
    }

    printf("Tamanho da fila: %d\n", qtd);
    imprime(&q_fila);

    while(1){
        if(dequeue(&q_fila) == FALSE)
            break;
        dequeue(&q_fila);
    }
	liberaChar(&pStr);
    return 0;

    /*
    Tamanho da fila: 5
    Atividade: Comer Prioridade: #1
    Atividade: Academia Prioridade: #2
    Atividade: Dormir Prioridade: #3
    Atividade: ElaborarQuestoes Prioridade: #4
    Atividade: Banhar Prioridade: #5
    */
}
