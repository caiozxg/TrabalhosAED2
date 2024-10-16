#include <stdio.h>
#include <stdlib.h>


//criar a estrutura da lista
typedef struct Node{
    int data;
    struct Node* next;



} Node;

//estrutura do nó cabeça
typedef struct HeadNode{
    struct Node *head;


}HeadNode;

//iniciar a lista apartir do nó cabeça
HeadNode* CreateList(){

    HeadNode *list = (HeadNode*)malloc(sizeof(Node));
    list->head = (Node*)malloc(sizeof(Node));
    list->head->next = NULL;
    return list;

}

void insertion(HeadNode* list,int data){
    Node *New = (Node*)malloc(sizeof(Node));
    New->data = data;
    New->next = NULL;
    if (list->head == NULL){
        list->head = New;
    }
    else{
        Node *aux = list->head;
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = New;
    }   

}


int main(){

HeadNode *list = CreateList();
insertion (list,9);
insertion (list,14);
insertion (list,12);
insertion (list,27);
insertion (list,30);
Node* lista = list->head;
while (lista->next != NULL){
    printf("->%d",lista->data);
    lista = lista->next;
}
    return 0;
}
