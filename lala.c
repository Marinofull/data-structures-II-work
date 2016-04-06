#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ARQUIVO 11
#define MAXIMO_VALOR_APONTADOR 10

typedef struct {
    int id, age, link;
    char name[20];

}cchain, *pcchain;

//h1 (chave) = chave mod TAMANHO_ARQUIVO
//h2 (chave) = max{ chave/TAMANHO_ARQUIVO, 1}
//O programa deverá conter duas constantes:
// TAMANHO_ARQUIVO: indica o número máximo de registros do arquivo.
// MAXIMO_VALOR_APONTADOR: indica o maior valor possível para o campo apontador

int max(int a, int b);
int hash1(int key);
int hash2(int key);

void initialize();

int search(int id, int *contAccess, int mode);
void insert(int id, char *name, int age);
void remover(int id);
// void print(int i, FILE path);
void printAll();
void media();

// pcchain create(int id, int age, char *name);

// TAMANHO_ARQUIVO: indica o número máximo de registros do arquivo.
// MAXIMO_VALOR_APONTADOR: indica o maior valor possível para o campo apontador
 FILE *f;

int main(){
    int id, age, link, contAccess;
    char name[20], op;

    initialize();

    // cchain r;
    // r.id=16;
    // r.age = 321;
    // r.link = 2;
    // strcpy(r.name, "flavio");
    // fseek(f, sizeof(cchain)*5, SEEK_SET);
    // fwrite(&r, sizeof(cchain), 1, f);
    // r.id=5;
    // r.age = 3231;
    // r.link = 0;
    // strcpy(r.name, "flavia");
    // fseek(f, sizeof(cchain)*7, SEEK_SET);
    // fwrite(&r, sizeof(cchain), 1, f);

    for(;;)
    {
        scanf(" %c", &op);
        switch(op)
        {
            case 'i':
                scanf("%d", &id);
                scanf(" %[^\n]s", name);
                scanf("%d", &age);
                insert(id, name, age);
                break;
            case 'c':
                scanf("%d", &id);
                search(id, &contAccess, 0);
                break;
            case 'r':
                scanf("%d", &id);
                remover(id);
                break;
            case 'p':
                printAll();
                break;
            case 'm':
                media();
                break;
            case 'e':
                return 0;
                break;
        }
    }

    return 0;
}



int max(int a, int b)//melhor reescrever como macro dpois
{
    return (a>b)?a:b;
}

/*
 * https://stackoverflow.com/questions/7868373/get-whole-number-part-of-a-float-objective-c
 * the guy sads "Converting to int won't work if the floating-point number is outside the range of int."
 * then concert to a long kkk
 * */


int hash1(int key)
{
    return key % TAMANHO_ARQUIVO;
}

int hash2(int key)
{
    return max(key/TAMANHO_ARQUIVO , 1);
}

void initialize()
{
    f = fopen("lili", "r+b");
    if(!f)
    {
        int i;
        f = fopen("lili", "w+b");
        cchain r;
        r.id = -1;
        r.link = 0;
        for(i=0; i < TAMANHO_ARQUIVO; i++)
            fwrite(&r, sizeof(cchain), 1, f);
    }
}


/*
pcchain create(int id, int age, char *name)
{
    cchain r;
    r.id = id;
    r.age = age;
    strcpy(r.name, name);
    r.link = 0;
    return NULL;
}*/

int search(int id, int *contAccess, int mode)
{
    cchain r;
    int p = hash1(id);
    fseek(f, sizeof(cchain)*p, SEEK_SET);
    fread(&r, sizeof(cchain), 1, f);
    *contAccess = 1;

    for(; (r.id != id) && (r.link != 0 ); )
    {
        p = ((hash2(r.id)*r.link) +p) % TAMANHO_ARQUIVO ; //cchain logic
        fseek(f, sizeof(cchain)*p, SEEK_SET);
        fread(&r, sizeof(cchain), 1, f);
        (*contAccess)++;
    }

    if(mode){
        return (r.id == id)?p:-1; // se num fô faz isso
    }else{
        if(r.id == id)
        { // pq r.id == id
            printf("chave: %d\n", r.id);
            printf("%s\n", r.name);
            printf("%d\n", r.age);
            return p;
        }

        printf("chave nao encontrada: %d\n", id);//ver se eh "nao" sem acento msm
        return -1;
    }
}

