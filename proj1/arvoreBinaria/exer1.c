#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "exer1.h"

Disciplina *criarNoDisciplina(int codigo, char nome[], int bloco, int carga) {
    // Essa funcao recebe os parametros: codigo:inteiro, nome:string, bloco:inteiro e carga:inteiro.
    // Ela vai alocar um espaco de memoria para a disciplina, em seguida atribuir os valores passados 
    // por parametro para cada area da struct.
    // Por fim vai retornar a struct que corresponde a nova disciplina criada.
    Disciplina *new = (Disciplina*) malloc (sizeof(Disciplina));
    new->codigo_disciplina = codigo;
    strcpy(new->nome_disciplina, nome);
    new->bloco = bloco;
    new->carga_horaria = carga;
    new->esq = NULL;
    new->dir = NULL;
    return new;
}


void inserirDisciplina(Disciplina **raiz, Disciplina *noDis) {
    // Essa funcao recebe a struct com o curso apontando para as disciplinas e imprime os dados das disciplinas do curso
    if (*raiz == NULL) {
        *raiz = noDis;
    } else if (noDis->codigo_disciplina < (*raiz)->codigo_disciplina) {
        inserirDisciplina(&((*raiz)->esq), noDis);
    } else {
        inserirDisciplina(&((*raiz)->dir), noDis);
    }
}


void imprimirDisciplinas(Disciplina *raiz) {
    // Essa funcao recebe a struct com o curso apontando para as disciplinas e imprime os dados das disciplinas do curso
    if (raiz != NULL){
        imprimirDisciplinas(raiz->esq);
        printf("\nDados da disciplina:\nCodigo: %d\nNome: %s\nBloco: %d\nCarga horaria: %d\n\n", raiz->codigo_disciplina, raiz->nome_disciplina, raiz->bloco, raiz->carga_horaria);
        imprimirDisciplinas(raiz->dir);
    }
}


// void imprimirDisciplinasPorCodigoCurso(Curso *raiz, int codigo_curso) {
//     if (raiz != NULL) {
//         imprimirDisciplinasPorCodigoCurso(raiz->esq, codigo_curso);

//         if (raiz->codigo_curso == codigo_curso) {
//             imprimirDisciplinas(raiz->arvoreDisciplina);
//         } 

//         imprimirDisciplinasPorCodigoCurso(raiz->dir, codigo_curso);
//     }
// }

// void imprimirDisciplinasPorCodigoCurso(Curso *raiz, int codigo_curso) {
//     // Essa funcao tem como parametros: raiz:struct e codigo_curso:inteiro.
//     if (raiz != NULL) {
//         if(codigo_curso < raiz->codigo_curso)
//             imprimirDisciplinasPorCodigoCurso(raiz->esq, codigo_curso);

//         if (raiz->codigo_curso == codigo_curso)
//             imprimirDisciplinas(raiz->arvoreDisciplina);
        
//         if(codigo_curso > raiz->codigo_curso)
//             imprimirDisciplinasPorCodigoCurso(raiz->dir, codigo_curso);
//     }
// }


int imprimirDisciplinasPorCodigoCurso(Curso *raiz, int codigo_curso) {
    // Essa funcao tem como parametros: raiz:struct e codigo_curso:inteiro.
    // Ela vai percorrer a arvore ate acha o codigo do curso que equivale ao valor passado ou ate encontrar NULL.
    // Se o curso for encontrado, a funcao "imprimirDisciplinas" vai ser chamada e a variavel que verifica se 
    // o curso foi encontrado recebe 1.
    // return: encontrou:inteiro.

    int encontrou = 0;

    if (raiz != NULL) {
        if(codigo_curso < raiz->codigo_curso)
            encontrou = imprimirDisciplinasPorCodigoCurso(raiz->esq, codigo_curso);

        if (raiz->codigo_curso == codigo_curso){
            imprimirDisciplinas(raiz->arvoreDisciplina);
            encontrou = 1;
        }
        
        if(codigo_curso > raiz->codigo_curso)
            encontrou = imprimirDisciplinasPorCodigoCurso(raiz->dir, codigo_curso);

        return (encontrou);
    }
}

