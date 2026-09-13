#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int val;
    struct no *esq;
    struct no *dir;
} NO;

NO *criarARV() {
    NO *novo = malloc(sizeof(NO));
    if(novo == NULL) {
        printf("Erro de alocação\n");
        return NULL;
    }
    novo->esq = NULL;
    novo->dir = NULL;

    return NULL;
}

void inserir(NO **raiz, int valor) {
    if(*raiz == NULL) {
        NO *novo = malloc(sizeof(NO));
        novo->val = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
    } else if(valor < (*raiz)->val) {
        inserir(&(*raiz)->esq, valor);
    } else {
        inserir(&(*raiz)->dir, valor);
    }
}

void mostrar(NO **raiz) {
    if(*raiz == NULL) {
        return;
    }
    mostrar(&(*raiz)->esq);
    printf("%d\n", (*raiz)->val);
    mostrar(&(*raiz)->dir);
}

int main() {
    NO* arv = criarARV();
    inserir(&arv, 10);
    inserir(&arv, 20);
    inserir(&arv, 30);
    
    mostrar(&arv);

    return 0;
}