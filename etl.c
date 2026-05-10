#include "etl.h"
#include "stringers.h"
#include "fila.h"
#include "pilha.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define PALAVRA_NAO_INCIADA -1

// Adiciona uma palavra nova a lista
void addTokenFila(char *texto, int comeco, int fim, Fila *saida, Pilha *hist){
    // Copia a faixa onde está a palavra
    char buffer[100];
    String palavraNova, palavraAnterior;
    criaStringFaixa(&palavraNova, texto, comeco, fim);

    // Verifica se há duplicata com a última da fila
    if(!lerFilaFim(saida, &palavraAnterior) || strcmp(palavraAnterior.texto, palavraNova.texto) != 0){
        // Caso não haja duplicata, adiciona a fila
        addFila(saida, palavraNova.texto);
        sprintf(buffer, "\"%s\"", palavraNova.texto);
        pushPilha(hist, buffer);
    }else{
        // Caso haja duplicata
        sprintf(buffer, "Ignorada duplicata: %s", palavraNova.texto);
        pushPilha(hist, buffer);
    }
}

void tokenizacaoRecursivo(char *texto, Fila *saida, Pilha *hist, int comecoPalavra, int atual){
    // Caso base: fim do vetor
    if(texto[atual] == '\0'){
        // Adiciona caso a saída haja uma palavra
        if(comecoPalavra != PALAVRA_NAO_INCIADA){
            addTokenFila(texto, comecoPalavra, atual, saida, hist);
        }
        return;
    }

    // Caso espaço
    if(texto[atual] == ' '){
        // Caso haja palavra ela é adicionada a saída
        if(comecoPalavra != PALAVRA_NAO_INCIADA){
            addTokenFila(texto, comecoPalavra, atual, saida, hist);
        }

        // Chama recursivamente, resetando o campo começo palavra
        return tokenizacaoRecursivo(texto, saida, hist, PALAVRA_NAO_INCIADA, atual+1);
    }

    // Caso tenha um caracter e nenhuma palavra tenha sido inicada
    if(comecoPalavra == PALAVRA_NAO_INCIADA){
        // Chama recursivamente, setando o campo começoPalavra com a posição atual
        return tokenizacaoRecursivo(texto, saida, hist, atual, atual+1);
    }

    // Por fim, caso se encontre no meio da palavra
    // Chama recursivamente apenas atualizando a posiçãoAtual
    return tokenizacaoRecursivo(texto, saida, hist, comecoPalavra, atual+1);
}

void tokenizacao(char *texto, Fila *saida, Pilha *hist){
    pushPilha(hist, "[");
    tokenizacaoRecursivo(texto, saida, hist, 0, 0);
    pushPilha(hist, "]");
}

void imprimeBits(char c){
    for(int i = 7; i >= 0; i--){
        printf("%d", (c>>i)&1);
    }
    printf("\n");
}

void etlLinha(char *texto, Fila *palavras, Pilha *historico){
    // Remove acentuação e deixa em caixa baixa
    int len = strlen(texto);

    //printf("%s\n",texto);
    for(int i = 0; i < len; i++){
        printf("%c %d\t",texto[i], texto[i]);
        imprimeBits(texto[i]);
        // Deixa Minúsculo
        texto[i] = tolower(texto[i]);

        // Tira acentuação
        int removeChars = removeAcentuacao(&texto[i], texto[i+1]);
        for(int j = 1; j <= removeChars && i + j < len; j++){
            shiftString(texto, i+j, len);
            len--;
        }
    }

    // adiciona log
    pushPilha(historico, texto);

    // Faz a tokenização
    tokenizacao(texto, palavras, historico);
}

bool etlArquivo(String caminho, Fila *palavras, Pilha *historico){
    // Abre arquivo
    FILE *arq = fopen(caminho.texto, "r");
    char buffer[BUFFER_SIZE];

    // Verifica se o arquivo foi aberto com sucesso
    if(!arq) return false;

    // Informa que o arquivo foi aberto
    sprintf(buffer, "Aberto: %s", caminho.texto);
    pushPilha(historico, buffer);

    // Faz o etf de cada linha
    while(fgets(buffer, BUFFER_SIZE, arq)){
        etlLinha(buffer, palavras, historico);
    }

    // Fecha arquivo
    fclose(arq);

    // Log
    sprintf(buffer, "Fechado: %s", caminho.texto);
    pushPilha(historico, buffer);

    return true;
}
