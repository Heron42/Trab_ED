#include "arvore.h"
#include <stdlib.h>

struct Arvore{
    unsigned char dado;
    Arv* sae;
    Arv* sad;
};

Arv* criaArvore(unsigned char dado){
    Arv* a = (Arv*)malloc(sizeof(Arv));
    a->sad = a->sae = NULL;
    a->dado = dado;

    return a;
}

Arv* criaArvNula(){
    Arv* a = (Arv*)malloc(sizeof(Arv));
    a->sad = a->sae = NULL;
    a->dado = '*';

    return a;
}

int ehFolha(Arv* r){
    if(r == NULL){
        return 0;
    }
    return (r->sae == NULL && r->sad == NULL);
}

unsigned char getDadoArvore(Arv* r){
    return r->dado;
}

Arv* getSae(Arv* a){
    return a->sae;
}

Arv* getSad(Arv* a){
    return a->sad;
}

Arv* fundeArvores(Arv* a1, Arv* a2){
    Arv* a = criaArvNula();
    a->sae = a1;
    a->sad = a2;

    return a;
}

void imprimeArvore(Arv* r, FILE* arq){
    if(r != NULL){
        if(r->sae == NULL && r->sad == NULL){
            fprintf(arq, "1 ");
            fprintf(arq, "%c\n", r->dado);
        }
        else{
            fprintf(arq, "0\n");
            imprimeArvore(r->sae, arq);
            imprimeArvore(r->sad, arq);
        }
    }
}

void liberaArvore(Arv* r){
    if(r != NULL){
        liberaArvore(r->sae);
        liberaArvore(r->sad);
        free(r);
    }
}