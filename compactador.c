#include <stdio.h>
#include "lista.h"
#include "arvore.h"
#include "bitmap.h"
#include <stdlib.h>
#include <string.h>


void geraCodigos(Arv* arv, char* string, char* codigos[]);

int main(int argc, char *argv[]){
    char* nomearquivo;
    strcpy(nomearquivo, argv[1]);
    FILE* arquivo = fopen(nomearquivo, "rb");   // Abre arquivo de leitura
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo a ser compactado\n");
        exit(1);
    }
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    unsigned char* buffer = malloc(tamanho);   
    fread(buffer, 1, tamanho, arquivo);     // Lê arquivo

    int peso[256] = {0};
    for(int i = 0;i<tamanho;i++){   // Define o peso de cada caracter
        peso[buffer[i]]++;
    }
    int qtd = 0;

    Lista* lista = criaLista();

    int maior = 0;
    for(int i = 0;i<256;i++){   //Acha o maior peso e atribui a "maior"
        if(peso[i] > maior){
            maior = peso[i];
        }
    }

    int menor;
    int marca = 0;
    int count = 0;
    while(1){   //Cria uma lista com os caracteres ordenados por peso
        menor = maior;
        for(int i = 0;i<256;i++){   // Acha o menor peso, desconsiderando os que já foram encontrados
            if(peso[i] < menor && peso[i] > marca){
                menor = peso[i];
            }
        }
        if(menor == marca){
            break;
        }
        for(int i = 0;i<256;i++){   //Insere os elementos na lista
            if(peso[i] == menor){
                unsigned char c = i;
                Arv* no = criaArvore(c);
                lista = insereLista(lista, no);
            }
        }

        marca = menor;
    }

    // Implementação do código de Huffman
    while(!retornaUnicoElemento(lista)){
        Arv* r = fundeArvores(retornaDadoListaPorIndice(lista, 1), retornaDadoListaPorIndice(lista, 2));
        lista = retiraLista(lista);
        lista = insereLista(lista, r);
    }
    Arv* huff = retornaDadoListaPorIndice(lista, 1);

    liberaLista(lista);

    char* codigos[256] = {0};

    geraCodigos(huff, "", codigos);

    bitmap* bm = bitmapInit(8*tamanho);

    for(int i = 0;i<tamanho;i++){
        unsigned char byte = buffer[i];
        char* codigo = codigos[byte];
        for(int j = 0;codigo[j] != '\0';j++){
            bitmapAppendLeastSignificantBit(bm, codigo[j] - '0');
        }
    }

    strcat(nomearquivo, ".comp");
    FILE* saida = fopen(nomearquivo, "wb");
    if(saida == NULL){
        printf("Erro na criação de arquivo de saida\n");
    }

    imprimeArvore(huff, saida);


    fwrite(bitmapGetContents(bm), 1, (bitmapGetLength(bm) + 7)/8, saida);
    fclose(saida);

    return 0;
}

void geraCodigos(Arv* arv, char* string, char* codigos[]){
    if(ehFolha(arv)){
        unsigned char c = getDadoArvore(arv);
        codigos[c] = strdup(string);
        return;
    }

    // Caminhando a esquerda ("0")
    char* novo = (char*)malloc(strlen(string) + 2);
    strcpy(novo, string);
    strcat(novo, "0");
    geraCodigos(getSae(arv), novo, codigos);
    free(novo);


    // Caminhando a direita ("1")
    novo = (char*)malloc(strlen(string) + 2);
    strcpy(novo, string);
    strcat(novo, "1");
    geraCodigos(getSad(arv), novo, codigos);
    free(novo);
}