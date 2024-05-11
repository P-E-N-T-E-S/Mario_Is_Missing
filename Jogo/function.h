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

typedef struct lista_ranking {
    int pontos;
    char nome[30];
    struct lista_ranking *next;
} ListaRanking;

//pedro
void inserir(Questions **head, char *pergunta, char *a, char *b, char *c, char *d, int resposta);
void acharLinha(const char *fileName, int linhaProcurada, int *array);
void lerArquivo(Questions **head, const char *fileName, int *array);
void imprimirPrimeiroValor(Questions *head);
void remover(Questions **head);
void sortearArquivo(Questions **head, int *array);
int randomValue();
void aleatorizarPerguntas(Questions** head);

//thomaz
int jogadores(FILE *dados);
int ordernar_ranking();
void sortranking(ListaRanking *ranking);
void addRanking(ListaRanking *ranking);
void salvar_ranking(char *get_name, int pontos);
ListaRanking* printranking();
char* strpontos(int pontos);

#endif