void procuraDisciplina(Disciplina *disciplina, int codigo_disciplina) {
    // Parametros:
    //  disciplina:struct
    //  codigo_disciplina:inteiro
    // Essa funcao vai procurar uma disciplina pelo codigo passado e vai imprimir seus dados na tela
    if (disciplina != NULL){
        if (disciplina->codigo_disciplina == codigo_disciplina){
            printf("\nDados da disciplina:\nCodigo: %d\nNome: %s\nBloco: %d\nCarga horaria: %d\n\n", disciplina->codigo_disciplina, disciplina->nome_disciplina, disciplina->bloco, disciplina->carga_horaria);
        } else {
            if (codigo_disciplina < disciplina->codigo_disciplina){
                procuraDisciplina(disciplina->esq, codigo_disciplina);
            } else {
                procuraDisciplina(disciplina->dir, codigo_disciplina);
            }
        }
    }
}

void imprimirDadosDisciplinasDadoCodigoCurso(Curso *raiz, int codigo_curso, int codigo_disciplina){
    // Parametros:
    //  raiz:struct
    //  codigo_curso:inteiro
    //  codigo_disciplina:inteiro
    // Esta funcao vai imprimir os dados de uma disciplina dado o código dela e do curso ao qual ela pertence;
    if (raiz != NULL){
        if (raiz->codigo_curso == codigo_curso){
            procuraDisciplina(raiz->arvoreDisciplina, codigo_disciplina);
            // imprimirDisciplinas(raiz->arvoreDisciplina);
        } else {
            if (codigo_curso < raiz->codigo_curso){
                imprimirDadosDisciplinasDadoCodigoCurso(raiz->esq, codigo_curso, codigo_disciplina);
            } else {
                imprimirDadosDisciplinasDadoCodigoCurso(raiz->dir, codigo_curso, codigo_disciplina);
            }
        }
    }
}

void procuraDisciplina2(Disciplina *disciplina, int bloco, int codigo_disciplina) {
    if (disciplina != NULL){
        if (disciplina->bloco == bloco){
            printf("\nDados da disciplina:\nCodigo: %d\nNome: %s\nBloco: %d\nCarga horaria: %d\n\n", disciplina->codigo_disciplina, disciplina->nome_disciplina, disciplina->bloco, disciplina->bloco);
        }
        procuraDisciplina2(disciplina->esq, bloco, codigo_disciplina);
        procuraDisciplina2(disciplina->dir, bloco, codigo_disciplina);
    }
}


// Imprimir as disciplinas de um determinado bloco de um curso, dado o bloco e o código do curso;
void imprimirDisciplinasBloco(Curso *raiz, int bloco, int codigo_curso) {
    if (raiz != NULL){
        if (raiz->codigo_curso == codigo_curso){
            procuraDisciplina2(raiz->arvoreDisciplina, bloco, raiz->arvoreDisciplina->codigo_disciplina);
        } else {
            if (codigo_curso < raiz->codigo_curso){
                imprimirDisciplinasBloco(raiz->esq, bloco, codigo_curso);
            } else {
                imprimirDisciplinasBloco(raiz->dir, bloco, codigo_curso);
            }
        }
    }
}

void procuraDisciplina3(Disciplina *disciplina, int carga_horaria, int codigo_disciplina) {
    if (disciplina != NULL){
        if (disciplina->carga_horaria == carga_horaria){
            printf("\nDados da disciplina:\nCodigo: %d\nNome: %s\nBloco: %d\nCarga horaria: %d\n\n", disciplina->codigo_disciplina, disciplina->nome_disciplina, disciplina->bloco, disciplina->carga_horaria);
        }
        procuraDisciplina3(disciplina->esq, carga_horaria, codigo_disciplina);
        procuraDisciplina3(disciplina->dir, carga_horaria, codigo_disciplina);
    }
}

