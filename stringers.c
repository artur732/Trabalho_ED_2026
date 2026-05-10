#include <string.h>
#include "stringers.h"
#include <stdint.h>
#include <stdio.h>

typedef struct{
    uint16_t comeco;
    uint16_t fim;
    char substituto;
}faixaUnicodeAscii;

void criaStringFaixa(String *s, char *entrada, int inicio, int fim){
    int tamanho = strlen(entrada);

    // Tratamento de erros
    if(!s) return;
    if(inicio >= fim || !entrada){
        s->texto[0] = '\0';
        s->tamanho = 0;
        return;
    }

    // Evita overflow
    if(fim - inicio > MAX_STRING - 1) fim = MAX_STRING - 2 + inicio;
    if(fim > tamanho) fim = tamanho;

    // Copia caracter por caracter
    int i;
    for(i = 0; i < fim - inicio; i++){
        s->texto[i] = entrada[inicio + i];
    }

    // Coloca \0 e salva o tamanho
    s->texto[i] = '\0';
    s->tamanho = fim - inicio;
}

// Cria uma struct de string, confirmando que não há nenhum erro de memória
void criaString(String *s, char *entrada){
    criaStringFaixa(s, entrada, 0, strlen(entrada));
}

bool imprimInt16(uint16_t num){
    for(int i = 15; i >= 0; i--){
        printf("%d", (num >> i)&1);
    }
    printf("\n");
}

int removeAcentuacao(char *caracter, char proxCaracter){
    // Tablea ASCII padrão
    if(*caracter >= 0){
        switch(*caracter){
            case '.': case ',': case ';': case '"': case '\n':
            case '!': case '?':
                *caracter = ' '; break;
        }

        return 0;
    }

    // Caracteres com acento (parte da tabela UTF-8)
    uint16_t codigo = *caracter & 0b00011111;
    codigo = codigo << 6;
    codigo += proxCaracter & 0b00111111;

    // Lista de caracteres da tabela UNICODE e seu substituto em ASCII
    faixaUnicodeAscii substituto[] = {
        {192, 198, 'a'},
        {199, 199, 'c'},
        {200, 203, 'e'},
        {204, 207, 'i'},
        {208, 208, 'd'},
        {209, 209, 'n'},
        {210, 214, 'o'},
        {217, 220, 'u'},
        {224, 230, 'a'},
        {231, 231, 'c'},
        {232, 235, 'e'},
        {236, 239, 'i'},
        {241, 241, 'n'},
        {242, 246, 'o'},
        {249, 252, 'u'},
    };

    // Passa por cada faixa de códigos UNICODE
    int tamanho = sizeof(substituto) / sizeof(substituto[0]);
    for(int i = 0; i < tamanho; i++){
        // Sai quando não achado
        if(codigo < substituto[i].comeco) break;

        // Quando o código do caracter está dentro da faixa
        if(codigo >= substituto[i].comeco && codigo <= substituto[i].fim){
            *caracter = substituto[i].substituto;
            return 1;
        }
    }

    return 0;
}

void shiftString(char *string, int comeco, int fim){
    for(int i = comeco; i < fim; i++){
        string[i] = string[i+1];
    }
}
