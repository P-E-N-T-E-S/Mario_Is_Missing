#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int lerranking(int argc, char *argv[]) {
    FILE *dados;
    dados = fopen(argv[1], "r");

    int i = 0;
    int qtd = jogadores(dados);
    Ranking *ranking = (Ranking *)malloc(qtd * sizeof(Ranking));

    while (!feof(dados)){
        fscanf(dados, "%s %d", ranking[i].nome, & ranking[i].pontos);
        i++;
    }

    fclose(dados);
    sortranking(ranking, qtd);
    addRanking(ranking, qtd, dados);
    free(ranking);

    return 0;
}

void sortranking(Ranking *ranking, int qtd) {
    int i, j;
    Ranking temp;

    for (i = 1; i < qtd; i++) {
        temp = ranking[i];
        j = i - 1;

        while (j >= 0 && ranking[j].pontos < temp.pontos) {
            ranking[j + 1] = ranking[j];
            j = j - 1;
        }

        ranking[j + 1] = temp;
    }
}

void addRanking(Ranking *ranking, int qtd, FILE * dados) {
    FILE *arquivo;
    arquivo = fopen(dados, "w");

    for (int i = 0; i < qtd; i++) {
        fprintf(arquivo, "%s %d\n", ranking[i].nome, ranking[i].pontos);
    }

    fclose(arquivo);
}

int jogadores(FILE *dados) {
    int linhas = 0;
    char ch;

    while ((ch = fgetc(dados)) != EOF) {
        if (ch == '\n') {
            linhas++;
        }
    }
    fseek(dados, 0, 0);
}