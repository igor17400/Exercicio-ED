#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

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
}

float calcula(char str[])
{
    int i;
    float vlr;
    float vlr2;
    char op;

    /* para cada caracter */
    for ( i= 0; str[i] != '\0'; i++)
    {
        /* se for um operador, empilha em pc*/
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^')
        {
            pc.v[pc.topo++] = str[i];
        }else if (str[i] >= '0' && str[i] <= '9'){ /* se for um número */
            sscanf(str+i, "%f", &vlr); /* le o valor */
            pf.v[pf.topo++] = vlr; /* empilha o valor */

            while (str[i+1] == '.' || (str[i+1] >= '0' && str[i+1] <= '9')) /* passa pelo float */
                i++;

        }else if (str[i] == ')'){ /* se for um fecha parênteses */
            vlr2 = pf.v[--(pf.topo)];                    /* desempilha o primeiro valor */
            vlr = pf.v[--(pf.topo)];                     /* desempilha o segundo valor */
            op = pc.v[--(pc.topo)];                      /* desempilha a operação */
            pf.v[pf.topo++] = fazConta (vlr, op, vlr2); /* calcula */
        }
        /* else --> se for um abre parenteses, simplesmente ignora */
    }
    return pf.v[pf.topo - 1];
}

int main (){
    char str[] = "(2*2)";
    float resp = calcula (str);
    printf ("%g\n", resp);

    return 0;
}
