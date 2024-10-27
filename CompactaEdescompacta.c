#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX 256

typedef struct NoHeap {
    unsigned char dado;
    int frequencia;
    struct NoHeap *esquerda, *direita;
} NoHeap;

typedef struct HeapMin {
    unsigned tamanho;
    unsigned capacidade;
    NoHeap **array;
} HeapMin;

typedef struct Codigo {
    char codigo[TAMANHO_MAX];
} Codigo;

Codigo tabelaCodigos[TAMANHO_MAX];

// Função para criar um novo nó
NoHeap* novoNo(unsigned char dado, int frequencia) {
    NoHeap* temp = (NoHeap*) malloc(sizeof(NoHeap));
    temp->esquerda = temp->direita = NULL;
    temp->dado = dado;
    temp->frequencia = frequencia;
    return temp;
}

// Função para criar uma heap mínima
HeapMin* criarHeapMin(unsigned capacidade) {
    HeapMin* heapMin = (HeapMin*) malloc(sizeof(HeapMin));
    heapMin->tamanho = 0;
    heapMin->capacidade = capacidade;
    heapMin->array = (NoHeap**) malloc(capacidade * sizeof(NoHeap*));
    return heapMin;
}

// Função para trocar dois nós da heap
void trocarNoHeap(NoHeap** a, NoHeap** b) {
    NoHeap* temp = *a;
    *a = *b;
    *b = temp;
}

// Função para garantir a propriedade de heap mínima (minHeapify)
void minHeapify(HeapMin* heapMin, unsigned int idx) {
    unsigned int menor = idx;
    unsigned int esquerda = 2 * idx + 1;
    unsigned int direita = 2 * idx + 2;

    if (esquerda < heapMin->tamanho && heapMin->array[esquerda]->frequencia < heapMin->array[menor]->frequencia)
        menor = esquerda;

    if (direita < heapMin->tamanho && heapMin->array[direita]->frequencia < heapMin->array[menor]->frequencia)
        menor = direita;

    if (menor != idx) {
        trocarNoHeap(&heapMin->array[menor], &heapMin->array[idx]);
        minHeapify(heapMin, menor);
    }
}

// Função para verificar se o heap tem tamanho 1
int tamanhoUm(HeapMin* heapMin) {
    return (heapMin->tamanho == 1);
}

// Função para remover o nó de menor frequência da heap
NoHeap* extrairMin(HeapMin* heapMin) {
    NoHeap* temp = heapMin->array[0];
    heapMin->array[0] = heapMin->array[heapMin->tamanho - 1];
    --(heapMin->tamanho);
    minHeapify(heapMin, 0);
    return temp;
}

