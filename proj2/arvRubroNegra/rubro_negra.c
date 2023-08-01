#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> //usado para transformar as letras da palavra em minusculas

#include "rubro_negra.h"

#define RED 1
#define BLACK 0

int cor(ArvRubroNegra *raiz){
    /**
     * Retorna a cor de um nó em uma árvore rubro-negra.
     *
     * @param raiz O nó da árvore rubro-negra.
     *
     * @return A cor do nó:
     *         - 0: Preto (BLACK)
     *         - 1: Vermelho (RED)
     */

    int cor;
    if(raiz == NULL) {
        cor = BLACK;
    } else {
        cor = raiz->cor;
    }
    return cor;
}

int inserirLinha(Lista **no, int num_linha){
    /**
     * Insere um número de linha em uma lista encadeada.
     *
     * @param no Um ponteiro para o ponteiro da lista encadeada.
     * @param num_linha O número da linha a ser inserido na lista.
     *
     * @return Um valor indicando se o número de linha foi inserido:
     *         - 0: O número de linha não foi inserido na lista.
     *         - 1: O número de linha foi inserido na lista.
     */

    int inseriu = 0;
    if (*no == NULL){
        *no = (Lista*) malloc (sizeof(Lista));

        if (*no != NULL){
            (*no)->num_linha = num_linha;
            (*no)->prox = NULL;
            // inseriu indica que inseriu o numero na lista ou não, 1 para sim 0 para não
            inseriu = 1;
        }
        
    } else {
        inseriu = inserirLinha(&((*no)->prox), num_linha);
    }

    return inseriu;
}

int criaNo(ArvRubroNegra **raiz, char *palavra, int num_linha) {
    /**
     * Cria um novo nó para ser inserido em uma árvore rubro-negra.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore rubro-negra.
     * @param palavra A palavra a ser inserida no novo nó.
     * @param num_linha O número da linha a ser associado à palavra.
     *
     * @return Um valor indicando se o nó foi criado:
     *         - 0: Não foi criado um novo nó.
     *         - 1: Foi criado um novo nó.
     */

    int criou = 0;
    if (*raiz == NULL) {
        *raiz = (ArvRubroNegra *)malloc(sizeof(ArvRubroNegra));
        if (*raiz != NULL) {
            (*raiz)->info = (Info *)malloc(sizeof(Info));
            (*raiz)->info->palavra = (char *)malloc((strlen(palavra) + 1) * sizeof(char));
            (*raiz)->info->num_lista = NULL;

            strcpy((*raiz)->info->palavra, palavra);
            inserirLinha(&((*raiz)->info->num_lista), num_linha);

            (*raiz)->cor = RED;
            (*raiz)->dir = NULL;
            (*raiz)->esq = NULL;
            criou = 1; // criou
        }
    } else {
        // Caso em que o nó já existe
        inserirLinha(&((*raiz)->info->num_lista), num_linha);
    }

    return criou;
}


