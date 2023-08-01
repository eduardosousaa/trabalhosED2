#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> //usado para transformar as letras da palavra em minusculas
// #include <windows.h>

#include "arv45.h"

void lerArquivo(Arv45 **raiz, Info **sobe){
    /**
     * Lê um arquivo de dados contendo informações de calçados e insere os dados em uma árvore 4-5.
     *
     * Esta função abre o arquivo "lojaCalcados.txt" para leitura e lê as informações de cada calçado contidas no arquivo.
     * Em seguida, chama a função inserir45 para inserir as informações do calçado na árvore 4-5.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore 4-5.
     * @param sobe Um ponteiro para a informação que será inserida na árvore caso haja uma subida durante a inserção.
    */

    FILE *arquivo;
    int cod, tam, qtd, linha, flag = 0;
    char tipo[100], marca[100];
    float preco;

    // Abrir o arquivo para leitura
    arquivo = fopen("lojaCalcados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }else{

        linha = 1;

        // Ler cada linha do arquivo até o final
        while (fscanf(arquivo, "%d %d %d %s %s %f\n", &cod, &tam, &qtd, tipo, marca, &preco) == 6) {
            inserir45(raiz, NULL, sobe, cod, tam, qtd, linha, tipo, marca, preco, &flag);
            if(flag == 0) 
                printf("Esse codigo nao foi inserido: %d\n", cod);
            flag = 0;
            linha++;
        }

        fclose(arquivo);

    }
}

Info *criaInfo(int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco){
    /**
     * Cria uma nova informação (Info) com os dados de um calçado.
     *
     * Esta função aloca memória para uma nova estrutura de informação (Info) e inicializa seus campos com os dados do calçado.
     *
     * @param cod O código do calçado.
     * @param tam O tamanho do calçado.
     * @param qtd A quantidade disponível do calçado.
     * @param linha O número da linha em que as informações do calçado foram lidas do arquivo.
     * @param tipo A string que representa o tipo do calçado.
     * @param marca A string que representa a marca do calçado.
     * @param preco O preço do calçado.
     *
     * @return Um ponteiro para a nova estrutura Info criada.
     */

    Info *info;

    info = (Info*) malloc (sizeof(Info));

    info->codigo = cod;
    info->tamanho = tam;
    info->qtd = qtd;
    info->linha = linha;

    info->tipo = (char *) malloc (sizeof(char) *(strlen(tipo) + 1));
    strcpy(info->tipo, tipo);

    info->marca = (char *) malloc(sizeof(char) *(strlen(marca) + 1));
    strcpy(info->marca, marca);

    info->preco = preco;

    return info;
}

Arv45 *criaNo(Info *info, Arv45 * NoEsq, Arv45 * noCentroEsq){
    /**
     * Cria um novo nó para a árvore 4-5.
     *
     * Esta função aloca memória para um novo nó da árvore 4-5 e inicializa seus campos.
     * O novo nó terá uma ou duas informações, dependendo da quantidade de informações no nó pai.
     *
     * @param info Um ponteiro para a primeira informação que será armazenada no novo nó.
     * @param NoEsq Um ponteiro para o nó filho esquerdo do novo nó.
     * @param noCentroEsq Um ponteiro para o nó filho central esquerdo do novo nó.
     *
     * @return Um ponteiro para o novo nó criado.
     */

    Arv45 *no;
    no = (Arv45 *) malloc (sizeof(Arv45));

    no->info1 = info;
    no->qtdInfo = 1;
    no->esq = NoEsq;
    no->centroEsq = noCentroEsq;
    no->centro = NULL;
    no->centroDir = NULL;
    no->dir = NULL;

    return no;
}

int ehFolha(Arv45 *no) {
    /**
     * Verifica se um nó da árvore 4-5 é uma folha.
     *
     * Esta função verifica se o nó passado como parâmetro é uma folha da árvore, ou seja, não possui filhos.
     *
     * @param no Um ponteiro para o nó a ser verificado.
     *
     * @return 1 se o nó é uma folha, 0 caso contrário.
     */

    int verifica = 0;

    if (no->esq == NULL){
        verifica = 1;
    }
    return verifica;
}

