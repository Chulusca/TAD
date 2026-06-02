#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node * next;
} node;

typedef node * list;

list removeIf(list l, int (*criteria)(int), int* count){
    if (l == NULL) {
        // Como el enunciado dice que count "no está inicializado", 
        // el mejor lugar para inicializarlo en 0 es el final de la recursión.
        *count = 0;
        return NULL;
    }
    // 2. Paso recursivo: procesamos el resto de la lista primero.
    // Esto conectará el nodo actual con el resultado de filtrar lo que le sigue.
    l->next = removeIf(l->next, criteria, count);

    if (criteria(l->elem) == 1) {
        list aux = l->next; // Guardamos la referencia al siguiente nodo
        free(l);            // Liberamos la memoria del nodo actual
        (*count)++;         // Incrementamos la cantidad de eliminados
        return aux;         // Retornamos la nueva cabeza (el nodo siguiente)
    }
    return l;
}