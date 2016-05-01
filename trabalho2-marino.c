#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char op;
    int length;

    scanf("%d", &length);
    //1. o tamanho do padrão (número de caracteres) será menor ou igual ao tamanho do texto;
    char text[length], pattern[length];
    //letras minúsculas, sem acento; ponto (’.’); vírgula (’,’) e espaço. O último
    //caractere do texto e do padrão não será um espaço.
    scanf(" %[^\n]s", text);
    scanf(" %[^\n]s", pattern);

    for(;;){
        scanf("%c", &op);
        switch (op){
            case 's':
                printf("voce selecionou %c", op);
                break;
            case 'u':
                printf("voce selecionou %c", op);
                break;
            case 'd':
                printf("voce selecionou %c", op);
                break;
            case 'e':
                printf("voce selecionou %c", op);
                return 0;
        }
    }
    return 0;
}
