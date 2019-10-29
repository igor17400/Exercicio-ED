#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
   char key[20];
} DataItem;

int hashCode(char *key, int size) {
    int total = 0;
    for(int i = 0; i < sizeof(key); i++){
        total += key[i];
    }
    printf("-----------\n");
    printf("%d\n", total % size);
    printf("-----------\n");
   return total % size;
}



void insert(DataItem* hashArray, char *key, int size) {

   DataItem *item = (DataItem*) malloc(sizeof(DataItem));
   strcpy(item->key, key);

   //get the hash
   int hashIndex = hashCode(key, size);

   //move in array until an empty or deleted cell
   while(strcmp(hashArray[hashIndex].key, "") != 0) {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= size;
   }

   hashArray[hashIndex] = *item;
}

void display(DataItem* hashArray, int size) {
   int i = 0;

   for(i = 0; i < size; i++) {
      if(strcmp(hashArray[i].key, "") != 0)
         printf(" (%s)",hashArray[i].key);
      else
         printf(" ~~ ");
   }

   printf("\n");
}

// DataItem *search(DataItem* hashArray, int key, int size) {
//    //get the hash
//    int hashIndex = hashCode(key, size);
//
//    //move in array until an empty
//    for(int i = 0; i < size; i++){
//
//       if(hashArray[hashIndex].key == key)
//          return &hashArray[hashIndex];
//
//       //go to next cell
//       ++hashIndex;
//
//       //wrap around the table
//       hashIndex %= size;
//    }
//
//    return NULL;
// }

int main() {
    int size;
    scanf("%d", &size);
    char nome[20];

    for(int i = 0; i < size; i++){
        scanf("%s\n", nome);
    }

    DataItem* hashArray = malloc(size*sizeof(DataItem*));
    DataItem* item;

    for(int i = 0; i < size; i++){
        strcpy(hashArray[i].key, "");
    }

    // insert(hashArray, "doralina", size);
    // insert(hashArray, "gabriela", size);
    // insert(hashArray, "quico", size);
    // insert(hashArray, "gabriela", size);
    // insert(hashArray, "evandro", size);


    display(hashArray, size);
    //
    // item = search(hashArray, 14, size);
    //
    // if(item != NULL) {
    //    printf("Element found: %d\n", item->data);
    // } else {
    //    printf("Element not found\n");
    // }

    free(hashArray);
}
