#include <stdio.h>
#include <stdlib.h>

//Ejercicios de CLAUDE

//Listas ordenadas de forma descendente.
typedef struct node {
    int head;
    struct node * tail;
} node;

typedef node * TList;

//Implementacion de las funciones recursivas para trabajar con listas

//Funcion para agregar un nodo.
TList add(TList l, int n){
    if (l == NULL) {
        TList newNode = malloc(sizeof(node));
        newNode->head = n;
        newNode->tail = NULL;
        return newNode;
    }   
    if (n > l->head){
        TList newNode = malloc(sizeof(node));
        newNode->head = n;
        newNode->tail = l;
        return newNode;
    }
    l->tail = add(l->tail, n);
    return l;
}

//Funcion para imprimir la lista.
void printList(TList l){
    if(l == NULL) return;
    printf("%d ", l->head);
    printList(l->tail);
}

int countNodes(TList l){
    if(l == NULL) return 0;
    return 1 + countNodes(l->tail);
}

int sumElements(TList l){
    if(l == NULL) return 0;
    return l->head + sumElements(l->tail);
}

int findMax(TList l){
    
}

int contains(TList l, int target){
    if(l == NULL) return 0;
    if(l->head == target) return 1;
    return contains(l->tail, target);
}

int isSorted(TList l){
    if (l == NULL || l->tail == NULL) return 1;

    if(l->head < l->tail->head) return 0;

    return isSorted(l->tail);
}

TList findNode(TList l, int target){
    if(l == NULL) return NULL;

    if(l->head == target) return l;

    return findNode(l->tail, target);
}

TList insertAtEnd(TList l, int newValue){
    if(l == NULL){
        TList newNode = malloc(sizeof(node));
        newNode->head = newValue;
        newNode->tail = NULL;
        return newNode;
    }

    //Paso recursivo para actualizar la lista
    l->tail = insertAtEnd(l->tail, newValue);

    return l;
}

TList deleteNode(TList l, int target){
    if(l == NULL) return NULL;

    if(l->head == target){
        TList aux = l->tail;
        free(l);
        return aux;
    }
    l->tail = deleteNode(l->tail, target);
    return l;
}

TList reverseList(TList l){
    if(l == NULL || l->tail == NULL) return l;

    TList newHead = reverseList(l->tail);
    l->tail->tail = l;
    l->tail = NULL;
    return newHead;
}

TList copyList(TList l){

}

TList appendList(TList l1, TList l2){
    if(l1 == NULL) return l2;
    l1->tail = appendList(l1->tail, l2);
    return l1;
}