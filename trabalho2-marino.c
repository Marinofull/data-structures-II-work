#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a < b) ? b : a)

void delta1(char *pattern, int *delta1table, int len);
void printdelta1(int *delta1table);
void delta2(char *pattern, int *delta2table, int len);
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
    delta2(pattern, delta2table, patternlength);

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
                printdelta2(pattern, delta2table, patternlength);
                break;
            case 'e':
                return 0;
        }
    }
    return 0;
}

void bmoore(int lent, char *text, int lenp, char *pattern, int *delta1table, int *delta2table){
    int jmp, aux, i, aki;
    //int *whereis;

    for(i=lenp-1;i<lent;){ //for eh parado quando o apontador ultrapassa o tamanho do texto
        aki = compare(text, pattern, lenp, i); //compara o padrão com o fragmento do texto começando pelo apontador i
        if(aki == -1){ //-1 eh quando encontra
            //pop(whereis, i-lenp); //se der tempo troca o print por uma lista das posições
            printf("%d\n", i-(lenp-1)+1); //i-(lenp-1) eh onde o padrão começa, +1 pra normalizar
            i= i-(lenp-1) + delta2table[0]; //delta2table[0] além de um salto maior que i++, também permite encontrar um padrao que tem prefixo no sufixo do anterior encontrado
        }else{
            aux = i - (lenp -1 - aki);//(lenp-1-aki) é quantos voltou até quebrar. aux recebe o local que quebrou
            i= aux + max(delta2table[aki], delta1table[text[aux]]); //salta o valor maior
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

//letras minúsculas, sem acento; ponto (’.’); vírgula (’,’) e espaço(46, 44, 32[utf-8 unix]).
void printdelta1(int *delta1table){
    int i;
    printf("Tabela Delta 1:\n");
    for (i=97; i<97+25; i++)
        printf("%c: %d\n", i, delta1table[i]);
    printf(".: %d\n", delta1table[46]);
    printf(",: %d\n", delta1table[44]);
    printf("’ ’: %d\n", delta1table[32]);
/*o caractere, seguido de dois pontos (’:’), seguido de um espaço,
seguido do valor de delta1 para o caractere.
Primeiro devem aparecer as letras, em ordem crescente, depois
o ponto (’.’), depois a vírgula (’,’) e depois o espaço. O caractere espaço
deve aparecer como a sequência de caracteres apóstrofe, espaço, apóstrofe
(’ ’).*/
}

int suffix_is_prefix(char *pattern, int lenp, int pos) {
    int i, lensuffix = lenp - pos;
    for (i=0; (i < lensuffix) && (pattern[i] == pattern[pos+i]); i++);
    //se lensuffix-i for zero é pq é prefixo: então retorne 1
    return (lensuffix-i)?0:1;
}

int len_suffix(char *pattern, int lenp, int pos) {
    int i;
    // retorna o lenthg do maior sufixo que repete apartir de pos
    for (i = 0; (pattern[pos-i] == pattern[lenp-1-i]) && (i < pos); i++);
    return i;
}

void delta2(char *pattern, int *delta2table, int lenp){
    int p;
    int last_prefix_index = lenp-1;

    for (p=lenp-1; p>=0; p--) {
        if (suffix_is_prefix(pattern, lenp, p+1)) {
            last_prefix_index = p+1;
        }
        delta2table[p] = last_prefix_index + (lenp-1 - p);
    }

    for (p=0; p < lenp-1; p++) {
        int slen = len_suffix(pattern, lenp, p);
        if (pattern[p - slen] != pattern[lenp-1 - slen]) {
            delta2table[lenp-1 - slen] = lenp-1 - p + slen;
        }
    }
}

void printdelta2(char *pattern, int *delta2table, int len){
    int i;
    printf("Tabela Delta 2:\n");
    for (i=0; i<len; i++){
        if (pattern[i]== 32)
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
