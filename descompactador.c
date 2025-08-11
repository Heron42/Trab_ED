#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "lista.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Execução incorreta\n");
        exit(1);
    }
    char* nomearquivo = strdup(argv[1]);
    FILE* arquivo = fopen(nomearquivo, "rb");   // Abre arquivo de leitura
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo a ser compactado\n");
        exit(1);
    }

    // Implementar função leArvore -> recria a arvore de huffman


    // Ler o conjunto de dados (Tem que arranjar algum jeito de saber os bits válidos do último byte)

    // * Usar o bitmap.h pra separar os bits dos bytes em unisigned char percorrendo pela árvore até achar o caracter e aí
    // imprimir o caracter (acho q da pra fazer direto)

    
}