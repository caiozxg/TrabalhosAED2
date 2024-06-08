# TrabalhosAED2

#include <stdlib.h>

#include <stdio.h> 
#include <unistd.h>



//utilizado para listas simplesmente encadeadas
typedef struct no{
    int valor;
    struct no *proximo;


}No;

///////////////////////////////////////////////////////////////////////////
//utilizada para nao circular
typedef struct {

    No *inicio;
    int tamanho;
}Lista;

typedef struct {

    No *inicio;
    No *fim;
    int tamanho;
}ListaCircular;


void iniciarlistaCircular(ListaCircular *listacircular);
void iniciarlista(Lista *lista);
No* busca1(Lista *lista, int ant);
No* remover1(Lista *lista, int num);
void inserir1(Lista *lista, int num);
void listaSimples(Lista *lista);
void inserir2(ListaCircular *listacircular, int num);
void listacircularmenu(ListaCircular *listacircular);
void imprimir(Lista lista);
void imprimircircular(ListaCircular listacircular);
//////////////////////////////////////////////////////////////////////////
void iniciarlistaCircular(ListaCircular *listacircular){
    listacircular->inicio = NULL;
    listacircular->fim = NULL;
    listacircular->tamanho = 0;
    


}



void iniciarlista(Lista *lista){
    lista->inicio = NULL;
    lista->tamanho = 0;


}

/////////////////////////////////////////////////////////////////////////

//busca lista simplesmente encadeada sem nó cabeça ordenada
No* busca1(Lista *lista,int ant){
    No *aux;
    aux = NULL;
    aux=lista->inicio;
    while (aux->proximo != NULL && aux->valor != ant){
        aux=aux->proximo;
    }
    if(aux == NULL){
        printf("elemento nao encontrado");
    
    }else{
        printf("elemento encontrado");
    }
        return aux;
}
//remoção lista simplesmente encadeada sem nó cabeça ordenada
No* remover1(Lista *lista,int num){
   
        No *aux,*remover = NULL;
        aux = lista->inicio;
        if (lista->inicio != NULL){
        while (aux->proximo->valor != num && aux->proximo != NULL){
            aux=aux->proximo;

        }
        if (aux->proximo){
        remover=aux->proximo;
        aux->proximo = remover->proximo;
        free(remover);
        }else{
            printf("elemento nao encontrado");
        }
        }else{
            printf("lista vazia!");
        }

}

//////////////////////////////////////////////////////////////////////////////

//inserção lista simplesmente encadeada sem nó cabeça ordenada
void inserir1(Lista *lista,int num){
    No *aux,*novo = malloc(sizeof(No));
    //testar se o novo nó foi corretamente alocado
    if (novo != NULL){
        novo->valor = num;
        //testamos se a lista esta vazia(será o primeiro numero da lista)
        if (lista->inicio == NULL){
            novo->proximo = NULL;
            lista->inicio = novo;
        }
        //caso o numero seja o menor de todos
        else if(novo->valor < lista->inicio->valor){
            novo->proximo = lista->inicio;
            lista->inicio = novo;
        }
        //outros casos
        else{

            
            aux = lista->inicio;
          
            while (aux->proximo != NULL && novo->valor > aux->proximo->valor){
                aux = aux->proximo;
            }
            novo->proximo=aux->proximo;
            aux->proximo=novo;
        }
         lista->tamanho++;
    }
    
    else{
        printf("ERRO AO ALOCAR A MEMORIA!");
    }


}