void adicionaNo(Arv45 **No, Info *info, Arv45 *filho){
    /**
     * Adiciona uma nova informação a um nó da árvore 4-5.
     *
     * Esta função adiciona uma nova informação a um nó da árvore 4-5 e atualiza seus ponteiros de filhos.
     * A função verifica a ordem do código da informação para determinar a posição correta de inserção e atualizar os ponteiros de filhos do nó.
     *
     * @param No Um ponteiro para o ponteiro do nó que será modificado pela função, caso a inserção resulte em uma subida.
     * @param info Um ponteiro para a nova informação a ser adicionada no nó.
     * @param filho Um ponteiro para o nó que será o filho do nó após a inserção.
     */

    if((*No)->qtdInfo == 1){
        if(info->codigo > (*No)->info1->codigo){
            (*No)->info2 = info;
            (*No)->centro = filho;

        } else {
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;

            (*No)->centro = (*No)->centroEsq;
            (*No)->centroEsq = filho;

        }
        (*No)->qtdInfo = 2;

    } else if((*No)->qtdInfo == 2){

        if(info->codigo > (*No)->info2->codigo){
            (*No)->info3 = info;
            (*No)->centroDir = filho;

        } else if(info->codigo > (*No)->info1->codigo && info->codigo < (*No)->info2->codigo){
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = info;

            (*No)->centroDir = (*No)->centro;
            (*No)->centro = filho;

        } else{
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;

            (*No)->centroDir = (*No)->centro;
            (*No)->centro = (*No)->centroEsq;
            (*No)->centroEsq = filho;

        }
        (*No)->qtdInfo = 3;

    } else{
        if(info->codigo > (*No)->info3->codigo){
            (*No)->info4 = info;
            (*No)->dir = filho;

        } else if(info->codigo > (*No)->info2->codigo && info->codigo < (*No)->info3->codigo){
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = info;

            (*No)->dir = (*No)->centroDir;
            (*No)->centroDir = filho;

        } else if (info->codigo > (*No)->info1->codigo && info->codigo < (*No)->info2->codigo){
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = info;

            (*No)->dir = (*No)->centroDir;
            (*No)->centroDir = (*No)->centro;
            (*No)->centro = filho;

        } else{
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;

            (*No)->dir = (*No)->centroDir;
            (*No)->centroDir = (*No)->centro;
            (*No)->centro = (*No)->centroEsq;
            (*No)->centroEsq = filho;
        }
        (*No)->qtdInfo = 4;
        
    }
}

Arv45 *quebraNo(Arv45 **raiz, Info *info, Info **sobe, Arv45 *filho){
    /**
'     * Realiza a quebra de um nó da árvore 4-5.
     *
     * Esta função é chamada quando um nó da árvore 4-5 está cheio (contém quatro informações) e precisa ser quebrado para manter a árvore balanceada.
     * A função recebe um nó, uma nova informação, um ponteiro para a informação que será "subida" para o nó pai e um nó filho que será o filho direito do novo nó após a quebra.
     * A função realiza a quebra do nó em dois novos nós, mantendo a ordem dos códigos das informações, e retorna o maior nó criado.
     *
     * @param raiz Um ponteiro para o ponteiro do nó pai da árvore 4-5.
     * @param info A nova informação a ser adicionada após a quebra.
     * @param sobe Um ponteiro para a informação que será "subida" para o nó pai.
     * @param filho Um ponteiro para o nó filho direito do novo nó após a quebra.
     *
     * @return Um ponteiro para o maior nó criado após a quebra.
     */

    Arv45 *maiorNo;

    if(info->codigo > (*raiz)->info4->codigo){
        *sobe = (*raiz)->info3;

        maiorNo = criaNo((*raiz)->info4, (*raiz)->centroDir, (*raiz)->dir);
        
        maiorNo->info2 = info;

        maiorNo->centro = filho;

        maiorNo->qtdInfo = 2;

    } else if(info->codigo > (*raiz)->info3->codigo){
        *sobe = (*raiz)->info3;

        maiorNo = criaNo(info, (*raiz)->centroDir, filho);
        
        maiorNo->info2 = (*raiz)->info4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

    } else if(info->codigo > (*raiz)->info2->codigo){
        *sobe = info;
        
        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->centroDir);
        
        maiorNo->info2 = (*raiz)->info4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

    } else if(info->codigo > (*raiz)->info1->codigo){
        *sobe = (*raiz)->info2;

        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->centroDir);
        
        maiorNo->info2 = (*raiz)->info4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

        (*raiz)->info2 = info;
        (*raiz)->centro = filho;

    } else {
        *sobe = (*raiz)->info2;

        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->centroDir);
        
        maiorNo->info2 = (*raiz)->info4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->centro = (*raiz)->centroEsq;
        
        (*raiz)->info1 = info;
        (*raiz)->centroEsq = filho;

    }

    (*raiz)->qtdInfo = 2;
    (*raiz)->centroDir = NULL;
    (*raiz)->dir = NULL;

    (*raiz)->info3 = NULL;
    (*raiz)->info4 = NULL;

    return maiorNo;
    
}

