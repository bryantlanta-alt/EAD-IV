#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ArvoreAVL.h"

typedef struct NO {
    int chv;
    int alt;
    struct NO *esq;
    struct NO *dir;
} NO;

typedef NO* arvAVL;

arvAVL* criarARV() {
    arvAVL* raiz = malloc(sizeof(arvAVL));

    if(raiz != NULL) *raiz = NULL;
    return raiz;
}

void liberarARV(arvAVL* raiz) {
    free(raiz);
}

int arv_alt(arvAVL nos) {
    if(nos == NULL) return -1;
    else
        return nos->alt;
}

int f_balanceamento(arvAVL raiz) {
    return (arv_alt(raiz->esq) - arv_alt(raiz->dir));
}

int qtd_no(arvAVL nos){
    if(nos == NULL) return 0;

    int nos_esq = qtd_no(nos->esq);
    int nos_dir = qtd_no(nos->dir);

    return (nos_esq + nos_dir + 1);
}

int maior(int a, int b) {
    return (a>b) ? a : b;
}

int arv_busca(arvAVL raiz, int chv) {
    if(raiz == NULL) return 0;

    if(chv == raiz->chv) {
        return 1;
    }
    
    if (chv > raiz->chv) return arv_busca(raiz->dir, chv);
    else
        return arv_busca(raiz->esq, chv);
}

void arv_inserir(arvAVL* raiz, int chv) {
    if(raiz == NULL) return;

    if(*raiz == NULL) {
        NO* novo = malloc(sizeof(NO));
        novo->chv = chv;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
    }

    if(chv < (*raiz)->chv) arv_inserir(&(*raiz)->esq, chv);
    else 
        arv_inserir(&(*raiz)->dir, chv);
}

void rotacao_LL(arvAVL* raiz) {
    if(raiz == NULL || *raiz == NULL || (*raiz)->esq == NULL) {
        return;
    }

    NO* no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;

    (*raiz)->alt = maior(arv_alt((*raiz)->esq), arv_alt((*raiz)->dir) + 1);
    no->alt = maior(arv_alt(no->esq), (*raiz)->alt + 1);
    
    *raiz = no;
}
void rotacao_RR(arvAVL* raiz) {
    if(raiz == NULL || *raiz == NULL || (*raiz)->dir == NULL) {
        return;
    }

    NO* no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;

    (*raiz)->alt = maior(arv_alt((*raiz)->dir), arv_alt((*raiz)->esq) + 1);
    no->alt = maior(arv_alt(no->dir), (*raiz)->alt + 1);
    
    *raiz = no;
}

void rotacao_RL(arvAVL* raiz) {
    rotacao_LL((*raiz)->dir);
    rotacao_RR(raiz);
}

void rotacao_LR(arvAVL* raiz) {
    rotacao_RR((*raiz)->esq);
    rotacao_LL(raiz);
}


int main(void) {
    setlocale(LC_ALL, "Portuguese");
    arvAVL* raiz = criarARV();
    
    // Testa a inserção de dados
    arv_inserir(raiz, 10);
    arv_inserir(raiz, 20);

    return 0;
}
