#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delta1(char *pattern, int *delta1table, int len);
void printdelta1(int *delta1table);
void delta2(char *pattern, int delta2table, int len);
void printdelta2(char *pattern, int *delta2table, int len);

void bmoore(int lent, char *text, int lenp, char *pattern, int *delta1table, int *delta2table);
int compare(char *text, char *pattern, int lenp, int pos);

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
                bmoore(textlength, text, patternlength, pattern, delta1table, delta2table);
                break;
            case 'u':
                printdelta1(delta1table);
                break;
            case 'd':
                printf("não há nada para opcao %c\n", op);
                break;
            case 'e':
                return 0;
        }
    }
    return 0;
}
/*
printf("%ld\n", sizeof(text)/sizeof(text[0])); tamanho alocado
printf("%ld\n", strlen(text)); tamanho até o \0
void search(int length, char *text, char *pattern){
    int i, n, v*;
    v = bmoore();
    n= (int) sizeof(v)/sizeof(v[0]);
    for(i=0; i-n; i--)
        printf("%d\n", v[i]);
    free(v);
}

int* bmoore(int length, char *text, char *pattern){}
*/

void bmoore(int lent, char *text, int lenp, char *pattern, int *delta1table, int *delta2table){
    int i, aki;
    //int *whereis;

    for(i=lenp-1;i<lent;){ //for eh parado quando o apontador ultrapassa o tamanho do texto
        aki = compare(text, pattern, lenp, i); //compara o padrão com o fragmento do texto começando pelo apontador i
        if(aki == -1){ //-1 eh quando encontra
            //pop(whereis, i-lenp); //se der tempo troca o print por uma lista das posições
            printf("%d\n", i-(lenp-1)+1); //i-(lenp-1) eh onde o padrão começa, +1 pra normalizar
            i++; // enquanto nao ha delta2
            //i= i-(lenp-1) + delta2table[0]; //delta2table[0] além de um salto maior que i++, também permite encontrar um padrao que tem prefixo no sufixo do anterior encontrado
        }else{
            aki = delta1table[text[i-(lenp-1-aki)]];
            i+= (aki)?aki:1; // se o delta1 do salto for zero, então usa 1
            //i+= max(delta2table[aki], delta1table[text[pos-aki]]); //salta o valor maior
        }
    }
}
/*1. busca padrão: Esta operação indicará a partir de quais posições do texto o
padrão ocorre. A posição do primeiro caractere é a posição 1.
A saída desta operação deve indicar, uma por linha,
as posições a partir das quais o padrão ocorre.
Caso o padrão não ocorra no texto, esta operação não gera nenhuma saída.*/

int compare(char *text, char *pattern, int lenp, int pos){
    int i = lenp-1;
    for(; (i>=0) && (text[pos] == pattern[i]); i--, pos--);
    return i;
}

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
    printf(".: %d\n", delta1table[46]);
    printf(",: %d\n", delta1table[44]);
    printf("’ ’: %d\n", delta1table[32]);
    //printf(".: %d", delta1table['.']);
    //printf(",: %d", delta1table[',']);
    //printf("’ ’: %d", delta1table[' ']);
/*o caractere, seguido de dois pontos (’:’), seguido de um espaço,
seguido do valor de delta1 para o caractere.
Primeiro devem aparecer as letras, em ordem crescente, depois
o ponto (’.’), depois a vírgula (’,’) e depois o espaço. O caractere espaço
deve aparecer como a sequência de caracteres apóstrofe, espaço, apóstrofe
(’ ’).*/
}

void delta2(char *pattern, int delta2table, int len){}

void printdelta2(char *pattern, int *delta2table, int len){
    int i;
    printf("Tabela Delta 2:\n");
    for (i=0; i<len; i++){
        if (delta2table[i]== ' ')
            printf("’ ’: %d\n", delta2table[i]);
        else
            printf("%c: %d\n", pattern[i], delta2table[i]);
    }
/*A saída deverá ser da seguinte forma. Na primeira linha, deve aparecer
"Tabela Delta 2:". Em seguida, cada linha conterá o valor de delta2 para
um caractere do padrão. Seguindo os caracteres do padrão, na ordem
em que aparecem, a operação deve imprimir: o caractere, seguido de dois
pontos (’:’), seguido de um espaço, seguido do valor de delta2 para o
caractere. Se o caractere espaço ocorrer no padrão, ele deve aparecer
como a sequência de caracteres apóstrofe, espaço, apóstrofe (’ ’).*/
}
