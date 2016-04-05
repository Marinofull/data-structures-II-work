#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    int id, age, link;
    char name[20];
}data, *pdata;


//h1 (chave) = chave mod TAMANHO_ARQUIVO
//h2 (chave) = max{ chave/TAMANHO_ARQUIVO, 1}
//O programa deverá conter duas constantes:
// TAMANHO_ARQUIVO: indica o número máximo de registros do arquivo.
// MAXIMO_VALOR_APONTADOR: indica o maior valor possível para o campo apontador

float floor(float n);
int max(int a, int b);
int hash1(int key, const int length);
int hash2(int key, const int lenght);


bool acho(int id, FILE *path);
void search(int id, FILE *path);
void insert(pdata r, FILE *path);
void remove(int id, FILE *path);
void print(int i, FILE path);
void printAll(FILE *path, int length);
void media(FILE *path);

pdata create(int id, int age, char *name);
