#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

#define VG 4 // número de vértices no grafo

void dijkstra(double graph[VG][VG], int V, int src, int dest) {
    double *dist = malloc(V * sizeof(double));
    int *prev = malloc(V * sizeof(int));
    bool *visited = malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++) {
        dist[i] = DBL_MAX;
        prev[i] = -1;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u]))
                u = v;
        }

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    printf("Caminho mais confiavel: %d", src);
    int current = dest;
    while (current != -1) {
        printf(" -> %d", current);
        current = prev[current];
    }
    printf("\n");

    free(dist);
    free(prev);
    free(visited);
}

int main() {
    double graph[VG][VG] = {{0, 0.3, 0.1, 0},
                          {0.3, 0, 0.5, 0.9},
                          {0.1, 0.5, 0, 0.2},
                          {0, 0.9, 0.2, 0}};

    int src, dest;
    while (1){
        printf("Digite o vertice de origem: ");
        scanf("%d", &src);
        if(src==-1){
            break;
        }
        printf("Digite o vertice de destino: ");
        scanf("%d", &dest);

        dijkstra(graph, VG, src, dest);
    }

    return 0;
}
