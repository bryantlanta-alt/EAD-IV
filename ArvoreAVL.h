#ifndef ARVORE_H
#define ARVORE_H

typedef struct no {
    int chv;
    int altura;
    struct no* esq;
    struct no* dir;
} NO;

typedef NO* arvAVL;

// incialização e remoção
arvAVL* criarARV();
void liberarARV(arvAVL* raiz);

// informações da arvore
int f_balanceamento(arvAVL raiz);
int arv_alt(arvAVL raiz);
int qtd_no(arvAVL raiz);
int maior(int a, int b);

// operações principais (buscar, inserir e remoção)
int arv_busca(arvAVL raiz, int valor);
int arv_inserir(arvAVL* raiz, int valor);
int arv_remover(arvAVL* raiz, int valor);

// testar ordem da arvore
void pre_ordem(arvAVL* raiz);
void em_ordem(arvAVL* raiz);
void pos_ordem(arvAVL* raiz);

#endif
