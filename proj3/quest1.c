#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <windows.h>

#define N 4 // Número de discos

// para_base3: Esta função converte um número na base 10 para a base 3. Ela recebe como parâmetros um número 
// inteiro num e um ponteiro para um array de inteiros arr. A função armazena a representação do número num na 
// base 3 no array arr.

// A conversão de um número na base 10 para a base 3 é necessária para representar as configurações dos discos 
// nos pinos do desafio da Torre de Hanói. Cada configuração pode ser representada por um vetor com tantas posições 
// quantas forem os discos. Na posição do disco será marcado o pino onde o disco está assentado. Como existem 3 pinos, 
// cada posição do vetor pode ter um valor entre 0 e 2, representando os pinos 0, 1 e 2.

// Ao converter um número na base 10 para a base 3, obtemos uma representação desse número como uma sequência de 
// dígitos na base 3. Essa sequência de dígitos pode ser usada para representar uma configuração dos discos nos 
// pinos. Por exemplo, se temos 4 discos, o número 0 na base 10 pode ser convertido para a base 3 como 0000, 
// representando a configuração em que todos os discos estão no pino 0. O número 80 na base 10 pode ser convertido 
// para a base 3 como 2222, representando a configuração em que todos os discos estão no pino 2.

// A conversão de números na base 10 para a base 3 permite criar uma correspondência entre os números inteiros e as 
// configurações dos discos nos pinos. Isso é útil para criar a matriz de adjacência do grafo que representa os 
// movimentos possíveis dos discos no desafio da Torre de Hanói. Cada configuração pode ser associada a um índice na 
// matriz de adjacência usando sua representação na base 3. Isso permite verificar facilmente se duas configurações 
// são adjacentes no grafo (ou seja, se é possível mover um disco de uma configuração para outra) e encontrar o menor 
// caminho entre duas configurações usando algoritmos de busca em grafos, como o Algoritmo de Dijkstra.



// cria_matriz_adjacencia: Esta função cria a matriz de adjacência do grafo que representa os movimentos 
// possíveis dos discos no desafio da Torre de Hanói para o caso de 4 discos. A função não recebe nenhum 
// parâmetro e retorna um ponteiro para a matriz de adjacência criada.

// dijkstra: Esta função encontra o menor caminho entre duas configurações de discos nos pinos usando o 
// Algoritmo de Dijkstra. A função recebe como parâmetros a matriz de adjacência do grafo, um ponteiro para 
// a configuração inicial dos discos nos pinos (config_inicial) e um ponteiro para a configuração final dos 
// discos nos pinos (config_final). A função retorna o menor número de movimentos necessários para chegar da 
// configuração inicial à configuração final.

// mede_tempo: Esta função mede o tempo gasto para encontrar a solução do desafio da Torre de Hanói 
// usando o Algoritmo de Dijkstra. A função recebe como parâmetros a matriz de adjacência do grafo, um ponteiro 
// para a configuração inicial dos discos nos pinos (config_inicial) e um ponteiro para a configuração final dos 
// discos nos pinos (config_final). A função retorna o tempo gasto em milissegundos para encontrar o menor caminho 
// entre essas duas configurações usando o Algoritmo de Dijkstra.



void imprime_configuracoes(int **configuracoes, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Configuracao %d: ", i+1);
        for (int j = 0; j < N; j++) {
            printf("%d ", configuracoes[i][j]);
        }
        printf("\n");
    }
}


// Função para converter um número na base 10 para a base 3
void para_base3(int num, int *arr) {
    for (int i = 0; i < N; i++) {
        arr[i] = num % 3;
        num /= 3;
    }
}

int mexeu(int **configuracoes, int i, int j)
{
    // Verifica se as duas configurações diferem em apenas uma posição
    int diff = 0;
    for (int k = 0; k < N; k++)
    {
        if (configuracoes[i][k] != configuracoes[j][k])
        {
            diff++;
        }
    }
    return diff;
}

int encontra_disc_movido(int **configuracoes, int i, int j)
{
    // Encontra o disco que foi movido
    int disco_movido;
    for (int k = 0; k < N; k++)
    {
        if (configuracoes[i][k] != configuracoes[j][k])
        {
            disco_movido = k;
            break;
        }
    }
    return disco_movido;
}

int ehMenor(int disco_movido, int **configuracoes, int i)
{
    /**
     * Verifica se um disco movido é o menor disco em relação à configuração atual.
     *
     * Esta função verifica se o disco movido é o menor disco no pino de origem em relação à configuração atual.
     * Ela percorre os discos no pino de origem e compara com o disco movido para determinar se é o menor.
     *
     * @param disco_movido O índice do disco que foi movido.
     * @param configuracoes Um array bidimensional que representa as configurações dos pinos.
     * @param i O índice da configuração atual a ser verificada.
     *
     * @return 1 se o disco movido for o menor na configuração atual, 0 caso contrário.
     */
    int eh_menor = 1;
    for (int k = 0; k < N; k++)
    {
        if (configuracoes[i][k] == configuracoes[i][disco_movido] && k < disco_movido)
        {
            eh_menor = 0;
            break;
        }
    }
    return eh_menor;
}

