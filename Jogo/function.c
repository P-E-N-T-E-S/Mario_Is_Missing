#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function.h"


int randomValue() {
    srand(time(NULL));
    return rand() % 4;
}

void sortearArquivo(Questions **head, int *array) {
    int op = randomValue();
    switch (op) {
        case 0:
            acharLinha("Perguntas/resposta.txt", 1, array);
            lerArquivo(head, "Perguntas/p1.txt", array);
            break;
        case 1:
            acharLinha("Perguntas/resposta.txt", 2, array);
            lerArquivo(head, "Perguntas/p2.txt", array);
            break;
        case 2:
            acharLinha("Perguntas/resposta.txt", 3, array);
            lerArquivo(head, "Perguntas/p3.txt", array);
            break;
        case 3:
            acharLinha("Perguntas/resposta.txt", 4, array);
            lerArquivo(head, "Perguntas/p4.txt", array);
            break;
        default:
            break;
    }
}


void acharLinha(const char *fileName, int linhaProcurada, int *array) {
    FILE *arquivo = fopen(fileName, "r");
    if (arquivo == NULL) {
        printf("ERRO: arquivo não encontrado");
        return;
    }
    char linha[256];
    int linhaAtual = 1;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linhaAtual == linhaProcurada) {
            char *partes = strtok(linha, " ");
            int indice = 0;
            while (partes != NULL && indice < 6) {
                array[indice] = atoi(partes);
                partes = strtok(NULL, " ");
                indice++;
            }
            break;
        }
        linhaAtual++;
    }
    fclose(arquivo);
    if (linhaAtual < linhaProcurada) {
        for (int i = 0; i < 6; i++) {
            array[i] = -1;
        }
    }
}


void lerArquivo(Questions **head, const char *fileName, int *array) {
    FILE *arquivo = fopen(fileName, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }
    int i = 0;
    while (!feof(arquivo)) {
        char pergunta[256], a[256], b[256], c[256], d[256];
        fgets(pergunta, sizeof(pergunta), arquivo);
        fgets(a, sizeof(a), arquivo);
        fgets(b, sizeof(b), arquivo);
        fgets(c, sizeof(c), arquivo);
        fgets(d, sizeof(d), arquivo);
        inserir(head, pergunta, a, b, c, d, array[i]);
        i++;
    }
    fclose(arquivo);
}

void inserir(Questions **head, char *pergunta, char *a, char *b, char *c, char *d, int resposta) {
    Questions *novo = (Questions *)malloc(sizeof(Questions));
    if (novo != NULL) {
        novo->pergunta = strdup(pergunta);
        novo->a = strdup(a);
        novo->b = strdup(b);
        novo->c = strdup(c);
        novo->d = strdup(d);
        novo->resposta = resposta;
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

void remover(Questions **head) {
    Questions *temp;
    if (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void imprimirPrimeiroValor(Questions *head) {
    printf("%s\n", head->pergunta);
    printf("%s\n", head->a);
    printf("%s\n", head->b);
    printf("%s\n", head->c);
    printf("%s\n", head->d);
    printf("%d\n", head->resposta);
}