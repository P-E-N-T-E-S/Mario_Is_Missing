#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

const char *dicas[] = {
    "Nesta cidade, você pode encontrar o Ninho de Pássaro, um estádio icônico construído para os Jogos Olímpicos de 2008.",
    "Há um antigo observatório astronômico que remonta ao século XV.",
    "O Palácio de Verão, um enorme complexo de jardins e edifícios históricos, é um dos locais mais bonitos e tranquilos da cidade.",
    "Beihai Park é um parque imperial antigo com um lago central, pagodes e jardins paisagísticos.",
    "O Templo do Céu é um complexo religioso onde os imperadores realizavam rituais para garantir boas colheitas e bênçãos divinas.",
    "Uma das iguarias locais é o Pato de Pequim, um prato de pato assado servido com panquecas, molho hoisin e cebolinha."
};

typedef struct ranking {
    int pontos;
    char nome[30];
} Ranking;

int randomValue();
int jogadores(FILE *dados);
int ordernar_ranking();
void sortranking(Ranking *ranking, int n);
void addRanking(Ranking *ranking, int qtd);
void salvar_ranking(char *get_name, int pontos);
Ranking* printranking();
char* strpontos(int pontos);

#endif