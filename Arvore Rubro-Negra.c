#include <stdio.h>
#include <stdlib.h>

typedef struct cor {
    int preto;
    int vermelho;
} COR;

typedef struct no {
    int dado;
    COR cor;
    struct no *esq;
    struct no *dir;
    struct no *pai;
} NO;

NO *criarNo(int valor) {
    NO* novo = malloc(sizeof(NO));

    if(novo == NULL) {
        printf("Erro de locação\n");
        return NULL;
    }
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;

    return NULL;    
}

void inserir(NO *raiz, int valor) {
    
}

int main () {
    NO* raiz = criarNo(10);

    if(raiz != NULL) {
        printf("No criada com sucesso!\n");
        return(raiz);
    }

    return 0;
}