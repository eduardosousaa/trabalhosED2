#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <windows.h>

#define N 4 // Número de discos

void imprime_configuracoes(int **configuracoes, int tamanho);
void para_base3(int num, int *arr);
int mexeu(int **configuracoes, int i, int j);
int encontra_disc_movido(int **configuracoes, int i, int j);
int mov_valido(int disco_movido, int **configuracoes, int j);
int **cria_matriz_adjacencia(int tamanho, int **configuracoes);
void imprime_menor_caminho_dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final);
int dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final);
double mede_tempo_dijkstra(int **matriz_adjacencia, int *config_inicial, int *config_final);
void imprime_menor_caminho_bellman_ford(int **matriz_adjacencia, int *config_inicial, int *config_final);
int bellman_ford(int **matriz_adjacencia, int *config_inicial, int *config_final);
double mede_tempo_bellman_ford(int **matriz_adjacencia, int *config_inicial, int *config_final);
void imprimir_matriz_adjacencia(int **matriz, int tamanho);
int validar_configuracoes(int *config_inicial, int *config_final);