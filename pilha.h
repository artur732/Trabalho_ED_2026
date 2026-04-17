#pragma once

#include "stringers.h"
#include <stdbool.h>

typedef struct NoPilha{
    String item;
    struct NoPilha *prox;
}NoPilha;

typedef struct{
    NoPilha *topo;
}Pilha;

void initPilha(Pilha *p);
bool pushPilha(Pilha *p, char *log);
void limparPilha(Pilha *p);
void imprimirPilha(Pilha *p);
