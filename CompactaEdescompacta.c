
//rgm 47534 
//caio de souza ortiz de angelis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#

typedef struct No {
    unsigned char simbolo;
    int frequencia;
    struct No *esquerda, *direita;
} No;

typedef struct {
    //maximo 256 pois a tabela asc vai de 0 a 255
    unsigned char codigoBits[256];
    int comprimento;
} CodigoHuffman;

No* criarNo(unsigned char simbolo, int frequencia, No *esquerda, No *direita) {
    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->simbolo = simbolo;
    novoNo->frequencia = frequencia;
    novoNo->esquerda = esquerda;
    novoNo->direita = direita;
    return novoNo;
}

No* construirArvoreHuffman(int frequencias[]) {
    No *lista[256];
    int tamanhoLista = 0;

    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            lista[tamanhoLista++] = criarNo(i, frequencias[i], NULL, NULL);
        }
    }

    while (tamanhoLista > 1) {
        int min1 = 0, min2 = 1;
        if (lista[min2]->frequencia < lista[min1]->frequencia) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }
        for (int i = 2; i < tamanhoLista; i++) {
            if (lista[i]->frequencia < lista[min1]->frequencia) {
                min2 = min1;
                min1 = i;
            } else if (lista[i]->frequencia < lista[min2]->frequencia) {
                min2 = i;
            }
        }
        No *novoNo = criarNo('\0', lista[min1]->frequencia + lista[min2]->frequencia,
                             lista[min1], lista[min2]);


        lista[min1] = novoNo;
        lista[min2] = lista[--tamanhoLista];
    }

    return lista[0];
}


void gerarCodigos(No *raiz, CodigoHuffman codigos[], unsigned char codigo[], int profundidade) {
    if (raiz->esquerda == NULL && raiz->direita == NULL) {
        codigos[raiz->simbolo].comprimento = profundidade;
        memcpy(codigos[raiz->simbolo].codigoBits, codigo, profundidade);
        return;
    }
    codigo[profundidade] = 0;
    gerarCodigos(raiz->esquerda, codigos, codigo, profundidade + 1);
    codigo[profundidade] = 1;
    gerarCodigos(raiz->direita, codigos, codigo, profundidade + 1);
}


void escreverArvore(No *raiz, FILE *saida) {
    if (raiz->esquerda == NULL && raiz->direita == NULL) {
        fputc('1', saida);
        fputc(raiz->simbolo, saida);
    } else {
        fputc('0', saida);
        escreverArvore(raiz->esquerda, saida);
        escreverArvore(raiz->direita, saida);
    }
}


No* lerArvore(FILE *entrada) {
    int bit = fgetc(entrada);
    if (bit == '1') {
        unsigned char simbolo = fgetc(entrada);
        return criarNo(simbolo, 0, NULL, NULL);
    }
    No *esquerda = lerArvore(entrada);
    No *direita = lerArvore(entrada);
    return criarNo('\0', 0, esquerda, direita);
}

void compactarArquivo(const char *nomeArquivo) {
    FILE *entrada = fopen(nomeArquivo, "rb");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir arquivo %s\n", nomeArquivo);
        return;
    }

    int frequencias[256] = {0};
    int simbolo;

    while ((simbolo = fgetc(entrada)) != EOF) {
        frequencias[simbolo]++;
    }
    rewind(entrada);

    No *raiz = construirArvoreHuffman(frequencias);
    CodigoHuffman codigos[256] = {0};
    unsigned char codigoTemp[256];
    gerarCodigos(raiz, codigos, codigoTemp, 0);

    char nomeSaida[100];
    snprintf(nomeSaida, sizeof(nomeSaida), "%s.cmp", nomeArquivo);
    FILE *saida = fopen(nomeSaida, "wb");

    escreverArvore(raiz, saida);

    unsigned char buffer = 0;
    int bitsNoBuffer = 0;
    while ((simbolo = fgetc(entrada)) != EOF) {
        for (int i = 0; i < codigos[simbolo].comprimento; i++) {
            buffer |= (codigos[simbolo].codigoBits[i] << (7 - bitsNoBuffer));
            bitsNoBuffer++;
            if (bitsNoBuffer == 8) {
                fputc(buffer, saida);
                buffer = 0;
                bitsNoBuffer = 0;
            }
        }
    }
    if (bitsNoBuffer > 0) {
        fputc(buffer, saida);
    }

    fclose(entrada);
    fclose(saida);
    
}

void descompactarArquivo(const char *nomeArquivo) {
    FILE *entrada = fopen(nomeArquivo, "rb");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir arquivo %s\n", nomeArquivo);
        return;
    }

    char nomeSaida[100];
    snprintf(nomeSaida, sizeof(nomeSaida), "%s.dcmp", nomeArquivo);
    FILE *saida = fopen(nomeSaida, "wb");

    No *raiz = lerArvore(entrada);
    No *atual = raiz;

    int simbolo;
    while ((simbolo = fgetc(entrada)) != EOF) {
        for (int i = 7; i >= 0; i--) {
            if ((simbolo & (1 << i)) == 0)
                atual = atual->esquerda;
            else
                atual = atual->direita;

            if (atual->esquerda == NULL && atual->direita == NULL) {
                fputc(atual->simbolo, saida);
                atual = raiz;
            }
        }
    }

    fclose(entrada);
    fclose(saida);
    printf("Arquivo descompactado como: %s\n", nomeSaida);
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <opcao> <nome_arquivo>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "c") == 0) {
        compactarArquivo(argv[2]);
    } else if (strcmp(argv[1], "d") == 0) {
        descompactarArquivo(argv[2]);
    } else {
        fprintf(stderr, "Opção inválida. Use 'c' para compactar e 'd' para descompactar.\n");
        return 1;
    }

    return 0;
}
