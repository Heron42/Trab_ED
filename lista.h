#ifndef _LISTA_H
#define _LISTA_H

#include "arvore.h"

typedef struct lista Lista;
typedef struct celula cel;

Lista* criaLista();

Lista* insereLista(Lista* l, void* dado);

Lista* retiraLista(Lista* l);

Arv* retornaDadoListaPorIndice(Lista* l, int i);

int retornaUnicoElemento(Lista* l);

void liberaLista(Lista* l);

#endif