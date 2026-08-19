#pragma once
#include<stdbool.h>
#include "fila.h"
#include "fila_dengao_negado.h"

#define TAMANHO_TABELA 100

//estrutura base da tabela hash
typedef struct nohash {

    int id;
    char palavra[50];
    struct nohash *prox;
} NoHash;

//estrutura da tabela hash
typedef struct tabela {

    NoHash* celula[TAMANHO_TABELA];
}Tabela;

extern int new_id;

void initTabela(Tabela *tab);

NoHash* cria_no(char *nome);

int hash(char *palavra);

void insere_ordenado(NoHash **l, NoHash *ins);

bool busca_na_tabela(Tabela *tab, char *pal);

int busca_na_tabela_return_ID(Tabela *tab, char *pal);

void insere_na_tabela(Tabela *tab, char *nome, Noidq **ldoc);

void passa_da_fila_p_tabela(Fila *f, Tabela *t, Noidq **ldoc);

void printa_lhash(NoHash *l);

void printa_hash(Tabela tab);

void libera_tabela(Tabela *tab);

void passa_ao_big_vector(char **bv, Tabela *tab);

void libera_lista_hash(NoHash **no);
