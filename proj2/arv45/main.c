#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
// #include <windows.h>

#include "arv45.h"

int main() {
    Arv45 *raiz;
    raiz = NULL;

    Info *sobe, *aux;
    aux = NULL;

    char resultado[100], tipo[100], marca[100];

    int op = -1, cod, qtd, tam, contador=0;
    float preco;

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
                printf("\nListagem dos calcados disponiveis:\n");
                mostrarInfos(raiz, 0);
                break;

            case 2:
                contador = 0;

                if (raiz != NULL) {
                    printf("Digite o codigo do calcado: ");
                    scanf("%d", &cod);

                    aux = buscarProduto(raiz, cod, &contador);

                    if (aux != NULL) {
                        printf("\nCalcado encontrado: ");
                        imprimirInfo(aux);
                    } else {
                        printf("\nCalcado nao encontrado! ");
                    }

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
