#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <windows.h>

#include "torre_hanoi.h"

#define N 4 // Número de discos

void imprime_configuracoes(int **configuracoes, int tamanho)
{
    /**
     * Imprime todas as possiveis configurações dos pinos.
     *
     * Esta função imprime as configurações dos pinos armazenadas em um array bidimensional.
     * Ela percorre as configurações e exibe os valores dos discos em cada configuração.
     *
     * @param configuracoes Um array bidimensional que representa as configurações dos pinos.
     * @param tamanho O número de configurações a serem impressas.
     */
    for (int i = 0; i < tamanho; i++)
    {
        printf("Configuracao %d: ", i + 1);
        for (int j = 0; j < N; j++)
        {
            printf("%d ", configuracoes[i][j]);
        }
        printf("\n");
    }
}

void para_base3(int num, int *arr)
{
    /**
     * Converte um número da base 10 para a base 3.
     *
     * Esta função converte um número da base 10 para a base 3, armazenando os dígitos da base 3 em um array fornecido.
     * Ela realiza a conversão dividindo repetidamente o número por 3 e armazenando os restos da divisão nos elementos do array.
     *
     * @param num O número na base 10 a ser convertido para a base 3.
     * @param arr Um array para armazenar os dígitos da base 3 resultantes da conversão.
     */
    for (int i = 0; i < N; i++)
    {
        arr[i] = num % 3;
        num /= 3;
    }
}

int mexeu(int **configuracoes, int i, int j)
{
    /**
     * Verifica se duas configurações de pinos diferem em apenas uma posição.
     *
     * Esta função verifica se duas configurações de pinos diferem em apenas uma posição.
     * Ela compara os discos nas posições correspondentes dos pinos das duas configurações e conta as diferenças.
     *
     * @param configuracoes Um array bidimensional que representa as configurações dos pinos.
     * @param i O índice da primeira configuração a ser comparada.
     * @param j O índice da segunda configuração a ser comparada.
     *
     * @return O número de posições diferentes entre as duas configurações.
     */
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
    /**
     * Encontra o índice do disco que foi movido entre duas configurações de pinos.
     *
     * Esta função encontra o índice do disco que foi movido entre duas configurações de pinos.
     * Ela compara as posições dos discos nas duas configurações e encontra o primeiro disco que difere entre elas.
     *
     * @param configuracoes Um array bidimensional que representa as configurações dos pinos.
     * @param i O índice da primeira configuração.
     * @param j O índice da segunda configuração.
     *
     * @return O índice do disco que foi movido entre as duas configurações.
     */
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


int **cria_matriz_adjacencia(int tamanho, int **configuracoes)
{
    /**
     * Cria a matriz de adjacência do grafo da Torre de Hanói com base nas configurações dos pinos.
     *
     * Esta função cria a matriz de adjacência para representar o grafo da Torre de Hanói.
     * A matriz é preenchida com valores inteiros, onde uma aresta entre duas configurações indica que um movimento válido pode ser feito entre elas.
     * As configurações são verificadas para movimentos válidos e uma aresta é criada se o movimento for válido.
     *
     * @param tamanho O tamanho da matriz de adjacência.
     * @param configuracoes Um array bidimensional que representa as configurações dos pinos.
     *
     * @return Um ponteiro para a matriz de adjacência recém-criada.
     */
    int **matriz_adjacencia = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++)
    {
        matriz_adjacencia[i] = calloc(tamanho, sizeof(int));
    }

    // Cria as arestas do grafo
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            int dif = mexeu(configuracoes, i, j);
            if (dif == 1)
            {
                int disco_movido = encontra_disc_movido(configuracoes, i, j);

                int eh_menor = mov_valido(disco_movido, configuracoes, i); 

                int eh_valido = mov_valido(disco_movido, configuracoes, j); 

                // Se o movimento é válido, cria uma aresta entre as duas configurações
                if (eh_menor && eh_valido)
                {
                    matriz_adjacencia[i][j] = 1;
                }
            }
        }
    }

    return matriz_adjacencia;
}

