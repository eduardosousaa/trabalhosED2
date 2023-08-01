#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> //usado para transformar as letras da palavra em minusculas
// #include <windows.h>

#include "arv23.h"


Info *criaInfo(char *palavra, Lista *lista, int num_linha){
    /**
     * Cria uma nova informação (Info) com uma palavra e lista de números de linha.
     *
     * Esta função aloca memória para uma nova estrutura de informação (Info) e inicializa seus campos.
     * A estrutura Info conterá uma palavra representada por uma string e uma lista de números de linha em que a palavra aparece.
     * Se a lista passada como parâmetro for nula (lista == NULL), a função criará uma nova lista encadeada e inserirá o número de linha.
     * Caso contrário, a lista fornecida será atribuída diretamente ao campo num_lista da estrutura Info.
     *
     * @param palavra A string que representa a palavra a ser armazenada na estrutura Info.
     * @param lista Um ponteiro para uma lista encadeada que contém números de linha em que a palavra aparece.
     * @param num_linha O número da linha a ser inserido na lista, caso a lista seja nula.
     *
     * @return Um ponteiro para a nova estrutura Info criada.
     */
    //Aloca memória para info
    Info *info;
    info = (Info*) malloc (sizeof(Info));

    info->palavra = (char*) malloc ((strlen(palavra) + 1) * sizeof(char));
    strcpy(info->palavra, palavra);

    if (lista == NULL){
        info->num_lista = NULL;
        inserirLinha(&(info->num_lista), num_linha);
    } else {
        info->num_lista = lista;
    }
    return info;
}

Arv23 *criaNo(Info *info, Arv23 *noEsq, Arv23 *noCentro, Arv23 *noDir){
    /**
     * Cria um novo nó para a árvore 2-3.
     *
     * Esta função aloca memória para um novo nó da árvore 2-3 e inicializa seus campos.
     * O novo nó terá uma única informação, apontada pelo ponteiro "info".
     *
     * @param info Um ponteiro para a informação que será armazenada no novo nó.
     * @param noEsq Um ponteiro para o nó filho esquerdo do novo nó.
     * @param noCentro Um ponteiro para o nó filho central do novo nó.
     * @param noDir Um ponteiro para o nó filho direito do novo nó.
     *
     * @return Um ponteiro para o novo nó criado.
     */

    Arv23 *new = (Arv23*) malloc (sizeof(Arv23));

    new->info1 = info;
    new->numInfo = 1;

    new->esq = noEsq;
    new->centro = noCentro;
    new->dir = NULL;

    return new;
}


void adicionaNo(Arv23 **raiz, Info *info, Arv23 *novo){
    /**
     * Adiciona uma nova informação a um nó da árvore 2-3.
     *
     * Esta função adiciona uma nova informação a um nó da árvore 2-3 e atualiza seus ponteiros de filhos.
     * A função verifica a ordem lexicográfica entre a nova informação e a informação existente no nó para
     * determinar a posição correta de inserção e atualizar os ponteiros de filhos do nó.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore 2-3.
     * @param info Um ponteiro para a nova informação a ser adicionada no nó.
     * @param novo Um ponteiro para o nó que será o filho direito do nó após a inserção.
     */

    if (strcmp(info->palavra, (*raiz)->info1->palavra) > 0){
        (*raiz)->info2 = info;
        (*raiz)->dir = novo;
    } else {
        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->info1 = info;

        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = novo;
    }
    (*raiz)->numInfo = 2;
}

int ehFolha(Arv23 *raiz) {
    /**
     * Verifica se um nó é uma folha na árvore 2-3.
     *
     * Esta função verifica se um nó específico da árvore 2-3 é uma folha, ou seja, se ele não possui filhos.
     *
     * @param raiz Um ponteiro para o nó que será verificado.
     *
     * @return Um valor inteiro que indica se o nó é uma folha ou não:
     *         - 0: O nó não é uma folha, pois possui pelo menos um filho.
     *         - 1: O nó é uma folha, pois não possui filhos.
     */
    int verifica = 0;

    if (raiz->esq == NULL){
        verifica = 1;
    }
    return verifica;
}

