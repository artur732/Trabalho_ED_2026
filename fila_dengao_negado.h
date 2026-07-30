#pragma once
typedef struct noidq {

    int id, qtdd;
    struct noidq *prox;
}Noidq;

extern int new_id;

void inicia_noidq(Noidq **l);

Noidq* cria_noidq(int id);

void adiciona_na_lista(Noidq **no, int id);

void atualiza_lista_idq(Noidq **l, int ID);

void printa_lidq(Noidq *l);

void libera_lista_idq(Noidq **no);

int numero_de_aparicoes(int id, Noidq *lista);
