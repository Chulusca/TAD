#include "polyADT.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct polyCDT{
    int degree;
    float coef; 
    struct polyCDT * tail;
} polyCDT;

polyADT newPolynomial(void){
    return NULL;
}

int isEmpty (polyADT poly){
    return poly == NULL;
}

static polyADT addTermRec(polyADT poly, float coef, int degree, int *exists){
    if(isEmpty(poly) || poly->degree < degree){
        polyADT aux = malloc(sizeof(polyADT));
        aux->degree = degree;
        aux->coef = coef;
        aux->tail = poly;
        return aux;
    }
    if (poly->degree == degree){
        *exists = 0;
        return poly;
    }
    poly->tail = addTermRec(poly->tail, coef, degree, exists);
    return poly;
}

int addTerm(polyADT* poly, float coef, int degree){
    int existe = 1;
    poly = addTermRec(*poly, coef, degree, &existe);
    return existe;
}

polyADT addPolynomial(polyADT p, polyADT q){
    if (p == NULL && q == NULL) return NULL;
    if (q == NULL) return addPolynomial(q, p);
//Base
    polyADT newPol = malloc(sizeof(polyADT));
    if(p == NULL || q->degree > p->degree){
        newPol->coef = q->coef;
        newPol->degree = q->degree;
        newPol->tail = addPolynomial(p, q->tail);
        return newPol;
    }
    if (q->degree < p->degree) {
        newPol->coef = p->coef;
        newPol->degree = p->degree;
        newPol->tail = addPolynomial(p->tail, q);
        return newPol;
    }
    newPol->coef = p->coef + q->coef;
    newPol->degree = p->degree;
    newPol->tail = addPolynomial(p->tail, q->tail);
    return newPol;
}
