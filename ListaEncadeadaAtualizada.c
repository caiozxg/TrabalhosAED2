#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

// Estrutura para listas simplesmente encadeadas
typedef struct no {
    int valor;
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
    int tamanho;
} Lista;

typedef struct {
    No *inicio;
    No *fim;
    int tamanho;
} ListaCircular;



///////////////////////////////////////////////////////////

void iniciarlistaCircular(ListaCircular *listacircular);
void iniciarlista(Lista *lista);
No* busca1(Lista *lista, int ant);
void remover1(Lista *lista, int num);
void inserir1(Lista *lista, int num);
void listaSimples(Lista *lista);
void inserir2(ListaCircular *listacircular, int num);
void listaCircularmenu(ListaCircular *listacircular);
void imprimir(Lista *lista);
void imprimircircular(ListaCircular *listacircular);

///////////////////////////////////////////////////////////////

void iniciarlistaCircular(ListaCircular *listacircular) {
    listacircular->inicio = NULL;
    listacircular->fim = NULL;
    listacircular->tamanho = 0;
}

void iniciarlista(Lista *lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

// Busca lista simplesmente encadeada sem nó cabeça ordenada
No* busca1(Lista *lista, int ant) {
    No *aux = lista->inicio;
    while (aux != NULL && aux->valor != ant) {
        aux = aux->proximo;
    }
    if (aux == NULL) {
        printf("Elemento nao encontrado\n");
    } else {
        printf("Elemento encontrado\n");
    }
    return aux;
}

// Remoção lista simplesmente encadeada sem nó cabeça ordenada
void remover1(Lista *lista, int num) {
    No *aux = lista->inicio;
    No *remover = NULL;
    if (aux != NULL && aux->valor == num) {
        remover = aux;
        lista->inicio = aux->proximo;
    } else {
        while (aux != NULL && aux->proximo != NULL && aux->proximo->valor != num) {
            aux = aux->proximo;
        }
        if (aux != NULL && aux->proximo != NULL) {
            remover = aux->proximo;
            aux->proximo = remover->proximo;
        }
    }
    if (remover != NULL) {
        free(remover);
        lista->tamanho--;
        printf("Elemento removido\n");
    } else {
        printf("Elemento nao encontrado\n");
    }
}

// Inserção lista simplesmente encadeada sem nó cabeça ordenada
void inserir1(Lista *lista, int num) {
    No *aux, *novo = malloc(sizeof(No));
    if (novo != NULL) {
        novo->valor = num;
        if (lista->inicio == NULL) {
            novo->proximo = NULL;
            lista->inicio = novo;
        } else if (novo->valor < lista->inicio->valor) {
            novo->proximo = lista->inicio;
            lista->inicio = novo;
        } else {
            aux = lista->inicio;
            while (aux->proximo != NULL && novo->valor > aux->proximo->valor) {
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        lista->tamanho++;
    } else {
        printf("Erro ao alocar a memoria!\n");
    }
}

// Lista simplesmente encadeada sem nó cabeça ordenada
void listaSimples(Lista *lista) {
    printf("-----------------------------------------\n");
    printf("Operacoes em lista simplesmente encadeada\n");
    int menu, num;

    do {
        printf("\nMenu:\n");
        printf("1. Busca\n");
        printf("2. Insercao\n");
        printf("3. Remocao\n");
        printf("4. Imprimir\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("Qual numero voce deseja buscar?\n");
                scanf("%d", &num);
                busca1(lista, num);
                break;
            case 2:
                printf("Qual numero voce deseja inserir?\n");
                scanf("%d", &num);
                inserir1(lista, num);
                break;
            case 3:
                printf("Qual numero voce deseja remover?\n");
                scanf("%d", &num);
                remover1(lista, num);
                break;
            case 4:
                imprimir(lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Por favor, escolha uma opcao valida.\n");
        }
    } while (menu != 0);
}

// Inserir em lista circular
void inserir2(ListaCircular *listacircular, int num) {
    No *aux, *novo = malloc(sizeof(No));
    if (novo != NULL) {
        novo->valor = num;
        if (listacircular->inicio == NULL) {
            listacircular->inicio = novo;
            listacircular->fim = novo;
            listacircular->fim->proximo=listacircular->inicio;
            //tambem insere no começo
        } else if (novo->valor < listacircular->inicio->valor) {
            novo->proximo = listacircular->inicio;
            listacircular->inicio = novo;
            listacircular->fim->proximo = listacircular->inicio;
        } else {
            aux = listacircular->inicio;
            while (aux->proximo != listacircular->inicio && novo->valor > aux->proximo->valor) {
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
            if (novo->proximo == listacircular->inicio) {
                listacircular->fim = novo;
            }
        }
        listacircular->tamanho++;
    } else {
        printf("Erro ao alocar a memoria!\n");
    }
}










No* remover2(ListaCircular *listacircular,int num){
 No *aux, *remover = NULL;

    if(listacircular->inicio){
        if(listacircular->inicio == listacircular->fim && listacircular->inicio->valor == num){
            remover = listacircular->inicio;
            listacircular->inicio = NULL;
            listacircular->fim = NULL;
            listacircular->tamanho--;
        }
        else if(listacircular->inicio->valor == num){
            remover = listacircular->inicio;
            listacircular->inicio = remover->proximo;
            listacircular->fim->proximo = listacircular->inicio;
            listacircular->tamanho--;
        }
        else{
            aux = listacircular->inicio;
            while(aux->proximo != listacircular->inicio && aux->proximo->valor != num)
                aux = aux->proximo;
            if(aux->proximo->valor == num){
                if(listacircular->fim == aux->proximo){
                    remover = aux->proximo;
                    aux->proximo = remover->proximo;
                    listacircular->fim = aux;
                }
                else{
                    remover = aux->proximo;
                    aux->proximo = remover->proximo;
                }
                listacircular->tamanho--;
            }
        }
    }

    return remover;
}
























void listaCircularmenu(ListaCircular *listacircular) {
    printf("------------------------------------------------------------------\n");
    printf("Operacoes em lista simplesmente encadeada, circular, sem no cabeca\n");
    int menu, num;

    do {
        printf("\nMenu:\n");
        printf("1. Busca\n");
        printf("2. Insercao\n");
        printf("3. Remocao\n");
        printf("4. Imprimir\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("Qual numero voce deseja buscar?\n");
                scanf("%d", &num);
                // busca2(&listacircular, num); // Faltando implementação
                break;
            case 2:
                printf("Qual numero voce deseja inserir?\n");
                scanf("%d", &num);
                inserir2(listacircular, num);
                break;
            case 3:
                printf("Qual numero voce deseja remover?\n");
                scanf("%d", &num);
                // remover2(&listacircular, num); // Faltando implementação
                break;
            case 4:
                imprimircircular(listacircular);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Por favor, escolha uma opcao valida.\n");
        }
    } while (menu != 0);
}

void imprimir(Lista *lista) {
    No *no = lista->inicio; 
    while (no != NULL) {
        printf("->%d", no->valor);
        no = no->proximo;
    }
    printf("\n");
}

void imprimircircular(ListaCircular *listacircular) {
    if (listacircular->inicio == NULL) {
        printf("Lista vazia\n");
        return;
    }
    No *teste = listacircular->inicio; 
    do {
        printf("->%d", teste->valor);
        teste = teste->proximo;
    } while (teste != listacircular->inicio);
    printf("\n");
}

int main() {
    int escolha;
    Lista lista;
    ListaCircular listacircular;
    iniciarlista(&lista);
    iniciarlistaCircular(&listacircular);

    do {
        printf("\nMenu:\n");
        printf("1. Busca, insercao e remocao em lista simplesmente encadeada sem no cabeca ordenada\n");
        printf("2. Busca, insercao e remocao em lista circular simplesmente encadeada sem no cabeca ordenada\n");
        printf("3. Busca, insercao e remocao em lista duplamente encadeada com no cabeca (sem ordenacao)\n");
        printf("4. Insercao e remocao em fila\n");
        printf("5. Insercao e remocao em pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                listaSimples(&lista);
                break;
            case 2:
                listaCircularmenu(&listacircular);
                break;
            case 3:
                // listaDuplamenteEncadeada(); // Faltando implementação
                break;
            case 4:
                // fila(); // Faltando implementação
                break;
            case 5:
                // pilha(); // Faltando implementação
                break;
            case 0:
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}
