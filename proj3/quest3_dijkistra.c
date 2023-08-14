#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define V 5 // número de vértices no grafo

int maxKey(double key[], bool mstSet[]) {
    double max = 0;
    int max_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] > max)
            max = key[v], max_index = v;

    return max_index;
}

void dijkstra(double graph[V][V], int src, int dest) {
    double *dist = malloc(V * sizeof(double));
    bool *sptSet = malloc(V * sizeof(bool));
    int *parent = malloc(V * sizeof(int));

    for (int i = 0; i < V; i++){
        dist[i] = 0;
        sptSet[i] = false;
        parent[i] = -1;
    }

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

    printf("Caminho mais confiavel: ");
    int u = dest;
    while(parent[u] != -1){
        printf("%d <- ", u);
        u = parent[u];
    }
    printf("%d\n", src);

    free(dist);
    free(sptSet);
}

int main() {
    double graph[V][V] = {{0, 0.3, 0.1, 0, 0},
                          {0.3, 0, 0.5, 0.9, 0},
                          {0.1, 0.5, 0, 0.2, 0},
                          {0, 0.9, 0.2, 0, 1},
                          {0,   0,   0,   1,   0}};

    dijkstra(graph, 2, 4);

    return 0;
}