void inserirLinha(Lista **no, int num_linha){
    /**
     * Insere um número de linha em uma lista encadeada.
     *
     * Esta função insere um número de linha em uma lista encadeada, representada por um ponteiro para o ponteiro
     * da lista encadeada. Se a lista estiver vazia (ponteiro para a lista for NULL), a função criará um novo nó
     * para armazenar o número de linha. Caso contrário, a função chamará recursivamente a si mesma para inserir
     * o número de linha no próximo nó da lista.
     *
     * @param no Um ponteiro para o ponteiro da lista encadeada.
     * @param num_linha O número da linha a ser inserido na lista.
     */

    if (*no == NULL){
        *no = (Lista*) malloc (sizeof(Lista));

        if (*no != NULL){
            (*no)->num_linha = num_linha;
            (*no)->prox = NULL;
        }
    } else {
        inserirLinha(&((*no)->prox), num_linha);
    }
}

Arv23 *quebraNo(Arv23 **raiz, Arv23 *filho, Info *info, Info **infoSobe) {
    /**
     * Divide um nó da árvore 2-3 em dois nós e retorna o nó criado com as informações maiores.
     *
     * Esta função divide um nó da árvore 2-3 em dois nós e retorna o nó criado com as informações maiores.
     * A função recebe o endereço do ponteiro da raiz da árvore, um ponteiro para o filho direito do nó sendo dividido,
     * uma nova informação a ser inserida na árvore (info) e um ponteiro para um ponteiro que armazenará a informação
     * que será propagada para cima na árvore após a divisão (infoSobe).
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore 2-3.
     * @param filho Um ponteiro para o nó filho direito do nó sendo dividido.
     * @param info Um ponteiro para a nova informação a ser inserida na árvore.
     * @param infoSobe Um ponteiro para o ponteiro que armazenará a informação que será propagada para cima após a divisão.
     *
     * @return Um ponteiro para o nó criado com as informações maiores após a divisão.
     */

    Arv23 *maiorNo;
    maiorNo = NULL;

    if (strcmp(info->palavra, (*raiz)->info2->palavra) > 0){
        *infoSobe = (*raiz)->info2;
        maiorNo = criaNo(info, (*raiz)->dir, filho, NULL);
    } else if (strcmp(info->palavra, (*raiz)->info1->palavra) < 0) {
        *infoSobe = (*raiz)->info1;
        maiorNo = criaNo((*raiz)->info2, (*raiz)->centro, (*raiz)->dir, NULL);

        (*raiz)->info1 = info;
        (*raiz)->centro = filho;
    } else {
        *infoSobe = info;
        maiorNo = criaNo((*raiz)->info2, filho, (*raiz)->dir, NULL);
    }
    
    (*raiz)->numInfo = 1;
    (*raiz)->info2 = NULL;
    (*raiz)->dir = NULL;

    return maiorNo;
    
}