Arv45 *inserir45(Arv45 **raiz, Arv45 *pai, Info **sobe, int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco, int *flag){
    /**
     * Insere uma nova informação na árvore 4-5.
     *
     * Esta função insere uma nova informação na árvore 4-5 e realiza as devidas quebras e atualizações nos nós conforme necessário para manter a árvore balanceada.
     * A função recebe um ponteiro para o ponteiro da raiz da árvore, um ponteiro para o nó pai, um ponteiro para a informação que será "subida" para o nó pai, bem como os dados do novo calçado a ser inserido.
     * A função também recebe um ponteiro "flag" para informar se a inserção foi realizada com sucesso.
     * Se a árvore estiver vazia, a função cria um novo nó raiz com a nova informação.
     * Caso contrário, ela navega pela árvore para encontrar a posição correta para a inserção e realiza as quebras conforme necessário.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore 4-5.
     * @param pai Um ponteiro para o nó pai do nó atual sendo analisado (NULL se o nó atual for a raiz).
     * @param sobe Um ponteiro para a informação que será "subida" para o nó pai em caso de quebra.
     * @param cod O código do novo calçado a ser inserido.
     * @param tam O tamanho do novo calçado a ser inserido.
     * @param qtd A quantidade disponível do novo calçado a ser inserido.
     * @param linha O número da linha em que as informações do novo calçado foram lidas do arquivo.
     * @param tipo A string que representa o tipo do novo calçado a ser inserido.
     * @param marca A string que representa a marca do novo calçado a ser inserido.
     * @param preco O preço do novo calçado a ser inserido.
     * @param flag Um ponteiro para a variável "flag" que indica se a inserção foi realizada com sucesso.
     *
     * @return Um ponteiro para o maior nó criado após as quebras (NULL se não houve quebra).
    */
    Arv45 *maiorNO;
    maiorNO = NULL;

    if(*raiz == NULL){
        *raiz = criaNo(criaInfo(cod, tam, qtd, linha, tipo, marca, preco), NULL, NULL);
        *flag = 1; // informa que a foi inserido
    } else{
        if(ehFolha(*raiz)){
            *flag = 1; // informa que a foi inserido
            if((*raiz)->qtdInfo < 4){
                adicionaNo(raiz, criaInfo(cod, tam, qtd, linha, tipo, marca, preco), NULL);
                maiorNO = NULL;
            } else{
                maiorNO = quebraNo(raiz, criaInfo(cod, tam, qtd, linha, tipo, marca, preco), sobe, NULL);

                if(pai == NULL){
                    *raiz = criaNo(*sobe, *raiz, maiorNO);
                    maiorNO = NULL;
                }
            }
        } else{
            if(cod < (*raiz)->info1->codigo)
                maiorNO = inserir45(&((*raiz)->esq), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);

            else if ((*raiz)->qtdInfo == 1 || ((*raiz)->qtdInfo <= 4 && cod < (*raiz) ->info2->codigo)) {
                maiorNO = inserir45(&((*raiz)->centroEsq), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);
            }
            else if(((*raiz)->qtdInfo == 2)  || ((*raiz)->qtdInfo <= 4 && cod < (*raiz)->info3->codigo)) {
                maiorNO = inserir45(&((*raiz)->centro), *raiz,  sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);
            }
            else if(((*raiz)->qtdInfo == 3) || ((*raiz)->qtdInfo == 4 && cod < (*raiz)->info4->codigo)) {
                maiorNO = inserir45(&((*raiz)->centroDir), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);
            }
            else {
                maiorNO = inserir45(&((*raiz)->dir), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);
            }

            if(maiorNO){
                if((*raiz)->qtdInfo < 4){
                    adicionaNo(raiz, *sobe, maiorNO);
                    maiorNO = NULL;
                } else {
                    maiorNO = quebraNo(raiz, *sobe, sobe, maiorNO);

                    if(pai == NULL){
                        *raiz = criaNo(*sobe, *raiz, maiorNO);
                        maiorNO = NULL;
                    }
                }
            }
        }
    }
    return maiorNO;
}

