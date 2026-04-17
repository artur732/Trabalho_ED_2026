#include "fila.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Inicia uma fila
void initFila(Fila *f){
    f->comeco = NULL;
    f->fim = NULL;
}

// Adiciona um item a fila
bool addFila(Fila *f, char* entrada){
    // Aloca um novo item
    NoFila *nova = malloc(sizeof(NoFila));

    if(!nova) return false;

    // Popula os campos
    criaString(&nova->item, entrada);
    nova->prox = NULL;

    // Caso fila esteja vazia
    if(!f->fim){
        f->comeco = nova;
        f->fim = nova;
        return true;
    }

    // Outro caso
    f->fim->prox = nova;
    f->fim = nova;

    return true;
}


bool removerFila(Fila *f, String *valor){
    // Verifica se a fila está vazia
    if(!f->comeco){
        return false;
    }

    // Lê o valor
    *valor = f->comeco->item;

    // Remove da Fila
    NoFila *aRemover = f->comeco;
    f->comeco = f->comeco->prox;

    // Caso a lista fique vazia, os dois vetores são atualizados
    if(!f->comeco) f->fim = NULL;

    // Limpa memória
    free(aRemover);

    return true;
}

// Retorna o valor do fim da fila
bool lerFilaFim(Fila *f, String *valor){
    if(!f->fim){
        valor->tamanho = 0;
        valor->texto[0] = '\0';
        return false;
    }

    *valor = f->fim->item;

    return true;
}

bool lerFilaComeco(Fila *f, String *valor){
    // Verifica se a fila está vazia
    if(!f->comeco){
        valor->tamanho = 0;
        valor->texto[0] = '\0';
        return false;
    }

    // Lê o valor
    *valor = f->comeco->item;

    return true;
}

// Limpa memória
void limparFila(Fila *f){
    NoFila *atual = f->comeco;
    while(atual){
        NoFila *aRemover = atual;
        atual = atual->prox;
        free(aRemover);
    }

    f->comeco = NULL;
    f->fim = NULL;
}
