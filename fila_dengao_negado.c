#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "fila.h"

typedef struct noidq {

    int id, qtdd;
    struct noidq *prox;
}Noidq;


void inicia_noidq(Noidq **l) {

    *l=NULL;
}

Noidq* cria_noidq(int id) {

    Noidq *novo=(Noidq*)malloc(sizeof(Noidq));
    if(novo==NULL) {

        printf("Erro de alocação de memória!\n");
        exit(1);
    }

    novo->qtdd=1;
    novo->prox=NULL;
    novo->id=id;

    return novo;
}


void atualiza_lista_idq(Noidq **l, int ID) {

    if(*l==NULL) {

        Noidq *novo=cria_noidq(ID);
        novo->prox=*l;
        *l=novo;
    } else {

    Noidq *aux=*l;
    Noidq *ant=NULL;

    while(aux!=NULL && aux->id!=ID) {

        ant=aux;
        aux=aux->prox;
    }

    if(aux==NULL) {

        Noidq *novo=cria_noidq(ID);
        novo->prox=aux;
        ant->prox=novo;

    } else {
        aux->qtdd+=1;
    }

    }
}

void adiciona_na_lista(Noidq **no, int id) {

    Noidq *novo=cria_noidq(id);

    if(*no==NULL)  {

        *no=novo;
    } else {

        Noidq *aux=*no;

        while(aux->prox!=NULL) {

            aux=aux->prox;
        }

        aux->prox=novo;
    }
}

void printa_lidq(Noidq *l) {

    Noidq *aux=l;

    while(aux!=NULL) {

        printf("%d|%d -> ", aux->id, aux->qtdd);
        aux=aux->prox;
    }

    printf("NULL\n");
}

void libera_lista_idq(Noidq **no) {

    while(*no!=NULL) {

        Noidq *aux=*no;
        *no=(*no)->prox;
        free(aux);
    }
}

int numero_de_aparicoes(int id, Noidq *lista) {

    Noidq *temp = lista;

    while(temp!=NULL) {

        if(temp->id == id) {

            return temp->qtdd;
        }

        temp=temp->prox;
    }

    return 0;

}

