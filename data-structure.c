#include "data-structure.h"

int hash1(int key, const int length)
{
    return key % length;
}

int hash2(int key, const int length)
{
    return max(floor(kay/length), 1);
}

pdata create(int id, int age, char *name)
{
    data r;
    r.id = id;
    r.age = age;
    strcpy(r.name, name);
    r.link = NULL; //pode isso? o.O

    return &r;
}

bool acho(int id, FILE *path);

void search(int id, FILE *path)
{
    data r;
    r = acho(id, path);

    if(r){
        printf("chave: %d\n", r.id);
        printf("%s\n", r.name);
        printf("%d\n", r.age);
    }
    else{
        printf("chave nao encontrada: %d\n", id);//ver se eh "nao" sem acento msm
    }
}

void insert(pdata r, FILE *path);



void remove(int id, FILE *path)
{
    //initializations

    if(){
        //...
    }
    else{
        printf("chave nao encontrada: %d\n", id);
    }
}

void print(int i, FILE *path)
{
    data r;
    r = acho(i, path);

    if(r)
    {
        printf("%d: ", i);
        printf("%d ", r.id);
        printf("%s ", r.name);
        printf("%d ", r.age);
        if(r.link)
            printf("%d\n", r.link);
        else
            printf("nulo\n");
    }
    else
        printf("%d: vazio", i);

}

void printAll(FILE *path, int length)
{
    for(int i=0; i<length; i++)
        print(i, path);
}

/*
 *
apenas o valor da média do número de acessos a registros do arquivo, considerando-se uma consulta a cada um dos registros armazenados no arquivo. Esta média deve ser apresentada sempre como um valor real,
com uma única casa decimal.
 */

void media(FILE *path)
{
//talvez seja melhor quando consultar o reg nunca consultado incrementar um contador
//será preciso add mais um campo da estrutura
}