// Imprimir todas as disciplinas de um determinado curso com a mesma carga horária, onde o código do curso e a carga horária devem ser informadas pelo usuário;
void imprimirDisCargaHoraria(Curso *raiz, int codigo_curso, int carga_horaria) {
    if (raiz != NULL){
        if (raiz->codigo_curso == codigo_curso){
            procuraDisciplina3(raiz->arvoreDisciplina, carga_horaria, raiz->arvoreDisciplina->codigo_disciplina);
        } else {
            if (codigo_curso < raiz->codigo_curso){
                imprimirDisCargaHoraria(raiz->esq, codigo_curso, carga_horaria);
            } else {
                imprimirDisCargaHoraria(raiz->dir, codigo_curso, carga_horaria);
            }
        }
    }
}


Curso *criarNoCurso(int codigo, char nome_curso[], int quantidade_blocos, int num_semanas) {
    Curso *new = (Curso*) malloc (sizeof(Curso));
    new->codigo_curso = codigo;
    strcpy(new->nome_curso, nome_curso);
    new->quantidade_blocos = quantidade_blocos;
    new->num_semanas = num_semanas;
    new->arvoreDisciplina = NULL;
    new->esq = NULL;
    new->dir = NULL;
    return new;
}

void inserirCurso(Curso **raiz, Curso *curso) {
    if (*raiz == NULL)
        *raiz = curso;
    else if (curso->codigo_curso < (*raiz)->codigo_curso){
        inserirCurso(&((*raiz)->esq), curso);
    } else {
        inserirCurso(&((*raiz)->dir), curso);
    }
}

Curso *buscarCursoPorCodigo(Curso *raiz, int codigo) {
    if (raiz == NULL || raiz->codigo_curso == codigo) {
        return raiz;
    }

    if (codigo < raiz->codigo_curso) {
        return buscarCursoPorCodigo(raiz->esq, codigo);
    } else {
        return buscarCursoPorCodigo(raiz->dir, codigo);
    }
}


void imprimirCursos(Curso *raiz) {
    if (raiz != NULL){
        imprimirCursos(raiz->esq);
        printf("\nDados do curso:\nCodigo: %d\nNome: %s\nQuantidade de blocos: %d\nNumero de semanas: %d\n\n", raiz->codigo_curso, raiz->nome_curso, raiz->quantidade_blocos, raiz->num_semanas);
        // if(raiz->arvoreDisciplina)
        //     imprimirDisciplinas(raiz->arvoreDisciplina);
        imprimirCursos(raiz->dir);
    }
}

void imprimirCursoPeloCodigo(Curso *raiz, int codigo_curso) {
    if (raiz != NULL){
        if (raiz->codigo_curso == codigo_curso){
            //  printf("\nDados do curso:\nCodigo: %d\nNome: %s\nQuantidade de blocos: %d\nNumero de semanas: %d\n\n", raiz->codigo_curso, raiz->nome_curso, raiz->quantidade_blocos, raiz->num_semanas);
        } else {
            if (codigo_curso < raiz->codigo_curso){
                imprimirCursoPeloCodigo(raiz->esq, codigo_curso);
            } else {
                imprimirCursoPeloCodigo(raiz->dir, codigo_curso);
            }
        }
    }
}


void imprimirCursosPorBlocosIguais(Curso *raiz, int quant_blocos) {
    if (raiz != NULL){
        if (raiz->quantidade_blocos == quant_blocos){
            printf("\nDados do curso:\nCodigo: %d\nNome: %s\nQuantidade de blocos: %d\nNumero de semanas: %d\n\n", raiz->codigo_curso, raiz->nome_curso, raiz->quantidade_blocos, raiz->num_semanas);
        }
        imprimirCursosPorBlocosIguais(raiz->esq, quant_blocos);
        imprimirCursosPorBlocosIguais(raiz->dir, quant_blocos);
    }
}

