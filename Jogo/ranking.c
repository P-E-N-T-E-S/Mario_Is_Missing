#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ordernar_ranking() {
    FILE *dados;
    dados = fopen("ranking.txt", "r");

    if (dados == NULL) {
        return 1;
    }

    int i = 0;
    ListaRanking *head = NULL;
    ListaRanking *aux = NULL;
    int leituras = 0;

    while (1) {
        ListaRanking *novo_jogador = (ListaRanking *)malloc(sizeof(ListaRanking));
        leituras = fscanf(dados, "%s %d", novo_jogador->nome, &novo_jogador->pontos);
        if (leituras != 2) {
            free(novo_jogador);
            if (leituras == EOF) {
                break;
            } else {
                fclose(dados);
                return 1;
            }
        }
        novo_jogador->next = NULL;

        if (head == NULL) {
            head = novo_jogador;
        } else {
            aux->next = novo_jogador;
        }

        aux = novo_jogador;
        i++;
    }

    fclose(dados);
    sortranking(head);
    addRanking(head);

    free_ranking(head);

    return 0;
}

void sortranking(ListaRanking *head) {
    ListaRanking *i, *j;
    ListaRanking temp;

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->pontos < j->pontos) {
                temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
}

void addRanking(ListaRanking *head) {
    FILE *arquivo;
    arquivo = fopen("ranking.txt", "w");

    ListaRanking *aux = head;
    while (aux != NULL) {
        fprintf(arquivo, "%s %d\n", aux->nome, aux->pontos);
        aux = aux->next;
    }

    fclose(arquivo);
}

void free_ranking(ListaRanking *head) {
    ListaRanking *aux = head;
    while (aux != NULL) {
        ListaRanking *temp = aux;
        aux = aux->next;
        free(temp);
    }
}

void salvar_ranking(char *get_name, int pontos) {
    FILE *dados;
    dados = fopen("ranking.txt", "a");

    if (dados != NULL) {
        fprintf(dados, "%s %d\n", get_name, pontos);
        fclose(dados);
    }
}

ListaRanking* printranking() {
    FILE *dados;
    dados = fopen("ranking.txt", "r");

    ListaRanking *head = NULL;
    ListaRanking *aux = NULL;

    while (!feof(dados)) {
        ListaRanking *novo_jogador = (ListaRanking *)malloc(sizeof(ListaRanking));
        if (fscanf(dados, "%s %d", novo_jogador->nome, &novo_jogador->pontos) != 2) {
            free(novo_jogador);
            break;
        }
        novo_jogador->next = NULL;

        if (head == NULL) {
            head = novo_jogador;
        } else {
            aux->next = novo_jogador;
        }

        aux = novo_jogador;
    }

    fclose(dados);
    sortranking(head);

    return head;
}

char* strpontos(int pontos) {
    char *str_pontos = (char *)malloc(20 * sizeof(char));
    snprintf(str_pontos, 20, "%d", pontos);
    return str_pontos;
}
