#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>

#include "fila.h"
#include "pilha.h"
#include "etl.h"
#include "hashishi.h"
#include "fila_dengao_negado.h"
#include "arve.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    // inicializa variáveis
    int qtdDocumentos;
    char buffer[1000];
    char palavras_buscadas_usuario[100];
    palavras_buscadas_usuario[0]='\0';

    // Fila dos documentos
    Fila documentos;
    initFila(&documentos);

    Pilha historico;
    initPilha(&historico);

    //printf("Tamanho MAX_STRING: %d\n", MAX_STRING);

    // Recebe a quantidade de documentos
    printf("Digite a quantidade de documentos a ser processados: ");
    scanf("%d", &qtdDocumentos);
    getchar();
    printf("\n");

    if(qtdDocumentos <= 0){
        printf("ERRO: Voce deve inserir ao menos um documento!\n");
        return 1;
    }

    // Lê o caminho de cada um e adiciona a fila
    for(int i =0; i < qtdDocumentos; i++){
        // Recebe endereço do documento
        printf("Digite o endereco do documento %d: ", i+1);
        fgets(buffer, MAX_STRING, stdin);
        buffer[strlen(buffer)-1] = '\0';

        addFila(&documentos, buffer);
    }

    printf("Digite as palavras que deseja buscar nos documentos: ");
    fgets(palavras_buscadas_usuario, 100, stdin);

    // Lê cada caminho da fila
    printf("\n");
    String arquivoAtual;

    ///criar três filas (ID + qtdd) e criar tabela hash
    Tabela tabelinha;
    //hash table
    initTabela(&tabelinha);
    //as três lista, com id e quantidade dos respectivos documentos
    Noidq *id_e_qdd[qtdDocumentos];
    for(int i=0;i<qtdDocumentos;i++) {

        inicia_noidq(&id_e_qdd[i]);
    }

    // ETL da entrada do usuários
    Fila palavras_entrada_usuario;
    initFila(&palavras_entrada_usuario);

    etlLinha(palavras_buscadas_usuario, &palavras_entrada_usuario, &historico);

    //CRIAR A ÁRVORE AQUI
    Arvore *abb;
    inicia_arvore(&abb);

    int cont=0;
    while(removerFila(&documentos, &arquivoAtual)){
        ///criar contzinho, pra poder colocar os esquemas nos lugares certos
        // Lista com plavras
        Fila palavrasDocumento;
        initFila(&palavrasDocumento);

        // Faz o ETL
        if(etlArquivo(arquivoAtual, &palavrasDocumento, &historico) == false){
            sprintf(buffer, "Erro ao abrir arquivo %s\n", arquivoAtual.texto);
            //printf(buffer);
            pushPilha(&historico, buffer);
            break;
        }

        ///ERRO  CORRIGIDIO--
        passa_da_fila_p_tabela(&palavrasDocumento, &tabelinha, &id_e_qdd[cont]);

        printa_hash(tabelinha);
        printf("\n\n");
        printa_lidq(id_e_qdd[cont]);


        // TODO Artur: Parte B

        // Intera por cada palavra
        String palavra;
        //printf("\nPALAVRAS\n");
        while(removerFila(&palavrasDocumento, &palavra)){
            // DEBUG: Só para testa, pode remover depois
            //printf("%s\n", palavra.texto);
        }

        // Loop pelas palavras de entrada
        String palavra_entrada;

        int score = 0;

        ///SCORE Árvore
        for(int i = 0; i < palavras_entrada_usuario.size; i++){
            // Lê a palavra na posição i da fila
            lerFilaPos(&palavras_entrada_usuario, i, &palavra_entrada);
            // Calculando o score

            int id_palavra = busca_na_tabela_return_ID(&tabelinha, palavra_entrada.texto);

            if(id_palavra>=0) {

                score += numero_de_aparicoes(id_palavra, id_e_qdd[cont]);
            }
        }

        inserir_na_arvore(&abb, cont, score, arquivoAtual.texto);

        // Imprime nome do arquivo
        printf("Arquivo: %s\n", arquivoAtual.texto);

        for(int i = 0; i < palavras_entrada_usuario.size; i++){
            // Lê a palavra na posição i da fila
            lerFilaPos(&palavras_entrada_usuario, i, &palavra_entrada);
            // Imprime a palavra
            printf("%s\n", palavra_entrada.texto);
        }

        limparFila(&palavrasDocumento);
        cont++;
    }
    ///depois de todo esse pega fogo, preciso criar o big master vector, pra colocar todos os valores nele ainda
    ///(safado)


    char *big_vector[new_id+1];//=malloc(new_id*(sizeof(char*)));

    for(int i=0;i<=new_id;i++) {
        big_vector[i]=NULL;
    }
    passa_ao_big_vector(big_vector, &tabelinha);

    printf("Vetor com as palavras: \n");
    for(int i=0;i<=new_id;i++) {

        if(big_vector[i]!=NULL) {
            printf("[%d]- %s\t",i ,  big_vector[i]);
        }
    }

    printa_relevancias(abb);

    // TODO: Parte C

    // DEBUG
    //printf("\nPILHA\n");
    //imprimirPilha(&historico);

    for(int i=0;i<qtdDocumentos;i++) {

        libera_lista_idq(&id_e_qdd[i]);
    }
    libera_tabela(&tabelinha);
    limparFila(&documentos);
    limparPilha(&historico);
    limparFila(&palavras_entrada_usuario);


    for(int i=1;i<=new_id;i++) {
        free(big_vector[i]);
    }

    libera_arvore(&abb);

    return 0;
}