void imprime_menor_caminho_dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final)
{
    /**
     * Imprime o menor caminho entre duas configurações usando o Algoritmo de Dijkstra.
     *
     * Esta função utiliza o Algoritmo de Dijkstra para encontrar o menor caminho entre duas configurações
     * representadas por vetores de configurações iniciais e finais. Ela utiliza uma matriz de adjacência
     * que descreve as relações entre as configurações, onde as arestas indicam os movimentos válidos.
     * Após encontrar o menor caminho, imprime cada configuração do caminho em ordem.
     *
     * @param matriz_adjacencia Uma matriz de adjacência que descreve as relações entre as configurações.
     * @param config_inicial Um array que representa a configuração inicial dos pinos.
     * @param config_final Um array que representa a configuração final dos pinos.
     */
    int tamanho = pow(3, N);
    int *distancias = malloc(tamanho * sizeof(int));
    int *visitados = calloc(tamanho, sizeof(int));
    int *antecessores = malloc(tamanho * sizeof(int));

    for (int i = 0; i < tamanho; i++)
    {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
        antecessores[i] = -1;
    }


    int indice_inicial = 0;
    for (int i = 0; i < N; i++)
    {
        indice_inicial += config_inicial[i] * pow(3, i);
    }
    int indice_final = 0;
    for (int i = 0; i < N; i++)
    {
        indice_final += config_final[i] * pow(3, i);
    }

    // Define a distância da configuração inicial como 0
    distancias[indice_inicial] = 0;

    // Executa o Algoritmo de Dijkstra
    for (int i = 0; i < tamanho - 1; i++)
    {
        int u = -1;
        for (int j = 0; j < tamanho; j++)
        {
            if (!visitados[j] && (u == -1 || distancias[j] < distancias[u]))
            {
                u = j;
            }
        }

        visitados[u] = 1;

        for (int v = 0; v < tamanho; v++)
        {
            if (!visitados[v] && matriz_adjacencia[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz_adjacencia[u][v] < distancias[v])
            {
                distancias[v] = distancias[u] + matriz_adjacencia[u][v];
                antecessores[v] = u;
            }
        }
    }

    // Imprime o menor caminho
    if (antecessores[indice_final] == -1)
    {
        printf("Não existe caminho entre as configurações inicial e final.\n");
    }
    else
    {
        int *caminho = malloc(tamanho * sizeof(int));
        int tamanho_caminho = 0;
        int atual = indice_final;
        while (atual != -1)
        {
            caminho[tamanho_caminho++] = atual;
            atual = antecessores[atual];
        }
        for (int i = tamanho_caminho - 1; i >= 0; i--)
        {
            int *config = malloc(N * sizeof(int));
            int indice = caminho[i];
            for (int j = N - 1; j >= 0; j--)
            {
                config[j] = indice % 3;
                indice /= 3;
            }
            for (int j = 0; j < N; j++)
            {
                printf("%d ", config[j]);
            }
            printf("\n");
            free(config);
        }
    }

    free(distancias);
    free(visitados);
    free(antecessores);
}

int dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final)
{
    /**
     * Encontra o menor caminho entre duas configurações usando o Algoritmo de Dijkstra.
     *
     * Esta função utiliza o Algoritmo de Dijkstra para encontrar o menor caminho entre duas configurações
     * representadas por vetores de configurações iniciais e finais. Ela utiliza uma matriz de adjacência
     * que descreve as relações entre as configurações, onde as arestas indicam os movimentos válidos.
     *
     * @param matriz_adjacencia Uma matriz de adjacência que descreve as relações entre as configurações.
     * @param config_inicial Um array que representa a configuração inicial dos pinos.
     * @param config_final Um array que representa a configuração final dos pinos.
     *
     * @return A menor distância (caminho) entre as configurações inicial e final.
     */
    int tamanho = pow(3, N);
    int *distancias = malloc(tamanho * sizeof(int));
    int *visitados = calloc(tamanho, sizeof(int));

    for (int i = 0; i < tamanho; i++)
    {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    int indice_inicial = 0;
    for (int i = 0; i < N; i++)
    {
        indice_inicial += config_inicial[i] * pow(3, i);
    }

    // exemplo:
    // config_inicial = {1, 0, 2, 0}
    // indice_inicial = 1 * 3^0 + 0 * 3^1 + 2 * 3^2 + 0 * 3^0
    // indice_inicial = 1 + 0 + 18 + 0
    // indice_inicial = 19

    int indice_final = 0;
    for (int i = 0; i < N; i++)
    {
        indice_final += config_final[i] * pow(3, i);
    }

    distancias[indice_inicial] = 0;

    // Executa o Algoritmo de Dijkstra
    for (int i = 0; i < tamanho - 1; i++)
    {
        int min_distancia = INT_MAX;
        int u;
        for (int j = 0; j < tamanho; j++)
        {
            if (!visitados[j] && distancias[j] <= min_distancia)
            {
                min_distancia = distancias[j];
                u = j;
            }
        }

        visitados[u] = 1;

        for (int v = 0; v < tamanho; v++)
        {
            if (!visitados[v] && matriz_adjacencia[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz_adjacencia[u][v] < distancias[v])
            {
                distancias[v] = distancias[u] + matriz_adjacencia[u][v];
            }
        }
    }

    return distancias[indice_final];
}

double mede_tempo_dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final)
{
    /**
     * Mede o tempo gasto para encontrar a solução do desafio da Torre de Hanói usando o Algoritmo de Dijkstra.
     *
     * Esta função utiliza o Algoritmo de Dijkstra para encontrar o menor caminho entre duas configurações
     * representadas por vetores de configurações iniciais e finais. Ela utiliza uma matriz de adjacência
     * que descreve as relações entre as configurações, onde as arestas indicam os movimentos válidos.
     * Mede o tempo gasto para a execução do algoritmo em milissegundos.
     *
     * @param matriz_adjacencia Uma matriz de adjacência que descreve as relações entre as configurações.
     * @param config_inicial Um array que representa a configuração inicial dos pinos.
     * @param config_final Um array que representa a configuração final dos pinos.
     *
     * @return O tempo gasto para encontrar a solução em milissegundos.
     */
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

void imprime_menor_caminho_bellman_ford(int **matriz_adjacencia, int *config_inicial, int *config_final)
{
    /**
     * Imprime o menor caminho entre duas configurações usando o Algoritmo Bellman-Ford.
     *
     * Esta função utiliza o Algoritmo Bellman-Ford para encontrar o menor caminho entre duas configurações
     * representadas por vetores de configurações iniciais e finais. Ela utiliza uma matriz de adjacência
     * que descreve as relações entre as configurações, onde as arestas indicam os movimentos válidos.
     * Após encontrar o menor caminho, imprime cada configuração do caminho em ordem.
     *
     * @param matriz_adjacencia Uma matriz de adjacência que descreve as relações entre as configurações.
     * @param config_inicial Um array que representa a configuração inicial dos pinos.
     * @param config_final Um array que representa a configuração final dos pinos.
     */
    int tamanho = pow(3, N);
    int *distancias = malloc(tamanho * sizeof(int));

    for (int i = 0; i < tamanho; i++)
    {
        distancias[i] = INT_MAX;
    }

    int indice_inicial = 0;
    for (int i = 0; i < N; i++)
    {
        indice_inicial += config_inicial[i] * pow(3, i);
    }
    int indice_final = 0;
    for (int i = 0; i < N; i++)
    {
        indice_final += config_final[i] * pow(3, i);
    }

    distancias[indice_inicial] = 0;

    // Executa o Algoritmo Ford-Moore-Bellman
    for (int i = 1; i < tamanho; i++)
    {
        for (int u = 0; u < tamanho; u++)
        {
            for (int v = 0; v < tamanho; v++)
            {
                if (matriz_adjacencia[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz_adjacencia[u][v] < distancias[v])
                {
                    distancias[v] = distancias[u] + matriz_adjacencia[u][v];
                }
            }
        }
    }

    // Imprime o menor caminho
    if (distancias[indice_final] == INT_MAX)
    {
        printf("Não existe caminho entre as configurações inicial e final.\n");
    }
    else
    {
        int indice_atual = indice_final;
        int *caminho = malloc(tamanho * sizeof(int));
        int tamanho_caminho = 0;

        while (indice_atual != indice_inicial)
        {
            caminho[tamanho_caminho++] = indice_atual;
            for (int u = 0; u < tamanho; u++)
            {
                if (matriz_adjacencia[u][indice_atual] && distancias[u] + matriz_adjacencia[u][indice_atual] == distancias[indice_atual])
                {
                    indice_atual = u;
                    break;
                }
            }
        }
        caminho[tamanho_caminho++] = indice_inicial;

        for (int i = tamanho_caminho - 1; i >= 0; i--)
        {
            int indice = caminho[i];
            int *config = malloc(N * sizeof(int));
            for (int j = N - 1; j >= 0; j--)
            {
                config[j] = indice % 3;
                indice /= 3;
            }
            for (int j = 0; j < N; j++)
            {
                printf("%d ", config[j]);
            }
            printf("\n");
            free(config);
        }

        free(caminho);
    }

    free(distancias);
}

int bellman_ford(int **matriz_adjacencia, int *config_inicial, int *config_final)
{
    /**
     * Encontra o menor caminho entre duas configurações usando o Algoritmo Ford-Moore-Bellman.
     *
     * Esta função utiliza o Algoritmo Ford-Moore-Bellman para encontrar o menor caminho entre duas configurações
     * representadas por vetores de configurações iniciais e finais. Ela utiliza uma matriz de adjacência
     * que descreve as relações entre as configurações, onde as arestas indicam os movimentos válidos.
     * Retorna a menor distância entre as configurações iniciais e finais considerando o peso das arestas.
     *
     * @param matriz_adjacencia Uma matriz de adjacência que descreve as relações entre as configurações.
     * @param config_inicial Um array que representa a configuração inicial dos pinos.
     * @param config_final Um array que representa a configuração final dos pinos.
     *
     * @return A menor distância entre as configurações iniciais e finais.
     */
    int tamanho = pow(3, N);
    int *distancias = malloc(tamanho * sizeof(int));

    for (int i = 0; i < tamanho; i++)
    {
        distancias[i] = INT_MAX;
    }

    int indice_inicial = 0;
    for (int i = 0; i < N; i++)
    {
        indice_inicial += config_inicial[i] * pow(3, i);
    }

    int indice_final = 0;
    for (int i = 0; i < N; i++)
    {
        indice_final += config_final[i] * pow(3, i);
    }

    distancias[indice_inicial] = 0;

    // Executa o Algoritmo Ford-Moore-Bellman
    for (int i = 1; i < tamanho; i++)
    {
        for (int u = 0; u < tamanho; u++)
        {
            for (int v = 0; v < tamanho; v++)
            {
                if (matriz_adjacencia[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz_adjacencia[u][v] < distancias[v])
                {
                    distancias[v] = distancias[u] + matriz_adjacencia[u][v];
                }
            }
        }
    }

    return distancias[indice_final];
}

double mede_tempo_bellman_ford(int **matriz_adjacencia, int *config_inicial, int *config_final)
{
    /**
     * Mede o tempo gasto para executar o Algoritmo Ford-Moore-Bellman para encontrar o menor caminho entre duas configurações.
     *
     * Esta função utiliza o Algoritmo Ford-Moore-Bellman para encontrar o menor caminho entre duas configurações
     * representadas por vetores de configurações iniciais e finais. Além disso, mede o tempo gasto para executar o algoritmo
     * utilizando a função QueryPerformanceCounter para obter o tempo inicial e final, e a função QueryPerformanceFrequency
     * para obter a frequência do contador de performance. O tempo gasto é retornado em milissegundos.
     *
     * @param matriz_adjacencia Uma matriz de adjacência que descreve as relações entre as configurações.
     * @param config_inicial Um array que representa a configuração inicial dos pinos.
     * @param config_final Um array que representa a configuração final dos pinos.
     *
     * @return O tempo gasto em milissegundos para executar o Algoritmo Ford-Moore-Bellman.
     */
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

void imprimir_matriz_adjacencia(int **matriz, int tamanho)
{
    /**
     * Imprime uma matriz de adjacência.
     *
     * Esta função imprime os valores de uma matriz de adjacência fornecida como entrada. Ela percorre a matriz
     * linha por linha e imprime os elementos separados por espaço. Cada linha é seguida por uma quebra de linha.
     *
     * @param matriz A matriz de adjacência a ser impressa.
     * @param tamanho O tamanho da matriz (número de linhas e colunas).
     */
    if(matriz != NULL){
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = 0; j < tamanho; j++)
            {
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }
    }else printf("Matriz vazia.\n");
}

int validar_configuracoes(int *config_inicial, int *config_final)
{
    /**
     * Valida as configurações de pinos iniciais e finais.
     *
     * Esta função valida as configurações de pinos iniciais e finais, verificando se os valores estão dentro dos limites aceitáveis.
     * Ela compara cada valor nas configurações com os limites (0, 1 e 2) para determinar se são válidos.
     *
     * @param config_inicial Um array que representa a configuração inicial dos pinos.
     * @param config_final Um array que representa a configuração final dos pinos.
     *
     * @return 1 se as configurações forem válidas, 0 se houver valores inválidos.
     */
    int valida = 1;
    for (int i = 0; i < N; i++)
    {
        if (config_inicial[i] < 0 || config_inicial[i] > 2 ||
            config_final[i] < 0 || config_final[i] > 2)
        {
            valida = 0;
        }
    }

    return valida;
}
