#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct airportCDT * airportADT;
/* Crea un sistema de administración de pistas y despegues de aviones
** de un aeropuerto.
** El sistema inicia sin pistas.
*/
airportADT newAirport(void);

/* Agrega una pista de despegue con el identificador runwayId.
** La pista inicia sin aviones.
** Retorna la cantidad actual de pistas en el sistema o -1 si falla.
** Falla si existe una pista con el identificador runwayId.
*/  
int addRunway(airportADT airportAdt, size_t runwayId);




/* Agrega al final de la pista de despegue con el identificador
** runwayId al avión de matrícula registration
** y retorna la cantidad actual de aviones en la pista o -1 si falla.
** Falla si la pista no existe.
*/
int addPlaneToRunway(airportADT airportAdt, size_t runwayId, const char * registration);

/* Elimina al avión que se encuentra al principio de la pista de
** despegue con el identificador runwayId
** y retorna la matrícula del avión eliminado o NULL si falla.
** Falla si la pista no existe.
** Falla si no hay aviones en la pista.
*/
char * takeOff(airportADT airportAdt, size_t runwayId);


/* Retorna un arreglo con las matrículas de los aviones que se
** encuentran en la pista de despegue con el identificador
** runwayId en orden inverso al orden de despegue (el último elemento
** del arreglo debe coincidir con el valor de retorno de una
** invocación a la función takeOff sobre esa pista).
** El arreglo debe ** contar con una cadena vacía "" como marca de fin.
** Si la pista no existe retorna NULL.
*/
char ** pendingFlights(airportADT airportAdt, size_t runwayId);


/* Libera los recursos utilizados por el sistema de administración de
** pistas y despegues de aviones de un aeropuerto.
*/
void freeAirport(airportADT airportAdt);




int
main(void) {
// Crea un sistema sin pistas
airportADT airportAdt = newAirport();
// Agrega la pista con el id 5
assert(addRunway(airportAdt, 5) == 1);
assert(addRunway(airportAdt, 0) == 2);
// Falla porque ya existe una pista con el id 5
assert(addRunway(airportAdt, 5) == -1);
// Falla porque no es válida la pista cero
assert(addRunway(airportAdt, 0) == -1);
// Agrega al final de la pista de id 5 al avión de matrícula AR01 y será
// el primero en despegar
char aux[20] = "AR01";
assert(addPlaneToRunway(airportAdt, 5, aux) == 1);
// Agrega al final de la pista de id 5 al avión de matrícula AC91 y será
// el segundo en despegar
strcpy(aux, "AC91");
assert(addPlaneToRunway(airportAdt, 5, aux) == 2);
strcpy(aux, "AC92");
assert(addPlaneToRunway(airportAdt, 5, aux) == 3);
// Obtiene los aviones por despegar de la pista de id 5 en orden inverso al
// orden de despegue
char ** aux = pendingFlights(airportAdt, 5);
assert(!strcmp(aux[0], "AC92"));
assert(!strcmp(aux[1], "AC91"));
assert(!strcmp(aux[2], "AR01"));
assert(!strcmp(aux[3], ""));
free(aux);
// Despega el primer avión de la pista de id 5
assert(!strcmp(takeOff(airportAdt, 5), "AR01"));
assert(!strcmp(takeOff(airportAdt, 5), "AC91"));
assert(!strcmp(takeOff(airportAdt, 5), "AC92"));
// Ya no quedan aviones por despegar en la pista de id 5
assert(takeOff(airportAdt, 5) == NULL);
// No existe la pista 3
assert(takeOff(airportAdt, 3) == NULL);
// No se puede agregar un avión a una pista que no existe
assert(addPlaneToRunway(airportAdt, 3, "FL91") == -1);
// No se puede agregar un avión a una pista que no existe
assert(pendingFlights(airportAdt, 3) == NULL);
freeAirport(airportAdt);
puts("Despegue exitoso!");
return 0;
}