Arv23 *inserirPalavra(Arv23  **raiz, char *palavra, int num_linha, Arv23 *pai, Info **infoSobe, int *inseriu){
    /**
     * Insere uma palavra na árvore 2-3.
     *
     * Esta função insere uma palavra em uma árvore 2-3, representada por um ponteiro para a raiz da árvore.
     * A função realiza a inserção de acordo com as regras da árvore 2-3. A árvore é balanceada durante a inserção,
     * dividindo os nós caso seja necessário e propagando informações para cima na árvore quando ocorre divisão.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore 2-3.
     * @param palavra A palavra a ser inserida na árvore.
     * @param num_linha O número da linha onde a palavra ocorre no arquivo.
     * @param pai Um ponteiro para o nó pai do nó atual. NULL caso o nó atual seja a raiz.
     * @param infoSobe Um ponteiro para o ponteiro de informação que será propagada para cima em caso de divisão de nós.
     * @param inseriu Um ponteiro para um inteiro que indica se a palavra foi inserida corretamente:
     *               - 0: A palavra não foi inserida na árvore.
     *               - 1: A palavra foi inserida na árvore.
     *               - 2: A palavra ja existe e apenas a linha foi atualizada.
     *
     * @return Um ponteiro para o nó que representa o maior valor da subárvore direita, caso ocorra divisão de nós.
     *         NULL caso não ocorra divisão de nós.
     */

    Arv23 *maiorNo;
    maiorNo = NULL;

    if (*raiz == NULL){
        *raiz = criaNo(criaInfo(palavra, NULL, num_linha), NULL, NULL, NULL);
        maiorNo = NULL;
        *inseriu = 1;
    } else if(strcmp(palavra, (*raiz)->info1->palavra) == 0){
        inserirLinha(&((*raiz)->info1->num_lista), num_linha);
        *inseriu = 2;
    }else if((*raiz)->numInfo == 2 && strcmp(palavra, (*raiz)->info2->palavra) == 0){
        inserirLinha(&((*raiz)->info2->num_lista), num_linha);
        *inseriu = 2;
    }else{
        if (ehFolha(*raiz)){
            if ((*raiz)->numInfo == 1){
                adicionaNo(raiz, criaInfo(palavra, NULL, num_linha), NULL);
                maiorNo = NULL;
                *inseriu = 1;
            } else {
                maiorNo = quebraNo(raiz, NULL, criaInfo(palavra, NULL, num_linha), infoSobe);

                if (pai == NULL){
                    *raiz = criaNo(*infoSobe, *raiz, maiorNo, NULL);
                    maiorNo = NULL;
                }
                *inseriu = 1;
            }
        } else {
            if (strcmp(palavra, (*raiz)->info1->palavra) < 0){
                // A palavra é menor que a primeira informação do nó atual, continua a busca na subárvore à esquerda
                maiorNo = inserirPalavra(&(*raiz)->esq, palavra, num_linha, *raiz, infoSobe, inseriu);
            } else if (((*raiz)->numInfo == 1) || (*raiz)->numInfo == 2 && strcmp(palavra, (*raiz)->info2->palavra) < 0){
                // A palavra é maior que a primeira informação e menor que a segunda (se existir), continua a busca na subárvore central
                maiorNo = inserirPalavra(&((*raiz)->centro), palavra, num_linha, *raiz, infoSobe, inseriu);
            } else {
                maiorNo = inserirPalavra(&((*raiz)->dir), palavra, num_linha, *raiz, infoSobe, inseriu);
            }
            if (maiorNo != NULL){
                if ((*raiz)->numInfo == 1){
                    adicionaNo(raiz, *infoSobe, maiorNo);
                    maiorNo = NULL;
                } else {
                    maiorNo = quebraNo(raiz, maiorNo, *infoSobe, infoSobe);
                            
                    if(pai == NULL){
                        *raiz = criaNo(*infoSobe, *raiz, maiorNo, NULL);
                        maiorNo = NULL;
                    }
                }
            }
        }
        
    }

    return (maiorNo);
}