int mov_valido(int disco_movido, int **configuracoes, int j)
{
    /**
     * Verifica se um movimento é válido, considerando o disco movido e a configuração de destino.
     *
     * Esta função verifica se um movimento é válido, considerando se o disco movido foi colocado em
     * cima de um disco maior ou na base de um pino em relação à configuração de destino.
     *
     * @param disco_movido O índice do disco que foi movido.
     * @param configuracoes Um array bidimensional que representa as configurações dos pinos.
     * @param j O índice da configuração de destino a ser verificada.
     *
     * @return 1 se o movimento for válido, 0 caso contrário.
     */
    int eh_valido = 1;
    for (int k = 0; k < N; k++)
    {
        if (configuracoes[j][k] == configuracoes[j][disco_movido] && k < disco_movido)
        {
            eh_valido = 0;
            break;
        }
    }
    return eh_valido;
}

// Função para criar a matriz de adjacência do grafo da Torre de Hanói
int **cria_matriz_adjacencia()
{
    // Aloca memória para a matriz de adjacência
    int tamanho = pow(3, N);
    int **matriz_adjacencia = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++)
    {
        matriz_adjacencia[i] = calloc(tamanho, sizeof(int));
    }

    // Aloca memória para a lista de configurações
    int **configuracoes = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++)
    {
        configuracoes[i] = malloc(N * sizeof(int));
        para_base3(i, configuracoes[i]);
    }

    // Cria as arestas do grafo
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            int diff = mexeu(configuracoes, i, j);
            // Se diferem em apenas uma posição, verifica se o movimento é válido
            if (diff == 1)
            {
                int disco_movido = encontra_disc_movido(configuracoes, i, j);

                int eh_menor = ehMenor(disco_movido, configuracoes, i);

                int eh_valido = mov_valido(disco_movido, configuracoes, j);

                // Se o movimento é válido, cria uma aresta entre as duas configurações
                if (eh_menor && eh_valido)
                {
                    matriz_adjacencia[i][j] = 1;
                }
            }
        }
    }

    imprime_configuracoes(configuracoes, tamanho);

    return matriz_adjacencia;
}

// Função para encontrar o menor caminho entre duas configurações usando o Algoritmo de Dijkstra
int dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final) {
    int tamanho = pow(3, N);
    int *distancias = malloc(tamanho * sizeof(int));
    int *visitados = calloc(tamanho, sizeof(int));

    // Inicializa as distâncias com infinito e os visitados com 0
    for (int i = 0; i < tamanho; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    // Converte a configuração inicial para um índice na matriz de adjacência
    int indice_inicial = 0;
    for (int i = 0; i < N; i++) {
        indice_inicial += config_inicial[i] * pow(3, i);
    }

    // exemplo:
    // config_inicial = {1, 0, 2, 0}
    // indice_inicial = 1 * 3^0 + 0 * 3^1 + 2 * 3^2 + 0 * 3^0
    // indice_inicial = 1 + 0 + 18 + 0
    // indice_inicial = 19


    // Converte a configuração final para um índice na matriz de adjacência
    int indice_final = 0;
    for (int i = 0; i < N; i++) {
        indice_final += config_final[i] * pow(3, i);
    }

    // Define a distância da configuração inicial como 0
    distancias[indice_inicial] = 0;

    // Executa o Algoritmo de Dijkstra
    for (int i = 0; i < tamanho - 1; i++) {
        // Encontra o vértice com a menor distância que ainda não foi visitado
        int min_distancia = INT_MAX;
        int u;
        for (int j = 0; j < tamanho; j++) {
            if (!visitados[j] && distancias[j] <= min_distancia) {
                min_distancia = distancias[j];
                u = j;
            }
        }

        // Marca o vértice como visitado
        visitados[u] = 1;

        // Atualiza as distâncias dos vértices adjacentes
        for (int v = 0; v < tamanho; v++) {
            if (!visitados[v] && matriz_adjacencia[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz_adjacencia[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + matriz_adjacencia[u][v];
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

    dijkstra(matriz_adjacencia, config_inicial, config_final);

    // Obtém o tempo final
    QueryPerformanceCounter(&fim);

    // Calcula o tempo total em milissegundos
    double tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) * 1000 / frequencia.QuadPart;

    return tempo_gasto;
}

// Exemplo de uso das funções cria_matriz_adjacencia, dijkstra e mede_tempo para resolver o desafio da Torre de Hanói para o caso de 4 discos
int main() {
    int **matriz_adjacencia = cria_matriz_adjacencia();

    int config_inicial[N] = {0, 0, 0, 0};
    int config_final[N] = {2, 2, 2, 2};

    printf("Menor numero de movimentos: %d\n", dijkstra(matriz_adjacencia, config_inicial, config_final));
    printf("Tempo gasto: %f milissegundos\n", mede_tempo(matriz_adjacencia, config_inicial, config_final));

    return 0;
}
