#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

//Caio De Souza Ortiz de Angelis
//rgm 47534

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

void bubblesortmelhorado(int32_t *vector, int tam) {
    int32_t mudou = 1, temp;
    while (mudou == 1) {
        mudou = 0;
        for (int32_t i = 0; i < tam - 1; i++) {
            if (vector[i] > vector[i + 1]) {
                temp = vector[i];
                vector[i] = vector[i + 1];
                vector[i + 1] = temp;
                mudou = 1;
            }
        }
    }
}

void insertionsort(int32_t *vector, int tam) {
    int32_t temp;
    for (int32_t i = 1; i < tam; i++) {
        temp = vector[i];
        int32_t j = i - 1;
        while (j >= 0 && temp < vector[j]) {
            vector[j + 1] = vector[j];
            j--;
        }
        vector[j + 1] = temp;
    }
}

void merge(int32_t *vector, int32_t left, int32_t mid, int32_t right) {
    int32_t tam1 = mid - left + 1;
    int32_t tam2 = right - mid;
    int32_t *L = (int32_t *)malloc(tam1 * sizeof(int32_t));
    int32_t *R = (int32_t *)malloc(tam2 * sizeof(int32_t));

    for (int32_t i = 0; i < tam1; i++) L[i] = vector[left + i];
    for (int32_t i = 0; i < tam2; i++) R[i] = vector[mid + 1 + i];

    int32_t i = 0, j = 0, k = left;
    while (i < tam1 && j < tam2) {
        if (L[i] <= R[j]) {
            vector[k] = L[i];
            i++;
        } else {
            vector[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < tam1) {
        vector[k] = L[i];
        i++;
        k++;
    }

    while (j < tam2) {
        vector[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergesort(int32_t *vector, int32_t left, int32_t right) {
    if (left < right) {
        int32_t mid = left + (right - left) / 2;
        mergesort(vector, left, mid);
        mergesort(vector, mid + 1, right);
        merge(vector, left, mid, right);
    }
}
void swap(int32_t *a, int32_t *b) {
    int32_t temp = *a;
    *a = *b;
    *b = temp;
}

int32_t partition_last(int32_t *vector, int32_t low, int32_t high) {
    int32_t pivot = vector[high];
    int32_t i = low - 1;

    for (int32_t j = low; j < high; j++) {
        if (vector[j] < pivot) {
            i++;
            swap(&vector[i], &vector[j]);
        }
    }
    swap(&vector[i + 1], &vector[high]);
    return i + 1;
}

void quicksort_end(int32_t *vector, int32_t low, int32_t high) {
    if (low < high) {
        int32_t pi = partition_last(vector, low, high);
        quicksort_end(vector, low, pi - 1);
        quicksort_end(vector, pi + 1, high);
    }
}

int32_t partition_random(int32_t *vector, int32_t low, int32_t high) {
    int32_t aux = low + rand() % (high - low + 1);
    swap(&vector[aux], &vector[high]);
    return partition_last(vector, low, high);
}

void quicksort_random(int32_t *vector, int32_t low, int32_t high) {
    if (low < high) {
        int32_t pi = partition_random(vector, low, high);
        quicksort_random(vector, low, pi - 1);
        quicksort_random(vector, pi + 1, high);
    }
}

int32_t median(int32_t *vector, int32_t low, int32_t high) {
    int32_t mid = low + (high - low) / 2;
    if (vector[low] > vector[mid])
        swap(&vector[low], &vector[mid]);
    if (vector[low] > vector[high])
        swap(&vector[low], &vector[high]);
    if (vector[mid] > vector[high])
        swap(&vector[mid], &vector[high]);
    swap(&vector[mid], &vector[high]);
    return partition_last(vector, low, high);
}

void quicksort_median(int32_t *vector, int32_t low, int32_t high) {
    if (low < high) {
        int32_t pi = median(vector, low, high);
        quicksort_median(vector, low, pi - 1);
        quicksort_median(vector, pi + 1, high);
    }
}
void heapify(int32_t *vector, int32_t n, int32_t i) {
    int32_t maior = i;
    int32_t esquerda = 2 * i + 1;
    int32_t direita = 2 * i + 2;

    if (esquerda < n && vector[esquerda] > vector[maior])
        maior = esquerda;

    if (direita < n && vector[direita] > vector[maior])
        maior = direita;

    if (maior != i) {
        int32_t temp = vector[i];
        vector[i] = vector[maior];
        vector[maior] = temp;

        heapify(vector, n, maior);
    }
}

void heapsort(int32_t *vector, int32_t n) {
    for (int32_t i = n / 2 - 1; i >= 0; i--)
        heapify(vector, n, i);

    for (int32_t i = n - 1; i >= 0; i--) {
        int32_t temp = vector[0];
        vector[0] = vector[i];
        vector[i] = temp;

        heapify(vector, i, 0);
    }
}

int main(int argc, char *argv[]) {
    clock_t inicio, fim;
    int menu = atoi(argv[1]);
    char *nome_arquivo_entrada = argv[2];
    char *nome_arquivo_saida = argv[3];

    FILE *file = fopen(nome_arquivo_entrada, "rb");
    if (file == NULL) {
        printf("erro ao abrir o arquivo\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    int32_t tamanho_arquivo = ftell(file) / sizeof(int32_t);
    fseek(file, 0, SEEK_SET);

    int32_t *vector = malloc(tamanho_arquivo * sizeof(int32_t));
    if (vector == NULL) {
        printf("erro ao alocar memoria\n");
        fclose(file);
        return 1;
    }

    fread(vector, sizeof(int32_t), tamanho_arquivo, file);
    fclose(file);

    inicio = clock();
    switch (menu) {
        case 1:
            bubblesort(vector, tamanho_arquivo);
            break;
        case 2:
            bubblesortmelhorado(vector, tamanho_arquivo);
            break;
        case 3:
            insertionsort(vector, tamanho_arquivo);
            break;
        case 4:
            mergesort(vector, 0, tamanho_arquivo - 1);
            break;
        case 5:
            quicksort_end(vector,0,tamanho_arquivo-1);
            break;
        case 6:
            quicksort_random(vector,0,tamanho_arquivo-1);
            break;
        case 7:
            quicksort_median(vector,0,tamanho_arquivo-1);
            break;
        case 8:
            heapsort(vector,tamanho_arquivo);
            break;
        default:
            printf("Opcao invalida\n");
            free(vector);
            return 1;
    }
    fim = clock();

    FILE *filesaida = fopen(nome_arquivo_saida, "wb");
    if (filesaida == NULL) {
        printf("erro ao abrir o arquivo de saida\n");
        free(vector);
        return 1;
    }

    fwrite(vector, sizeof(int32_t), tamanho_arquivo, filesaida);
    fclose(filesaida);
    free(vector);

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("o tempo para executar a funcao foi de: %.3f segundos\n", tempo);
    return 0;
}
