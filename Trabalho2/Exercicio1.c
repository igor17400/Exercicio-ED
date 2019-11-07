#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

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

void imprimeSemNewLine(fila *q) {

    tipo_elem *x;
    x = q->inicio;

    while(x != NULL) {
        printf("%c", x->nome);
        x = x->ligado_com;
    }
    printf("\n");
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

/* -------------------- FILA UNIVERSAL ------------------ */
/* cria fila */
fila q_fila;
/* ------------------------------------------------------ */

char* alocarChar(int size){
    char* aloc_char = (char*) malloc(size*sizeof(char));
    if(aloc_char == NULL){
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



/*----------------- Lógica da Árvore quaternária --------------------*/
int deslocamento = 0;

typedef struct quad_tree_node{
    int bit;
    struct quad_tree_node *primeiro;
    struct quad_tree_node *segundo;
    struct quad_tree_node *terceiro;
    struct quad_tree_node *quarto;
} quad_tree_node;

typedef struct quad_tree{
    quad_tree_node *raiz;
} quad_tree;

_Bool subdivisaoArvore(quad_tree_node *node, int limite);
void qualPosicaoSubdivisao(quad_tree_node **node, int pos, int limite);

quad_tree_node* criarNoArvore(int bit){
    quad_tree_node *node = (quad_tree_node*) malloc(sizeof(quad_tree_node));
    if(node){
        node->bit = bit;
        node->primeiro = NULL;
        node->segundo = NULL;
        node->terceiro = NULL;
        node->quarto = NULL;
    }
    return node;
} /* criação de um nó da arvore */

void freeNodeArvore(quad_tree_node *node){
    if (node){
        freeNodeArvore(node->primeiro);
        freeNodeArvore(node->segundo);
        freeNodeArvore(node->terceiro);
        freeNodeArvore(node->quarto);
        free(node);
        node = NULL;
    }
} /* apagar um nó da arvore */

_Bool qualPosicaoCriar(quad_tree_node *node, int pos, int bit){
    if(pos == 0){
        node->primeiro = criarNoArvore(bit);
    } else if(pos == 1){
        node->segundo = criarNoArvore(bit);
    } else if(pos == 2){
        node->terceiro = criarNoArvore(bit);
    } else if(pos == 3){
        node->quarto = criarNoArvore(bit);
    }

    return true;
}

int sizeFunction(const char* input){
    char str[100];
    strcpy(str, input);
    int i;
    int size = 0;

    for(i = 0; str[i] != '\0'; i++){
        size++;
    }
    size++;

    return size;
}

void recortaString(char* str, char* nova_str, int pos, int size){
    int i, j;

    for(i = pos, j = 0; str[i] != '\0'; i++, j++){
        nova_str[j] = str[i];
    }

    while(j < size){
        nova_str[j] = '\0';
        j++;
    }
}

void qualPosicaoSubdivisao(quad_tree_node **node, int pos, int limite){
    if(pos == 0){
        subdivisaoArvore((*node)->primeiro, limite);
    } else if(pos == 1){
        subdivisaoArvore((*node)->segundo, limite);
    } else if(pos == 2){
        subdivisaoArvore((*node)->terceiro, limite);
    } else if(pos == 3){
        subdivisaoArvore((*node)->quarto, limite);
    }
}

_Bool subdivisaoArvore(quad_tree_node *node, int limite){

    // imprimeSemNewLine(&q_fila);

    int i = 0;
    int bit = 0;
    char coringa;

    if (node){
        // dequeue(&q_fila);
        while(!isEmpty(&q_fila)){
            if(limite == 4){
                return false;
            }

            coringa = dequeue(&q_fila);
            if(coringa == 'p'){
                deslocamento = 0;
                bit = 2;
                qualPosicaoCriar(node, (i)%4, bit);
                limite++;
                qualPosicaoSubdivisao(&node, (i)%4, 0);
                i++;
                // imprimeSemNewLine(&q_fila);
                continue;
            }

            if(coringa == 'e'){
                bit = 1;
            } else if(coringa == 'f'){
                bit = 0;
            }

            qualPosicaoCriar(node, (i)%4, bit);
            i++;

            limite++;
            deslocamento++;
        }
    }

    return true;
}


quad_tree* inicializacaoArvore(void){
    quad_tree *tree = (quad_tree*)malloc(sizeof(quad_tree));
    if (tree){
        tree->raiz = criarNoArvore(2);
        dequeue(&q_fila);
        subdivisaoArvore(tree->raiz, 0);
    }
    return tree;
}

void freeArvore(quad_tree *tree){
    if (tree){
        freeNodeArvore(tree->raiz);
        free(tree);
    }
}

void mostra_arvore(quad_tree_node* root) {
    printf("(");
    if(root != NULL){
        printf("%i ", root->bit);
        mostra_arvore(root->primeiro);
        printf(" ");
        mostra_arvore(root->segundo);
        printf(" ");
        mostra_arvore(root->terceiro);
        printf(" ");
        mostra_arvore(root->quarto);
    }
    printf(")");
} /* print dos nós da árvore */

/*-------------------------------------------------------------------*/

/*-----------------------  Resposta utilizando arvores ----------------------*/

quad_tree* inicializacaoArvoreResposta(void){
    quad_tree *tree = (quad_tree*)malloc(sizeof(quad_tree));
    if (tree){
        tree->raiz = criarNoArvore(2);
    }
    return tree;
}

quad_tree_node *juntarArvores(quad_tree_node *node1, quad_tree_node *node2){

    if(node1 == NULL){
        return node2;
    }
    if(node2 == NULL){
        return node1;
    }

    if(node1->bit == 0 && node2->bit != 0){
        node2->bit = 0;
        node2->primeiro = NULL;
        node2->segundo = NULL;
        node2->terceiro = NULL;
        node2->quarto = NULL;
    } else if(node1->bit != 0 && node2->bit == 0){
        node1->bit = 0;
        node1->primeiro = NULL;
        node1->segundo = NULL;
        node1->terceiro = NULL;
        node1->quarto = NULL;
    } else if(node1->bit == 0 && node2->bit == 0){
        node1->bit = 0;
    }else if(node1->bit == 1 && node2->bit == 2){
        node1->bit = 2;
    }

    node1->primeiro = juntarArvores(node1->primeiro, node2->primeiro);
    node1->segundo = juntarArvores(node1->segundo, node2->segundo);
    node1->terceiro = juntarArvores(node1->terceiro, node2->terceiro);
    node1->quarto = juntarArvores(node1->quarto, node2->quarto);

    return node1;
}

int calculaValor(quad_tree_node *node, int valor, int *total){

    if(node){
        if(node->bit == 2){
            valor = valor/4;
        } else if(node->bit == 0){
            *total += valor;
        }

        calculaValor(node->primeiro, valor, total);
        calculaValor(node->segundo, valor, total);
        calculaValor(node->terceiro, valor, total);
        calculaValor(node->quarto, valor, total);

        return *total;
    }

    return *total;
}

/*-------------------------------------------------------------------*/


/*-----------------------  Lógica para matriz ------------------------*/
_Bool searchSumMatriz(quad_tree_node* root, int **total, int *turn, int *turn_dentro){
    if (root != NULL){

        /* ------------------------------------ */
        if(*turn_dentro == 1){
            if(root->bit == 0){
                total[0][3] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 2){
            if(root->bit == 0){
                total[0][2] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 3){
            if(root->bit == 0){
                total[1][2] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 4){
            if(root->bit == 0){
                total[1][3] = 1;
            }
            (*turn_dentro) = 0;
            (*turn)++;
            return true;
        }

        /* ------------------------------------ */
        if(*turn_dentro == 5){
            if(root->bit == 0){
                total[0][1] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 6){
            if(root->bit == 0){
                total[0][0] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 7){
            if(root->bit == 0){
                total[1][0] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 8){
            if(root->bit == 0){
                total[1][1] = 1;
            }
            (*turn_dentro) = 0;
            (*turn)++;
            return true;
        }

        /* ------------------------------------ */
        if(*turn_dentro == 9){
            if(root->bit == 0){
                total[2][1] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 10){
            if(root->bit == 0){
                total[2][0] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 11){
            if(root->bit == 0){
                total[3][0] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 12){
            if(root->bit == 0){
                total[3][1] = 1;
            }
            (*turn_dentro) = 0;
            (*turn)++;
            return true;
        }

        /* ------------------------------------ */
        if(*turn_dentro == 13){
            if(root->bit == 0){
                total[2][3] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 14){
            if(root->bit == 0){
                total[2][2] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 15){
            if(root->bit == 0){
                total[3][2] = 1;
            }
            (*turn_dentro)++;
            return true;
        } else if(*turn_dentro == 16){
            if(root->bit == 0){
                total[3][3] = 1;
            }
            (*turn_dentro) = 0;
            return true;
        }

        /* ------------------------------------ */
        if(*turn == 0){
            (*turn)++;
        } else if(*turn == 1){
            if(root->bit == 0){
                total[0][3] = 1;
                total[0][2] = 1;
                total[1][2] = 1;
                total[1][3] = 1;
            } else if(root->bit == 2){
                (*turn_dentro) = 0;
                (*turn_dentro)++;
                (*turn)--;
            }
            (*turn)++;
        } else if(*turn == 2){
            if(root->bit == 0){
                total[0][1] = 1;
                total[0][0] = 1;
                total[1][0] = 1;
                total[1][1] = 1;
            } else if(root->bit == 2){
                (*turn_dentro) = 4;
                (*turn_dentro)++;
                (*turn)--;
            }
            (*turn)++;
        } else if(*turn == 3){
            if(root->bit == 0){
                total[2][1] = 1;
                total[2][0] = 1;
                total[3][0] = 1;
                total[3][1] = 1;
            } else if(root->bit == 2){
                (*turn_dentro) = 8;
                (*turn_dentro)++;
                (*turn)--;
            }
            (*turn)++;
        } else if(*turn == 4){
            if(root->bit == 0){
                total[2][3] = 1;
                total[2][2] = 1;
                total[3][2] = 1;
                total[3][3] = 1;
            } else if(root->bit == 2){
                (*turn_dentro) = 12;
                (*turn_dentro)++;
                (*turn)--;
            }
            (*turn)++;
        }


        searchSumMatriz(root->primeiro, total, turn, turn_dentro);
        searchSumMatriz(root->segundo, total, turn, turn_dentro);
        searchSumMatriz(root->terceiro, total, turn, turn_dentro);
        searchSumMatriz(root->quarto, total, turn, turn_dentro);

        return true;
    }
    return false;
}

int numeroDeNiveis(char *str){
    int i = 0;
    int nNiveis = 0;
    for(i = 0; str[i] != '\0'; i++){
        if(str[i] == 'p'){
            nNiveis++;
        }
    }
    nNiveis++;
    return nNiveis;
}

void criarFila(char *str){
    int i;

    for(i = 0; str[i]!='\0'; i++){
        enqueue(&q_fila, str[i]);
    }
}

int** alocaMatriz(int mLinhas, int nColunas){
    int** matriz;

    matriz = (int**) malloc(mLinhas * sizeof(int*));
    for(int i = 0; i < mLinhas; i++){
        matriz[i] = (int*) malloc(nColunas * sizeof(int));
    }
    return matriz;
}

void desalocaMatriz(int **matriz, int mLinhas, int nColunas){
    for(int i = 0; i < mLinhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void inicializaMatriz(int **matriz, int mLinhas, int nColunas){
    int i, j;
    for(i = 0; i < mLinhas; i++){
        for(j = 0; j < nColunas; j++){
            matriz[i][j] = 0;
        }
    }
}

void printMatriz(int **matriz, int mLinhas, int nColunas){
    int i, j;
    for(i = 0; i < mLinhas; i++){
        for(j = 0; j < nColunas; j++){
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

int totalPixel(int **matriz, int mLinhas, int nColunas){
    int i, j;
    int total = 0;
    for(i = 0; i < mLinhas; i++){
        for(j = 0; j < nColunas; j++){
            total += matriz[i][j]*64;
        }
    }

    return total;
}

void totalPixelDeDuasMatrizes(int **matriz1, int **matriz2, int **resultado, int mLinhas, int nColunas){
    int i, j;
    for(i = 0; i < mLinhas; i++){
        for(j = 0; j < nColunas; j++){
            if(matriz1[i][j]){
                resultado[i][j] = 1;
            }else if(matriz2[i][j]){
                resultado[i][j] = 1;
            } else {
                resultado[i][j] = 0;
            }
        }
    }
}

/*-------------------------------------------------------------------*/

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

/*
peeepffff
peeepeeee

pp(eeef)p(ffee)fe
ppeeefpffeefe
pefepeefe
pefep(eefe)

pp(eeef)p(ffee)fp(eefe)
ppeeefpffeefpeefe
pefee

pp(eeef)p(ffee)fp(eefe)
ppeeefpffeefpeefe
pefee
*/

int main(){

    create(&q_fila);
    int len_max = 1365;

    quad_tree *tree;
    quad_tree *tree2;
    char* str = alocarChar(1365);
    char* str2 = alocarChar(1365);

    int total1 = 0;
    int total_resposta = 0;

//    scanf("%s", str);
    str = entraStringGrande(str, len_max);
    criarFila(str);
//    scanf("%s", str2);
    str2 = entraStringGrande(str2, len_max);

    tree = inicializacaoArvore();
    // mostra_arvore(tree->raiz);
    liberaChar(&str);

    // printf("\n");
    // printf("\n");
    // printf("\n");

    criarFila(str2);
    tree2 = inicializacaoArvore();
    // mostra_arvore(tree2->raiz);
    liberaChar(&str2);

    // printf("\n");
    // printf("\n");
    // printf("\n");

    juntarArvores(tree->raiz, tree2->raiz);
    // mostra_arvore(tree->raiz);


    total_resposta = calculaValor(tree->raiz, 1024, &total1);
    printf("%d\n", total_resposta);

    freeArvore(tree);
    // freeArvore(tree2);
    return 0;
}

/*
Exemplo figura:
--------------
ppeeffpfeeefe
                p
   p          p       f      e
e e f f    f e e e
--------------
--------------
ppeeefpfeeefe
                   p
      p          p       f      e
   e e e f    f e e e
--------------
--------------
pefepeeff
             p
 e       f       e       p
                     e  e f  f
--------------
--------------
pefepeefe
           p
 e      f     e     p
                 e e f e
--------------
p p(eeef) p(ffee) f e
ppeeefpffeefe

                p
    p        p      f      e
e e e f   f f e e
 --------------
 --------------
 p p(eeef) p(ffee) p(eeef) p(ffee)
 ppeeefpffeepeeefpffee

                    p
     p        p           p          e
 e e e f   f f e e     e e e f    f f e e
  --------------
 --------------
 p p(eeef) p(f p(eeef) ee) f e
 ppeeefpfpeeefeefe

                      p
       p                     p           f      e
 e   e   e   f       f    p    e    e
                       e e e f
  --------------
 --------------
 peeef

       p
 e   e   e   f
 --------------
 --------------
 peefe

       p
 e   e   f   e
 --------------
 --------------
 peeepffff

             p
     e    e     e     p
                   f f f f
 --------------
*/

/*
Entrada:                Saída:
--------------------------------
peeef                   512
peefe
*/

/*

pppppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefepppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefeppfefepfefepfefepfefe

pppppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefpppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefefppefefpefefpefefpefef

*/
