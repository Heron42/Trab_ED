#include "lista.h"
#include <stdlib.h>

struct celula{
    void* dado;
    cel* prox;
};

struct lista{
    cel* prim;
    cel* ult;
};


Lista* criaLista(){
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->prim = l->ult = NULL;

    return l;
}

Lista* insereLista(Lista* l, void* dado){
    cel* newcel = (cel*)malloc(sizeof(cel));
    newcel->dado = dado;
    
    if(l->prim == NULL && l->ult == NULL){
        l->prim = l->ult = newcel;
    }
    else{
        l->ult->prox = newcel;
        l->ult = newcel;
    }
    newcel->prox = NULL;

    return l;
}

Lista* retiraLista(Lista* l){
    if(!(l->prim == l->ult)){
        cel* p = l->prim;
        if(l->ult == l->prim->prox){
            l->prim = l->ult = NULL;
            free(p->prox);
            free(p);
        }
        else{
            l->prim = l->prim->prox->prox;
            free(p->prox);
            free(p);
        }
    }

    return l;
}

void* retornaDadoListaPorIndice(Lista* l, int i){
    int j = 1;
    for(cel* p = l->prim;p != NULL;p = p->prox){
        if(j == i){
            return p;
        }
        j++;
    }
}

int retornaUnicoElemento(Lista* l){
    if(l->prim == l->ult && l->prim != NULL){
        return 1;
    }
    return 0;
}

void liberaLista(Lista* l){
    free(l->prim);
    free(l);
}