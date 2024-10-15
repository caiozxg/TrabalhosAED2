#include <stdio.h>
#include <stdlib.h>


void bubblesort(int *vector){
    int temp;
    for (int i=0;i<tam;i++){
        if (vector[i]>vector[i+1]){
            temp = vector[j];
            vector[i]=vector[i+1];
            vector[i+1]=temp;
            }
    }
}

void bubblesortmelhorado(int *vector){
    int mudou=1;
    // chega se mudou ou nao
    while (mudou == 1){
        int i = 0;
        mudou = 0;
        for (i<tam ; i++){
            if (vector[i]>vector[i+1]){
                temp = vector[j];
                vector[i]=vector[i+1];
                vector[i+1]=temp;
                mudou = 1;
            }
        }



    }

}


void insertionsort(int *vector){
    //percorre aumentando 1 a cada vez
    for (int i=1;i<tam;i++){
        temp = vector[i];
        int j = i-1;
        //move os numeros maiores que os que estao guardado em temp para direita
        while (j>=1 && temp < vector[j]){
            vector[j+1] = vector[j];
            j--;


        }       
        //adiciona o temp no lugar certo
        vector[j+1] = temp;
    }
}


int main(int argc,char argv[]){
    char nome_arquivo_entrada = argv[2];
    char nome_arquivo_saida = argv[3];
    int aux[];
   File *file = fopen("nome_arquivo","rb");
   if (file == NULL ){
    printf("erro ao abrir o arquivo");


   }else{
    



























   }



    fclose(file);

    return 0;
}
