#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
//estrutura para pilhas
typedef struct nopilha {
    int valor;
    struct nopilha *proximo;
} Nopilha;

// Estrutura da pilha
typedef struct {
    Nopilha *topo;
    int tamanho;
} Pilha;

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

// Utilizado para listas duplamente encadeadas
typedef struct nodup {
    int valor;
    struct nodup *proximo;
    struct nodup *anterior;
} NoDup;

// Utilizada para listadup não circular
typedef struct {
    NoDup *inicio;
    int tamanho;
} ListaDup;




///////////////////////////////////////////////////////////
void iniciarPilha(Pilha *pilha);
void inserirPilha(Pilha *pilha, int valor);
int removerPilha(Pilha *pilha);
void imprimirPilha(Pilha pilha);
void limparPilha(Pilha *pilha);
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
void iniciarlistadup(ListaDup *listaduplamente);

///////////////////////////////////////////////////////////////
void iniciarlistadup(ListaDup *listadup) {
    listadup->inicio = (NoDup *)malloc(sizeof(NoDup));
    listadup->inicio->proximo = NULL;
    listadup->inicio->anterior = NULL;
    listadup->tamanho = 0;
}
// Função para inicializar a pilha
void iniciarPilha(Pilha *pilha) {
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

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




// busca em lista circular

No* busca2(ListaCircular *listacircular, int ant) {
    No *aux = listacircular->inicio;
    do {
        if (aux->valor == ant) {
            printf("Elemento encontrado\n");
            return aux;
        }
        aux = aux->proximo;
    } while (aux != listacircular->inicio);
    
    printf("Elemento nao encontrado\n");
    return NULL;
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
                busca2(listacircular, num); 
                break;
            case 2:
                printf("Qual numero voce deseja inserir?\n");
                scanf("%d", &num);
                inserir2(listacircular, num);
                break;
            case 3:
                printf("Qual numero voce deseja remover?\n");
                scanf("%d", &num);
                remover2(listacircular, num); 
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


//lista duplamente encadeada com nó cabeça
// Busca na listadup simplesmente encadeada sem nó cabeça ordenada
NoDup* busca3(ListaDup *listadup, int ant) {
    NoDup *aux;
    aux = listadup->inicio;
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

// Remoção na listadup simplesmente encadeada sem nó cabeça ordenada
void remover3(ListaDup *listadup, int num) {
    NoDup *aux = listadup->inicio->proximo;
    while (aux != NULL && aux->valor != num) {
        aux = aux->proximo;
    }
    
    if (aux != NULL) {
        if (aux->anterior != NULL) {
            aux->anterior->proximo = aux->proximo;
            
        }
        if (aux->proximo != NULL) {
            aux->proximo->anterior = aux->anterior;
           
        }
       
        free(aux);
        listadup->tamanho--;
    }
}

// Inserção na lista duplamente encadeada sem nó cabeça ordenada
void inserir3(ListaDup *listadup, int num) {
    NoDup *novo = (NoDup *)malloc(sizeof(NoDup));
    if (novo == NULL) {
        printf("Erro ao alocar memória para novo no.\n");
        return;
    }

    novo->valor = num;
    novo->proximo = NULL;

    // Encontra o último nó
    NoDup *ultimo = listadup->inicio;
    while (ultimo->proximo != NULL) {
        ultimo = ultimo->proximo;
    }

    // Insere o novo nó após o último
    ultimo->proximo = novo;
    novo->anterior = ultimo;

    listadup->tamanho++;
}

// Função para imprimir listadup simplesmente encadeada
void imprimirdup(ListaDup listadup) {
    NoDup *no = listadup.inicio->proximo;
    if (listadup.inicio->proximo == NULL){
        printf("Lista Duplamente encadeada vazia\n");
        return;
    }
    printf("Lista Duplamente encadead: ");
    while (no != NULL) {
        printf("-> %d ", no->valor);
        no = no->proximo;
    }
    printf("\n");
}

// Função principal para operações em lista duplamente encadeada
void listaduplamente(ListaDup *listadup) {
    printf("-----------------------------------------\n");
    printf("Operacoes em listadup simplesmente encadeada\n");
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
                busca3(listadup, num);
                break;
            case 2:
                printf("Qual numero voce deseja inserir?\n");
                scanf("%d", &num);
                inserir3(listadup, num);
                break;
            case 3:
                printf("Qual numero voce deseja remover?\n");
                scanf("%d", &num);
                remover3(listadup, num);
                break;
            case 4:
                imprimirdup(*listadup);
                break;
            case 0:
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida! Por favor, escolha uma opcao valida.\n");
        }
    } while (menu != 0);
}

// Função para inserir um elemento na pilha
void inserir4(Pilha *pilha, int valor) {
    Nopilha *novo = (Nopilha *)malloc(sizeof(Nopilha));
    if (novo == NULL) {
        printf("Erro ao alocar memória para novo nó.\n");
        return;
    }
    novo->valor = valor;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
}

// Função para remover um elemento da pilha
int remover4(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha está vazia.\n");
        return -1; // Indicador de erro
    }
    Nopilha *remover = pilha->topo;
    int valor = remover->valor;
    pilha->topo = pilha->topo->proximo;
    free(remover);
    pilha->tamanho--;
    return valor;
}


void pilhamenu(Pilha *pilha) {
    printf("-----------------------------------------\n");
    printf("Operacoes em listadup simplesmente encadeada\n");
    int menu, num;

    do {
        printf("\nMenu:\n");
        printf("1. Insercao\n");
        printf("2. Remocao\n");
        printf("3. Imprimir\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("Qual numero voce deseja inserir?\n");
                scanf("%d", &num);
                inserir4(pilha, num);
                break;
            case 2:
                remover4(pilha);
                break;
            case 3:
                imprimirPilha(*pilha);
                break;
            case 0:
                printf("Saindo...\n");
                exit(0);
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
// Função para imprimir os elementos da pilha
void imprimirPilha(Pilha pilha) {
    Nopilha *no = pilha.topo;

    printf("Pilha: ");
    if (pilha.topo == NULL){
        printf("vazia!");
    }
    while (no != NULL) {
        if (no != NULL){
        printf("%d", no->valor);
        if (no->proximo != NULL)
        printf(" -> ");
        }
        no = no->proximo;
    }
    
}

int main() {
    int escolha;
    Lista lista;
    ListaCircular listacircular;
    ListaDup listadup;
    Pilha pilha;
    iniciarlista(&lista);
    iniciarlistaCircular(&listacircular);
    iniciarlistadup(&listadup);
    iniciarPilha(&pilha);
    
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
                listaduplamente(&listadup);
                break;
            case 4:
                // fila(); // Faltando implementação
                break;
            case 5:
                pilhamenu(&pilha);
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
