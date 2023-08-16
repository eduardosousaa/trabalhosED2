#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define V 4 // número de vértices no grafo

int maxKey(double key[], bool mstSet[]) {
    double max = 0;
    int max_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] > max){
            max = key[v]; 
            max_index = v;
        }

    return max_index;
}

void imprm_camnh(int parent[], int j) {
    /**
     * Imprime o caminho de um vértice até o vértice de destino usando os pais calculados.
     *
     * Esta função imprime o caminho de um vértice até o vértice de destino usando os pais calculados.
     * Ela utiliza recursão para imprimir o caminho na ordem correta.
     *
     * @param parent Um array que armazena os pais de cada vértice no caminho.
     * @param j O vértice de destino para o qual o caminho será impresso.
     */
    if (parent[j] == -1)
        return;

    imprm_camnh(parent, parent[j]);

    printf(" -> %d", j);
}

void iniclz_array(double *dist, bool *sptSet, int *parent){
    /**
     * Inicializa os arrays de distâncias, sptSet e parent com valores padrão.
     *
     * Esta função inicializa os arrays de distâncias, sptSet e parent com valores padrão.
     * O array de distâncias é preenchido com zeros, o array sptSet é preenchido com valores booleanos "false" e o array parent é preenchido com -1.
     *
     * @param dist Um array para armazenar as distâncias.
     * @param sptSet Um array booleano para rastrear se um vértice está incluído no conjunto SPT.
     * @param parent Um array para armazenar os pais de cada vértice.
     */
    for (int i = 0; i < V; i++){
        dist[i] = 0;
        sptSet[i] = false;
        parent[i] = -1;
    }
}

void dijkstra(double graph[V][V], int src, int dest) {
    /**
     * Executa o algoritmo de Dijkstra para encontrar o caminho mais confiável entre vértices em um grafo ponderado.
     *
     * Esta função utiliza o algoritmo de Dijkstra para encontrar o caminho mais confiável entre um vértice de origem (src) e um vértice de destino (dest)
     * em um grafo ponderado representado por uma matriz de adjacência.
     * O caminho mais confiável é calculado considerando os pesos das arestas.
     *
     * @param graph A matriz de adjacência representando o grafo ponderado.
     * @param src O vértice de origem para iniciar o cálculo do caminho.
     * @param dest O vértice de destino para o qual o caminho mais confiável será calculado.
     */
    double *dist = malloc(V * sizeof(double));
    bool *sptSet = malloc(V * sizeof(bool));
    int *parent = malloc(V * sizeof(int));

    iniclz_array(dist, sptSet, parent);

    dist[src] = 1;

    for (int count = 0; count < V - 1; count++) {
        int u = maxKey(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++){
            if (!sptSet[v] && graph[u][v] && dist[u] != 0 && dist[u] * graph[u][v] > dist[v]){
                parent[v] = u;
                dist[v] = dist[u] * graph[u][v];
            }
        }
    }

    printf("Caminho mais confiavel: %d", src);
    imprm_camnh(parent, dest);
    printf("\n");

    free(dist);
    free(sptSet);
    free(parent);
}

int main() {
    double graph[V][V] = {{0, 0.3, 0.1, 0},
                          {0.3, 0, 0.5, 0.9},
                          {0.1, 0.5, 0, 0.2},
                          {0, 0.9, 0.2, 0}};

    dijkstra(graph, 2, 3);

    return 0;
}
