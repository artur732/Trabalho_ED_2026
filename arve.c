#include "arve.h"

Arvore* cria_no_arvore(int id, int score, char *nome) {

    Arvore *nova = (Arvore*)malloc(sizeof(Arvore));
    if(nova==NULL) {

        printf("Erro de alocação de memória!\n");
        exit(0);
    }

    nova->id_documento = id;
    nova->score_relevancia = score;
    strcpy(nova->nome, nome);
    nova->dir = NULL;
    nova->esq = NULL;

    return nova;
}

void inicia_arvore(Arvore **raiz) {

    *(raiz)=NULL;
}

void inserir_na_arvore(Arvore **raiz, int id, int score, char *nome) {


    if((*raiz)==NULL) {
        *raiz = cria_no_arvore(id, score, nome);
        return;
    }

    if((*raiz)->score_relevancia <= score) {
        inserir_na_arvore(&(*raiz)->dir, id, score, nome);

    } else if((*raiz)->score_relevancia > score) {
        inserir_na_arvore(&(*raiz)->esq, id, score, nome);

    }
}

void libera_arvore(Arvore **raiz) {

    if(*raiz==NULL) return;

    if((*raiz)->dir != NULL) {

        libera_arvore(&(*raiz)->dir);
    }

    if((*raiz)->esq != NULL) {

        libera_arvore(&(*raiz)->esq);
    }

    if((*raiz)->dir==NULL && (*raiz)->esq == NULL) {

        free(*raiz);
    }
}

void execucao_printa_relevancias(Arvore *raiz) {

    if(raiz==NULL) return;

    execucao_printa_relevancias(raiz->dir);

    printf("Documento: %s\t Score de relevância: %d\n", raiz->nome, raiz->score_relevancia);

    execucao_printa_relevancias(raiz->esq);
}

void printa_relevancias(Arvore *raiz) {

    printf("Os documentos e sua ordem de relevância confome as palavras dadas são: \n\n");
    execucao_printa_relevancias(raiz);
}

