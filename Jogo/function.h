

typedef struct questiontree{
    int id;
    char perguntas;
    struct questiontree *left;
    struct questiontree *right;
    char *alternativas[];
}Questiontree;

void iniciar(Questiontree** root, int id, char perguntas,  )
