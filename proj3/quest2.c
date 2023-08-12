#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <windows.h>

#define N 4 // Número de discos

// Função para converter um número na base 10 para a base 3
void para_base3(int num, int *arr) {
    for (int i = 0; i < N; i++) {
        arr[i] = num % 3;
        num /= 3;
    }
}

// Função para criar a matriz de adjacência do grafo da Torre de Hanói
int **cria_matriz_adjacencia() {
    // Aloca memória para a matriz de adjacência
    int tamanho = pow(3, N);
    int **matriz_adjacencia = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++) {
        matriz_adjacencia[i] = calloc(tamanho, sizeof(int));
    }

    // Aloca memória para a lista de configurações
    int **configuracoes = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++) {
        configuracoes[i] = malloc(N * sizeof(int));
        para_base3(i, configuracoes[i]);
    }

    // Cria as arestas do grafo
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            // Verifica se as duas configurações diferem em apenas uma posição
            int diff = 0;
            for (int k = 0; k < N; k++) {
                if (configuracoes[i][k] != configuracoes[j][k]) {
                    diff++;
                }
            }
            // Se diferem em apenas uma posição, verifica se o movimento é válido
            if (diff == 1) {
                // Encontra o disco que foi movido
                int disco_movido;
                for (int k = 0; k < N; k++) {
                    if (configuracoes[i][k] != configuracoes[j][k]) {
                        disco_movido = k;
                        break;
                    }
                }
                // Verifica se o disco movido é o menor disco no pino de origem
                int eh_menor = 1;
                for (int k = 0; k < N; k++) {
                    if (configuracoes[i][k] == configuracoes[i][disco_movido] && k < disco_movido) {
                        eh_menor = 0;
                        break;
                    }
                }
                // Verifica se o disco movido foi colocado em cima de um disco maior ou na base de um pino
                int eh_valido = 1;
                for (int k = 0; k < N; k++) {
                    if (configuracoes[j][k] == configuracoes[j][disco_movido] && k < disco_movido) {
                        eh_valido = 0;
                        break;
                    }
                }
                // Se o movimento é válido, cria uma aresta entre as duas configurações
                if (eh_menor && eh_valido) {
                    matriz_adjacencia[i][j] = 1;
                }
            }
        }
    }

    return matriz_adjacencia;
}

// Função para encontrar o menor caminho entre duas configurações usando o Algoritmo Ford-Moore-Bellman
int bellman_ford(int **matriz_adjacencia, int *config_inicial, int *config_final) {
    int tamanho = pow(3, N);
    int *distancias = malloc(tamanho * sizeof(int));

    // Inicializa as distâncias com infinito
    for (int i = 0; i < tamanho; i++) {
        distancias[i] = INT_MAX;
    }

    // Converte a configuração inicial para um índice na matriz de adjacência
    int indice_inicial = 0;
    for (int i = 0; i < N; i++) {
        indice_inicial += config_inicial[i] * pow(3, i);
    }

    // Converte a configuração final para um índice na matriz de adjacência
    int indice_final = 0;
    for (int i = 0; i < N; i++) {
        indice_final += config_final[i] * pow(3, i);
    }

    // Define a distância da configuração inicial como 0
    distancias[indice_inicial] = 0;

    // Executa o Algoritmo Ford-Moore-Bellman
    for (int i = 1; i < tamanho; i++) {
        for (int u = 0; u < tamanho; u++) {
            for (int v = 0; v < tamanho; v++) {
                if (matriz_adjacencia[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz_adjacencia[u][v] < distancias[v]) {
                    distancias[v] = distancias[u] + matriz_adjacencia[u][v];
                }
            }
        }
    }

    // Retorna a menor distância entre a configuração inicial e a configuração final
    return distancias[indice_final];
}

// Função para medir o tempo gasto para encontrar a solução do desafio da Torre de Hanói
double mede_tempo(int **matriz_adjacencia, int *config_inicial, int *config_final) {
    LARGE_INTEGER inicio, fim, frequencia;

    // Obtém a frequência do contador de performance
    QueryPerformanceFrequency(&frequencia);

    // Obtém o tempo inicial
    QueryPerformanceCounter(&inicio);

    bellman_ford(matriz_adjacencia, config_inicial, config_final);

    // Obtém o tempo final
    QueryPerformanceCounter(&fim);

    // Calcula o tempo total em milissegundos
    double tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) * 1000 / frequencia.QuadPart;

    return tempo_gasto;
}

// Exemplo de uso das funções cria_matriz_adjacencia, bellman_ford e mede_tempo para resolver o desafio da Torre de Hanói para o caso de 4 discos
int main() {
    int **matriz_adjacencia = cria_matriz_adjacencia();

    int config_inicial[N] = {0, 0, 0, 0};
    int config_final[N] = {2, 2, 2, 2};

    printf("Menor número de movimentos: %d\n", bellman_ford(matriz_adjacencia, config_inicial, config_final));
    printf("Tempo gasto: %f milissegundos\n", mede_tempo(matriz_adjacencia, config_inicial, config_final));

    return 0;
}