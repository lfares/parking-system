#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/*************************************
    Functions for courtyard 1
**************************************/
void create_stack(Stack **s) {
    *s = malloc(sizeof(Stack)); 
    (*s)->begin = NULL;
    return;
}

void empty_stack(Stack **s) {
    Node *aux;
    while (!isEmpty_stack(*s)) {
        aux = (*s)->begin;
        (*s)->begin = (*s)->begin->next;
        free(aux);
    }
    free(*s);
    *s = NULL;
    return;
}

int checkSize_stack(Stack *s) {
    Node *aux = s->begin;
    int count = 0;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    return count;
}

int isFull_stack(Stack *s){
    if (checkSize_stack(s) == 10){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty_stack(Stack *s) {
    return (s->begin == NULL);
}

void push(Stack *s, elem x) {
    Node *aux = malloc(sizeof(Node)); 
    aux->info = x; 
    aux->next = s->begin;
    s->begin = aux;
    return;
}

int pop(Stack *s, elem *x) {
    Node *aux;
    if (isEmpty_stack(s))
        return 1; 
    *x = s->begin->info;
    aux = s->begin; 
    s->begin = s->begin->next; 
    free(aux); 
    return 0; 
}

/*************************************
    Functions for courtyard 2
**************************************/

void create_queue(Queue **q) {
    *q = malloc(sizeof(Queue)); 
    // make queue empty
    (*q)->begin = NULL;
    (*q)->end = NULL;
    return;
}

void empty_queue(Queue **q) {
    // erase all cars
    Node *aux;
    while ((*q)->begin != NULL) {
        aux = (*q)->begin;
        (*q)->begin = (*q)->begin->next;
        free(aux);
    }
    // erase queue
    free(*q);
    *q = NULL;
    return;
}

void in(Queue *q, elem x) {
    Node *aux;
    aux = malloc(sizeof(Node));
    aux->info = x;
    aux->next = NULL;
    if (!isEmpty_queue(q))
        q->end->next = aux;
    q->end = aux;
    if (isEmpty_queue(q))
        q->begin = aux;
    return;
}

int checkSize_queue(Queue *q) {
    Node *aux = q->begin;
    int count = 0;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    return count;
}

int out(Queue *q, elem *x) {
    Node *aux;
    if (isEmpty_queue(q))
        return 1; 
    *x = q->begin->info; 
    aux = q->begin; 
    q->begin = q->begin->next; 
    free(aux); 
    return 0; 
}

int isEmpty_queue(Queue *q) {
    return (q->begin == NULL);
}

int isFull_queue(Queue *q){
    if (checkSize_queue(q) == 10){
        return 1;
    }
    else{
        return 0;
    }
}