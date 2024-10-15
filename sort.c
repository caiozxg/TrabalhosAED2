#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void bubblesort(int32_t *vector, int32_t tam) {
    int32_t temp;
    for (int32_t i = 0; i < tam - 1; i++) {  
        for (int32_t j = 0; j < tam - i - 1; j++) {
            if (vector[j] > vector[j + 1]) {
                temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp; 
            }
        }
    }
}

// void bubblesortmelhorado(int32_t *vector,int tam){
//     int32_t mudou=1,temp;
//     // chega se mudou ou nao
//     while (mudou == 1){
        
//         mudou = 0;
//         for (int32_t i = 0;i<tam;i++){
//             if (vector[i]>vector[i+1]){
//                 temp = vector[i];
//                 vector[i]=vector[i+1];
//                 vector[i+1]=temp;
//                 mudou = 1;
//             }
//         }



//     }

// }


// void insertionsort(int32_t *vector,int tam){
//     //percorre aumentando 1 a cada vez
//     int32_t temp;
//     for (int32_t i=1;i<tam;i++){
//         temp = vector[i];
//         int32_t j = i-1;
//         //move os numeros maiores que os que estao guardado em temp para direita
//         while (j>=1 && temp < vector[j]){
//             vector[j+1] = vector[j];
//             j--;


//         }       
//         //adiciona o temp no lugar certo
//         vector[j+1] = temp;
//     }
// }


int main(int argc, char *argv[]) {
   
    clock_t inicio,fim;
    char *nome_arquivo_entrada = argv[1];

    char *nome_arquivo_saida = argv[2];

    FILE *file = fopen(nome_arquivo_entrada, "rb");
    
    if (file == NULL) {

        printf("erro ao abrir o arquivo\n");

        return 1;
    }

    int32_t tamanho_arquivo;

    //aponta para o final para pegarmos o tamanho 

    fseek(file, 0, SEEK_END);

    tamanho_arquivo = ftell(file);

    int32_t *vector = malloc(tamanho_arquivo);

    if (vector == NULL) { 
        printf("erro ao alocar memoria\n");
        fclose(file);
        return 1;
    }

    //volta o ponteiro para o começo

    fseek(file, 0, SEEK_SET);
    //armazenar os numeros no vetor
    for (int32_t i = 0; i < tamanho_arquivo / sizeof(int32_t); i++) {
        fread(&vector[i], sizeof(int32_t), 1, file);
    }



    fclose(file);

    srand(time(NULL));
    inicio = clock();
    bubblesort(vector,tamanho_arquivo/sizeof(int32_t));
    fim = clock();


    //abrir arquivo de saida para adicionar os numeros
    FILE *filesaida = fopen(nome_arquivo_saida, "wb");
    if (filesaida == NULL) {
        printf("erro ao abrir o arquivo de saida\n");
        free(vector);
        return 1;
    }

    fseek(filesaida, 0, SEEK_SET);

        //escrever os numeros do vetor no arquivo de saida
    for (int32_t i = 0; i < tamanho_arquivo / sizeof(int32_t); i++) {
            fwrite(&vector[i], sizeof(int32_t), 1, filesaida);
    }


    fclose(filesaida);
    free(vector);
    double tempo=0;
    tempo += (double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("o tempo para executar a funcao foi de: %.3f \n\n",tempo);
    return 0;
}
