#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    
    const char *types[] = {
        "Nesta cidade, você pode encontrar o Ninho de Pássaro, um estádio icônico construído para os Jogos Olímpicos de 2008.",
        "Há um antigo observatório astronômico que remonta ao século XV.",
        "O Palácio de Verão, um enorme complexo de jardins e edifícios históricos, é um dos locais mais bonitos e tranquilos da cidade.",
        "Beihai Park é um parque imperial antigo com um lago central, pagodes e jardins paisagísticos.",
        "O Templo do Céu é um complexo religioso onde os imperadores realizavam rituais para garantir boas colheitas e bênçãos divinas.",
        "Uma das iguarias locais é o Pato de Pequim, um prato de pato assado servido com panquecas, molho hoisin e cebolinha."
    };

    const int tamanhoArray = 6;
    int array[tamanhoArray];

    Questions *head = NULL;
    sortearArquivo(&head, array);
    aleatorizarPerguntas(&head);
    for (int i = 0; i < 6; i++) {
        imprimirPrimeiroValor(head);
        remover(&head);
    }

    return 0;
}
