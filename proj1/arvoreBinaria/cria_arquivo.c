#include <stdio.h>
#include <stdlib.h>

#define TAM 1000

int main() {
    FILE *arquivo;
    int vetor[10];
    int contador = 0;
    int numero;

    // Abrir o arquivo para leitura
    arquivo = fopen("arquivo_ordenado.txt", "w");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    for(int i = 1; i <= TAM; i++)
        fprintf(arquivo, "%d\n", i);

    // Fechar o arquivo
    fclose(arquivo);

    return 0;
}