void insert(int id, char *name, int age)
{
    int lala, acho, lastChainId;
    cchain r;

    acho = search(id, &lala, 1);
    if(acho == -1){// s n tiver ngm lá começa
        acho = hash1(id);
        fseek(f, sizeof(cchain)*acho, SEEK_SET);
        fread(&r, sizeof(cchain), 1, f);
        if(r.id == -1){// se o primeiro tiver vazio ja foi \o/
            fseek(f, sizeof(cchain)*acho, SEEK_SET);
            r.id = id;
            r.age = age;
            strcpy(r.name, name);
            r.link = 0;
            fwrite(&r, sizeof(cchain), 1, f);
        }
        else
        {
            if(acho == hash1(r.id)){
                int cont = 1, prox = acho, lugar=0;
                while(r.link != 0){
                    prox = (hash2(r.id)*r.link + prox) % TAMANHO_ARQUIVO;
                    fseek(f, sizeof(cchain)*prox, SEEK_SET);
                    fread(&r, sizeof(cchain), 1, f);
                }

                lastChainId = r.id;
                lugar += hash2(lastChainId);
                fseek(f, sizeof(cchain)*((prox+lugar)%TAMANHO_ARQUIVO), SEEK_SET);
                fread(&r, sizeof(cchain), 1, f);
                while(r.id != -1){
                    lugar += hash2(lastChainId);
                    fseek(f, sizeof(cchain)*((prox+lugar)%TAMANHO_ARQUIVO), SEEK_SET);
                    fread(&r, sizeof(cchain), 1, f);
                    cont++;
                }
                r.id = id;
                r.age = age;
                strcpy(r.name, name);
                r.link = 0;
                fseek(f, sizeof(cchain)*((prox+lugar)%TAMANHO_ARQUIVO), SEEK_SET);
                fwrite(&r, sizeof(cchain), 1, f);
                fseek(f, sizeof(cchain)*prox, SEEK_SET);
                fread(&r, sizeof(cchain), 1, f);
                r.link = cont;
                fseek(f, sizeof(cchain)*prox, SEEK_SET);
                fwrite(&r, sizeof(cchain), 1, f);
            }
            else{
                int i;
                for(i=0; i<TAMANHO_ARQUIVO; i++)//concerta o pai
                {
                    fseek(f, sizeof(cchain)*i, SEEK_SET);
                    fread(&r, sizeof(cchain), 1, f);
                    if(r.id != -1)
                        if(((r.link * hash2(r.id) + i)%TAMANHO_ARQUIVO) == acho)
                            break;
                }
                r.link = 0;
                fseek(f, sizeof(cchain)*i, SEEK_SET);
                fwrite(&r, sizeof(cchain), 1, f);



                cchain v[TAMANHO_ARQUIVO];
                int qtdelem=0, prox = acho;

                do{
                    fseek(f, sizeof(cchain)*prox, SEEK_SET);
                    fread(&r, sizeof(cchain), 1, f);
                    v[qtdelem]= r;
                    r.id= -1;
                    fseek(f, sizeof(cchain)*prox, SEEK_SET);
                    fwrite(&r, sizeof(cchain), 1, f);
                    prox = (hash2(v[qtdelem].id)*v[qtdelem].link + prox) % TAMANHO_ARQUIVO;
                    qtdelem++;
                }while(r.link != 0);

                r.id= id;
                r.age = age;
                strcpy(r.name, name);
                r.link = 0;
                fseek(f, sizeof(cchain)*acho, SEEK_SET);
                fwrite(&r, sizeof(cchain), 1, f);

                for(i=0; i+qtdelem; i--)
                    insert(v[-i].id, v[-i].name, v[-i].age);
            }
        }

    }
    else{
        printf("chave ja existente: %d\n", id);
    }


}



void remover(int id)
{
    cchain r;
    int lala, acho;
    acho = search(id, &lala, 1);
    if( acho != -1){
        int i;
        for(i=0; i<TAMANHO_ARQUIVO; i++)//concerta o pai
        {
            fseek(f, sizeof(cchain)*i, SEEK_SET);
            fread(&r, sizeof(cchain), 1, f);
            if(r.id != -1)
                if(((r.link * hash2(r.id) + i)%TAMANHO_ARQUIVO) == acho)
                    break;
        }
        r.link = 0;
        fseek(f, sizeof(cchain)*i, SEEK_SET);
        fwrite(&r, sizeof(cchain), 1, f);

        cchain v[TAMANHO_ARQUIVO];
        int qtdelem=0, prox = acho;

        do{
            fseek(f, sizeof(cchain)*prox, SEEK_SET);
            fread(&r, sizeof(cchain), 1, f);
            v[qtdelem]= r;
            r.id= -1;
            fseek(f, sizeof(cchain)*prox, SEEK_SET);
            fwrite(&r, sizeof(cchain), 1, f);
            prox = (hash2(v[qtdelem].id)*v[qtdelem].link + prox) % TAMANHO_ARQUIVO;
            qtdelem++;
        }while(r.link != 0);

        for(i=-1; i+qtdelem; i--)// n paro de kkk
            insert(v[-i].id, v[-i].name, v[-i].age);
    }
    else{
        printf("chave nao encontrada: %d\n", id);
    }
}

void printAll()
{
    int i;
    cchain r;
    rewind(f);
    for(i=0; i+TAMANHO_ARQUIVO; i--) //kkkkkkkkkkkkkkkkkkkkkk
    {
        fread(&r, sizeof(cchain), 1, f);

        printf("%d: ", -i);
        if(r.id != -1)
        {
            printf("%d ", r.id);
            printf("%s ", r.name);
            printf("%d ", r.age);
            if(r.link)
                printf("%d\n", r.link);
            else
                printf("nulo\n");
        }
        else
            printf("vazio\n");
        }
}

/*
apenas o valor da média do número de acessos a registros do arquivo, considerando-se uma consulta a cada um dos registros armazenados no arquivo. Esta média deve ser apresentada sempre como um valor real,
com uma única casa decimal.
 */

void media()
{
    int i, contAccess;
    float totalAccess = 0, totalFile = 0;
    cchain r;
    for(i=0; -i<TAMANHO_ARQUIVO; i--)//kkkk
    {
        fseek(f, sizeof(cchain)*(-i), SEEK_SET);
        fread(&r, sizeof(cchain), 1, f);

        if(r.id != -1){
            search(r.id, &contAccess, 1);
            totalAccess+=contAccess;
            totalFile++;
        }
    }

    if(totalFile == 0)
        printf("%.1f\n", 0.0);
    else{
        float media = totalAccess/totalFile;
        printf("%.1f\n", media);
    }
}

