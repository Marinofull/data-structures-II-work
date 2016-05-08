#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delta1(char *pattern, int *delta1table, int len);
void printdelta1(int *delta1table);

int main()
{
    char op;
    int textlength, patternlength;
    int delta1table[128];
    int *delta2table;

    scanf("%d", &textlength);
    //1. o tamanho do padrão (número de caracteres) será menor ou igual ao tamanho do texto;
    char text[textlength], pattern[textlength];
    //letras minúsculas, sem acento; ponto (’.’); vírgula (’,’) e espaço(44, 46, 32[utf-8 unix]). O último
    //caractere do texto e do padrão não será um espaço.
    scanf(" %[^\n]s", text);
    scanf(" %[^\n]s", pattern);
    patternlength = strlen(pattern);

    int i;
    for(i=0; i<128; i++)
        delta1table[i]=patternlength;
    delta1(pattern, delta1table, patternlength);
    delta2table = (int*) malloc(sizeof(int) * patternlength);

    for(;;){
        scanf(" %c", &op);
        switch (op){
            case 's':
                printf("voce selecionou %c\n", op);
                break;
            case 'u':
                //printf("voce selecionou %c\n", op);
                printdelta1(delta1table);
                break;
            case 'd':
                printf("voce selecionou %c\n", op);
                break;
            case 'e':
                printf("voce selecionou %c\n", op);
                return 0;
        }
    }
    return 0;
}
/*
printf("%ld\n", sizeof(text)/sizeof(text[0])); tamanho alocado
printf("%ld\n", strlen(text)); tamanha até o \0
void search(int length, char *text, char *pattern){
    int i, n, v*;
    v = bmoore();
    n= (int) sizeof(v)/sizeof(v[0]);
    for(i=0; i-n; i--)
        printf("%d\n", v[i]);
    free(v);
}

int* bmoore(int length, char *text, char *pattern){}
int* delta2(char *pattern){}
void printdelta2(int *delta2table){}
*/

void delta1(char *pattern, int *delta1table, int len){
    int i;
    for(i=0; i<len; i++)
        delta1table[pattern[i]]= len - (i+1);
}

//letras minúsculas, sem acento; ponto (’.’); vírgula (’,’) e espaço(46, 44, 32[utf-8 unix]). O último
void printdelta1(int *delta1table){
    int i;
    printf("Tabela Delta 1:\n");
    for (i=97; i<97+25; i++)
        printf("%c: %d\n", i, delta1table[i]);
    printf("’.’: %d\n", delta1table[46]);
    printf("’,’: %d\n", delta1table[44]);
    printf("’ ’: %d\n", delta1table[32]);
    //printf("’.’: %d", delta1table['.']);
    //printf("’,’: %d", delta1table[',']);
    //printf("’ ’: %d", delta1table[' ']);
/*o caractere, seguido de dois pontos (’:’), seguido de um espaço,
seguido do valor de delta1 para o caractere.
Primeiro devem aparecer as letras, em ordem crescente, depois
o ponto (’.’), depois a vírgula (’,’) e depois o espaço. O caractere espaço
deve aparecer como a sequência de caracteres apóstrofe, espaço, apóstrofe
(’ ’).*/
}
