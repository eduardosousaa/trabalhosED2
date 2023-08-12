// Suponha um grafo orientado G = (V,E) no qual cada aresta (u,v) "pertence a" E tem um valor associado r(u,v), o 
// qual  é  um  número  real  no  intervalo 0<=r(u,v)<=1  que  representa  a  confiabilidade  de  um  canal  de 
// comunicação do vértice u até o vértice v. Interpretamos r(u,v) como a probabilidade de que o canal de u 
// até  v  não  venha  a  falhar,  e  supomos  que  essas  probabilidades  são  independentes.  Faça  um  programa 
// eficiente para encontrar o caminho mais confiável entre dois vértices dados.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VG 4 // número de vértices no grafo

int maxKey(double key[], bool mstSet[], int V) {
    /**
     * Encontra o vértice não incluído na MST com a maior chave (peso).
     *
     * Esta função encontra o vértice que ainda não foi incluído na árvore geradora mínima (MST)
     * e possui a maior chave (peso) entre os vértices não incluídos.
     *
     * @param key Um array que armazena as chaves (pesos) dos vértices.
     * @param mstSet Um array booleano que indica se um vértice está incluído na MST.
     * @param V O número de vértices no grafo.
     *
     * @return O índice do vértice com a maior chave (peso) entre os vértices não incluídos na MST.
     */
    double max = 0;
    int max_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] > max)
            max = key[v], max_index = v;

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

void imprm_MST(int parent[], double **graph, int V) {
    /**
     * Imprime a árvore geradora mínima (MST) encontrada pelo algoritmo de Prim.
     *
     * Esta função imprime a árvore geradora mínima (MST) encontrada pelo algoritmo de Prim.
     * Ela exibe cada aresta da MST junto com seu peso.
     *
     * @param parent Um array que armazena os pais de cada vértice na MST.
     * @param graph A matriz de adjacência representando o grafo ponderado.
     * @param V O número de vértices no grafo.
     */
    printf("Aresta \tPeso\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%lf \n", parent[i], i, graph[i][parent[i]]);
}

void primMST(double graph[VG][VG], int V, int src, int dest) {
    /**
     * Executa o algoritmo Prim para encontrar a árvore geradora mínima (MST) em um grafo ponderado.
     *
     * Esta função utiliza o algoritmo de Prim para encontrar a MST em um grafo representado por uma matriz de adjacência.
     * O vértice de origem (src) é especificado para iniciar a construção da MST.
     * O vértice de destino (dest) é usado para imprimir o caminho mais confiável da origem ao destino.
     *
     * @param graph A matriz de adjacência representando o grafo ponderado.
     * @param V O número de vértices no grafo.
     * @param src O vértice de origem para iniciar a construção da MST.
     * @param dest O vértice de destino para imprimir o caminho mais confiável da origem ao destino.
     */
    int *parent = malloc(V * sizeof(int));
    double *key = malloc(V * sizeof(double));
    bool *mstSet = malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++){
        key[i] = 0;
        mstSet[i] = false;
    }

    key[src] = 1;
    parent[src] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = maxKey(key, mstSet, V);
        printf("u = %d\n", u);
        mstSet[u] = true;

        for (int v = 0; v < V; v++){
            if (graph[u][v] && mstSet[v] == false && graph[u][v] > key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
                printf("Pai: %d\n", parent[v]);
                printf("key: %f\n", key[v]);
            }
        }
    }

    printf("Caminho mais confiavel: %d", src);
    imprm_camnh(parent, dest);
    printf("\n");
    free(parent);
    free(key);
    free(mstSet);
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

        primMST(graph, VG, src, dest);
    }

    return 0;
}