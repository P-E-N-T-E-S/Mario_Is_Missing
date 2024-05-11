#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef struct questiontree {
    int id;
    char *perguntas;
    char *a;
    char *b;
    char *c;
    char *d;
    char resposta;
    struct questiontree *next;
} Questiontree;

typedef struct ranking {
    int pontos;
    char nome[30];
} Ranking;

int randomValue();
int jogadores(FILE *dados);
void sortranking(Ranking *ranking, int n);
void addRanking(Ranking *ranking, int qtd, FILE * dados);
void inserir(Questiontree **head, int id, char *pergunta, char *a, char *b, char *c, char *d, char resposta);
void lerArquivo(const char *nomeArquivo, Questiontree **head);
void sortearArquivo();
char* pontoschar(const char *array, char str_pontos);
char* strpontos(int pontos);

#endif