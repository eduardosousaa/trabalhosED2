#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "exer2.h"

void embaralhar(int *array, int tamanho) {
    srand(time(NULL));

    for (int i = tamanho - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int sortearNumero() {
    // Array com os números disponíveis
    int numeros[] = {12, 15, 20, 22, 25, 30};

    // Número total de elementos no array
    int numNumeros = sizeof(numeros) / sizeof(numeros[0]);

    // Inicializar o gerador de números aleatórios com base no tempo atual
    srand(time(NULL));

    // Sortear um índice aleatório para selecionar um número
    int indice = rand() % numNumeros;

    // Armazenar o número selecionado
    int numeroSorteado = numeros[indice];

    // Retornar o número sorteado
    return numeroSorteado;
}