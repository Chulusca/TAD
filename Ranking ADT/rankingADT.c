#include "rankingADT.h"
#include <stdio.h>
#include <stdlib.h>
#define BLOQUE 5
typedef struct rankingCDT {
    elemType * elements;
    size_t size;
    size_t capacity;
    compare cmp;
} rankingCDT;

rankingADT newRanking(elemType elems[], size_t dim, compare cmp){
    rankingADT r = malloc(sizeof(struct rankingCDT));
    r->size = dim;
    r->capacity = dim > 0 ? dim : 10; // Capacidad inicial base si dim es 0
    r->elements = malloc(r->capacity * sizeof(elemType));
    r->cmp = cmp;
    for (size_t i = 0; i < dim; i++) {
        r->elements[i] = elems[i];
    }
    return r;
}

void addRanking(rankingADT ranking, elemType elem){
    //Recorro ranking buscando si existe el elemnto
    char encontrado = 0;
    for (size_t i = 0; i < ranking->size && !encontrado; i++)
    {
        if(ranking->cmp(ranking->elements[i], elem) == 0){
            encontrado = 1;
            //Existe
            if(i != 0){
                elemType aux = ranking->elements[i-1];
                ranking->elements[i-1] = ranking->elements[i];
                ranking->elements[i] = aux;
            }
        }
    }
    //No existe lo añado al final (Validar si tengo espacio para hacerlo)
    if(!encontrado){ 
        if(ranking->size == ranking->capacity){
            ranking->elements = realloc(ranking->elements, (ranking->capacity + BLOQUE)* sizeof(elemType));
            ranking->capacity += BLOQUE;
        }
        ranking->elements[ranking->size] = elem;
        ranking->size ++;
    }
}

size_t size(const rankingADT ranking){
    return ranking->size;
}

static void swap_up(rankingADT r, size_t idx){
    if (idx > 0 && idx < r->size) {
        elemType temp = r->elements[idx];
        r->elements[idx] = r->elements[idx - 1];
        r->elements[idx - 1] = temp;
    }
}

int getByRanking(rankingADT ranking, size_t n, elemType * elem){
    //Valido que el elemnto n exista
    if(n < 1 || n > ranking->size) return 0;
    size_t idx = n - 1;
    *elem = ranking->elements[idx];
    swap_up(ranking, idx);
    return 1;
}   

elemType * getTopRanking(const rankingADT ranking, size_t * top){
    // Casos borde: ranking vacío o se piden 0 elementos
    if (ranking->size == 0 || *top == 0) {
        *top = 0;
        return NULL;
    }
    // Si se piden más elementos de los que existen, ajustamos *top
    if (*top > ranking->size) {
        *top = ranking->size;
    }
    // Asignamos memoria para devolver el top
    elemType * topElements = malloc(*top * sizeof(elemType));
    for (size_t i = 0; i < *top; i++)
    {
        topElements[i] = ranking->elements[i];
    }
    return topElements;
}

int contains(rankingADT ranking, elemType elem){
    char encontrado = 0;
    for (size_t i = 0; i < ranking->size && !encontrado; i++)
    {
        if(ranking->cmp(ranking->elements[i], elem)){
            encontrado = 1;
            swap_up(ranking, i);
        }
    }
    return encontrado;  
}

void downByRanking(rankingADT ranking, size_t n){
    // Subir el elemento del índice 'n' equivale a bajar el elemento del puesto 'n'
    swap_up(ranking, n);
}

void freeRanking(rankingADT ranking){
    if (ranking != NULL) {
        free(ranking->elements);
        free(ranking);
    }
}

int position(const rankingADT ranking, elemType elem){
    for (size_t i = 0; i < ranking->size; i++)
    {
        if(ranking->cmp(ranking->elements[i], elem) == 0){
            return i + 1;
        }
    }
    return 0;
}