void imprimirInfo(Info *info){
    /**
     * Imprime as informações de um calçado contidas na estrutura Info.
     *
     * Esta função recebe um ponteiro para a estrutura Info de um calçado e imprime seus campos na saída padrão.
     *
     * @param info Um ponteiro para a estrutura Info do calçado a ser impresso.
     */

    printf("\ncodigo: %d, tamanho: %d, quantidade: %d, linha: %d, tipo: %s, marca: %s, preco: %.2f\n", info->codigo, info->tamanho, info->qtd, info->linha, info->tipo, info->marca, info->preco);
}

void mostrarInfos(Arv45 *raiz, int nivel) {
    /**
     * Mostra as informações contidas nos nós da árvore 4-5.
     *
     * Esta função recebe um ponteiro para a raiz da árvore 4-5 e um nível, e imprime em ordem as informações contidas em todos os nós da árvore.
     * Ela imprime os campos da estrutura Info contidos em cada nó e a quantidade de informações no nó.
     *
     * @param raiz Um ponteiro para a raiz da árvore 4-5.
     * @param nivel O nível atual da árvore (0 na primeira chamada).
    */

    if (raiz != NULL) {
        mostrarInfos(raiz->esq, nivel + 1);

        imprimirInfo(raiz->info1);
        if (raiz->qtdInfo == 2 || raiz->qtdInfo > 2)
            imprimirInfo(raiz->info2);
        if (raiz->qtdInfo == 3 || raiz->qtdInfo > 3)
            imprimirInfo(raiz->info3);
        if (raiz->qtdInfo == 4)
            imprimirInfo(raiz->info4);
        printf("Quantidade Info: %d\n", raiz->qtdInfo);

        mostrarInfos(raiz->centroEsq, nivel + 1);
        mostrarInfos(raiz->centro, nivel + 1);
        mostrarInfos(raiz->centroDir, nivel + 1); 
        mostrarInfos(raiz->dir, nivel + 1);
    }
}


Info *buscarProduto(Arv45 *raiz, int cod, int *cont){
    /**
     * Busca um produto na árvore 4-5 pelo código.
     *
     * Esta função busca um produto na árvore 4-5 com base no código do produto fornecido.
     * Ela retorna um ponteiro para a estrutura Info do produto, caso encontrado, ou NULL caso o produto não seja encontrado.
     * A função realiza uma busca recursiva pela árvore, comparando o código do produto com os códigos das informações em cada nó.
     *
     * @param raiz Um ponteiro para a raiz da árvore 4-5.
     * @param cod O código do produto a ser buscado.
     *
     * @return Um ponteiro para a estrutura Info do produto encontrado ou NULL se o produto não for encontrado.
     */
    Info *achou = NULL;

    if(raiz){
        *cont+=1;
        if(cod == raiz->info1->codigo)
            achou = raiz->info1;

        if(raiz->qtdInfo == 2){
            if(cod == raiz->info2->codigo)
                achou = raiz->info2;

        } 
        if(raiz->qtdInfo == 3){
            if(cod == raiz->info3->codigo)
                achou = raiz->info3;

        }
        if(raiz->qtdInfo == 4){
            if(cod == raiz->info4->codigo)
                achou = raiz->info4;

        }
        if(achou == NULL){
            if(cod < raiz->info1->codigo)
                achou = buscarProduto(raiz->esq, cod, cont);

            else if(raiz->qtdInfo == 1 || (raiz->qtdInfo <= 4 && cod < raiz->info2->codigo)) {
                achou = buscarProduto(raiz->centroEsq, cod, cont);
            }
            else if((raiz->qtdInfo == 2)  || (raiz->qtdInfo <= 4 && cod < raiz->info3->codigo)) {
                achou = buscarProduto(raiz->centro, cod, cont);
            }
            else if((raiz->qtdInfo == 3) || (raiz->qtdInfo == 4 && cod < raiz->info4->codigo)) {
                achou = buscarProduto(raiz->centroDir, cod, cont);
            }
            else {
                achou = buscarProduto(raiz->dir, cod, cont);
            }
        }
    }
    return achou;
}


