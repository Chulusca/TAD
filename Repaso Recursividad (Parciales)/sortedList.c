#include <stdio.h>

typedef struct node * TList;

typedef struct node {
    int elem;
    struct node * tail;
} TNode;

TList sortedList(TList list){
    //Caso base
    if (list == NULL) return list;

    list->tail = sortedList(list->tail);

    //Caso donde tengo que eliminar
    if(list->tail != NULL){
        if(list->tail->elem <= list->elem){
            TList aux = list->tail;
            free(list);
            return aux;
        }
    }
    
    return list;
}