// Função para inserir um nó na heap
void inserirHeapMin(HeapMin* heapMin, NoHeap* noHeap) {
    ++(heapMin->tamanho);
    unsigned int i = heapMin->tamanho - 1;

    while (i && noHeap->frequencia < heapMin->array[(i - 1) / 2]->frequencia) {
        heapMin->array[i] = heapMin->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heapMin->array[i] = noHeap;
}

// Função para construir uma heap mínima inicializada
HeapMin* construirEPreencherHeap(unsigned char dados[], int frequencias[], int tamanho) {
    HeapMin* heapMin = criarHeapMin(tamanho);

    for (int i = 0; i < tamanho; ++i)
        heapMin->array[i] = novoNo(dados[i], frequencias[i]);

    heapMin->tamanho = tamanho;

    for (int i = (heapMin->tamanho - 1) / 2; i >= 0; --i)
        minHeapify(heapMin, i);

    return heapMin;
}

// Função para construir a árvore de Huffman
NoHeap* construirArvoreHuffman(unsigned char dados[], int frequencias[], int tamanho) {
    NoHeap *esquerda, *direita, *topo;
    HeapMin* heapMin = construirEPreencherHeap(dados, frequencias, tamanho);

    while (!tamanhoUm(heapMin)) {
        esquerda = extrairMin(heapMin);
        direita = extrairMin(heapMin);

        topo = novoNo('$', esquerda->frequencia + direita->frequencia);
        topo->esquerda = esquerda;
        topo->direita = direita;

        inserirHeapMin(heapMin, topo);
    }

    return extrairMin(heapMin);
}

// Função para gerar os códigos de Huffman
void gerarCodigos(NoHeap* raiz, char codigo[], int topo) {
    if (raiz->esquerda) {
        codigo[topo] = '0';
        gerarCodigos(raiz->esquerda, codigo, topo + 1);
    }

    if (raiz->direita) {
        codigo[topo] = '1';
        gerarCodigos(raiz->direita, codigo, topo + 1);
    }

    if (!(raiz->esquerda) && !(raiz->direita)) {
        codigo[topo] = '\0';
        strcpy(tabelaCodigos[raiz->dado].codigo, codigo);
    }
}

// Função para serializar a árvore de Huffman no arquivo
void serializarArvore(NoHeap *raiz, FILE *saida) {
    if (!raiz) {
        fputc('#', saida); // Caractere especial para nó nulo
        return;
    }
    fputc(raiz->dado, saida);
    serializarArvore(raiz->esquerda, saida);
    serializarArvore(raiz->direita, saida);
}

// Função para desserializar a árvore de Huffman do arquivo
NoHeap* desserializarArvore(FILE *entrada) {
    unsigned char dado = fgetc(entrada);
    if (dado == '#') return NULL;

    NoHeap* no = novoNo(dado, 0);
    no->esquerda = desserializarArvore(entrada);
    no->direita = desserializarArvore(entrada);
    return no;
}

// Função auxiliar para escrever bits no arquivo
void escreverBits(FILE *arquivo, unsigned char *buffer, int *indice, unsigned char bit) {
    if (bit == '1')
        buffer[*indice / 8] |= (1 << (7 - (*indice % 8))); // Define o bit na posição correta
    (*indice)++;

    // Se o buffer estiver cheio (8 bits), escreva-o no arquivo
    if (*indice == 8) {
        fwrite(buffer, sizeof(unsigned char), 1, arquivo);
        buffer[0] = 0; // Limpa o buffer
        *indice = 0;
    }
}

// Função para compactar o arquivo
void compactarArquivo(char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    int frequencias[TAMANHO_MAX] = {0};
    unsigned char c;
    while (fread(&c, sizeof(unsigned char), 1, file)) 
        frequencias[c]++;
    
    fclose(file);

    unsigned char dados[TAMANHO_MAX];
    int tamanho = 0;
    for (int i = 0; i < TAMANHO_MAX; i++) {
        if (frequencias[i] > 0) {
            dados[tamanho] = i;
            tamanho++;
        }
    }

    NoHeap* raiz = construirArvoreHuffman(dados, frequencias, tamanho);

    // Gerar nome do arquivo de saída para compactação
    char nome_saida[256];
    snprintf(nome_saida, sizeof(nome_saida), "%s.cmp", nome_arquivo);
    FILE *saida = fopen(nome_saida, "wb");
    if (!saida) {
        printf("Erro ao criar o arquivo de saída\n");
        return;
    }

    // Serializar a árvore de Huffman no arquivo de saída
    serializarArvore(raiz, saida);

    // Reabrir o arquivo de entrada para leitura dos dados originais
    file = fopen(nome_arquivo, "rb");

    // Gerar códigos de Huffman
    char codigo[TAMANHO_MAX];
    gerarCodigos(raiz, codigo, 0);

    // Preparar para a escrita dos bits no arquivo compactado
    unsigned char buffer = 0; // Buffer para armazenar os bits antes de escrever no arquivo
    int indice = 0;            // Posição atual no buffer

    // Codificar os dados e escrever no arquivo compactado
    while (fread(&c, sizeof(unsigned char), 1, file)) {
        char *codigo_huffman = tabelaCodigos[c].codigo; // Obter o código Huffman correspondente ao caractere

        // Escrever cada bit do código Huffman no arquivo
        for (int i = 0; codigo_huffman[i] != '\0'; i++) {
            escreverBits(saida, &buffer, &indice, codigo_huffman[i]);
        }
    }

    // Se houver bits restantes no buffer (menos que 8 bits), gravá-los
    if (indice > 0) {
        fwrite(&buffer, sizeof(unsigned char), 1, saida);
    }

    // Fechar arquivos
    fclose(file);
    fclose(saida);
}

// Função para ler bits do arquivo durante a descompactação
unsigned char lerBit(FILE *arquivo, unsigned char *buffer, int *indice, int *tamanho_buffer) {
    // Se todos os bits do buffer foram lidos, carregue o próximo byte
    if (*indice == *tamanho_buffer) {
        fread(buffer, sizeof(unsigned char), 1, arquivo);
        *indice = 0;
        *tamanho_buffer = 8;
    }

    // Extrair o bit do buffer
    unsigned char bit = ((*buffer >> (7 - *indice)) & 1);
    (*indice)++;
    return bit;
}

// Função para descompactar o arquivo
void descompactarArquivo(char *nome_arquivo) {
    char nome_saida[256];
    snprintf(nome_saida, sizeof(nome_saida), "%s.dcmp", nome_arquivo);
    FILE *entrada = fopen(nome_arquivo, "rb");
    FILE *saida = fopen(nome_saida, "wb");

    if (!entrada || !saida) {
        printf("Erro ao abrir arquivo de entrada ou saída\n");
        return;
    }

    // Desserializar a árvore de Huffman do arquivo de entrada
    NoHeap* raiz = desserializarArvore(entrada);

    // Preparar para leitura de bits do arquivo compactado
    unsigned char buffer = 0;
    int indice = 0;
    int tamanho_buffer = 0;

    // Lógica para ler bits e descompactar os dados usando a árvore de Huffman
    NoHeap* atual = raiz;
    while (1) {
        unsigned char bit = lerBit(entrada, &buffer, &indice, &tamanho_buffer);

        // Navegar na árvore de Huffman com base nos bits lidos
        if (bit == 0) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }

        // Se chegamos em uma folha, escrevemos o caractere no arquivo de saída
        if (!(atual->esquerda) && !(atual->direita)) {
            fputc(atual->dado, saida);
            atual = raiz; // Retornar à raiz para decodificar o próximo caractere
        }

        // Se o arquivo de entrada acabar, terminamos a descompactação
        if (feof(entrada)) {
            break;
        }
    }

    fclose(entrada);
    fclose(saida);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <opcao> <arquivo>\nOpcoes: c (compactar), d (descompactar)\n", argv[0]);
        return 1;
    }

    char opcao = argv[1][0];
    char *nome_arquivo = argv[2];

    if (opcao == 'c') {
        compactarArquivo(nome_arquivo);
    } else if (opcao == 'd') {
        descompactarArquivo(nome_arquivo);
    } else {
        printf("Opcao invalida. Use 'c' para compactar ou 'd' para descompactar.\n");
        return 1;
    }

    return 0;
}

