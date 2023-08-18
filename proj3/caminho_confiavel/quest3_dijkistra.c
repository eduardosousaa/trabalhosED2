#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 4 // número de vértices no grafo

int maior_chave(double chaves[], int arvMenrCamnh[])
{
    /**
     * Encontra o vértice com a maior chave entre os vértices não incluídos na árvore mínima.
     *
     * Esta função percorre as chaves de todos os vértices não incluídos na árvore mínima (arvMenrCamnh)
     * e encontra o vértice com a maior chave. Essa função é frequentemente usada em algoritmos de árvore geradora mínima,
     * como o algoritmo de Prim, para selecionar o próximo vértice a ser adicionado à árvore.
     *
     * @param chaves Um array que armazena as chaves (pesos) associadas a cada vértice.
     * @param arvMenrCamnh Um array que indica quais vértices já estão na árvore mínima (0 para não incluídos, 1 para incluídos).
     * @return O índice do vértice com a maior chave.
     */
    double max = 0;
    int vertice_maior_peso;

    for (int v = 0; v < V; v++)
        if (arvMenrCamnh[v] == 0 && chaves[v] > max)
        {
            max = chaves[v];
            vertice_maior_peso = v;
        }

    return vertice_maior_peso;
}

void imprm_camnh(int pai[], int j)
{
    /**
     * Imprime o caminho de um vértice até um destino utilizando informações de pais.
     *
     * Esta função imprime o caminho percorrido de um vértice até um destino, utilizando informações de pais.
     * Ela utiliza recursão para percorrer o caminho na ordem inversa, indo do destino até o vértice inicial.
     * O caminho é impresso em ordem correta, usando informações armazenadas nos pais de cada vértice.
     *
     * @param pai Um array que armazena os pais de cada vértice no caminho.
     * @param j O vértice de destino para o qual o caminho será impresso.
     */
    if (pai[j] == -1)
        return;

    imprm_camnh(pai, pai[j]);

    printf(" -> %d", j);
}

void iniclz_array(double *dist, int *arvMenrCamnh, int *pai)
{
    /**
     * Inicializa arrays de distâncias, árvore do menor caminho e pais com valores padrão.
     *
     * Esta função inicializa os arrays de distâncias, árvore do menor caminho e pais com valores padrão.
     * Ela percorre os arrays e atribui valores específicos a cada elemento. Os arrays são usados em algoritmos
     * de busca de caminho em grafos.
     *
     * @param dist Um array de distâncias a ser inicializado.
     * @param arvMenrCamnh Um array da árvore do menor caminho a ser inicializado.
     * @param pai Um array de pais a ser inicializado.
     */
    for (int i = 0; i < V; i++)
    {
        dist[i] = 0;
        arvMenrCamnh[i] = 0;
        pai[i] = -1;
    }
}

void dijkstra(double grafo[V][V], int origem, int dest)
{
    /**
     * Executa o algoritmo de Dijkstra para encontrar o caminho mais confiável entre vértices em um grafo ponderado.
     *
     * Esta função utiliza o algoritmo de Dijkstra para encontrar o caminho mais confiável entre um vértice de origem (origem) e um vértice de destino (dest)
     * em um grafo ponderado representado por uma matriz de adjacência.
     * O caminho mais confiável é calculado considerando os pesos das arestas.
     *
     * @param grafo A matriz de adjacência representando o grafo ponderado.
     * @param origem O vértice de origem para iniciar o cálculo do caminho.
     * @param dest O vértice de destino para o qual o caminho mais confiável será calculado.
     */
    double *dist = malloc(V * sizeof(double));
    int *amcSet = malloc(V * sizeof(int)); // usada para setar a arvore de menor caminho (amc)
    int *pai = malloc(V * sizeof(int));

    iniclz_array(dist, amcSet, pai);

    dist[origem] = 1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = maior_chave(dist, amcSet);
        amcSet[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!amcSet[v] && grafo[u][v] && dist[u] != 0 && dist[u] * grafo[u][v] > dist[v])
            {
                pai[v] = u;
                dist[v] = dist[u] * grafo[u][v];
            }
        }
    }

    printf("Caminho mais confiavel: %d", origem);
    imprm_camnh(pai, dest);
    printf("\n");

    free(dist);
    free(amcSet);
    free(pai);
}

int main()
{
    double grafo[V][V] = {{0, 0.3, 0.1, 0},
                          {0.3, 0, 0.5, 0.9},
                          {0.1, 0.5, 0, 0.2},
                          {0, 0.9, 0.2, 0}};

    dijkstra(grafo, 2, 3);

    return 0;
}