void rotacaoEsquerda(ArvRubroNegra **raiz){
    /*
    Essa função realiza uma rotação à esquerda na árvore Rubro-Negra. Ela recebe um ponteiro para um ponteiro da raiz da árvore (ArvRubroNegra **raiz) e executa a rotação. O que a função faz é basicamente trocar os nós raiz e raiz->dir para manter as propriedades da árvore.
    */
    ArvRubroNegra *aux;

    aux = (*raiz)->dir; 
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

void rotacaoDireita(ArvRubroNegra **raiz){
    /*
    Essa função realiza uma rotação à direita na árvore Rubro-Negra. Ela recebe um ponteiro para um ponteiro da raiz da árvore (ArvRubroNegra **raiz) e executa a rotação. O que a função faz é basicamente trocar os nós raiz e raiz->esq para manter as propriedades da árvore.
    */
    ArvRubroNegra *aux;

    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}

void trocaCor(ArvRubroNegra  *raiz){
    /*
    Essa função inverte a cor do nó (RED para BLACK ou BLACK para RED) e também inverte a cor dos filhos, caso existam. Essa operação é utilizada após realizar as rotações para garantir que a árvore mantenha as propriedades da árvore Rubro-Negra.
    */
    if(raiz != NULL){
        raiz->cor = !raiz->cor; 
        if(raiz->dir) {
            raiz->dir->cor = !raiz->dir->cor;
        } else if(raiz->esq)
            raiz->esq->cor = !raiz->esq->cor; 
    }
}

int inserirPalavra(ArvRubroNegra  **raiz, char *palavra, int num_linha){
    /**
     * Insere uma palavra em uma árvore rubro-negra e associa um número de linha a ela.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore rubro-negra.
     * @param palavra A palavra a ser inserida na árvore.
     * @param num_linha O número da linha em que a palavra está presente.
     *
     * @return O valor de criouNo, indicando o resultado da inserção:
     *         - 0: Não foi criado um novo nó na árvore.
     *         - 1: Foi criado um novo nó na árvore.
     *         - 2: A palavra já existe na árvore e apenas o número da linha foi atualizada.
     */
    
    int criouNo = 0;
    if (*raiz == NULL){
        criouNo = criaNo(raiz, palavra, num_linha);
    }
    //É verificado se o valor está na arvore, se estiver colocar o numero da linha na lista de numeros.
    else if (strcmp((*raiz)->info->palavra, palavra) == 0){
        criouNo = 2; //Já existe
        inserirLinha(&((*raiz)->info->num_lista), num_linha);
    } else if (strcmp((*raiz)->info->palavra, palavra) < 0){
        criouNo = inserirPalavra(&((*raiz)->dir), palavra, num_linha);
    } else if(strcmp((*raiz)->info->palavra, palavra) > 0) {
        criouNo = inserirPalavra(&((*raiz)->esq), palavra, num_linha); 
    }

    if(cor((*raiz)->dir) == RED && cor((*raiz)->esq) == BLACK)
        rotacaoEsquerda(raiz);
    if(cor((*raiz)->esq) == RED && cor((*raiz)->esq->esq) == RED)
        rotacaoDireita(raiz);
    if(cor((*raiz)->esq) == RED && cor((*raiz)->dir) == RED)
        trocaCor(*raiz);

    return criouNo;
}



int inserirRubro(ArvRubroNegra  **raiz, char *palavra, int num_linha){
    /**
     * Insere uma palavra em uma árvore rubro-negra e associa um número de linha a ela.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore rubro-negra.
     * @param palavra A palavra a ser inserida na árvore.
     * @param num_linha O número da linha em que a palavra está presente.
     *
     * @return O valor de inseriu, indicando o resultado da inserção:
     *         - 0: A palavra não foi inserida na árvore.
     *         - 1: A palavra foi inserida na árvore.
     *         - 2: A palavra já existe na árvore e apenas o número da linha foi atualizada.
     */

    for(int i=0; palavra[i] != '\0'; i++) {
        palavra[i] = tolower(palavra[i]);
    }

    int inseriu = inserirPalavra(raiz, palavra, num_linha);
    if (*raiz != NULL){
        (*raiz)->cor = BLACK;
    }
    return inseriu;
}


int lerArquivoTexto(ArvRubroNegra **raiz, const char *nome_arquivo) {
    /**
     * Lê um arquivo de texto e processa as palavras, inserindo-as em uma árvore rubro-negra.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore rubro-negra.
     * @param nome_arquivo O nome do arquivo de texto a ser lido.
     *
     * @return Um valor indicando se a leitura do arquivo foi bem-sucedida:
     *         - 0: O arquivo não pôde ser aberto.
     *         - 1: A leitura do arquivo foi bem-sucedida.
     */

    int leitura = 1;
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        leitura = 0;
        return leitura;
    }

    char linha[1000];
    int num_linha = 1;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, " \t\n,.");
        while (token != NULL) {
            // Converte a palavra para letras minúsculas
            for (int i = 0; token[i] != '\0'; i++) {
                token[i] = tolower(token[i]);
            }

            inserirRubro(raiz, token, num_linha);

            token = strtok(NULL, " \t\n,.");
        }

        num_linha++;
    }

    fclose(arquivo);
    return leitura;
}


