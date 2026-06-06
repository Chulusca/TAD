#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char head;
    int hits;
    struct node * tail;
} node;

typedef node * TList;

TList addElem(TList l, char elem){
    if (l == NULL) {
        TList newNode = malloc(sizeof(node));
        newNode->hits = 0;
        newNode->head = elem;
        newNode->tail = NULL;
        return newNode;
    }

    if(l->head == elem){
        l->hits++;
    }
    else{
        l->tail = addElem(l->tail, elem); 
    }

    if(l->tail != NULL && l->tail->hits > l->hits){
        //swapeo
        char aux;
        int aux2;
        aux = l->head;
        aux2 = l->hits;

        l->head = l->tail->head;
        l->hits = l->tail->hits;

        l->tail->head = aux;
        l->tail->hits = aux2;
    }
    return l;

}


//X NULL 
//2