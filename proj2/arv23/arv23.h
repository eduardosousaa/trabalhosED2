// Definição da lista encadeada de números de linha
typedef struct lista{
    int num_linha;
    struct lista *prox;
}Lista;

// Info vai conter a palavra e a lista de números das linha
typedef struct info{
    char *palavra;
    Lista *num_lista;
}Info;

typedef struct arv23{
    Info *info1, *info2;
    int numInfo;
    struct arv23 *esq, *centro, *dir;
}Arv23;

Info *criaInfo(char *palavra, Lista *lista, int linha);
Arv23 *criaNo(Info *info, Arv23 *noEsq, Arv23 *noCentro, Arv23 *noDir);
void adicionaNo(Arv23 **raiz, Info *info, Arv23 *novo);
int ehFolha(Arv23 *raiz);
Arv23 *quebraNo(Arv23 **raiz, Arv23 *filho, Info *info, Info **infoSobe);
void inserirLinha(Lista **no, int linha);
Arv23 *inserirPalavra(Arv23  **raiz, char *palavra, int num_linha, Arv23 *pai, Info **infoSobe, int *inseriu);
void imprimirEmOrdem(Arv23 *raiz, int cont);
void imprimirLinhas(Lista *no, int cont);
int lerArquivoTexto(Arv23 **raiz, const char *nome_arquivo);
int buscarPalavra(Arv23 *raiz, char palavra[], Arv23 **noEncontrado);
void MaiorInfoRemoveEsq(Arv23 **raiz, Arv23 **maiorPai, Arv23 **maiorInfoRemove, int infoLocal, int linha);
void redistribuiArv(Arv23 **raiz, Arv23 **pai);
int removerArv23(Arv23 **pai, Arv23 **raiz, char *palavra, int linha);
void buscar_palavra(Arv23 *raiz, char palavra[], int *resultado, int *cont);
int remvLinhs(Lista** lista, int valor);