void imprmrInOrdem(ArvRubroNegra *raiz, int cont){
    /**
     * Imprime as palavras da árvore rubro-negra em ordem alfabética junto aos números das linhas em que a palavra aparece.
     *
     * @param raiz A raiz da árvore rubro-negra.
     * @param cont Um contador para controle recursivo.
     */
    if(raiz != NULL){
        imprmrInOrdem(raiz->esq, cont+1);
        printf("%s: ", raiz->info->palavra);
        imprmrLinhs(raiz->info->num_lista, 0);
        printf("\n");
        imprmrInOrdem(raiz->dir, cont+1);
    }else if(cont == 0){
        printf("Arvore vazia!\n");
    }
}

void imprmrLinhs(Lista *raiz, int cont){
    //Função responsável por imprimir as linhas associadas a uma palavra encontrada na árvore. 
    if(raiz!=NULL){
        if(cont==0)
            printf("%d", raiz->num_linha);
        else printf(", %d", raiz->num_linha);
        imprmrLinhs(raiz->prox, cont+1);
    }
}


int buscrPalvr(ArvRubroNegra *raiz, char palavra[], ArvRubroNegra **No, int *cont){
    //Função responsável por buscar uma palavra na Árvore Rubro-Negra.
    int achou = 0;
    if(raiz != NULL){
        *cont+=1;
        if(strcmp(raiz->info->palavra, palavra) == 0){
            *No = (ArvRubroNegra *)malloc(sizeof(ArvRubroNegra));
            (*No)->info = (Info *)malloc(sizeof(Info));
            (*No)->info->palavra = (char *)malloc((strlen(palavra) + 1) * sizeof(char));
            achou = 1;
            strcpy((*No)->info->palavra, raiz->info->palavra);
            (*No)->info->num_lista = raiz->info->num_lista;
        } else if(strcmp(raiz->info->palavra, palavra) < 0){
            achou = buscrPalvr(raiz->dir, palavra, No, cont);
        }else if(strcmp(raiz->info->palavra, palavra) > 0){
            achou = buscrPalvr(raiz->esq, palavra, No, cont);
        }
    }
    return achou;
}


// funcao auxiliar para remover uma palavra
ArvRubroNegra *buscrFolh(ArvRubroNegra *ultimo){
    // vai procurar o maior filho a esquerda do no.
    // quando encontra-lo a variavel aux vai pegar esse valor.
    if(ultimo->dir != NULL){
        buscrFolh(ultimo->dir);
    }else{
        return ultimo;
    }
}

int remvPalvr(ArvRubroNegra **raiz, char palavra[]){
    //Função principal para remover palavra na árvore rubro-negra
    int removeu = 0;
    ArvRubroNegra *aux = NULL;
    if(*raiz != NULL){
        if(strcmp((*raiz)->info->palavra, palavra) == 0){
            if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
                aux = *raiz;
                (*raiz) = NULL;
            }else if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
                if((*raiz)->esq != NULL){
                    aux = *raiz;
                    *raiz = (*raiz)->esq;
                }else{
                    aux = *raiz;
                    *raiz = (*raiz)->dir;
                }
            }else{
                aux = buscrFolh((*raiz)->esq);
                *raiz = aux;
                aux = NULL;
            }
            free(aux);
            removeu = 1;
        }else if(strcmp((*raiz)->info->palavra, palavra) < 0){
            removeu = remvPalvr(&((*raiz)->dir), palavra);
        }else if(strcmp((*raiz)->info->palavra, palavra) > 0){
            removeu = remvPalvr(&((*raiz)->esq), palavra);
        }
    }

    if(cor((*raiz)->dir) == RED && cor((*raiz)->esq) == BLACK)
        rotacaoEsquerda(raiz);
    if(cor((*raiz)->esq) == RED && cor((*raiz)->esq->esq) == RED)
        rotacaoDireita(raiz);
    if(cor((*raiz)->esq) == RED && cor((*raiz)->dir) == RED)
        trocaCor(*raiz);

    return removeu;
}