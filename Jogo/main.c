#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct questiontree {
    char *perguntas;
    char *a;
    char *b;
    char *c;
    char *d;
    struct questiontree *next;
} Questiontree;

void inserir(Questiontree **head, char *pergunta, char *a, char *b, char *c, char *d);

void lerArquivo(Questiontree **head, const char *fileName){
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

void inserir(Questiontree **head, char *pergunta, char *a, char *b, char *c, char *d) {
    Questiontree *novo = (Questiontree *)malloc(sizeof(Questiontree));
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
            Questiontree *aux = *head;
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = novo;
        }
    }
}

void remover(Questiontree **head){
    Questiontree *temp;
    if(*head != NULL){
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void imprimirPrimeiroValor(Questiontree *head) {
    printf("%s\n", head->perguntas);
    printf("%s\n", head->a);
    printf("%s\n", head->b);
    printf("%s\n", head->c);
    printf("%s\n", head->d);
}

int main() {
    int respostas[] = {1, 2, 3, 4, 5, 6};
    int resposta;
    int j = 0;
    Questiontree *head = NULL;
    lerArquivo(&head, "p1.txt");

    for (int i = 0; i < 6; i++) {
        imprimirPrimeiroValor(head);
        scanf("%d", &resposta);

        if (resposta == respostas[j]) {
            printf("U win!\n");
            remover(&head);
        } else {
            printf("U lose\n");
            break;
        }

        j++;
    }

    return 0;
}