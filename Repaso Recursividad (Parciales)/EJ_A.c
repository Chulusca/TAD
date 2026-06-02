#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char digit;
    struct node * next;
} node;

typedef node * list;

list toDigits(unsigned long n){
    if(n == 0) return NULL;
    list newNode = malloc(sizeof(node));
    newNode->digit = n%10;
    newNode->next = toDigits(n/10);
    return newNode;
}

