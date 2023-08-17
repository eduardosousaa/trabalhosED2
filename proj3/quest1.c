#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <windows.h>

#define N 4 // Número de discos

void imprime_configuracoes(int **configuracoes, int tamanho)
{
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

// Função para converter um número na base 10 para a base 3
void para_base3(int num, int *arr)
{
    for (int i = 0; i < N; i++)
    {
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
int **cria_matriz_adjacencia(int tamanho, int **configuracoes, int *criou)
{
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
            int diff = mexeu(configuracoes, i, j);
            // Se diferem em apenas uma posição, verifica se o movimento é válido
            if (diff == 1)
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

// Função para encontrar o menor caminho entre duas configurações usando o Algoritmo de Dijkstra
int dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final)
{
    int tamanho = pow(3, N);
    int *distancias = malloc(tamanho * sizeof(int));
    int *visitados = calloc(tamanho, sizeof(int));

    // Inicializa as distâncias com infinito e os visitados com 0
    for (int i = 0; i < tamanho; i++)
    {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    // Converte a configuração inicial para um índice na matriz de adjacência
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

    // Converte a configuração final para um índice na matriz de adjacência
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
        // Encontra o vértice com a menor distância que ainda não foi visitado
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

        // Marca o vértice como visitado
        visitados[u] = 1;

        // Atualiza as distâncias dos vértices adjacentes
        for (int v = 0; v < tamanho; v++)
        {
            if (!visitados[v] && matriz_adjacencia[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz_adjacencia[u][v] < distancias[v])
            {
                distancias[v] = distancias[u] + matriz_adjacencia[u][v];
            }
        }
    }

    // Retorna a menor distância entre a configuração inicial e a configuração final
    return distancias[indice_final];
}

// Função para medir o tempo gasto para encontrar a solução do desafio da Torre de Hanói
double mede_tempo(int **matriz_adjacencia, int *config_inicial, int *config_final)
{
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

// Função para imprimir uma matriz de adjacência
void imprimir_matriz_adjacencia(int **matriz, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int validar_configuracoes(int *config_inicial, int *config_final)
{
    // Verifica se os valores das configurações estão dentro dos limites aceitáveis
    for (int i = 0; i < N; i++)
    {
        if (config_inicial[i] < 0 || config_inicial[i] > 2 ||
            config_final[i] < 0 || config_final[i] > 2)
        {
            printf("Erro: Valores inválidos nas configurações.\n");
            return 0;
        }
    }

    return 1; // Configurações válidas
}



void menu()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Modelar grafo a partir de uma matriz de adjacencia\n");
    printf("2. Imprimir possiveis configuracoes da torre\n");
    printf("3. Encontrar menor caminho\n");
    printf("4. Medir tempo para encontrar o menor caminho\n");
    printf("5. Imprimir matriz de adjacencia\n");
    printf("0. Sair\n");
}

// Exemplo de uso das funções cria_matriz_adjacencia, dijkstra e mede_tempo para resolver o desafio da Torre de Hanói para o caso de 4 discos
int main()
{
    // Aloca memória para a matriz de adjacência
    int tamanho = pow(3, N);

    // Aloca memória para a lista de configurações
    int **configuracoes = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++)
    {
        configuracoes[i] = malloc(N * sizeof(int));
        para_base3(i, configuracoes[i]);
    }

    // int **matriz_adjacencia = cria_matriz_adjacencia(tamanho, configuracoes);

    // int config_inicial[N] = {0, 0, 0, 0};
    // int config_final[N] = {2, 2, 2, 2};

    // imprime_configuracoes(configuracoes, tamanho);

    // printf("Menor numero de movimentos: %d\n", dijkstra(matriz_adjacencia, config_inicial, config_final));
    // printf("Tempo gasto: %f milissegundos\n", mede_tempo(matriz_adjacencia, config_inicial, config_final));

    int inicio[N], fim[N];
    int config_inicial[N] = {0, 0, 0, 0};
    int config_final[N] = {2, 2, 2, 2};
    int **matriz_adjacencia;
    int op, confirma = 0, indice_inicio = 0, indice_fim = 0;

    do
    {
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            matriz_adjacencia = cria_matriz_adjacencia(tamanho, configuracoes, &confirma);
            break;
        case 2:
            imprime_configuracoes(configuracoes, tamanho);
            break;
        case 3:
            printf("Exemplos de configuracoes: \nTodos os discos no primeiro pino: 0 0 0 0 \n");
            printf("Todos os discos no ultimo pino: 2 2 2 2\n\n");
            printf("Insira os valores das configurações inicial e final (4 valores separados por espaço):\n");
            printf("Configuracao inicial: ");
            for (int i = 0; i < N; i++)
            {
                scanf("%d", &inicio[i]);
            }
            printf("Configuracao final: ");
            for (int i = 0; i < N; i++)
            {
                scanf("%d", &fim[i]);
            }
            if(validar_configuracoes(inicio, fim)){
                printf("Menor numero de movimentos: %d\n", dijkstra(matriz_adjacencia, inicio, fim));
            }else{
                printf("Configuracoes invalidas!\n");
            }
            break;
        case 4:
            printf("Tempo gasto: %f milissegundos\n", mede_tempo(matriz_adjacencia, config_inicial, config_final));
            break;
        case 5:
            imprimir_matriz_adjacencia(matriz_adjacencia, tamanho);
            break;
        case 0:
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opção inválida. Escolha novamente.\n");
        }
    } while (op != 0);

    return 0;
}
