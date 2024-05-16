#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// Essa função lê todo o arquivo onde está o ranking e atribui linha a linha a uma lista encadeada também chama as funções sort add
int ordernar_ranking() {
  FILE *dados;
  dados = fopen("Perguntas/ranking.txt", "r");

  int i = 0;
  ListaRanking *head = NULL;
  ListaRanking *aux = NULL;

  // Lê os dados do arquivo e cria uma lista encadeada de jogadores
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
    i++;
  }

  fclose(dados);
  
  // Ordena a lista de jogadores
  sortranking(head);

  // Salva a lista ordenada no arquivo
  addRanking(head);

  // Libera a memória alocada para a lista
  free_ranking(head);
  return 0;
}

// Função para salvar um novo jogador no arquivo de ranking
void salvar_ranking(char *get_name, int pontos) {
  FILE *dados;
  dados = fopen("Perguntas/ranking.txt", "a");

  if (dados != NULL) {
    fprintf(dados, "%s %d\n", get_name, pontos);
    fclose(dados);
  }
}

// Essa função utiliza do algoritmo de ordenação "bubble sort" para colocar em ordem o ranking
void sortranking(ListaRanking *ranking) {
  ListaRanking *i, *j;
  ListaRanking temp;

  for (i = ranking; i != NULL; i = i->next) {
    for (j = i->next; j != NULL; j = j->next) {
      if (i->pontos < j->pontos) {
        temp = *i;
        *i = *j;
        *j = temp;

        ListaRanking *temp_next = i->next;
        i->next = j->next;
        j->next = temp_next;
      }
    }
  }
}

// Essa função sobrescrever o arquivo de ranking mas agora de forma ordenada.
void addRanking(ListaRanking *head) {
  FILE *arquivo;
  arquivo = fopen("Perguntas/ranking.txt", "w");

  ListaRanking *aux = head;
  while (aux != NULL) {
    fprintf(arquivo, "%s %d\n", aux->nome, aux->pontos);
    aux = aux->next;
  }

  fclose(arquivo);
}

// Função para liberar a memória alocada para a lista de jogadores
void free_ranking(ListaRanking *head) {
  ListaRanking *aux = head;
  while (aux != NULL) {
    ListaRanking *temp = aux;
    aux = aux->next;
    free(temp);
  }
}

// Essa função é utilizada para retornar os valores dentro do arquivo ranking em uma lista encadeada.
ListaRanking *printranking() {
  FILE *dados;
  dados = fopen("Perguntas/ranking.txt", "r");

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
  
  // Ordena a lista de jogadores
  sortranking(head);

  return head;
}

// Transformar de inteiro para char
char *strpontos(int pontos) {
  char *str_pontos = (char *)malloc(20 * sizeof(char));
  snprintf(str_pontos, 20, "%d", pontos);
  return str_pontos;
}