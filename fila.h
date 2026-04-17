#pragma once

#include "stringers.h"
#include <stdbool.h>

extern int new_id;

typedef struct NoFila{
    String item;
    struct NoFila *prox;
}NoFila;

typedef struct{
    NoFila *comeco;
    NoFila *fim;
}Fila;

void initFila(Fila *f);
bool addFila(Fila *f, char* entrada);
bool removerFila(Fila *f, String *valor);
void limparFila(Fila *f);
bool lerFilaComeco(Fila *f, String *valor);
bool lerFilaFim(Fila *f, String *valor);
