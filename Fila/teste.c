#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

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

void containPalindrome(char *string){
    int n = strlen(string);
    int flag = 0;
    char *teste = malloc(40*sizeof(char));
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            for(int k = i; k <= j; k++){
                strncat(teste, &string[k], 1);
            }
            if(isPalindrome(teste) && strlen(teste) > 2)
                flag++;
            strcpy(teste, "");
        }
    }
    free(teste);
    if(flag > 0)
        printf("%s\n", string);
}



int main()
{
    char string[40];
    scanf("%s", string);
    containPalindrome(string);
}
