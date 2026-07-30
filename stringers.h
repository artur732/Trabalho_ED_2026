#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING 50

typedef struct{
    char texto[MAX_STRING];
    size_t tamanho;
}String;

void criaStringFaixa(String *s, char *entrada, int inicio, int fim);
void criaString(String *s, char *entrada);
int removeAcentuacao(char *c1, char c2);
void shiftString(char *string, int comeco, int fim);