// Usada para encontrar a folha mais à direita em uma subárvore
// Até encontrar o último nó à direita e atribuindo o novo nó folha a esse local.
void buscarfolha(Disciplina **ultimo, Disciplina *filho){
    if(*ultimo){
        buscarfolha(&((*ultimo)->dir), filho);
    }
    else {
        (*ultimo) = filho;
    }
}


void removerDisciplina(Disciplina **raiz,int codigo){
    if (*raiz != NULL){
        Disciplina *aux;
        if((*raiz)->codigo_disciplina == codigo){
            // Se o nó não tem filhos
            if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
                free(*raiz);
                (*raiz) = NULL;
            }
            // Se o nó tem apenas um filho
            else if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
                Disciplina *endFilho;
                if((*raiz)->esq != NULL){
                    aux = *raiz;
                    endFilho = (*raiz)->esq;
                    *raiz = endFilho;
                    free(aux);
                    aux = NULL;
                }
                else{
                    aux = *raiz;
                    endFilho = (*raiz)->dir;
                    *raiz = endFilho;
                    free(aux);
                    aux = NULL;
                }
            }
            else{
                Disciplina *filho;
                aux = *raiz;
                filho = (*raiz)->esq;
                // encontrar o nó folha mais à direita da subárvore esquerda, que será movido para o lugar do nó a ser removido.
                buscarfolha(&((*raiz)->esq), (*raiz)->dir);
                *raiz = filho;
                free(aux);      
                aux = NULL;          
            }
        }
        else if (codigo < (*raiz)->codigo_disciplina){
            removerDisciplina(&(*raiz)->esq,codigo);
        }
        else {
            removerDisciplina(&(*raiz)->dir,codigo);
        }

    }
}

void buscarCursoParaRemover(Curso **raiz, int codigo_disciplina, int codigo){
    if (*raiz != NULL){
        if ((*raiz)->codigo_curso == codigo){
            removerDisciplina(&(*raiz)->arvoreDisciplina, codigo_disciplina);
        }
        else if (codigo < (*raiz)->codigo_curso){
            buscarCursoParaRemover(&(*raiz)->esq, codigo_disciplina, codigo);
        }
        else {
            buscarCursoParaRemover(&(*raiz)->dir, codigo_disciplina, codigo);
        }
    }
}

void buscarfolhaCurso(Curso **filho1, Curso *filho2){
    if(*filho1){
        buscarfolhaCurso(&((*filho1)->dir), filho2);
    }
    else {
        (*filho1) = filho2;
    }
}

Curso *enderecoFilho(Curso *raiz) {
    Curso *aux;
    if (raiz->dir) {
        aux = raiz->dir;
    } else {
        aux = raiz->esq;
    }
    return aux;
}

void removerCurso(Curso **raiz, int codigo){
    if (*raiz != NULL){
        Curso *aux;
        if((*raiz)->codigo_curso == codigo){
            //Verifica se o curso não tem discciplinas para poder remover
            if ((*raiz)->arvoreDisciplina == NULL){
                if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
                free(*raiz);
                (*raiz) = NULL;
            }
            else if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
                Curso *endFilho;
                endFilho = enderecoFilho(*raiz); //Retorna a raiz da esquerda ou da direita
                aux = *raiz;
                *raiz = endFilho;
                free(aux);
                aux = NULL;
            } else { // Dois Filhos
                Curso *filho;
                aux = *raiz;
                filho = (*raiz)->esq;
                buscarfolhaCurso(&((*raiz)->esq), (*raiz)->dir);
                *raiz = filho;
                free(aux);      
                aux = NULL;          
            }
            }
        }
        else if (codigo < (*raiz)->codigo_curso){
            removerCurso(&(*raiz)->esq,codigo);
        }
        else {
            removerCurso(&(*raiz)->dir,codigo);
        }
    }
}


