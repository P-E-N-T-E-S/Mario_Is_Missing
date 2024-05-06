#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function.h"


int randomValue(){
    srand(time(NULL));
    int i = rand() % 4;
    return i;
}

void sortearArquivo(){
    int op = randomValue();
    Questiontree *head = NULL;
    switch (op)
    {
    case 1:
        lerArquivo("Mario_Is_Missing/Jogo/Perguntas/p1.txt", &head);
        break;
    
    case 2:
        lerArquivo("Mario_Is_Missing/Jogo/Perguntas/p2.txt", &head);
        break;
    
    case 3:
        lerArquivo("Mario_Is_Missing/Jogo/Perguntas/p3.txt", &head);
        break;
    case 4:
        lerArquivo("Mario_Is_Missing/Jogo/Perguntas/p4.txt", &head);
        break;
    default:
        break;
    }
}


void inserir(Questiontree **head, int id, char *pergunta, char *a, char *b, char *c, char *d, char resposta){
    Questiontree *novo = (Questiontree *)malloc(sizeof(Questiontree));
    if(novo != NULL){
        novo->id = id;
        strcpy(novo->perguntas, pergunta);
        strcpy(novo->a, a);
        strcpy(novo->b, b);
        strcpy(novo->c, c);
        strcpy(novo->d, d);
        novo->resposta = resposta;
        novo->next = *head;
        *head = novo;
    }
}

void lerArquivo(const char *nomeArquivo, Questiontree **head){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }
    char linha[256];
    while(fgets(linha, sizeof(linha), arquivo)){

        if(linha[0] == '\n'){
            continue;
        }

        if (linha[strlen(linha) - 1] == '\n'){
            linha[strlen(linha) - 1] = '\0';
        }
        if (linha[0] >= '0' && linha[0] <= '9') {
            int id;
            char pergunta[256], a[256], b[256], c[256], d[256], resposta;

            sscanf(linha, "%d", &id);
            fgets(pergunta, sizeof(pergunta), arquivo);
            fgets(a, sizeof(a), arquivo);
            fgets(b, sizeof(b), arquivo);
            fgets(c, sizeof(c), arquivo);
            fgets(d, sizeof(d), arquivo);
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "%c", &resposta);

            inserir(&(*head), id, pergunta, a, b, c, d, resposta);
        }
    }
    fclose(arquivo);
}