int lerArquivoTexto(Arv23 **raiz, const char *nome_arquivo) {
    /**
     * Lê um arquivo de texto e insere as palavras em uma árvore 2-3.
     *
     * Esta função lê um arquivo de texto e insere cada palavra em uma árvore 2-3,
     * representada por um ponteiro para a raiz da árvore. O arquivo é lido linha por
     * linha, e cada linha é tokenizada para obter as palavras individuais. As palavras
     * são convertidas para letras minúsculas antes da inserção na árvore.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore 2-3.
     * @param nome_arquivo O nome do arquivo de texto a ser lido.
     *
     * @return Um valor indicando se o arquivo foi lido e as palavras foram inseridas
     *         corretamente na árvore:
     *         - 0: Falha na leitura do arquivo ou erro na inserção de palavras.
     *         - 1: O arquivo foi lido e as palavras foram inseridas na árvore com sucesso.
    */

    int leitura = 1;
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "r");
    Info *aux;
    aux = NULL;

    if (arquivo == NULL) {
        leitura = 0;
        return leitura;
    }
    char linha[1000];
    char *token;
    int num_linha = 1, confirma = 0;
    Info *infoSobe;
    infoSobe = NULL;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        token = strtok(linha, " \t\n,.");

        while (token != NULL) {
            // Converte a palavra para letras minúsculas
            for (int i = 0; token[i] != '\0'; i++) {
                token[i] = tolower(token[i]);
            }
            token[strcspn(token, "\n")] = '\0';
            inserirPalavra(raiz, token, num_linha, NULL, &infoSobe, &confirma);
            token = strtok(NULL, " \t\n,.");
        }

        num_linha++;
    }

    fclose(arquivo);
    return leitura;
}


void buscar_palavra(Arv23 *raiz, char palavra[], int *resultado, int *cont){
    /**
     * Busca uma palavra na árvore 2-3 e imprime suas informações.
     *
     * Esta função busca uma palavra na árvore 2-3 e imprime suas informações caso a palavra seja encontrada.
     * A função utiliza uma abordagem recursiva para percorrer a árvore e comparar as palavras nos nós com a palavra buscada.
     * Se a palavra for encontrada em um nó da árvore, a função imprime a palavra e a lista de números de linha em que ela aparece.
     * O resultado da busca é armazenado no ponteiro "resultado". Se a palavra for encontrada, o valor apontado por "resultado" é alterado para 1.
     *
     * @param raiz Um ponteiro para o nó raiz da árvore 2-3.
     * @param palavra A palavra a ser buscada na árvore.
     * @param resultado Um ponteiro para um inteiro que armazena o resultado da busca (0 se a palavra não for encontrada, 1 se for encontrada).
     */

    if (raiz != NULL){
        *cont += 1;
        if (strcmp(palavra, raiz->info1->palavra) == 0){
            printf("\nPalavra: %s\n", palavra);
            printf("Linha: ");
            imprimirLinhas(raiz->info1->num_lista, 0);
            printf("\n");
            *resultado = 1;
        }
        if (raiz->numInfo == 2){
            if (strcmp(palavra, raiz->info2->palavra) == 0){
            printf("\nPalavra: %s\n", palavra);
            printf("Linha: ");
            imprimirLinhas(raiz->info2->num_lista, 1);
            printf("\n");
            *resultado = 1;
            }
        }
        
        if (*resultado == 0 && strcmp(palavra, raiz->info1->palavra) < 0){
            buscar_palavra(raiz->esq, palavra, resultado, cont);
        } else if (*resultado == 0 && raiz->numInfo == 1 || raiz->numInfo == 2 && strcmp(palavra, raiz->info2->palavra) < 0){
            buscar_palavra(raiz->centro, palavra, resultado, cont);
        } else if(*resultado == 0 && raiz->numInfo == 2 && strcmp(palavra, raiz->info2->palavra) > 0) {
            buscar_palavra(raiz->dir, palavra, resultado, cont);
        }
    }
}


void imprimirEmOrdem(Arv23 *raiz, int cont) {
    /**
     * Imprime os nós de uma árvore 2-3 em ordem.
     *
     * Esta função imprime os nós de uma árvore 2-3 em ordem. Cada nó da árvore representa uma palavra
     * e seus números de linha associados. A função utiliza uma abordagem recursiva para percorrer a árvore em ordem, imprimindo as palavras e suas respectivas listas de números de linha.
     *
     * @param raiz Um ponteiro para o nó raiz da árvore 2-3.
     * @param cont Um contador que auxilia no controle da recursão e formatação da impressão.
    */

    if (raiz != NULL) {
        if (raiz->numInfo == 1) {
            printf("%s: ", raiz->info1->palavra);
            imprimirLinhas(raiz->info1->num_lista, 0);
            printf("\n");
        } else if (raiz->numInfo == 2) {
            printf("%s: ", raiz->info1->palavra);
            imprimirLinhas(raiz->info1->num_lista, 0);
            printf("\n");
            printf("%s: ", raiz->info2->palavra);
            imprimirLinhas(raiz->info2->num_lista, 0);
            printf("\n");
        }
        imprimirEmOrdem(raiz->esq, cont + 1);
        imprimirEmOrdem(raiz->centro, cont + 1); // Imprime o nó central
        imprimirEmOrdem(raiz->dir, cont + 1);
    } else if (cont == 0){
        printf("Arvore vazia!\n");
    }
}



