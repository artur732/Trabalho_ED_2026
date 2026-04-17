#include <string.h>
#include "stringers.h"

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

char removeAcentuacao(char c){
    switch(c){
        case 'Ç': case 'ç':
            return 'c';

        case 'á': case 'à': case 'ã': case 'â':
        case 'Á': case 'À': case 'Ã': case 'Â':
            return 'a';

        case 'ó': case 'ò': case 'õ': case 'ô':
        case 'Ó': case 'Ò': case 'Õ': case 'Ô':
            return 'o';

        case 'é': case 'è': case 'ê':
        case 'É': case 'È': case 'Ê':
            return 'e';

        case 'í': case 'ì':
        case 'Í': case 'Ì':
            return 'i';

        case 'ú': case 'ù': case 'û':
        case 'Ú': case 'Ù': case 'Û':
            return 'u';

        case '.': case ',': case ';': case '"': case '\n': case ':':
            return ' ';
    }

    return c;
}
