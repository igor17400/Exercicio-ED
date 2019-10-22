#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct Node
{
    char str[40];
    struct Node *prox;
} Node;

typedef struct elem {
    int info;
    char nome[20];
    struct elem *ligado_com;
} tipo_elem;

typedef struct{
    tipo_elem *inicio;
    tipo_elem *fim;
} fila;

void insereNoComeco(struct Node** head_ref, char *str){
    struct Node *novo_node = (struct Node*)malloc(sizeof(Node));
    if(novo_node == NULL){
        printf("Error.");
    } else{
        // novo_node->str = str;
        strcpy(novo_node->str, str);
        novo_node->prox = *head_ref;

        //SE LIGA
        *head_ref = novo_node;
    }
}

void deletaLista(struct Node** head_ref){
   struct Node* atual = *head_ref;
   struct Node* proximo;

   while (atual != NULL)
   {
       proximo = atual->prox;
       free(atual);
       atual = proximo;
   }

   *head_ref = NULL;
}

void printList(Node *node){
    // printf("*\n");
    Node * temp = node;
    while (temp != NULL)
    {
        printf("%s\n", temp->str);
        temp = temp->prox;
    }
}

char* returnList(Node *node, int size){
    Node * temp = node;
    int i = 0;
    while (temp != NULL){
        if(i == size)
            break;
        temp = temp->prox;
        i++;
    }
    // printf("** %s\n", temp->str);
    return temp->str;
}

void create(fila *q) {
    q->inicio = NULL;
    q->fim = NULL;
}

boolean isEmpty (fila *q) {
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

    if(pStr != NULL){
    	int c = EOF;
    	unsigned int i =0;

    	while (( c = getchar() ) != '\n' && c != EOF)
    	{
    		pStr[i++]=(char)c;

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
    /* Começamos com uma lista vazia */
    Node* head = NULL;

    int n = strlen(string);
    int flag = 0;
    int i, j, k = 0;
    // char juncao[100] = "";
    char *teste = malloc(40*sizeof(char));
    char compare1[40] = "";
    char compare2[40] = "";
    // strncat(juncao, "_", 3);
    int size = 0;

    for(i = 0; i < n; i++){
        for(j = i; j < n; j++){
            for(k = i; k <= j; k++){
                strncat(teste, &string[k], 1);
            }
            if(isPalindrome(teste) && (strlen(teste) > 2) ){
                size++;
                insereNoComeco(&head, teste);
                // printf("-->* %s\n", teste);
                // printList(head);
            }
            strcpy(teste, "");
        }
    }

    /*verificacao de 2-palindrome*/
    for(i = 0; i < size; i++){
        strcpy(compare1, returnList(head, i));
        for(j = i + 1; j < size; j++){
            strcpy(compare2, returnList(head, j));
            if(strlen(compare1) > strlen(compare2)){
                if( strstr(compare1, compare2) == NULL ){
                    flag++;
                }
            } else if(strlen(compare1) <= strlen(compare2)){
                if( strstr(compare2, compare1) == NULL ){
                    flag++;
                }
            }
        }
    }
    // printf("****\n");
    // printList(head);
    // printf("****\n");

    strcpy(teste, "");
    // strcpy(juncao, "");
    free(teste);
    if(flag >= 1){
        return 1;
    } else {
        return 0;
    }
}

int main(){

    unsigned int len_max = 128;

    char *pStr = alocarChar(len_max);
    char *nomes;

    /* cria fila */
    fila q_fila;
    create(&q_fila);

    /* recebo entrada */
    pStr = entraStringGrande(pStr, len_max);
    /* separo nomes */
    nomes = strtok(pStr, " ");
    while (nomes != NULL) {
        if(containPalindrome(nomes)){
            enqueue(&q_fila, nomes);
        }
        nomes = strtok(NULL, " ");
    }

    /*  printf("************\n"); */
    imprime(&q_fila);

    while(1){
        if(dequeue(&q_fila) == FALSE)
            break;
        dequeue(&q_fila);
    }
	liberaChar(&pStr);
    return 0;
}