void imprimirLinhas(Lista *no, int cont) {
    /**
     * Imprime os números de linha de uma lista encadeada.
     *
     * Esta função imprime os números de linha de uma lista encadeada. A lista contém os números de linha em que uma
     * palavra aparece. A função utiliza uma abordagem recursiva para percorrer a lista encadeada e imprimir os números
     * de linha em ordem.
     *
     * @param no Um ponteiro para o nó da lista encadeada.
     * @param cont Um contador que auxilia no controle da recursão e formatação da impressão.
    */

    if (no != NULL) {
        if (cont == 0) {
            printf("%d", no->num_linha);
        } else {
            printf(" %d", no->num_linha);
        }
        imprimirLinhas(no->prox, cont + 1);
    }
}


int remvLinhs(Lista** lista, int valor) {
    /**
     * Remove um elemento de uma lista encadeada.
     *
     * Esta função é responsável por remover um elemento específico de uma lista encadeada.
     * Ela recebe um ponteiro para o ponteiro da lista, bem como o valor do elemento a ser removido.
     * A função percorre a lista até encontrar o elemento a ser removido.
     * Se o elemento for encontrado, ele é removido da lista e a memória é liberada.
     *
     * @param lista Um ponteiro para o ponteiro da lista encadeada (pode ser atualizado após a remoção).
     * @param valor O valor do elemento a ser removido da lista.
     *
     * @return Um valor indicando se o elemento foi removido:
     *         - 0: O elemento não foi encontrado na lista.
     *         - 1: O elemento foi removido da lista.
    */

    int removeu = 0;
    if (*lista != NULL) {
        Lista* anterior = NULL;
        Lista* atual = *lista;

        // Percorrer a lista procurando o elemento a ser removido
        while (atual != NULL && atual->num_linha != valor) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual == NULL) {
            // Elemento não encontrado na lista
            removeu = 0;
        }

        // Elemento encontrado, remover da lista
        else if (anterior == NULL) {
            // O elemento a ser removido é o primeiro da lista
            *lista = atual->prox;
            removeu = 1;
        } else {
            anterior->prox = atual->prox;
            removeu = 1;
        }

        free(atual); // Liberar a memória do elemento removido
    }
    return removeu;
}


