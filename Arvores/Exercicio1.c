#include <stdio.h>
#include <stdlib.h>


typedef struct ab_int{
    int dado;
    struct ab_int *esq;
    struct ab_int *dir;
} ab_int;

typedef struct ab_char{
    char dado;
    struct ab_char *esq;
    struct ab_char *dir;
} ab_char;

void criarArvore(ab_int **pRaiz){
    *pRaiz = NULL;
}

int alturaChar(ab_char *raiz) {
    /* Insira o código aqui. */
    if(raiz == NULL)
        return 0;

    int esquerda = alturaChar(raiz->esq);
    int direita = alturaChar(raiz->dir);

    if (esquerda > direita) {
        return esquerda + 1;
    } else {
        return direita + 1;
    }
}

void insere(ab_char** p_raiz, ab_char* e) {
    /* Insira o código aqui. */
    if(e == NULL){
        return;
    }

    if (*p_raiz == NULL){
	      *p_raiz = (ab_char*)malloc(sizeof(ab_char));
	      (*p_raiz)->esq = NULL;
	      (*p_raiz)->dir = NULL;
	      (*p_raiz)->dado = e->dado;
	} else {
        int altura_dir = alturaChar((*p_raiz)->dir);
        int altura_esq = alturaChar((*p_raiz)->esq);

        if (altura_dir < altura_esq) {
			insere(&((*p_raiz)->dir), e);
		} else {
			insere(&((*p_raiz)->esq), e);
		}
	}
}


void insereIgor(ab_char** p_raiz, char e) {
    /* Insira o código aqui. */

    if (*p_raiz == NULL){
	      *p_raiz = (ab_char*)malloc(sizeof(ab_char));
	      (*p_raiz)->esq = NULL;
	      (*p_raiz)->dir = NULL;
	      (*p_raiz)->dado = e;
	} else {
        int altura_dir = alturaChar((*p_raiz)->dir);
        int altura_esq = alturaChar((*p_raiz)->esq);

        if (altura_dir < altura_esq) {
            insereIgor(&((*p_raiz)->dir), e);
		} else {
			insereIgor(&((*p_raiz)->esq), e);
		}
	}
}


// (a (b (e () ()) (f () ())) (c (d () ()) ()))

// (a (b (c (e (f () ()) ()) ()) ()) (d () ()))

void insercao(ab_int **pRaiz, int numero2){
	if (*pRaiz == NULL){
	      *pRaiz=(ab_int *)malloc(sizeof (ab_int));
	      (*pRaiz)->esq=NULL;
	      (*pRaiz)->dir=NULL;
	      (*pRaiz)->dado=numero2;
	} else {
		if (numero2 < ((*pRaiz)->dado)) {
			insercao(&((*pRaiz)->esq), numero2);
		} else {
			insercao(&((*pRaiz)->dir), numero2);
		}
	}
}

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int alturaMenosUm(ab_int *raiz){
    if( (raiz == NULL) || (raiz->esq == NULL && raiz->dir == NULL) )
        return 0;


    return 1 + maior(alturaMenosUm(raiz->esq), alturaMenosUm(raiz->dir));
}

int altura(ab_int *raiz) {
    /* Insira o código aqui. */
    if(raiz == NULL)
        return 0;

    int esquerda = altura(raiz->esq);
    int direita = altura(raiz->dir);

    if (esquerda > direita) {
        return esquerda + 1;
    } else {
        return direita + 1;
    }
}

void exibirEmOrdem(ab_int *pRaiz){
    if(pRaiz != NULL){
        exibirEmOrdem(pRaiz->esq);
        printf("\n%i", pRaiz->dado);
        exibirEmOrdem(pRaiz->dir);
    }
}

void exibirPreOrdem(ab_int *pRaiz){
    if(pRaiz != NULL){
        printf("\n%i", pRaiz->dado);
        exibirPreOrdem(pRaiz->esq);
        exibirPreOrdem(pRaiz->dir);
    }
}

void mostra_arvore(ab_int* raiz) {
    /* Insira o código aqui. */
    printf("(");
    if(raiz != NULL){
        printf("%i ", raiz->dado);
        mostra_arvore(raiz->esq);
        printf(" ");
        mostra_arvore(raiz->dir);
    }

    printf(")");
}

void mostra_arvore_char(ab_char* raiz) {
    /* Insira o código aqui. */
    printf("(");
    if(raiz != NULL){
        printf("%c ", raiz->dado);
        mostra_arvore_char(raiz->esq);
        printf(" ");
        mostra_arvore_char(raiz->dir);
    }

    printf(")");
}

void createAbChar(ab_char** e, char ch){
    if(*e == NULL){
        (*e)->dado = ch;
        (*e)->esq = NULL;
        (*e)->dir = NULL;
    }
}

void rotaciona_esquerda(ab_char **p_raiz) {
    if((*p_raiz)->dir == NULL)
        return;

    ab_char *q_node;
    ab_char *q_node_dois = NULL;

    q_node = *p_raiz;

    q_node_dois = (*p_raiz)->dir->esq;

    (*p_raiz) = (*p_raiz)->dir;

    (*p_raiz)->esq = q_node;

    q_node->dir = q_node_dois;
}





int main()
{

    ab_int *pRaiz;
    ab_int *raiz_null = NULL;

    ab_char *Raiz = NULL;

    criarArvore(&pRaiz);
    insercao(&pRaiz, 2);
    insercao(&pRaiz, 3);
    insercao(&pRaiz, 1);
    insercao(&pRaiz, 4);

    printf("\n------------------------\n");
    exibirPreOrdem(pRaiz);
    printf("\n------------------------\n");
    exibirEmOrdem(pRaiz);
    printf("\n------------------------\n");
    mostra_arvore(pRaiz);
    printf("\n------------------------\n");
    mostra_arvore(raiz_null);
    printf("\n------------------------\n");

    insereIgor(&Raiz, 'a');
    insereIgor(&Raiz, 'b');
    insereIgor(&Raiz, 'c');
    printf("\n-------########----------\n");
    mostra_arvore_char(Raiz);
    printf("\n------------------------\n");

    printf("\n1)------########----------\n");
    rotaciona_esquerda(&(Raiz->esq));
    mostra_arvore_char(Raiz);
    printf("\n------------------------\n");

    printf("\n2)------########----------\n");
    rotaciona_esquerda(&(Raiz->dir));
    mostra_arvore_char(Raiz);
    printf("\n------------------------\n");

    printf("\n3)------########----------\n");
    rotaciona_esquerda(&(Raiz));
    mostra_arvore_char(Raiz);
    printf("\n------------------------\n");



    return 0;
}
