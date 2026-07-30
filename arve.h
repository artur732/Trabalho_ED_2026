#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct arvore {

    char nome[50];
    int id_documento;
    int score_relevancia;
    struct arvore *dir;
    struct arvore *esq;
} Arvore;

Arvore* cria_no_arvore(int id, int score, char *nome);

void inicia_arvore(Arvore **raiz);

void inserir_na_arvore(Arvore **raiz, int id, int score, char *nome);

void libera_arvore(Arvore **raiz);

void execucao_printa_relevancias(Arvore *raiz);

void printa_relevancias(Arvore *raiz);
