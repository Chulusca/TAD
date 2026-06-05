Implementar la función recursiva removeIf que reciba
● list: una lista (puede estar vacía)
● criteria: una función que reciba un entero y retorne 1 ó 0
● count: un puntero a entero. No está inicializado
La función debe eliminar de list todos los elementos que al ser evaluados por la
función criteria retorne 1. En el parámetro *dim debe indicar cuántos elementos se
eliminaron
Ejemplo: si la lista fuera 2 -> 5 -> 1 -> 4 -> 3 -> 7 y la función criteria retorna 1 si
el elemento es par, la lista ahora es 5 -> 1 -> 3 -> 7, y se eliminaron 2 elementos
NO SE ADMITIRÁ UNA SOLUCIÓN QUE TENGA UN CICLO DENTRO DE LA
FUNCIÓN.
NO DEFINIR MACROS NI FUNCIONES AUXILIARES

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int head;
    struct node * tail;
} node;

typedef node * TList;