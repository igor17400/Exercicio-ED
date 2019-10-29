#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX 30


// {2 ^ [3 - (4 / 8)]}
// {2 * [3 - (4 / 8)]}
//8^3

struct pilhaFloat{
    int topo;
    float v[MAX];
} pf;

struct pilhaChar{
    int topo;
    char v[MAX];
} pc;

float fazConta(float vlr, char op, float vlr2){
    if ('+' == op)
        return vlr + vlr2;
    if ( '-' == op)
        return vlr - vlr2;
    if ( '*' == op)
        return  vlr * vlr2;
    if ('/' == op)
        return vlr / vlr2;
    if('^' == op){
        for(int i = 0; i < vlr2; i++){
            vlr*=vlr;
        }
        return vlr;
    }

    else {
        return 0;
    }
}

float calcula(char str[]) {
    int i;
    float vlr;
    float vlr2;
    char op;
    int flag_abre = 0;
    int flag_fecha = 0;
    int flag_numero = 0;

    /* para cada caracter */
    for (i = 0; str[i] != '\0'; i++){

        /* se for um operador, empilha em pc*/
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^'){
            pc.v[pc.topo++] = str[i];

        }else if (str[i] >= '0' && str[i] <= '9'){ /* se for um número */
            sscanf(str+i, "%f", &vlr); /* le o valor */
            pf.v[pf.topo++] = vlr; /* empilha o valor */
            flag_numero++;

            while (str[i+1] == '.' || (str[i+1] >= '0' && str[i+1] <= '9')) /* passa pelo float */
                i++;

        }else if (str[i] == ')'){ /* se for um fecha parênteses */
            if(flag_numero == 0){
                return -334;
            }
            flag_fecha++;
            vlr2 = pf.v[--(pf.topo)];                    /* desempilha o primeiro valor */
            vlr = pf.v[--(pf.topo)];                     /* desempilha o segundo valor */
            op = pc.v[--(pc.topo)];                      /* desempilha a operação */
            if(op == '+' || op == '-' || op == '*' || op == '/' || op == '^')
                pf.v[pf.topo++] = fazConta (vlr, op, vlr2); /* calcula */
            else
                return -334;

        } else if(str[i] == '('){ /* se for um abre parenteses */
            flag_abre++;
        }
    }

    if(flag_abre != flag_fecha){
        return -334; /* so o indicador de que deu errado */
    }
    return pf.v[pf.topo - 1];
}

char* replaceChar(char* str, char ch, char Newch){
    int i;
    for(i = 0; i <= strlen(str); i++){
  		if(str[i] == ch){
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

_Bool checaParate(char* str){
    int flag_abre = 0;
    int flag_fecha = 0;
    int i;

    /* para cada caracter */
    for ( i= 0; str[i] != '\0'; i++){
        if (str[i] == ')'){ /* se for um fecha parênteses */
            flag_fecha++;
        } else if(str[i] == '('){ /* se for um abre parenteses */
            flag_abre++;
        }
    }

    if(flag_abre != flag_fecha)
        return false; /* so o indicador de que deu errado */
    return true;
}

 _Bool valida(const char* expressao) {
   /* Insira seu código aqui. */
   char expressao_um[101];
   char expressao_dois[101];
   char expressao_tres[101];
   int flag = 0;

   strcpy(expressao_um, expressao);
   strcpy(expressao_dois, replaceChar(expressao_um, '[', '('));
   strcpy(expressao_dois, replaceChar(expressao_um, ']', ')'));
   strcpy(expressao_dois, replaceChar(expressao_um, '{', '('));
   strcpy(expressao_dois, replaceChar(expressao_um, '}', ')'));
   remove_spaces(expressao_dois);
   // printf("1 - %s\n", expressao_dois);

   if(checaParate(expressao_dois) == false){
       // printf("3 - ola\n");
       return false;
   }

   if(expressao_dois[0] != '('){
       char ch1 = '(';
       strncat(expressao_tres, &ch1, 1);
       flag = 1;
   }
   // printf("2 - %s\n", expressao_tres);
   strncat(expressao_tres, expressao_dois, 101);
   // printf("3 - %s\n", expressao_tres);

   int size = 0;
   while(expressao_tres[size] != '\0'){
       size++;
   }

   if(flag == 1){
       char ch2 = ')';
       strncat(expressao_tres, &ch2, 1);
   }

   // printf("final -> %s\n", expressao_tres);
   float resp = calcula (expressao_tres);
   // printf("resp = %f\n",resp );
   if(resp != -334){
       // printf("1 - ola\n");
       return true;
   } else {
       // printf("2 - ola\n");
       return false;
   }
}


int main() {
    char expressao[101];

    scanf("%100[^\n]", expressao);

    if (valida(expressao))
        printf("VALIDA\n");
    else
        printf("INVALIDA\n");

    return 0;
}
