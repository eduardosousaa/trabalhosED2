#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> //usado para transformar as letras da palavra em minusculas
#include <windows.h>

#include "rubro_negra.h"

int main() {
    srand(time(NULL));

    ArvRubroNegra *arvore = NULL, *No = NULL;
    const char *arquivo = "palavras.txt";

    int op = -1, construiu = 0, achou = 0, confirma = 0, linha, contador = 0;
    char palavra[20];

    LARGE_INTEGER inicio, fim, frequencia;

    // CÓDIGO DE MEDIR TEMPO PARA LINUX 
    // clock_t inicio, fim;
    // double tempo_decorrido;

    while(op!=0){
        printf("\n");
        printf("0 - Encerrar\n"
        "1 - Construir arvore a partir de um arquivo texto\n"
        "2 - Imprimir arvore em ordem\n"
        "3 - Buscar palavra\n"
        "4 - Adicionar palavra\n"
        "5 - Excluir palavra\n"
        "Digite a opcao: ");
        scanf("%d", &op);
        switch (op){
            case 0:
                printf("Programa encerrado!\n");
                break;
            case 1: 
                construiu = lerArquivoTexto(&arvore, arquivo);
                if(construiu == 1){
                    printf("Arvore a partir do arquivo %s criada com sucesso!\n", arquivo);
                }else{
                    printf("Falha ao criar arvore a partir do arquivo %s!\n", arquivo);
                }
                break;
            case 2:
                imprmrInOrdem(arvore, 0);
                break;
            case 3:
                printf("Digite a palavra que deseja buscar: ");
                scanf("%s", palavra);
                contador = 0;
                for(int i=0; palavra[i] != '\0'; i++) {
                    palavra[i] = tolower(palavra[i]);
                }

                // Obtém a frequência do contador de performance
                QueryPerformanceFrequency(&frequencia); 

                // Obtém o tempo inicial
                // inicio = clock();
                QueryPerformanceCounter(&inicio);

                achou = buscrPalvr(arvore, palavra, &No, &contador);

                // Obtém o tempo final
                // fim = clock(); // marca o fim da seção de código
                QueryPerformanceCounter(&fim);

                // Calcula o tempo total em milissegundos
                // tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
                double tempo_busca = (double)(fim.QuadPart - inicio.QuadPart) * 1000 / frequencia.QuadPart;

                if(achou == 1){
                    // printf("A palavra '%s' esta presente nas seguintes linhas: ");
                    // imprmrLinhs(No->info->num_lista, 0);
                    // printf("\n");
                }else if(achou == 0){
                    printf("A palavra '%s' nao foi encontrada!\n");
                }

                // Exibe o tempo médio de preenchimento da árvore
                // printf("Tempo decorrido: %.2f segundos\n", tempo_decorrido);
                printf("Tempo medio: %.5f milissegundos\n", tempo_busca);
                printf("Para achar a palavra foram percorridos %d Nos\n", contador);
                
                break;
            case 4:
                printf("Digite a palavra que deseja adicionar: ");
                scanf("%s", palavra);
                printf("Digite em que linha deseja acrescentar a palavra: ");
                scanf("%d", &linha);
                confirma = inserirRubro(&arvore, palavra, linha);
                if(confirma == 0){
                    printf("Falha ao inserir palavra na arvore!\n");
                }else if(confirma == 1){
                    printf("A palavra '%s' foi inserida com sucesso na arvore!\n", palavra);
                }else if(confirma == 2){
                    printf("A palavra '%s' ja existe na arvore e apenas o numero da linha foi atualizado!\n", palavra);
                }
                break;
            case 5: 
                printf("Digite a palavra que deseja excluir: ");
                scanf("%s", palavra);
                for(int i=0; palavra[i] != '\0'; i++) {
                    palavra[i] = tolower(palavra[i]);
                }
                confirma = remvPalvr(&arvore, palavra);
                if(confirma == 0){
                    printf("Falha ao remover palavra na arvore!\n");
                }else if(confirma == 1){
                    printf("A palavra '%s' foi removida com sucesso na arvore!\n", palavra);
                }
                break;
            default:
                printf("Essa opcao nao existe\n");
                break;
        }
    }

    return 0;
}