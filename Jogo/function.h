#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef struct questiontree{
    int id;
    char *perguntas;
    char *a;
    char *b;
    char *c;
    char *d;
    char resposta;
    struct questiontree *left;
    struct questiontree *right;
}Questiontree;

int randomValue();


#endif /* FUNCTIONS_H_ */