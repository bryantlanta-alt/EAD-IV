#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct no {
    int val;
    struct no *esq;
    struct no *dir;
} NO;

NO *criarARV() {
    return NULL;
}

NO *menor(NO *raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    if(raiz->esq == NULL) {
        return raiz;    
    }

    return menor(raiz->esq);
}

NO *maior(NO *raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    if(raiz->dir == NULL) {
        return raiz;    
    }

    return maior(raiz->dir);
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

void remover (NO **raiz, int valor) {

    if(*raiz == NULL) {
        printf("A árvore não existe!\n");
        return;
    }

    // Caso 1 (nó folha):
    if(valor < (*raiz)->val) {
        remover(&(*raiz)->esq, valor);
    } else if (valor > (*raiz)->val) {
        remover(&(*raiz)->dir, valor);
    } else {
        if((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
            free(*raiz);
            *raiz = NULL;
            printf("Nó folha removido\n");
        }

        // Caso 2 (nó pai tem 1 filho):
        else if((*raiz)->esq == NULL) {                //verificando o lado esquerdo
            NO* aux = *raiz;
            *raiz = (*raiz)->dir;
            free(aux);
            printf("Nó com 1 filho (dir) removido\n");
        }

        else if((*raiz)->dir == NULL) {                //verificando o lado direita
            NO* aux = *raiz;
            *raiz = (*raiz)->esq;
            free(aux);
            printf("Nó com 1 filho (esq) removido\n");
        }

        else {
            NO *aux = menor((*raiz)->dir);             // escolhi receber o menor número do lado direito
            (*raiz)->val = aux->val;
            printf("Caso 3 de remoção executado\n");
            remover(&(*raiz)->dir, aux->val);
        }

    }
}


void mostrar(NO **raiz) {
    if(*raiz == NULL) {
        return;
    }
    mostrar(&(*raiz)->esq);
    printf("%d, ", (*raiz)->val);
    mostrar(&(*raiz)->dir);
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    NO* arv = criarARV();

    printf("Inserindo... ");
    inserir(&arv, 10);
    inserir(&arv, 20);
    inserir(&arv, 30);
    inserir(&arv, 5);
    inserir(&arv, 7);
    mostrar(&arv);
    printf("\n");

    remover(&arv, 30);

    printf("Valores: ");
    mostrar(&arv);
    printf("\n");

    printf("Inserindo... ");
    inserir(&arv, 30);
    mostrar(&arv);
    printf("\n");

    remover(&arv, 20);

    printf("Valores: ");
    mostrar(&arv);
    printf("\n");

    remover(&arv, 5);

    printf("Valores: ");
    mostrar(&arv);
    printf("\n");

    printf("Inserindo... ");
    inserir(&arv, 20);
    inserir(&arv, 25);
    inserir(&arv, 15);
    inserir(&arv, 5);
    mostrar(&arv);
    printf("\n");

    remover(&arv, 20);

    printf("Valores: ");
    mostrar(&arv);
    printf("\n");

    return 0;
}