void atualizarArquivo(Info *no) {
    /**
     * Atualiza as informações de um produto no arquivo.
     *
     * Esta função recebe um ponteiro para a estrutura Info de um produto e atualiza as informações desse produto no arquivo "lojaCalcados.txt".
     * A função abre o arquivo, localiza a linha correspondente ao produto pelo número de linha armazenado na estrutura Info e sobrescreve os dados do produto no arquivo.
     *
     * @param no Um ponteiro para a estrutura Info do produto a ser atualizado.
    */

    char nomeArquivo[] = "lojaCalcados.txt";
    FILE *arquivo;
    int linhaAtual = 1;
    char linha[100];

    arquivo = fopen(nomeArquivo, "r+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    } else {
        int flag = 1;
        // Percorre o arquivo até a linha desejada
        while (linhaAtual < no->linha) {
            if (fgets(linha, sizeof(linha), arquivo) == NULL) {
                printf("Linha alvo fora do alcance do arquivo.\n");
                fclose(arquivo);
                flag = 0;
            }
            linhaAtual++;
        }

        if (flag) {
            fseek(arquivo, -1, SEEK_CUR); // Volta 1 caractere para sobrescrever a quebra de linha
            // Código, tamanho, quantidade, tipo, marca, preco.
            fprintf(arquivo, "\n%d %d %d %s %s %.2f", no->codigo, no->tamanho, no->qtd, no->tipo, no->marca, no->preco);
            fclose(arquivo);
        }
    }
}


void vender(Arv45 *raiz, int qtd, int cod, char *resultado) {
    /**
     * Realiza a venda de um produto da árvore 4-5.
     *
     * Esta função realiza a venda de um produto da árvore 4-5 com base no código do produto fornecido e na quantidade desejada.
     * Ela recebe um ponteiro para a raiz da árvore, a quantidade desejada para venda, o código do produto a ser vendido e um ponteiro para uma string "resultado".
     * O resultado da venda é armazenado na string "resultado" para ser exibido posteriormente.
     * A função busca o produto na árvore utilizando a função "buscarProduto" e atualiza a quantidade do produto após a venda utilizando a função "atualizarArquivo".
     *
     * @param raiz Um ponteiro para a raiz da árvore 4-5.
     * @param qtd A quantidade desejada para venda.
     * @param cod O código do produto a ser vendido.
     * @param resultado Um ponteiro para uma string que armazenará o resultado da venda.
     */
    Info *aux;
    int cont=0;

    aux = buscarProduto(raiz, cod, &cont);

    if (aux != NULL) {
        if (qtd > aux->qtd) {
            char str_numero[100];
            snprintf(str_numero, sizeof(str_numero), "%d", aux->qtd);
            strcpy(resultado, "Nao e possivel comprar pois nao temos essa quantidade de produto. Estao disponiveis somente ");
            strcat(resultado, str_numero);
        } else if (qtd > aux->qtd && aux->qtd != 0) {
            aux->qtd = 0;
            atualizarArquivo(aux);
            strcpy(resultado, "Compra realizada com sucesso. Estoque esgotado.\n");
        } else if (qtd != 0 && aux->qtd != 0) {
            aux->qtd -= qtd;
            atualizarArquivo(aux);
            strcpy(resultado, "Compra realizada com sucesso.\n");
        } else {
            if (qtd == 0) {
                strcpy(resultado, "Voce digitou 0, ou seja, nao e possivel comprar.\n");
            } else {
                strcpy(resultado, "Nao e possivel comprar pois o produto nao esta disponivel.\n");
            }
        }
    } else {
        strcpy(resultado, "Produto nao encontrado.\n");
    }
}

