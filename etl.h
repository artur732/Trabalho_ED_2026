#pragma once

#include <stdbool.h>
#include "stringers.h"
#include "fila.h"
#include "pilha.h"

#define BUFFER_SIZE 500

void tokenizacao(char *texto, Fila *saida, Pilha *hist);
bool etlArquivo(String caminho, Fila *palavras, Pilha *historico);
void etlLinha(char *texto, Fila *palavras, Pilha *historico);
