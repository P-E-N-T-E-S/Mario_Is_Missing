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
int ordernar_ranking();
void sortranking(Ranking *ranking, int n);
void addRanking(Ranking *ranking, int qtd);
void salvar_ranking(char *get_name, int pontos);
Ranking* printranking();
char* strpontos(int pontos);

#endif