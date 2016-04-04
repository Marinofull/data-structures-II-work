#include "data-structure.h"


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
                print("aqui");
                break;
            case 'm':
                media("aqui");
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
