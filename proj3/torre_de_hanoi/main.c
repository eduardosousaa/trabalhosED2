#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <windows.h>

#include "torre_hanoi.h"

#define N 4 // Número de discos

void menu()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Modelar grafo a partir de uma matriz de adjacencia\n");
    printf("2. Imprimir possiveis configuracoes da torre\n");
    printf("3. Encontrar menor caminho com Dijkstra\n");
    printf("4. Encontrar menor caminho com Ford-Moore-Bellman\n");
    printf("5. Medir tempo para encontrar o menor caminho com dijkstra\n");
    printf("6. Medir tempo para encontrar o menor caminho com Ford-Moore-Bellman\n");
    printf("7. Imprimir menor caminho com Dijkstra\n");
    printf("8. Imprimir menor caminho com Ford-Moore-Bellman\n");
    printf("9. Imprimir matriz de adjacencia\n");
    printf("0. Sair\n");
}

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
    int **matriz_adjacencia = NULL;
    int op, confirma = 0, indice_inicio = 0, indice_fim = 0;

    do
    {
        menu();
        scanf("%d", &op);
        printf("\n");

        switch (op)
        {
        case 1:
            matriz_adjacencia = cria_matriz_adjacencia(tamanho, configuracoes);
            if (matriz_adjacencia != NULL)
                printf("Matriz de adjacencia criada com sucesso!\n");
            else
                printf("Falha ao criar matriz de adjacencia.\n");
            break;
        case 2:
            imprime_configuracoes(configuracoes, tamanho);
            break;
        case 3:
            printf("=-=-=-= Encontrar menor caminho com Dijkstra =-=-=-=\n\n");
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
            if (matriz_adjacencia != NULL)
            {
                if (validar_configuracoes(inicio, fim))
                {
                    printf("\nMenor numero de movimentos: %d\n", dijkstra(matriz_adjacencia, inicio, fim));
                }
                else
                {
                    printf("\nErro: Valores inválidos nas configurações.\n");
                }
            }
            else
                printf("\nA matriz de adjacencia ainda nao foi criada.\n");
            break;
        case 4:
            printf("=-=-=-= Encontrar menor caminho com Ford-Moore-Bellman =-=-=-=\n\n");
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
            if (matriz_adjacencia != NULL)
            {
                if (validar_configuracoes(inicio, fim))
                {
                    printf("\nMenor numero de movimentos: %d\n", bellman_ford(matriz_adjacencia, inicio, fim));
                }
                else
                {
                    printf("\nErro: Valores inválidos nas configurações.\n");
                }
            }
            else
                printf("\nA matriz de adjacencia ainda nao foi criada.\n");
            break;
        case 5:
            printf("=-=-=-= Medir tempo para encontrar o menor caminho com Dijkstra =-=-=-=\n\n");
            if (matriz_adjacencia != NULL)
                printf("Tempo gasto: %f milissegundos\n", mede_tempo_dijkstra(matriz_adjacencia, config_inicial, config_final));
            else
                printf("A matriz de adjacencia ainda nao foi criada.\n");
            break;
        case 6:
            printf("=-=-=-= Medir tempo para encontrar o menor caminho com Ford-Moore-Bellman =-=-=-=\n\n");
            if (matriz_adjacencia != NULL)
                printf("Tempo gasto: %f milissegundos\n", mede_tempo_bellman_ford(matriz_adjacencia, config_inicial, config_final));
            else
                printf("A matriz de adjacencia ainda nao foi criada.\n");
            break;
        case 7:
            if(matriz_adjacencia != NULL){
                printf("Configuracoes dos discos no menor caminho: \n");
                imprime_menor_caminho_dijkstra(matriz_adjacencia, config_inicial, config_final);
            }else
                printf("A matriz de adjacencia ainda nao foi criada.\n");
            break;
        case 8:
            if(matriz_adjacencia != NULL){
                printf("Configuracoes dos discos no menor caminho: \n");
                imprime_menor_caminho_bellman_ford(matriz_adjacencia, config_inicial, config_final);
            }else
                printf("A matriz de adjacencia ainda nao foi criada.\n");
            break;
        case 9:
            if (matriz_adjacencia != NULL)
                imprimir_matriz_adjacencia(matriz_adjacencia, tamanho);
            else
                printf("A matriz de adjacencia ainda nao foi criada.\n");
            break;
        case 0:
            printf("Programa finalizado.\n");
            break;
        default:
            printf("Opção inválida. Escolha novamente.\n");
        }
    } while (op != 0);

    return 0;
}