//1-lista simplesmente encadeada sem nó cabeça ordenada;
void listaSimples(Lista *lista) {
    printf("-----------------------------------------\n");
    printf("Operacoes em lista simplesmente encadeada\n");
    int menu,num;

    // Loop para manter o menu sendo exibido até que o usuário decida sair
    do {
        // Exibindo o menu
    
        printf("\nMenu:\n");
        printf("1. Busca\n");
        printf("2. Inserção\n");
        printf("3. Remoção\n");
        printf("4-imprimir");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &menu);

        // Verificando a escolha do usuário usando switch case
        switch (menu) {
            case 1:
                printf("qual numero voce deseja buscar?\n");
                scanf("%d",&num);
                busca1(&lista,num);
                break;
            case 2:
                printf("qual numero voce deseja inserir?\n");
                scanf("%d",&num);
                inserir1(&lista,num);
                break;
            case 3:
                printf("qual numero voce deseja remover?\n");
                scanf("%d",&num);
                remover1(&lista,num);
                break;
            case 4:
                imprimir(lista);
                break;
            case 0:
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opção invalida! Por favor, escolha uma opção valida.\n");
        }
    } while (menu != 0);

}
//2-Busca, inserção e remoção em lista circular simplesmente encadeada sem nó cabeça ordenada;

//busca em circular


//inserir em cicular
void inserir2(ListaCircular *listacircular,int num){
    No *aux,*novo = malloc(sizeof(No));
    //testar se o novo nó foi corretamente alocado
    if (novo != NULL){
        novo->valor = num;
        //testamos se a lista esta vazia(será o primeiro numero da lista)
        if (listacircular->inicio == NULL){
            listacircular->inicio = novo;
            listacircular->fim= novo;
            listacircular->fim->proximo=listacircular->inicio;

        }
        //caso o numero seja o menor de todos
        else if(novo->valor < listacircular->inicio->valor){
            novo->proximo = listacircular->inicio;
            listacircular->inicio = novo;
            listacircular->fim->proximo = novo;

        }
        //outros casos
        else{

            
            aux = listacircular->inicio;
          
            while (aux->proximo != NULL && novo->valor > aux->proximo->valor){
                aux = aux->proximo;
            }
            novo->proximo=aux->proximo;
            aux->proximo=novo;
        }
         listacircular->tamanho++;
    }
    
    else{
        printf("ERRO AO ALOCAR A MEMORIA!");
    }
}











void listaCircularmenu(ListaCircular *listacircular){
    printf("----------------------------------------------------------------\n");
    printf("Operacoes em lista simplesmente encadeada,circular,sem no cabeca\n");
    int menu,num;

    // Loop para manter o menu sendo exibido até que o usuário decida sair
    do {
        // Exibindo o menu
    
        printf("\nMenu:\n");
        printf("1. Busca\n");
        printf("2. Inserção\n");
        printf("3. Remoção\n");
        printf("4-imprimir");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &menu);

        // Verificando a escolha do usuário usando switch case
        switch (menu) {
            case 1:
                printf("qual numero voce deseja buscar?\n");
                scanf("%d",&num);
               // busca2(&listacircular,num);
                break;
            case 2:
                printf("qual numero voce deseja inserir?\n");
                scanf("%d",&num);
                inserir2(&listacircular,num);
                break;
            case 3:
                printf("qual numero voce deseja remover?\n");
                scanf("%d",&num);
                //remover2(&listacircular,num);
                break;
            case 4:
                imprimircircular(listacircular);
                break;
            case 0:
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opção invalida! Por favor, escolha uma opção valida.\n");
        }
    } while (menu != 0);
}




void imprimir(Lista lista){
    //imprimiremos a lista(uma copia dela,por isso o .)
    No *no=lista.inicio->proximo; 
   
    while (no !=NULL){
        
        
        printf("->%d",no->valor);
        no=no->proximo;
         
    }



}

void imprimircircular(ListaCircular listacircular){
    //imprimiremos a lista(uma copia dela,por isso o .)
    No *teste;
    teste=listacircular.inicio; 
    while (teste != listacircular.inicio){
        
        
        printf("->%d",teste->valor);
        teste=teste->proximo;
         
    }



}






//função principal
int main(){

     int escolha;
     Lista lista;
     ListaCircular listacircular;
     iniciarlista(&lista);
     iniciarlistaCircular(&listacircular);
//menu para escolher qual opção sera usada
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
            //    listaDuplamenteEncadeada();
                break;
            case 4:
             //   fila();
                break;
            case 5:
              //  pilha();
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
