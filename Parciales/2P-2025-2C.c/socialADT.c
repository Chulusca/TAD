#include "socialADT.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BLOQUE 10

typedef struct influencerNode {
    influencerData data;
    struct influencerNode * next;
} influencerNode;

typedef struct socialCDT {
    influencerNode * first;
    size_t size; 
} socialCDT;

socialADT newSocial(void){
    socialADT newSocial = malloc(sizeof(socialCDT));
    newSocial->first = NULL;
    newSocial->size = 0;
    return newSocial;
}

influencerNode * addInfluencerRec(influencerNode * current, influencerNode * newNode){
    if (current == NULL) {
        return newNode;
    }
    if (current->data.followers > newNode->data.followers){
        newNode->next = current;
        return newNode;
    }
    current->next = addInfluencerRec(current->next, newNode);
    return current;
}

int addInfluencer(socialADT social, const char * id, size_t followers){
    //Tiene menos de 1000 no lo agrego.
    if (followers < 1000) return 0;
    influencerNode * newNode = malloc(sizeof(influencerNode));
    newNode->data.id = malloc(strlen(id) + 1);

    strcpy(newNode->data.id, id);
    newNode->data.followers = followers; 
    newNode->next = NULL;

    social->first = addInfluencerRec(social->first, newNode);
    social->size++;
    return 1;
}

influencerData * influencers(const socialADT social, size_t n, size_t * dim){
    //Casos donde no voy a encontrar influencers.
    if(n == 0 || social->size == 0) {
        *dim = 0;
        return NULL;
    }

    *dim = 0;
    int i = 0;
    int aumentos = 1;
    influencerNode * current = social->first;
    influencerData * vec = malloc(BLOQUE * sizeof(influencerData));

    while (current != NULL) {
        if (current->data.followers / 1000 == n){
            if(i == (aumentos*BLOQUE)){
                vec = realloc(vec, BLOQUE*(++aumentos) * sizeof(influencerData));
            }
            vec[i].followers = current->data.followers;
            vec[i].id = malloc(strlen(current->data.id) + 1);
            strcpy(vec[i].id, current->data.id);
            (*dim)++;
            i++;
        }
        current = current->next;
    }

    if(*dim == 0) {  
        free(vec);
        return NULL;
    }
    
    return vec;
} 