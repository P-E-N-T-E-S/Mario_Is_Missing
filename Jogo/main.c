#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Questions {
    char *perguntas;
    char *a;
    char *b;
    char *c;
    char *d;
    struct Questions *next;
} Questions;

void inserir(Questions **head, char *pergunta, char *a, char *b, char *c, char *d);

void lerArquivo(Questions **head, const char *fileName){
    FILE *arquivo = fopen(fileName, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }
    while(!feof(arquivo)){
            char pergunta[256], a[256], b[256], c[256], d[256];
            fgets(pergunta, sizeof(pergunta), arquivo);
            fgets(a, sizeof(a), arquivo);
            fgets(b, sizeof(b), arquivo);
            fgets(c, sizeof(c), arquivo);
            fgets(d, sizeof(d), arquivo);
            inserir(&(*head), pergunta, a, b, c, d);
        }
    fclose(arquivo);
}

void inserir(Questions **head, char *pergunta, char *a, char *b, char *c, char *d) {
    Questions *novo = (Questions *)malloc(sizeof(Questions));
    if (novo != NULL) {
        novo->perguntas = strdup(pergunta);
        novo->a = strdup(a);
        novo->b = strdup(b);
        novo->c = strdup(c);
        novo->d = strdup(d);
        novo->next = NULL;

        if (*head == NULL) {
            *head = novo;
        } else {
            Questions *aux = *head;
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = novo;
        }
    }
}

void remover(Questions **head){
    Questions *temp;
    if(*head != NULL){
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void imprimirPrimeiroValor(Questions *head) {
    printf("%s\n", head->perguntas);
    printf("%s\n", head->a);
    printf("%s\n", head->b);
    printf("%s\n", head->c);
    printf("%s\n", head->d);
}

