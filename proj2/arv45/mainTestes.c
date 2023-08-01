#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#include "arv45.h"

int main() {
    Arv45 *raiz;
    raiz = NULL;

    Info *sobe, *aux;
    aux = NULL;

    char resultado[100], tipo[100], marca[100];

    int op = -1, cod, qtd, tam, contador=0;
    float preco;

    LARGE_INTEGER inicio, fim, frequencia;

    // CÓDIGO DE MEDIR TEMPO PARA LINUX 
    // clock_t inicio, fim;
    // double tempo_decorrido;

    // Leitura do arquivo txt
    lerArquivo(&raiz, &sobe);

    while (op != 0) {
        printf("\n");
        printf("0 - Encerrar\n"
               "1 - Imprimir arvore em ordem\n"
               "2 - Buscar calcado\n"
               "3 - Comprar calcado\n"
               "4 - Adicionar calcado\n"
               "Digite a opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 0:
                printf("\nPrograma encerrado!\n");
                break;

            case 1:
                printf("Listagem dos calcados disponiveis:\n");
                mostrarInfos(raiz, 0);
                break;

            case 2:
                contador = 0;

                if (raiz != NULL) {
                    printf("Digite o codigo do calcado: ");
                    scanf("%d", &cod);

                    // Obtém a frequência do contador de performance
                    QueryPerformanceFrequency(&frequencia); 

                    // Obtém o tempo inicial
                    // inicio = clock();
                    QueryPerformanceCounter(&inicio);

                    aux = buscarProduto(raiz, cod, &contador);

                    // Obtém o tempo final
                    // fim = clock(); // marca o fim da seção de código
                    QueryPerformanceCounter(&fim);

                    // Calcula o tempo total em milissegundos
                    // tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
                    double tempo_busca = (double)(fim.QuadPart - inicio.QuadPart) * 1000 / frequencia.QuadPart;

                    if (aux != NULL) {
                        printf("\nCalcado encontrado: ");
                        imprimirInfo(aux);
                    } else {
                        printf("\nCalcado nao encontrado: ");
                    }

                    // Exibe o tempo médio de preenchimento da árvore
                    // printf("Tempo decorrido: %.2f segundos\n", tempo_decorrido);
                    printf("Tempo medio: %.5f milissegundos\n", tempo_busca);
                    printf("Para achar a palavra foram percorridos %d Nos\n", contador);

                } else {
                    printf("Arvore vazia.\n");
                }

                break;

            case 3:
                if (raiz != NULL) {
                    printf("Lista de calcados disponiveis:\n");
                    mostrarInfos(raiz, 0);

                    printf("\nDigite o codigo do calcado: ");
                    scanf("%d", &cod);
                    printf("\nDigite a quantidade de calcados: ");
                    scanf("%d", &qtd);

                    vender(raiz, qtd, cod, resultado);
                    printf("%s", resultado);
                } else {
                    printf("Arvore vazia.\n");
                }
                break;

            case 4:

                if (raiz != NULL) {
                    printf("\nDigite o codigo do produto: ");
                    scanf("%d", &cod);
                    printf("Digite o tamanho do produto: ");
                    scanf("%d", &tam);
                    printf("Digite a quantidade do produto: ");
                    scanf("%d", &qtd);
                    printf("Digite o tipo do produto: ");
                    scanf("%s", tipo);
                    printf("Digite a marca do produto: ");
                    scanf("%s", marca);
                    printf("Digite o preco do produto: ");
                    scanf("%f", &preco);

                    adicionarCalcados(&raiz, &sobe, cod, tam, qtd, tipo, marca, preco, resultado);
                    printf("%s", resultado);
                } else {
                    printf("Arvore vazia.\n");
                }
                break;
        }
    }
    return 0;
}
