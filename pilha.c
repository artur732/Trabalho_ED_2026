#include "pilha.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// inicializa a pilha
void initPilha(Pilha *p){
    p->topo = NULL;
}

// Adiciona um item a pilha
bool pushPilha(Pilha *p, char *log){
    // Aloca
    NoPilha *novo = malloc(sizeof(NoPilha));

    // Verifica se há erro de memória
    if(!novo) return false;

    // Popula os campos
    criaString(&novo->item, log);
    novo->prox = p->topo;
    // Inseri no topo
    p->topo = novo;

    return true;
}

// Imprimi a pilha
void imprimirPilha(Pilha *p){
    NoPilha *atual = p->topo;
    while(atual){
        printf("%s\n", atual->item.texto);
        atual = atual->prox;
    }
}

// Limpa a pilha
void limparPilha(Pilha *p){
    NoPilha *atual = p->topo;

    while(atual){
        NoPilha *aRemover = atual;
        atual = atual->prox;
        free(aRemover);
    }

    p->topo = NULL;
}
