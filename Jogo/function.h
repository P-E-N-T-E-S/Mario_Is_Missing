#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

typedef struct Questions {
    char *pergunta;
    char *a;
    char *b;
    char *c;
    char *d;
    int resposta;
    struct Questions *next;
} Questions;

typedef struct ranking {
    int pontos;
    char nome[30];
} Ranking;

//pedro
void inserir(Questions **head, char *pergunta, char *a, char *b, char *c, char *d, int resposta);
void acharLinha(const char *fileName, int linhaProcurada, int *array);
void lerArquivo(Questions **head, const char *fileName, int *array);
void imprimirPrimeiroValor(Questions *head);
void remover(Questions **head);
void sortearArquivo(Questions **head, int *array);
void aleatorizarPerguntas(Questions** head);

//thomaz
int randomValue();
int jogadores(FILE *dados);
int ordernar_ranking();
void sortranking(Ranking *ranking, int n);
void addRanking(Ranking *ranking, int qtd);
void salvar_ranking(char *get_name, int pontos);
Ranking* printranking();
char* strpontos(int pontos);

#endif