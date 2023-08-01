#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "exer2.h"

int main() {
    srand(time(NULL));

    Curso  *arvoreCursos;
    arvoreCursos = NULL;

    Curso *aux;
    aux = NULL;

    int cod_curso, num_semanas, qtd_blocos, cod_disc, bloco_curso, carga_horaria, bloco_dis;
    char nome_curso[100], nome_dis[100];

    int opcao = -1;

    while(opcao != 0){
        printf("\n");
        printf("0 - Encerrar\n"
        "1 - Inserir curso\n"
        "2 - Inserir disciplina\n"
        "3 - Imprimir arvore de cursos\n"
        "4 - Imprimir dados de um curso\n"
        "5 - Imprimir cursos com a mesma quantidade de blocos\n"
        "6 - Imprimir arvore de disciplinas pelo codigo\n"
        "7 - Imprimir dados de um disciplina\n"
        "8 - Imprimir as disciplinas de um determinado bloco\n"
        "9 -Imprimir disciplinas com a mesma carga horária\n"
        "10 - Excluir uma disciplina\n"
        "11 - Excluir um curso\n"
        "Digite a opcao: ");
        scanf("%d", &opcao);
        switch (opcao){
        case 0:
            break;

        case 1:
            printf("Digite o codigo do curso: ");
            scanf("%d", &cod_curso);
            printf("Nome do curso: ");
            scanf("%s", nome_curso);
            printf("Quantidade de blocos: ");
            scanf("%d", &qtd_blocos);
            printf("Numero de semanas: ");
            scanf("%d", &num_semanas);
            insrrCurs(&arvoreCursos, criarNoCurso(cod_curso, nome_curso, qtd_blocos, num_semanas));
            break;
            
        case 2:
            printf("Digite o codigo do curso: ");
            scanf("%d", &cod_curso);
            aux = buscarCursoPorCodigo(arvoreCursos, cod_curso);
            if (aux != NULL) {
                printf("Digite o codigo da disciplina: ");
                scanf("%d", &cod_disc);
                printf("Nome da disciplina: ");
                scanf("%s", nome_dis);
                printf("Bloco da disciplina: ");
                scanf("%d", &bloco_dis);
                printf("Carga hoararia da disciplina: ");
                scanf("%d", &carga_horaria);
                inserirDis(&aux->arvoreDisciplina, criarNoDisciplina(cod_disc, nome_dis, bloco_dis, carga_horaria));
            } else {
                printf("Curso nao encontrado :/");
            }
            break;

        case 3:
            // (1) Imprimir a árvore de cursos em ordem crescente pelo código do curso;
            imprimirCursos(arvoreCursos);
            
            break;
        
        case 4:
            // (2)Imprimir os dados de um curso dado o código do mesmo;
            printf("Digite o codigo do curso que deseja imprimir: ");
            scanf("%d", &cod_curso);
            imprimirCursoPeloCodigo(arvoreCursos, cod_curso);
            break;

        case 5:
            // (3)Imprimir todos os cursos com a mesma quantidade de blocos, onde o usuário informe a quantidade de blocos;
            printf("Digite a quantidade de blocos: ");
            scanf("%d", &qtd_blocos);
            imprimirCursosPorBlocosIguais(arvoreCursos, qtd_blocos); 
            
            break;

        case 6:
             //(4)Imprimir a árvore de disciplinas em ordem crescente pelo código das disciplinas dado o código do curso;
            printf("Digite o codigo do curso: ");
            scanf("%d", &cod_curso);
            imprimirDisciplinasPorCodigoCurso(arvoreCursos, cod_curso); 
             
            break;

        case 7:
            // (5)Imprimir os dados de uma disciplina dado o código dela e do curso ao qual ela pertence;
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &cod_disc);
            printf("Digite o codigo do curso: ");
            scanf("%d", &cod_curso);
            imprimirDadosDisciplinasDadoCodigoCurso(arvoreCursos, cod_curso, cod_disc);
            break;

        case 8:
            // 6)Imprimir as disciplinas de um determinado bloco de um curso, dado o bloco e o código do curso;
            printf("Digite o bloco do curso: ");
            scanf("%d", &bloco_curso);
            printf("Digite o codigo do curso: ");
            scanf("%d", &cod_curso);
            imprimirDisciplinasBloco(arvoreCursos, bloco_curso, cod_curso); 
            break;

        case 9:
            // (7) Imprimir todas as disciplinas de um determinado curso com a mesma carga horária, onde o código do curso e a carga horária devem ser informadas pelo usuário;
            printf("Digite o codigo do curso: ");
            scanf("%d", &cod_curso);
            printf("Digite a carga horaria: ");
            scanf("%d", &carga_horaria);
            imprimirDisCargaHoraria(arvoreCursos, cod_curso, carga_horaria); 
            break;

        case 10:
            // (8) Excluir uma disciplina dado o código da disciplina e o código do curso;
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &cod_disc);
            printf("Digite o codigo do curso: ");
            scanf("%d", &cod_curso);
            buscarCursoParaRemover(&arvoreCursos, cod_disc, cod_curso);
            break;

        case 11:
            // (9)Excluir um curso dado o código do mesmo, desde que não tenha nenhuma disciplina cadastrada para aquele curso
            printf("Digite o codigo do curso: ");
            scanf("%d", &cod_curso);
            removerCurso(&arvoreCursos, cod_curso);
            break;

        default:
        printf("Essa opcao nao existe\n");
            break;
        }
    }
    return 0;
}