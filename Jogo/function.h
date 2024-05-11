#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


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

#endif