#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

//inserir dicas em uma lista encadeada
void append(Dicas **head, const char *dica) {
    Dicas *novo = (Dicas *)malloc(sizeof(Dicas));
    novo->dica = strdup(dica);
    novo->next = NULL;
    if (*head == NULL) {
        *head = novo;
        return;
    }
    Dicas *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = novo;
}

//ler o arquivo de dicas
void lerDicas(Dicas **head) {
    FILE *file = fopen("Perguntas/dicas.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        append(head, buffer);
    }

    fclose(file);

}

//remover a head da lista
void removerDicas(Dicas **head) {
    Dicas *temp;
    if (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

//liberar a lista de dicas
void freeDicaList(Dicas *head) {
    Dicas *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->dica);
        free(temp);
    }
}
