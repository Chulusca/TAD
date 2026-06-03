#include <stdio.h>
#include <stdlib.h>
#include "squirrelADT.h"

#define MAX_BLOCKS 1000
#define DISTANCE_TO_BLOCK(squirrelAdt, distance) (((distance) / (squirrelAdt)->blockSize))

struct row {
    size_t * squirrels;
    size_t dimCols;
};  

typedef struct squirrelCensusCDT{
    struct row * rows;
    size_t dimRows;
    size_t blockSize;
} squirrelCensusCDT;

squirrelCensusADT newSquirrelCensus(size_t blockSizeMeters){
    if (blockSizeMeters == 0) {
        return NULL; // Invalid block size
    }
    squirrelCensusADT toReturn = malloc(sizeof(squirrelCensusCDT));
    toReturn->blockSize = blockSizeMeters;
    toReturn->dimRows = 0;
    toReturn->rows = NULL; // Initialize rows to NULL
    return toReturn;
}

size_t countSquirrel(squirrelCensusADT squirrelAdt, size_t yDistance, size_t xDistance){
    size_t yIdx = DISTANCE_TO_BLOCK(squirrelAdt, yDistance);
    size_t xIdx = DISTANCE_TO_BLOCK(squirrelAdt, xDistance);
    if (yIdx >= squirrelAdt->dimRows) {
        squirrelAdt->rows = realloc(squirrelAdt->rows, (yIdx + 1) * sizeof(struct row));
        for (size_t i = squirrelAdt->dimRows; i <= yIdx; i++) {
            squirrelAdt->rows[i].squirrels = NULL;
            squirrelAdt->rows[i].dimCols = 0;
        }
        squirrelAdt->dimRows = yIdx + 1;
    }
    if (xIdx >= squirrelAdt->rows[yIdx].dimCols) {
        squirrelAdt->rows[yIdx].squirrels = realloc(squirrelAdt->rows[yIdx].squirrels, (xIdx + 1) * sizeof(size_t));
        for (size_t i = squirrelAdt->rows[yIdx].dimCols; i <= xIdx; i++) {
            squirrelAdt->rows[yIdx].squirrels[i] = 0;
        }
        squirrelAdt->rows[yIdx].dimCols = xIdx + 1;
    }

    return ++squirrelAdt->rows[yIdx].dimCols[yIdx].squirrels[xIdx];
}

size_t squirrelsInBlock(const squirrelCensusADT squirrlAdt, size_t yDist, size_t xDist){
    size_t yIdx = DISTANCE_TO_BLOCK(squirrelAdt, yDist);
    size_t xIdx = DISTANCE_TO_BLOCK(squirrelAdt, xDist);
    if (yIdx >= squirrelAdt->dimRows || xIdx >= squirrelAdt->rows[yIdx].dimCols) {
        return 0; // Fuera de los limites.
    }
    return squirrelAdt->rows[yIdx].squirrels[xIdx];
}

void freeSquirrelCensus(squirrelCensusADT squirrelAdt){
    for (size_t i = 0; i < squirrelAdt->dimRows; i++) {
        free(squirrelAdt->rows[i].squirrels);
    }
    free(squirrelAdt->rows);
    free(squirrelAdt);
}
