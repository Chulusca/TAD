#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	const char * person;
	unsigned int popularity;
	struct node * tail;
} node;

typedef node * TList;

TList upPop (TList list, const char * nombre, int incrementoPopularidad){
	//Caso base 1 (No existe la persona)
	if (list == NULL){
		TList nuevo = malloc(sizeof(node));
		nuevo->person = nombre;
		nuevo->popularity = incrementoPopularidad;
		nuevo->tail = NULL;
		return nuevo;
	}

	//Caso base, existe, incrementamos
	if(strcmp(list->person, nombre) == 0){
		list->popularity += incrementoPopularidad;
		return list;
	}

	list->tail = upPop(list->tail, nombre, incrementoPopularidad);

	if(list->tail != NULL && list->popularity < list->tail->popularity){
		const char * tmp_p     = list->person;
        unsigned int tmp_q     = list->popularity;
        list->person           = list->tail->person;
        list->popularity       = list->tail->popularity;
        list->tail->person     = tmp_p;
        list->tail->popularity = tmp_q;
	}	

	return list;

}