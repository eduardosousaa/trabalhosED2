#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> //usado para transformar as letras da palavra em minusculas

#include "rubro_negra.h"

int main() {
    srand(time(NULL));

    ArvRubroNegra *arvore, *No;
    arvore = NULL;
    No = NULL;

    const char *arquivo = "texto.txt";

    int op = -1, construiu = 0, achou = 0, confirma = 0, linha, contador = 0;
    char palavra[20];

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
                contador = 0;
                printf("Digite a palavra que deseja buscar: ");
                scanf("%s", palavra);
                for(int i=0; palavra[i] != '\0'; i++) {
                    palavra[i] = tolower(palavra[i]);
                }
                achou = buscrPalvr(arvore, palavra, &No, &contador);
                if(achou == 1){
                    printf("A palavra '%s' esta presente nas seguintes linhas: ");
                    imprmrLinhs(No->info->num_lista, 0);
                    printf("\n");
                }else if(achou == 0){
                    printf("A palavra '%s' nao foi encontrada!\n");
                }
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