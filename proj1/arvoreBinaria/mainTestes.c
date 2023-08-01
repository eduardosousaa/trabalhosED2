#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "exer1.h"

#define TAM 1000
#define TAM2 75000

void lerArquivo(int vetor[]){
    FILE *arquivo;
    int contador = 0;
    int numero;

    // Abrir o arquivo para leitura
    arquivo = fopen("arquivo_ordenado.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL)
        printf("Erro ao abrir o arquivo.\n");
    // Ler cada número do arquivo e armazená-lo no vetor
    while (fscanf(arquivo, "%d", &numero) != EOF) {
        vetor[contador] = numero;
        contador++;
    }
    // Fechar o arquivo
    fclose(arquivo);
}

int main(){
    int vetor[TAM];

    Curso  *arvoreCursos;
    arvoreCursos = NULL;

    LARGE_INTEGER inicio, fim, frequencia;
    double tempo_total = 0.0;
    double tempo_total2 = 0.0;

     // Obtém a frequência do contador de performance
    QueryPerformanceFrequency(&frequencia); 

    
    // Realiza as inserções 30 vezes
    for (int j = 0; j < 30; j++) {

        // Obtém o tempo inicial
        QueryPerformanceCounter(&inicio);

        lerArquivo(vetor);

        //Criação das árvores com as inserções embaralhadas
        for (int i = 0; i < TAM; i++) {
            int qtd_blocos = sortearNumero();
            int num_semanas = qtd_blocos;
            char nome_curso[50];
            sprintf(nome_curso, "Curso %d", i + 1);
            inserirCurso(&arvoreCursos, criarNoCurso(vetor[i], nome_curso, qtd_blocos, num_semanas));
        }

        // Obtém o tempo final
        QueryPerformanceCounter(&fim);

        // Calcula o tempo total em milissegundos
        double tempo_insercao = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart * 1000;

        tempo_total += tempo_insercao;
    }

    // Calcula a média do tempo de inserção
    double media_tempo_insercao = tempo_total / 30;

    // Exibe o tempo médio de preenchimento da árvore
    printf("Tempo medio: %.5f milissegundos\n", media_tempo_insercao);

    for (int i = 0; i < 30; i++){
        // Obtém o tempo inicial
        QueryPerformanceCounter(&inicio);

        imprimirCursoPeloCodigo(arvoreCursos, 567); //610240
        
        // Obtém o tempo final
        QueryPerformanceCounter(&fim);

        // Calcula o tempo total em milissegundos
        double tempo_busca = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart * 1000;

        tempo_total2 += tempo_busca;
    }

    // Calcula a média do tempo de busca
    double media_tempo_busca = tempo_total2 / 30;

    // Exibe o tempo médio de preenchimento da árvore
    printf("Tempo medio: %.5f milissegundos\n", media_tempo_busca);

    return 0;
}

