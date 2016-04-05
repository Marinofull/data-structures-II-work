#include "data-structure.h"

// TAMANHO_ARQUIVO: indica o número máximo de registros do arquivo.
// MAXIMO_VALOR_APONTADOR: indica o maior valor possível para o campo apontador

int main(){
    int id, age, link;
    char name[20], op;
    FILE f;
    pdata reg;

    for(;;)
    {
        scanf("%c\n", &op);
        switch(op)
        {
            case 'i':
                scanf("%d\n", &id);
                scanf("%s\n", name);
                scanf("%d\n", &age);
                reg = create(id, age, name);
                insert(reg, "aqui");
                break;
            case 'c':
                scanf("%d\n", &id);
                search(id, "aqui");
                break;
            case 'r':
                scanf("%d\n", &id);
                remove(id, "aqui");
                break;
            case 'p':
                printAll("aqui", (int) TAMANHO_ARQUIVO);//presisa msm bindar? o.O
                break;
            case 'm':
                media("aqui", (int) TAMANHO_ARQUIVO);
                break;
            case 'e':
                return 0;
                break;
            default:
                break;
        }
    }

    return 0;
}
