#include "data-structure.h"
#include <stdio.h>

int max(const long a, const int b)//melhor reescrever como macro dpois
{
    return (a<b)?a:b;
}

/*
 * https://stackoverflow.com/questions/7868373/get-whole-number-part-of-a-float-objective-c
 * the guy sads "Converting to int won't work if the floating-point number is outside the range of int."
 * then concert to a long kkk
 * */
long floor(float x)
{
   return (long) x;
}

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
    r.javi = 0;
    r.link = NULL; //pode isso? o.O

    return &r;
}

bool acho(int id, FILE *path, const int mode);
//quando encontra retorna o registro
//se no reg buscado javi == 0, soma com mode
//se somou, inc no int no inicio do arquivo

void search(int id, FILE *path)
{
    data r;
    r = acho(id, path, 1);

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
        printf("%d: vazio\n", i);

}

void printAll(FILE *path, const int length)
{
    for(int i=0; i+length; i--) //kkkkkkkkkkkkkkkkkkkkkk
        print(i, path);
}

/*
 *
apenas o valor da média do número de acessos a registros do arquivo, considerando-se uma consulta a cada um dos registros armazenados no arquivo. Esta média deve ser apresentada sempre como um valor real,
com uma única casa decimal.
 */

void media(FILE *path, const int length)
{
    int total;
    float media;
    media = total / length;
    //pega o total de acessos no int do começo do arquivo
    printf("%.1f\n", media);
}
