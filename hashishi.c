#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "hashishi.h"
#include "fila.h"
#include "stringers.h"
//#include "kk.h"
#include "fila_dengao_negado.h"
#define TAMANHO_TABELA 100

int new_id=1;

// para definir os ID's queridos
//static int new_id=1;

//iniciar tabela
void initTabela(Tabela *tab) {

    for(int i=0;i<TAMANHO_TABELA;i++) {

        tab->celula[i]=NULL;
    }
}


//criar estrutura base da tabela hash
NoHash* cria_no(char *nome) {

    NoHash *novo=(NoHash*)malloc(sizeof(NoHash));
    if(novo==NULL) {

        printf("Erro de alocação de memória!\n");
        exit(1);
    }

    strcpy(novo->palavra,nome);

    //novo->qtdd=0;
    novo->id=new_id;
    new_id+=1;
    novo->prox=NULL;

    return novo;
}


//função hash, que recebe uma palavra como chave
int hash(char *palavra) {

    int fut_chav=0;

    for(int i=0;palavra[i]!='\0';i++) {

        fut_chav+=palavra[i]*i;
    }

    if(fut_chav<0) {

        fut_chav*=-1;
    }

    return fut_chav%TAMANHO_TABELA;
}


//função que insere ordenadamente por ID's
void insere_ordenado(NoHash **l, NoHash *ins) {

    /*if(*l==NULL) {

        *l=ins;
    } else {

        NoHash *aux=*l;
        NoHash *ant;

        while(aux->prox!=NULL && ins->id > aux->id) {

            ant=aux;
            aux=aux->prox;
        }

        if(ins->id < aux->id) {

            ant->prox=ins;
            ins->prox=aux;
        } else {

            aux->prox=ins;
        }
    }*/

    ins->prox=*l;
    *l=ins;
}


//para averiguar se o elemento está na tabela, se deve ser colocado no vetor
bool busca_na_tabela(Tabela *tab, char *pal) {

    int ind = hash(pal);

    if(tab->celula[ind]==NULL) {
        return true;
    }

    NoHash *aux=tab->celula[ind];

     while (aux != NULL) {

        if (strcmp(aux->palavra, pal) == 0) {
            return false;
        }
        aux = aux->prox;
    }

    return true;
}

int busca_na_tabela_return_ID(Tabela *tab, char *pal) {

    int ind = hash(pal);

    if(tab->celula[ind]==NULL) {
        return -1;
    }

    NoHash *aux=tab->celula[ind];

     while (aux != NULL) {

        if (strcmp(aux->palavra, pal) == 0) {
            return aux->id;
        }
        aux = aux->prox;
    }

    return -1;
}

void insere_na_tabela(Tabela *tab, char *nome, Noidq **ldoc) {

    int ind=hash(nome);

    if(busca_na_tabela(tab, nome)) {

        NoHash *novo=cria_no(nome);

        if(tab->celula[ind]!=NULL) {

            //tab->celula[ind]->qtdd=1;

            insere_ordenado(&tab->celula[ind], novo);
        } else {

            //novo->qtdd=1;

            tab->celula[ind]=novo;
        }

    }

    int i_d=busca_na_tabela_return_ID(tab, nome);

    if(i_d>0) {

        atualiza_lista_idq(ldoc, i_d);
    } else {

        printf("L\n");
        //Não faz sentido
    }
}

void passa_da_fila_p_tabela(Fila *f, Tabela *t, Noidq **ldoc) {

    NoFila *aux=f->comeco;

    while(aux!=NULL) {

        insere_na_tabela(t, aux->item.texto, ldoc);
        aux=aux->prox;
    }
}

//há alguma coisa que está dando o erro -1073741819 (0xC0000005), e não está printando na

void printa_lhash(NoHash *l) {

    NoHash *aux=l;

    while(aux!=NULL) {

        printf("%s\t", aux->palavra);
        aux=aux->prox;
    }

    printf("NULL\n");
}

void printa_hash(Tabela tab) {

    for(int i=0;i<TAMANHO_TABELA;i++) {

        NoHash *aux=tab.celula[i];

        if(aux!=NULL) {

            printf("[%d]= ", i+1);
            printa_lhash(aux);
        }
    }
}

void passa_ao_big_vector(char **bv, Tabela *tab) {

    for(int i=0;i<TAMANHO_TABELA;i++) {

        NoHash *aux=tab->celula[i];

        while(aux!=NULL) {

            int tamanho=strlen(aux->palavra);

            bv[aux->id]=malloc((tamanho+1)*sizeof(char));
            if(bv[aux->id]==NULL) {

                printf("Erro de alocação de memória!\n");
                exit(1);
            }

            strcpy(bv[aux->id], aux->palavra);
            aux=aux->prox;
        }
    }
}

void libera_lista_hash(NoHash **no){

    while(*no!=NULL) {

        NoHash *aux=*no;
        *no=(*no)->prox;
        free(aux);
    }
}

void libera_tabela(Tabela *tab) {

    for(int i=0;i<TAMANHO_TABELA;i++) {

        libera_lista_hash(&tab->celula[i]);
    }
}

//Artur, cê tem que fazer uma lista c/ um sentinela que vai guardar todos os ID's e quantas vezes eles repetem.PRA CADA DOCUMENTO TEM QUE TER UM DESSE.
//Além disso, meu bom, cê precisa de construir o vetor global ESTÁtico, onde cada elelemento
//Está na posição [ID]

//man, a estrtégia é: fazer uma função que recebe uma lista que vê nela mesma quantas vezes
//aquela palavra repete (palavra presente na própria lista). Aí a lista tem suas palavras
//de mesmo id apagadas
//
