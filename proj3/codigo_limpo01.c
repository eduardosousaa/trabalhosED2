#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <windows.h>

#define N 4 

void para_base3(int num, int *arr) {
    for (int i = 0; i < N; i++) {
        arr[i] = num % 3;
        num /= 3;
    }
}

int **cria_matriz_adjacencia() {
    int tamanho = pow(3, N);
    int **matriz_adjacencia = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++) {
        matriz_adjacencia[i] = calloc(tamanho, sizeof(int));
    }

    int **configuracoes = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++) {
        configuracoes[i] = malloc(N * sizeof(int));
        para_base3(i, configuracoes[i]);
    }

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            int diff = 0;
            for (int k = 0; k < N; k++) {
                if (configuracoes[i][k] != configuracoes[j][k]) {
                    diff++;
                }
            }
            if (diff == 1) {
                int disco_movido;
                for (int k = 0; k < N; k++) {
                    if (configuracoes[i][k] != configuracoes[j][k]) {
                        disco_movido = k;
                        break;
                    }
                }
                int eh_menor = 1;
                for (int k = 0; k < N; k++) {
                    if (configuracoes[i][k] == configuracoes[i][disco_movido] && k < disco_movido) {
                        eh_menor = 0;
                        break;
                    }
                }
                int eh_valido = 1;
                for (int k = 0; k < N; k++) {
                    if (configuracoes[j][k] == configuracoes[j][disco_movido] && k < disco_movido) {
                        eh_valido = 0;
                        break;
                    }
                }
                if (eh_menor && eh_valido) {
                    matriz_adjacencia[i][j] = 1;
                }
            }
        }
    }

    return matriz_adjacencia;
}

int dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final) {
    int tamanho = pow(3, N);
    int *distancias = malloc(tamanho * sizeof(int));
    int *visitados = calloc(tamanho, sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    int indice_inicial = 0;
    for (int i = 0; i < N; i++) {
        indice_inicial += config_inicial[i] * pow(3, i);
    }

    int indice_final = 0;
    for (int i = 0; i < N; i++) {
        indice_final += config_final[i] * pow(3, i);
    }

    distancias[indice_inicial] = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        int min_distancia = INT_MAX;
        int u;
        for (int j = 0; j < tamanho; j++) {
            if (!visitados[j] && distancias[j] <= min_distancia) {
                min_distancia = distancias[j];
                u = j;
            }
        }

        visitados[u] = 1;

        for (int v = 0; v < tamanho; v++) {
            if (!visitados[v] && matriz_adjacencia[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz_adjacencia[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + matriz_adjacencia[u][v];
            }
        }
    }

    return distancias[indice_final];
}

double mede_tempo(int **matriz_adjacencia, int *config_inicial, int *config_final) {
    LARGE_INTEGER inicio, fim, frequencia;

    QueryPerformanceFrequency(&frequencia);

    QueryPerformanceCounter(&inicio);

    dijkstra(matriz_adjacencia, config_inicial, config_final);

    QueryPerformanceCounter(&fim);

    double tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) * 1000 / frequencia.QuadPart;

    return tempo_gasto;
}


int main() {
    int **matriz_adjacencia = cria_matriz_adjacencia();

    int config_inicial[N] = {0, 0, 0, 0};
    int config_final[N] = {2, 2, 2, 2};

    printf("Menor numero de movimentos: %d\n", dijkstra(matriz_adjacencia, config_inicial, config_final));
    printf("Tempo gasto: %f milissegundos\n", mede_tempo(matriz_adjacencia, config_inicial, config_final));

    return 0;
}
