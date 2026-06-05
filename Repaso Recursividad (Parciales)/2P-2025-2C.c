#include <stdio.h>
#include <stdlib.h>


typedef struct node {
	int head;
	struct node * tail;
} node;

typedef node * TList;

TList removeIf(TList list, int (*criteria)(int), int * count){
	if (list == NULL) {
		*count = 0;
		return NULL;
	}

	//Paso recursivo
	list->tail = removeIf(list->tail, criteria, count);

	/* Luego decidir sobre el nodo actual */
	if(criteria(list->head) == 1){
		/* Hay que eliminar este nodo */
        TList siguiente = list->tail;
        free(list);
        *count += 1;
        return siguiente;	
	}
	return list;
}