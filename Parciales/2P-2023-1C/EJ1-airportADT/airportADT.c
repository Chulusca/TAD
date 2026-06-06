#include "airportADT.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node{
    char * head;
    struct node * tail;
} node;

typedef node * ListaAviones;

typedef struct Pista{
    size_t cantAviones;
    ListaAviones aviones;
    char ocupada;
} Pista;

typedef struct airportCDT{
    size_t cantPistas;
    size_t capacidadPistas;
    Pista * pistas;
} airportCDT;

airportADT newAirport(void){
    airportADT newAirport = malloc(sizeof(airportCDT));
    newAirport->cantPistas = 0;
    newAirport->capacidadPistas = 0;
    newAirport->pistas = NULL;
    return newAirport;
}

int addRunway(airportADT airport, size_t runwayId){
    if(airport == NULL || runwayId == 0) return -1;
    int idxPista = runwayId-1;

    //Si no tengo que pedir espacio
    if(runwayId <= airport->capacidadPistas){
        if(airport->pistas[idxPista].ocupada == 1){
            return -1;
        }
        //Añado
        airport->pistas[idxPista].ocupada = 1;
        airport->pistas[idxPista].aviones = NULL;
        airport->pistas[idxPista].cantAviones = 0;
        airport->cantPistas++;
        return airport->cantPistas;
    }

    //Si tengo que pedir espacio
    airport->pistas = realloc(airport->pistas, runwayId * sizeof(Pista));
    // Añado
    for (size_t i = airport->capacidadPistas; i < runwayId; i++)
    {
        airport->pistas[i].ocupada = 0;
        airport->pistas[i].aviones = NULL;
    }
    airport->pistas[idxPista].ocupada = 1;
    airport->pistas[idxPista].aviones = NULL;
    airport->pistas[idxPista].cantAviones = 0;

    airport->capacidadPistas = runwayId;
    airport->cantPistas++;
    return airport->cantPistas;
}

ListaAviones AddPlaneRec(ListaAviones l, const char * registration){
    if(l == NULL){
        ListaAviones newList = malloc(sizeof(node));
        newList->tail = NULL;
        newList->head = strdup(registration);
        return newList;
    }

    if(l->tail == NULL){
        ListaAviones newList = malloc(sizeof(node));
        newList->tail = NULL;
        newList->head = strdup(registration);
        l->tail = newList;
        return l;
    }
    l->tail = AddPlaneRec(l->tail, registration);
    return l;
}

int addPlaneToRunway(airportADT airport, size_t runwayId, const char * registration){
    int idxPista = runwayId-1;
    //Pista no existe.
    if(airport->capacidadPistas < runwayId || runwayId == 0) return -1;
    //Pista no esta ocupada
    if(airport->pistas[idxPista].ocupada == 0) return -1;

    //EXISTE
    airport->pistas[idxPista].aviones = addPlaneRec(airport->pistas[idxPista].aviones, registration);
    airport->pistas[idxPista].cantAviones++;
    return airport->pistas[idxPista].cantAviones;
}

char * takeOff(airportADT airport, size_t runwayId){
    int idxPista = runwayId-1;
    if(airport->capacidadPistas < runwayId || runwayId == 0) return NULL;
    if(airport->pistas[idxPista].ocupada == 0) return NULL;

    char * reg = strdup(airport->pistas[idxPista].aviones->head);
    ListaAviones auxL = airport->pistas[idxPista].aviones;
    auxL = airport->pistas[idxPista].aviones->tail;

    free(auxL->head);
    free(airport->pistas[idxPista].aviones);

    airport->pistas[idxPista].aviones = auxL;
    return reg;
}

char ** pendingFlights(airportADT airportAdt, size_t runwayId){
    //Cambiar logica de la lista
}

void freeAirport(airportADT airportAdt){
    //Free
}