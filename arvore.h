#ifndef _ARVORE_H
#define _ARVORE_H

#include <stdio.h>

typedef struct Arvore Arv;

Arv* criaArvore(unsigned char dado);

Arv* criaArvNula();

int ehFolha(Arv* r);

unsigned char getDadoArvore(Arv* r);

Arv* getSae(Arv* a);

Arv* getSad(Arv* a);

Arv* fundeArvores(Arv* a1, Arv* a2);

void imprimeArvore(Arv* r, FILE* arq);

void liberaArvore(Arv* r);


#endif