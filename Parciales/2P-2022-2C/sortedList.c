#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node * TList;

typedef struct node {
    int elem;
    struct node * tail;
} TNode;

TList sortedList(TList l){
    if(l == NULL) return NULL;

    if(l->tail != NULL){
        if(l->elem >= l->tail->elem){
            TList aux = l->tail;
            free(l);
            return sortedList(aux);
        }
        l->tail = sortedList(l->tail);
        return l;
    }
    return l;
}