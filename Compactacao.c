#include <stdlib.h>
#include <stdio.h>


typedef struct NoHeap{

    char dado;
    int frequencia;
    struct NoHeap *Esquerda,*Direita;

}NoHeap;


typedef struct HeapMin{

    unsigned tamanho;
    unsigned capacidade;
}HeapMin;





int main(int argc,char *argv[]){
    nome_arquivo = argv[1];
    char *nome_arquivo = argv[2];
    FILE *file =fopen(nome_arquivo,"rb");
    int frequencias[256] = {0};
    if (file == NULL){
        printf("erro ao abrir o arquivo");
        return 0;
    }

    char c;

    while (fread(&c,sizeof(char),1,file)){

        frequencias[(unsigned char)c]++;

    }












    return 0;
}