void MaiorInfoRemoveEsq(Arv23 **raiz, Arv23 **maiorPai, Arv23 **maiorInfoRemove, int infoLocal, int linha){
    /**
     * Encontra o maior valor menor ou igual à palavra na subárvore esquerda e o substitui.
     *
     * Esta função é responsável por encontrar o maior valor menor ou igual à palavra na subárvore esquerda e o substituir.
     * Ela é utilizada durante a remoção de uma palavra na árvore 2-3 quando a palavra a ser removida não é uma folha.
     * A função percorre a subárvore esquerda e encontra o maior valor menor ou igual à palavra.
     * Em seguida, realiza a troca das palavras e chama a função `removerArv23` para remover o valor encontrado.
     * A função `redistribuiArv` também é chamada para realizar a redistribuição dos nós após a remoção.
     *
     * @param raiz Um ponteiro para o ponteiro do nó raiz da árvore 2-3 (pode ser atualizado após a remoção).
     * @param maiorPai Um ponteiro para o ponteiro do pai do nó com o maior valor menor ou igual à palavra.
     * @param maiorInfoRemove Um ponteiro para o ponteiro do nó com o maior valor menor ou igual à palavra (pode ser atualizado após a remoção).
     * @param infoLocal Indica se o valor a ser encontrado é o info1 ou info2 do nó (1 para info1, 2 para info2).
     * @param linha O número de linha associado à palavra a ser removida da lista de números de linha.
    */

    if (*maiorInfoRemove != NULL){
        if ((*maiorInfoRemove)->esq == NULL){
            char *aux;
            aux = (char *) malloc (sizeof(char) * 50);
            strcpy(aux, "NOT FOUND");

            if (infoLocal == 1){
                strcpy(aux, (*raiz)->info1->palavra);

                if ((*maiorInfoRemove)->numInfo == 2){
                    strcpy((*raiz)->info1->palavra, (*maiorInfoRemove)->info2->palavra);
                    strcpy((*maiorInfoRemove)->info2->palavra, aux);
                } else {
                    strcpy((*raiz)->info1->palavra, (*maiorInfoRemove)->info1->palavra);
                    strcpy((*maiorInfoRemove)->info1->palavra, aux);
                }
                
            } else if (infoLocal == 2){
                strcpy(aux, (*raiz)->info2->palavra);

                if ((*maiorInfoRemove)->numInfo == 2){
                    strcpy((*raiz)->info2->palavra, (*maiorInfoRemove)->info2->palavra);
                    strcpy((*maiorInfoRemove)->info2->palavra, aux);
                } else {
                    strcpy((*raiz)->info2->palavra, (*maiorInfoRemove)->info1->palavra);
                    strcpy((*maiorInfoRemove)->info1->palavra, aux);
                }
                
            }
            
            removerArv23(maiorPai, maiorInfoRemove, aux, linha);
        }
        else {
            if ((*maiorInfoRemove)->numInfo == 2){
                MaiorInfoRemoveEsq(raiz, maiorInfoRemove, &(*maiorInfoRemove)->dir, infoLocal, linha);
            } else if ((*maiorInfoRemove)->numInfo == 1){
                MaiorInfoRemoveEsq(raiz, maiorInfoRemove, &(*maiorInfoRemove)->centro, infoLocal, linha);
            }        
        }
    }
    redistribuiArv(maiorInfoRemove, maiorPai);
}


