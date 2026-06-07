#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bikeSharingADT.h"


//Calculo de inidice de estacion, idx = id-1
//Calculo de indice de dock, idx = id

typedef struct Stations{
    char * docks;
    size_t cantDocksLibres;
    size_t docksCount; //Cantidad, capacidad
    size_t cantBikes;
    char activa;
} Stations;

typedef struct bikeSharingCDT{
    Stations * listaStations;
    size_t capacidad;
    size_t estacionesActivas;
} bikeSharingCDT;

bikeSharingADT newBikeSharing(size_t maxStationsCount){
    bikeSharingADT newBikeSharing = malloc(sizeof(bikeSharingCDT));
    newBikeSharing->capacidad = maxStationsCount;
    newBikeSharing->listaStations = calloc(maxStationsCount, sizeof(Stations));
    newBikeSharing->estacionesActivas = 0;
    return newBikeSharing;
}

int addStation(bikeSharingADT bikeSharing, size_t stationId, size_t docksCount){
    //Validar que el stationId este en rango.
    if (bikeSharing == NULL) return -1;
    if (stationId > bikeSharing->capacidad || stationId < 1) return -1;
    int idx = stationId-1;

    //Existe estacion con el id
    if(bikeSharing->listaStations[idx].activa == 1) return -1; 

    bikeSharing->listaStations[idx].docksCount = docksCount;
    bikeSharing->listaStations[idx].cantBikes = docksCount;
    bikeSharing->listaStations[idx].activa = 1;
    bikeSharing->listaStations[idx].docks = malloc(sizeof(char) * docksCount);
    bikeSharing->listaStations[idx].cantDocksLibres = 0;
    bikeSharing->estacionesActivas++;

    for (size_t i = 0; i < docksCount; i++)
    {
        bikeSharing->listaStations[idx].docks[i] = 1;
    }
    return bikeSharing->estacionesActivas;  
}

size_t rentBike(bikeSharingADT bikeSharing, size_t stationId, size_t dockId){
    //VALIDO EL ADT
    if (bikeSharing == NULL) return -1;
    //Valido rango de station
    if (stationId > bikeSharing->capacidad || stationId < 1) return -1;
    int idx = stationId-1;
    //Valido que la estacion sea invalida
    if(bikeSharing->listaStations[idx].activa == 0) return -1;
    //Valido si el dockId es invalido
    if (dockId > bikeSharing->listaStations[idx].docksCount-1) return -1;
    //Valido si no existe bicicleta
    if (bikeSharing->listaStations[idx].docks[dockId] == 0) return -1;

    bikeSharing->listaStations[idx].docks[dockId] = 0;
    bikeSharing->listaStations[idx].cantBikes--;
    bikeSharing->listaStations[idx].cantDocksLibres++;
    return 0;
}

size_t bikesAvailable(bikeSharingADT bikeSharing, size_t stationId){
    //VALIDO EL ADT
    if (bikeSharing == NULL) return -1;
    //Valido rango de station
    if (stationId > bikeSharing->capacidad || stationId < 1) return -1;
    int idx = stationId-1;
    if(bikeSharing->listaStations[idx].activa == 0) return -1;

    return bikeSharing->listaStations[idx].cantBikes;
}

size_t returnBike(bikeSharingADT bikeSharing, size_t stationId, size_t dockId){
    if (bikeSharing == NULL) return -1;

    //Validar stationId.
    if (stationId > bikeSharing->capacidad || stationId < 1) return -1;
    int idx = stationId-1;
    if(bikeSharing->listaStations[idx].activa == 0) return -1;

    //Valido si el dockId es invalido
    if (dockId > bikeSharing->listaStations[idx].docksCount-1) return -1;
    //Valido si no existe bicicleta
    if (bikeSharing->listaStations[idx].docks[dockId] == 1) return -1;

    bikeSharing->listaStations[idx].docks[dockId] = 1;
    bikeSharing->listaStations[idx].cantBikes++;
    bikeSharing->listaStations[idx].cantDocksLibres--;

    return 0;
}

size_t docksAvailable(bikeSharingADT bikeSharing, size_t stationId){
    if (bikeSharing == NULL) return -1;

    //Validar stationId.
    if (stationId > bikeSharing->capacidad || stationId < 1) return -1;
    int idx = stationId-1;
    if(bikeSharing->listaStations[idx].activa == 0) return -1;

    return bikeSharing->listaStations[idx].cantDocksLibres;
}

/* Libera todos los recursos utilizados */
void freeBikeSharing(bikeSharingADT bikeSharing){
    if (bikeSharing == NULL) return;

    for (size_t i = 0; i < bikeSharing->capacidad; i++)
    {
        free(bikeSharing->listaStations[i].docks);
    }
    free(bikeSharing->listaStations);
    free(bikeSharing);
}