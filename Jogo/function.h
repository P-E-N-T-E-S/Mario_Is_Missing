#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

//Function.c
typedef struct Questions {
    char *pergunta;
    char *a;
    char *b;
    char *c;
    char *d;
    int resposta;
    struct Questions *next;
} Questions;

//Ranking.c
typedef struct lista_ranking {
    int pontos;
    char nome[30];
    struct lista_ranking *next;
} ListaRanking;

//Dica.c
typedef struct Dicas {
    char *dica;
    struct Dicas *next;
} Dicas;

//Function.c
void inserir(Questions **head, char *pergunta, char *a, char *b, char *c, char *d, int resposta);
void acharLinha(const char *fileName, int linhaProcurada, int *array);
void lerArquivo(Questions **head, const char *fileName, int *array);
void remover(Questions **head);
void sortearArquivo(Questions **head, int *array);
int randomValue();
void aleatorizarPerguntas(Questions** head);

//Ranking.c
int ordernar_ranking();
void sortranking(ListaRanking *ranking);
void addRanking(ListaRanking *ranking);
void salvar_ranking(char *get_name, int pontos);
ListaRanking *printranking();
char *strpontos(int pontos);
void free_ranking(ListaRanking *head);

//Dica.c
void append(Dicas **head, const char *dica);
void lerDicas(Dicas **head);
void freeDicaList(Dicas *head);

#endif