void redistribuiArv(Arv23 **raiz, Arv23 **pai) {
    /**
     * Redistribui os nós de uma árvore 2-3 após a remoção de uma palavra.
     *
     * Esta função é responsável por redistribuir os nós de uma árvore 2-3 após a remoção de uma palavra.
     * A redistribuição é realizada para manter as propriedades da árvore 2-3 após a remoção.
     * A função percorre a árvore 2-3 e realiza as redistribuições de acordo com os casos específicos de remoção.
     *
     * @param raiz Um ponteiro para o ponteiro do nó raiz da árvore 2-3 (pode ser atualizado após a redistribuição).
     * @param pai Um ponteiro para o ponteiro do pai do nó atual (pai do nó raiz inicialmente).
     */

    if (*raiz != NULL)
        if ((*raiz)->numInfo == 0) {
            if (pai != NULL) {
                if ((*raiz) == ((*pai)->dir)) {
                    if ((*pai)->centro->numInfo == 2) {
                        (*raiz)->info1 = (*pai)->info1;
                        (*raiz)->numInfo = 1;
                        (*pai)->info2 = (*pai)->centro->info2;
                        (*pai)->centro->numInfo = 1;
                        (*raiz)->esq = (*pai)->centro->dir;
                        (*pai)->centro->dir = NULL;
                    }
                    else if ((*pai)->centro->numInfo == 1) {
                        (*raiz)->info2 = (*pai)->info2;
                        (*raiz)->dir = (*raiz)->centro;
                        (*raiz)->info1 = (*pai)->centro->info1;
                        (*raiz)->numInfo = 2;
                        (*pai)->numInfo = 1;
                        (*raiz)->centro = (*pai)->centro->centro;
                        (*raiz)->esq = (*pai)->centro->esq;
                        free((*pai)->centro);
                        (*pai)->centro = (*raiz);
                        (*pai)->dir = NULL;
                    }
                }
                else if ((*raiz) == (*pai)->centro) {
                    if ((*pai)->esq->numInfo == 2) {
                        (*raiz)->info1 = (*pai)->info1;
                        (*raiz)->numInfo = 1;
                        (*pai)->info1 = (*pai)->esq->info2;
                        (*pai)->esq->numInfo = 1;
                        (*raiz)->esq = (*pai)->esq->dir;
                        (*pai)->esq->dir = NULL;
                    }
                    else if ((*pai)->esq->numInfo == 1) {
                        if ((*pai)->numInfo == 2) {
                            (*raiz)->info2 = (*pai)->info1;
                            (*raiz)->info1 = (*pai)->esq->info1;
                            (*raiz)->numInfo = 2;
                            (*raiz)->dir = (*raiz)->centro;
                            (*raiz)->centro = (*pai)->esq->centro;
                            (*raiz)->esq = (*pai)->esq->esq;
                            free((*pai)->esq);
                            (*pai)->esq = (*raiz);
                            (*pai)->info1 = (*pai)->info2;
                            (*pai)->numInfo = 1;
                            (*pai)->centro = (*pai)->dir;
                            (*pai)->dir = NULL;
                        }
                        else if ((*pai)->numInfo == 1) {
                            (*raiz)->info2 = (*pai)->info1;
                            (*raiz)->info1 = (*pai)->esq->info1;
                            (*raiz)->numInfo = 2;
                            (*pai)->numInfo = 0;
                            (*raiz)->dir = (*raiz)->centro;
                            (*raiz)->centro = (*pai)->esq->centro;
                            (*raiz)->esq = (*pai)->esq->esq;
                            free((*pai)->esq);
                            (*pai)->esq = NULL;
                        }
                    }
                }
                else if ((*raiz) == (*pai)->esq) {
                    if ((*pai)->centro->numInfo == 2) {
                        (*raiz)->info1 = (*pai)->info1;
                        (*raiz)->numInfo = 1;
                        (*pai)->info1 = (*pai)->centro->info1;
                        (*pai)->centro->numInfo = 1;
                        (*pai)->centro->info1 = (*pai)->centro->info2;
                        (*raiz)->esq = (*raiz)->centro;
                        (*raiz)->centro = (*pai)->centro->esq;
                        (*pai)->centro->esq = (*pai)->centro->centro;
                        (*pai)->centro->centro = (*pai)->centro->dir;
                        (*pai)->centro->dir = NULL;
                    }
                    else if ((*pai)->centro->numInfo == 1) {
                        if ((*pai)->numInfo == 2) {
                            (*raiz)->info1 = (*pai)->info1;
                            (*raiz)->info2 = (*pai)->centro->info1;
                            (*raiz)->numInfo = 2;
                            (*raiz)->esq = (*raiz)->centro;
                            (*raiz)->centro = (*pai)->centro->esq;
                            (*raiz)->dir = (*pai)->centro->centro;
                            (*pai)->info1 = (*pai)->info2;
                            (*pai)->numInfo = 1;
                            free((*pai)->centro);
                            (*pai)->centro = (*pai)->dir;
                            (*pai)->dir = NULL;
                        }
                        else if ((*pai)->numInfo == 1) {
                            (*raiz)->info1 = (*pai)->info1;
                            (*raiz)->esq = (*raiz)->centro;
                            (*raiz)->info2 = (*pai)->centro->info1;
                            (*raiz)->centro = (*pai)->centro->esq;
                            (*raiz)->dir = (*pai)->centro->centro;
                            (*pai)->numInfo = 0;
                            (*raiz)->numInfo = 2;
                            free((*pai)->centro);
                            (*pai)->centro = (*raiz);
                            (*pai)->esq = NULL;
                        }
                    }
                }
            }
            else if (pai == NULL) {
                (*raiz) = (*raiz)->centro;
            }   
        }
}


