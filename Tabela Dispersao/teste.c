#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    char nome[20];
    int qtd;
    struct Node *next;
    struct Node *prev;
} Node;

void printList(Node *node){
    Node * temp = node;
    while (temp != NULL)
    {
        printf("%s %d \n", temp->nome, temp->qtd);
        temp = temp->next;
    }
}

void insereNoComeco(struct Node** head_ref, char *nome, int qtd){
    struct Node *novo_node = (struct Node*) malloc(sizeof(Node));
    if(!novo_node){
        printf("Error.");
    } else{
        strcpy(novo_node->nome, nome);
        novo_node->qtd = qtd;
        novo_node->next = *head_ref;
        novo_node->prev = NULL;

        if ((*head_ref) != NULL)
            (*head_ref)->prev = novo_node;

        *head_ref = novo_node;
    }
}

void deletaLista(struct Node** head_ref)
{
   struct Node* atual = *head_ref;
   struct Node* proximo;

   while (atual != NULL){
       proximo = atual->next;
       free(atual);
       atual = proximo;
   }

   *head_ref = NULL;
}

/* Checks whether the value x is present in linked list */
_Bool search(Node* head, char *nome){
    struct Node* current = head;  // Initialize current
    while (current != NULL){
        if (strcmp(current->nome, nome) == 0)
            return true;
        current = current->next;
    }
    return false;
}

void searchIncrementa(Node* head, char *nome){
    struct Node* current = head;  // Initialize current
    while (current != NULL){
        if (strcmp(current->nome, nome) == 0){
            current->qtd++;
        }
        current = current->next;
    }
}

void printListReversa(Node *node)
{
    if(node == NULL){
        return;
    }
    printListReversa(node->next);


    printf("%s %d \n", node->nome, node->qtd);
}

int main(){
    /* Começamos com uma lista vazia */
    Node* head = NULL;
    int qtd;
    scanf("%d", &qtd);
    char nome[20];

    for(int i = 0; i < qtd; i++){
        scanf("%s", nome);
        if(search(head, nome))
            searchIncrementa(head, nome);
        else
            insereNoComeco(&head, nome, 0);
    }

    printListReversa(head);

    return 0;
}
