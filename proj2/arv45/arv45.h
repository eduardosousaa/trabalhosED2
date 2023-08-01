#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> //usado para transformar as letras da palavra em minusculas
// #include <windows.h>

//código,  tipo, marca, tamanho, quantidade e preço.
typedef struct info{
    int codigo, tamanho, qtd, linha;
    char *tipo, *marca;
    float preco;
}Info;

typedef struct arv45{
    Info *info1, *info2, *info3, *info4;
    int qtdInfo;

    struct arv45 *esq, *centroEsq, *centro, *centroDir, *dir;
}Arv45;

void lerArquivo(Arv45 **raiz, Info **sobe);
Info *criaInfo(int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco);
Arv45 *criaNo(Info *info, Arv45 *noEsq, Arv45 *noCentroEsq);
int ehfolha(Arv45 *no);
void adicionaNo(Arv45 **no, Info *info, Arv45 *filho);
Arv45 *quebraNo(Arv45 **raiz, Info *info, Info **sobe, Arv45 *filho);
Arv45 *inserir45(Arv45 **raiz, Arv45 *pai, Info **sobe, int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco, int *flag);
void imprimirInfo(Info *info);
void mostrarInfos(Arv45 *raiz, int nivel);
void atualizarArquivo(Info *no);
void vender(Arv45 *raiz, int qtd, int codigo, char *resultado);
void reporProduto(Arv45 *raiz);
void reporProduto(Arv45 *raiz);
int quantidadeLinhas();
void adicionarCalcados(Arv45 **raiz, Info **sobe, int codigo, int tamanho, int qtd, char *tipo, char *marca, float preco, char *resultado);
Info *buscarProduto(Arv45 *raiz, int cod, int *cont);