int removerArv23(Arv23 **pai, Arv23 **raiz, char *palavra, int linha){
    /**
     * Remove uma palavra e seu número de linha associado da árvore 2-3.
     *
     * Esta função remove uma palavra e seu número de linha associado da árvore 2-3.
     * A função utiliza uma abordagem recursiva para percorrer a árvore em busca da palavra a ser removida.
     * Caso a palavra seja encontrada, a função remove o número de linha da lista associada a essa palavra.
     * Se a lista de números de linha ficar vazia após a remoção, a função realiza a remoção da palavra propriamente dita da árvore.
     * A remoção de uma palavra pode causar uma redistribuição dos nós da árvore.
     * O parâmetro "pai" é um ponteiro para o ponteiro do pai do nó atual. Ele é usado para realizar a redistribuição dos nós após a remoção.
     *
     * @param pai Um ponteiro para o ponteiro do pai do nó atual (pai do nó raiz inicialmente).
     * @param raiz Um ponteiro para o ponteiro do nó raiz da árvore 2-3 (pode ser atualizado após a remoção).
     * @param palavra A palavra a ser removida da árvore.
     * @param linha O número de linha associado à palavra a ser removido da lista de números de linha.
     *
     * @return Um valor indicando se a palavra e o número de linha foram removidos:
     *         - 0: A palavra e o número de linha não foram removidos da árvore.
     *         - 1: A palavra e o número de linha foram removidos da árvore.
    */

    int removeu = 0;
    if (*raiz != NULL){
        if (strcmp(palavra, (*raiz)->info1->palavra) == 0){
            if((*raiz)->info1->num_lista != NULL){
                removeu = remvLinhs(&(*raiz)->info1->num_lista, linha);
            }
            if((*raiz)->info1->num_lista == NULL){
                if (ehFolha(*raiz)){
                    if ((*raiz)->numInfo == 2){
                        (*raiz)->info1 = (*raiz)->info2;
                        (*raiz)->numInfo = 1;
                    }
                    else if ((*raiz)->numInfo == 1){
                        (*raiz)->numInfo = 0;
                    }
                    removeu = 1;
                } else {
                    Arv23 **maiorInfoRemove = &((*raiz)->esq);
                    Arv23 **maiorPai = raiz;
                    MaiorInfoRemoveEsq(raiz, maiorPai, maiorInfoRemove, 1, linha);
                }
            }
            
        } else if ((*raiz)->numInfo == 2 && strcmp(palavra, (*raiz)->info2->palavra) == 0){
            if((*raiz)->info2->num_lista != NULL){
                removeu = remvLinhs(&(*raiz)->info2->num_lista, linha);
            }
            if((*raiz)->info2->num_lista == NULL){
                if (ehFolha(*raiz)){
                    (*raiz)->numInfo = 1;
                } else {
                    Arv23 **maiorInfoRemove = &((*raiz)->centro);
                    Arv23 **maiorPai = raiz;
                    MaiorInfoRemoveEsq(raiz, maiorPai, maiorInfoRemove, 2, linha);
                }
                removeu = 1;
            }
        }
        else if (strcmp(palavra, (*raiz)->info1->palavra) < 0){
            removeu = removerArv23(raiz, &(*raiz)->esq, palavra, linha);
        } else if ((*raiz)->numInfo == 1 || (*raiz)->numInfo == 2 && strcmp(palavra, (*raiz)->info2->palavra) < 0){
            removeu = removerArv23(raiz, &(*raiz)->centro, palavra, linha);
        } else {
            removeu = removerArv23(raiz, &(*raiz)->dir, palavra, linha);
        }
        
    }
    redistribuiArv(raiz, pai);

    return removeu;
}



