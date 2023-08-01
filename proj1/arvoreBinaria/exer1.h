typedef struct disciplina {
    int codigo_disciplina;
    char nome_disciplina[50];
    int bloco;
    int carga_horaria;
    struct disciplina *esq, *dir;
}Disciplina;

typedef struct curso {
    int codigo_curso;
    char nome_curso[50];
    int quantidade_blocos;
    int num_semanas;
    struct disciplina *arvoreDisciplina;
    struct curso *esq, *dir;
}Curso;

void embaralhar(int *array, int tamanho);
int sortearNumero();

Disciplina *criarNoDisciplina(int codigo, char nome[], int bloco, int carga);
void inserirDisciplina(Disciplina **raiz, Disciplina *noDis);
void imprimirDisciplinas(Disciplina *raiz);
int imprimirDisciplinasPorCodigoCurso(Curso *raiz, int codigo_curso);
void procuraDisciplina(Disciplina *disciplina, int codigo_disciplina);
void imprimirDadosDisciplinasDadoCodigoCurso(Curso *raiz, int codigo_curso, int codigo_disciplina);
void procuraDisciplina2(Disciplina *disciplina, int bloco, int codigo_disciplina);
void imprimirDisciplinasBloco(Curso *raiz, int bloco, int codigo_curso);
void procuraDisciplina3(Disciplina *disciplina, int carga_horaria, int codigo_disciplina);
void imprimirDisCargaHoraria(Curso *raiz, int codigo_curso, int carga_horaria);
void buscarfolha(Disciplina **ultimo, Disciplina *filho);
void removerDisciplina(Disciplina **raiz,int codigo);
void buscarCursoParaRemover(Curso **raiz, int codigo_disciplina, int codigo);

Curso *criarNoCurso(int codigo, char nome_curso[], int quantidade_blocos, int num_semanas);
void inserirCurso(Curso **raiz, Curso *curso);
Curso *buscarCursoPorCodigo(Curso *raiz, int codigo);
void imprimirCursos(Curso *raiz);
void imprimirCursoPeloCodigo(Curso *raiz, int codigo_curso);
void imprimirCursosPorBlocosIguais(Curso *raiz, int quant_blocos);
void buscarfolhaCurso(Curso **filho1, Curso *filho2);
Curso *enderecoFilho(Curso *raiz);
void removerCurso(Curso **raiz, int codigo);