// Função para repor o estoque de um produto
void reporProduto(Arv45 *raiz) {
    /**
     * Repõe o estoque de um produto da árvore 4-5.
     *
     * Esta função permite repor o estoque de um produto da árvore 4-5.
     * Ela exibe as informações de todos os produtos da árvore utilizando a função "mostrarInfos".
     * Em seguida, o usuário seleciona um produto pelo código e insere a quantidade a ser adicionada ao estoque.
     * A função busca o produto na árvore utilizando a função "buscarProduto" e atualiza a quantidade do produto após a reposição utilizando a função "atualizarArquivo".
     *
     * @param raiz Um ponteiro para a raiz da árvore 4-5.
     */
    mostrarInfos(raiz, 0);
    int cod, qtd, opcompra, cont=0;
    Info *aux;

    printf("Escolha o produto pelo codigo: ");
    scanf("%d", &cod);

    aux = buscarProduto(raiz, cod, &cont);

    if (aux != NULL) {
        printf("Quantidade de produtos a serem adicionados: ");
        scanf("%d", &qtd);

        if (qtd > 0) {
            aux->qtd += qtd;
            atualizarArquivo(aux);
            printf("Estoque do produto atualizado com sucesso.\n");
        } else {
            printf("Quantidade de produto inferior ou igual a zero. Nenhum item foi adicionado ao estoque.\n");
        }
    } else {
        printf("Produto nao encontrado.\n");
    }
}

int quantidadeLinhas() {
    /**
     * Obtém a quantidade de linhas em um arquivo.
     *
     * Esta função abre o arquivo "lojaCalcados.txt" e conta a quantidade de linhas presentes no arquivo.
     * A função retorna o número total de linhas contadas no arquivo.
     *
     * @return O número total de linhas no arquivo "lojaCalcados.txt".
     */

    FILE *arquivo;
    arquivo = fopen("lojaCalcados.txt", "r");
    char tipo[100], marca[100], linha[250];
    int qtdLinha = 1;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        ++qtdLinha;
    }

    fclose(arquivo);
    return qtdLinha;
}


void adicionarCalcados(Arv45 **raiz, Info **sobe, int cod, int tam, int qtd, char *tipo, char *marca, float preco, char *resultado) {
    /**
     * Adiciona novos calçados ao estoque na árvore 4-5 e no arquivo.
     *
     * Esta função permite adicionar novos calçados ao estoque da árvore 4-5.
     * Ela recebe um ponteiro para a raiz da árvore, um ponteiro para a informação que será "subida" para o nó pai em caso de quebra, além dos dados do novo calçado.
     * A função adiciona o novo calçado à árvore utilizando a função "inserir45" e também o insere no arquivo "lojaCalcados.txt".
     * O resultado da inserção é armazenado na string "resultado" para ser exibido posteriormente.
     *
     * @param raiz Um ponteiro para o ponteiro da raiz da árvore 4-5.
     * @param sobe Um ponteiro para a informação que será "subida" para o nó pai em caso de quebra.
     * @param cod O código do novo calçado a ser inserido.
     * @param tam O tamanho do novo calçado a ser inserido.
     * @param qtd A quantidade disponível do novo calçado a ser inserido.
     * @param tipo A string que representa o tipo do novo calçado a ser inserido.
     * @param marca A string que representa a marca do novo calçado a ser inserido.
     * @param preco O preço do novo calçado a ser inserido.
     * @param resultado Um ponteiro para uma string que armazenará o resultado da inserção.
     */
    
    FILE *arquivo;

    arquivo = fopen("lojaCalcados.txt", "a");

    if (arquivo == NULL) {
        strcpy(resultado, "Erro ao abrir o arquivo.\n");
    } else {
        int flag = 0, qtdLinha = 1;

        qtdLinha = quantidadeLinhas();

        inserir45(raiz, NULL, sobe, cod, tam, qtd, qtdLinha, tipo, marca, preco, &flag);

        if (flag == 1) {
            fprintf(arquivo, "\n%d %d %d %s %s %.2f", cod, tam, qtd, tipo, marca, preco);
            strcpy(resultado, "\nO produto foi inserido com sucesso.\n");
        } else {
            strcpy(resultado, "\nO produto nao foi inserido. Codigo de produto ja existe.\n");
        }

        fclose(arquivo);
    }
}
